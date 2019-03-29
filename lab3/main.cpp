#include <wx/wx.h>
#include "Window.h"
#include "MainWindow.h"

class MyApp : public wxApp {
public:
	bool OnInit();
	int OnExit() { return 0; }
};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
	wxFrame *mainFrame = new MainWindow();
	mainFrame->Show(true);
	SetTopWindow(mainFrame);
	return true;
}