// PassHelp.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MessaengerClient.h"
#include "PassHelp.h"
#include "afxdialogex.h"


// CPassHelp ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPassHelp, CDialogEx)

CPassHelp::CPassHelp(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PASSHELP, pParent)
{

}

CPassHelp::~CPassHelp()
{
}

void CPassHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, EDIT_ID, editID);
}


BEGIN_MESSAGE_MAP(CPassHelp, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CPassHelp::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPassHelp �޽��� ó�����Դϴ�.


void CPassHelp::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		// 0 |/| ȸ������:2 |/| �� �� �� |/| ��й�ȣ
		CString sendData;
		CString ID;
		editID.GetWindowText(ID);

		// ���� ����
		sendData.Format(_T("\\x80x0|/|3|/|%s"), ID);
		pApp->SendData(sendData);

		// â ����
		this->EndDialog(0);
	}
}
