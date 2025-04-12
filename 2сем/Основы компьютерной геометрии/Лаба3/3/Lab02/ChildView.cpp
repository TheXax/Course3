
// ChildView.cpp: реализация класса CChildView
//

#include "stdafx.h"
#include "Lab3.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView
//конструктор

CChildView::CChildView()
{
}

//деструктор
CChildView::~CChildView()
{
}

//привязка списка заданий
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT() //Обработчик для сообщения рисования
	ON_COMMAND(ID_TESTS_F1, &CChildView::OnTestsF1)
	ON_COMMAND(ID_TESTS_F2, &CChildView::OnTestsF2)
	ON_COMMAND(ID_TESTS_F3, &CChildView::OnTestsF3)
END_MESSAGE_MAP()



// Обработчики сообщений CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE; // добавляет клиентскую рамку вокруг окна.

	cs.style &= ~WS_BORDER; //  Удаляет стиль WS_BORDER, который отвечает за стандартную рамку окна.

	// Задает класс окна для создаваемого окна. 
	// В данном случае, это класс окна, созданный с помощью функции 
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr); 

	return TRUE;
}

void CChildView::OnPaint()
{
	/*CPaintDC - это класс, который предоставляет контекст устройства для рисования в окне.
	dc(this) - создает объект CPaintDC, связанный с окном this (текущее окно).*/

	CPaintDC dc(this); // контекст устройства для рисования 
	dc.SetMapMode(MM_ANISOTROPIC);
	if (Index == 1) 
	{
		Graph.Draw(dc, 1, 1); 
	} 
}

double CChildView::MyF1(double x)
{
	double y = sin(x) / x;
	return y;
}

double CChildView::MyF2(double x)
{
	double y = sqrt(fabs(x)) * sin(x);
	return y;
}

//Определяет границы для оси X и шаг. Вычисляет количество точек 𝑁 и выделяет память для массивов 𝑋 и 𝑌
void CChildView::OnTestsF1()	// MM_TEXT
{
	double xL = -3 * pi;
	double xH = -xL;
	double dx = pi / 36;		// шаг
	int N = (xH - xL) / dx;
	X.RedimMatrix(N + 1);
	Y.RedimMatrix(N + 1);
	for (int i = 0; i <= N; i++)
	{
		X(i) = xL + i * dx;
		Y(i) = MyF1(X(i));
	}
	//параметры рисования
	PenLine.Set(PS_SOLID, 1, RGB(255, 0, 0));
	PenAxis.Set(PS_SOLID, 2, RGB(0, 0, 255));
	RW.SetRect(200, 200, 600, 600);
	Graph.SetParams(X - 0.01, Y, RW);
	Graph.SetPenLine(PenLine);
	Graph.SetPenAxis(PenAxis);
	Index = 1;
	this->Invalidate();
}

void CChildView::OnTestsF2()
{
	Invalidate(); 

	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;    // Сплошная заливка кисти
	lb.lbColor = RGB(255, 0, 0); // Красный цвет линии
	lb.lbHatch = 0;

	// Создаем расширенную кисть (толщина 5, пунктир)
	CPen myPen;
	DWORD dashStyle[] = { 10, 10 };  // Чередование: 10 пикселей линии, 5 пикселей пробела
	myPen.CreatePen(PS_GEOMETRIC | PS_USERSTYLE, 5, &lb, 10, dashStyle);

	CPaintDC dc(this);
	CPen* pOldPen = dc.SelectObject(&myPen);

	double xL = -6 * pi;
	double xH = -xL;
	double dx = pi / 36;
	int N = (xH - xL) / dx;
	X.RedimMatrix(N + 1);
	Y.RedimMatrix(N + 1);
	for (int i = 0; i <= N; i++)
	{
		X(i) = xL + i * dx;
		Y(i) = MyF2(X(i));
	}
	PenLine.Set(PS_DASHDOT, 1, RGB(255, 0, 0));
	PenAxis.Set(PS_SOLID, 2, RGB(0, 0, 0));
	RW.SetRect(200, 200, 600, 600);
	Graph.SetParams(X - 0.01, Y, RW);
	Graph.SetPenLine(PenLine);
	Graph.SetPenAxis(PenAxis);
	Index = 1;
	this->Invalidate();
}

void CChildView::OnTestsF3()
{
	Invalidate();

	CPaintDC dc(this);

	int N = 8;  // Восьмиугольник
	double R = 10; // Радиус окружности
	X.RedimMatrix(N + 1);
	Y.RedimMatrix(N + 1);

	for (int i = 0; i < N; i++)
	{
		double angle = 2 * pi * i / N; // Угол в радианах
		X(i) = R * cos(angle);
		Y(i) = R * sin(angle);
	}

	X(N) = X(0);
	Y(N) = Y(0);

	PenLine.Set(PS_SOLID, 3, RGB(255, 0, 0));
	PenAxis.Set(PS_SOLID, 2, RGB(0, 0, 0));
	RW.SetRect(200, 200, 600, 600);
	Graph.SetParams(X - 0.01, Y, RW);
	Graph.SetPenLine(PenLine);
	Graph.SetPenAxis(PenAxis);
	Graph.Draw(dc, 0, 1);

	N = 1800;
	X.RedimMatrix(N);
	Y.RedimMatrix(N);

	double radius = 10.0;

	for (int i = 0; i < N; i++)
	{
		double angle = 2.0 * 3.14 * i / N;
		X(i) = radius * cos(angle);
		Y(i) = radius * sin(angle);
	}

	PenLine.Set(PS_SOLID, 2, RGB(0, 0, 255));
	PenAxis.Set(PS_SOLID, 2, RGB(0, 0, 0));
	RW.SetRect(200, 200, 600, 600);
	Graph.SetParams(X - 0.01, Y, RW);
	Graph.SetPenLine(PenLine);
	Graph.SetPenAxis(PenAxis);
	Graph.Draw(dc, 0, 0);
}