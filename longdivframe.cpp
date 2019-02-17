#include "longdivframe.h"

LongDivFrame::LongDivFrame(const wxString& title, const wxPoint &pos, const wxSize &size): wxFrame(NULL, wxID_ANY, title, pos, size){
	wxMenu *menuFile = new wxMenu;
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar *menuBar = new wxMenuBar;
	
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");
	
	SetMenuBar(menuBar);
	
	CreateStatusBar();
	SetStatusText("Welcome to Long division calculator!");
	
	Bind(wxEVT_MENU, &LongDivFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &LongDivFrame::OnExit, this, wxID_EXIT);
	
	calculateButton = new wxButton(this,
								   BUTTON_Calculate,
								   _T("Calculate"),
								   wxPoint(140,50),
								   wxSize(75,25),
								   0);
	
	
	TextDivisor = new wxTextCtrl(this,
							 TEXT_Divisor,
							 "",
							 wxPoint(20,20),
							 wxSize(120,20),
							 wxTE_MULTILINE | wxTE_RICH,
							 wxDefaultValidator,
							 wxT("divisor"));
	
	TextDividend = new wxTextCtrl(this,
							 TEXT_Dividend,
							 "",
							 wxPoint(200,20),
							 wxSize(120,20),
							 wxTE_MULTILINE | wxTE_RICH,
							 wxDefaultValidator,
							 wxT("dividend"));
	
	grid = new wxGrid(this,
					  -1,
					  wxPoint( 20, 80 ),
					  wxSize( 1200, 550 )); //was 700, 440
	grid->CreateGrid(100,100);
	
	//Set table properties, so that it is read-only and editing is restricted 
	grid->DisableDragGridSize();
	grid->EnableEditing(false);
	grid->EnableGridLines(false);
	grid->HideColLabels();
	grid->HideRowLabels();
		
}

void LongDivFrame::OnExit(wxCommandEvent& event){
	Close(true);
}

void LongDivFrame::OnAbout(wxCommandEvent& event){
	wxMessageBox("This is a Long division calculator",
				 "About Long division calculator",
				 wxOK | wxICON_INFORMATION);
}

void LongDivFrame::OnCalculateButtonPress(wxCommandEvent& event){
	wxStrDividend = TextDividend->GetValue();
	wxString wxStrDivisor = TextDivisor->GetValue();
	std::string strDivisor = wxStrDivisor.ToStdString();
	divisor = std::stoull (strDivisor, 0, 0);
	
	gridRowPosition = 2;
	gridColumnPosition = 2;
	
	grid->ClearGrid();
	
	grid->SetCellValue(1, 0, wxStrDivisor);
	grid->SetCellValue(1, 1, L"\u27CC");
	for(int i = 0; i < wxStrDividend.size(); i++){
		grid->SetCellValue(1, i+2, wxStrDividend[i]);
	}

	std::string quotient = CalculateLongDivision();
	
	for(int i = 0; i < quotient.size(); i++){
		grid->SetCellValue(0, i+2, quotient[i]);
	}
	
}



std::string LongDivFrame::CalculateLongDivision(){
	
	std::string strQuotient;
	std::string strDividend = wxStrDividend.ToStdString();
	int stringPosition = 0;
	unsigned long long sequence = strDividend[stringPosition] - '0';
	
	while (strDividend.size() > stringPosition){
		strQuotient += (sequence / divisor) + '0';
		
		wxString wxStrSequence;
		wxStrSequence << sequence;
		
		wxString wxStrMultiple;
		wxStrMultiple << (sequence / divisor) * divisor;
		
		wxString wxStrDifference;
		wxStrDifference << sequence - ((sequence / divisor) * divisor);
		
		DrawLongDivision(wxStrSequence, wxStrMultiple, wxStrDifference);
		
		if(strDividend.size() == stringPosition + 1 && sequence % divisor != 0){
			int remainder = sequence - ((sequence / divisor) * divisor);
			strQuotient = CalculateLongDivisionRemainder(strQuotient, remainder);
		}
		
		sequence = (sequence % divisor) * 10 + strDividend[++stringPosition] - '0';
	}
	
	// If divisor is greater than number 
    if (strQuotient.length() == 0){
		return "0";
	}
      
    // else return 
    return strQuotient; 
	
}

std::string LongDivFrame::CalculateLongDivisionRemainder(std::string strQuotient, int remainder){
	strQuotient += ".";
	gridColumnPosition++;

	bool quit = false;

	while(quit == false){
		if(remainder % divisor == remainder){
			remainder *= 10;
			strQuotient += (remainder / divisor) + '0';

			wxString wxStrRemainder;
			wxStrRemainder << remainder;

			wxString wxStrMultiple;
			wxStrMultiple << (remainder / divisor) * divisor;

			wxString wxStrDifference;
			wxStrDifference << remainder - ((remainder / divisor) * divisor);

			DrawLongDivision(wxStrRemainder, wxStrMultiple, wxStrDifference);

		}
		else if (remainder % divisor != 0){
			remainder = remainder % divisor;
		}
		else{
			quit = true;
		}
	}
	
	return strQuotient;
	
}

void LongDivFrame::DrawLongDivision(wxString wxStrSequence, wxString wxStrMultiple, wxString wxStrDifference){
	
	int charPosition = wxStrSequence.size() - 1;
	
	for(int i = 0; i < wxStrSequence.size(); i++){
		grid->SetCellValue(gridRowPosition, gridColumnPosition - charPosition, wxStrSequence[i]);
		charPosition--;
	}
	
	gridRowPosition++;
	charPosition = wxStrMultiple.size() - 1;
	
	for(int i = 0; i < wxStrMultiple.size(); i++){
		grid->SetCellValue(gridRowPosition, gridColumnPosition - charPosition, wxStrMultiple[i]);
		charPosition--;
	}
	
	gridRowPosition++;
	charPosition = wxStrDifference.size() - 1;
	
	for(int i = 0; i < wxStrDifference.size(); i++){
		grid->SetCellValue(gridRowPosition, gridColumnPosition - charPosition, wxStrDifference[i]);
		charPosition--;
	}
	
	gridColumnPosition++;
	gridRowPosition++;
	gridRowPosition++;
	
}