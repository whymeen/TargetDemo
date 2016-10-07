
// TargetDemoDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TargetDemo.h"
#include "TargetDemoDlg.h"
#include "afxdialogex.h"
#include "tinyxml2.h"
#include "afxtempl.h"


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


// CTargetDemoDlg 대화 상자



CTargetDemoDlg::CTargetDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TARGETDEMO_DIALOG, pParent)
	, ti_id(0)
	, ti_type(0)
	, ti_x(0)
	, ti_y(0)
	, ti_path(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTargetDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, ti_id);
	DDX_Text(pDX, IDC_EDIT_TYPE, ti_type);
	DDX_Text(pDX, IDC_EDIT_X, ti_x);
	DDX_Text(pDX, IDC_EDIT_Y, ti_y);
	DDX_Text(pDX, IDC_EDIT_PATH, ti_path);
	DDX_Control(pDX, IDC_GRID, m_Grid);
}

BEGIN_MESSAGE_MAP(CTargetDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CTargetDemoDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CTargetDemoDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CTargetDemoDlg::OnBnClickedButtonInput)
	ON_BN_CLICKED(IDC_BUTTON_Clear, &CTargetDemoDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CTargetDemoDlg 메시지 처리기

BOOL CTargetDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	


    // 그리드 테이블 생성

	m_Grid.SetEditable(false);
	m_Grid.SetTextBkColor(RGB(0xFF, 0xFF, 0xE0));//yellow background
	m_Grid.SetRowCount(1); //
	m_Grid.SetColumnCount(5); //
	m_Grid.SetFixedRowCount(1); //

	for (int row = 0; row < m_Grid.GetRowCount(); row++)
		for (int col = 0; col < m_Grid.GetColumnCount(); col++)
		{

			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;

			m_Grid.SetRowHeight(row, 30); //set row heigh          
			m_Grid.SetColumnWidth(0, 135); //set column width 
			m_Grid.SetColumnWidth(col, 135); //

			if (row == 0 && col == 0) //
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T("ID"), col);
			}
			else if (row == 0 && col == 1) //
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T(" Type "), col);
			}
			else if (row == 0 && col == 2) //
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T(" X "), col);
			}
			else if (row == 0 && col == 3) //
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T(" Y "), col);
			}
			else if (row == 0 && col == 4) //
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T(" Path "), col);
			}
			else
			{
				Item.nFormat = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
				Item.strText.Format(_T(""), 2);
			}
			m_Grid.SetItem(&Item);
		}

		

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTargetDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTargetDemoDlg::OnPaint()
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
HCURSOR CTargetDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTargetDemoDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CTargetDemoDlg::OnBnClickedButtonLoad()
{

	CString str = _T("XML files(*.xml)|*.xml");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);
	if (IDOK == dlg.DoModal())
	{
		tVector.clear();

		CString strPathName = dlg.GetPathName();
		tinyxml2::XMLDocument doc;
		doc.LoadFile((CStringA)strPathName);

		// Root Node 접근
		tinyxml2::XMLElement* pRootNode = doc.FirstChildElement("Target_Information");
		if (NULL == pRootNode)
			return;

		// 노드의 애트리뷰트 값을 얻기
		// 원하는 Node의 Element 접근 후 값 읽기
		
		// "Field"의 노드의 마지막 애트리뷰트까지 반복
    	for (tinyxml2::XMLElement* pNodeElem = pRootNode->FirstChildElement("Field");pNodeElem; pNodeElem= pNodeElem->NextSiblingElement())
		{		
			tinyxml2::XMLAttribute* pAttribute = (tinyxml2::XMLAttribute*)pNodeElem->FirstAttribute(); //현재 노드의 첫번째 애트리뷰트 값으로 이동
				
			targetInform ti;
			ti.id = pAttribute->IntValue();									// 값을 Int로 반환하여 저장

			pAttribute = (tinyxml2::XMLAttribute*)pAttribute->Next();		// 다음노드로 이동
			ti.type = pAttribute->IntValue();								// 값을 Int로 반환하여 저장

			pAttribute = (tinyxml2::XMLAttribute*)pAttribute->Next();		// 다음노드로 이동
			ti.x = pAttribute->DoubleValue();								// 값을 double로 반환하여 저장

			pAttribute = (tinyxml2::XMLAttribute*)pAttribute->Next();		// 다음노드로 이동
			ti.y = pAttribute->DoubleValue();								// 값을 double로 반환하여 저장    

			pAttribute = (tinyxml2::XMLAttribute*)pAttribute->Next();		// 다음노드로 이동
			const char* pszAttribute = pAttribute->Value();					// pszAttribute=Data

			ti.path = (CString)pszAttribute;
			tVector.push_back(ti);											// vector에 저장
		}
		ShowGrid();
  }
}


void CTargetDemoDlg::OnBnClickedButtonSave()
{

	CString str = _T("XML files(*.xml)|*.xml");
	CFileDialog dlg(false, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);
	if (IDOK == dlg.DoModal())
	{
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLDeclaration* pDecl = doc.NewDeclaration();
		doc.LinkEndChild(pDecl);

		// Root Node
		tinyxml2::XMLElement* pRootNode = doc.NewElement("Target_Information");
		doc.LinkEndChild(pRootNode);

		// child Node
		for (int i = 0; i < tVector.size(); i++)
		{
			targetInform ti;
			ti = tVector.at(i);
			tinyxml2::XMLElement* pNode =  doc.NewElement("Field");
			pRootNode->LinkEndChild(pNode);
			pNode->SetAttribute("id", ti.id);     //id
			pNode->SetAttribute("type", ti.type); //type
			pNode->SetAttribute("x", ti.x); // X (소수점)
			pNode->SetAttribute("y", ti.y); // Y (소수점)
			pNode->SetAttribute("path", (CStringA)ti.path);
		}

		// .xml 저장
		CString strSavePathName = dlg.GetPathName();
		doc.SaveFile((CStringA)strSavePathName);

	}
}




void CTargetDemoDlg::OnBnClickedButtonInput()
{
	
	UpdateData();
	VectorAdd(ti_id, ti_type, ti_x, ti_y, ti_path);
	ShowGrid();
	
}


void CTargetDemoDlg::OnBnClickedButtonClear()
{
	int nRow = m_Grid.GetFocusCell().row;
	if (nRow >= 0)
	{
		tVec_it = tVector.begin() + (nRow - 1);
		tVector.erase(tVec_it);
		m_Grid.DeleteRow(nRow);
		m_Grid.Invalidate();
	}
}

void CTargetDemoDlg::VectorAdd(int id, int type, double x, double y, CString path)
{
	targetInform ti;
	ti.id = id;
	ti.type = type;
	ti.x = x;
	ti.y = y;
	ti.path = path;
	tVector.push_back(ti);
}


void CTargetDemoDlg::ShowGrid()
{
	m_Grid.SetRowCount(tVector.size() +1);
	for (int row = 0; row < tVector.size(); row++)
	{
		targetInform ti;
		ti = tVector.at(row);
		for (int col = 0; col < m_Grid.GetColumnCount(); col++)
		{
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row + 1;
			Item.col = col;
			if (col == 0) //
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T("%d"), ti.id);
			}
			if (col == 1) //
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T("%d"), ti.type);
			}
			if (col == 2) //
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T("%f"), ti.x);
			}
			if (col == 3) //
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T("%f"), ti.y);
			}
			if (col == 4) //
			{
				Item.nFormat = DT_CENTER | DT_WORDBREAK;
				Item.strText.Format(_T("%s"), ti.path);
			}
			m_Grid.SetItem(&Item);
		}
	}
	m_Grid.Invalidate();
}