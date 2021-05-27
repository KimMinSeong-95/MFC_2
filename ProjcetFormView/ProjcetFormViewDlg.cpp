
// ProjcetFormViewDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ProjcetFormView.h"
#include "ProjcetFormViewDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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
END_MESSAGE_MAP()


// CProjcetFormViewDlg 대화 상자



CProjcetFormViewDlg::CProjcetFormViewDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJCETFORMVIEW_DIALOG, pParent)
	, m_strName(_T(""))
	, m_nAge(0)
	, m_Gender(FALSE)
	, m_nCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProjcetFormViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_AGE, m_nAge);
	DDX_Radio(pDX, IDC_RADIO1, m_Gender);

	DDX_Control(pDX, IDC_CTRL_FRIEND, m_ctrlFriend);
	DDX_Control(pDX, IDC_SPIN_CTRL, m_ctrlSpin);	
}

BEGIN_MESSAGE_MAP(CProjcetFormViewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CProjcetFormViewDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CProjcetFormViewDlg::OnBnClickedButtonDelete)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_CTRL_FRIEND, &CProjcetFormViewDlg::OnLvnEndlabeleditCtrlFriend)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CProjcetFormViewDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CProjcetFormViewDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CProjcetFormViewDlg 메시지 처리기

BOOL CProjcetFormViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 1. 빈 방을 생성한다.
	static CImageList imgList;
	imgList.Create(16, 16, ILC_COLOR32, 2, 0);

	// 2. 각 방에 이미지를 추가한다.(ico, bmp)
	imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_MALE));
	imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_FEMALE));

	// 3. 컨트롤과 이미지 리스트가 결합
	m_ctrlFriend.SetImageList(&imgList, LVSIL_SMALL);

	//==================================================================
	m_ctrlFriend.InsertColumn(0, _T("이름"), 0, 100);
	m_ctrlFriend.InsertColumn(1, _T("나이"), 0, 100);
	m_ctrlFriend.InsertColumn(2, _T("성별"), 0, 100);

	m_ctrlSpin.SetRange(0, 100);
	m_ctrlSpin.SetPos(0);

	DWORD bwStyle = m_ctrlFriend.GetExtendedStyle();
	m_ctrlFriend.SetExtendedStyle(bwStyle
		| LVS_EX_FULLROWSELECT
		| LVS_EX_CHECKBOXES
		//| LVS_EX_GRIDLINES
		);
	//==================================================================
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CProjcetFormViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CProjcetFormViewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CProjcetFormViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CProjcetFormViewDlg::OnBnClickedButtonAdd()
{
	UpdateData(1);

	// 1. 리스트 컨트롤에 추가
	CString Temp;
	Temp.Format(_T("%d"), m_nAge);
	
	if (m_nCount >= 5)
	{
		MessageBox(_T("더 이상 추가할 수 없습니다."));
		return;
	}
	m_ctrlFriend.InsertItem(0, m_strName, m_Gender);
	m_ctrlFriend.SetItemText(0, 1, Temp);
	if (m_Gender == 0)
		m_ctrlFriend.SetItemText(0, 2, _T("남성"));
	else
		m_ctrlFriend.SetItemText(0, 2, _T("여성"));

	// 2. CPerson에 저장
	m_pPerson[m_nCount].m_strName = m_strName;
	m_pPerson[m_nCount].m_nAge = m_nAge;
	m_pPerson[m_nCount].m_bGender = m_Gender;

	m_nCount++;
}


void CProjcetFormViewDlg::OnBnClickedButtonDelete()
{
	int nIndex = m_ctrlFriend.GetItemCount();
	
	for (int i = m_nCount-1; i >= 0; i--)
	{
		if (m_ctrlFriend.GetCheck(i) == TRUE)
		{
			m_ctrlFriend.DeleteItem(i);
			m_nCount--;
		}
	}
}


void CProjcetFormViewDlg::OnLvnEndlabeleditCtrlFriend(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CEdit* pEdit = m_ctrlFriend.GetEditControl();
	CString strTemp;
	pEdit->GetWindowText(strTemp);

	m_ctrlFriend.SetItemText(pDispInfo->item.iItem, 0, strTemp);

	*pResult = 0;
}



void CProjcetFormViewDlg::OnBnClickedButtonSave()
{
	// 대화상자
	CFileDialog dlg(FALSE); // TRUE : 열기 , FALSE : 저장
	if(dlg.DoModal() != IDOK) return;

	/////////////////////////////////////////////////////////////////////////////////////
	CFile file(dlg.GetPathName(), CFile::modeCreate | CFile::modeReadWrite);

	CArchive ar(&file, CArchive::store);

	ar << m_nCount;
	for (int i = 0; i < m_nCount; i++)
	{
		m_pPerson[i].Serialize(ar);
	}
	/////////////////////////////////////////
	// 메모리와 화면 초기화
	/*for (int i = m_nCount - 1; i >= 0; i--)
	{*/
		//m_ctrlFriend.DeleteItem(i);
		//m_pPerson[i].m_strName = _T("");
		//m_pPerson[i].m_nAge = 0;
		//m_pPerson[i].m_bGender = FALSE;
	//}
	m_nCount = 0;
	m_ctrlFriend.DeleteAllItems();
}


void CProjcetFormViewDlg::OnBnClickedButtonLoad()
{
	CFileDialog dlg(TRUE); // TRUE : 열기 , FALSE : 저장
	if (dlg.DoModal() != IDOK) return;
	//////////////////////////////////////////////////////////
	// 메모리 화면 초기화
	m_nCount = 0;
	m_ctrlFriend.DeleteAllItems();
	/////////////////////////////////////////////////////
	CFile file(dlg.GetPathName(), CFile::modeRead);

	CArchive ar(&file, CArchive::load);

	ar >> m_nCount;
	for (int i = 0; i < m_nCount; i++)
	{
		m_pPerson[i].Serialize(ar);
	}
	/////////////////////////////////
	// 화면에 표시
	CString Temp;
	
	for (int i = 0; i < m_nCount; i++)
	{
		Temp.Format(_T("%d"), m_pPerson[i].m_nAge);
		m_ctrlFriend.InsertItem(0, m_pPerson[i].m_strName, m_pPerson[i].m_bGender);
		m_ctrlFriend.SetItemText(0, 1, Temp);
		if (m_pPerson[i].m_bGender == 0)
			m_ctrlFriend.SetItemText(0, 2, _T("남성"));
		else
			m_ctrlFriend.SetItemText(0, 2, _T("여성"));
	}
}