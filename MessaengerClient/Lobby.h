#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Lobby ��ȭ �����Դϴ�.

class Lobby : public CDialogEx
{
	DECLARE_DYNAMIC(Lobby)

public:
	Lobby(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Lobby();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOBBY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	HICON m_hIcon;
public:
	afx_msg HCURSOR OnQueryDragIcon();
	BOOL m_bRoomList;
	BOOL m_bFriendList;
	CButton BtnTalkList;
	CListCtrl m_ctrlList;
	CListCtrl m_ctrlListWhisp;
	CRoomList *m_pRoomList;
	CFriendList *m_pFriendList;
	CString TitleString;
	CString RoomPassString;
	std::map<INT32, CString> m_WhispIndex;
	int RoomStatus;	// 0: ����, 1: �����, 2:�Ӹ�	// ���� �Ȼ����
	afx_msg void OnDblclkListRoom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnClickedTalklist();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnClickedFriendlist();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedRoommake();
};
