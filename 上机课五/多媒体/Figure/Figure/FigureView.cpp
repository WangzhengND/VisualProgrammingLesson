// FigureView.cpp : CFigureView ���ʵ��
//

#include "stdafx.h"
#include "Figure.h"

#include "FigureDoc.h"
#include "FigureView.h"
#include "GlobalApi.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFigureView

IMPLEMENT_DYNCREATE(CFigureView, CScrollView)

BEGIN_MESSAGE_MAP(CFigureView, CScrollView)
	ON_COMMAND(ID_FILE_OPEN, &CFigureView::OnFileOpen)
	ON_COMMAND(ID_PS_BW, &CFigureView::OnPsBw)
	ON_COMMAND(ID_PS_CANNY, &CFigureView::OnPsCanny)
	ON_BN_CLICKED(IDC_NOPS, &CFigureView::OnBnClickedNoPs)
	ON_BN_CLICKED(IDC_BW, &CFigureView::OnBnClickedBW)
	ON_BN_CLICKED(IDC_EDGE, &CFigureView::OnBnClickedEdge)
	ON_COMMAND(ID_PS_SOFT, &CFigureView::OnPsSoft)
	ON_COMMAND(ID_PS_SHARP, &CFigureView::OnPsSharp)
	ON_COMMAND(ID_PS_BLUR, &CFigureView::OnPsBlur)
	ON_COMMAND(ID_PS_DIFFUSE, &CFigureView::OnPsDiffuse)
	ON_COMMAND(ID_PS_BRIGHT, &CFigureView::OnPsBright)
	ON_COMMAND(ID_PS_DARK, &CFigureView::OnPsDark)
	ON_COMMAND(ID_PS_OPPOSE, &CFigureView::OnPsOppose)
	ON_BN_CLICKED(IDC_SOFT, &CFigureView::OnBnClickedSoft)
	ON_BN_CLICKED(IDC_SHARP, &CFigureView::OnBnClickedSharp)
	ON_BN_CLICKED(IDC_BLUR, &CFigureView::OnBnClickedBlur)
	ON_BN_CLICKED(IDC_DIFFUSE, &CFigureView::OnBnClickedDiffuse)
	ON_BN_CLICKED(IDC_BRIGHT, &CFigureView::OnBnClickedBright)
	ON_BN_CLICKED(IDC_DARK, &CFigureView::OnBnClickedDark)
	ON_BN_CLICKED(IDC_OPPOSE, &CFigureView::OnBnClickedOppose)
//	ON_COMMAND(ID_FILE_SAVE_AS, &CFigureView::OnFileSaveAs)
END_MESSAGE_MAP()

// CFigureView ����/����

CFigureView::CFigureView()
{
	// TODO: �ڴ˴���ӹ������

}

CFigureView::~CFigureView()
{
}

BOOL CFigureView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CFigureView ����

void CFigureView::OnDraw(CDC* pDC)
{
	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CBrush BackBrush;
	BackBrush.CreateSolidBrush(RGB(255,255,255));
	CBrush* pOldBrush = pDC->SelectObject(&BackBrush);
	pDC->Rectangle(CRect(-1,-1,3000,3000));
	pDC->SelectObject(pOldBrush);
	if (!m_imageFile.IsNull()){
		m_imageFile.StretchBlt(pDC->m_hDC,CRect(&m_rectShow),SRCCOPY);
	}
}

