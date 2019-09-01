#ifndef GUI_H
#define GUI_H
#include "Frame.h"
#include <wx/wx.h>

class GUI : public Frame {
public:
	GUI() : Frame(NULL) {
		_image = new wxImage();
		wxInitAllImageHandlers();
	}

	~GUI() {
		delete _image;
	}

protected:
	void FrameOnUpdateUI(wxUpdateUIEvent& event);
	void _loadButtonOnButtonClick(wxCommandEvent& event);
	void _cenzuraButtonOnButtonClick(wxCommandEvent& event);
	void _erodeButtonOnButtonClick(wxCommandEvent& event);
	void _checkBoxOnCheckBox(wxCommandEvent& event);

private:
	wxImage * _image;
	wxImage * _originalImage;
	void refresh(wxClientDC &dc);
};

#endif // GUI_H