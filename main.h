#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class LongDivApp: public wxApp
{
  public:
  virtual bool OnInit() wxOVERRIDE;
  virtual int OnExit() wxOVERRIDE;
};