
// MessaengerClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_DESTROY()
//	ON_COMMAND(AFX_ID_PREVIEW_CLOSE, &CAboutDlg::OnAfxIdPreviewClose)
//	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMessaengerClientDlg ��ȭ ����



CMessaengerClientDlg::CMessaengerClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MESSAENGERCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMessaengerClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMessaengerClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_LOGIN, &CMessaengerClientDlg::OnClickedLogin)
	ON_BN_CLICKED(ID_REGISTER, &CMessaengerClientDlg::OnClickedRegister)
	ON_BN_CLICKED(ID_ACC_SEARCH, &CMessaengerClientDlg::OnClickedAccSearch)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMessaengerClientDlg �޽��� ó����
BOOL CMessaengerClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CFont DlgFont;
	LOGFONT LogFont;

	// Static ��Ʈ�� Font ���� ��������
	GetDlgItem(STATIC_ID)->GetFont()->GetLogFont(&LogFont);

	// Font ����
	LogFont.lfHeight = 15;
	
	// Font ����
	DlgFont.CreateFontIndirect(&LogFont);
	GetDlgItem(STATIC_ID)->SetFont(&DlgFont);
	GetDlgItem(STATIC_PASS)->SetFont(&DlgFont);
	DlgFont.DeleteObject();

	CMessaengerClientDlg dlg;

	BOOL bResult = FALSE;
	LONG lResult = SetWindowLong(this->GetSafeHwnd()
		, GWL_EXSTYLE
		, GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) | WS_EX_LAYERED);

	if (!lResult) {
		AfxMessageBox(_T("Fail to SetWindowLong..."));
		return FALSE;
	}

	bResult = SetLayeredWindowAttributes(0, 255, LWA_ALPHA);
	if (!bResult) {
		AfxMessageBox(_T("Fail to SetLayeredWindowAttributes..."));
		return FALSE;
	}

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMessaengerClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMessaengerClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMessaengerClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMessaengerClientDlg::OnClickedLogin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString editID;
	GetDlgItemText(EDIT_ID, editID);

	if (editID.GetLength() == 0) {
		GetDlgItem(EDIT_ID)->SetFocus();
		MessageBox(_T("���̵� �Է����ּ���."), _T("�α���"), MB_ICONERROR);
		return;
	}
	if (GetDlgItem(EDIT_ID) == GetFocus()) {
		GetDlgItem(EDIT_PASS)->SetFocus();
		return;
	}

	CString editPASS;
	GetDlgItemText(EDIT_PASS, editPASS);
	if (editPASS.GetLength() == 0) {
		MessageBox(_T("��й�ȣ�� �Է����ּ���."), _T("�α���"), MB_ICONERROR);
		return;
	}

	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	pApp->ServerConnect();

	//// �α��� �����
	//// PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);
	//if (!SetLayeredWindowAttributes(0, 0, LWA_ALPHA)) {
	//	AfxMessageBox(_T("Fail to SetWindowLong..."));
	//}

	//// �κ�â ����
	//Lobby *lobby = new Lobby((CWnd *)this);
	//lobby->DoModal();
	//// MessageBox(editID + " " + editPASS, _T("LOGIN"));
	//delete lobby;
	//this->DestroyWindow();

	// �α��� ����
	// PostMessage(WM_SHOWWINDOW, TRUE, SW_OTHERUNZOOM);
}


void CMessaengerClientDlg::OnClickedRegister()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CRegister Dialog;
	
	SetDlgItemText(EDIT_ID, _T(""));
	SetDlgItemText(EDIT_PASS, _T(""));

	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	pApp->ServerConnect();

	Dialog.DoModal();
}


void CMessaengerClientDlg::OnClickedAccSearch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CPassHelp Dialog;
	
	SetDlgItemText(EDIT_ID, _T(""));
	SetDlgItemText(EDIT_PASS, _T(""));

	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	pApp->ServerConnect();

	Dialog.DoModal();
}

void CMessaengerClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CMessaengerClientApp *pApp = (CMessaengerClientApp *)AfxGetApp();
	pApp->ServerDisconnect();
}
