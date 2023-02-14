#ifndef MAIN_APPLICATION_PLOT_OBJECTS_PLOT2D_PLOT2D_H_
#define MAIN_APPLICATION_PLOT_OBJECTS_PLOT2D_PLOT2D_H_

#include <string>
#include <vector>

#include "dvs/math/math.h"
#include "misc/color_map.h"
#include "opengl_low_level/opengl_header.h"
#include "opengl_low_level/vertex_buffer.h"
#include "plot_objects/plot_object_base/plot_object_base.h"

class Plot2D : public PlotObjectBase
{
public:
    Plot2D();
    Plot2D(const CommunicationHeader& hdr,
           ReceivedData& received_data,
           const std::unique_ptr<const ConvertedDataBase>& converted_data,
           
           const PlotObjectAttributes& plot_object_attributes,
           const PropertiesData& properties_data,
           const ShaderCollection shader_collection,
           ColorPicker& color_picker);
    ~Plot2D();

    LegendProperties getLegendProperties() const override;
    void updateWithNewData(ReceivedData& received_data,
                           const CommunicationHeader& hdr,
                           const std::unique_ptr<const ConvertedDataBase>& converted_data,
                           const Properties& props) override;

    void render() override;

    static std::unique_ptr<const ConvertedDataBase> convertRawData(const PlotObjectAttributes& attributes,
                                                                   const PropertiesData& properties_data,
                                                                   const uint8_t* const data_ptr);

private:
    VertexBuffer vertex_buffer_;
    float gap_size_, dash_size_;

    size_t num_points_;

    void findMinMax() override;
};

#endif  // MAIN_APPLICATION_PLOT_OBJECTS_PLOT2D_PLOT2D_H_
