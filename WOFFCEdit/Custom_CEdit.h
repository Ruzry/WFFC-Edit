#pragma once
#include <afxwin.h>


class Custom_CEdit :
	public CEdit
{
public:
	Custom_CEdit();
	~Custom_CEdit();


	bool checkPoint;
	bool negative;
	bool isFocused = false;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

