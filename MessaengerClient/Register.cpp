// Register.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MessaengerClient.h"
#include "Register.h"
#include "afxdialogex.h"


// CRegister ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CRegister, CDialogEx)

CRegister::CRegister(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REGISTER, pParent)
{

}

CRegister::~CRegister()
{
}

void CRegister::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, EDIT_ID, editID);
	DDX_Control(pDX, EDIT_PASS, editPass);
}


BEGIN_MESSAGE_MAP(CRegister, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegister::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CRegister::OnBnClickedButton2)
END_MESSAGE_MAP()


// CRegister �޽��� ó�����Դϴ�.


void CRegister::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		// 0 |/| ȸ������:2 |/| �� �� �� |/| ��й�ȣ
		CString sendData;
		CString ID, PASS;
		editID.GetWindowText(ID);
		editPass.GetWindowText(PASS);

		// ���� ����
		sendData.Format(_T("\\x80x0|/|2|/|%s|/|%s"), ID, PASS);
		pApp->SendData(sendData);

		// â ����
		this->EndDialog(0);
	}
}


void CRegister::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// â ����
	this->EndDialog(0);
}
