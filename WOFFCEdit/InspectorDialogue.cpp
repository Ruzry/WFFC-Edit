// InspectorDialogue.cpp : implementation file
//

#include "stdafx.h"
#include "InspectorDialogue.h"
#include "afxdialogex.h"


// InspectorDialogue dialog

IMPLEMENT_DYNAMIC(InspectorDialogue, CDialogEx)

InspectorDialogue::InspectorDialogue(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, check_enableDisable(TRUE)
{
	m_selectedObjects = new std::vector<int>;
	m_selectedObjects->clear();
}

InspectorDialogue::~InspectorDialogue()
{
}

/**
	Initalize pointer connections between toolMain, this and the 3D preview window.
	@param ToolMain* pointer
*/
void InspectorDialogue::initializeConnection(ToolMain * toolSystem)
{
	m_Tool_System = toolSystem;
	m_Display_List = m_Tool_System->getDisplayList();
	m_selectedObjects = m_Tool_System->getSelectedObjects();
	m_inputCommands = m_Tool_System->getInputCommands();

	m_d3d11Renderer.setSelectedObjects(m_Tool_System->getSelectedObjects());
	m_d3d11Renderer.setInputCommands(m_Tool_System->getInputCommands());
	m_d3d11Renderer.setMouseInWindow(&m_DirXView.mouseInWindow);
}

/**
	Dialogue Update function
*/
void InspectorDialogue::update()
{

	updateSelectionEditText();

	updateTransformEditText();

	updateNameEdit();

	if (m_selectedObjects->size() == 1) {
		
		//Update Sliders

		slider_X_Pos.SetPos(m_Display_List->at(m_selectedObjects->at(0)).m_X_Pos_Slider_Offset);

		slider_Y_Pos.SetPos(m_Display_List->at(m_selectedObjects->at(0)).m_Y_Pos_Slider_Offset);

		slider_Z_Pos.SetPos(m_Display_List->at(m_selectedObjects->at(0)).m_Z_Pos_Slider_Offset);

		slider_X_Rot.SetPos(m_Display_List->at(m_selectedObjects->at(0)).m_X_Rot_Slider_Offset);

		slider_Y_Rot.SetPos(m_Display_List->at(m_selectedObjects->at(0)).m_Y_Rot_Slider_Offset);

		slider_Z_Rot.SetPos(m_Display_List->at(m_selectedObjects->at(0)).m_Z_Rot_Slider_Offset);

		slider_X_Scale.SetPos(m_Display_List->at(m_selectedObjects->at(0)).m_X_Scale_Slider_Offset);

		slider_Y_Scale.SetPos(m_Display_List->at(m_selectedObjects->at(0)).m_Y_Scale_Slider_Offset);

		slider_Z_Scale.SetPos(m_Display_List->at(m_selectedObjects->at(0)).m_Z_Scale_Slider_Offset);
	
		//Updates Check box state
		if (check_focus == false) {
			if (m_Display_List->at(m_selectedObjects->at(0)).m_render)
				check_Visible.SetCheck(BST_CHECKED);
			else
				check_Visible.SetCheck(BST_UNCHECKED);
		}
	}
	else {
	
		//Set sliders position to default if nothing is selected

		slider_X_Pos.SetPos(0);

		slider_Y_Pos.SetPos(0);

		slider_Z_Pos.SetPos(0);

		slider_X_Rot.SetPos(0);

		slider_Y_Rot.SetPos(0);

		slider_Z_Rot.SetPos(0);

		slider_X_Scale.SetPos(0);

		slider_Y_Scale.SetPos(0);

		slider_Z_Scale.SetPos(0);
	
	}

	m_d3d11Renderer.Tick();

}

/**
	Seperate function for updating the ID Display box
*/
void InspectorDialogue::updateSelectionEditText()
{
	CString outputString;
	std::wstring tempString;

	if (m_selectedObjects->size() > 0) {

		outputString.Empty();

		for (int i = 0; i < m_selectedObjects->size(); i++) {

			if (i == 0) {
				int temp = m_selectedObjects->at(i);
				tempString = std::to_wstring(temp);
			}
			else {
				tempString.append(L", ");
				tempString.append(std::to_wstring(m_selectedObjects->at(i)));
			}

			outputString = tempString.c_str();
		}

		SetDlgItemText(IDC_EDIT_TEXT_ID, outputString);
	}
	else
	{
		outputString.Empty();
		outputString.SetString(_T("Select an Object "));
		SetDlgItemText(IDC_EDIT_TEXT_ID, outputString);
	}
}

/**
	Seperate Function for updating the Transform text boxes
*/
void InspectorDialogue::updateTransformEditText()
{

	CString posXString, posYString, posZString;
	CString rotXString, rotYString, rotZString;
	CString scaleXString, scaleYString, scaleZString;

	std::wstring tempString;

	if (m_selectedObjects->size() == 1) {
	
		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects->at(0)).m_position.x + m_Display_List->at(m_selectedObjects->at(0)).m_X_Pos_Slider_Offset);
		posXString = tempString.c_str();
	
		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects->at(0)).m_position.y + m_Display_List->at(m_selectedObjects->at(0)).m_Y_Pos_Slider_Offset);
		posYString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects->at(0)).m_position.z + m_Display_List->at(m_selectedObjects->at(0)).m_Z_Pos_Slider_Offset);
		posZString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects->at(0)).m_orientation.x + m_Display_List->at(m_selectedObjects->at(0)).m_X_Rot_Slider_Offset);
		rotXString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects->at(0)).m_orientation.y + m_Display_List->at(m_selectedObjects->at(0)).m_Y_Rot_Slider_Offset);
		rotYString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects->at(0)).m_orientation.z + m_Display_List->at(m_selectedObjects->at(0)).m_Z_Rot_Slider_Offset);
		rotZString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects->at(0)).m_scale.x + m_Display_List->at(m_selectedObjects->at(0)).m_X_Scale_Slider_Offset);
		scaleXString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects->at(0)).m_scale.y + m_Display_List->at(m_selectedObjects->at(0)).m_Y_Scale_Slider_Offset);
		scaleYString = tempString.c_str();

		tempString = std::to_wstring(m_Display_List->at(m_selectedObjects->at(0)).m_scale.z + m_Display_List->at(m_selectedObjects->at(0)).m_Z_Scale_Slider_Offset);
		scaleZString = tempString.c_str();

	}
	else if (m_selectedObjects->size() > 1) 
	{
	
	}
	else {
	
	
	}



	if (!edit_X_Pos.isFocused) 
		SetDlgItemText(IDC_EDIT_X_POS, posXString);

	if (!edit_Y_Pos.isFocused)
		SetDlgItemText(IDC_EDIT_Y_POS, posYString);
	
	if (!edit_Z_Pos.isFocused)
		SetDlgItemText(IDC_EDIT_Z_POS, posZString);

	if (!edit_X_Rot.isFocused)
		SetDlgItemText(IDC_EDIT_X_ROT, rotXString);

	if (!edit_Y_Rot.isFocused)
		SetDlgItemText(IDC_EDIT_Y_ROT, rotYString);
	
	if (!edit_Z_Rot.isFocused)
		SetDlgItemText(IDC_EDIT_Z_ROT, rotZString);

	if (!edit_X_Scale.isFocused)
		SetDlgItemText(IDC_EDIT_X_SCALE, scaleXString);

	if (!edit_Y_Scale.isFocused)
		SetDlgItemText(IDC_EDIT_Y_SCALE, scaleYString);

	if (!edit_Z_Scale.isFocused)
		SetDlgItemText(IDC_EDIT_Z_SCALE, scaleZString);

}

