#include <wx/wx.h>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

double Shepard(int N, float d[100][3], float x, float y) {
	double a = 0;
	double b = 0;
	double wk = 0;

	for(int i = 0; i < N; i++) {
		wk = 1. / std::abs((x - d[i][0])*(x - d[i][0]) + (y - d[i][1])*(y - d[i][1]));
		a += wk * d[i][2];
		b += wk;
	}
	return a / b;
}

void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints) {
	wxMemoryDC memDC;
	memDC.SelectObject(MemoryBitmap);
	memDC.SetBackground(*wxWHITE_BRUSH);
	memDC.Clear();

	double** points = new double*[500];
	for (int i = 0; i < 500; i++)
		points[i] = new double[500];

	double fMin = d[0][2];
	double fMax = d[0][2];

	for (int i = 0; i < N; i++) {
		if (d[i][2] < fMin)
			fMin = d[i][2];
		if (d[i][2] > fMax)
			fMax = d[i][2];
	}
	for (int x = 0; x < 500; x++)
		for (int y = 0; y < 500; y++)
			points[y][x] = Shepard(N, d, y / 100.0 - 2.5, -x / 100.0 + 2.5);

	unsigned char* data = new unsigned char[500 * 500 * 3];
	if (MappingType) {
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (1 == MappingType) {
					float color = ((points[x][y] - fMin) / (fMax - fMin) - 0.5) * 2;
					data[y * 500 * 3 + x * 3 + 0] = 127 - 127 * color;
					data[y * 500 * 3 + x * 3 + 1] = 0;
					data[y * 500 * 3 + x * 3 + 2] = 127 + 127 * color;
				}
				else if (2 == MappingType) {
					float color = ((points[x][y] - fMin) / (fMax - fMin) - 0.5) * 2;
					data[y * 500 * 3 + x * 3 + 0] = color < 0 ? 255 * std::abs(color) : 0;
					data[y * 500 * 3 + x * 3 + 1] = 255 - 255 * std::abs(color);
					data[y * 500 * 3 + x * 3 + 2] = color > 0 ? 255 * std::abs(color) : 0;
				}
				else if (MappingType == 3) {
					float color = ((points[x][y] - fMin) / (fMax - fMin) - 0.5) * 2;
					data[y * 500 * 3 + x * 3 + 0] = 127 + 127 * color;
					data[y * 500 * 3 + x * 3 + 1] = 127 + 127 * color;
					data[y * 500 * 3 + x * 3 + 2] = 127 + 127 * color;
				}
			}
		}
		wxImage tmp(500, 500, data);
		wxBitmap tmp2(tmp);
		memDC.DrawBitmap(tmp2, 0, 0);
	}
	//delete[] data;
	
	if (Contour) {
		memDC.SetPen(*wxBLACK);
		memDC.SetBrush(*wxTRANSPARENT_BRUSH);
		for (int level = 0; level < NoLevels; level++) {
			float thresholdPoint = fMin + (level + 1) * (fMax - fMin) / (NoLevels + 1.0f);
			for (int x = 0; x < 500; ++x) {
				for (int y = 0; y < 500; ++y) {
					if (points[y][x] > thresholdPoint) {
						for (int i = -1; i <= 1; i++) {
							for (int j = -1; j <= 1; j++) {
								if (i != 0 && j != 0 && (y + i >= 0) && (y + i < 500) && (y + j >= 0) &&
									(x + j < 500) && (points[y + i][x + j] < thresholdPoint)) {
									memDC.DrawPoint(y, x);
								}
							}
						}
					}
				}
			}
		}
	}


	if (ShowPoints) {
		memDC.SetPen(*wxBLACK);
		memDC.SetBrush(*wxTRANSPARENT_BRUSH);
		for (int i = 0; i < N; ++i) {
			const int x = (d[i][0] + 2.5) * 100;
			const int y = (2.5 - d[i][1]) * 100;
			memDC.DrawLine(x, y + 3, x, y - 3);
			memDC.DrawLine(x - 3, y, x + 3, y);
		}
	}

	for (int i = 0; i < 500; i++)
		delete[] points[i];
	delete[] points;
}