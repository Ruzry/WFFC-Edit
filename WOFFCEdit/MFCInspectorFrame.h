#pragma once
#include <afxwin.h>
#include <afxext.h>

class MFCInspectorFrame :
	public CWnd
{
public:
	MFCInspectorFrame();
	~MFCInspectorFrame();

protected:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

