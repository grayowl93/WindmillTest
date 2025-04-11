
// WindmillTest.cpp : アプリケーションのクラス動作を定義します。
//

#include "pch.h"
#include "framework.h"
#include "WindmillTest.h"
#include "WindmillTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWindmillTestApp

BEGIN_MESSAGE_MAP(CWindmillTestApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWindmillTestApp の構築

CWindmillTestApp::CWindmillTestApp()
{
	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CWindmillTestApp オブジェクト

CWindmillTestApp theApp;


// CWindmillTestApp の初期化

BOOL CWindmillTestApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ダイアログにシェル ツリー ビューまたはシェル リスト ビュー コントロールが
	// 含まれている場合にシェル マネージャーを作成します。
	CShellManager *pShellManager = new CShellManager;

	// MFC コントロールでテーマを有効にするために、"Windows ネイティブ" のビジュアル マネージャーをアクティブ化
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	// INIファイル作成場所指定.
#if 1
	TCHAR crDir[MAX_PATH + 1];
	TCHAR drive[MAX_PATH + 1];
	TCHAR dir[MAX_PATH + 1];
	TCHAR fname[MAX_PATH + 1];
	TCHAR ext[MAX_PATH + 1];
	GetModuleFileName(NULL, crDir, MAX_PATH + 1);

	// ファイルパスを分割
	::_wsplitpath_s(crDir, drive, dir, fname, ext);
	// ドライブとディレクトリ名を結合して実行ファイルパスとする
	swprintf(crDir, MAX_PATH, _T("%s%sCWindmillTest.ini"), drive, dir);

//	strInfilePath = CString(drive) + CString(dir);
//	strInfilePath = crDir;
//	strInfilePath += _T(".¥¥CWindmillTest.ini");
#else
	TCHAR crDir[MAX_PATH + 1];
	GetCurrentDirectory(MAX_PATH + 1, crDir);

//	CString strInfilePath;

//	strInfilePath = crDir;
	swprintf(crDir, MAX_PATH, _T("%s\\CWindmillTest.ini"), crDir);
#endif
	// INIファイル保存.
	this->m_pszProfileName = crDir;

	CWindmillTestDlg dlg;
	dlg.pSaveParent = this;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: ダイアログの作成に失敗しました。アプリケーションは予期せずに終了します。\n");
		TRACE(traceAppMsg, 0, "警告: ダイアログで MFC コントロールを使用している場合、#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS を指定できません。\n");
	}

	// 上で作成されたシェル マネージャーを削除します。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif
//	if (m_pszProfileName)
//	{
//		free((void*)m_pszProfileName);             // メモリの解放
//		m_pszProfileName = NULL;
//	}

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

