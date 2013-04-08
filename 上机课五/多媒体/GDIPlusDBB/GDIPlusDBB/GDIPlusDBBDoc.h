// GDIPlusDBBDoc.h : interface of the CGDIPlusDBBDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDIPLUSDBBDOC_H__7D30EA2D_A1E7_44F3_805F_8847187321EA__INCLUDED_)
#define AFX_GDIPLUSDBBDOC_H__7D30EA2D_A1E7_44F3_805F_8847187321EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGDIPlusDBBDoc : public CDocument
{
protected: // create from serialization only
	CGDIPlusDBBDoc();
	DECLARE_DYNCREATE(CGDIPlusDBBDoc)

// Attributes
public:
	CString m_pStrMapName;							// ��ͼ��
	CString m_pStrMapPath;							// ��ͼ·��
	int m_nMapWidth;								// ��ͼ���
	int m_nMapHeight;								// ��ͼ�߶�

// Operations
public:
	CString GetEXEPath();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGDIPlusDBBDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGDIPlusDBBDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGDIPlusDBBDoc)
	afx_msg void OnMap1();
	afx_msg void OnMap2();
	afx_msg void OnMap3();
	afx_msg void OnFileNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GDIPLUSDBBDOC_H__7D30EA2D_A1E7_44F3_805F_8847187321EA__INCLUDED_)
