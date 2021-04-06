#ifndef DVS_ENUMS_H_
#define DVS_ENUMS_H_

#include <stdint.h>

namespace dvs
{
namespace internal
{

enum class FunctionHeaderObjectType : uint16_t
{
    UNKNOWN,
    FUNCTION,
    NUM_BUFFERS_REQUIRED,
    NUM_BYTES,
    DATA_STRUCTURE,
    BYTES_PER_ELEMENT,
    DATA_TYPE,
    NUM_ELEMENTS,
    DIMENSION_2D,
    HAS_PAYLOAD,
    AZIMUTH,
    ELEVATION,
    AXES_DIMENSIONS,
    AXIS_MIN_MAX_VEC,
    POS2D,
    FIGURE_NUM,
    PROPERTY
};

enum class PropertyType : uint8_t
{
    UNKNOWN,
    LINE_WIDTH,
    ALPHA,
    NAME,
    LINE_STYLE,
    COLOR,
    EDGE_COLOR,
    FACE_COLOR,
    COLOR_MAP,
    POINT_SIZE,
    _PERSISTENT,
};

enum class Function : uint8_t
{
    UNKNOWN,
    LINE3D,
    PLANE_XY,
    PLANE_XZ,
    PLANE_YZ,
    GRID_ON,
    GRID_OFF,
    PLOT2,
    PLOT3,
    SCATTER2,
    SCATTER3,
    LINE_BETWEEN_POINTS_3D,
    POLYGON_FROM_4_POINTS,
    FIGURE,
    CLEAR,
    HOLD_ON,
    HOLD_OFF,
    POSITION,
    SURF,
    IM_SHOW,
    AXES,
    VIEW,
    SOFT_CLEAR
};

enum class DataType : uint8_t
{
    UNKNOWN,
    FLOAT,
    DOUBLE,
    INT8,
    INT16,
    INT32,
    INT64,
    UINT8,
    UINT16,
    UINT32,
    UINT64
};

enum class DataStructure : uint8_t
{
    UNKNOWN,
    MATRIX,
    VECTOR,
    IMAGE,
    TEXT
};

}

namespace properties
{
    constexpr internal::PropertyType PERSISTENT = internal::PropertyType::_PERSISTENT;
}

}


#endif
