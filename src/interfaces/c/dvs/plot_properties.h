#ifndef DVS_PLOT_PROPERTIES_H_
#define DVS_PLOT_PROPERTIES_H_

#include "dvs/communication_header_object.h"
#include "dvs/enumerations.h"

#define PROPERTY_TYPE_SERIALIZATION_TYPE uint8_t

CommunicationHeaderObject Color(const uint8_t red, const uint8_t green, const uint8_t blue)
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + 3U * sizeof(uint8_t);

    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_COLOR;
    hdr_obj.data[1U] = red;
    hdr_obj.data[2U] = green;
    hdr_obj.data[3U] = blue;

    return hdr_obj;
}

CommunicationHeaderObject FaceColor(const uint8_t red, const uint8_t green, const uint8_t blue)
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t) + 3U * sizeof(uint8_t);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_FACE_COLOR;
    hdr_obj.data[1U] = red;
    hdr_obj.data[2U] = green;
    hdr_obj.data[3U] = blue;
    hdr_obj.data[4U] = 1U;  // TODO: use_color

    return hdr_obj;
}

CommunicationHeaderObject EdgeColor(const uint8_t red, const uint8_t green, const uint8_t blue)
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t) + 3U * sizeof(uint8_t);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_EDGE_COLOR;
    hdr_obj.data[1U] = red;
    hdr_obj.data[2U] = green;
    hdr_obj.data[3U] = blue;
    hdr_obj.data[4U] = 1U;  // TODO: use_color

    return hdr_obj;
}

CommunicationHeaderObject ColorMapJet()
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_COLOR_MAP;
    hdr_obj.data[1U] = (uint8_t)CM_JET;

    return hdr_obj;
}

CommunicationHeaderObject ColorMapHsv()
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_COLOR_MAP;
    hdr_obj.data[1U] = (uint8_t)CM_HSV;

    return hdr_obj;
}

CommunicationHeaderObject ColorMapMagma()
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t);
    memset(hdr_obj.data, 0, kMaxNumFunctionHeaderBytes);

    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_COLOR_MAP;
    hdr_obj.data[1U] = (uint8_t)CM_MAGMA;

    return hdr_obj;
}

CommunicationHeaderObject ColorMapViridis()
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_COLOR_MAP;
    hdr_obj.data[1U] = (uint8_t)CM_VIRIDIS;

    return hdr_obj;
}

CommunicationHeaderObject ColorMapPastel()
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_COLOR_MAP;
    hdr_obj.data[1U] = (uint8_t)CM_PASTEL;

    return hdr_obj;
}

CommunicationHeaderObject ColorMapJetSoft()
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_COLOR_MAP;
    hdr_obj.data[1U] = (uint8_t)CM_JET_SOFT;

    return hdr_obj;
}

CommunicationHeaderObject ColorMapJetBright()
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_COLOR_MAP;
    hdr_obj.data[1U] = (uint8_t)CM_JET_BRIGHT;

    return hdr_obj;
}

CommunicationHeaderObject Alpha(const float alpha)
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(float);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_ALPHA;
    memcpy(hdr_obj.data + 1U, &alpha, sizeof(float));

    return hdr_obj;
}

CommunicationHeaderObject PointSize(const int8_t point_size)
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_POINT_SIZE;
    hdr_obj.data[1U] = point_size;

    return hdr_obj;
}

CommunicationHeaderObject LineWidth(const uint8_t line_width)
{
    CommunicationHeaderObject hdr_obj;

    hdr_obj.type = CHOT_PROPERTY;
    hdr_obj.num_bytes = sizeof(uint8_t) + sizeof(uint8_t);
    hdr_obj.data[0U] = (PROPERTY_TYPE_SERIALIZATION_TYPE)PT_LINE_WIDTH;
    hdr_obj.data[1U] = line_width;

    return hdr_obj;
}
#endif  // DVS_PLOT_PROPERTIES_H_
