#include <wx/wx.h>
#include <memory>
#include "CImg.h"
#include "GUI.h"

class MyApp : public wxApp {

public:
	virtual bool OnInit();
	virtual int OnExit() { return 0; }
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
	wxFrame *mainFrame = new GUI();
	mainFrame->Show(true);
	SetTopWindow(mainFrame);
	return true;
}