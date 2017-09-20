// OleRichEditCtrl.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COleRichEditCtrl

COleRichEditCtrl::COleRichEditCtrl()
{
	m_bCallbackSet = FALSE;
}

COleRichEditCtrl::~COleRichEditCtrl()
{
	// IExRichEditOleCallback class is a reference-counted class  
	// which deletes itself and for which delete should not be called

	// delete m_pIRichEditOleCallback;
}


BEGIN_MESSAGE_MAP(COleRichEditCtrl, CRichEditCtrl)
	//{{AFX_MSG_MAP(COleRichEditCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int COleRichEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRichEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// m_pIRichEditOleCallback should have been created in PreSubclassWindow

	ASSERT(m_pIRichEditOleCallback != NULL);

	// set the IExRichEditOleCallback pointer if it wasn't set 
	// successfully in PreSubclassWindow

	if (!m_bCallbackSet)
	{
		SetOLECallback(m_pIRichEditOleCallback);
	}

	return 0;
}

void COleRichEditCtrl::PreSubclassWindow()
{
	// base class first
	CRichEditCtrl::PreSubclassWindow();

	m_pIRichEditOleCallback = NULL;
	m_pIRichEditOleCallback = new IExRichEditOleCallback;
	ASSERT(m_pIRichEditOleCallback != NULL);

	m_bCallbackSet = SetOLECallback(m_pIRichEditOleCallback);
}


long COleRichEditCtrl::StreamInFromResource(int iRes, LPCTSTR sType)
{
	HINSTANCE hInst = AfxGetInstanceHandle();
	HRSRC hRsrc = ::FindResource(hInst,
		MAKEINTRESOURCE(iRes), sType);

	DWORD len = SizeofResource(hInst, hRsrc);
	BYTE* lpRsrc = (BYTE*)LoadResource(hInst, hRsrc);
	ASSERT(lpRsrc);

	CMemFile mfile;
	mfile.Attach(lpRsrc, len);

	EDITSTREAM es;
	es.pfnCallback = readFunction;
	es.dwError = 0;
	es.dwCookie = (DWORD)&mfile;

	return StreamIn(SF_RTF, es);
}


