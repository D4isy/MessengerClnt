// Room.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "afxdialogex.h"

// CRoom 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRoom, CDialogEx)

CRoom::CRoom(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ROOM, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CRoom::~CRoom()
{

}

void CRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDHTMLEventsDlg)
	DDX_Control(pDX, IDC_EDIT_TEXT, EditText);
	DDX_Control(pDX, IDC_RICHEDIT, m_RichEditCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRoom, CDialogEx)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(ID_ROOM_EXIT, &CRoom::OnBnClickedRoomExit)
	ON_BN_CLICKED(IDC_BTN_SEND, &CRoom::OnBnClickedBtnSend)
//	ON_WM_SIZE()
END_MESSAGE_MAP()


// CRoom 메시지 처리기입니다.


void CRoom::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == VK_ESCAPE) {
#ifdef DEBUG
		MessageBox(_T("ESCAPE (for Room.cpp)"));
#endif // DEBUG

		return;
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CRoom::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE) { return TRUE; }
	if (pMsg->wParam == VK_ESCAPE) { return TRUE; }
	return CDialogEx::PreTranslateMessage(pMsg);
}

BEGIN_EVENTSINK_MAP(CRoom, CDialogEx)
END_EVENTSINK_MAP()

void CRoom::OnBnClickedBtnSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString text;
	EditText.GetWindowText(text);
	EditText.SetWindowText(_T(""));

	/*text = text.Trim();
	if (!text.GetLength())
		return;

	text = _T("[닉네임]\n") + text + _T("\n");

	int nLen = m_RichEditCtrl.GetWindowTextLength();
	m_RichEditCtrl.SetSel(nLen, nLen);
	m_RichEditCtrl.ReplaceSel(text);*/

	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	if (pApp) {
		ViewMessage(MSG_ME, pApp->userID, text);
		//ViewMessage(MSG_YOU, pApp->userID, _T("뭐냐"));

		CTabCtrl *pTabCtrl = dynamic_cast<CTabCtrl *>(GetParent());
		if (!pTabCtrl) {
			return;
		}
		CRoomList *pRoomList = dynamic_cast<CRoomList *>(pTabCtrl->GetParent());

		if (pRoomList != NULL) {
			// 2 |/| 룸 번호 |/| 입력 내용 |/| 원본과 암호화 값 (clnt)
			CString sendData;
			sendData.Format(_T("\\x80x2|/|%u|/|%s|/|암호화"), pRoomList->m_Lastest_Index, text);
			pApp->SendData(sendData);
		}
	}

#ifdef DEBUG
	//CString str = m_RichEditCtrl.GetRTF();
	//str.Insert(str.ReverseFind(_T('\\')), CString("\\viewkind4\\uc1\\pard\\lang1042\\f0\\fs17\\qr ") + CString("a\n"));
	//MessageBox(str);
	//str.Delete(str.ReverseFind(_T('\\'))-1, 8);
	//str.Format(_T("%s%s"), str, _T("\\par }"));
	//MessageBox(str);
	//str = CString("{\\rtf1\\ansi\\ansicpg949\\deff0\\deflang1033\\deflangfe1042{\\fonttbl{\\f0\\fnil\\fcharset129 \\'b8\\'bc\\'c0\\'ba \\'b0\\'ed\\'b5\\'f1;}{\\f1\\fswiss\\fprq2\\fcharset0 Arial;}}\n\\viewkind4\\uc1\\pard\\lang1042\\f0\\fs17 a\\fs30 a\\fs20 b\\fs17\n\\par \\pard\\sa200\\sl276\\slmult1\\qr\\tx4402\\lang18\\fs20 a\n\\par \\pard\\lang1042\\f1\\fs17 55555555555555555555555555555555555555555555555555555555555555555555555555555555555555\n\\par\\qr bbb\n\\par\n}");
	//str = _T("{\\rtf1 RE50W by Jim Dunne Copyright")
	//	_T(" (C) 2005\\par http://www.topjimmy.net/tjs \\par")
	//	_T("{\\field{\\*\\fldinst{HYPERLINK mailto:jim@dunnes.net")
	//	_T(" }}{\\fldrslt{\\cf1\\ul jim@dunnes.net}}}}");

	//SETTEXTEX m_st50W;
	//m_st50W.codepage = 1200;
	//m_st50W.flags = ST_SELECTION;
	//m_RichEditCtrl.SendMessage(EM_SETTEXTEX, (WPARAM)&m_st50W, (LPARAM)(LPCTSTR(m_csMessage)));

	//{ // 진하게
	//	CHARFORMAT cf = { sizeof(cf) };
	//	cf.dwEffects = CFM_BOLD;
	//	cf.dwMask = CFM_BOLD;
	//	m_RichEditCtrl.SetSel(0, 2);
	//	m_RichEditCtrl.SetSelectionCharFormat(cf);
	//}

	// 셋팅
	//m_RichEditCtrl.SetRTF(str);
