#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CRoom ��ȭ �����Դϴ�.

class CRoom : public CDialogEx
{
	DECLARE_DYNAMIC(CRoom)

public:
	CRoom(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRoom();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ROOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
