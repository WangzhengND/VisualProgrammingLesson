// FigureDoc.h : CFigureDoc ��Ľӿ�
//


#pragma once

class CFigureDoc : public CDocument
{
protected: // �������л�����
	CFigureDoc();
	DECLARE_DYNCREATE(CFigureDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CFigureDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};


