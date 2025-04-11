
// WindmillTestDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "WindmillTest.h"
#include "WindmillTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// CWindmillTestDlg ダイアログ



CWindmillTestDlg::CWindmillTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINDMILLTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWindmillTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWindmillTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_IMG_DIR, &CWindmillTestDlg::OnBnClickedButtonImgDir)
	ON_BN_CLICKED(IDC_BUTTON_BEFORE, &CWindmillTestDlg::OnBnClickedButtonBefore)
	ON_BN_CLICKED(IDC_BUTTON_FORWORD, &CWindmillTestDlg::OnBnClickedButtonForword)
	ON_BN_CLICKED(IDOK, &CWindmillTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWindmillTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_MOVIE_OUTPUT, &CWindmillTestDlg::OnBnClickedCheckMovieOutput)
	ON_BN_CLICKED(IDC_BUTTON_MOVIE_FILE, &CWindmillTestDlg::OnBnClickedButtonMovieFile)
END_MESSAGE_MAP()


// CWindmillTestDlg メッセージ ハンドラー

BOOL CWindmillTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	GetDlgItem(IDC_BUTTON_BEFORE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_FORWORD)->EnableWindow(FALSE);
#if 0
	int num = cv::getNumberOfCPUs();
	int thlead = cv::getNumThreads();
	int i = cv::getThreadNum();
#endif

	if (pSaveParent != NULL)
	{
		strInfilePath = pSaveParent->m_pszProfileName;
	}
	else
	{
		TCHAR crDir[MAX_PATH + 1];
		TCHAR drive[MAX_PATH + 1];
		TCHAR dir[MAX_PATH + 1];
		TCHAR fname[MAX_PATH + 1];
		TCHAR ext[MAX_PATH + 1];
		GetModuleFileName(NULL,crDir,MAX_PATH + 1);

		// ファイルパスを分割
		::_wsplitpath_s(crDir, drive, dir, fname, ext);
		// ドライブとディレクトリ名を結合して実行ファイルパス+iniファイルとする
		swprintf(crDir, MAX_PATH, _T("%s%sCWindmillTest.ini"), drive, dir);

		strInfilePath = crDir;
	}

	int nValue = ::GetPrivateProfileInt(L"Setting", L"SaveMovie", 0, strInfilePath);

	((CButton*)GetDlgItem(IDC_CHECK_MOVIE_OUTPUT))->SetCheck(nValue);
	if(nValue == 1)
	{
		GetDlgItem(IDC_BUTTON_MOVIE_FILE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_OUTPUT_DIR)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MOVIE_FILE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OUTPUT_DIR)->EnableWindow(FALSE);
	}

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CWindmillTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CWindmillTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (reDraw)
		{
			reDraw = false;

//			CStatic* pictureB = (CStatic*)GetDlgItem(IDC__MAIN_IMG);
//			pictureB->SetBitmap(cimg[current_img_pos]);
	//StretchBltで描画領域に合わせてリサイズ
#if 0
			CDC* cdc;

			cdc = GetDlgItem(IDC__MAIN_IMG)->GetDC();

			CDC bmpDC;
			CBitmap* cbmp;
			cbmp = CBitmap::FromHandle(cimg[current_img_pos]);
			bmpDC.CreateCompatibleDC(cdc);
			CBitmap* oldbmp = bmpDC.SelectObject(cbmp);
			//伸縮すると画像が汚くなるので伸縮モードを指定
			//詳細はMSDN参照
			cdc->SetStretchBltMode(STRETCH_HALFTONE);
			//ブラシのずれを防止するためSetBrushOrgExを呼び出す
			cdc->SetBrushOrg(0, 0);
			//画像を伸縮してピクチャーボックスに表示
			//詳細はMSDN参照
			cdc->StretchBlt(0, 0, iWidth, iHeight, &bmpDC, 0, 0, cimg[current_img_pos].GetWidth(), cimg[current_img_pos].GetHeight(), SRCCOPY);
			bmpDC.SelectObject(oldbmp);
			//後片付け
			cbmp->DeleteObject();
			bmpDC.DeleteDC();
			ReleaseDC(cdc);
#endif
//			StretchBlt(DispMain.GetDC(), 0, 0, iWidth, iHeight, cimg[current_img_pos].GetDC(), 0, 0, cimg[current_img_pos].GetWidth(), cimg[current_img_pos].GetHeight(),  SRCCOPY);
#if 1	
			CStatic* pictureB = (CStatic*)GetDlgItem(IDC__MAIN_IMG);
			pictureB->SetBitmap(DispMain);
			pictureB = (CStatic*)GetDlgItem(IDC_GRAY_IMG);
			pictureB->SetBitmap(DispGray);
			pictureB = (CStatic*)GetDlgItem(IDC_1BIT_IMG);
			pictureB->SetBitmap(Disp1Bit);
			pictureB = (CStatic*)GetDlgItem(IDC_1BIT_DIFF_IMG1);
			pictureB->SetBitmap(Disp1BitDiff1);
			pictureB = (CStatic*)GetDlgItem(IDC_1BIT_DIFF_IMG2);
			pictureB->SetBitmap(Disp1BitDiff2);
			pictureB = (CStatic*)GetDlgItem(IDC_1BIT_DIFF_IMG3);
			pictureB->SetBitmap(Disp1BitDiff);
			pictureB = (CStatic*)GetDlgItem(IDC_1BIT_DETECT_IMG);
			pictureB->SetBitmap(DispDraft);
#endif
		}

		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CWindmillTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWindmillTestDlg::OnBnClickedButtonImgDir()
{
	CFileDialog dlg(TRUE, _T(""), _T(""), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, 
		_T("JPEGファイル(*.jpg;*.JPG)|*.jpg;*.JPG|")
		_T("MP4ファイル(*.mp4;*.MP4)|*.mp4;*.MP4|")
		_T("すべてのファイル(*.*)|*.*||")
		, this);

	if (dlg.DoModal() == IDOK)
	{
		CString fullPathName = dlg.GetPathName();
		CString	fullPathCheck;

		if (PathFileExists(fullPathName))
		{
			current_img_pos = 0;
			current_fram_counter = 0;
			SetDlgItemText(IDC_EDIT_INPUT_DIR, fullPathName);
			//current_img_dir = 
			TCHAR s[_MAX_PATH];
			TCHAR drive[_MAX_DRIVE];
			TCHAR dir[_MAX_DIR];
			TCHAR file[_MAX_FNAME];
			TCHAR file_num[_MAX_FNAME];
			TCHAR ext[_MAX_EXT];
			::_wsplitpath_s(fullPathName, drive, dir, file,ext);

			if ((_tcscmp(ext, _T(".MP4")) == 0) ||
				(_tcscmp(ext, _T(".mp4")) == 0))
			{
				readMP4 = true;
				MovieInputFullPathName = fullPathName;
				GetDlgItem(IDC_BUTTON_BEFORE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_FORWORD)->EnableWindow(FALSE);
			}
			else
			{
				readMP4 = false;
				CString file_name;
				file_name.Format(_T("%s%s"),file,ext);
				SetDlgItemText(IDC_STATIC_CURRENT_FRAME, file_name);

				bool file_name_text = false;
				current_img_digits = 0;
				int i = 0;
				int j = 0;
				int pos = 0;
				for (i = wcslen(file) - 1; i >= 0; i--)
				{
					if ((file[i] < '0')||(file[i] > '9'))
					{
						file_name_text = true;
						pos = i + 1;
						break;
					}
					current_img_digits++;
				}
				for (i = pos,j = 0;i < wcslen(file);i++,j++)
				{
					file_num[j] = file[i];
				}
				file_num[j] = NULL;
				current_img_counter = _wtoi(file_num);
				file[pos] = NULL;

				current_img_dir.Format(_T("%s%s"), drive,dir);
				current_file_name.Format(_T("%s"), file);
				current_file_ext.Format(_T("%s"), ext);

				current_format.Format(_T("%s%%0%dd%s"), file, current_img_digits, ext);

				if (current_img_counter > 0)
				{
					current_file.Format(current_format, current_img_counter - 1);

					fullPathCheck.Format(_T("%s%s"), current_img_dir, current_file);
					if (PathFileExists(fullPathCheck))
					{
						GetDlgItem(IDC_BUTTON_BEFORE)->EnableWindow(TRUE);
					}
					else
					{
						GetDlgItem(IDC_BUTTON_BEFORE)->EnableWindow(FALSE);
					}
				}

				current_file.Format(current_format, current_img_counter + 1);
				fullPathCheck.Format(_T("%s%s"), current_img_dir, current_file);
				if (PathFileExists(fullPathCheck))
				{
					GetDlgItem(IDC_BUTTON_FORWORD)->EnableWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_BUTTON_FORWORD)->EnableWindow(FALSE);
				}
				LoadImageFile(fullPathName);
			}


			for (int i = 0; i < 3; i++)
			{
				if (!binary[i].empty())
				{
					binary[i].release();
				}
			}
		}
	}
}