/* static */
DWORD CALLBACK COleRichEditCtrl::readFunction(DWORD dwCookie,
	LPBYTE lpBuf,			// the buffer to fill
	LONG nCount,			// number of bytes to read
	LONG* nRead)			// number of bytes actually read
{
	CFile* fp = (CFile *)dwCookie;
	*nRead = fp->Read(lpBuf, nCount);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////

COleRichEditCtrl::IExRichEditOleCallback::IExRichEditOleCallback()
{
	pStorage = NULL;
	m_iNumStorages = 0;
	m_dwRef = 0;

	// set up OLE storage

	HRESULT hResult = ::StgCreateDocfile(NULL,
		STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE /*| STGM_DELETEONRELEASE */ | STGM_CREATE,
		0, &pStorage);

	if (pStorage == NULL ||
		hResult != S_OK)
	{
		AfxThrowOleException(hResult);
	}
}

COleRichEditCtrl::IExRichEditOleCallback::~IExRichEditOleCallback()
{
}

HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::GetNewStorage(LPSTORAGE* lplpstg)
{
	m_iNumStorages++;
	WCHAR tName[50];
	swprintf_s(tName, sizeof(tName), _T("REOLEStorage%d"), m_iNumStorages);

	HRESULT hResult = pStorage->CreateStorage(tName,
		STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
		0, 0, lplpstg);

	if (hResult != S_OK)
	{
		::AfxThrowOleException(hResult);
	}

	return hResult;
}

HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::QueryInterface(REFIID iid, void ** ppvObject)
{

	HRESULT hr = S_OK;
	*ppvObject = NULL;

	if (iid == IID_IUnknown ||
		iid == IID_IRichEditOleCallback)
	{
		*ppvObject = this;
		AddRef();
		hr = NOERROR;
	}
	else
	{
		hr = E_NOINTERFACE;
	}

	return hr;
}



ULONG STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::AddRef()
{
	return ++m_dwRef;
}



ULONG STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::Release()
{
	if (--m_dwRef == 0)
	{
		delete this;
		return 0;
	}

	return m_dwRef;
}


HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::GetInPlaceContext(LPOLEINPLACEFRAME FAR *lplpFrame,
	LPOLEINPLACEUIWINDOW FAR *lplpDoc, LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::ShowContainerUI(BOOL fShow)
{
	return S_OK;
}



HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::QueryInsertObject(LPCLSID lpclsid, LPSTORAGE lpstg, LONG cp)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::DeleteObject(LPOLEOBJECT lpoleobj)
{
	return S_OK;
}



HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::QueryAcceptData(LPDATAOBJECT lpdataobj, CLIPFORMAT FAR *lpcfFormat,
	DWORD reco, BOOL fReally, HGLOBAL hMetaPict)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::ContextSensitiveHelp(BOOL fEnterMode)
{
	return S_OK;
}



HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::GetClipboardData(CHARRANGE FAR *lpchrg, DWORD reco, LPDATAOBJECT FAR *lplpdataobj)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::GetDragDropEffect(BOOL fDrag, DWORD grfKeyState, LPDWORD pdwEffect)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE
COleRichEditCtrl::IExRichEditOleCallback::GetContextMenu(WORD seltyp, LPOLEOBJECT lpoleobj, CHARRANGE FAR *lpchrg,
	HMENU FAR *lphmenu)
{
	return S_OK;
}

CString COleRichEditCtrl::GetRTF()
{
	// Return the RTF string of the text in the control.

	// Stream out here.
	EDITSTREAM es;
	es.dwError = 0;
	es.pfnCallback = CBStreamOut;		// Set the callback

	CString sRTF = _T("");

	es.dwCookie = (DWORD)&sRTF;	// so sRTF receives the string

	StreamOut(SF_RTF, es);			// Call CRichEditCtrl::StreamOut to get the string.
									///

	return sRTF;

}

void COleRichEditCtrl::SetRTF(CString sRTF)
{
	// Put the RTF string sRTF into the rich edit control.

	// Read the text in
	EDITSTREAM es;
	memset(&es, 0, sizeof(es));
	es.dwError = 0;
	es.pfnCallback = CBStreamIn;
	es.dwCookie = (DWORD_PTR)&sRTF;
	StreamIn(SF_RTF, es);	// Do it.

}

/*
Callback function to stream an RTF string into the rich edit control.
*/
DWORD CALLBACK COleRichEditCtrl::CBStreamIn(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	// We insert the rich text here.

	/*
	This function taken from CodeGuru.com
	http://www.codeguru.com/richedit/rtf_string_streamin.shtml
	Zafir Anjum
	*/

	//CString *pstr = (CString *)dwCookie;

	//if (pstr->GetLength() < cb)
	//{
	//	*pcb = pstr->GetLength();
	//	memcpy(pbBuff, LPSTR(LPCTSTR(*pstr)), *pcb);
	//	pstr->Empty();
	//}
	//else
	//{
	//	*pcb = cb;
	//	memcpy(pbBuff, LPSTR(LPCTSTR(*pstr)), *pcb);
	//	*pstr = pstr->Right(pstr->GetLength() - cb);
	//}
	///

	CString *psBuffer = (CString*)dwCookie;
	if (cb > psBuffer->GetLength())
		cb = psBuffer->GetLength();
	for (int i = 0; i < cb; i++)
		*(pbBuff + i) = (BYTE)psBuffer->GetAt(i);
	*pcb = cb;
	*psBuffer = psBuffer->Mid(cb);
	return 0;
}

/*
Callback function to stream the RTF string out of the rich edit control.
*/
DWORD CALLBACK COleRichEditCtrl::CBStreamOut(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	// Address of our string var is in psEntry
	CString *psEntry = (CString*)dwCookie;


	CString tmpEntry = _T("");
	tmpEntry = (CString)pbBuff;

	// And write it!!!
	*psEntry += tmpEntry.Left(cb);

	return 0;
}

bool COleRichEditCtrl::SelectionIsBold()
{
	CHARFORMAT cf = GetCharFormat();

	if (cf.dwEffects & CFM_BOLD)
		return true;
	else
		return false;
}

bool COleRichEditCtrl::SelectionIsItalic()
{
	CHARFORMAT cf = GetCharFormat();

	if (cf.dwEffects & CFM_ITALIC)
		return true;
	else
		return false;
}

bool COleRichEditCtrl::SelectionIsUnderlined()
{
	CHARFORMAT cf = GetCharFormat();

	if (cf.dwEffects & CFM_UNDERLINE)
		return true;
	else
		return false;
}

CHARFORMAT COleRichEditCtrl::GetCharFormat(DWORD dwMask)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);

	cf.dwMask = dwMask;

	GetSelectionCharFormat(cf);

	return cf;
}

