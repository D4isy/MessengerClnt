#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CFriendList 폼 뷰입니다.

class CFriendList : public CDialogEx
{
	DECLARE_DYNCREATE(CFriendList)

public:
	CFriendList(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CFriendList();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FRIENDLIST };
#endif
	CTreeCtrl m_Tree;

protected:
	CImageList m_imgList;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnSelchangedTreeFriend(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedFriendDel();
	afx_msg void OnClickedFriendAdd();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditName;
	HTREEITEM m_hItemDrag;
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	void DeleteSelected();
	void ReportDeleteBackToParent(HTREEITEM hOld);
	afx_msg void OnBegindragTreeFriend(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void OnEndDrag(UINT nFlags, CPoint point);
	void FinishDragging(BOOL bDraggingImageList);
	afx_msg void OnDblclkTreeFriend(NMHDR *pNMHDR, LRESULT *pResult);
};