void CWindmillTestDlg::OnBnClickedCheckMovieOutput()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	if(((CButton*)GetDlgItem(IDC_CHECK_MOVIE_OUTPUT))->GetCheck())
	{
		GetDlgItem(IDC_BUTTON_MOVIE_FILE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_OUTPUT_DIR)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MOVIE_FILE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_OUTPUT_DIR)->EnableWindow(FALSE);
	}
}

void CWindmillTestDlg::OnBnClickedButtonMovieFile()
{
	CFileDialog dlg(FALSE, _T(""), _T(""), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("MP4ファイル(*.mp4;*.MP4)|*.mp4;*.MP4|")
		_T("すべてのファイル(*.*)|*.*||")
		, this);

	if (dlg.DoModal() == IDOK)
	{
		MovieFullPathName = dlg.GetPathName();

		if (!PathFileExists(MovieFullPathName))
		{
			SetDlgItemText(IDC_EDIT_OUTPUT_DIR, MovieFullPathName);
		}
	}
}

void CWindmillTestDlg::OnBnClickedButtonBefore()
{
#if 1
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CString	fullPathCheck;

	if (current_img_counter > 0)
	{
		current_file.Format(current_format, current_img_counter - 1);

		fullPathCheck.Format(_T("%s%s"), current_img_dir, current_file);
		if (PathFileExists(fullPathCheck))
		{
			SetDlgItemText(IDC_STATIC_CURRENT_FRAME, current_file);
			if (current_img_pos > 0)
			{
				current_img_pos--;
			}
			else
			{
				current_img_pos = 2;
			}
			current_fram_counter--;
			LoadImageFile(fullPathCheck);
			current_img_counter--;
			current_file.Format(current_format, current_img_counter - 1);

			fullPathCheck.Format(_T("%s%s"), current_img_dir, current_file);
			if (PathFileExists(fullPathCheck))
			{
				GetDlgItem(IDC_BUTTON_BEFORE)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_BUTTON_BEFORE)->EnableWindow(FALSE);
			}
			GetDlgItem(IDC_BUTTON_FORWORD)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_BEFORE)->EnableWindow(FALSE);
		}
	}
	else
	{
		GetDlgItem(IDC_BUTTON_BEFORE)->EnableWindow(FALSE);
	}
#endif
}


void CWindmillTestDlg::OnBnClickedButtonForword()
{
#if 1
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CString	fullPathCheck;

	current_file.Format(current_format, current_img_counter + 1);
	fullPathCheck.Format(_T("%s%s"), current_img_dir, current_file);
	if (PathFileExists(fullPathCheck))
	{
		SetDlgItemText(IDC_STATIC_CURRENT_FRAME, current_file);
		current_img_pos++;
		if (current_img_pos >= 3)
		{
			current_img_pos = 0;
		}
		current_fram_counter++;
		LoadImageFile(fullPathCheck);

		DiffImage(current_img_pos);
		POINT center, left, right;
		GetMaxLabelPositon(center, left, right);

		cv::circle(DraftImage, cv::Point(center.x, center.y), 300, (255, 0, 0), 5);

		UpdateDraff();

		current_img_counter++;

		current_file.Format(current_format, current_img_counter + 1);
		fullPathCheck.Format(_T("%s%s"), current_img_dir, current_file);
		if (PathFileExists(fullPathCheck))
		{
			GetDlgItem(IDC_BUTTON_FORWORD)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_FORWORD)->EnableWindow(FALSE);
		}
		GetDlgItem(IDC_BUTTON_BEFORE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_FORWORD)->EnableWindow(FALSE);
	}
