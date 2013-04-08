// TestLyricDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestLyric.h"
#include "TestLyricDlg.h"
#include ".\testlyricdlg.h"

#define SLIDER_TIMER  11

#define MILLISECS_DIVIDE 10000L

const int MINIMUM_VOLUME=3000;

#define  WM_PENDING_STOP_PLAY  WM_USER+522


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestLyricDlg �Ի���

CTestLyricDlg::CTestLyricDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestLyricDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iMainTime = 0;
	m_FilterGraph = NULL;
	m_SliderTimer = 0;
	m_FileTimeinNanos = 0;//�ļ�������ʱ��
}

void CTestLyricDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_TextColorNormal);
	DDX_Control(pDX, IDC_BUTTON3, m_TextHighlighted);
	DDX_Control(pDX, IDC_TIME_SLIDER, m_TimeSlider);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_VolumeSlider);
}

BEGIN_MESSAGE_MAP(CTestLyricDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_DROPFILES() //�����ļ��Ϸ���Ϣ
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_CBN_SELENDOK (IDC_COMBO_SCROLLMODE, OnSelectScrollMode)
	ON_BN_CLICKED(IDC_ADD_FILE, OnBnClickedAddFile)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_MESSAGE(WM_GRAPHNOTIFY, OnGraphNotify)
	ON_MESSAGE(WM_PENDING_STOP_PLAY, OnPendingStopPlay)
	//}}AFX_MSG_MAP
	
	ON_BN_CLICKED(IDC_CHECK1, OnCheckFadeEffect)
END_MESSAGE_MAP()


// CTestLyricDlg ��Ϣ�������

BOOL CTestLyricDlg::OnInitDialog()
{

  	CDialog::OnInitDialog();

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CRect rc;
	GetWindowRect(&rc);
	 

	m_TimeSlider.SetRange(0, 1000);
	m_TimeSlider.SetPos(0);

	m_VolumeSlider.SetRange(0, MINIMUM_VOLUME, TRUE);

	DragAcceptFiles(TRUE); //�����ļ��Ϸ�
    
	 BOOL ret = m_wndLyric.Create(this);
	 m_wndLyric.MoveWindow(200, 200, rc.Width(), 300);
	 m_wndLyric.ShowWindow(1);

	((CComboBox*)GetDlgItem(IDC_COMBO_AUDIO_FILE))->SetCurSel(0);

    ((CComboBox*)GetDlgItem(IDC_COMBO_SCROLLMODE))->AddString("��ֱ");
    ((CComboBox*)GetDlgItem(IDC_COMBO_SCROLLMODE))->AddString("ˮƽ");
	((CComboBox*)GetDlgItem(IDC_COMBO_SCROLLMODE))->SetCurSel(0);

	m_TextColorNormal.SetColor( RGB(125,158,192));
	m_TextHighlighted.SetColor( RGB(255,255,0) );

	return TRUE;  
}

void CTestLyricDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


void CTestLyricDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CTestLyricDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestLyricDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}


void CTestLyricDlg::OnSelectScrollMode()
{
  int nSel =  ((CComboBox*)GetDlgItem(IDC_COMBO_SCROLLMODE))->GetCurSel();
  if(nSel==0)//vertical
	  m_wndLyric.SetVerticalMode();
  else//horzional 
	  m_wndLyric.SetHorzionalMode();
 
}



BOOL CTestLyricDlg::OpenLyricFile(LPCSTR szFilePath)
{
  m_wndLyric.SetTextStateColor(m_TextColorNormal.GetColor(), m_TextHighlighted.GetColor());
  m_iMainTime = 0;

  BOOL bSuccess = FALSE;

  	WIN32_FIND_DATA fd;
	CString szPath = szFilePath;

	HANDLE hFind=FindFirstFile(szPath,&fd);


	if( hFind!=INVALID_HANDLE_VALUE )
	{
		if( szPath.Right(4) == ".lrc")
		{
		   bSuccess = TRUE;
		}	
	}
	
	if(hFind!=INVALID_HANDLE_VALUE)
		FindClose(hFind);

  if(bSuccess)
  { 
	 //��ȡ����ļ�����
	m_wndLyric.ReadFile(szPath);

  }
   
  return bSuccess;
}

