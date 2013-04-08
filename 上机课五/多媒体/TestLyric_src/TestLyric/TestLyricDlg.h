// TestLyricDlg.h : ͷ�ļ�
//

#pragma once


#include "LiveWnd.h"
#include "colourpickerxp.h"
#include "afxwin.h"
#include <streams.h>
#include "DXGraph.h"
#include "afxcmn.h"

// CTestLyricDlg �Ի���
class CTestLyricDlg : public CDialog
{
// ����
public:
	CTestLyricDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTLYRIC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:

	CSliderCtrl	      m_TimeSlider;
   	CSliderCtrl       m_VolumeSlider;
    CLiveWnd          m_wndLyric; //�����ʾ����
	CColourPickerXP   m_TextColorNormal; 
	CColourPickerXP   m_TextHighlighted;
    int               m_iMainTime; //��ʲ��ŵ�ǰʱ��

	int     GetSongTotalTime(); //����ļ��ܲ��ų���(��λ: ms)
	int     GetCurrentTime(); //��õ�ǰ����λ�õ�ʱ��(��λ: ms)


	BOOL    CreateGraph(void);        // ����������Ƶ��Filter Graph
	void    DestroyGraph(void);       // ����Filter Graph

	BOOL    OpenLyricFile(LPCSTR szFilePath); //�򿪸���ļ�

// ʵ��
protected:
	HICON m_hIcon;
	
	CDXGraph *   m_FilterGraph;     // Filter Graph��װ
	CString      m_SourceFile;      // �ļ�·��
	UINT         m_SliderTimer;     // ��ʱ��ID

	LONGLONG     m_FileTimeinNanos; //�ļ�ʱ�䳤��(��λΪ100����, ����10^(-4) ms )


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	void  OnDropFiles(HDROP hDropInfo );
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSelectScrollMode();
   	afx_msg void OnButtonPlay();
	afx_msg void OnButtonPause();
	afx_msg void OnButtonStop();
	afx_msg void OnBnClickedAddFile();
	afx_msg LRESULT OnGraphNotify(WPARAM inWParam, LPARAM inLParam);
	afx_msg LRESULT OnPendingStopPlay(WPARAM wparam, LPARAM lparam);
	afx_msg void OnCheckFadeEffect();
};
