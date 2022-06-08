
// Adapter - Vector-RasterView.cpp : implementation of the CAdapterVectorRasterView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Adapter - Vector-Raster.h"
#endif

#include "Adapter - Vector-RasterDoc.h"
#include "Adapter - Vector-RasterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdapterVectorRasterView

IMPLEMENT_DYNCREATE(CAdapterVectorRasterView, CView)

BEGIN_MESSAGE_MAP(CAdapterVectorRasterView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CAdapterVectorRasterView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CAdapterVectorRasterView construction/destruction

CAdapterVectorRasterView::CAdapterVectorRasterView() noexcept
{
	// TODO: add construction code here

}

CAdapterVectorRasterView::~CAdapterVectorRasterView()
{
}

BOOL CAdapterVectorRasterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CAdapterVectorRasterView drawing

void CAdapterVectorRasterView::OnDraw(CDC* /*pDC*/)
{
	CAdapterVectorRasterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CAdapterVectorRasterView printing


void CAdapterVectorRasterView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CAdapterVectorRasterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAdapterVectorRasterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAdapterVectorRasterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CAdapterVectorRasterView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CAdapterVectorRasterView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CAdapterVectorRasterView diagnostics

#ifdef _DEBUG
void CAdapterVectorRasterView::AssertValid() const
{
	CView::AssertValid();
}

void CAdapterVectorRasterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAdapterVectorRasterDoc* CAdapterVectorRasterView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAdapterVectorRasterDoc)));
	return (CAdapterVectorRasterDoc*)m_pDocument;
}
#endif //_DEBUG


// CAdapterVectorRasterView message handlers
