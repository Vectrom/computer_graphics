#include <wx/dcbuffer.h>
#include <wx/colordlg.h>
#include "MainWindow.h"

MainWindow::MainWindow() : Window(nullptr), _isBananaActivated(false), _bananaPosition(0), _chosenFigure(star), _starColour(*wxBLACK),_textString("Ma³pka"), _imageHandler(new wxPNGHandler()) {
	_bananaScrollBar->SetScrollbar(0, 1, 100, 1);
	wxImage::AddHandler(_imageHandler);
	wxImage bananaImage = wxImage(wxSize(50, 38));
	bananaImage.LoadFile("banan.png", wxBITMAP_TYPE_PNG);
	_banana = new wxBitmap(bananaImage);
	_fileDialog = new wxFileDialog(this, _("Wybierz plik:"), _(""), _("result.jpg"), _(".jpg"), wxFD_SAVE);
	_timer = new wxTimer();
	_timer->SetOwner(this);
	Bind(wxEVT_TIMER, &MainWindow::waggle, this);
}	

MainWindow::~MainWindow() {
	delete _banana;
	delete _fileDialog;
}

void MainWindow::_panelOnPaint(wxPaintEvent & event) {
	wxClientDC dcClient(_panel);
	_panel->Refresh();
	_panel->Update();
	draw(dcClient);
}

void MainWindow::_panelOnUpdateUI(wxUpdateUIEvent & event) {
	wxClientDC dcClient(_panel);
	draw(dcClient);
}

void MainWindow::_saveButtonOnButtonClick(wxCommandEvent & event) {
	wxClientDC dcClient(_panel);
	wxBufferedDC dcBuffer(&dcClient);
	PrepareDC(dcBuffer);
	wxInitAllImageHandlers();
	
	wxString filePath;
	
	if(_fileDialog->ShowModal() == wxID_OK) {
		Refresh();
		
		filePath = _fileDialog->GetPath();

		wxSize size = _panel->GetVirtualSize();
		wxBitmap bitmapToSave(size);

		wxMemoryDC memory;
		memory.SelectObject(bitmapToSave);
		memory.Blit(0, 0, size.GetX(), size.GetY(), &dcBuffer, 0, 0, wxCOPY, true);

		wxImage imageToSave = bitmapToSave.ConvertToImage();
		imageToSave.SaveFile(filePath, wxBITMAP_TYPE_JPEG);
	}
}

void MainWindow::_bananaCheckBoxOnCheckBox(wxCommandEvent & event) {
	_isBananaActivated = event.IsChecked();
	_bananaScrollBar->Enable(_isBananaActivated);
	Refresh();
}

void MainWindow::_waggleButtonOnCheckBox(wxCommandEvent & event) {
	if (event.IsChecked()) {
		_bananaScrollBar->Enable(true);
		_timer->Start(100);
	}
	else {
		_timer->Stop();
		_bananaScrollBar->Enable(_isBananaActivated);
	}
	Refresh();
}

void MainWindow::_bananaScrollBarOnScroll(wxScrollEvent & event) {
	_bananaPosition = event.GetPosition();
	_bananaProgressBar->SetValue(_bananaPosition);
	Refresh();
}

void MainWindow::_colorButtonOnButtonClick(wxCommandEvent & event) {
	wxColourDialog colourDialog(this);
	if (colourDialog.ShowModal() == wxID_OK)
		_starColour = colourDialog.GetColourData().GetColour();
	Refresh();
}

void MainWindow::_textOnText(wxCommandEvent & event) {
	_textString = event.GetString();
	wxClientDC dcClient(_panel);
	draw(dcClient);
	Refresh();
}

void MainWindow::_choicePaintingOnChoice(wxCommandEvent & event) {
	_chosenFigure = event.GetSelection();
	Refresh();
}