#endif
}

void	CWindmillTestDlg::LoadImageFile(CString file_name)
{
#if 1

	if (!cimg[current_img_pos].IsNull())
	{
		cimg[current_img_pos].Detach();
		cimg[current_img_pos].Destroy();
	}
	cimg[current_img_pos].Load(file_name);
	int width = cimg[current_img_pos].GetWidth();
	int height = cimg[current_img_pos].GetHeight();

#if 0
	if (!cDraft.IsNull())
	{
		cDraft.Detach();
		cDraft.Destroy();
	}
	cDraft = cimg[current_img_pos];

	if (!cGray[current_img_pos].IsNull())
	{
		cGray[current_img_pos].Detach();
		cGray[current_img_pos].Destroy();
	}
	cGray[current_img_pos].Create(width, height, 32);

	if (!c2Bit[current_img_pos].IsNull())
	{
		c2Bit[current_img_pos].Detach();
		c2Bit[current_img_pos].Destroy();
	}
	c2Bit[current_img_pos].Create(width, height, 32);
#endif

	int w, h;
#if 1
	// 表示サイズを決定する.
	h = 60;
	w = (int)((double)h * ((double)width / (double)height));

	if (!DispMain.IsNull())
	{
		DispMain.Detach();
		DispMain.Destroy();
	}
	DispMain.Create(w, h, cimg[current_img_pos].GetBPP(), 0);
	iWidth = width;
	iHeight = height;
//	iWidth = w;
//	iHeight = h;

	if (!DispGray.IsNull())
	{
		DispGray.Detach();
		DispGray.Destroy();
	}
	DispGray.Create(w, h, cimg[current_img_pos].GetBPP(), 0);

	if (!DispDraft.IsNull())
	{
		DispDraft.Detach();
		DispDraft.Destroy();
	}
	DispDraft.Create(3*w, 3*h, cimg[current_img_pos].GetBPP(), 0);

	if (!Disp1Bit.IsNull())
	{
		Disp1Bit.Detach();
		Disp1Bit.Destroy();
	}
	Disp1Bit.Create(w, h, cimg[current_img_pos].GetBPP(), 0);

	if (!Disp1BitDiff1.IsNull())
	{
		Disp1BitDiff1.Detach();
		Disp1BitDiff1.Destroy();
	}
	Disp1BitDiff1.Create(w, h, cimg[current_img_pos].GetBPP(), 0);
	if (!Disp1BitDiff2.IsNull())
	{
		Disp1BitDiff2.Detach();
		Disp1BitDiff2.Destroy();
	}
	Disp1BitDiff2.Create(w, h, cimg[current_img_pos].GetBPP(), 0);
	if (!Disp1BitDiff.IsNull())
	{
		Disp1BitDiff.Detach();
		Disp1BitDiff.Destroy();
	}
	Disp1BitDiff.Create(w, h, cimg[current_img_pos].GetBPP(), 0);

	Gray2BitImage(current_img_pos, DispGray, Disp1Bit);
//	MatToCImage(DraftImage, cDraft);
//	UpdateDraff();

	HDC	hDC_Dst = DispMain.GetDC();
	HDC	hDC_Src = cimg[current_img_pos].GetDC();
	StretchBlt(hDC_Dst, 0, 0, w, h, hDC_Src, 0, 0, cimg[current_img_pos].GetWidth(), cimg[current_img_pos].GetHeight(), SRCCOPY);
	DispMain.ReleaseDC();
	cimg[current_img_pos].ReleaseDC();
#if 0
	hDC_Dst = DispGray.GetDC();
	hDC_Src = cGray[current_img_pos].GetDC();
	StretchBlt(hDC_Dst, 0, 0, w, h, hDC_Src, 0, 0, cGray[current_img_pos].GetWidth(), cGray[current_img_pos].GetHeight(), SRCCOPY);
	DispGray.ReleaseDC();
	cGray[current_img_pos].ReleaseDC();

	hDC_Dst = Disp1Bit.GetDC();
	hDC_Src = c2Bit[current_img_pos].GetDC();
	StretchBlt(hDC_Dst, 0, 0, w, h, hDC_Src, 0, 0, c2Bit[current_img_pos].GetWidth(), c2Bit[current_img_pos].GetHeight(), SRCCOPY);
	Disp1Bit.ReleaseDC();
	c2Bit[current_img_pos].ReleaseDC();
#endif
#endif
	reDraw = true;
	this->Invalidate();
#endif
}

void CWindmillTestDlg::Gray2BitImage(int pos, CImage& dstImg, CImage& dstImg2)
{
//	cv::Mat img;
	cv::Mat gray;
//	cv::Mat binary;
	cv::Mat	r_gray;
	cv::Mat	r_binary;
#if 1
	int i,x,y;
	int w, h;
	uchar r, g, b;
	size_t matPitch;
	uchar* pTmpData;
	BYTE* pImgData;

	w = cimg[pos].GetWidth();
	h = cimg[pos].GetHeight();
#if 0
	img.create(h, w, CV_8UC3);

	matPitch = img.cols * img.elemSize();
	pTmpData = img.data + (cimg[pos].GetHeight() - 1) * matPitch;
	pImgData = (BYTE*)cimg[pos].GetBits();
	for (i = 0; i < cimg[pos].GetHeight(); i++, pTmpData -= matPitch, pImgData += cimg[pos].GetPitch())
		memcpy(pTmpData, pImgData, matPitch);
#endif

	if (!DraftImage.empty())
	{
		DraftImage.release();
	}
	DraftImage = NewImage.clone();

	CImageToMat(cimg[pos], NewImage);

	cv::cvtColor(NewImage, gray, cv::COLOR_BGR2GRAY);

	if (!binary[pos].empty())
	{
		binary[pos].release();
	}
	cv::threshold(gray, binary[pos], 0, 255, cv::THRESH_OTSU);
#if 0
	int g_width = gray.cols;
	int g_height = gray.rows;
	int g_channels = gray.channels();

	int b_width = binary.cols;
	int b_height = binary.rows;
	int b_channels = binary.channels();
#endif
	double w_rate, h_rate;

	w_rate = (double)dstImg.GetWidth() / (double)w;
	h_rate = (double)dstImg.GetHeight() / (double)h;

	cv::resize(gray, r_gray, cv::Size(), w_rate, h_rate);
//	imshow("gray", r_gray);
	cv::resize(binary[pos], r_binary, cv::Size(), w_rate, h_rate);
//	imshow("binary", r_binary);

#if 1
	int g_width = r_gray.cols;
	int g_height = r_gray.rows;
	int g_channels = r_gray.channels();

	int b_width = r_binary.cols;
	int b_height = r_binary.rows;
	int b_channels = r_binary.channels();
#endif
	w = dstImg.GetWidth();
	h = dstImg.GetHeight();

	if (w > g_width)
	{
		w = g_width;
	}
	if (w > b_width)
	{
		w = b_width;
	}
	if (h > g_height)
	{
		h = g_height;
	}
	if (h > b_height)
	{
		h = b_height;
	}

	for (y = 0;y < h;y++)
	{
		for (x = 0;x < w;x++)
		{
			r = r_gray.at<uchar>(y, x);
			g = b = r;
//			dstImg.SetPixel(x, dstImg.GetHeight() - y -1, RGB(r, g, b));
			dstImg.SetPixel(x, y, RGB(r, g, b));
			r = r_binary.at<uchar>(y, x);
			g = b = r;
//			dstImg2.SetPixel(x, dstImg2.GetHeight() - y - 1, RGB(r, g, b));
			dstImg2.SetPixel(x, y, RGB(r, g, b));
		}
	}
#endif

#if 0
	resize(img, img, cv::Size(), 0.1, 0.1);
	imshow("img", img);
	resize(gray, gray, cv::Size(), 0.1, 0.1);
	imshow("gray", gray);
	resize(binary, binary, cv::Size(), 0.1, 0.1);
	imshow("binary", binary);
#endif
//	img.release();
	gray.release();
//	binary.release();
	r_gray.release();
	r_binary.release();
}

