#pragma once
#include <afxwin.h> 
#include <afxext.h>


// CChildView window

class CChildRender : public CWnd
{
	// Construction
public:
	CChildRender();

	// Attributes
public:

	// Operations
public:
	bool mouseInWindow;
	float scrollPosition;
	// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Implementation
public:
	virtual ~CChildRender();
private:
	

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	DECLARE_MESSAGE_MAP()
};

