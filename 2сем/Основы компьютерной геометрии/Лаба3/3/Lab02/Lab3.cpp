
// Lab02.cpp: определяет поведение классов для приложения.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Lab3.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab3App

//задание ссылки на характерное задание
BEGIN_MESSAGE_MAP(Clab3App, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &Clab3App::OnAppAbout)
END_MESSAGE_MAP()


// Создание Clab3App

Clab3App::Clab3App()
{
	SetAppID(_T("Lab3.AppID.NoVersion"));

}

// Единственный объект Clab3App

Clab3App theApp;


// Инициализация Clab3App

BOOL Clab3App::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));
	
	//Создается объект главного окна (рамки) и устанавливается как основное окно приложения
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// создайте и загрузите рамку с его ресурсами
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);


	// Разрешить использование расширенных символов в горячих клавишах меню
	CMFCToolBar::m_bExtCharTranslation = TRUE;

	// Одно и только одно окно было инициализировано, поэтому отобразите и обновите его
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;	
}

int Clab3App::ExitInstance()
{
	//TODO: обработайте дополнительные ресурсы, которые могли быть добавлены
	return CWinApp::ExitInstance();
}

// Обработчики сообщений Clab2App


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Команда приложения для запуска диалога
void Clab3App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// Обработчики сообщений Clab2App



