#pragma once


// CRoomCreate ��ȭ �����Դϴ�.

class CRoomCreate : public CDialogEx
{
	DECLARE_DYNAMIC(CRoomCreate)

public:
	CRoomCreate(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRoomCreate();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CREATEROOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedIdok();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioPrivate();
	afx_msg void OnBnClickedRadioPublic();
	afx_msg void OnBnClickedIdcancel();
};