/**
	Reset sliders back to default
*/
void InspectorDialogue::resetSliders()
{
	slider_X_Pos.SetPos(0);
	slider_Y_Pos.SetPos(0);
	slider_Z_Pos.SetPos(0);

	slider_X_Rot.SetPos(0);
	slider_Y_Rot.SetPos(0);
	slider_Z_Rot.SetPos(0);

	slider_X_Scale.SetPos(0);
	slider_Y_Scale.SetPos(0);
	slider_Z_Scale.SetPos(0);

}

/**
	Update function for Name Input box
*/
void InspectorDialogue::updateNameEdit()
{
	CString temp;

	if (m_selectedObjects->size() == 1) 
		temp = m_Display_List->at(m_selectedObjects->at(0)).m_name.c_str();
	

	if(!edit_Set_Name_IsFocused)
		SetDlgItemText(IDC_EDIT_NAME_INPUT, temp);
	
}

/**
	MFC Generated Method Linking UI elements to Code counterparts
*/
void InspectorDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXT_ID, edit_TextBox_ObjectID);

	DDX_Control(pDX, IDC_EDIT_X_POS, edit_X_Pos);
	DDX_Control(pDX, IDC_EDIT_Y_POS, edit_Y_Pos);
	DDX_Control(pDX, IDC_EDIT_Z_POS, edit_Z_Pos);

	DDX_Control(pDX, IDC_EDIT_X_ROT, edit_X_Rot);
	DDX_Control(pDX, IDC_EDIT_Y_ROT, edit_Y_Rot);
	DDX_Control(pDX, IDC_EDIT_Z_ROT, edit_Z_Rot);

	DDX_Control(pDX, IDC_EDIT_X_SCALE, edit_X_Scale);
	DDX_Control(pDX, IDC_EDIT_Y_SCALE, edit_Y_Scale);
	DDX_Control(pDX, IDC_EDIT_Z_SCALE, edit_Z_Scale);

	DDX_Control(pDX, IDC_SLIDER_X_POS, slider_X_Pos);
	DDX_Control(pDX, IDC_SLIDER_Y_POS, slider_Y_Pos);
	DDX_Control(pDX, IDC_SLIDER_Z_POS, slider_Z_Pos);

	DDX_Control(pDX, IDC_SLIDER_X_ROT, slider_X_Rot);
	DDX_Control(pDX, IDC_SLIDER_Y_ROT, slider_Y_Rot);
	DDX_Control(pDX, IDC_SLIDER_Z_ROT, slider_Z_Rot);

	DDX_Control(pDX, IDC_SLIDER_X_SCALE, slider_X_Scale);
	DDX_Control(pDX, IDC_SLIDER_Y_SCALE, slider_Y_Scale);
	DDX_Control(pDX, IDC_SLIDER_Z_SCALE, slider_Z_Scale);
	DDX_Control(pDX, IDC_CHECK_VISIBLE, check_Visible);

	DDX_Check(pDX, IDC_CHECK_VISIBLE, check_enableDisable);
	DDX_Control(pDX, IDC_EDIT_NAME_INPUT, edit_Set_Name);
}

