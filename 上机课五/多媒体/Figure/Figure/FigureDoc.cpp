// FigureDoc.cpp : CFigureDoc ���ʵ��
//

#include "stdafx.h"
#include "Figure.h"

#include "FigureDoc.h"
#include "MainFrm.h "
#include "FigureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFigureDoc

IMPLEMENT_DYNCREATE(CFigureDoc, CDocument)

BEGIN_MESSAGE_MAP(CFigureDoc, CDocument)
END_MESSAGE_MAP()


// CFigureDoc ����/����

CFigureDoc::CFigureDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CFigureDoc::~CFigureDoc()
{
}

BOOL CFigureDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CFigureDoc ���л�

void CFigureDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CFigureDoc ���

#ifdef _DEBUG
void CFigureDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFigureDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFigureDoc ����

BOOL CFigureDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �ڴ����ר�ô����/����û���
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd; 
	CFigureView *pView = (CFigureView *)pMain->GetActiveView();
	pView->m_imageFile.Save(lpszPathName);
	return TRUE;
}
