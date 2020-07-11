#pragma once
#include <afxwin.h>
class MyCustom_CEdit :
	public CEdit
{
public:
	MyCustom_CEdit();
	~MyCustom_CEdit();


	bool isFocused = false;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

};

