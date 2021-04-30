#ifndef GUI_ELEMENT_H_
#define GUI_ELEMENT_H_

#include <memory>

#include <wx/wx.h>
#include <wx/notebook.h>

#include "enumerations.h"
#include "math/math.h"
#include "plot_window_gl_pane.h"
#include "project_file.h"

class GuiElement
{
private:
    // GuiElementType type_;

    PlotWindowGLPane* gl_pane_;
    std::string name_;

    bool is_dockable_;
    bool is_docked_;

    project_file::Element element_;
public:
    GuiElement() = delete;
    GuiElement(wxPanel* parent,
               const wxPoint& position,
               const wxSize& size,
               const std::string& name,
               project_file::Element& element)
    {
        is_dockable_ = false;
        is_docked_ = false;
        name_ = name;
        element_ = element;

        gl_pane_ = new PlotWindowGLPane(parent, position, size);
    }

    GuiElement(wxNotebookPage* parent,
               const project_file::Element& element)
    {
        is_dockable_ = false;
        is_docked_ = false;
        name_ = element.name;
        element_ = element;

        gl_pane_ = new PlotWindowGLPane(parent, wxPoint(0, 0), wxSize(10, 10));
    }

    GuiElement(wxFrame* parent,
               const wxPoint& position,
               const wxSize& size,
               const std::string& name,
               project_file::Element& element)
    {
        is_dockable_ = false;
        is_docked_ = false;
        name_ = name;
        element_ = element;

        gl_pane_ = new PlotWindowGLPane(parent, position, size);
    }

    void show()
    {
        gl_pane_->Show();
    }

    void hide()
    {
        gl_pane_->Hide();
    }

    void addData(std::unique_ptr<const ReceivedData> received_data, const dvs::internal::FunctionHeader& hdr)
    {
        gl_pane_->addData(std::move(received_data), hdr);
    }

    std::string name() const
    {
        return name_;
    }

    void changeSize(const Vec2Df tab_cell_size)
    {
        /*float inc_x = static_cast<float>(parent_panel_size.GetWidth() - tab.margin_left_right * 2) / static_cast<float>(tab.num_cols);
        float inc_y = static_cast<float>(parent_panel_size.GetHeight() - tab.margin_top_bottom * 2) / static_cast<float>(tab.num_rows);

        float xpos = tab.margin_left_right + element_.col * inc_x + tab.spacing_cols;
        float ypos = tab.margin_top_bottom + element_.row * inc_y + tab.spacing_rows;
        wxSize sq(element_.width * inc_x - tab.spacing_cols * 2, element_.height * inc_y - tab.spacing_rows * 2);
        wxPoint pos(xpos, ypos);
        gl_pane_->setPosAndSize(pos, sq);*/
        const wxSize size(element_.width * tab_cell_size.x, element_.height * tab_cell_size.y);
        const wxPoint pos(element_.cell_idx_x * tab_cell_size.x, element_.cell_idx_y * tab_cell_size.y);
        gl_pane_->setPosAndSize(pos, size);
    }

};

#endif
