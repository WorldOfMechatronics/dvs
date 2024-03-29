#ifndef MAIN_APPLICATION_AXES_LEGEND_PROPERTIES_H_
#define MAIN_APPLICATION_AXES_LEGEND_PROPERTIES_H_

#include <string>
#include <string_view>

#include "dvs/enumerations.h"
#include "dvs/plot_properties.h"
#include "misc/rgb_triplet.h"

// TODO: This should be filled in plot_object_base and the individual object types

enum class LegendType
{
    LINE,
    POLYGON,
    DOT
};

struct LegendProperties
{
    std::string_view name;
    LegendType type;
    RGBTripletf color;
    RGBTripletf edge_color;
    RGBTripletf face_color;
    dvs::properties::ColorMap color_map;
    bool has_color_map;

    float point_size;
    dvs::properties::ScatterStyle scatter_style;

    // dvs::properties::LineStyle line_style;
};

#endif  // MAIN_APPLICATION_AXES_LEGEND_PROPERTIES_H_
