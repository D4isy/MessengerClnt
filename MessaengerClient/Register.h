#pragma once
#include "afxwin.h"


// CRegister 대화 상자입니다.

class CRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CRegister)

public:
	CRegister(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRegister();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CEdit editID;
	CEdit editPass;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