/**
	Standard CWnd Initialisation method for the 3D Inspector
*/
BOOL InspectorDialogue::OnInitDialog()
{
	//Initialize sliders to sit in the middle for both positive and negative adujustment

	CDialogEx::OnInitDialog();

	//edit_X_Pos.ModifyStyle(0, ES_NUMBER);

	slider_X_Pos.SetRange(-200, 200, true);
	slider_X_Pos.SetPos(0);

	slider_Y_Pos.SetRange(-200, 200, true);
	slider_Y_Pos.SetPos(0);

	slider_Z_Pos.SetRange(-200, 200, true);
	slider_Z_Pos.SetPos(0);

	slider_X_Rot.SetRange(-200, 200, true);
	slider_X_Rot.SetPos(0);

	slider_Y_Rot.SetRange(-200, 200, true);
	slider_Y_Rot.SetPos(0);

	slider_Z_Rot.SetRange(-200, 200, true);
	slider_Z_Rot.SetPos(0);

	slider_X_Scale.SetRange(-200, 200, true);
	slider_X_Scale.SetPos(0);

	slider_Y_Scale.SetRange(-200, 200, true);
	slider_Y_Scale.SetPos(0);

	slider_Z_Scale.SetRange(-200, 200, true);
	slider_Z_Scale.SetPos(0);

	//edit_test.SubclassDlgItem(IDC_EDIT1, this);
	//edit_X_Pos.SubclassDlgItem(IDC_EDIT_X_POS, this);

		// create a view to occupy the client area of the frame //This is where DirectX is rendered
	if (!m_DirXView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(35, 220, 605, 445), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	m_DirXView.ShowWindow(SW_SHOW);
	m_d3d11Renderer.Initialize(m_DirXView.GetSafeHwnd(), 600, 440);

	return true;
}


BEGIN_MESSAGE_MAP(InspectorDialogue, CDialogEx)

	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_X_POS, &InspectorDialogue::OnNMCustomdrawSliderXPos)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Y_POS, &InspectorDialogue::OnNMCustomdrawSliderYPos)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Z_POS, &InspectorDialogue::OnNMCustomdrawSliderZPos)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_X_ROT, &InspectorDialogue::OnNMCustomdrawSliderXRot)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Y_ROT, &InspectorDialogue::OnNMCustomdrawSliderYRot)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Z_ROT, &InspectorDialogue::OnNMCustomdrawSliderZRot)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_X_SCALE, &InspectorDialogue::OnNMCustomdrawSliderXScale)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Y_SCALE, &InspectorDialogue::OnNMCustomdrawSliderYScale)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Z_SCALE, &InspectorDialogue::OnNMCustomdrawSliderZScale)
	ON_EN_SETFOCUS(IDC_EDIT_X_POS, &InspectorDialogue::OnEnSetfocusEditXPos)
	ON_EN_KILLFOCUS(IDC_EDIT_X_POS, &InspectorDialogue::OnEnKillfocusEditXPos)
	ON_EN_CHANGE(IDC_EDIT_X_POS, &InspectorDialogue::OnEnChangeEditXPos)
	ON_EN_SETFOCUS(IDC_EDIT_Y_POS, &InspectorDialogue::OnEnSetfocusEditYPos)
	ON_EN_KILLFOCUS(IDC_EDIT_Y_POS, &InspectorDialogue::OnEnKillfocusEditYPos)
	ON_EN_CHANGE(IDC_EDIT_Y_POS, &InspectorDialogue::OnEnChangeEditYPos)
	ON_EN_SETFOCUS(IDC_EDIT_Z_POS, &InspectorDialogue::OnEnSetfocusEditZPos)
	ON_EN_KILLFOCUS(IDC_EDIT_Z_POS, &InspectorDialogue::OnEnKillfocusEditZPos)
	ON_EN_CHANGE(IDC_EDIT_Z_POS, &InspectorDialogue::OnEnChangeEditZPos)
	ON_EN_SETFOCUS(IDC_EDIT_X_ROT, &InspectorDialogue::OnEnSetfocusEditXRot)
	ON_EN_KILLFOCUS(IDC_EDIT_X_ROT, &InspectorDialogue::OnEnKillfocusEditXRot)
	ON_EN_CHANGE(IDC_EDIT_X_ROT, &InspectorDialogue::OnEnChangeEditXRot)
	ON_EN_SETFOCUS(IDC_EDIT_Y_ROT, &InspectorDialogue::OnEnSetfocusEditYRot)
	ON_EN_KILLFOCUS(IDC_EDIT_Y_ROT, &InspectorDialogue::OnEnKillfocusEditYRot)
	ON_EN_CHANGE(IDC_EDIT_Y_ROT, &InspectorDialogue::OnEnChangeEditYRot)
	ON_EN_SETFOCUS(IDC_EDIT_Z_ROT, &InspectorDialogue::OnEnSetfocusEditZRot)
	ON_EN_KILLFOCUS(IDC_EDIT_Z_ROT, &InspectorDialogue::OnEnKillfocusEditZRot)
	ON_EN_CHANGE(IDC_EDIT_Z_ROT, &InspectorDialogue::OnEnChangeEditZRot)
	ON_EN_SETFOCUS(IDC_EDIT_X_SCALE, &InspectorDialogue::OnEnSetfocusEditXScale)
	ON_EN_KILLFOCUS(IDC_EDIT_X_SCALE, &InspectorDialogue::OnEnKillfocusEditXScale)
	ON_EN_CHANGE(IDC_EDIT_X_SCALE, &InspectorDialogue::OnEnChangeEditXScale)
	ON_EN_SETFOCUS(IDC_EDIT_Y_SCALE, &InspectorDialogue::OnEnSetfocusEditYScale)
	ON_EN_KILLFOCUS(IDC_EDIT_Y_SCALE, &InspectorDialogue::OnEnKillfocusEditYScale)
	ON_EN_CHANGE(IDC_EDIT_Y_SCALE, &InspectorDialogue::OnEnChangeEditYScale)
	ON_EN_SETFOCUS(IDC_EDIT_Z_SCALE, &InspectorDialogue::OnEnSetfocusEditZScale)
	ON_EN_KILLFOCUS(IDC_EDIT_Z_SCALE, &InspectorDialogue::OnEnKillfocusEditZScale)
	ON_EN_CHANGE(IDC_EDIT_Z_SCALE, &InspectorDialogue::OnEnChangeEditZScale)
	ON_BN_CLICKED(IDC_CHECK_VISIBLE, &InspectorDialogue::OnBnClickedCheckVisible)
	ON_BN_KILLFOCUS(IDC_CHECK_VISIBLE, &InspectorDialogue::OnBnKillfocusCheckVisible)
	ON_BN_SETFOCUS(IDC_CHECK_VISIBLE, &InspectorDialogue::OnBnSetfocusCheckVisible)
	ON_EN_CHANGE(IDC_EDIT_NAME_INPUT, &InspectorDialogue::OnEnChangeEditNameInput)
	ON_EN_SETFOCUS(IDC_EDIT_NAME_INPUT, &InspectorDialogue::OnEnSetfocusEditNameInput)
	ON_EN_KILLFOCUS(IDC_EDIT_NAME_INPUT, &InspectorDialogue::OnEnKillfocusEditNameInput)