#endif // DEBUG

	// Auto-Scrolling
	// m_RichEditCtrl.LineScroll(m_RichEditCtrl.GetLineCount());
	m_RichEditCtrl.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

void CRoom::OnBnClickedRoomExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTabCtrl *pTabCtrl = dynamic_cast<CTabCtrl *>(GetParent());
	if (!pTabCtrl) {
		return;
	}
	CRoomList *pRoomList = dynamic_cast<CRoomList *>(pTabCtrl->GetParent());

	if (pRoomList != NULL) {
		pRoomList->RemoveRoom();
	}
}

void CRoom::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	delete this;

	CDialogEx::PostNcDestroy();
}

void CRoom::ViewMessage(int type, CString &userName, CString msg)
{
	msg = msg.Trim();
	if (!msg.GetLength())
		return;

	CString str = m_RichEditCtrl.GetRTF();

	if (type == MSG_ME) {
		str.Insert(str.ReverseFind(_T('\\')), CString("\\viewkind4\\uc1\\pard\\lang1042\\f0\\fs17\\qr "));
		//str.Delete(str.ReverseFind(_T('\\')) - 1, 8);
		//str.Format(_T("%s%s"), str, _T("\\par }"));
		m_RichEditCtrl.SetRTF(str);
	}

	int nLen = m_RichEditCtrl.GetWindowTextLength();
	m_RichEditCtrl.SetSel(nLen, nLen);

	{
		wchar_t wChar;
		int nStringLength, nReturn;
		for (nStringLength = 0, nReturn = 0; nStringLength < msg.GetLength(); nStringLength++) {
			wChar = msg.GetAt(nStringLength);
			if (nReturn > 28) {
				// 추가
				msg.Insert(nStringLength - 1, _T("\n"));
				nReturn = 0;
			}
			else if (wChar == '\n') {
				nReturn = 0;
			}

			if (wChar >= 48 && wChar <= 57) {				// 숫자
				nReturn++;
			} 
			else if ((wChar >= 65 && wChar <= 90) ||
					 (wChar >= 97 && wChar <= 122)) {		// 영어
				nReturn++;
			}
			else if ((wChar >= 33 && wChar <= 47) ||
					 (wChar >= 58 && wChar <= 64) ||
					 (wChar >= 91 && wChar <= 96) ||
					 (wChar >= 123 && wChar <= 126)) {		// 특수기호
				nReturn++;
			}
			else if ((wChar >= 0x1100 && wChar <= 0x11F9) ||
					 (wChar >= 0x3130 && wChar <= 0x318E) ||
					 (wChar >= 0xAC00 && wChar <= 0xD7A3)) {
				nReturn += 2;
			}
			else {
				nReturn += 2;
			}
		}
	}
	//if (0) {
	//	wstring strUni = msg;
	//	int len = WideCharToMultiByte(CP_ACP, 0, &strUni[0], -1, NULL, 0, NULL, NULL);
	//	string strMulti(len, 0);
	//	WideCharToMultiByte(CP_ACP, 0, &strUni[0], -1, &strMulti[0], len, NULL, NULL);

	//	int nStringLength, nReturn;
	//	for (nStringLength = 0, nReturn = 0; nStringLength < len - 1; ) {

	//		if (nReturn > 28) {
	//			// 추가
	//			strMulti.insert(nStringLength - 1, string("\n"));
	//			len++;

	//			nReturn = 0;
	//		}
	//		else if (strMulti[nStringLength] == '\n') {
	//			nReturn = 0;
	//		}

	//		strMulti.at(nStringLength);
	//		if (IsDBCSLeadByte(strMulti[nStringLength])) {
	//			nReturn += 2;
	//			nStringLength += 2;		// 2byte Character
	//		}
	//		else {
	//			nReturn += 1;
	//			nStringLength += 1; //1byte Character
	//		}
	//	}

	//	msg = CA2CT(strMulti.c_str());
	//}

	CString text = userName + _T("\n") + msg + _T("\n\n");
	m_RichEditCtrl.ReplaceSel(text);

	if (type == MSG_ME) {
		str = m_RichEditCtrl.GetRTF();
		str.Insert(str.ReverseFind(_T('\\')), CString("\\viewkind4\\uc1\\pard\\lang1042\\f0\\fs17\\ql "));
		m_RichEditCtrl.SetRTF(str);
	}
}