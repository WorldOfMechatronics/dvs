#ifndef DVS_INTERNAL_H_
#define DVS_INTERNAL_H_

#include <stdint.h>

#include "dvs/communication.h"
#include "dvs/communication_header.h"
#include "dvs/internal.h"
#include "dvs/math/math.h"
#include "dvs/uint8_array.h"

const uint64_t kMagicNumber = 0xdeadbeefcafebabe;
const uint64_t kMaxNumBytesForOneTransmission = 1380;
const uint64_t kTcpPortNum = 9755;

int checkAck(char data[256])
{
    const int ack_received = data[0] == 'a' && data[1] == 'c' && data[2] == 'k' && data[3] == '#' && data[4] == '\0';
    return ack_received;
}

uint8_t isBigEndian()
{
    const uint32_t x = 1;
    const uint8_t* const ptr = (uint8_t*)(&x);

    if (ptr[0] == '\x01')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

uint64_t minVal(const uint64_t v0, const uint64_t v1)
{
    if (v0 < v1)
    {
        return v0;
    }
    else
    {
        return v1;
    }
}

void sendThroughTcpInterface(const uint8_t* const data_blob, const uint64_t num_bytes)
{
    int tcp_sockfd;
    struct sockaddr_in tcp_servaddr;

    tcp_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&tcp_servaddr, sizeof(tcp_servaddr));

    tcp_servaddr.sin_family = AF_INET;
    tcp_servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    tcp_servaddr.sin_port = htons(kTcpPortNum);

    if (connect(tcp_sockfd, (struct sockaddr*)&tcp_servaddr, sizeof(tcp_servaddr)) == (-1))
    {
        printf("Failed to connect!\n");
    }

    const uint64_t num_bytes_to_send = num_bytes;

    write(tcp_sockfd, &num_bytes_to_send, sizeof(uint64_t));
    write(tcp_sockfd, data_blob, num_bytes);

    close(tcp_sockfd);
}

#define APPEND_PROPERTIES(__hdr, __first_prop)                 \
    {                                                          \
        va_list __args;                                        \
        va_start(__args, __first_prop);                        \
                                                               \
        CommunicationHeaderObject __prp = __first_prop;        \
        while (__prp.type != CHOT_UNKNOWN)                     \
        {                                                      \
            appendProperty(&__hdr, &__prp);                    \
            __prp = va_arg(__args, CommunicationHeaderObject); \
        }                                                      \
        va_end(__args);                                        \
    }

#define APPEND_OBJ(__hdr, __type, __val, __target_data_type)                                                        \
    {                                                                                                               \
        CommunicationHeaderObject* const __current_obj = (__hdr)->objects + (__hdr)->obj_idx;                       \
        __current_obj->type = __type;                                                                               \
        __current_obj->num_bytes = sizeof(__target_data_type);                                                      \
        __target_data_type __tmp_val = __val;                                                                       \
        memcpy(__current_obj->data, &__tmp_val, sizeof(__target_data_type));                                        \
        appendObjectIndexToCommunicationHeaderObjectLookupTable(&((__hdr)->objects_lut), __type, (__hdr)->obj_idx); \
        (__hdr)->obj_idx += 1;                                                                                      \
    }

typedef void (*SendFunction)(const uint8_t* const, const uint64_t);

SendFunction getSendFunction()
{
    return sendThroughTcpInterface;
}

#define COMMUNICATION_HEADER_OBJECT_TYPE_TRANSMISSION_TYPE uint16_t
#define COMMUNICATION_HEADER_OBJECT_NUM_BYTES_TRANSMISSION_TYPE uint8_t

int countNumHeaderBytes(const CommunicationHeader* const hdr)
{
    // 2 for first two bytes, that indicates how many objects and
    // props there will be in the buffer
    size_t s = 2;

    s += sizeof(Function);

    // Object look up table
    s += sizeof(uint8_t) + hdr->objects_lut.size;

    // Properties look up table
    s += sizeof(uint8_t) + hdr->props_lut.size;

    const size_t base_size = sizeof(COMMUNICATION_HEADER_OBJECT_TYPE_TRANSMISSION_TYPE) +
                             sizeof(COMMUNICATION_HEADER_OBJECT_NUM_BYTES_TRANSMISSION_TYPE);

    for (size_t k = 0; k < hdr->obj_idx; k++)
    {
        s += base_size + hdr->objects[k].num_bytes;
    }

    for (size_t k = 0; k < hdr->prop_idx; k++)
    {
        s += base_size + hdr->props[k].num_bytes;
    }

    s += NUM_FLAGS;

    return s;
}