END_MESSAGE_MAP()


// InspectorDialogue message handlers






void InspectorDialogue::OnNMCustomdrawSliderXPos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (m_selectedObjects->size() == 1) {
		m_Display_List->at(m_selectedObjects->at(0)).m_X_Pos_Slider_Offset = slider_X_Pos.GetPos();
	}
	else {
		slider_X_Pos.SetPos(0);
	}

	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderYPos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (m_selectedObjects->size() == 1) {
		m_Display_List->at(m_selectedObjects->at(0)).m_Y_Pos_Slider_Offset = slider_Y_Pos.GetPos();
	}
	else {
		slider_Y_Pos.SetPos(0);
	}

	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderZPos(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (m_selectedObjects->size() == 1) {
		m_Display_List->at(m_selectedObjects->at(0)).m_Z_Pos_Slider_Offset = slider_Z_Pos.GetPos();
	}
	else {
		slider_Z_Pos.SetPos(0);
	}

	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderXRot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (m_selectedObjects->size() == 1) {
		m_Display_List->at(m_selectedObjects->at(0)).m_X_Rot_Slider_Offset = slider_X_Rot.GetPos();
	}
	else {
		slider_X_Rot.SetPos(0);
	}

	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderYRot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (m_selectedObjects->size() == 1) {
		m_Display_List->at(m_selectedObjects->at(0)).m_Y_Rot_Slider_Offset = slider_Y_Rot.GetPos();
	}
	else {
		slider_Y_Rot.SetPos(0);
	}
	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderZRot(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (m_selectedObjects->size() == 1) {
		m_Display_List->at(m_selectedObjects->at(0)).m_Z_Rot_Slider_Offset = slider_Z_Rot.GetPos();
	}
	else {
		slider_Z_Rot.SetPos(0);
	}
	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderXScale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (m_selectedObjects->size() == 1) {
		m_Display_List->at(m_selectedObjects->at(0)).m_X_Scale_Slider_Offset = slider_X_Scale.GetPos();
	}
	else {
		slider_X_Scale.SetPos(0);
	}
	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderYScale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (m_selectedObjects->size() == 1) {
		m_Display_List->at(m_selectedObjects->at(0)).m_Y_Scale_Slider_Offset = slider_Y_Scale.GetPos();
	}
	else {
		slider_Y_Scale.SetPos(0);
	}
	*pResult = 0;
}


void InspectorDialogue::OnNMCustomdrawSliderZScale(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	if (m_selectedObjects->size() == 1) {
		m_Display_List->at(m_selectedObjects->at(0)).m_Z_Scale_Slider_Offset = slider_Z_Scale.GetPos();
	}
	else {
		slider_Z_Scale.SetPos(0);
	}
	*pResult = 0;
}


void InspectorDialogue::OnEnSetfocusEditXPos()
{
	edit_X_Pos.isFocused = true;

	if (m_selectedObjects->size() == 1) {

		m_Display_List->at(m_selectedObjects->at(0)).m_position.x += m_Display_List->at(m_selectedObjects->at(0)).m_X_Pos_Slider_Offset;
		m_Display_List->at(m_selectedObjects->at(0)).m_X_Pos_Slider_Offset = 0;
		slider_X_Pos.SetPos(0);

	}
}


void InspectorDialogue::OnEnKillfocusEditXPos()
{
	edit_X_Pos.isFocused = false;
}


void InspectorDialogue::OnEnChangeEditXPos()
{
	if (edit_X_Pos.isFocused) {
		CString temp;
		edit_X_Pos.GetWindowTextW(temp);

		if (temp.GetLength() > 0) {
			m_Display_List->at(m_selectedObjects->at(0)).m_position.x = _ttof(temp);
		}

	}
}


void InspectorDialogue::OnEnSetfocusEditYPos()
{
	edit_Y_Pos.isFocused = true;

	if (m_selectedObjects->size() == 1) {

		m_Display_List->at(m_selectedObjects->at(0)).m_position.y += m_Display_List->at(m_selectedObjects->at(0)).m_Y_Pos_Slider_Offset;
		m_Display_List->at(m_selectedObjects->at(0)).m_Y_Pos_Slider_Offset = 0;
		slider_Y_Pos.SetPos(0);

	}
}


void InspectorDialogue::OnEnKillfocusEditYPos()
{
	edit_Y_Pos.isFocused = false;
}


void InspectorDialogue::OnEnChangeEditYPos()
{
	if (edit_Y_Pos.isFocused) {
		CString temp;
		edit_Y_Pos.GetWindowTextW(temp);

		if (temp.GetLength() > 0) {
			m_Display_List->at(m_selectedObjects->at(0)).m_position.y = _ttof(temp);
		}
	}
}


void InspectorDialogue::OnEnSetfocusEditZPos()
{
	edit_Z_Pos.isFocused = true;

	if (m_selectedObjects->size() == 1) {

		m_Display_List->at(m_selectedObjects->at(0)).m_position.z += m_Display_List->at(m_selectedObjects->at(0)).m_Z_Pos_Slider_Offset;
		m_Display_List->at(m_selectedObjects->at(0)).m_Z_Pos_Slider_Offset = 0;
		slider_Z_Pos.SetPos(0);

	}
}


void InspectorDialogue::OnEnKillfocusEditZPos()
{
	edit_Z_Pos.isFocused = false;
}


void InspectorDialogue::OnEnChangeEditZPos()
{
	if (edit_Z_Pos.isFocused) {
		CString temp;
		edit_Z_Pos.GetWindowTextW(temp);

		if (temp.GetLength() > 0) {
			m_Display_List->at(m_selectedObjects->at(0)).m_position.z = _ttof(temp);
		}
	}
}


void InspectorDialogue::OnEnSetfocusEditXRot()
{
	edit_X_Rot.isFocused = true;

	if (m_selectedObjects->size() == 1) {

		m_Display_List->at(m_selectedObjects->at(0)).m_orientation.x += m_Display_List->at(m_selectedObjects->at(0)).m_X_Rot_Slider_Offset;
		m_Display_List->at(m_selectedObjects->at(0)).m_X_Rot_Slider_Offset = 0;
		slider_X_Rot.SetPos(0);

	}
}


void InspectorDialogue::OnEnKillfocusEditXRot()
{
	edit_X_Rot.isFocused = false;
}


void InspectorDialogue::OnEnChangeEditXRot()
{
	if (edit_X_Rot.isFocused) {
		CString temp;
		edit_X_Rot.GetWindowTextW(temp);

		if (temp.GetLength() > 0) {
			m_Display_List->at(m_selectedObjects->at(0)).m_orientation.x = _ttof(temp);
		}
	}
}


void InspectorDialogue::OnEnSetfocusEditYRot()
{
	edit_Y_Rot.isFocused = true;

	if (m_selectedObjects->size() == 1) {

		m_Display_List->at(m_selectedObjects->at(0)).m_orientation.y += m_Display_List->at(m_selectedObjects->at(0)).m_Y_Rot_Slider_Offset;
		m_Display_List->at(m_selectedObjects->at(0)).m_Y_Rot_Slider_Offset = 0;
		slider_Y_Rot.SetPos(0);

	}
}


void InspectorDialogue::OnEnKillfocusEditYRot()
{
	edit_Y_Rot.isFocused = false;
}


void InspectorDialogue::OnEnChangeEditYRot()
{
	if (edit_Y_Rot.isFocused) {
		CString temp;
		edit_Y_Rot.GetWindowTextW(temp);

		if (temp.GetLength() > 0) {
			m_Display_List->at(m_selectedObjects->at(0)).m_orientation.y = _ttof(temp);
		}
	}
}


void InspectorDialogue::OnEnSetfocusEditZRot()
{
	edit_Z_Rot.isFocused = true;

	if (m_selectedObjects->size() == 1) {

		m_Display_List->at(m_selectedObjects->at(0)).m_orientation.z += m_Display_List->at(m_selectedObjects->at(0)).m_Z_Rot_Slider_Offset;
		m_Display_List->at(m_selectedObjects->at(0)).m_Z_Rot_Slider_Offset = 0;
		slider_Z_Rot.SetPos(0);

	}
}


void InspectorDialogue::OnEnKillfocusEditZRot()
{
	edit_Z_Rot.isFocused = false;
}


void InspectorDialogue::OnEnChangeEditZRot()
{
	if (edit_Z_Rot.isFocused) {
		CString temp;
		edit_Z_Rot.GetWindowTextW(temp);

		if (temp.GetLength() > 0) {
			m_Display_List->at(m_selectedObjects->at(0)).m_orientation.z = _ttof(temp);
		}
	}
}


void InspectorDialogue::OnEnSetfocusEditXScale()
{
	edit_X_Scale.isFocused = true;

	if (m_selectedObjects->size() == 1) {

		m_Display_List->at(m_selectedObjects->at(0)).m_scale.x += m_Display_List->at(m_selectedObjects->at(0)).m_X_Scale_Slider_Offset;
		m_Display_List->at(m_selectedObjects->at(0)).m_X_Scale_Slider_Offset = 0;
		slider_X_Scale.SetPos(0);

	}
}


void InspectorDialogue::OnEnKillfocusEditXScale()
{
	edit_X_Scale.isFocused = false;
}


void InspectorDialogue::OnEnChangeEditXScale()
{
	if (edit_X_Scale.isFocused) {
		CString temp;
		edit_X_Scale.GetWindowTextW(temp);

		if (temp.GetLength() > 0) {
			m_Display_List->at(m_selectedObjects->at(0)).m_scale.x = _ttof(temp);
		}
	}
}


void InspectorDialogue::OnEnSetfocusEditYScale()
{
	edit_Y_Scale.isFocused = true;

	if (m_selectedObjects->size() == 1) {

		m_Display_List->at(m_selectedObjects->at(0)).m_scale.y += m_Display_List->at(m_selectedObjects->at(0)).m_Y_Scale_Slider_Offset;
		m_Display_List->at(m_selectedObjects->at(0)).m_Y_Scale_Slider_Offset = 0;
		slider_Y_Scale.SetPos(0);

	}
}


void InspectorDialogue::OnEnKillfocusEditYScale()
{
	edit_Y_Scale.isFocused = false;
}


void InspectorDialogue::OnEnChangeEditYScale()
{
	if (edit_Y_Scale.isFocused) {
		CString temp;
		edit_Y_Scale.GetWindowTextW(temp);

		if (temp.GetLength() > 0) {
			m_Display_List->at(m_selectedObjects->at(0)).m_scale.y = _ttof(temp);
		}
	}
}


void InspectorDialogue::OnEnSetfocusEditZScale()
{
	edit_Z_Scale.isFocused = true;

	if (m_selectedObjects->size() == 1) {

		m_Display_List->at(m_selectedObjects->at(0)).m_scale.z += m_Display_List->at(m_selectedObjects->at(0)).m_Z_Scale_Slider_Offset;
		m_Display_List->at(m_selectedObjects->at(0)).m_Z_Scale_Slider_Offset = 0;
		slider_Z_Scale.SetPos(0);

	}
}


void InspectorDialogue::OnEnKillfocusEditZScale()
{
	edit_Z_Scale.isFocused = false;
}


void InspectorDialogue::OnEnChangeEditZScale()
{
	if (edit_Z_Scale.isFocused) {
		CString temp;
		edit_Z_Scale.GetWindowTextW(temp);

		if (temp.GetLength() > 0) {
			m_Display_List->at(m_selectedObjects->at(0)).m_scale.z = _ttof(temp);
		}
	}
}


void InspectorDialogue::OnBnClickedCheckVisible()
{
	UpdateData();

	if (check_enableDisable) {
		if (m_selectedObjects->size() == 1){
			m_Display_List->at(m_selectedObjects->at(0)).m_render = true;
		}
	}
	else {
		if (m_selectedObjects->size() == 1) {
			m_Display_List->at(m_selectedObjects->at(0)).m_render = false;
		}
	}
}


void InspectorDialogue::OnBnKillfocusCheckVisible()
{
	check_Visible.SetCheck(BST_UNCHECKED);
	check_focus = false;
}


void InspectorDialogue::OnBnSetfocusCheckVisible()
{
	check_focus = true;

	if (m_selectedObjects->at(0) == 1) {

		if(m_Display_List->at(m_selectedObjects->at(0)).m_render)
			check_Visible.SetCheck(BST_CHECKED);
		else
			check_Visible.SetCheck(BST_UNCHECKED);
	}
}


void InspectorDialogue::OnEnChangeEditNameInput()
{
	CString temp;
	edit_Set_Name.GetWindowTextW(temp);
	CT2CA pszConvertedAnsiString(temp);

	std::string basicString(pszConvertedAnsiString);

	if (m_selectedObjects->size() == 1) {
		m_Display_List->at(m_selectedObjects->at(0)).m_name = basicString;
	
	}

}


void InspectorDialogue::OnEnSetfocusEditNameInput()
{
	edit_Set_Name_IsFocused = true;
}


void InspectorDialogue::OnEnKillfocusEditNameInput()
{
	edit_Set_Name_IsFocused = false;
}
