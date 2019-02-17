#include <wx/wxprec.h>
#include "wx/grid.h"
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <iostream>
#include <sstream>

class LongDivFrame: public wxFrame{
	private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnCalculateButtonPress(wxCommandEvent& event);
	
	std::string CalculateLongDivision();
	std::string CalculateLongDivisionRemainder(std::string strQuotient, int remainder);
	void DrawLongDivision(wxString wxStrSequence, wxString wxStrMultiple, wxString wxStrDifference);
	
	wxString wxStrDividend;
	unsigned long long divisor;
	int gridRowPosition;
	int gridColumnPosition;
	
	wxButton *calculateButton;
	wxTextCtrl *TextDivisor;
	wxTextCtrl *TextDividend;
	wxTextCtrl *TextAnswer;
	wxGrid *grid;
	
	public:
	LongDivFrame(const wxString& title, const wxPoint &pos, const wxSize &size);

	
	DECLARE_EVENT_TABLE()
};

enum{
	//Declares an id which will be used to call our button
	BUTTON_Calculate = wxID_HIGHEST + 4,
	TEXT_Answer = wxID_HIGHEST + 3,
	TEXT_Divisor = wxID_HIGHEST + 2, // declares an id which will be used to call our button
	TEXT_Dividend = wxID_HIGHEST + 1, // declares an id which will be used to call our button
};