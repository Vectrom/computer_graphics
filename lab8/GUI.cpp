#include "GUI.h"
#include <FreeImage.h>
#include "CImg.h"
#include <wx/dcbuffer.h>
#include <wx/window.h>
#include <string>

void GUI::FrameOnUpdateUI(wxUpdateUIEvent& event) {
	wxClientDC dc(_panel);
	refresh(dc);
}

void GUI::_loadButtonOnButtonClick(wxCommandEvent& event) {
	wxClientDC dc(_panel);
	wxFileDialog * dialog = new wxFileDialog(this, "Proszê wybraæ zdjêcie", "", "", wxT("Obraz JPEG (*.jpg)|*.jpg"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	dialog->ShowModal();
	std::string info("Rozmiar obrazka: ");
	_image->LoadFile(dialog->GetPath(), wxBITMAP_TYPE_JPEG);
	*_originalImage = _image->Copy();

	FIBITMAP *dib = FreeImage_Load(FIF_JPEG, dialog->GetPath(), JPEG_DEFAULT);
	FITAG *tagMake = NULL;
	info += std::to_string(FreeImage_GetWidth(dib)) + "*" + std::to_string(FreeImage_GetHeight(dib)) + "\n EXIF Info:\n";
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "Artist", &tagMake);
	info += std::string("Artist: ") + std::string((FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake))) + std::string("\n");
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "Copyright", &tagMake);
	info += std::string("Copyright: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake) + std::string("\n");
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "ResolutionUnit", &tagMake);
	info += std::string("Resolution Unit: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake) + std::string("\n");
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "XResolution", &tagMake);
	info += std::string("XResolution: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake) + std::string("\n");
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "YCbCrPositioning", &tagMake);
	info += std::string("YCbCrPositioning: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake) + std::string("\n");
	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "YResolution", &tagMake);
	info += std::string("YResolution: ") + FreeImage_TagToString(FIMD_EXIF_MAIN, tagMake);
	FreeImage_Unload(dib);

	info += "\n";
	_imageInfo->AppendText(info);
	refresh(dc);
}

void GUI::_cenzuraButtonOnButtonClick(wxCommandEvent& event) {
	*_image = _originalImage->Copy();
	wxClientDC dc(_panel);
	if (_image->Ok()) {
		const int pixelsHeight = 0.1 * _image->GetHeight();
		const int pixelsWidth = 0.2 * _image->GetWidth();
		const int xStart = 0.55 * _image->GetWidth();
		const int yStart = 0.05 * _image->GetHeight();

		cimg_library::CImg<unsigned char> cImage(pixelsWidth, pixelsHeight, 1, 3);
		for (int i = 0; i < pixelsWidth; i++) {
			for (int j = 0; j < pixelsHeight; j++) {
				cImage(i, j, 0) = _image->GetRed(xStart + i, yStart + j);
				cImage(i, j, 1) = _image->GetGreen(xStart + i, yStart + j);
				cImage(i, j, 2) = _image->GetBlue(xStart + i, yStart + j);
			}
		}
		cImage.blur(2.5);
		for (int i = 0; i < pixelsWidth; i++)
			for (int j = 0; j < pixelsHeight; j++)
				_image->SetRGB(xStart + i, yStart + j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));

		refresh(dc);
	}
}

void GUI::_erodeButtonOnButtonClick(wxCommandEvent& event) {
	*_image = _originalImage->Copy();
	wxClientDC dc(_panel);
	if (_image->Ok()) {
		const int height = _image->GetHeight();
		const int width = _image->GetWidth();
		cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);
		for (int i = 0; i < width; ++i) {
			for (int j = 0; j < height; ++j) {
				cImage(i, j, 0) = _image->GetRed(i, j);
				cImage(i, j, 1) = _image->GetGreen(i, j);
				cImage(i, j, 2) = _image->GetBlue(i, j);
			}
		}
		cImage.erode(5, 5);
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				_image->SetRGB(i, j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));

		refresh(dc);
	}
}

void GUI::_checkBoxOnCheckBox(wxCommandEvent& event) {

}

void GUI::refresh(wxClientDC &dc) {
	wxBufferedDC buff(&dc);
	if (_image->Ok()) {
		_image->Rescale(dc.GetSize().x, dc.GetSize().y);
		wxBitmap bitmap(*_image);
		buff.DrawBitmap(bitmap, 0, 0);
	}
}