void CFigureView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	CMainFrame* pFrame = (CMainFrame*)::AfxGetMainWnd();
	HWND hWnd = pFrame->m_wndDlgBar.GetSafeHwnd();

	CWnd* pWnd = CWnd::FromHandle(hWnd);

	m_btnNoPS.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		CRect(2,2,40,40), pWnd, IDC_NOPS);
	// CWinXPButtonST button
	m_btnNoPS.SetIcon(IDI_NOPS);
	m_btnNoPS.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnNoPS.SetRounded(TRUE);
	m_btnNoPS.SetTooltipText("���ļ�");

	m_btnBW.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		CRect(60,2,100,40), pWnd, IDC_BW);
	m_btnBW.SetIcon(IDI_BW);
	m_btnBW.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnBW.SetRounded(TRUE);
	m_btnBW.SetTooltipText("��ͼ��ת��Ϊ�ڰ�");

	m_btnEdge.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		CRect(100,2,140,40), pWnd, IDC_EDGE);
	m_btnEdge.SetIcon(IDI_EDGE);
	m_btnEdge.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnEdge.SetRounded(TRUE);
	m_btnEdge.SetTooltipText("Canny����ȡ��Ե");

	m_btnSoft.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		CRect(158,2,198,40), pWnd, IDC_SOFT);
	m_btnSoft.SetIcon(IDI_SOFT);
	m_btnSoft.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnSoft.SetRounded(TRUE);
	m_btnSoft.SetTooltipText("�ữ");

	m_btnSharp.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		CRect(198,2,238,40), pWnd, IDC_SHARP);
	m_btnSharp.SetIcon(IDI_SHARP);
	m_btnSharp.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnSharp.SetRounded(TRUE);
	m_btnSharp.SetTooltipText("��");

	m_btnBlur.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		CRect(256,2,296,40), pWnd, IDC_BLUR);
	m_btnBlur.SetIcon(IDI_BLUR);
	m_btnBlur.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnBlur.SetRounded(TRUE);
	m_btnBlur.SetTooltipText("ģ��");

	m_btnDiffuse.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		CRect(296,2,336,40), pWnd, IDC_DIFFUSE);
	m_btnDiffuse.SetIcon(IDI_DIFFUSE);
	m_btnDiffuse.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnDiffuse.SetRounded(TRUE);
	m_btnDiffuse.SetTooltipText("��");

	m_btnBright.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		CRect(354,2,394,40), pWnd, IDC_BRIGHT);
	m_btnBright.SetIcon(IDI_BRIGHT);
	m_btnBright.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnBright.SetRounded(TRUE);
	m_btnBright.SetTooltipText("����");

	m_btnDark.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		CRect(394,2,434,40), pWnd, IDC_DARK);
	m_btnDark.SetIcon(IDI_DARK);
	m_btnDark.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnDark.SetRounded(TRUE);
	m_btnDark.SetTooltipText("����");

	m_btnOppose.Create(_T(""), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
		CRect(452,2,492,40), pWnd, IDC_OPPOSE);
	m_btnOppose.SetIcon(IDI_OPPOSE);
	m_btnOppose.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btnOppose.SetRounded(TRUE);
	m_btnOppose.SetTooltipText("��Ƭ��");

}


// CFigureView ���

#ifdef _DEBUG
void CFigureView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CFigureView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CFigureDoc* CFigureView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFigureDoc)));
	return (CFigureDoc*)m_pDocument;
}
#endif //_DEBUG


// CFigureView ��Ϣ�������

void CFigureView::OnFileOpen()
{
	// TODO: �ڴ���������������
	CString strFilter;
	CString strImageFileName;
	CSimpleArray<GUID> aguidFileTypes;
	HRESULT hResult;
	hResult = m_imageFile.GetExporterFilterString(strFilter,aguidFileTypes);
	if(FAILED(hResult))
	{
		MessageBox("װ���ļ����͹���������ʧ��","��Ϣ��ʾ",MB_OK);
		return;
	}
	strFilter = "All File(*.*)|*.*|"+strFilter;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,strFilter);
	hResult = (int)dlg.DoModal();
	if(hResult != IDOK) 
		return;
	strImageFileName.Format(dlg.GetFileName());
	m_imageFile.Destroy();
	hResult = m_imageFile.Load(strImageFileName);
	if(FAILED(hResult))
	{
		MessageBox("װ��ͼ���ļ�����ʧ��","��Ϣ��ʾ",MB_OK);
		return;
	}
	m_rectShow = CRect(0,0,m_imageFile.GetWidth(),m_imageFile.GetHeight());
	SetScrollSizes(MM_TEXT,CSize(m_rectShow.Width(),m_rectShow.Height()));
	CWnd* pWnd=AfxGetMainWnd();
	pWnd->SetWindowTextA("��ǰ���ڴ򿪵��ļ�����Ϊ:"+strImageFileName);
	Invalidate();
}

