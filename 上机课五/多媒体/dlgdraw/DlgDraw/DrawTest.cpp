// DrawTest.cpp : implementation file
//

#include "stdafx.h"
#include "DlgDraw.h"
#include "DrawTest.h"
#include <time.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawTest dialog


CDrawTest::CDrawTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrawTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDrawTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawTest)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDrawTest, CDialog)
	//{{AFX_MSG_MAP(CDrawTest)
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawTest message handlers

BOOL CDrawTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Low = 0;
	m_High = 1024;
	m_now =0;
	SetTimer(1,100,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDrawTest::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CDrawTest::DrawWave(CDC *pDC)
{
	CRect rect;
	
	CString str;
	int i;
	int m_left,m_top,m_right,m_bottom;
	
    int m_Interval = (m_High - m_Low)/10;
	if (m_Interval < 1)  m_Interval = 1;
	
	// ��ȡ����������ı���
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	
	pWnd->GetClientRect(&rect);
	pDC->Rectangle(&rect);
	
	
    m_left = rect.left+10;
	m_top = rect.top+10;
	m_right = rect.right-10;
	m_bottom = rect.bottom-20;
	
	int m_IntervalPan = (m_right - m_left)/11;
	if (m_IntervalPan < 1 ) m_IntervalPan =1;
	
	// �������ʶ���
	CPen* pPenRed = new CPen;
	
	// ��ɫ����
	pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));
	
	// �������ʶ���
	CPen* pPenBlue = new CPen;
	
	// ��ɫ����
	pPenBlue->CreatePen(PS_SOLID,1,RGB(0,0, 255));
	
	// �������ʶ���
	CPen* pPenGreen = new CPen;
	
	// ��ɫ����
	pPenGreen->CreatePen(PS_DOT,1,RGB(0,255,0));
	
	// ѡ�е�ǰ��ɫ���ʣ���������ǰ�Ļ���
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	
	// ����������
	pDC->MoveTo(m_left,m_top);
	
	// ��ֱ��
	pDC->LineTo(m_left,m_bottom);
	
	// ˮƽ��
	pDC->LineTo(m_right,m_bottom);
	
	
	// дX��̶�ֵ
	for(i=0;i<10;i++)
	{
		//str.Format(_T("%d"),m_Min+i*m_Interval);
		str.Format(_T("%d"),m_Low+i*m_Interval);
		pDC->TextOut(m_left+i*m_IntervalPan,m_bottom+3,str);		
	}
	//str.Format(_T("%d"),m_Max);
	str.Format(_T("%d"),m_High);
	pDC->TextOut(m_left+10*m_IntervalPan,m_bottom+3,str);		
	
	
	// ����X��̶�
	for (i = m_left; i < m_right-20; i += 5)
	{
		if ((i & 1) == 0)
		{
			// 10�ı���
			pDC->MoveTo(i + 10, m_bottom);
			pDC->LineTo(i + 10, m_bottom+4);
		}
		else
		{
			// 10�ı���
			pDC->MoveTo(i + 10, m_bottom);
			pDC->LineTo(i + 10, m_bottom+2);
		}
	}
	
	// ����Y���ͷ
	pDC->MoveTo(m_right-5,m_bottom-5);
	pDC->LineTo(m_right,m_bottom);
	pDC->LineTo(m_right-5,m_bottom+5);
	
	// ����X���ͷ	
	pDC->MoveTo(m_left-5,m_top+5);
	pDC->LineTo(m_left,m_top);
	pDC->LineTo(m_left+5,m_top+5);
	

	
	// ����Y������ ѡ����ɫ����
    pDC->SelectObject(pPenGreen);	
    //
	int iTemp = (m_bottom  - m_top)/5;
    for (i = 1 ;i <= 5 ;i++)
	{
		pDC->MoveTo(m_left,m_bottom - i*iTemp);
		pDC->LineTo(m_right,m_bottom - i*iTemp);
	}

    //���鸳ֵ
	if(m_now<1024)
	{
	    m_now++;
	}
	else
	{
		m_now = 0;
	}
	for(i = m_Low;i<m_High;i++)
	{ 
		//m_lCount[i]=(rand()%10+rand()%100+rand()%1000)%1024;
        m_lCount[i] = (int)(sin(i-m_now)*204); 
	}
	int xTemp;
	int yTemp;
	// ���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);
	for (i = m_Low; i <= m_High; i=i+3)
	{		
		xTemp = m_left+(i-m_Low)*m_IntervalPan/m_Interval;
		yTemp = m_bottom/2 - (int) (m_lCount[i] * m_bottom / 1024);
		if (yTemp < m_top) yTemp = m_top;
		if((xTemp >=m_left)&&(xTemp <=m_right))
		{
			pDC->MoveTo(xTemp, m_bottom/2);
			pDC->LineTo(xTemp, yTemp);
		}
	}
	// �ָ���ǰ�Ļ���
	pDC->SelectObject(pOldPen);	
	
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;
	return;
}

void CDrawTest::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	
	// ��ȡ����������ı���
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	
	pWnd->GetClientRect(&rect);
	// ָ��
	pDC = pWnd->GetDC();	
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	
	//pDC->Rectangle(&rect);

	
    //�ڴ��ͼ
    CBitmap memBitmap;
	CBitmap* pOldBmp = NULL;
	memDC.CreateCompatibleDC(pDC);
	memBitmap.CreateCompatibleBitmap(pDC,rect.right,rect.bottom);
	pOldBmp = memDC.SelectObject(&memBitmap);
	memDC.BitBlt(rect.left,rect.top,rect.right,rect.bottom,pDC,0,0,SRCCOPY);
	DrawWave(&memDC);
	pDC->BitBlt(rect.left,rect.top,rect.right,rect.bottom,&memDC,0,0,SRCCOPY);

	memDC.SelectObject(pOldBmp);
	memDC.DeleteDC();
	memBitmap.DeleteObject();

	CDialog::OnTimer(nIDEvent);
}