void CWindmillTestDlg::CImageToMat(CImage& img, Mat& mat)
{
	size_t matPitch;
	uchar* pTmpData;
	BYTE* pImgData;

	if (img.IsNull())
	{
		return;
	}

	if (!mat.empty())
	{
		mat.release();
	}

	mat.create(img.GetHeight(), img.GetWidth(), CV_8UC3);
#if 1
	matPitch = mat.cols * mat.elemSize();
	pTmpData = mat.data;
	pImgData = (BYTE*)img.GetBits();
	for (int i = 0; i < img.GetHeight(); i++, pTmpData += matPitch, pImgData += img.GetPitch())
		memcpy(pTmpData, pImgData, matPitch);
#else
	matPitch = mat.cols * mat.elemSize();
	pTmpData = mat.data + (img.GetHeight() - 1) * matPitch;
	pImgData = (BYTE*)img.GetBits();
	for (int i = 0; i < img.GetHeight(); i++, pTmpData -= matPitch, pImgData += img.GetPitch())
		memcpy(pTmpData, pImgData, matPitch);
#endif

//	cv::Mat check;
//	cv::resize(mat, check, cv::Size(), 0.2, 0.2);
//	imshow("input image",check);
}

void CWindmillTestDlg::MatToCImage(Mat& mat, CImage& img)
{
	if (mat.empty())
	{
		return;
	}

	if (!img.IsNull())
	{
		img.Detach();
		img.Destroy();
	}

	img.Create(mat.cols, mat.rows, 32, 0);

	for (int y = 0; y < mat.rows; y++) {
		for (int x = 0; x < mat.cols; x++) {
			uchar r, g, b;

			b = mat.at<cv::Vec3b>(y, x)[0];
			g = mat.at<cv::Vec3b>(y, x)[1];
			r = mat.at<cv::Vec3b>(y, x)[2];

			img.SetPixel(x, y, RGB(r, g, b));
		}
	}
}

void CWindmillTestDlg::drawAxis(cv::Mat& img, cv::Point p, cv::Point q, cv::Scalar colour, const float scale, int thickness)
{
	double angle = atan2((double)p.y - q.y, (double)p.x - q.x); // angle in radians
	double hypotenuse = sqrt((double)(p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x));
	// Here we lengthen the arrow by a factor of scale
	q.x = (int)(p.x - scale * hypotenuse * cos(angle));
	q.y = (int)(p.y - scale * hypotenuse * sin(angle));
	cv::line(img, p, q, colour, thickness, cv::LINE_AA);
	// create the arrow hooks
	p.x = (int)(q.x + 9 * cos(angle + CV_PI / 4));
	p.y = (int)(q.y + 9 * sin(angle + CV_PI / 4));
	cv::line(img, p, q, colour, thickness, cv::LINE_AA);
	p.x = (int)(q.x + 9 * cos(angle - CV_PI / 4));
	p.y = (int)(q.y + 9 * sin(angle - CV_PI / 4));
	cv::line(img, p, q, colour, thickness, cv::LINE_AA);
}