void CFigureView::MakeBlackWhiteImage(CImage& pImage, int iType)
{
	CWaitCursor WaitCursor;
	int Height = pImage.GetHeight();
	int Width = pImage.GetWidth();
	if(!pImage.IsIndexed())
	{
		for(int x=0; x<Width; x++){
			for(int y=0; y<Height;y++)
			{
				COLORREF pixel=pImage.GetPixel(x,y);
				byte r,g,b,Result;
				r = GetRValue(pixel);
				g = GetGValue(pixel);
				b = GetBValue(pixel);
				switch(iType)
				{
				case 0:
					Result = ((r+g+b)/3);
					break;
				case 1:
					Result = max(max(r,g),b);
					break;
				case 2:
					Result = (2.7*r+0.2*g+0.1*b);
					break;
				}
				pImage.SetPixel(x,y,RGB(Result,Result,Result));
			}
		}
	}
	else
	{
		int MaxColors = pImage.GetMaxColorTableEntries();
		RGBQUAD* ColorTable = new RGBQUAD[MaxColors];
		pImage.GetColorTable(0,MaxColors,ColorTable);
		for(int i=0;i<MaxColors;i++)
		{
			byte r,g,b,Result;
			r = ColorTable[i].rgbRed;
			g = ColorTable[i].rgbGreen;
			b = ColorTable[i].rgbBlue;
			switch(iType)
			{
			case 0:
				Result = ((r+g+b)/3);
				break;
			case 1:
				Result = max(max(r,g),b);
				break;
			case 2:
				Result = (2.7*r+0.2*g+0.1*b);
				break;
			}
			ColorTable[i].rgbRed = Result;
			ColorTable[i].rgbGreen = Result;
			ColorTable[i].rgbBlue = Result;
		}
		pImage.SetColorTable(0,MaxColors,ColorTable);
		delete ColorTable;
	}
}

