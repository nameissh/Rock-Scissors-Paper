
// FinalProject01Dlg.cpp: 구현 파일
//


#include "framework.h"
#include "FinalProject01.h"
#include "FinalProject01Dlg.h"
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


// CFinalProject01Dlg 대화 상자



CFinalProject01Dlg::CFinalProject01Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINALPROJECT01_DIALOG, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFinalProject01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture, m_picture);
	DDX_Control(pDX, IDC_EDIT1, m_box1);
	DDX_Control(pDX, IDC_EDIT2, m_box2);
}

BEGIN_MESSAGE_MAP(CFinalProject01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CFinalProject01Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFinalProject01Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFinalProject01Dlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT2, &CFinalProject01Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &CFinalProject01Dlg::OnEnChangeEdit1)
	ON_MESSAGE(WM_MYRECEIVE, &CFinalProject01Dlg::OnReceive)
END_MESSAGE_MAP()


// CFinalProject01Dlg 메시지 처리기

BOOL CFinalProject01Dlg::OnInitDialog()
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



	capture = new VideoCapture(0);

	if (!capture->isOpened())
	{
		MessageBox(_T("웹캠을 열수 없습니다. \n"));
	}  

	capture->set(CAP_PROP_FRAME_WIDTH, 320);																	// 웹캠 크기를  320x240으로 지정  
	capture->set(CAP_PROP_FRAME_HEIGHT, 240);

	SetTimer(1000, 30, NULL);

	m_comm = new CSerialComm(_T("\\\\.\\COM5"), _T("115200"), _T("None"), _T("8 Bit"), _T("1 Bit"));          // initial Comm port
	if (m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
	{
		;
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFinalProject01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFinalProject01Dlg::OnPaint()
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
HCURSOR CFinalProject01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CFinalProject01Dlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	((CSerialComm*)lpara)->HandleClose();
	delete ((CSerialComm*)lpara);

	return 0;
}


LRESULT CFinalProject01Dlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str;

	char* data = new char[length + 1];
	if (m_comm)
	{
		m_comm->Receive(data, length);																	// Length 길이만큼 데이터 받음.
		data[length] = _T('\0');
		str += _T("\r\n");

		str = CString(data);
		m_box1.SetWindowTextW(str);																		// m_box1 = CEdit, str을 바로 m_box1에 출력해줌

		str = "";
		m_box1.LineScroll(m_box1.GetLineCount());
	}
	delete data;

	return 0;
}


