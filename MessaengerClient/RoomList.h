#pragma once
#include "afxcmn.h"


// CRoomList 대화 상자입니다.

class CRoomList : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomList)

public:
	CRoomList(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRoomList();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABCTL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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