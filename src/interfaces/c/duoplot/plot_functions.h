#ifndef DUOPLOT_PLOT_FUNCTIONS_H
#define DUOPLOT_PLOT_FUNCTIONS_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "duoplot/communication_header.h"
#include "duoplot/internal.h"
#include "duoplot/math/math.h"
#include "duoplot/pp.h"
#include "duoplot/structures.h"

DUOPLOT_WEAK void duoplot_internal_plotFunction3D(const Vector* const x,
                                                  const Vector* const y,
                                                  const Vector* const z,
                                                  const Function fcn,
                                                  const duoplot_internal_CommunicationHeaderObject first_prop,
                                                  ...)
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, fcn);

    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_DATA_TYPE, x->data_type, uint8_t);
    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_NUM_ELEMENTS, x->num_elements, uint32_t);

    DUOPLOT_INTERNAL_APPEND_PROPERTIES(hdr, first_prop);

    duoplot_internal_sendHeaderAndThreeVectors(duoplot_internal_getSendFunction(), x, y, z, &hdr);
}

DUOPLOT_WEAK void duoplot_internal_plotFunction2D(const Vector* const x,
                                                  const Vector* const y,
                                                  const Function fcn,
                                                  const duoplot_internal_CommunicationHeaderObject first_prop,
                                                  ...)
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, fcn);

    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_DATA_TYPE, x->data_type, uint8_t);
    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_NUM_ELEMENTS, x->num_elements, uint32_t);

    DUOPLOT_INTERNAL_APPEND_PROPERTIES(hdr, first_prop);

    duoplot_internal_sendHeaderAndTwoVectors(duoplot_internal_getSendFunction(), x, y, &hdr);
}

DUOPLOT_WEAK void duoplot_internal_surfFunction(const Matrix* const x,
                                                const Matrix* const y,
                                                const Matrix* const z,
                                                const duoplot_internal_CommunicationHeaderObject first_prop,
                                                ...)
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, F_SURF);

    duoplot_internal_Dimension2D dims = {x->num_rows, x->num_cols};

    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_DATA_TYPE, x->data_type, uint8_t);
    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_NUM_ELEMENTS, x->num_rows * x->num_cols, uint32_t);  // Needed?
    duoplot_internal_appendDims(&hdr, CHOT_DIMENSION_2D, dims);

    DUOPLOT_INTERNAL_APPEND_PROPERTIES(hdr, first_prop);

    duoplot_internal_sendHeaderAndThreeMatrices(duoplot_internal_getSendFunction(), x, y, z, &hdr);
}

DUOPLOT_WEAK void duoplot_internal_drawMeshFunction(const Point3DArray vertices,
                                                    const IndexTripletArray indices,
                                                    const duoplot_internal_CommunicationHeaderObject first_prop,
                                                    ...)
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, F_DRAW_MESH);

    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_DATA_TYPE, DT_DOUBLE, uint8_t);
    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_NUM_ELEMENTS, indices.num_elements, uint32_t);
    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_NUM_VERTICES, vertices.num_elements, uint32_t);
    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_NUM_INDICES, indices.num_elements, uint32_t);

    DUOPLOT_INTERNAL_APPEND_PROPERTIES(hdr, first_prop);

    duoplot_internal_sendHeaderAndTwoByteArrays(duoplot_internal_getSendFunction(),
                                                (uint8_t*)(vertices.elements),
                                                vertices.num_elements * sizeof(Triangle3DD),
                                                (uint8_t*)(indices.elements),
                                                indices.num_elements * sizeof(IndexTriplet),
                                                &hdr);
}

DUOPLOT_WEAK void duoplot_internal_imShowFunction(const ImageC3* const img,
                                                  const duoplot_internal_CommunicationHeaderObject first_prop,
                                                  ...)
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, F_IM_SHOW);

    duoplot_internal_Dimension2D dims = {img->num_rows, img->num_cols};

    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_DATA_TYPE, img->data_type, uint8_t);
    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_NUM_CHANNELS, 3, uint8_t);
    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_NUM_ELEMENTS, img->num_rows * img->num_cols, uint32_t);  // Needed?
    duoplot_internal_appendDims(&hdr, CHOT_DIMENSION_2D, dims);

    DUOPLOT_INTERNAL_APPEND_PROPERTIES(hdr, first_prop);

    duoplot_internal_sendHeaderAndByteArray(
        duoplot_internal_getSendFunction(),
        (uint8_t*)(img->data),
        img->num_rows * img->num_cols * 3 * duoplot_internal_dataTypeToNumBytes(img->data_type),
        &hdr);
}