void CWindmillTestDlg::DiffImage(int pos)
{
	int t0,t1,t2;

	if (pos == 0)
	{
		t0 = 1;
		t1 = 2;
		t2 = 0;
	}
	else
	{
		t1 = pos - 1;
		if (t1 == 0)
		{
			t0 = 2;
			t2 = 1;
		}
		else
		{
			t0 = t1 - 1;
			if (t1 == 2)
			{
				t2 = 0;
			}
			else {
				t2 = t1 + 1;
			}
		}
	}
	if ((binary[t0].empty()) ||
		(binary[t1].empty())||
		(binary[t2].empty()))
	{
		return;
	}
	if (!diff1.empty())
	{
		diff1.release();
	}
	if (!diff2.empty())
	{
		diff2.release();
	}
	if (!diff.empty())
	{
		diff.release();
	}
	cv::absdiff(binary[t0], binary[t1], diff1);
	cv::absdiff(binary[t1], binary[t2], diff2);
	cv::bitwise_and(diff1, diff2, diff);

	// 輪郭を検出します。
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(diff, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

//	CImageToMat(cDraft, DraftImage);
	size_t	max_pos = 0;
	double max_area = 0.0;
	for (size_t i = 0; i < contours.size(); i++) {

		// 面積が小さすぎる場合と多きすぎる場合を除外します。
		double area = cv::contourArea(contours[i]);
		if (area < 1e2 || 1e5 < area) {
			continue;
		}
		// 輪郭を描画します。
		cv::drawContours(DraftImage, contours, i, cv::Scalar(0, 0, 255), 2);
		// 各輪郭について、それぞれ方向を検出します。
//		getOrientation(contours[i], diff);
		if (max_area < area)
		{
			max_area	= area;
			max_pos = i;
		}
	}


#if 1
	if (max_pos != 0)
	{
		cv::Mat destination;
		bitwise_not(diff, destination);


		// 主成分分析のために、対象となる輪郭のみを別のバッファにコピーします。
		cv::Mat data_pts = cv::Mat(contours[max_pos].size(), 2, CV_64F); // [pts.size() x 2] 行列
		for (int i = 0; i < data_pts.rows; i++) {
			data_pts.at<double>(i, 0) = contours[max_pos][i].x;
			data_pts.at<double>(i, 1) = contours[max_pos][i].y;
		}

		// 主成分分析の実行
		cv::PCA pca_analysis(data_pts, cv::Mat(), cv::PCA::DATA_AS_ROW);

		// [分析結果] 中心の座標
		cv::Point cntr = cv::Point(pca_analysis.mean.at<double>(0, 0),
			pca_analysis.mean.at<double>(0, 1));

		// [分析結果] 固有値と固有ベクトル
		std::vector<cv::Point2d> eigen_vecs(2);
		std::vector<double> eigen_val(2);
		for (int i = 0; i < 2; i++) {
			eigen_vecs[i] = cv::Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
				pca_analysis.eigenvectors.at<double>(i, 1));
			eigen_val[i] = pca_analysis.eigenvalues.at<double>(i);
		}

		cv::Point p1 = cntr + 0.02 * cv::Point(eigen_vecs[0].x * eigen_val[0], eigen_vecs[0].y * eigen_val[0]);
		cv::Point p2 = cntr - 0.02 * cv::Point(eigen_vecs[1].x * eigen_val[1], eigen_vecs[1].y * eigen_val[1]);

		drawAxis(diff, cntr, p1, cv::Scalar(0, 255, 0), 1);
		drawAxis(diff, cntr, p2, cv::Scalar(255, 255, 0), 5);
		drawAxis(DraftImage, cntr, p1, cv::Scalar(0, 255, 0), 1,3);
		drawAxis(DraftImage, cntr, p2, cv::Scalar(255, 255, 0), 1,3);

		blade_center[blade_current] = cntr;
		blade_top[blade_current] = p1;
		blade_new = blade_current;
		blade_current++;
		if (blade_current >= 5)
		{
			blade_current = 0;
		}
		POINT center;
		GetTurnCenter(center);
		if ((center.x < iWidth)&&(center.x != 0))
		{
			cv::circle(DraftImage, cv::Point(center.x, center.y), 100, (0, 0, 255), 5);
		}
	}
#endif

	cv::Mat	r_binary1;
	cv::Mat	r_binary2;
	cv::Mat	r_binary;
	double w_rate, h_rate;
	int i, x, y;
	int w, h;
	uchar r, g, b;

	w = diff.cols;
	h = diff.rows;

//	cv::Mat	check_DraftImage;
//	cv::resize(DraftImage, check_DraftImage, cv::Size(), 0.2, 0.2);
//	imshow("Black&White", check_DraftImage);

	w_rate = (double)Disp1BitDiff.GetWidth() / (double)w;
	h_rate = (double)Disp1BitDiff.GetHeight() / (double)h;
	cv::resize(diff1, r_binary1, cv::Size(), w_rate, h_rate);
	cv::resize(diff2, r_binary2, cv::Size(), w_rate, h_rate);
	cv::resize(diff, r_binary, cv::Size(), w_rate, h_rate);

	int b_width = r_binary.cols;
	int b_height = r_binary.rows;
	int b_channels = r_binary.channels();

	w = Disp1BitDiff.GetWidth();
	h = Disp1BitDiff.GetHeight();

	if (w > b_width)
	{
		w = b_width;
	}
	if (h > b_height)
	{
		h = b_height;
	}

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
		{
			r = r_binary1.at<uchar>(y, x);
			g = b = r;
//			Disp1BitDiff1.SetPixel(x, Disp1BitDiff1.GetHeight() - y - 1, RGB(r, g, b));
			Disp1BitDiff1.SetPixel(x, y, RGB(r, g, b));

			r = r_binary2.at<uchar>(y, x);
			g = b = r;
//			Disp1BitDiff2.SetPixel(x, Disp1BitDiff2.GetHeight() - y - 1, RGB(r, g, b));
			Disp1BitDiff2.SetPixel(x, y, RGB(r, g, b));

			r = r_binary.at<uchar>(y, x);
			g = b = r;
//			Disp1BitDiff.SetPixel(x, Disp1BitDiff.GetHeight() - y - 1, RGB(r, g, b));
			Disp1BitDiff.SetPixel(x,  y, RGB(r, g, b));
		}
	}

	r_binary1.release();
	r_binary2.release();
	r_binary.release();
}

