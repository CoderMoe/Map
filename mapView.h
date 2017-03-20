
// mapView.h : interface of the CmapView class
//

#pragma once
#define POINTNUM 6
struct MYPOINT
{
	double longitude;
	double latitude;
};

class CmapView : public CView
{
private:
	MYPOINT mypoint[POINTNUM];
protected: // create from serialization only
	CmapView();
	DECLARE_DYNCREATE(CmapView)

// Attributes
public:
	CmapDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CmapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mapView.cpp
inline CmapDoc* CmapView::GetDocument() const
   { return reinterpret_cast<CmapDoc*>(m_pDocument); }
#endif