void COleRichEditCtrl::SetCharStyle(int MASK, int STYLE, int nStart, int nEnd)
{
	CHARFORMAT cf;
	cf.cbSize = sizeof(CHARFORMAT);
	//cf.dwMask = MASK;

	GetSelectionCharFormat(cf);

	if (cf.dwMask & MASK)	// selection is all the same
	{
		cf.dwEffects ^= STYLE;
	}
	else
	{
		cf.dwEffects |= STYLE;
	}

	cf.dwMask = MASK;

	SetSelectionCharFormat(cf);

}

void COleRichEditCtrl::SetSelectionBold()
{
	long start = 0, end = 0;
	GetSel(start, end);		// Get the current selection

	SetCharStyle(CFM_BOLD, CFE_BOLD, start, end);	// Make it bold
}

void COleRichEditCtrl::SetSelectionItalic()
{
	long start = 0, end = 0;
	GetSel(start, end);

	SetCharStyle(CFM_ITALIC, CFE_ITALIC, start, end);
}

void COleRichEditCtrl::SetSelectionUnderlined()
{
	long start = 0, end = 0;
	GetSel(start, end);

	SetCharStyle(CFM_UNDERLINE, CFE_UNDERLINE, start, end);
}

void COleRichEditCtrl::SetParagraphCenter()
{
	PARAFORMAT paraFormat;
	paraFormat.cbSize = sizeof(PARAFORMAT);
	paraFormat.dwMask = PFM_ALIGNMENT;
	paraFormat.wAlignment = PFA_CENTER;

	SetParaFormat(paraFormat);	// Set the paragraph.
}

void COleRichEditCtrl::SetParagraphLeft()
{
	PARAFORMAT paraFormat;
	paraFormat.cbSize = sizeof(PARAFORMAT);
	paraFormat.dwMask = PFM_ALIGNMENT;
	paraFormat.wAlignment = PFA_LEFT;

	SetParaFormat(paraFormat);
}

void COleRichEditCtrl::SetParagraphRight()
{
	PARAFORMAT paraFormat;
	paraFormat.cbSize = sizeof(PARAFORMAT);
	paraFormat.dwMask = PFM_ALIGNMENT;
	paraFormat.wAlignment = PFA_RIGHT;

	SetParaFormat(paraFormat);
}

bool COleRichEditCtrl::ParagraphIsCentered()
{
	PARAFORMAT pf = GetParagraphFormat();

	if (pf.wAlignment == PFA_CENTER)
		return true;
	else
		return false;
}

bool COleRichEditCtrl::ParagraphIsLeft()
{
	PARAFORMAT pf = GetParagraphFormat();

	if (pf.wAlignment == PFA_LEFT)
		return true;
	else
		return false;
}

