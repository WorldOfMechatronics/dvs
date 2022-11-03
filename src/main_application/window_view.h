#ifndef MAIN_APPLICATION_WINDOW_VIEW_H_
#define MAIN_APPLICATION_WINDOW_VIEW_H_

#include <wx/button.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
#include <wx/wx.h>

#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <tuple>
#include <utility>
#include <vector>

#include "axes/axes.h"
#include "gui_element.h"
#include "plot_pane.h"
#include "project_state/project_settings.h"
#include "tab_buttons.h"

class GuiTab
{
private:
    std::string name_;
    std::map<std::string, GuiElement*> gui_elements_;

public:
    GuiTab(wxFrame* parent,
           const TabSettings& tab_settings,
           const std::function<void(const char key)>& notify_main_window_key_pressed,
           const std::function<void(const char key)>& notify_main_window_key_released,
           const std::function<void(const wxPoint pos)>& notify_parent_window_right_mouse_pressed)
        : name_{tab_settings.name}
    {
        const float grid_size_ = 1.0f;

        for (const auto& elem : tab_settings.elements)
        {
            GuiElement* const ge = new PlotPane(parent,
                                                elem,
                                                grid_size_,
                                                notify_main_window_key_pressed,
                                                notify_main_window_key_released,
                                                notify_parent_window_right_mouse_pressed);

            ge->updateSizeFromParent(parent->GetSize());
            gui_elements_[elem.name] = ge;
        }
    }

    void showAllElements()
    {
        for (auto const& ge : gui_elements_)
        {
            ge.second->show();
        }
    }

    void hideAllElements()
    {
        for (auto const& ge : gui_elements_)
        {
            ge.second->hide();
        }
    }

    void updateSizeFromParent(const wxSize new_size) const
    {
        for (auto const& ge : gui_elements_)
        {
            ge.second->updateSizeFromParent(new_size);
        }
    }

    std::string getName() const
    {
        return name_;
    }

    void setIsEditing(const bool is_editing)
    {
        for (auto const& ge : gui_elements_)
        {
            ge.second->setIsEditing(is_editing);
        }
    }

    void resetSelection()
    {
        for (auto it : gui_elements_)
        {
            it.second->resetSelection();
            it.second->refresh();
        }
    }

    TabSettings getTabSettings() const
    {
        TabSettings ts;

        ts.name = name_;

        for (const auto& ge : gui_elements_)
        {
            ts.elements.push_back(ge.second->getElementSettings());
        }

        return ts;
    }

    std::map<std::string, GuiElement*> getGuiElements() const
    {
        return gui_elements_;
    }
};

class WindowView : public wxFrame
{
private:
    enum ClickSource
    {
        TAB_BUTTON,
        GUI_ELEMENT,
        THIS
    };

    TabButtons tab_buttons_;
    std::map<std::string, GuiTab*> tabs_;
    int callback_id_;
    AxesSettings axes_settings_{};
    void tabChanged(const std::string name);
    std::function<void(const char key)> notify_main_window_key_pressed_;
    std::function<void(const char key)> notify_main_window_key_released_;
    float grid_size_;
    std::string name_;
    std::map<std::string, GuiElement*> gui_elements_;
    int current_unnamed_idx_;
    bool is_editing_;
    std::string name_of_selected_element_;
    WindowSettings* settings_;

    wxMenu* popup_menu_window_;
    wxMenu* popup_menu_element_;
    wxMenu* popup_menu_tab_;

public:
    WindowView() = delete;
    WindowView(wxFrame* parent,
               const WindowSettings& window_settings,
               const int callback_id,
               const std::function<void(const char key)>& notify_main_window_key_pressed,
               const std::function<void(const char key)>& notify_main_window_key_released);

    void newElement(const std::string& element_name);
    void newElement();
    int getCallbackId() const;
    void OnSize(wxSizeEvent& event);

    void onActivate(wxActivateEvent& event);
    void hide();
    void show();
    void setName(const std::string& new_name);
    void startEdit();
    void stopEdit();
    void resetSelectionForAllChildren();
    WindowSettings getWindowSettings() const;
    std::map<std::string, GuiElement*> getGuiElements() const;
    std::string getName() const;
    void childModified(wxCommandEvent& event);

    void deleteSelectedElement();
    void setSelectedElementName(const std::string& new_name);
    void mouseLeftPressed(wxMouseEvent& WXUNUSED(event));
    void setFirstElementSelected();

    void mouseRightPressed(const wxPoint pos, const ClickSource source);

    void mouseRightPressedCallback(wxMouseEvent& event);

    std::vector<ElementSettings> getElementSettingsList() const;

    std::string getSelectedElementName();

    virtual void OnClose(wxCloseEvent& event);
};

#endif  // MAIN_APPLICATION_WINDOW_VIEW_H_
