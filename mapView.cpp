
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
		
		p->x = (int)(distanceLongLat(minLongitude, mypoint[i].longitude, maxLatitude, maxLatitude) / ratio / 10) + 300;
		p->y = (int)(distanceLongLat(minLongitude, minLongitude, maxLatitude, mypoint[i].latitude) / ratio / 10) + 50;
		
		mp.push_back(*p);
	}

	
	//pDC->MoveTo(mp[0]);
	POINT *pt = new POINT[POINTNUM];
	CPen pen;
	pen.CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	CPen* oldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < POINTNUM; i++)
	{
		
		CString str;
		str.Format(_T("%d"), i);
		
		pDC->TextOutW(mp[i].x, mp[i].y, str);
		
		//pDC->LineTo(mp[i]);
		
		pt[i].x = mp[i].x;
		pt[i].y = mp[i].y;	
	}
	pDC->Polyline(pt, 6);
	pDC->SelectObject(oldPen);
	delete p;
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
