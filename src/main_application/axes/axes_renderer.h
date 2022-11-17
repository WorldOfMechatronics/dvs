#ifndef MAIN_APPLICATION_AXES_AXES_RENDERER_H_
#define MAIN_APPLICATION_AXES_AXES_RENDERER_H_

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>
#include <vector>

#include "axes/grid_numbers.h"
#include "axes/legend_properties.h"
#include "axes/legend_renderer.h"
#include "axes/plot_box_grid.h"
#include "axes/plot_box_silhouette.h"
#include "axes/plot_box_walls.h"
#include "axes/plot_pane_background.h"
#include "axes/plot_pane_help.h"
#include "axes/structures/axes_limits.h"
#include "axes/structures/axes_settings.h"
#include "axes/structures/grid_vectors.h"
#include "axes/structures/view_angles.h"
#include "axes/text_rendering.h"
#include "axes/zoom_rect.h"
#include "io_devices/mouse_state.h"
#include "opengl_low_level/opengl_low_level.h"
#include "shader.h"

class AxesRenderer
{
private:
    TextRenderer text_renderer_;
    ShaderCollection shader_collection_;
    LegendRenderer legend_renderer_;

    ViewAngles view_angles_;
    AxesLimits axes_limits_;

    AxesSettings axes_settings_;

    PlotBoxWalls plot_box_walls_{};
    PlotBoxSilhouette plot_box_silhouette_{};
    PlotBoxGrid plot_box_grid_{};
    PlotPaneBackground plot_pane_background_{};
    PlotPaneHelp plot_pane_help_{};

    glm::mat4 orth_projection_mat;
    glm::mat4 persp_projection_mat;
    glm::mat4 projection_mat;
    glm::mat4 view_mat;
    glm::mat4 model_mat;
    glm::mat4 scale_mat;
    glm::mat4 window_scale_mat_;

    Matrix<double> rot_mat;

    float width_, height_;
    Vec3d scale_for_window_;

    GridVectors grid_vectors_;
    bool use_perspective_proj_;
    Vec2f mouse_pos_at_press_;
    Vec2f current_mouse_pos_;
    ZoomRect zoom_rect_;
    MouseInteractionType mouse_interaction_type_;
    bool mouse_pressed_;
    bool render_zoom_rect_;
    bool render_legend_;
    bool global_illumination_active_;
    Vec3d light_pos_;
    std::vector<LegendProperties> legend_properties_;

    void renderBackground();
    void renderPlotBox();
    void renderBoxGrid();
    void enableClipPlanes();
    void renderLegend();
    void setClipPlane(const GLuint program_id,
                      const std::string pln,
                      const Point3d& p0,
                      const Point3d& p1,
                      const Point3d& p2,
                      const bool invert) const;

public:
    AxesRenderer(const ShaderCollection shader_collection);

    void updateStates(const AxesLimits& axes_limits,
                      const ViewAngles& view_angles,
                      const GridVectors& gv,
                      const bool use_perspective_proj,
                      const float width,
                      const float height,
                      const Vec2f mouse_pos_at_press,
                      const Vec2f current_mouse_pos,
                      const MouseInteractionType mouse_interaction_type,
                      const bool mouse_pressed,
                      const bool render_zoom_rect,
                      const bool render_legend,
                      const float legend_scale_factor,
                      const std::vector<LegendProperties>& legend_properties);
    void render();
    void plotBegin();
    void plotEnd();
    void activateGlobalIllumination(const Vec3d& light_pos);
    void resetGlobalIllumination();
};

#endif  // MAIN_APPLICATION_AXES_AXES_RENDERER_H_
