// Register.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MessaengerClient.h"
#include "Register.h"
#include "afxdialogex.h"


// CRegister 대화 상자입니다.

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


// CRegister 메시지 처리기입니다.


void CRegister::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		// 0 |/| 회원가입:2 |/| 아 이 디 |/| 비밀번호
		CString sendData;
		CString ID, PASS;
		editID.GetWindowText(ID);
		editPass.GetWindowText(PASS);

		// 계정 생성
		sendData.Format(_T("\\x80x0|/|2|/|%s|/|%s"), ID, PASS);
		pApp->SendData(sendData);

		// 창 종료
		this->EndDialog(0);
	}
}


void CRegister::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 창 종료
	this->EndDialog(0);
}
