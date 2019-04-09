#include <vector>
#include <fstream>
#include <algorithm>
#include "GUIMyFrame1.h"
#include "vecmat.h"

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent ) {
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

bool compare(Segment& s1, Segment& s2) {
	return s1.begin.y > s2.begin.y;
}

void GUIMyFrame1::changeColor() {
	double blue = 255.0;
	double red = 0.0;
	double iterator = 255.0 / data.size();
	std::sort(data.begin(), data.end(), compare);
	for (auto & elem : data) {
		elem.color.R = red;
		elem.color.G = 0;
		elem.color.B = blue;
		red += iterator;
		blue -= iterator;
	}
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event ) {
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event ) {
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)  {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open()) {
   data.clear();
   while (!in.eof()) {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
 changeColor();
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event ) {
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));

Repaint();
}

Matrix4 GUIMyFrame1::SetTranslation(double dx, double dy, double dz) {
	Matrix4 translation;
	translation.data[0][0] = 1;
	translation.data[1][1] = 1;
	translation.data[2][2] = 1;
	translation.data[0][3] = dx;
	translation.data[1][3] = -dy;
	translation.data[2][3] = dz;
	return translation;
}

Matrix4 GUIMyFrame1::SetRotationX(double alpha) {
	Matrix4 rotation;
	double cosAlpha = cos(alpha * M_PI / 180);
	double sinAlpha = sin(alpha * M_PI / 180);
	rotation.data[0][0] = 1;
	rotation.data[1][1] = cosAlpha;
	rotation.data[1][2] = -sinAlpha;
	rotation.data[2][1] = sinAlpha;
	rotation.data[2][2] = cosAlpha;
	return rotation;
}

Matrix4 GUIMyFrame1::SetRotationY(double alpha) {
	Matrix4 rotation;
	double cosAlpha = cos(alpha * M_PI / 180);
	double sinAlpha = sin(alpha * M_PI / 180);
	rotation.data[0][0] = cosAlpha;
	rotation.data[0][2] = sinAlpha;
	rotation.data[2][0] = -sinAlpha;
	rotation.data[2][2] = cosAlpha;
	rotation.data[1][1] = 1;
	return rotation;
}

Matrix4 GUIMyFrame1::SetRotationZ(double alpha) {
	Matrix4 rotation;
	double cosAlpha = cos(alpha * M_PI / 180);
	double sinAlpha = sin(alpha * M_PI / 180);
	rotation.data[0][0] = cosAlpha;
	rotation.data[0][1] = -sinAlpha;
	rotation.data[1][0] = sinAlpha;
	rotation.data[1][1] = cosAlpha;
	rotation.data[2][2] = 1;
	return rotation;
}

Matrix4 GUIMyFrame1::SetScale(double dx, double dy, double dz) {
	Matrix4 scale;
	scale.data[0][0] = dx;
	scale.data[1][1] = -dy;
	scale.data[2][2] = dz;
	return scale;
}

Matrix4 GUIMyFrame1::SetCenter() {
	Matrix4 center;
	center.data[0][0] = 1;
	center.data[1][1] = 1;
	center.data[2][2] = 1;
	center.data[0][3] = 0.5;
	center.data[1][3] = 0.5;
	return center;
}

void GUIMyFrame1::Repaint() {
	wxClientDC dcClient(WxPanel);
	wxBufferedDC dcBuffer(&dcClient);

	int width, height;
	WxPanel->GetSize(&width, &height);

	dcBuffer.SetBackground(wxBrush(RGB(255, 255, 255)));
	dcBuffer.Clear();
	dcBuffer.SetClippingRegion(wxRect(0, 0, width, height));

	Matrix4 translation = SetTranslation((WxSB_TranslationX->GetValue() - 100.0) / 50.0, (WxSB_TranslationY->GetValue() - 100.0) / 50.0, (WxSB_TranslationZ->GetValue() - 100.0) / 50.0 + 2.0);
	Matrix4 rotation = SetRotationX(WxSB_RotateX->GetValue()) * SetRotationY(WxSB_RotateY->GetValue()) * SetRotationZ(WxSB_RotateZ->GetValue());
	Matrix4 scale = SetScale(WxSB_ScaleX->GetValue() / 100.0, WxSB_ScaleY->GetValue() / 100.0, WxSB_ScaleZ->GetValue() / 100.0);
	Matrix4 center = SetCenter();
	Matrix4 transformation = translation * rotation * scale;

	for (const auto & elem : data) {
		Vector4 start, end;
		
		start.Set(elem.begin.x, elem.begin.y, elem.begin.z);
		start = transformation * start;

		end.Set(elem.end.x, elem.end.y, elem.end.z);
		end = transformation * end;

		dcBuffer.SetPen(wxPen(RGB(elem.color.R, elem.color.G, elem.color.B)));	

		if(start.GetZ() < 0) 
			start.Set(start.GetX(), start.GetY(), 0.0001);
		if(end.GetZ() < 0)
			end.Set(start.GetX(), start.GetY(), 0.0001);
		if (start.GetZ() > 0 && end.GetZ() > 0) {
			start.Set(start.GetX() / start.GetZ(), start.GetY() / start.GetZ(), start.GetZ());
			start = center * start;
			end.Set(end.GetX() / end.GetZ(), end.GetY() / end.GetZ(), end.GetZ());
			end = center * end;
			dcBuffer.DrawLine(start.GetX() * width, start.GetY() * height, end.GetX() * width, end.GetY() * height);
		}
	}
}