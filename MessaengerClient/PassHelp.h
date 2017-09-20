#pragma once
#include "afxwin.h"


// CPassHelp 대화 상자입니다.

class CPassHelp : public CDialogEx
{
	DECLARE_DYNAMIC(CPassHelp)

public:
	CPassHelp(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPassHelp();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PASSHELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit editID;
	afx_msg void OnBnClickedButton1();
};
