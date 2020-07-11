#include "Custom_CEdit.h"



Custom_CEdit::Custom_CEdit()
{
	CEdit();
}


Custom_CEdit::~Custom_CEdit()
{
}

BEGIN_MESSAGE_MAP(Custom_CEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

void Custom_CEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == '.' && checkPoint == true) //Is a point and there is already a point
	{
		//Show message  
	}
	else if (nChar == '.' && checkPoint == false) //Is a point but there is no point
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}

	if ((nChar < '0' || nChar > '9') && nChar != 8) //Is not a number or backspace
	{
		//Show message
	}
	else //Valid
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}

	if (nChar == '-' && negative == true) {
	
	}
	else if (nChar == '-' && negative == false) {
		
		negative = true;
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}

	CString temp;
	this->GetWindowTextW(temp);

	if (negative == true) {
		if (temp.Find('-') != 0) {
			temp.Remove('-');
			this->SetWindowTextW(temp);
		}
	}
}

void Custom_CEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString temp;
	this->GetWindowTextW(temp);

	if (temp.Find('.') == -1)
		checkPoint = false; //There is no point
	else
		checkPoint = true; //There is a point

	if (temp.Find('-') == -1)
		negative = false;
	else
		negative = true;


	OutputDebugString(temp);
	OutputDebugStringA("\n");

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}


