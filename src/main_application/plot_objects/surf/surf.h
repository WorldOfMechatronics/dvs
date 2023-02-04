#ifndef MAIN_APPLICATION_PLOT_OBJECTS_SURF_SURF_H_
#define MAIN_APPLICATION_PLOT_OBJECTS_SURF_SURF_H_

#include <string>
#include <vector>

#include "dvs/math/math.h"
#include "main_application/misc/color_map.h"
#include "misc/color_map.h"
#include "opengl_low_level/opengl_low_level.h"
#include "opengl_low_level/vertex_buffer.h"
#include "plot_objects/plot_object_base/plot_object_base.h"

class Surf : public PlotObjectBase
{
public:
    Surf();
    Surf(const CommunicationHeader& hdr,
         ReceivedData& received_data,
         const std::unique_ptr<const ConvertedDataBase>& converted_data,
         const Properties& props,
         const ShaderCollection shader_collection,
         ColorPicker& color_picker);
    ~Surf();

    LegendProperties getLegendProperties() const override;
    bool affectsColormapMinMax() const override;
    void updateWithNewData(ReceivedData& received_data,
                           const CommunicationHeader& hdr,
                           const std::unique_ptr<const ConvertedDataBase>& converted_data,
                           const Properties& props) override;

    static std::unique_ptr<const ConvertedDataBase> convertRawData(const PlotObjectAttributes& attributes,
                                                                   const uint8_t* const data_ptr);
    void render() override;

private:
    VertexBuffer vertex_buffer_;
    VertexBuffer vertex_buffer_lines_;
    Dimension2D dims_;

    size_t num_elements_to_render_;
    size_t num_lines_to_render_;

    void findMinMax() override;
};

#endif  // MAIN_APPLICATION_PLOT_OBJECTS_SURF_SURF_H_
