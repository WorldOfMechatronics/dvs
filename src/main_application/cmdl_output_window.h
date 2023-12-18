#ifndef CMDL_OUTPUT_WINDOW_H
#define CMDL_OUTPUT_WINDOW_H

#include <wx/button.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/textctrl.h>
#include <wx/timer.h>
#include <wx/window.h>
#include <wx/wx.h>

#include "color.h"

class CmdlOutputWindow : public wxFrame
{
private:
    wxTextCtrl* text_ctrl_;

public:
    CmdlOutputWindow();
    ~CmdlOutputWindow();

    void OnSize(wxSizeEvent& event);

    void pushNewText(const Color_t col, const std::string& text);
};

#endif  // CMDL_OUTPUT_WINDOW_H
