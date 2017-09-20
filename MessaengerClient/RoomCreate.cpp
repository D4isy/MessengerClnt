// RoomCreate.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MessaengerClient.h"
#include "RoomCreate.h"
#include "afxdialogex.h"


// CRoomCreate ��ȭ �����Դϴ�.

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


// CRoomCreate �޽��� ó�����Դϴ�.


void CRoomCreate::OnBnClickedIdok()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Lobby *pLobby = dynamic_cast<Lobby *>(GetParent());
	if (pLobby) {
		GetDlgItemText(EDIT_ROOMNAME, pLobby->TitleString);
		GetDlgItemText(EDIT_ROOMPASS, pLobby->RoomPassString);

		int nCheck = GetCheckedRadioButton(IDC_RADIO_PUBLIC, IDC_RADIO_PRIVATE);
		if (nCheck == IDC_RADIO_PUBLIC) {
			pLobby->RoomStatus = 0;	// ������
		}
		else {
			pLobby->RoomStatus = 1;	// �� ������
		}

		// 2���� �Ӹ�
	}

	EndDialog(CR_IDOK);
}

void CRoomCreate::OnBnClickedIdcancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	EndDialog(CR_IDCANCEL);
}

BOOL CRoomCreate::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CButton *pButton = (CButton*)GetDlgItem(IDC_RADIO_PUBLIC);
	pButton->SetCheck(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CRoomCreate::OnBnClickedRadioPrivate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CEdit *pEdit = (CEdit*)GetDlgItem(EDIT_ROOMPASS);
	pEdit->EnableWindow(TRUE);
}

void CRoomCreate::OnBnClickedRadioPublic()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CEdit *pEdit = (CEdit*)GetDlgItem(EDIT_ROOMPASS);
	pEdit->EnableWindow(FALSE);
}