void MainWindow::draw(wxClientDC & dcClient) {
	wxBufferedDC dcBuffer(&dcClient);
	PrepareDC(dcBuffer);
	dcBuffer.Clear();

	wxSize center = _panel->GetVirtualSize();
	int x = center.GetWidth() / 2;
	int y = center.GetHeight() / 2;
	dcBuffer.SetDeviceOrigin(0, 0);

	dcBuffer.SetPen(wxPen(*wxBLACK_PEN));
	dcBuffer.DrawLine(x, y - 20, x, y + 70); //body
	dcBuffer.DrawLine(x, y, x + 40, y + 25); //right arm
	dcBuffer.DrawLine(x, y + 70, x + 30, y + 100); //right leg
	dcBuffer.DrawLine(x, y + 70, x - 30, y + 100); //left leg
	dcBuffer.DrawCircle(x, y - 30, 20); //head
	dcBuffer.DrawCircle(x + 10, y - 35, 4); //right eye
	dcBuffer.DrawCircle(x - 10, y - 35, 4); //left eye
	dcBuffer.SetBrush(wxBrush(*wxBLACK_BRUSH));
	dcBuffer.DrawCircle(x + 10, y - 35, 1); //right pupil
	dcBuffer.DrawCircle(x - 10, y - 35, 1); //left pupil

	_starPosition[0] = wxPoint(x - 100, y - 120);
	_starPosition[1] = wxPoint(x - 85, y - 75);
	_starPosition[2] = wxPoint(x - 125, y - 100);
	_starPosition[3] = wxPoint(x - 75, y - 100);
	_starPosition[4] = wxPoint(x - 115, y - 75);

	dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));
	if(_isBananaActivated) {
		dcBuffer.DrawBitmap(*_banana, x - 80, y - _bananaPosition / 2); //banana
		dcBuffer.DrawLine(x, y, x - 40, y + 25 - _bananaPosition / 2); //left arm
		dcBuffer.DrawEllipticArc(x - 13, y - 30, 26, 15, 0, -180); //happy
	}
	else {
		dcBuffer.DrawLine(x, y, x - 40, y + 25 - _bananaPosition / 2); //left arm
		dcBuffer.DrawEllipticArc(x - 13, y - 25, 26, 15, 0, 180); //sad
	}

	dcBuffer.SetPen(wxPen(wxColour(_starColour)));
	dcBuffer.SetBrush(wxBrush(wxColour(_starColour)));
	switch(_chosenFigure) {
	case star:
		dcBuffer.DrawPolygon(5, _starPosition, wxWINDING_RULE); //star
		break;
	case moon:
		dcBuffer.SetPen(wxPen(*wxLIGHT_GREY_PEN));
		dcBuffer.SetBrush(wxBrush(*wxLIGHT_GREY_BRUSH));
		dcBuffer.DrawCircle(x - 100, y - 100, 30); //moon
		dcBuffer.SetPen(wxPen(*wxWHITE_PEN));
		dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));
		dcBuffer.DrawCircle(x - 115, y - 115, 30);
		dcBuffer.SetPen(wxPen(*wxBLACK_PEN));
		dcBuffer.SetBrush(wxBrush(*wxBLACK_BRUSH));
		dcBuffer.DrawCircle(x - 80, y - 100, 3); //moon eye
		dcBuffer.DrawEllipticArc(x - 95, y - 90, 15, 5, 40, -220); //moon smile
		break;
	case sun:
		dcBuffer.SetPen(wxPen(*wxYELLOW_PEN));
		dcBuffer.SetBrush(wxBrush(*wxYELLOW_BRUSH));
		dcBuffer.DrawCircle(x - 100, y - 100, 30); //sun
		break;
	}

	dcBuffer.SetPen(wxPen(wxColour(*wxBLACK), 3));
	dcBuffer.DrawText(_textString, x - 100, y + 90);
	dcBuffer.SetFont(wxFont(wxFontInfo(40).FaceName("Forte")));
	dcBuffer.SetPen(wxPen(wxColour(*wxBLACK), 20));
	dcBuffer.DrawRotatedText(_textString, x + 70, y + 100, 90);

}

void MainWindow::waggle(wxTimerEvent & e) {
	static int step = 5;
	_bananaPosition = _bananaScrollBar->GetThumbPosition();

	if (_bananaPosition >= 99) step = -5;
	else if (_bananaPosition <= 0) step = 5;
	
	_bananaScrollBar->SetThumbPosition(_bananaPosition + step);
	_bananaProgressBar->SetValue(_bananaPosition + step);

	Refresh();
}
