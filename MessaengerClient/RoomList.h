#pragma once
#include "afxcmn.h"


// CRoomList ��ȭ �����Դϴ�.

class CRoomList : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomList)

public:
	CRoomList(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRoomList();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABCTL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeRoomlist(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
public:
	virtual void PostNcDestroy();
	HICON m_hIcon;
	CTabCtrl m_Tab;
	CRoom *m_pRoom;
	int m_Lastest_Index;
	std::vector<INT32> m_pTabIdx;
	std::map<INT32, INT32> m_mScrollPos;
	std::map<INT32, CString> m_pText;
	std::map<INT32, CString> m_pInputText;

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	BOOL RemoveRoom();
	void InsertRoom(CString &title, INT32 Index);
	void SelectRoom(INT32 Index);
	void SelectRoomMapIndex(INT32 nMapIndex);
	void ExitRoom(INT32 IndexRoom, INT32 Index);
	void SetSelNewTab();
	afx_msg void OnSelchangingTabRoomlist(NMHDR *pNMHDR, LRESULT *pResult);
	void SendRoomMessage(UINT32 roomIndex, int type, CString userName, CString msg);
};