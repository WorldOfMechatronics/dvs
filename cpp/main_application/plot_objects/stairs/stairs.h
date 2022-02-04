#ifndef DVS_STAIRS_H_
#define DVS_STAIRS_H_

#include <string>
#include <vector>

#include "dvs/math/math.h"
#include "opengl_low_level/data_structures.h"
#include "opengl_low_level/opengl_low_level.h"
#include "plot_objects/plot_object_base/plot_object_base.h"

class Stairs : public PlotObjectBase
{
private:
    uint8_t* points_ptr_;

    void findMinMax() override;

public:
    Stairs();
    Stairs(std::unique_ptr<const ReceivedData> received_data, const FunctionHeader& hdr);
    ~Stairs();

    void render() override;
};

#endif