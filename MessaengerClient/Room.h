#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CRoom 대화 상자입니다.

class CRoom : public CDialogEx
{
	DECLARE_DYNAMIC(CRoom)

public:
	CRoom(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRoom();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon;
	COleRichEditCtrl m_RichEditCtrl;
	CEdit EditText;
	
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedRoomExit();
	afx_msg void OnBnClickedBtnSend();

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PostNcDestroy();

	void ViewMessage(int type, CString &userName, CString msg);

	DECLARE_EVENTSINK_MAP()
};
