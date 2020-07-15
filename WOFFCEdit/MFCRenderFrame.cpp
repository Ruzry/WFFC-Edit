
#include "MFCRenderFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildRender::CChildRender()
{
	scrollPosition = 0.0f;
}

CChildRender::~CChildRender()
{
}


BEGIN_MESSAGE_MAP(CChildRender, CWnd)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHWHEEL()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildRender::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildRender::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

void CChildRender::OnMouseMove(UINT nFlags, CPoint point)
{
	mouseInWindow = true;

	TRACKMOUSEEVENT tme;
	tme.cbSize = sizeof(tme);
	tme.hwndTrack = this->GetSafeHwnd();
	tme.dwFlags = TME_HOVER | TME_LEAVE;
	tme.dwHoverTime = HOVER_DEFAULT;
	TrackMouseEvent(&tme);

	CWnd::OnMouseMove(nFlags, point);
	
}

void CChildRender::OnMouseLeave()
{
	mouseInWindow = false;
	CWnd::OnMouseLeave();
	
}

BOOL CChildRender::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

	scrollPosition += zDelta;

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}