void CWindmillTestDlg::GetMaxLabelPositon(POINT& center, POINT& left, POINT& right)
{
	if (diff.empty())
	{
		return;
	}
	//ラべリング処理
	cv::Mat LabelImg;
	cv::Mat stats;
	cv::Mat centroids;
	int nLab = cv::connectedComponentsWithStats(diff, LabelImg, stats, centroids);

	int i;
	int max;
	int pos;

	Rect basicRect = Rect(0, 0, diff.cols, diff.rows);
	Rect getRectangle;
	bool ifDrawingBox = false;

	for (i = 1, max = 0,pos = 0;i < nLab;i++)
	{
		if (max < stats.at<int>(i, CC_STAT_AREA))
		{
			max = stats.at<int>(i, CC_STAT_AREA);
			pos = i;
		}
	}

	if (max < 500)
	{
		left.x = 0;
		left.y = 0;
		right.x = 0;
		right.y = 0;
		center.x = 0;
		center.y = 0;
	}
	else
	{
		left.x = stats.at<int>(pos, CC_STAT_LEFT);
		left.y = stats.at<int>(pos, CC_STAT_TOP);
		right.x = left.x + stats.at<int>(pos, CC_STAT_WIDTH);
		right.y = left.y + stats.at<int>(pos, CC_STAT_HEIGHT);
		center.x = (left.x + right.x)>>1;
		center.y = (left.y + right.y) >> 1;
	}
#if 0
	for (int i = 1; i < nLab; i++)
	{
		ifDrawingBox = false;

		// Extend the bounding box of connected component for easier recognition
		if (stats.at<int>(i - 1, CC_STAT_AREA) > 80 && stats.at<int>(i - 1, CC_STAT_AREA) < 3000)
		{
			ifDrawingBox = true;
			int left = stats.at<int>(i - 1, CC_STAT_HEIGHT) / 4;
			getRectangle = Rect(stats.at<int>(i - 1, CC_STAT_LEFT) - left, stats.at<int>(i - 1, CC_STAT_TOP) - left, stats.at<int>(i - 1, CC_STAT_WIDTH) + 2 * left, stats.at<int>(i - 1, CC_STAT_HEIGHT) + 2 * left);
			getRectangle &= basicRect;
		}
		if (ifDrawingBox && !getRectangle.empty())
		{
			Mat roi = image(getRectangle);
			predictor(net, roi, classId, probability);

			if (probability < confThreshold)
				continue;

			rectangle(rawImage, getRectangle, Scalar(128, 255, 128), 2);

			position = Point(getRectangle.br().x - 7, getRectangle.br().y + 25);
			putText(rawImage, std::to_string(classId), position, 3, 1.0, Scalar(128, 128, 255), 2);
		}
	}
#endif

	LabelImg.release();
	stats.release();
	centroids.release();
}

void CWindmillTestDlg::GetTurnCenter(POINT& center)
{
	if (current_fram_counter > 6)
	{
		point a, b, c, d,cross;

		a.x = blade_center[blade_current].x;
		a.y = blade_center[blade_current].y;
		b.x = blade_top[blade_current].x;
		b.y = blade_top[blade_current].y;
		c.x = blade_center[blade_new].x;
		c.y = blade_center[blade_new].y;
		d.x = blade_top[blade_new].x;
		d.y = blade_top[blade_new].y;
		cross = Intersection(a, b,c, d);

		if ((iWidth > (int)cross.x) ||
			(iHeight > (int)cross.y))
		{
			center.x = (LONG)cross.x;
			center.y = (LONG)cross.y;
		}
		else
		{
			center.x = 0;
			center.y = 0;
		}
	}
	else
	{
		center.x = 0;
		center.y = 0;
	}
}

void CWindmillTestDlg::UpdateDraff()
{
#if 1
	cv::Mat r_img;
//	int i, x, y;
//	int w, h;
	uchar r, g, b;

//	w = DispDraft.GetWidth();
//	h = DispDraft.GetHeight();

	cv::resize(DraftImage, r_img, cv::Size(), (double)DispDraft.GetWidth() /(double)DraftImage.cols, (double)DispDraft.GetHeight() / (double)DraftImage.rows);
//	imshow("r_img", r_img);

	MatToCImage(r_img, DispDraft);

//	for (y = 0; y < h; y++)
//	{
//		for (x = 0; x < w; x++)
//		{
//			r = r_img.at<uchar>(y, x);
//			g = b = r;
//			DispDraft.SetPixel(x, y, RGB(r, g, b));
//		}
//	}
#else
	HDC	hDC_Dst = DispDraft.GetDC();
	HDC	hDC_Src = cDraft.GetDC();

	StretchBlt(hDC_Dst, 0, 0, DispDraft.GetWidth(), DispDraft.GetHeight(), hDC_Src, 0, 0, cDraft.GetWidth(), cDraft.GetHeight(), SRCCOPY);
	cDraft.ReleaseDC();
	DispDraft.ReleaseDC();
#endif
}

void CWindmillTestDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	//CDialogEx::OnOK();
	if (PathFileExists(MovieFullPathName))
	{
		if(MessageBox(_T("動画保存開始"),_T("ファイルがあります\n削除して書き込みを始めてもよいですか？"), MB_OKCANCEL | MB_ICONQUESTION)== IDNO)
		{
			return;
		}

		DeleteFile(MovieFullPathName);
	}

	cv::VideoCapture video;
	std::string input_file = "";

	input_file = CStringA(MovieInputFullPathName).GetBuffer();;

	if (readMP4)
	{
		// 動画ファイルを開く
		video.open(input_file);
		if (video.isOpened() == false) {
			// 動画ファイルが開けなかったときは終了する
			return;
		}
	}

	cv::VideoWriter writer;
	int    width, height, fourcc; // 作成する動画ファイルの設定
	fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v'); // ビデオフォーマットの指定( ISO MPEG-4 / .mp4)
	double fps;
	double w_rate = 0.1;
	double h_rate = 0.1;
	//	width = (int)video.get(cv::CAP_PROP_FRAME_WIDTH);	// フレーム横幅を取得
//	height = (int)video.get(cv::CAP_PROP_FRAME_HEIGHT);	// フレーム縦幅を取得
//	fps = video.get(cv::CAP_PROP_FPS);				// フレームレートを取得
	if (readMP4)
	{
		width = int(video.get(cv::CAP_PROP_FRAME_WIDTH));
		height = int(video.get(cv::CAP_PROP_FRAME_HEIGHT));
		fps = video.get(cv::CAP_PROP_FPS);

		w_rate = 0.2;
		h_rate = 0.2;

	}
	else
	{
		width = cimg[current_img_pos].GetWidth();
		height = cimg[current_img_pos].GetHeight();

	fps = 30.0;
	}

//	LPTSTR *file= (LPTSTR*)MovieFullPathName.GetBuffer();

//	cv::String cvfilename = "E:\\work\\トラッキングカメラ\\20230412_ジェイウインド東京湾臨海風力発電所 東京風ぐるま\\フロント画像相当\\風車_動画切り出し静止画\\test.mp4";
//	strcpy(cvfilename, file, );
	std::string cvfilename = "";
	cvfilename = CStringA(MovieFullPathName).GetBuffer();;

	if (!writer.open(cvfilename, fourcc, fps, cv::Size(width, height)))
	{
		return;
	}

#if 0
	if (readMP4)
	{
		video.release();
	}
	writer.release();
	return;
#endif