void fillBufferWithHeader(const CommunicationHeader* const hdr, uint8_t* const buffer)
{
    // #define COMMUNICATION_HEADER_OBJECT_TYPE_TRANSMISSION_TYPE uint16_t
    // enum class CommunicationHeaderObjectType : uint16_t

    size_t idx = 0U;
    buffer[idx] = (uint8_t)(hdr->obj_idx);
    idx++;

    buffer[idx] = (uint8_t)(hdr->prop_idx);
    idx++;

    buffer[idx] = (uint8_t)(hdr->function);
    idx++;

    // Objects look up table
    buffer[idx] = (uint8_t)(hdr->objects_lut.size);
    idx++;

    memcpy(buffer + idx, hdr->objects_lut.data, hdr->objects_lut.size);
    idx += hdr->objects_lut.size;

    // Properties look up table
    buffer[idx] = (uint8_t)(hdr->props_lut.size);
    idx++;

    memcpy(buffer + idx, hdr->props_lut.data, hdr->props_lut.size);
    idx += hdr->props_lut.size;

    const CommunicationHeaderObject* const objects = hdr->objects;

    for (size_t k = 0; k < hdr->obj_idx; k++)
    {
        memcpy(&(buffer[idx]), &(objects[k].type), sizeof(COMMUNICATION_HEADER_OBJECT_TYPE_TRANSMISSION_TYPE));
        idx += sizeof(COMMUNICATION_HEADER_OBJECT_TYPE_TRANSMISSION_TYPE);

        memcpy(
            &(buffer[idx]), &(objects[k].num_bytes), sizeof(COMMUNICATION_HEADER_OBJECT_NUM_BYTES_TRANSMISSION_TYPE));
        idx += sizeof(COMMUNICATION_HEADER_OBJECT_NUM_BYTES_TRANSMISSION_TYPE);

        memcpy(&(buffer[idx]), objects[k].data, objects[k].num_bytes);
        idx += objects[k].num_bytes;
    }

    memcpy(buffer + idx, hdr->flags, NUM_FLAGS);
}

