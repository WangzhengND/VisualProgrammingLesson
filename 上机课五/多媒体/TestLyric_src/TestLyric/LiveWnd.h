#pragma once

#include <vector>

using namespace std;

typedef struct tagTime{
  int     lineNum;
  float   timeValue;
  int     dd;//�������(����ˮƽ����ģʽ)
}TIMETAG;

float StrToSS(LPCSTR lpszTag);
int   CompareTime(TIMETAG& tag1, TIMETAG& tag2);
// CLiveWnd

#define   WM_NOTIFY_LYRIC   WM_USER + 1265

class CLiveWnd : public CWnd
{
	DECLARE_DYNAMIC(CLiveWnd)

public:
	CLiveWnd();
	virtual ~CLiveWnd();


public: 

	BOOL    Create(CWnd* parent);
	BOOL    Initialize(); //����GDI��Դ
	void    Cleanup();  //�ͷ�GDI��Դ
	BOOL    TextToScreen( void ); //����ʵ�������
	BOOL    Start();//������ʱ��
	void    Stop(); //ֹͣ��ʱ��
	void    ClearLyrics(); //����������
    void    ResetParam();
	void    UpdateDC(); //���ڴ�С�ı�ʱ�ؽ���ص�GDI��Դ

    inline  int     GetLineCount(); //������и�ʵ������������ظ����ģ�
	inline  float   GetTimeValue(int lineNumber); //���ĳ�и�ʵ�ʱ���ǩ

	void     SetFadeIn(BOOL flag) { m_bFadeEffect = flag; }
    
    
	int     GetX(int); //���ĳ�и����Դ������Ͻǵĺ�����
	int     GetY(int); //���ĳ�и����Դ������Ͻǵ�������
	int     GetPlayPos(); //��ȡ��ǰ���ŵ�ʱ���
	int     GetHorzLen(int Index); //���ĳ�и����ʾ�ĺ�����
	int     GetHorzTextW(int Index); //���ĳ�и�ʵ���ʾ���
	void    SetHorzData(); //����ˮƽ����ģʽ��ÿ������ʾ�������еĺ�����
	void    Sort(); //�����и�ʰ�ʱ���ǩ����
    void    DrawHighlightedLine(int); //��������һ��
	void    AddTimeTag(LPCSTR lpszTag, int lineNumber); //���һ���µ�ʱ���ǩ������
    void    AddWord(LPCSTR lpszWord); //����µ�һ���ʵ�������
	void    SetHorzionalMode(); //ˮƽ����ģʽ
	void    SetVerticalMode(); //��ֱ����ģʽ
    void    SetTextStateColor(COLORREF clrNormal, COLORREF clrHighlighted); //���ø�����屳���͸�����ɫ
	void    Forwards(int millisecond);//ǰ��
	void    Backwards(int millisecond);//����
    BOOL    ReadFile(LPCSTR lpszFile); //��ȡ����ļ�(.lrc)
	BOOL    SpliceLine(LPCSTR line, int lineNumber); //��������ļ���һ��
	LPCSTR  GetString(int number); //��ȡĳһ�и��

	std::vector<TIMETAG> m_vTimeTags; //��ʲ��ŵ�ʱ���ǩ
	std::vector<CString> m_vWords; //�洢ÿ����


private: 

private: 
	CWnd*    m_pParent;
	HDC      m_dcMemoryDC;
	HDC      m_dcWinDC;
	int      m_iDrawHeight;
	int      m_iDrawWidth;
	int      m_iDrawX;
	int      m_iDrawY;

	int      m_nTextHeight;
	int      m_nTextSpace;

    int      m_iTextOutX;
	int      m_iTextOutY;

	int      m_iTimeInterval;
	int      m_iCurrent;
	int      m_iStartedPos;
    int      m_iScrollTotal;
	int      m_iMouseWheelTotal;
    int      m_iTime;

	 HWND    m_hWindow;
	CRect    m_rectangle;
	HBITMAP  m_hMemoryBitmap;
	HBRUSH   m_hBrushBackground;
	HFONT    m_hFont;
	COLORREF m_clrForeground;
	COLORREF m_clrBackground;
    COLORREF m_clrTextHighlighted;
	BOOL     m_bVertical; 

	BOOL     m_bFadeEffect; //�Ƿ��뵭��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent); //��ʱ������
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt ); //������������Ϣ
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);  //��������Ϣ
};


