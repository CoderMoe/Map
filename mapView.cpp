
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
END_MESSAGE_MAP()

// CmapView construction/destruction

CmapView::CmapView()
{
	// TODO: add construction code here
	mypoint[0].longitude = 116.380825;//116.380825,39.902988
	mypoint[0].latitude = 39.902988;
	mypoint[1].longitude = 116.380789;//116.380789,39.887211
	mypoint[1].latitude = 39.887211;
	mypoint[2].longitude = 116.36771;//116.36771,39.886934
	mypoint[2].latitude = 39.886934;
	mypoint[3].longitude = 116.360164;//116.360164,39.879847
	mypoint[3].latitude = 39.879847;
	mypoint[4].longitude = 116.3708;//116.3708,39.875307
	mypoint[4].latitude = 39.875307;
}

CmapView::~CmapView()
{
	
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
		extern void minLonmaxLat(MYPOINT * point, int NUM, double minLongitude, double maxLatitude);
		extern double distanceLongLat(double longitudeA, double longitudeB, double latitudeA, double latitudeB);
		double minLongitude = mypoint[0].longitude;
		double maxLatitude = mypoint[0].latitude;
		minLonmaxLat(mypoint, POINTNUM, minLongitude, maxLatitude);
		
		p->x = (int)(distanceLongLat(minLongitude, mypoint[i].longitude, maxLatitude, maxLatitude) / ratio / 2)+550;
		p->y = (int)(distanceLongLat(minLongitude, minLongitude, maxLatitude, mypoint[i].latitude) / ratio / 2)+50;
		
		mp.push_back(*p);
	}

	
	pDC->MoveTo(mp[0]);
	for (int i = 0; i < POINTNUM; i++)
	{
		CPen pen;
		pen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		CPen* oldPen = pDC->SelectObject(&pen);
		CString str;
		str.Format(_T("%d"), i);
		
		pDC->TextOutW(mp[i].x, mp[i].y, str);
		
		pDC->LineTo(mp[i]);
		pDC->SelectObject(oldPen);
		
		
	}
	delete p;
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