//�Ϸ��ļ���Ϣ��Ӧ
void CTestLyricDlg::OnDropFiles(HDROP hDropInfo )
{
	unsigned int cFile = 0, i = 0;
	CHAR szFileNname[MAX_PATH] = {'\0'};
	cFile = ::DragQueryFile( hDropInfo, 0xFFFFFFFF, NULL, MAX_PATH );
	for(i = 0; i < cFile; i++)
	{
		DWORD fileAttrib = 0x0;
		::DragQueryFile( hDropInfo, i, szFileNname, MAX_PATH );
		fileAttrib = GetFileAttributes(szFileNname);
		if (0x10 == (fileAttrib & FILE_ATTRIBUTE_DIRECTORY))
		{  // folder


		}
		else
		{   //file
			CString strFileType;
			CString strFilePath = szFileNname;
			strFilePath.MakeLower();
			strFileType = strFilePath.Mid(strFilePath.ReverseFind('.'));
			if(strFileType.Find(".wma")!=-1
				||strFileType.Find(".mp3")!=-1 
				|| strFileType.Find(".wav")!= -1)
			{
						
				  m_SourceFile = strFilePath;
		
				  //��ComboBox��Ӹ����ļ�·������ѡ��ø���
			      int index = ((CComboBox*)GetDlgItem(IDC_COMBO_AUDIO_FILE))->AddString(m_SourceFile);
		          ((CComboBox*)GetDlgItem(IDC_COMBO_AUDIO_FILE))->SetCurSel(index);

			}
			else
			{

				::MessageBox(NULL,_T("��֧�ָ��ļ���ʽ����"),_T("��ʾ"),MB_OK|MB_ICONINFORMATION);
			}
		}
	}
}

//��Combo����Ӹ����ļ�·���������µ�ǰ�ļ�·��m_SourceFileΪ���²������
void CTestLyricDlg::OnBnClickedAddFile()
{
	CString    strFilter = "";
	strFilter += "Audio File (*.mp3;*.wma;*.wav)|*.mp3;*.wma;*.wav|";
	strFilter += "All Files (*.*)|*.*|";

	CFileDialog dlgOpen(TRUE, NULL, NULL, OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, strFilter, this);
	if (IDOK == dlgOpen.DoModal()) 
	{
		m_SourceFile = dlgOpen.GetPathName();

		  //��ComboBox��Ӹ����ļ�·������ѡ��ø���
		int index = ((CComboBox*)GetDlgItem(IDC_COMBO_AUDIO_FILE))->AddString(m_SourceFile);
		((CComboBox*)GetDlgItem(IDC_COMBO_AUDIO_FILE))->SetCurSel(index);
	}
}


void CTestLyricDlg::OnButtonPlay() 
{
	if(m_FilterGraph == NULL)
	{
	
		//��ȡ�����ļ�·��
		CString szFileName;
		((CComboBox*)GetDlgItem(IDC_COMBO_AUDIO_FILE))->GetWindowText(szFileName);

			
		m_SourceFile = szFileName;

		if(m_SourceFile.IsEmpty())
		{
              MessageBox("��ѡ����ļ�·��Ϊ�գ�", "��ʾ", MB_OK|MB_ICONWARNING);
			  return;
		}

	    //�ؽ�Directshow Graph
		 if(!CreateGraph())
		 {
            TRACE("CreateGraph() failed! \n");

			DestroyGraph();
		    m_FilterGraph = NULL;
			return;
		 }

		 	  
		 //����ļ�����ʱ�䳤��
	     m_FilterGraph->GetDuration(&m_FileTimeinNanos);

		 TRACE("File duration: %ld ms\n", m_FileTimeinNanos/MILLISECS_DIVIDE);

		 long volume = m_FilterGraph->GetAudioVolume();

		 m_VolumeSlider.SetPos(volume);

		 /////////////////////////////////////////////////////

		CString strLyricFile;

		//���ݸ����ļ���ȷ������ļ���(����ļ�����������ļ�λ��ͬһĿ¼)
		int pos = 0;
		if( (pos = szFileName.ReverseFind('.')) != -1)
		{
			 strLyricFile = szFileName.Left(pos);
			strLyricFile += ".lrc";
		} 
		else
		{
			return;
		}
        
		//�ڸ����ļ���Ŀ¼���Ҹ���ļ�
		if(!OpenLyricFile(strLyricFile))
		{
           if(IDOK != MessageBox("����ļ������ڣ�����ȻҪ���Ÿ������ļ���", "��ʾ", MB_OK|MB_ICONWARNING))
		   {
			   m_wndLyric.Stop();
		       m_wndLyric.ClearLyrics();
			   return;
		   }
		   m_wndLyric.Stop();
		   m_wndLyric.ClearLyrics();
		}


	}

     //��ʼ���Ÿ��
	 m_wndLyric.Start();



	//��ʼ��������
	if (m_FilterGraph)
	{
		m_FilterGraph->Run();
		//������ʱ��
		if (m_SliderTimer == 0)
		{
			m_SliderTimer = SetTimer(SLIDER_TIMER, 100, NULL);
		}
	}
	
}

//��ͣ����
void CTestLyricDlg::OnButtonPause() 
{
	if (m_FilterGraph)
	{
		m_FilterGraph->Pause();
		// Start a timer
		if (m_SliderTimer == 0)
		{
			m_SliderTimer = SetTimer(SLIDER_TIMER, 100, NULL);
		}
	}
}

