#pragma once
#include "resource.h"
#include "CMatrix.h"
#include "LibGraph.h"
#include "LibPyramid.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class CMainWnd : public CFrameWnd
{
private:
	CPyramid PIR;  // Пирамида
	CRect WinRect; // Область в окне
	CMatrix PView; // Точка наблюдения в сферической СК
	CMatrix PView2;
	int Index; //индекс состояния
	COLORREF ligthColor; //цвет света
	CMenu menu; //меню
	DECLARE_MESSAGE_MAP()
	int OnCreate(LPCREATESTRUCT);

//конструктор класса
	//создание главного окна с названием и пра-рами, а также установка начальной точки наблюдения
public:
	CMainWnd::CMainWnd() 
	{
		Create(NULL, L"Lab5", WS_OVERLAPPEDWINDOW, CRect(10, 10, 700, 800), NULL, NULL);
		Index = 0;
		PView.RedimMatrix(3);
		PView2.RedimMatrix(3);
		PView(0) = 10; PView(1) = 0; PView(2) = 90;
		PView2(0) = 15; PView2(1) = 45; PView2(2) = 90;
		ligthColor = RGB(128, 236, 158); //цвет зелёный
	}

	//для обработки различных событий, таких как отрисовка окна, нажатие клавиш, изменение размера, установка цвета света, положения камеры 
	void OnPaint();
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnSize(UINT nType, int cx, int cy);
	void OnPuramid3();
	void Exit();
	afx_msg void SetLigthColor();
	afx_msg void SetCameraPosition();
	afx_msg void SetLigthPosition();
	afx_msg void DefaultCameraPosition();
};

//Определяет, какие сообщения будут обрабатываться и какие функции будут вызываться в ответ на эти сообщения
BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_COMMAND(ID_30004, OnPuramid3)
	ON_COMMAND(ID_EXIT, Exit)
	ON_COMMAND(ID_30006, SetLigthColor)
	ON_COMMAND(ID_30007, SetCameraPosition)
	ON_COMMAND(ID_30008, SetLigthPosition)
	ON_COMMAND(ID_30009, DefaultCameraPosition)
END_MESSAGE_MAP()

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	menu.LoadMenu(IDR_MENU1); // Загрузить меню из файла ресурса
	SetMenu(&menu); // Установить меню
	return 0;
}

//отрисовки окна. Если Index равен 3, вызывает метод для отрисовки пирамиды с учетом света
void CMainWnd::OnPaint()
{
	CPaintDC dc(this);
	if (Index == 3)
		PIR.DrawLightSphere(dc, PView, PView2, WinRect, ligthColor);
		//PIR.ColorDraw(dc, PView, WinRect, ligthColor);
}

void CMainWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//return;
	if ((Index == 1) || (Index == 2) || (Index == 3)||(Index==4))
	{
		switch (nChar)
		{
		case VK_UP:
		{
			double d = PView(2) - 3;
			if (d >= 0)PView(2) = d;
			break;
		}
		case VK_DOWN:
		{
			double d = PView(2) + 3;
			if (d <= 180)
				PView(2) = d;
			break;
		}
		case VK_LEFT:
		{
			double d = PView(1) - 3;  
			if (d >= -180)
				PView(1) = d;
			else
				PView(1) = d + 360;
			break;
		}
		case VK_RIGHT:
		{
			double d = PView(1) + 3;
			if (d <= 180)
				PView(1) = d;
			else
				PView(1) = d - 360;
			break;
		}
		}
		Invalidate();
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

//размеры окна
void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	WinRect.SetRect(100, 100, cx - 100, cy - 100);
}

//станавливает Index на 3 и вызывает перерисовку окна
void CMainWnd::OnPuramid3()
{
	Index = 3;
	Invalidate();
}

//перерисовка с учётом указанного цвета света
void CMainWnd::SetLigthColor()
{
	std::string line;

	int r = 0;
	int g = 0;
	int b = 0;

	std::ifstream in("C:\\Лабы\\Основы компьютерной геометрии\\Лаба9\\color.txt");

	if (in.is_open())
	{
		std::getline(in, line);
		r = stoi(line);

		std::getline(in, line);
		g = stoi(line);

		std::getline(in, line);
		b = stoi(line);
	}
	in.close();

	ligthColor = RGB(r, g, b);

	Invalidate();
}

//положение камеры из файла
void CMainWnd::SetCameraPosition()
{
	std::string line;

	int r = 0;
	int fi = 0;
	int teta = 0;

	std::ifstream in("C:\\Лабы\\Основы компьютерной геометрии\\Лаба9\\camera_position.txt");

	if (in.is_open())
	{
		std::getline(in, line);
		r = stoi(line);

		std::getline(in, line);
		fi = stoi(line);

		std::getline(in, line);
		teta = stoi(line);
	}
	in.close();

	PView(0) = r;
	PView(1) = fi;
	PView(2) = teta;

	Invalidate();
}

//положение света из файла
void CMainWnd::SetLigthPosition()
{
	std::string line;

	int r = PView2(0);
	int fi = PView2(0);
	int teta = PView2(2);

	std::ifstream in("C:\\Лабы\\Основы компьютерной геометрии\\Лаба9\\light_position.txt");

	if (in.is_open())
	{
		std::getline(in, line);
		r = stoi(line);

		std::getline(in, line);
		fi = stoi(line);

		std::getline(in, line);
		teta = stoi(line);
	}
	in.close();

	PView2(0) = r;
	PView2(1) = fi;
	PView2(2) = teta;

	Invalidate();
}


void CMainWnd::DefaultCameraPosition()
{
	PView(0) = 10; 
	PView(1) = 0; 
	PView(2) = 90;

	Invalidate();
}

void CMainWnd::Exit()
{
	DestroyWindow();
}