void CFigureView::OnPsBw()
{
	// TODO: �ڴ���������������
	MakeBlackWhiteImage(m_imageFile,0);

	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CFigureView::OnPsCanny()
{
	// TODO: �ڴ���������������
	CWaitCursor WaitCursor;

	int nWidth = m_imageFile.GetWidth();
	int nHeight= m_imageFile.GetHeight();

	// �����ڴ棬�洢ͼ������
	unsigned char * pUnchImage = new unsigned char[nWidth*nHeight];
	// ��ͼ�����ݱ����ھ�����
	for(int y = 0;y<nHeight;y++)
	{
		for(int x = 0;x<nWidth;x++)
		{
			COLORREF pixel=m_imageFile.GetPixel(x,y);
			byte r,g,b;
			r = GetRValue(pixel);
			g = GetGValue(pixel);
			b = GetBValue(pixel);
			pUnchImage[y*nWidth+x] = 255<<24 | r<<16| g<<8|b;
		}
	}

	// canny���Ӽ����Ľ��
	unsigned char * pUnchEdge = new unsigned char[nWidth*nHeight];

	// ����canny�������б߽���ȡ
	Canny(pUnchImage, nWidth, nHeight, 0.4, 0.4, 0.79, pUnchEdge) ;

	//���������ͼ��ת��Ϊ����
	for(int y=0; y<nHeight; y++)
	{
		for(int x=0; x<nWidth; x++)
		{
			byte r,g,b,Result;
			r = (0x000000ff&pUnchEdge[y*nWidth+x]>>16)?0:255;
			g = (0x000000ff&pUnchEdge[y*nWidth+x]>>8)?0:255;
			b = (0x000000ff&pUnchEdge[y*nWidth+x])?0:255;
			Result = ((r+g+b)/3);
			m_imageFile.SetPixelRGB(x,y,Result,Result,Result);
		}
	}

	MakeBlackWhiteImage(m_imageFile,0);

	delete []pUnchImage;
	pUnchImage = NULL  ;
	delete []pUnchEdge ;
	pUnchEdge = NULL   ;

	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CFigureView::OnBnClickedNoPs(void)
{
	OnFileOpen();
}

void CFigureView::OnBnClickedBW(void)
{
	OnPsBw();
}

void CFigureView::OnBnClickedEdge(void)
{
	OnPsCanny();
}

void CFigureView::SoftImage(CImage& pImage)
{
	CWaitCursor WaitCursor;
	int height = pImage.GetHeight();
	int width = pImage.GetWidth();
	int Gauss[9]={1,2,1,2,4,2,1,2,1};
	for(int x=1;x<width-1;x++)
	{
		for(int y=1;y<height-1;y++)
		{
			int r=0,g=0,b=0;
			int index=0;
			for(int col=-1;col<=1;col++)
				for(int row=-1;row<=1;row++)
				{
					COLORREF pixel=pImage.GetPixel(x+row,y+col);
					r+=GetRValue(pixel)*Gauss[index];
					g+=GetGValue(pixel)*Gauss[index];
					b+=GetBValue(pixel)*Gauss[index];
					index++;
				}
				r/=16;
				g/=16;
				b/=16;
				r=r>255?255:r;
				r=r<0?0:r;
				g=g>255?255:g;
				g=g<0?0:g;
				b=b>255?255:b;
				b=b<0?0:b;
				pImage.SetPixelRGB(x-1,y-1,r,g,b);
		}
	}
}

void CFigureView::SharpImage(CImage& pImage)
{
	CWaitCursor WaitCursor;
	int height=pImage.GetHeight();
	int width=pImage.GetWidth();
	int Laplacian[9]={-1,-1,-1,-1,9,-1,-1,-1,-1};
	for(int x=1;x<width-1;x++)
	{
		for(int y=1;y<height-1;y++)
		{
			int r=0,g=0,b=0;
			int index=0;
			for(int col=-1;col<=1;col++)
				for(int row=-1;row<=1;row++)
				{
					COLORREF pixel=pImage.GetPixel(x+row,y+col);
					r+=GetRValue(pixel)*Laplacian[index];
					g+=GetGValue(pixel)*Laplacian[index];
					b+=GetBValue(pixel)*Laplacian[index];
					index++;
				}
				r=r>255?255:r;
				r=r<0?0:r;
				g=g>255?255:g;
				g=g<0?0:g;
				b=b>255?255:b;
				b=b<0?0:b;
				pImage.SetPixelRGB(x-1,y-1,r,g,b);
		}
	}
}

void CFigureView::BlurImage(CImage& pImage)
{
	CWaitCursor WaitCursor;
	int height = pImage.GetHeight();
	int width = pImage.GetWidth();
	COLORREF cLeft = 0;
	COLORREF cCur = PointColor(0,0,pImage);
	COLORREF cRight, cUp, cDown;
	BYTE r,g,b;
	for(int i=2; i<height-2; i++)
	{
		cLeft=0;
		for(int j=2; j<width-2; j++)
		{
			cRight = PointColor(j+1,i,pImage);
			cUp = PointColor(j, i-1 ,pImage);
			cDown = PointColor(j,i+1,pImage);
			r=(BYTE)(((int)(GetRValue(cCur)<<2)+GetRValue(cLeft)+GetRValue(cRight)
				+GetRValue(cUp)+GetRValue(cDown))>>3);
			g=(BYTE)(((int)(GetGValue(cCur)<<2)+GetGValue(cLeft)+GetGValue(cRight)
				+GetGValue(cUp)+GetGValue(cDown))>>3);
			b=(BYTE)(((int)(GetBValue(cCur)<<2)+GetBValue(cLeft)+GetBValue(cRight)
				+GetBValue(cUp)+GetBValue(cDown))>>3);
			PointColor(j,i,RGB(r,g,b),pImage);
			cLeft = cCur;
			cCur = cRight;
		}
	}
}

void CFigureView::DiffuseImage(CImage& pImage)
{
	CWaitCursor WaitCursor;
	int height = pImage.GetHeight();
	int width = pImage.GetWidth();
	for(int x=1;x<width;x++)
	{
		for(int y=1;y<height;y++)
		{
			COLORREF pixel;
			double f=RAND_MAX;
			int k=(int)(24*(rand())/f);
			int dx=x+k%15;
			int dy=y+k%15;
			if(dx>=width)dx=width-1;
			if(dy>=height)dy=height-1;
			pixel=pImage.GetPixel(dx,dy);
			pImage.SetPixel(x,y,pixel);
		}
	}
}

inline COLORREF CFigureView::PointColor(int x, int y, CImage& pImage)
{
	return (*(COLORREF*)(pImage.GetPixelAddress(x,y+1)));
}

inline void CFigureView::PointColor(int x, int y, COLORREF c, CImage& pImage)
{
	BYTE* p = (BYTE*)pImage.GetPixelAddress(x,y+1);
	*p++ = GetRValue(c);
	*p++ = GetGValue(c);
	*p = GetBValue(c);
}

void CFigureView::BrightImage(CImage& pImage)
{
	CWaitCursor WaitCursor;
	int width = pImage.GetWidth();
	int height = pImage.GetHeight();
	for(int x=1;x<width-1;x++)
	{
		for(int y=1;y<height-1;y++)
		{
			COLORREF pixel = PointColor(x,y,pImage);
			byte r,g,b;
			r=GetRValue(pixel);
			g=GetGValue(pixel);
			b=GetBValue(pixel);
			r=(r*3+255)/4;
			g=(g*3+255)/4;
			b=(b*3+255)/4;
			r=r>255?255:r;
			g=g>255?255:g;
			b=b>255?255:b;
			PointColor(x,y,RGB(r,g,b),pImage);
		}
	}
}

void CFigureView::DarkImage(CImage& pImage)
{
	CWaitCursor WaitCursor;
	int width = pImage.GetWidth();
	int height = pImage.GetHeight();
	for(int x=0;x<width;x++)
	{
		for(int y=0;y<height;y++)
		{
			COLORREF pixel=pImage.GetPixel(x,y);
			byte r,g,b;
			r=GetRValue(pixel);
			g=GetGValue(pixel);
			b=GetBValue(pixel);
			pImage.SetPixelRGB(x,y,r*0.8,g*0.8,b*0.8);
		}
	}
}

void CFigureView::OnPsSoft()
{
	// TODO: �ڴ���������������
	SoftImage(m_imageFile);

	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CFigureView::OnPsSharp()
{
	// TODO: �ڴ���������������
	SharpImage(m_imageFile);

	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CFigureView::OnPsBlur()
{
	// TODO: �ڴ���������������
	BlurImage(m_imageFile);

	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CFigureView::OnPsDiffuse()
{
	// TODO: �ڴ���������������
	DiffuseImage(m_imageFile);

	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CFigureView::OnPsBright()
{
	// TODO: �ڴ���������������
	BrightImage(m_imageFile);

	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CFigureView::OnPsDark()
{
	// TODO: �ڴ���������������
	DarkImage(m_imageFile);

	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CFigureView::OpposeImage(CImage& pImage)
{
	CWaitCursor WaitCursor;
	int height = m_imageFile.GetHeight();
	int width = m_imageFile.GetWidth();
	for(int x=0;x<width;x++)
	{
		for(int y=0;y<height;y++)
		{
			COLORREF pixel=m_imageFile.GetPixel(x,y);
			byte r,g,b;
			r=GetRValue(pixel);
			g=GetGValue(pixel);
			b=GetBValue(pixel);
			m_imageFile.SetPixelRGB(x,y,255-r,255-g,255-b);
		}
	}
}

void CFigureView::OnPsOppose()
{
	// TODO: �ڴ���������������
	OpposeImage(m_imageFile);

	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->SetModifiedFlag(TRUE);
	Invalidate();
}

void CFigureView::OnBnClickedSoft(void)
{
	OnPsSoft();
}

void CFigureView::OnBnClickedSharp(void)
{
	OnPsSharp();
}

void CFigureView::OnBnClickedBlur(void)
{
	OnPsBlur();
}

void CFigureView::OnBnClickedDiffuse(void)
{
	OnPsDiffuse();
}

void CFigureView::OnBnClickedBright(void)
{
	OnPsBright();
}

void CFigureView::OnBnClickedDark(void)
{
	OnPsDark();
}

void CFigureView::OnBnClickedOppose(void)
{
	OnPsOppose();
}