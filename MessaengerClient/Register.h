#pragma once
#include "afxwin.h"


// CRegister ��ȭ �����Դϴ�.

class CRegister : public CDialogEx
{
	DECLARE_DYNAMIC(CRegister)

public:
	CRegister(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRegister();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit editID;
	CEdit editPass;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
