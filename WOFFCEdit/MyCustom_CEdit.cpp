#include "MyCustom_CEdit.h"



MyCustom_CEdit::MyCustom_CEdit()
{
}


MyCustom_CEdit::~MyCustom_CEdit()
{
}
BEGIN_MESSAGE_MAP(MyCustom_CEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


void MyCustom_CEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}


void MyCustom_CEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
