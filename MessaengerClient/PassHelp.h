#pragma once
#include "afxwin.h"


// CPassHelp ��ȭ �����Դϴ�.

class CPassHelp : public CDialogEx
{
	DECLARE_DYNAMIC(CPassHelp)

public:
	CPassHelp(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPassHelp();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PASSHELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit editID;
	afx_msg void OnBnClickedButton1();
};
