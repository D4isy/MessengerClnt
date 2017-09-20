#pragma once


// CRoomCreate 대화 상자입니다.

class CRoomCreate : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomCreate)

public:
	CRoomCreate(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRoomCreate();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATEROOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedIdok();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioPrivate();
	afx_msg void OnBnClickedRadioPublic();
	afx_msg void OnBnClickedIdcancel();
};
