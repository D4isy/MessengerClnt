
// MessaengerClientDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CMessaengerClientDlg ��ȭ ����
class CMessaengerClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMessaengerClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESSAENGERCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CRgn m_Rgn;
	afx_msg void OnClickedLogin();
	afx_msg void OnClickedRegister();
	afx_msg void OnClickedAccSearch();
	afx_msg void OnDestroy();
};
