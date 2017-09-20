// RoomCreate.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MessaengerClient.h"
#include "RoomCreate.h"
#include "afxdialogex.h"


// CRoomCreate 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRoomCreate, CDialogEx)

CRoomCreate::CRoomCreate(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CREATEROOM, pParent)
{
}

CRoomCreate::~CRoomCreate()
{
}

void CRoomCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRoomCreate, CDialogEx)
	ON_BN_CLICKED(CR_IDOK, &CRoomCreate::OnBnClickedIdok)
	ON_BN_CLICKED(IDC_RADIO_PRIVATE, &CRoomCreate::OnBnClickedRadioPrivate)
	ON_BN_CLICKED(IDC_RADIO_PUBLIC, &CRoomCreate::OnBnClickedRadioPublic)
	ON_BN_CLICKED(CR_IDCANCEL, &CRoomCreate::OnBnClickedIdcancel)
END_MESSAGE_MAP()


// CRoomCreate 메시지 처리기입니다.


void CRoomCreate::OnBnClickedIdok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Lobby *pLobby = dynamic_cast<Lobby *>(GetParent());
	if (pLobby) {
		GetDlgItemText(EDIT_ROOMNAME, pLobby->TitleString);
		GetDlgItemText(EDIT_ROOMPASS, pLobby->RoomPassString);

		int nCheck = GetCheckedRadioButton(IDC_RADIO_PUBLIC, IDC_RADIO_PRIVATE);
		if (nCheck == IDC_RADIO_PUBLIC) {
			pLobby->RoomStatus = 0;	// 공개방
		}
		else {
			pLobby->RoomStatus = 1;	// 비 공개방
		}

		// 2번은 귓말
	}

	EndDialog(CR_IDOK);
}

void CRoomCreate::OnBnClickedIdcancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	EndDialog(CR_IDCANCEL);
}

BOOL CRoomCreate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CButton *pButton = (CButton*)GetDlgItem(IDC_RADIO_PUBLIC);
	pButton->SetCheck(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CRoomCreate::OnBnClickedRadioPrivate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEdit *pEdit = (CEdit*)GetDlgItem(EDIT_ROOMPASS);
	pEdit->EnableWindow(TRUE);
}

void CRoomCreate::OnBnClickedRadioPublic()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEdit *pEdit = (CEdit*)GetDlgItem(EDIT_ROOMPASS);
	pEdit->EnableWindow(FALSE);
}
