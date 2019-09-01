///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Frame
///////////////////////////////////////////////////////////////////////////////
class Frame : public wxFrame
{
	private:

	protected:
		wxButton* _loadButton;
		wxButton* _cenzuraButton;
		wxButton* _erodeButton;
		wxCheckBox* _checkBox;
		wxGauge* _gauge;
		wxTextCtrl* _imageInfo;
		wxPanel* _panel;

		// Virtual event handlers, overide them in your derived class
		virtual void FrameOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void _loadButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void _cenzuraButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void _erodeButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void _checkBoxOnCheckBox( wxCommandEvent& event ) { event.Skip(); }


	public:

		Frame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Podstawy Grafiki Komputerowej - Lab 8 - Damian Płóciennik"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1116,577 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Frame();

};