void CFinalProject01Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CFinalProject01Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
 
	capture->read(frame);																				// mat_frame = 입력 이미지

	//cvtColor(frame, frame, COLOR_BGR2GRAY);															// grayscale 이미지로 변환, 컬러영상을 띄우려면 주석 처리

	cvtColor(frame, hsv_frame, COLOR_BGR2HSV);

	Mat yellow_mask, yellow_frame;
	inRange(hsv_frame, lowery, uppery, yellow_mask);													// src_hsv 영상에서 HSV 색 성분 범위가 lowerb에서 upperb 사이인 위치의 픽셀만 흰색으로 설정한 mask 영상 생성
	bitwise_and(frame, hsv_frame, yellow_frame, yellow_mask);											// frame + hsv_frame + yellow_mask = yellow_frame

	Mat red_mask, red_frame;
	inRange(hsv_frame, lowerr, upperr, red_mask);
	bitwise_and(frame, frame, red_frame, red_mask);														// frame + hsv_frame + red_mask = red_frame

	Mat labels, stats, centroids;
	int cnt1 = connectedComponentsWithStats(yellow_mask, labels, stats, centroids);						// 전체 레이블 개수로 return, cnt = labels - 1
	int cnt2 = connectedComponentsWithStats(red_mask, labels, stats, centroids);

	int rock = 0;
	int scissors = 0;
	int paper = 0;
	int num_yellow = cnt1 - 1;
	int num_red = cnt2 - 1;

	String text;

	if (num_red > 0)																					// 빨간색 스티커가 0개보다 많으면 (1개)
		text = "Rock!";

	else if (num_yellow == 2)
		text = "Scissors!";

	else if (num_yellow == 5)
		text = "Paper!";

	putText(frame, text, Point(20, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);


	int bpp = 8 * frame.elemSize();																		// 화면에 보여주기 위한 처리
	assert((bpp == 8 || bpp == 24 || bpp == 32));

	int padding = 0;

	if (bpp < 32)																						// DWORD 정렬: 32비트 이미지 → 각 픽셀에 4바이트 필요
	{
		padding = 4 - (frame.cols % 4);
	}

	if (padding == 4)
		padding = 0;

	int border = 0;

	if (bpp < 32)																						// DWORD 정렬: 32비트 이미지 → 각 픽셀에 4바이트 필요
	{
		border = 4 - (frame.cols % 4);
	}

	Mat temp;

	if (border > 0 || frame.isContinuous() == false)
	{
		cv::copyMakeBorder(frame, temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);						// 오른쪽에 최대 3픽셀의 필요한 열 추가
	}

	else
	{
		temp = frame;
	}

	RECT r;
	m_picture.GetClientRect(&r);
	cv::Size winSize(r.right, r.bottom);

	cimage_mfc.Create(winSize.width, winSize.height, 24);

	BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	bitInfo->bmiHeader.biBitCount = bpp;
	bitInfo->bmiHeader.biWidth = temp.cols;
	bitInfo->bmiHeader.biHeight = -temp.rows;
	bitInfo->bmiHeader.biPlanes = 1;
	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo->bmiHeader.biCompression = BI_RGB;
	bitInfo->bmiHeader.biClrImportant = 0;
	bitInfo->bmiHeader.biClrUsed = 0;
	bitInfo->bmiHeader.biSizeImage = 0;
	bitInfo->bmiHeader.biXPelsPerMeter = 0;
	bitInfo->bmiHeader.biYPelsPerMeter = 0;

	if (bpp == 8)																						// grayscale인 경우 팔레트 필요
	{
		RGBQUAD* palette = bitInfo->bmiColors;
		for (int i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}

	if (temp.cols == winSize.width && temp.rows == winSize.height)										// 영상이 대상 사각형과 사이즈가 다름, 전체 사각형에서 스트레치 사용
	{																									// src와 dst는 같은 사이즈, 전송 메모리 블록, 여기에 최대 3픽셀의 너비의 패딩 테두리 표시
		SetDIBitsToDevice(cimage_mfc.GetDC(),															// 대상 사각형
			0, 0, winSize.width, winSize.height,
			0, 0, 0, temp.rows,
			temp.data, bitInfo, DIB_RGB_COLORS);
	}

	else
	{
		int destx = 0, desty = 0;																		// 대상 사각형
		int destw = winSize.width;
		int desth = winSize.height;

		int imgx = 0, imgy = 0;																			// src 비트맵에 정의된 사각형, mat_temp.cols 대신 너비를 사용하면 패딩 테두리가 무시됨
		int imgWidth = temp.cols - border;
		int imgHeight = temp.rows;

		StretchDIBits(cimage_mfc.GetDC(),
			destx, desty, destw, desth,
			imgx, imgy, imgWidth, imgHeight,
			temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
	}

	HDC dc = ::GetDC(m_picture.m_hWnd);
	cimage_mfc.BitBlt(dc, 0, 0);

	::ReleaseDC(m_picture.m_hWnd, dc);

	cimage_mfc.ReleaseDC();
	cimage_mfc.Destroy();

	CDialogEx::OnTimer(nIDEvent);
}


void CFinalProject01Dlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.



	CString str;

	str = _T("S");

	m_comm->Send(str, str.GetLength());
}


void CFinalProject01Dlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str;

	str = _T("N");

	m_comm->Send(str, str.GetLength());
}


void CFinalProject01Dlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str;

	str = _T("B");

	m_comm->Send(str, str.GetLength());
}


void CFinalProject01Dlg::OnEnChangeEdit1()																								// computer
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CFinalProject01Dlg::OnEnChangeEdit2()																								// score
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}