//ֹͣ����
void CTestLyricDlg::OnButtonStop() 
{
	if (m_FilterGraph)
	{
		m_FilterGraph->SetCurrentPosition(0);
		m_FilterGraph->Stop();

	    //ֹͣ��ʱ��
		if (m_SliderTimer)
		{
			KillTimer(m_SliderTimer);
			m_SliderTimer = 0;
		}

		DestroyGraph();
		m_FilterGraph = NULL;
	}
	m_TimeSlider.SetPos(0);
}



BOOL CTestLyricDlg::CreateGraph(void)
{
	//���ͷ��Ѵ�����Filter Graph
	DestroyGraph();

	m_FilterGraph = new CDXGraph();
	if (m_FilterGraph->Create())
	{
		// ����������ļ���Directshow Filter Graph(ʹ���������ӷ�ʽ)
		
		bool bSuccess = m_FilterGraph->RenderFile(m_SourceFile);
        if(!bSuccess)
			return FALSE;

		// Set video window and notification window
		//m_FilterGraph->SetDisplayWindow(mVideoWindow.GetSafeHwnd());
		
		m_FilterGraph->SetNotifyWindow(this->GetSafeHwnd());

		m_FilterGraph->Pause();

		return bSuccess;
	}
	return FALSE;
}

void CTestLyricDlg::DestroyGraph(void)
{
	if (m_FilterGraph)
	{
	
		m_FilterGraph->Stop();
		m_FilterGraph->SetNotifyWindow(NULL);

		delete m_FilterGraph;
		m_FilterGraph = NULL;
	}
}

//����ˮƽ���������϶��͵����Ϣ
void CTestLyricDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if(nSBCode == SB_ENDSCROLL)  // ���� End scroll��Ϣ.
	  return;

	if (pScrollBar->GetSafeHwnd() == m_TimeSlider.GetSafeHwnd())
	{
		if (m_FilterGraph)
		{
			// ����������ʱ��λ��
			LONGLONG duration = 0;
			m_FilterGraph->GetDuration(&duration);
			LONGLONG pos = duration * m_TimeSlider.GetPos() / 1000;
			m_FilterGraph->SetCurrentPosition(pos);
		}		
	}

	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void CTestLyricDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if(nSBCode == SB_ENDSCROLL)  // ���� End scroll
	  return;

	if(pScrollBar->GetSafeHwnd() == m_VolumeSlider.GetSafeHwnd())
	{
	   if(m_FilterGraph)
	   {
		int nPosition = m_VolumeSlider.GetPos();
		int lVolume = -1 * nPosition;
			
		m_FilterGraph->SetAudioVolume(lVolume);
	   }
	}
	else
	{
		CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
	}
}

// Deal with the graph events 
LRESULT CTestLyricDlg::OnGraphNotify(WPARAM inWParam, LPARAM inLParam)
{
	IMediaEventEx * pEvent = NULL;
	if (m_FilterGraph && (pEvent = m_FilterGraph->GetEventHandle()))
	{
		LONG   eventCode = 0, eventParam1 = 0, eventParam2 = 0;
		while (SUCCEEDED(pEvent->GetEvent(&eventCode, &eventParam1, &eventParam2, 0)))
		{ 
			// Spin through the events
			pEvent->FreeEventParams(eventCode, eventParam1, eventParam2);
			switch (eventCode)
			{
			case EC_COMPLETE:
				PostMessage(WM_PENDING_STOP_PLAY, 0, 0);
				break;
			case EC_USERABORT:
			case EC_ERRORABORT:
                PostMessage(WM_PENDING_STOP_PLAY, 0, 0);
				break;

			default:
				break;
			}
		}
	}
	return 0;
}

LRESULT CTestLyricDlg::OnPendingStopPlay(WPARAM wparam, LPARAM lparam)
{
	OnButtonStop();
   return 0;
}

void CTestLyricDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == m_SliderTimer && m_FilterGraph)
	{
		LONGLONG pos = 0, duration = m_FileTimeinNanos;

		m_FilterGraph->GetCurrentPosition(&pos);
		//m_FilterGraph->GetDuration(&duration);

		// ��ò�����λ�ã����Ҹ��½�����
		int newPos = int(pos * 1000 / duration);
		if (m_TimeSlider.GetPos() != newPos)
		{
			m_TimeSlider.SetPos(newPos);
		}

		long ms = pos / (MILLISECS_DIVIDE);
		//���¸�ʵ�ǰʱ��
		m_iMainTime = ms;
	}

	CDialog::OnTimer(nIDEvent);
}

//����ʱ�䵥λΪms
int CTestLyricDlg::GetCurrentTime()
{
   return m_iMainTime;
}

//����ʱ�䵥λΪms
int CTestLyricDlg::GetSongTotalTime()
{
  int ms = m_FileTimeinNanos/ (MILLISECS_DIVIDE);
  return ms;
}

void CTestLyricDlg::OnCheckFadeEffect()
{
	if(((CButton*)GetDlgItem(IDC_CHECK1))->GetState() & 1)
		m_wndLyric.SetFadeIn(TRUE);
	else
		m_wndLyric.SetFadeIn(FALSE);
}
