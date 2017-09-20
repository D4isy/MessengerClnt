
// MessaengerClientDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CMessaengerClientDlg 대화 상자
class CMessaengerClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CMessaengerClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESSAENGERCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