bool COleRichEditCtrl::ParagraphIsRight()
{
	PARAFORMAT pf = GetParagraphFormat();

	if (pf.wAlignment == PFA_RIGHT)
		return true;
	else
		return false;
}

PARAFORMAT COleRichEditCtrl::GetParagraphFormat()
{
	PARAFORMAT pf;
	pf.cbSize = sizeof(PARAFORMAT);

	pf.dwMask = PFM_ALIGNMENT | PFM_NUMBERING;

	GetParaFormat(pf);

	return pf;
}

void COleRichEditCtrl::SetParagraphBulleted()
{
	PARAFORMAT paraformat = GetParagraphFormat();

	if ((paraformat.dwMask & PFM_NUMBERING) && (paraformat.wNumbering == PFN_BULLET))
	{
		paraformat.wNumbering = 0;
		paraformat.dxOffset = 0;
		paraformat.dxStartIndent = 0;
		paraformat.dwMask = PFM_NUMBERING | PFM_STARTINDENT | PFM_OFFSET;
	}
	else
	{
		paraformat.wNumbering = PFN_BULLET;
		paraformat.dwMask = PFM_NUMBERING;
		if (paraformat.dxOffset == 0)
		{
			paraformat.dxOffset = 4;
			paraformat.dwMask = PFM_NUMBERING | PFM_STARTINDENT | PFM_OFFSET;
		}
	}

	SetParaFormat(paraformat);

}

bool COleRichEditCtrl::ParagraphIsBulleted()
{
	PARAFORMAT pf = GetParagraphFormat();

	if (pf.wNumbering == PFN_BULLET)
		return true;
	else
		return false;
}

void COleRichEditCtrl::SelectColor()
{
	CColorDialog dlg;

	CHARFORMAT cf = GetCharFormat();

	if (cf.dwEffects & CFE_AUTOCOLOR) cf.dwEffects -= CFE_AUTOCOLOR;

	// Get a color from the common color dialog.
	if (dlg.DoModal() == IDOK)
	{
		cf.crTextColor = dlg.GetColor();
	}

	cf.dwMask = CFM_COLOR;

	SetSelectionCharFormat(cf);
}

void COleRichEditCtrl::SetFontName(CString sFontName)
{
	CHARFORMAT cf = GetCharFormat();

	// Set the font name.
	for (int i = 0; i <= sFontName.GetLength() - 1; i++)
		cf.szFaceName[i] = sFontName[i];


	cf.dwMask = CFM_FACE;

	SetSelectionCharFormat(cf);
}

void COleRichEditCtrl::SetFontSize(int nPointSize)
{
	CHARFORMAT cf = GetCharFormat();

	nPointSize *= 20;	// convert from to twips
	cf.yHeight = nPointSize;

	cf.dwMask = CFM_SIZE;

	SetSelectionCharFormat(cf);
}

void COleRichEditCtrl::GetSystemFonts(CStringArray &saFontList)
{
	CDC *pDC = GetDC();

	EnumFonts(pDC->GetSafeHdc(), NULL, (FONTENUMPROC)CBEnumFonts, (LPARAM)&saFontList);//Enumerate

}

BOOL CALLBACK COleRichEditCtrl::CBEnumFonts(LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwType, LPARAM lpData)
{
	// This function was written with the help of CCustComboBox, by Girish Bharadwaj.
	// Available from Codeguru.

	if (dwType == TRUETYPE_FONTTYPE)
	{
		((CStringArray *)lpData)->Add(lplf->lfFaceName);
	}

	return true;
}

CString COleRichEditCtrl::GetSelectionFontName()
{
	CHARFORMAT cf = GetCharFormat();

	CString sName = cf.szFaceName;

	return sName;
}

long COleRichEditCtrl::GetSelectionFontSize()
{
	CHARFORMAT cf = GetCharFormat();

	long nSize = cf.yHeight / 20;

	return nSize;
}
