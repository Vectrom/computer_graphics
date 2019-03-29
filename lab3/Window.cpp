///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Window.h"

///////////////////////////////////////////////////////////////////////////

Window::Window( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 600,400 ), wxDefaultSize );

	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxHORIZONTAL );

	_panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	_panel->SetBackgroundColour( wxColour( 255, 255, 255 ) );

	mainSizer->Add( _panel, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* optionsSizer;
	optionsSizer = new wxBoxSizer( wxVERTICAL );

	_saveButton = new wxButton( this, wxID_ANY, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer->Add( _saveButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	_bananaCheckBox = new wxCheckBox( this, wxID_ANY, wxT("Daj banana!"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer->Add( _bananaCheckBox, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	_waggleButton = new wxCheckBox( this, wxID_ANY, wxT("Pomachaj!"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer->Add( _waggleButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	_bananaScrollBar = new wxScrollBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	_bananaScrollBar->Enable( false );

	optionsSizer->Add( _bananaScrollBar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );

	_bananaProgressBar = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	_bananaProgressBar->SetValue( 0 );
	optionsSizer->Add( _bananaProgressBar, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	_colorButton = new wxButton( this, wxID_ANY, wxT("Kolor gwiazdki"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer->Add( _colorButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	_text = new wxTextCtrl( this, wxID_ANY, wxT("Małpka"), wxDefaultPosition, wxDefaultSize, 0 );
	optionsSizer->Add( _text, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxString _choicePaintingChoices[] = { wxT("Gwiazdka"), wxT("Księżyc"), wxT("Słonko") };
	int _choicePaintingNChoices = sizeof( _choicePaintingChoices ) / sizeof( wxString );
	_choicePainting = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, _choicePaintingNChoices, _choicePaintingChoices, 0 );
	_choicePainting->SetSelection( 0 );
	optionsSizer->Add( _choicePainting, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	mainSizer->Add( optionsSizer, 0, wxEXPAND, 5 );


	this->SetSizer( mainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	_panel->Connect( wxEVT_PAINT, wxPaintEventHandler( Window::_panelOnPaint ), NULL, this );
	_panel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Window::_panelOnUpdateUI ), NULL, this );
	_saveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_saveButtonOnButtonClick ), NULL, this );
	_bananaCheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::_bananaCheckBoxOnCheckBox ), NULL, this );
	_waggleButton->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::_waggleButtonOnCheckBox ), NULL, this );
	_bananaScrollBar->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_colorButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_colorButtonOnButtonClick ), NULL, this );
	_text->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Window::_textOnText ), NULL, this );
	_choicePainting->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( Window::_choicePaintingOnChoice ), NULL, this );
}

Window::~Window()
{
	// Disconnect Events
	_panel->Disconnect( wxEVT_PAINT, wxPaintEventHandler( Window::_panelOnPaint ), NULL, this );
	_panel->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Window::_panelOnUpdateUI ), NULL, this );
	_saveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_saveButtonOnButtonClick ), NULL, this );
	_bananaCheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::_bananaCheckBoxOnCheckBox ), NULL, this );
	_waggleButton->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( Window::_waggleButtonOnCheckBox ), NULL, this );
	_bananaScrollBar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_bananaScrollBar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Window::_bananaScrollBarOnScroll ), NULL, this );
	_colorButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( Window::_colorButtonOnButtonClick ), NULL, this );
	_text->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( Window::_textOnText ), NULL, this );
	_choicePainting->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( Window::_choicePaintingOnChoice ), NULL, this );

}
