// FigureView.h : CFigureView ��Ľӿ�
//


#pragma once
#include "atlimage.h"
#include "atltypes.h"
#include "WinXPButtonST.h"

class CFigureView : public CScrollView
{
protected: // �������л�����
	CFigureView();
	DECLARE_DYNCREATE(CFigureView)

// ����
public:
	CFigureDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CFigureView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
	CImage m_imageFile;
	CRect m_rectShow;
	afx_msg void OnFileOpen();
	void MakeBlackWhiteImage(CImage& pImage, int iType);
	afx_msg void OnPsBw();
	afx_msg void OnPsCanny();
	
	afx_msg void OnBnClickedNoPs(void);
	CWinXPButtonST m_btnNoPS;
	CWinXPButtonST m_btnBW;
	CWinXPButtonST m_btnEdge;
	afx_msg void OnBnClickedBW(void);
	afx_msg void OnBnClickedEdge(void);
	void SoftImage(CImage& pImage);// �ữͼ��
	void SharpImage(CImage& pImage);//��ͼ��
	void BlurImage(CImage& pImage);//ģ��ͼ��

	void DiffuseImage(CImage& pImage);// ��
	inline COLORREF PointColor(int x, int y, CImage& pImage);
	inline void PointColor(int x, int y, COLORREF c, CImage& pImage);
	void BrightImage(CImage& pImage);
	void DarkImage(CImage& pImage);
	afx_msg void OnPsSoft();
	afx_msg void OnPsSharp();
	afx_msg void OnPsBlur();
	afx_msg void OnPsDiffuse();
	afx_msg void OnPsBright();
	afx_msg void OnPsDark();
	void OpposeImage(CImage& pImage);//��Ƭ������
	afx_msg void OnPsOppose();

	CWinXPButtonST m_btnSoft;
	CWinXPButtonST m_btnSharp;

	CWinXPButtonST m_btnBlur;
	CWinXPButtonST m_btnDiffuse;

	CWinXPButtonST m_btnBright;
	CWinXPButtonST m_btnDark;

	CWinXPButtonST m_btnOppose;

	afx_msg void OnBnClickedSoft(void);
	afx_msg void OnBnClickedSharp(void);
	afx_msg void OnBnClickedBlur(void);
	afx_msg void OnBnClickedDiffuse(void);
	afx_msg void OnBnClickedBright(void);
	afx_msg void OnBnClickedDark(void);
	afx_msg void OnBnClickedOppose(void);
//	afx_msg void OnFileSaveAs();
};

#ifndef _DEBUG  // FigureView.cpp �еĵ��԰汾
inline CFigureDoc* CFigureView::GetDocument() const
   { return reinterpret_cast<CFigureDoc*>(m_pDocument); }
#endif

