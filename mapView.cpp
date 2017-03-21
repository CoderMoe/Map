
// mapView.cpp : implementation of the CmapView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "map.h"
#endif

#include "mapDoc.h"
#include "mapView.h"
#include "cmath"
#include "vector"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmapView

IMPLEMENT_DYNCREATE(CmapView, CView)

BEGIN_MESSAGE_MAP(CmapView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CmapView construction/destruction

CmapView::CmapView()
{
	// TODO: add construction code here
	m_bMouseDrag = FALSE;
	m_bMouseClick = FALSE;
	m_reDrawFlag = TRUE;
	m_ptDragStart.x = 0;
	m_ptDragStart.y = 0;
	m_ptDragOffset.x = 0;
	m_ptDragOffset.y = 0;
	scale = 1;

	mypoint[0].longitude = 116.404682;//116.404682,39.919798
	mypoint[0].latitude = 39.919798;
	mypoint[1].longitude = 116.408491;//116.408491,39.920019
	mypoint[1].latitude = 39.920019;
	mypoint[2].longitude = 116.407916;//116.407916,39.929315
	mypoint[2].latitude = 39.929315;
	mypoint[3].longitude = 116.398286;//116.398286,39.929039
	mypoint[3].latitude = 39.929039;
	mypoint[4].longitude = 116.398717;//116.398717,39.919577
	mypoint[4].latitude = 39.919577;
	mypoint[5].longitude = 116.402239; //116.402239,39.919743
	mypoint[5].latitude = 39.919743;
}

CmapView::~CmapView()
{
	delete temppt;
}

BOOL CmapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CmapView drawing

void CmapView::OnDraw(CDC* pDC)
{
	CmapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	
	std::vector<CPoint> mp;

	extern double mymain(MYPOINT *mypoint, int NUM);
	double maxdistance;
	maxdistance = mymain(mypoint, POINTNUM);
	CRect rect;
	GetClientRect(&rect);
	
	double ratio = 2 * maxdistance / sqrt((rect.Height() * rect.Height() + rect.Width() * rect.Width()));
	CPoint * p = new CPoint();
	for (int i = 0; i < POINTNUM; i++)
	{
		extern void minLonmaxLat(MYPOINT * point, int NUM, double  *minLongitude, double *maxLatitude);
		extern double distanceLongLat(double longitudeA, double longitudeB, double latitudeA, double latitudeB);
		double minLongitude = mypoint[0].longitude;
		double maxLatitude = mypoint[0].latitude;
		minLonmaxLat(mypoint, POINTNUM, &minLongitude, &maxLatitude);

		p->x = (int)(distanceLongLat(minLongitude, mypoint[i].longitude, maxLatitude, maxLatitude) / ratio / 2);
		p->y = (int)(distanceLongLat(minLongitude, minLongitude, maxLatitude, mypoint[i].latitude) / ratio / 2);

		mp.push_back(*p);
	}
	delete p;

	
	//pDC->MoveTo(mp[0]);
	POINT *pt = new POINT[POINTNUM];
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);

	for (int i = 0; i < POINTNUM; i++)
	{

		CString str;
		str.Format(_T("%d"), i);
		//pDC->LineTo(mp[i]);
		if (m_reDrawFlag)
		{
			temppt[i].x = mp[i].x;
			temppt[i].y = mp[i].y;
		}
	
		pt[i].x = temppt[i].x + m_ptDragOffset.x;
		pt[i].y = temppt[i].y + m_ptDragOffset.y;
		temppt[i].x = pt[i].x * scale;
		temppt[i].y = pt[i].y * scale;
		
		pDC->TextOutW(temppt[i].x, temppt[i].y, str);
	}
	
	pDC->Polyline(temppt, 6);
	pDC->SelectObject(oldPen);
	scale = 1;
	delete pt;
}


// CmapView printing

BOOL CmapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CmapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CmapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CmapView diagnostics

#ifdef _DEBUG
void CmapView::AssertValid() const
{
	CView::AssertValid();
}

void CmapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmapDoc* CmapView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmapDoc)));
	return (CmapDoc*)m_pDocument;
}
#endif //_DEBUG


// CmapView message handlers


void CmapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	m_bMouseClick = TRUE;
	m_ptDragStart.x = point.x;//保存鼠标第一次点击位置的坐标
	m_ptDragStart.y = point.y;
//	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}


void CmapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_ptDragOffset.x = 0;
	m_ptDragOffset.y = 0;
	m_bMouseDrag = FALSE;
	m_bMouseClick = FALSE;

	CView::OnLButtonUp(nFlags, point);
}


void CmapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bMouseDrag = TRUE;
	if (m_bMouseDrag == TRUE && m_bMouseClick == TRUE)
	{
	
		m_ptDragOffset.x = (point.x - m_ptDragStart.x) / 30;
		m_ptDragOffset.y = (point.y - m_ptDragStart.y) / 30;
		m_reDrawFlag = FALSE;
		Invalidate();
	}
	
	CView::OnMouseMove(nFlags, point);
}


BOOL CmapView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	if (zDelta > 0)
	{
		scale = scale * 1.5;
	}
	if (zDelta < 0)
	{
		
		scale = scale / 1.5;	
	}
	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
