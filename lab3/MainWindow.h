#pragma once
#include <wx/filedlg.h>
#include <wx/timer.h>
#include "Window.h"

class MainWindow : public Window {
public:
	MainWindow();
	~MainWindow();
	void _panelOnPaint(wxPaintEvent& event);
	void _panelOnUpdateUI(wxUpdateUIEvent& event);
	void _saveButtonOnButtonClick(wxCommandEvent& event);
	void _bananaCheckBoxOnCheckBox(wxCommandEvent& event);
	void _waggleButtonOnCheckBox(wxCommandEvent& event);
	void _bananaScrollBarOnScroll(wxScrollEvent& event);
	void _colorButtonOnButtonClick(wxCommandEvent& event);
	void _textOnText(wxCommandEvent& event);
	void _choicePaintingOnChoice(wxCommandEvent& event);
	void draw(wxClientDC & dcClient);

private:
	void waggle(wxTimerEvent &e);

	enum figure {star = 0, moon = 1, sun = 2};

	bool _isBananaActivated;
	int _bananaPosition;
	int _chosenFigure;
	wxColour _starColour;
	wxBitmap * _banana;
	wxString _textString;
	wxPoint _starPosition[5];
	wxImageHandler * _imageHandler;
	wxFileDialog * _fileDialog;
	wxTimer * _timer;
	
};