#define duoplot_imShow(img, ...) \
    duoplot_internal_imShowFunction((ImageC3*)&img, ##__VA_ARGS__, duoplot_internal_getLastCommHdrObj())

#define duoplot_drawMesh(vertices, indices, ...) \
    duoplot_internal_drawMeshFunction(vertices, indices, ##__VA_ARGS__, duoplot_internal_getLastCommHdrObj())

#define duoplot_surf(x, y, z, ...) \
    duoplot_internal_surfFunction( \
        (Matrix*)&x, (Matrix*)&y, (Matrix*)&z, ##__VA_ARGS__, duoplot_internal_getLastCommHdrObj())

#define duoplot_plot(x, y, ...)      \
    duoplot_internal_plotFunction2D( \
        (Vector*)&x, (Vector*)&y, F_PLOT2, ##__VA_ARGS__, duoplot_internal_getLastCommHdrObj())

#define duoplot_scatter(x, y, ...)   \
    duoplot_internal_plotFunction2D( \
        (Vector*)&x, (Vector*)&y, F_SCATTER2, ##__VA_ARGS__, duoplot_internal_getLastCommHdrObj())

#define duoplot_plot3(x, y, z, ...)  \
    duoplot_internal_plotFunction3D( \
        (Vector*)&x, (Vector*)&y, (Vector*)&z, F_PLOT3, ##__VA_ARGS__, duoplot_internal_getLastCommHdrObj())

#define duoplot_scatter3(x, y, z, ...) \
    duoplot_internal_plotFunction3D(   \
        (Vector*)&x, (Vector*)&y, (Vector*)&z, F_SCATTER3, ##__VA_ARGS__, duoplot_internal_getLastCommHdrObj())

DUOPLOT_WEAK void duoplot_setCurrentElement(const char* const name)
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, F_SET_CURRENT_ELEMENT);

    duoplot_internal_CommunicationHeaderObject* const current_obj = hdr.objects + hdr.obj_idx;

    current_obj->type = CHOT_ELEMENT_NAME;

    const size_t name_length = strnlen(name, 100U);
    current_obj->num_bytes = sizeof(uint8_t) + sizeof(uint8_t) + (uint8_t)name_length;

    memset(current_obj->data, 0, DUOPLOT_INTERNAL_MAX_NUM_FUNCTION_HEADER_BYTES);

    current_obj->data[0U] = PT_NAME;
    current_obj->data[1U] = name_length;
    memcpy(current_obj->data + 2U, name, name_length);

    duoplot_internal_appendObjectIndexToCommunicationHeaderObjectLookupTable(
        &(hdr.objects_lut), CHOT_ELEMENT_NAME, hdr.obj_idx);

    hdr.obj_idx += 1;

    duoplot_internal_sendHeader(duoplot_internal_getSendFunction(), &hdr);
}

DUOPLOT_WEAK void duoplot_clearView()
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, F_CLEAR);

    duoplot_internal_sendHeader(duoplot_internal_getSendFunction(), &hdr);
}

DUOPLOT_WEAK void duoplot_softClearView()
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, F_SOFT_CLEAR);

    duoplot_internal_sendHeader(duoplot_internal_getSendFunction(), &hdr);
}

DUOPLOT_WEAK void duoplot_view(const float azimuth, const float elevation)
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, F_VIEW);

    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_AZIMUTH, azimuth, float);
    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_ELEVATION, elevation, float);

    duoplot_internal_sendHeader(duoplot_internal_getSendFunction(), &hdr);
}

DUOPLOT_WEAK void duoplot_axis(const Vec3D min_bound, const Vec3D max_bound)
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, F_AXES_3D);

    typedef struct S_Bnd3D
    {
        Vec3D min_bnd;
        Vec3D max_bnd;
    } Bnd3D;

    const Bnd3D bnd = {min_bound, max_bound};

    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_AXIS_MIN_MAX_VEC, bnd, Bnd3D);

    duoplot_internal_sendHeader(duoplot_internal_getSendFunction(), &hdr);
}

DUOPLOT_WEAK void duoplot_axis2D(const Vec2D min_bound, const Vec2D max_bound)
{
    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, F_AXES_3D);

    typedef struct S_Bnd3D
    {
        Vec3D min_bnd;
        Vec3D max_bnd;
    } Bnd3D;
    const Vec3D v0 = {min_bound.x, min_bound.y, 0.0};
    const Vec3D v1 = {max_bound.x, max_bound.y, 0.0};

    const Bnd3D bnd = {v0, v1};

    DUOPLOT_INTERNAL_APPEND_OBJ(&hdr, CHOT_AXIS_MIN_MAX_VEC, bnd, Bnd3D);

    duoplot_internal_sendHeader(duoplot_internal_getSendFunction(), &hdr);
}

DUOPLOT_WEAK void duoplot_setTitle(const char* const title)
{
    if (title == NULL || title[0] == '\0')
    {
        return;
    }

    duoplot_internal_CommunicationHeader hdr;
    duoplot_internal_initCommunicationHeader(&hdr, F_SET_TITLE);

    duoplot_internal_CommunicationHeaderObject* const current_obj = hdr.objects + hdr.obj_idx;

    current_obj->type = CHOT_TITLE_STRING;

    const size_t name_length = strnlen(title, 100U);
    current_obj->num_bytes = sizeof(uint8_t) + sizeof(uint8_t) + (uint8_t)name_length;

    memset(current_obj->data, 0, DUOPLOT_INTERNAL_MAX_NUM_FUNCTION_HEADER_BYTES);

    current_obj->data[0U] = PT_NAME;
    current_obj->data[1U] = name_length;
    memcpy(current_obj->data + 2U, title, name_length);

    duoplot_internal_appendObjectIndexToCommunicationHeaderObjectLookupTable(
        &(hdr.objects_lut), CHOT_TITLE_STRING, hdr.obj_idx);

    hdr.obj_idx += 1;

    duoplot_internal_sendHeader(duoplot_internal_getSendFunction(), &hdr);
}

#endif  // DUOPLOT_PLOT_FUNCTIONS_H