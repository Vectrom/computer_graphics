#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c, int w, int h) : _w(w), _h(h) {
    cfg= std::move(c);
    x_step=200;
}

void ChartClass::Set_Range()
{
 double xmin=9999.9,xmax=-9999.9,ymin=9999.9,ymax=-9999.9;
 double x,y,step;
 int i;

 xmin=cfg->Get_x_start();
 xmax=cfg->Get_x_stop();

 step=(cfg->Get_x_stop()-cfg->Get_x_start())/(double)x_step;
 x=cfg->Get_x_start();

 for (i=0;i<=x_step;i++)
  {
   y=GetFunctionValue(x);
   if (y>ymax) ymax=y;
   if (y<ymin) ymin=y;
   x=x+step;
  }

 y_min=ymin;
 y_max=ymax;
 x_min=xmin;
 x_max=xmax;
}


double ChartClass::GetFunctionValue(double x)
{
 if (cfg->Get_F_type()==1) return x*x;
 if (cfg->Get_F_type()==2) return 0.5*exp(4*x-3*x*x);
 return x+sin(x*4.0);
}

void ChartClass::Draw(wxDC *dc) {
	 dc->SetBackground(wxBrush(RGB(255, 255, 255)));
	 dc->Clear();
	 dc->SetPen(wxPen(RGB(255, 0, 0)));
	 dc->DrawRectangle(10, 10, _w - 20, _h - 20);
	 dc->SetClippingRegion(wxRect(10, 10, _w - 20, _h - 20));
	 dc->SetPen(wxPen(RGB(0, 0, 255)));
	 Matrix transformation;

	 if (cfg->RotateScreenCenter())
		 transformation = SetRotation(cfg->Get_Alpha()) * SetTranslation(cfg->Get_dX(), cfg->Get_dY()) * SetScale();
	 else
		 transformation = SetTranslation(cfg->Get_dX(), cfg->Get_dY()) * SetRotation(cfg->Get_Alpha()) * SetScale();

	 drawAxis(dc, transformation);

	 dc->SetPen(wxPen(RGB(0, 255, 0)));

	 double step = (x_max - x_min) / x_step;

	 for (double i = x_min; i < x_max; i += step)
		 drawLine2d(dc, transformation, i, GetFunctionValue(i), i + step, GetFunctionValue(i + step));

}

void ChartClass::drawLine2d(wxDC *dc, Matrix t, double x1, double y1, double x2, double y2) {
	Vector startPoint, endPoint;
	startPoint.Set(x1, y1);
	endPoint.Set(x2, y2);
	startPoint = t * startPoint;
	endPoint = t * endPoint;
	dc->DrawLine(startPoint.GetX(), _h - startPoint.GetY(), endPoint.GetX(), _h - endPoint.GetY());
}

void ChartClass::drawAxis(wxDC * dc, Matrix t) {
	drawLine2d(dc, t, cfg->Get_x_start(), 0, cfg->Get_x_stop(), 0); //oX
	drawLine2d(dc, t, 0, Get_Y_min(), 0, Get_Y_max()); // oY

	drawLine2d(dc, t, x_max, 0, x_max - 0.05, 0.05); //arrow oX
	drawLine2d(dc, t, x_max, 0, x_max - 0.05, -0.05);

	drawLine2d(dc, t, 0, y_max, 0.05, y_max - 0.05); //arrow oY
	drawLine2d(dc, t, 0, y_max, -0.05, y_max - 0.05);

	double dy = 1 + int((cfg->Get_y1() - cfg->Get_y0()) / 10);

	Vector coords;
	for (double i = x_min; i <= x_max; i += 0.5) {
		drawLine2d(dc, t, i, -0.05, i, 0.05);
		coords.Set(i-0.1, -0.1);
		coords = t * coords;
		dc->DrawRotatedText(wxString::Format(wxT("%0.2g"), i), coords.GetX() + 0.2, _h - coords.GetY(), cfg->Get_Alpha());
	}

	for (double i = y_min; i <= y_max; i += dy) {
		drawLine2d(dc, t, -0.05, i, 0.05, i);
		coords.Set(0.1, i);
		coords = t * coords;
		dc->DrawRotatedText(wxString::Format(wxT("%0.2g"), i), coords.GetX(), _h - coords.GetY() - 0.2, cfg->Get_Alpha());
	}
}

double ChartClass::Get_Y_min()
{
    Set_Range();
    return y_min;
}

double ChartClass::Get_Y_max()
{
    Set_Range();
    return y_max;
}

Matrix ChartClass::SetRotation(double alpha) {
	double x, y;

	if(cfg->RotateScreenCenter()) {
		x = _w / 2.0;
		y = _h / 2.0;
	}
	else {
		Matrix tmp = SetScale();
		x = tmp.data[0][2];
		y = tmp.data[1][2];
	}

	Matrix rotation;
	double cosAlpha = cos(alpha * M_PI / 180);
	double sinAlpha = sin(alpha * M_PI / 180);
	rotation.data[0][0] = cosAlpha;
	rotation.data[0][1] = -sinAlpha;
	rotation.data[1][0] = sinAlpha;
	rotation.data[1][1] = cosAlpha;
	rotation.data[0][2] = x * (1 - cosAlpha) + y * sinAlpha;
	rotation.data[1][2] = -x * sinAlpha + y * (1 - cosAlpha);
	return rotation;
}

Matrix ChartClass::SetTranslation(double dx, double dy) {
	Matrix translation;
	translation.data[0][0] = 1.0;
	translation.data[1][1] = 1.0;
	translation.data[0][2] = dx;
	translation.data[1][2] = -dy;
	return translation;
}

Matrix ChartClass::SetScale() {
	Matrix scale;
	scale.data[0][0] = (_w - 20.0) / (cfg->Get_x1() - cfg->Get_x0());
	scale.data[1][1] = (_h - 20.0) / (cfg->Get_y1() - cfg->Get_y0());
	scale.data[0][2] = 10.0 - scale.data[0][0] * cfg->Get_x0();
	scale.data[1][2] = 10.0 - scale.data[1][1] * cfg->Get_y0();
	return scale;
}