void sendHeaderAndByteArray(SendFunction send_function,
                            const uint8_t* const array,
                            const size_t num_bytes_from_array,
                            CommunicationHeader* hdr)
{
    const uint64_t num_bytes_hdr = countNumHeaderBytes(hdr);

    // + 1 bytes for endianness byte
    // + 2 * sizeof(uint64_t) for magic number and number of bytes in transfer
    const uint64_t num_bytes = num_bytes_from_array + num_bytes_hdr + 1 + 2 * sizeof(uint64_t);

    uint8_t* const data_blob = malloc(num_bytes);

    uint64_t idx = 0;
    data_blob[idx] = isBigEndian();
    idx += 1;

    memcpy(&(data_blob[idx]), &kMagicNumber, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    memcpy(&(data_blob[sizeof(uint64_t) + 1]), &num_bytes, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    fillBufferWithHeader(hdr, &(data_blob[idx]));
    idx += num_bytes_hdr;

    memcpy(&(data_blob[idx]), array, num_bytes_from_array);
    idx += num_bytes_from_array;

    send_function(data_blob, num_bytes);

    free(data_blob);
}

void sendHeaderAndTwoByteArrays(SendFunction send_function,
                                const uint8_t* const array0,
                                const size_t num_bytes_from_array0,
                                const uint8_t* const array1,
                                const size_t num_bytes_from_array1,
                                CommunicationHeader* hdr)
{
    const uint64_t num_bytes_hdr = countNumHeaderBytes(hdr);

    // + 1 bytes for endianness byte
    // + 2 * sizeof(uint64_t) for magic number and number of bytes in transfer
    const uint64_t num_bytes = num_bytes_from_array0 + num_bytes_from_array1 + num_bytes_hdr + 1 + 2 * sizeof(uint64_t);

    uint8_t* const data_blob = malloc(num_bytes);

    uint64_t idx = 0;
    data_blob[idx] = isBigEndian();
    idx += 1;

    memcpy(&(data_blob[idx]), &kMagicNumber, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    memcpy(&(data_blob[sizeof(uint64_t) + 1]), &num_bytes, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    fillBufferWithHeader(hdr, &(data_blob[idx]));
    idx += num_bytes_hdr;

    memcpy(&(data_blob[idx]), array0, num_bytes_from_array0);
    idx += num_bytes_from_array0;

    memcpy(&(data_blob[idx]), array1, num_bytes_from_array1);
    idx += num_bytes_from_array1;

    send_function(data_blob, num_bytes);

    free(data_blob);
}

void sendHeaderAndTwoVectors(SendFunction send_function,
                             const Vector* const x,
                             const Vector* const y,
                             CommunicationHeader* hdr)
{
    const uint64_t num_bytes_hdr = countNumHeaderBytes(hdr);
    const uint64_t num_bytes_one_vector = x->num_elements * x->num_bytes_per_element;

    const uint64_t num_bytes_from_object = 2 * num_bytes_one_vector + num_bytes_hdr;

    // + 1 bytes for endianness byte
    // + 2 * sizeof(uint64_t) for magic number and number of bytes in transfer
    const uint64_t num_bytes = num_bytes_from_object + 1 + 2 * sizeof(uint64_t);

    uint8_t* const data_blob = malloc(num_bytes);

    uint64_t idx = 0;
    data_blob[idx] = isBigEndian();
    idx += 1;

    memcpy(&(data_blob[idx]), &kMagicNumber, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    memcpy(&(data_blob[sizeof(uint64_t) + 1]), &num_bytes, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    fillBufferWithHeader(hdr, &(data_blob[idx]));
    idx += num_bytes_hdr;

    memcpy(&(data_blob[idx]), x->data, num_bytes_one_vector);
    idx += num_bytes_one_vector;

    memcpy(&(data_blob[idx]), y->data, num_bytes_one_vector);
    idx += num_bytes_one_vector;

    send_function(data_blob, num_bytes);

    free(data_blob);
}

void sendHeaderAndThreeMatrices(SendFunction send_function,
                                const Matrix* const x,
                                const Matrix* const y,
                                const Matrix* const z,
                                CommunicationHeader* hdr)
{
    const uint64_t num_bytes_hdr = countNumHeaderBytes(hdr);
    const uint64_t num_bytes_one_matrix = x->num_rows * x->num_cols * x->num_bytes_per_element;

    const uint64_t num_bytes_from_object = 3 * num_bytes_one_matrix + num_bytes_hdr;

    // + 1 bytes for endianness byte
    // + 2 * sizeof(uint64_t) for magic number and number of bytes in transfer
    const uint64_t num_bytes = num_bytes_from_object + 1 + 2 * sizeof(uint64_t);

    uint8_t* const data_blob = malloc(num_bytes);

    uint64_t idx = 0;
    data_blob[idx] = isBigEndian();
    idx += 1;

    memcpy(&(data_blob[idx]), &kMagicNumber, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    memcpy(&(data_blob[sizeof(uint64_t) + 1]), &num_bytes, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    fillBufferWithHeader(hdr, &(data_blob[idx]));
    idx += num_bytes_hdr;

    memcpy(&(data_blob[idx]), x->data, num_bytes_one_matrix);
    idx += num_bytes_one_matrix;

    memcpy(&(data_blob[idx]), y->data, num_bytes_one_matrix);
    idx += num_bytes_one_matrix;

    memcpy(&(data_blob[idx]), z->data, num_bytes_one_matrix);
    idx += num_bytes_one_matrix;

    send_function(data_blob, num_bytes);

    free(data_blob);
}

void sendHeaderAndThreeVectors(SendFunction send_function,
                               const Vector* const x,
                               const Vector* const y,
                               const Vector* const z,
                               CommunicationHeader* hdr)
{
    const uint64_t num_bytes_hdr = countNumHeaderBytes(hdr);
    const uint64_t num_bytes_one_vector = x->num_elements * x->num_bytes_per_element;

    const uint64_t num_bytes_from_object = 3 * num_bytes_one_vector + num_bytes_hdr;

    // + 1 bytes for endianness byte
    // + 2 * sizeof(uint64_t) for magic number and number of bytes in transfer
    const uint64_t num_bytes = num_bytes_from_object + 1 + 2 * sizeof(uint64_t);

    uint8_t* const data_blob = malloc(num_bytes);

    uint64_t idx = 0;
    data_blob[idx] = isBigEndian();
    idx += 1;

    memcpy(&(data_blob[idx]), &kMagicNumber, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    memcpy(&(data_blob[sizeof(uint64_t) + 1]), &num_bytes, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    fillBufferWithHeader(hdr, &(data_blob[idx]));
    idx += num_bytes_hdr;

    memcpy(&(data_blob[idx]), x->data, num_bytes_one_vector);
    idx += num_bytes_one_vector;

    memcpy(&(data_blob[idx]), y->data, num_bytes_one_vector);
    idx += num_bytes_one_vector;

    memcpy(&(data_blob[idx]), z->data, num_bytes_one_vector);
    idx += num_bytes_one_vector;

    send_function(data_blob, num_bytes);

    free(data_blob);
}

void sendHeader(SendFunction send_function, CommunicationHeader* hdr)
{
    const uint64_t num_bytes_hdr = countNumHeaderBytes(hdr);

    // + 1 bytes for endianness byte
    // + 2 * sizeof(uint64_t) for magic number and number of bytes in transfer
    const uint64_t num_bytes = num_bytes_hdr + 1 + 2 * sizeof(uint64_t);

    uint8_t* const data_blob = malloc(num_bytes);

    uint64_t idx = 0;
    data_blob[idx] = isBigEndian();
    idx += 1;

    memcpy(&(data_blob[idx]), &kMagicNumber, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    memcpy(&(data_blob[sizeof(uint64_t) + 1]), &num_bytes, sizeof(uint64_t));
    idx += sizeof(uint64_t);

    fillBufferWithHeader(hdr, &(data_blob[idx]));
    idx += num_bytes_hdr;

    send_function(data_blob, num_bytes);

    free(data_blob);
}

#endif  // DVS_INTERNAL_H_
