#include "main.h"
#include "longdivframe.h"

IMPLEMENT_APP(LongDivApp)

bool LongDivApp::OnInit()
{
	LongDivFrame *longdivframe = new LongDivFrame("Long division calculator", wxPoint(1,1), wxSize(1280,720)); //size was 800,600
    longdivframe->Show(true);
	
	SetTopWindow(longdivframe);
	
	return true;
}

BEGIN_EVENT_TABLE ( LongDivFrame, wxFrame )
	EVT_BUTTON ( BUTTON_Calculate, LongDivFrame::OnCalculateButtonPress ) // Tell the OS to run MainFrame::OnExit when
END_EVENT_TABLE() // The button is pressed

int LongDivApp::OnExit()
{

    return 0;
}