// MultiThread3.h : main header file for the MULTITHREAD3 application
//

#if !defined(AFX_MULTITHREAD3_H__3EF8E997_0D43_425C_8DA0_EE7BE6E12722__INCLUDED_)
#define AFX_MULTITHREAD3_H__3EF8E997_0D43_425C_8DA0_EE7BE6E12722__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiThread3App:
// See MultiThread3.cpp for the implementation of this class
//

class CMultiThread3App : public CWinApp
{
public:
	CMultiThread3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiThread3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMultiThread3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MULTITHREAD3_H__3EF8E997_0D43_425C_8DA0_EE7BE6E12722__INCLUDED_)
