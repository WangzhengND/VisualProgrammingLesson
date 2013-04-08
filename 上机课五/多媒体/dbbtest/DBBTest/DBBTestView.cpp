// DBBTestView.cpp : implementation of the CDBBTestView class
//

#include "stdafx.h"
#include "DBBTest.h"

#include "DBBTestDoc.h"
#include "DBBTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView

IMPLEMENT_DYNCREATE(CDBBTestView, CView)

BEGIN_MESSAGE_MAP(CDBBTestView, CView)
	//{{AFX_MSG_MAP(CDBBTestView)
	ON_WM_TIMER()
	ON_COMMAND(ID_TEST_NORMAL, OnTestNormal)
	ON_COMMAND(ID_TEST_DBB, OnTestDbb)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView construction/destruction

CDBBTestView::CDBBTestView()
{
	// TODO: add construction code here
	m_bStart = FALSE;
	m_bUseDBB = FALSE;
	m_nRadius = 1;
}

CDBBTestView::~CDBBTestView()
{
}

BOOL CDBBTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView drawing

void CDBBTestView::OnDraw(CDC* pDC)
{
	CDBBTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView printing

BOOL CDBBTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDBBTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDBBTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView diagnostics

#ifdef _DEBUG
void CDBBTestView::AssertValid() const
{
	CView::AssertValid();
}

void CDBBTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDBBTestDoc* CDBBTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBBTestDoc)));
	return (CDBBTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDBBTestView message handlers

void CDBBTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// ��ʼ����˫������ص�Ҫ��
	InitialDBB();

	// ���ö�ʱ��
	SetTimer(1, 100, NULL);
}

void CDBBTestView::OnTimer(UINT nIDEvent) 
{
	if(!m_bStart)	return;	// �Ƿ�ʼ?

	// ��Ӧ��ʱ���¼�
	
	if(m_nRadius < 16)		// �뾶����
	{
		m_nRadius++;
	}
	else
	{
		m_nRadius = 0;
	}

	// ʹ�ò�ͬ�Ļ�ͼ��ʽ
	if(!m_bUseDBB)
	{
		DrawManyCircle();
	}
	else
	{
		DrawManyCircleUseDBB();
	}

	CView::OnTimer(nIDEvent);
}


void CDBBTestView::DrawManyCircle()
{
	// ��View�ڻ��ܶ��Բ

	CDC *pdcView = this->GetDC();						// �õ�View��DC

	CRect rt;
	this->GetClientRect(&rt);							// ��ͼ����

	pdcView->FillSolidRect(&rt, 0x00FFFFFF);			// ���ð�ɫĨȥ��һ�λ��Ƶ�ͼ��

	// ��Բ
	for(int i = 0; i < rt.Width() - 1; i+= 16)
	{
		for(int j = 0; j < rt.Height() - 1; j+= 16)
		{
			pdcView->Ellipse(i, j, i + m_nRadius, j + m_nRadius);
		}
	}

	this->ReleaseDC(pdcView);							// �ͷ�view���豸����
}


void CDBBTestView::DrawManyCircleUseDBB()
{
	// ��View����˫���廭�ܶ��Բ

	CDC *pdcView = this->GetDC();

	CRect rt;
	this->GetClientRect(&rt);

	m_dcMemory.FillSolidRect(&rt, 0x00FFFFFF);			// ��ɫ���, ע��,����ǻ����ڴ��豸������

	// ��Բ
	for(int i = 0; i < rt.Width() - 1; i+= 16)
	{
		for(int j = 0; j < rt.Height() - 1; j+= 16)
		{
			m_dcMemory.Ellipse(i, j, i + m_nRadius, j + m_nRadius);
		}
	}

	// һ���ԵĽ��ڴ��豸�����ϻ�����ϵ�ͼ��"��"����Ļ��
	pdcView->BitBlt(0, 0, rt.Width(), rt.Height(), &m_dcMemory, 0, 0, SRCCOPY);

	this->ReleaseDC(pdcView);							// �ͷ�view���豸����


}

// ��ʼ����˫������ص�Ҫ��
void CDBBTestView::InitialDBB()
{
	CRect rt;
	this->GetClientRect(&rt);

	// Ϊ��ĻDC�������ݵ��ڴ�DC
	if(!m_dcMemory.CreateCompatibleDC(NULL))				
	{														
		::PostQuitMessage(0);
	}	

	// ����λͼ
	m_Bmp.CreateCompatibleBitmap(&m_dcMemory, rt.Width(), rt.Height());

	// �൱��ѡ�񻭲�
	::SelectObject(m_dcMemory.GetSafeHdc(), m_Bmp);			
	
}

void CDBBTestView::OnTestNormal() 
{
	// ʹ����ͨ��ͼģʽ
	m_bUseDBB = FALSE;

	m_bStart = TRUE;
}

void CDBBTestView::OnTestDbb() 
{
	// ʹ��˫����ģʽ
	m_bUseDBB = TRUE;
	
	m_bStart = TRUE;

}
