cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(main-app)

include_directories(${REPO_DIR}/src/main_application)
include_directories(${REPO_DIR}/src/interfaces/cpp)

set(CPP_SOURCE_FILES main.cpp
                     axes/axes_interactor.cpp

                     axes/axes_renderer.cpp
                     axes/plot_box_walls.cpp
                     axes/plot_box_silhouette.cpp
                     axes/plot_pane_background.cpp
                     axes/zoom_rect.cpp
                     axes/grid_numbers.cpp
                     axes/plot_box_grid.cpp
                     axes/text_rendering.cpp
                     axes/legend_renderer.cpp
                     axes/point_selection_box.cpp

                     axes/axes_side_configuration.cpp

                     project_state/project_settings.cpp
                     project_state/element_settings.cpp
                     project_state/plot_pane_settings.cpp
                     project_state/other_gui_settings.cpp

                     shader.cpp

                     settings_window.cpp

                     gui_elements.cpp
                     gui_element.cpp

                     editing_silhouette.cpp

                     cmdl_output_window.cpp

                     platform_paths.cpp

                     axes/structures/axes_limits.cpp
                     axes/structures/axes_settings.cpp
                     axes/structures/view_angles.cpp

                     misc/number_formatting.cpp

                     plot_objects/plot_object_base/plot_object_base.cpp
                     plot_objects/draw_mesh/draw_mesh.cpp
                     plot_objects/im_show/im_show.cpp
                     plot_objects/plot_collection2/plot_collection2.cpp
                     plot_objects/plot_collection3/plot_collection3.cpp
                     plot_objects/plot2d/plot2d.cpp
                     plot_objects/plot3d/plot3d.cpp
                     plot_objects/fast_plot2d/fast_plot2d.cpp
                     plot_objects/fast_plot3d/fast_plot3d.cpp
                     plot_objects/line_collection2/line_collection2.cpp
                     plot_objects/line_collection3/line_collection3.cpp
                     plot_objects/stem/stem.cpp
                     plot_objects/scatter/scatter.cpp
                     plot_objects/scatter3/scatter3.cpp
                     plot_objects/stairs/stairs.cpp
                     plot_objects/surf/surf.cpp
                     plot_objects/scrolling_plot2d/scrolling_plot2d.cpp

                     globals.cpp

                     project_state/configuration_agent.cpp

                     communication/received_data.cpp
                     communication/data_receiver.cpp
                     input_data.cpp
                     point_selection.cpp

                     tray_icon.cpp
                     tab_button.cpp
                     close_button.cpp
                     window_button.cpp
                     gui_window.cpp
                     gui_tab.cpp
                     events.cpp
                     tab_buttons.cpp
                     help_pane.cpp
                     plot_data_handler.cpp
                     plot_pane.cpp
                     color_picker.cpp
                     main_window.cpp
                     main_window_receive.cpp

                     properties.cpp)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${REPO_DIR}/src/build/)

add_executable(duoplot ${CPP_SOURCE_FILES})
target_link_libraries(duoplot ${wxWidgets_LIBRARIES}
                          ${OPENGL_LIBRARIES}
                          ${GLUT_LIBRARY}
                          ${PLATFORM_LIBRARIES}
                          /Users/danielpi/work/dvs/src/externals/freetype/build/libfreetype.a)
