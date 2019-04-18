#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event ) {
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.ConvertToGreyscale();
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Blur(5);
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Mirror();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Scale(320, 240);
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Rotate(30 * M_PI / 180, wxPoint(Img_Org.GetWidth()/2, Img_Org.GetHeight()/2));
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.RotateHue(0.5);
}

void GUIMyFrame1::m_b_mask_click(wxCommandEvent& event) {
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}
		

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy();
	int height = Img_Org.GetHeight();
	int width = Img_Org.GetWidth();
	int size = width * height * 3;
	unsigned char * imageData = Img_Cpy.GetData();
	unsigned char * oldImageData = new unsigned char[size];
	std::copy(imageData, imageData + size, oldImageData);

#pragma omp paraller for
	for(int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			for (int k = 0; k < 3; k++) {
				int tmp = 0;
				tmp += oldImageData[k + (i - 1) * width * 3 + (j + 1) * 3];
				tmp += -oldImageData[k + (i - 1) * width * 3 + (j - 1) * 3];
				tmp += oldImageData[k + i * width * 3 + (j + 1) * 3];
				tmp += -oldImageData[k + i * width * 3 + (j - 1) * 3];
				tmp += oldImageData[k + (i + 1) * width * 3 + (j + 1) * 3];
				tmp += -oldImageData[k + (i + 1) * width * 3 + (j - 1) * 3];
				imageData[k + i * width * 3 + j * 3] = std::abs(tmp) / 3.0;
			}
		}
	}
	delete[] oldImageData;
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event ) {
	Img_Cpy = Img_Org.Copy();
	int size = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
	unsigned char * imageData = Img_Cpy.GetData();
	for (int i = 0; i < size; i++)
		imageData[i] = imageData[i] < 128 ? 0 : 255;
}


void GUIMyFrame1::Contrast(double value) {
	Img_Cpy = Img_Org.Copy();
	int size = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
	unsigned char * imageData = Img_Cpy.GetData();
	double contrast = (value + 100) / (100.0001 - value);
	for (int i = 0; i < size; i++) {
		int tmp = (imageData[i] - 255.0 / 2) * contrast + 255.0 / 2;
		if (tmp > 255)
			tmp = 255;
		else if (tmp < 0)
			tmp = 0;
		imageData[i] = tmp;
	}
}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 wxBufferedDC dcBuffer(&dc);
 dcBuffer.Clear();
 m_scrolledWindow->DoPrepareDC(dcBuffer); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 dcBuffer.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value) {
	Img_Cpy = Img_Org.Copy();
	int size = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
	unsigned char * imageData = Img_Cpy.GetData();
	for (int i = 0; i < size; i++) {
		int tmp = imageData[i] + value;
		if (tmp > 255)
			tmp = 255;
		else if (tmp < 0)
			tmp = 0;
		imageData[i] = tmp;
	}
}