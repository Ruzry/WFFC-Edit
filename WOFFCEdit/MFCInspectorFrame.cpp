#include "MFCInspectorFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

MFCInspectorFrame::MFCInspectorFrame()
{
}


MFCInspectorFrame::~MFCInspectorFrame()
{
}

BEGIN_MESSAGE_MAP(MFCInspectorFrame, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL MFCInspectorFrame::PreCreateWindow(CREATESTRUCT & cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void MFCInspectorFrame::OnPaint()
{
	CPaintDC dc(this);
}
