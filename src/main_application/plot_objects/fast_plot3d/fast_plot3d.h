#ifndef MAIN_APPLICATION_PLOT_OBJECTS_FAST_PLOT3D_FAST_PLOT3D_H_
#define MAIN_APPLICATION_PLOT_OBJECTS_FAST_PLOT3D_FAST_PLOT3D_H_

#include <string>
#include <vector>

#include "dvs/math/math.h"
#include "main_application/plot_objects/utils.h"
#include "opengl_low_level/data_structures.h"
#include "opengl_low_level/opengl_low_level.h"
#include "plot_objects/plot_object_base/plot_object_base.h"

class FastPlot3D : public PlotObjectBase
{
private:
    uint8_t* points_ptr_;

    void findMinMax() override;

public:
    FastPlot3D();
    FastPlot3D(std::unique_ptr<const ReceivedData> received_data, const FunctionHeader& hdr, const ShaderCollection shader_collection);
    ~FastPlot3D();

    void render() override;
};

#endif // MAIN_APPLICATION_PLOT_OBJECTS_FAST_PLOT3D_FAST_PLOT3D_H_