//	int frame_counter = 0;
	current_fram_counter = 0;
	current_img_pos = 0;

	while (1) {
		if (readMP4)
		{
//			if (!cimg[current_img_pos].IsNull())
//			{
//				cimg[current_img_pos].Detach();
//				cimg[current_img_pos].Destroy();
//			}
//			cimg[current_img_pos].Load(file_name);


			if (!NewImage.empty())
			{
				NewImage.release();
			}
#if 1
			video.read(NewImage);
//			if (!NewImage.empty())
//			{
//				continue;
//			}
#else
			if (!video.read(NewImage))
			{
				break;
			}
#endif
			cv::Mat gray;
			//	cv::Mat binary;
//			cv::Mat	r_gray;
//			cv::Mat	r_binary;

			int i, x, y;
			int w, h;

			h = NewImage.cols;
			w = NewImage.rows;

			if ((h == 0) && (w == 0))
			{
				break;
			}

			iWidth = h;
			iHeight = w;


			cv::cvtColor(NewImage, gray, cv::COLOR_BGR2GRAY);

			if (!binary[current_img_pos].empty())
			{
				binary[current_img_pos].release();
			}
			cv::threshold(gray, binary[current_img_pos], 0, 255, cv::THRESH_OTSU);
#if 0
			int g_width = gray.cols;
			int g_height = gray.rows;
			int g_channels = gray.channels();

			int b_width = binary.cols;
			int b_height = binary.rows;
			int b_channels = binary.channels();
			double w_rate, h_rate;

			w_rate = (double)dstImg.GetWidth() / (double)w;
			h_rate = (double)dstImg.GetHeight() / (double)h;

			cv::resize(gray, r_gray, cv::Size(), w_rate, h_rate);
			//	imshow("gray", r_gray);
			cv::resize(binary[pos], r_binary, cv::Size(), w_rate, h_rate);
			//	imshow("binary", r_binary);


			int g_width = r_gray.cols;
			int g_height = r_gray.rows;
			int g_channels = r_gray.channels();

			int b_width = r_binary.cols;
			int b_height = r_binary.rows;
			int b_channels = r_binary.channels();

			w = dstImg.GetWidth();
			h = dstImg.GetHeight();

			if (w > g_width)
			{
				w = g_width;
			}
			if (w > b_width)
			{
				w = b_width;
			}
			if (h > g_height)
			{
				h = g_height;
			}
			if (h > b_height)
			{
				h = b_height;
			}

			for (y = 0; y < h; y++)
			{
				for (x = 0; x < w; x++)
				{
					r = r_gray.at<uchar>(y, x);
					g = b = r;
					//			dstImg.SetPixel(x, dstImg.GetHeight() - y -1, RGB(r, g, b));
					dstImg.SetPixel(x, y, RGB(r, g, b));
					r = r_binary.at<uchar>(y, x);
					g = b = r;
					//			dstImg2.SetPixel(x, dstImg2.GetHeight() - y - 1, RGB(r, g, b));
					dstImg2.SetPixel(x, y, RGB(r, g, b));
				}
			}
#endif


#if 0
			resize(img, img, cv::Size(), 0.1, 0.1);
			imshow("img", img);
			resize(gray, gray, cv::Size(), 0.1, 0.1);
			imshow("gray", gray);
			resize(binary, binary, cv::Size(), 0.1, 0.1);
			imshow("binary", binary);
#endif
			//	img.release();
			gray.release();
			//	binary.release();
//			r_gray.release();
//			r_binary.release();









			current_fram_counter++;
			if (current_fram_counter > 2)
			{
				int t0, t1, t2;

				if (current_img_pos == 0)
				{
					t0 = 1;
					t1 = 2;
					t2 = 0;
				}
				else
				{
					t1 = current_img_pos - 1;
					if (t1 == 0)
					{
						t0 = 2;
						t2 = 1;
					}
					else
					{
						t0 = t1 - 1;
						if (t1 == 2)
						{
							t2 = 0;
						}
						else {
							t2 = t1 + 1;
						}
					}
				}

				if (!diff1.empty())
				{
					diff1.release();
				}
				if (!diff2.empty())
				{
					diff2.release();
				}
				if (!diff.empty())
				{
					diff.release();
				}
				cv::absdiff(binary[t0], binary[t1], diff1);
				cv::absdiff(binary[t1], binary[t2], diff2);
				cv::bitwise_and(diff1, diff2, diff);

				POINT center, left, right;
				GetMaxLabelPositon(center, left, right);

				if ((center.x != 0) && (center.y != 0))
				{
					circle(DraftImage, cv::Point(center.x, center.y), 300, (255, 0, 0), 5);
				}

				// 輪郭を検出します。
				std::vector<std::vector<cv::Point> > contours;
				cv::findContours(diff, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

				//	CImageToMat(cDraft, DraftImage);
				size_t	max_pos = 0;
				double max_area = 0.0;
				for (size_t i = 0; i < contours.size(); i++) {

					// 面積が小さすぎる場合と多きすぎる場合を除外します。
					double area = cv::contourArea(contours[i]);
					if (area < 1e2 || 1e5 < area) {
						continue;
					}
					// 輪郭を描画します。
					cv::drawContours(DraftImage, contours, i, cv::Scalar(0, 0, 255), 2);
					// 各輪郭について、それぞれ方向を検出します。
			//		getOrientation(contours[i], diff);
					if (max_area < area)
					{
						max_area = area;
						max_pos = i;
					}
				}
				if (max_pos != 0)
				{
					cv::Mat destination;
					bitwise_not(diff, destination);


					// 主成分分析のために、対象となる輪郭のみを別のバッファにコピーします。
					cv::Mat data_pts = cv::Mat(contours[max_pos].size(), 2, CV_64F); // [pts.size() x 2] 行列
					for (int i = 0; i < data_pts.rows; i++) {
						data_pts.at<double>(i, 0) = contours[max_pos][i].x;
						data_pts.at<double>(i, 1) = contours[max_pos][i].y;
					}

					// 主成分分析の実行
					cv::PCA pca_analysis(data_pts, cv::Mat(), cv::PCA::DATA_AS_ROW);

					// [分析結果] 中心の座標
					cv::Point cntr = cv::Point(pca_analysis.mean.at<double>(0, 0),
						pca_analysis.mean.at<double>(0, 1));

					// [分析結果] 固有値と固有ベクトル
					std::vector<cv::Point2d> eigen_vecs(2);
					std::vector<double> eigen_val(2);
					for (int i = 0; i < 2; i++) {
						eigen_vecs[i] = cv::Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
							pca_analysis.eigenvectors.at<double>(i, 1));
						eigen_val[i] = pca_analysis.eigenvalues.at<double>(i);
					}

					cv::Point p1 = cntr + 0.02 * cv::Point(eigen_vecs[0].x * eigen_val[0], eigen_vecs[0].y * eigen_val[0]);
					cv::Point p2 = cntr - 0.02 * cv::Point(eigen_vecs[1].x * eigen_val[1], eigen_vecs[1].y * eigen_val[1]);

					drawAxis(diff, cntr, p1, cv::Scalar(0, 255, 0), 1);
					drawAxis(diff, cntr, p2, cv::Scalar(255, 255, 0), 5);
					drawAxis(DraftImage, cntr, p1, cv::Scalar(0, 255, 0), 1, 3);
					drawAxis(DraftImage, cntr, p2, cv::Scalar(255, 255, 0), 1, 3);

					blade_center[blade_current] = cntr;
					blade_top[blade_current] = p1;
					blade_new = blade_current;
					blade_current++;
					if (blade_current >= 5)
					{
						blade_current = 0;
					}
					POINT center;
					GetTurnCenter(center);
					if ((center.x < iWidth) && (center.x != 0))
					{
						cv::circle(DraftImage, cv::Point(center.x, center.y), 100, (0, 0, 255), 5);
					}
				}

				writer << DraftImage;  // 画像 image を動画ファイルへ書き出す
#if 0
				cv::Mat	r_binary;
				cv::Mat	r_DraftImage;
				cv::resize(diff, r_binary, cv::Size(), w_rate, h_rate);
				cv::resize(DraftImage, r_DraftImage, cv::Size(), w_rate, h_rate);
				imshow("binary", r_binary);
				imshow("draft", r_DraftImage);
				r_binary.release();
				r_DraftImage.release();
#endif
			}

			if (!DraftImage.empty())
			{
				DraftImage.release();
			}
			DraftImage = NewImage.clone();

			current_img_pos++;
			if (current_img_pos >= 3)
			{
				current_img_pos = 0;
			}
		}else
		{
			CString	fullPathCheck;

			current_file.Format(current_format, current_img_counter + 1);
			fullPathCheck.Format(_T("%s%s"), current_img_dir, current_file);
			if (PathFileExists(fullPathCheck))
			{
				//			SetDlgItemText(IDC_STATIC_CURRENT_FRAME, current_file);
				current_img_pos++;
				if (current_img_pos >= 3)
				{
					current_img_pos = 0;
				}
				LoadImageFile(fullPathCheck);

				DiffImage(current_img_pos);

				current_fram_counter++;
				if (current_fram_counter > 2)
				{
					POINT center, left, right;
					GetMaxLabelPositon(center, left, right);

					circle(DraftImage, cv::Point(center.x, center.y), 300, (255, 0, 0), 5);

				}

				UpdateDraff();

				current_img_counter++;

				current_file.Format(current_format, current_img_counter + 1);
				fullPathCheck.Format(_T("%s%s"), current_img_dir, current_file);
				if (PathFileExists(fullPathCheck))
				{
					//next frame.
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
			if (current_fram_counter > 2)
			{
				writer << DraftImage;  // 画像 image を動画ファイルへ書き出す
			}
		}
//		video >> image; // videoからimageへ1フレームを取り込む
//		if (image.empty() == true) break; // 画像が読み込めなかったとき、無限ループを抜ける
//		cv::imshow("showing", image); // ウィンドウに動画を表示する
//		if (frame_counter > 40)
//		{
//			break;
//		}
		//		if (cv::waitKey(1) == 'q') break; //qを押すと終了
	}
	if (readMP4)
	{
		video.release();
	}
	writer.release();
//	MovieFullPathName.ReleaseBuffer();
}


void CWindmillTestDlg::OnBnClickedCancel()
{
#if 1
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	for (int i = 0; i < 3; i++)
	{
		if (!cimg[i].IsNull())
		{
			cimg[i].Detach();
			cimg[i].Destroy();
		}
#if 0
		if (!cGray[i].IsNull())
		{
			cGray[i].Detach();
			cGray[i].Destroy();
		}
		if (!c2Bit[i].IsNull())
		{
			c2Bit[i].Detach();
			c2Bit[i].Destroy();
		}
#endif
#if 0
		if (gray[i] != NULL)
		{
		}
		if (binary[i] != NULL)
		{
			binary[i]->release();
			binary[i] = NULL;
		}
#endif
		//		gray[i].release();
		if (!binary[i].empty())
		{
			binary[i].release();
		}

		TCHAR	value[128] = _T("0");
		if (((CButton*)GetDlgItem(IDC_CHECK_MOVIE_OUTPUT))->GetCheck())
		{
			wsprintf(value, _T("1"));
		}

		WritePrivateProfileString(L"Setting", L"SaveMovie", value, strInfilePath);
	}

#if 0
	if (!cDraft.IsNull())
	{
		cDraft.Detach();
		cDraft.Destroy();
	}
#endif
	if (!diff1.empty())
	{
		diff1.release();
	}
	if (!diff2.empty())
	{
		diff2.release();
	}
	if (!diff.empty())
	{
		diff.release();
	}

	if (!DraftImage.empty())
	{
		DraftImage.release();
	}

	if (!NewImage.empty())
	{
		NewImage.release();
	}
	
	if (!DispMain.IsNull())
	{
		DispMain.Detach();
		DispMain.Destroy();
	}
	if (!DispGray.IsNull())
	{
		DispGray.Detach();
		DispGray.Destroy();
	}
	if (!Disp1Bit.IsNull())
	{
		Disp1Bit.Detach();
		Disp1Bit.Destroy();
	}
	if (!Disp1BitDiff1.IsNull())
	{
		Disp1BitDiff1.Detach();
		Disp1BitDiff1.Destroy();
	}
	if (!Disp1BitDiff2.IsNull())
	{
		Disp1BitDiff2.Detach();
		Disp1BitDiff2.Destroy();
	}
	if (!Disp1BitDiff.IsNull())
	{
		Disp1BitDiff.Detach();
		Disp1BitDiff.Destroy();
	}
#endif
	CDialogEx::OnCancel();
}




