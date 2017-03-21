
// mapView.h : interface of the CmapView class
//

#pragma once
#define POINTNUM 6
#include "vector"
struct MYPOINT
{
	double longitude;
	double latitude;
};

class CmapView : public CView
{
private:
	MYPOINT mypoint[POINTNUM];
	BOOL	m_bMouseDrag;//判断鼠标是否被拖拽的布尔型变量
	BOOL	m_bMouseClick;
	POINT   m_ptDragStart;//鼠标第一次点击地图时的坐标
	POINT   m_ptDragOffset;//鼠标第二次点击与第一次点击的偏移量
	BOOL    m_reDrawFlag;
	POINT * temppt = new POINT[POINTNUM];
	double   scale;
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
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in mapView.cpp
inline CmapDoc* CmapView::GetDocument() const
   { return reinterpret_cast<CmapDoc*>(m_pDocument); }
#endif

