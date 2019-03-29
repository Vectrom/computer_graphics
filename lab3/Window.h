///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Window
///////////////////////////////////////////////////////////////////////////////
class Window : public wxFrame
{
	private:

	protected:
		wxPanel* _panel;
		wxButton* _saveButton;
		wxCheckBox* _bananaCheckBox;
		wxCheckBox* _waggleButton;
		wxScrollBar* _bananaScrollBar;
		wxGauge* _bananaProgressBar;
		wxButton* _colorButton;
		wxTextCtrl* _text;
		wxChoice* _choicePainting;

		// Virtual event handlers, overide them in your derived class
		virtual void _panelOnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void _panelOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void _saveButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void _bananaCheckBoxOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void _waggleButtonOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void _bananaScrollBarOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void _colorButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void _textOnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void _choicePaintingOnChoice( wxCommandEvent& event ) { event.Skip(); }


	public:

		Window( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Podstawy Grafiki Komputerowej - Lab 3 - Damian Płóciennik"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,400 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Window();

};

