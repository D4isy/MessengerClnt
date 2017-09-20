// PassHelp.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MessaengerClient.h"
#include "PassHelp.h"
#include "afxdialogex.h"


// CPassHelp 대화 상자입니다.

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


// CPassHelp 메시지 처리기입니다.


void CPassHelp::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		// 0 |/| 회원가입:2 |/| 아 이 디 |/| 비밀번호
		CString sendData;
		CString ID;
		editID.GetWindowText(ID);

		// 계정 생성
		sendData.Format(_T("\\x80x0|/|3|/|%s"), ID);
		pApp->SendData(sendData);

		// 창 종료
		this->EndDialog(0);
	}
}
