#pragma once
#include "afxdialogex.h"
#include "resource.h"
#include "afxwin.h"
#include "SceneObject.h"
#include <vector>
#include "DisplayObject.h"
#include <codecvt>


// utility wrapper to adapt locale-bound facets for wstring/wbuffer convert
template <typename Facet>
struct deletable_facet : Facet
{
	using Facet::Facet;
};

// SelectDialogue dialog
class SelectDialogue : public CDialogEx
{
	DECLARE_DYNAMIC(SelectDialogue)

public:
	SelectDialogue(CWnd* pParent, std::vector<SceneObject>* SceneGraph);   // modal // takes in out scenegraph in the constructor
	SelectDialogue(CWnd* pParent = NULL);
	virtual ~SelectDialogue();
	void SetObjectData(std::vector<SceneObject>* SceneGraph, std::vector<DisplayObject>* displayList, std::vector<int> * Selection, std::vector<int> * previouseIDs, bool* selected);	//passing in pointers to the data the class will operate on.
	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

private:
	bool* m_selected;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void End();		//kill the dialogue
	afx_msg void Select();	//Item has been selected

	std::vector<SceneObject> * m_sceneGraph;
	std::vector<int>* m_currentSelections;
	std::vector<int>* m_previousSelections;
	std::vector<DisplayObject>* m_displayList;

	DECLARE_MESSAGE_MAP()
public:
	// Control variable for more efficient access of the listbox
	CListBox m_listBox;
	virtual BOOL OnInitDialog() override;
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLbnSelchangeList1();

	CButton m_OkButton;
};


INT_PTR CALLBACK SelectProc( HWND   hwndDlg,UINT   uMsg,WPARAM wParam,LPARAM lParam);