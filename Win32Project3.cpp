#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "stdafx.h"
#include "Win32Project3.h"

#define MAX_LOADSTRING 100
#pragma warning(disable : 4996)

//#define ___liracalc

// Global Variables:
HINSTANCE hInst;							// current instance
TCHAR szTitle[MAX_LOADSTRING] = L"TETRIS";				// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING] = L"poiuytrewq";	// the main window class name
wchar_t window_class_name[] = L"HOLOVNE_VIKNO";
int ak = 0;
HWND hhhwww;
int typ_gry = 1;

// Додаємо глобальні змінні для шрифту
wchar_t* g_availableMonospaceFont = NULL;
int g_currentFontIndex = 0; // Індекс поточного шрифту в списку
float g_fontScale = 1.0f; // Коефіцієнт масштабування шрифту

// Функція для отримання масштабу за замовчуванням для шрифту
float GetDefaultFontScale(const wchar_t* fontName) {
    if (wcscmp(fontName, L"Consolas") == 0) {
        return 1.0f;
    }
    else if (wcscmp(fontName, L"Courier New") == 0) {
        return 0.91f;
    }
    else {
        return 0.97f; // Для всіх Linux шрифтів
    }
}

// Функція для зміни масштабу шрифту
void ChangeFontScale(bool increase) {
    if (increase) {
        g_fontScale = min(1.5f, g_fontScale + 0.01f);
    } else {
        g_fontScale = max(0.5f, g_fontScale - 0.01f);
    }
    
    // Зберігаємо новий масштаб в setup
    wchar_t wbuf[32];
    swprintf_s(wbuf, L"%.2f", g_fontScale);
    set_setup(L"font_scale", wbuf);
    save_setup();
}

// Функція для перемикання шрифту
void SwitchToNextFont() {
    const wchar_t* MONOSPACE_FONTS[] = {
        L"Consolas",
        L"DejaVu Sans Mono",
        L"Liberation Mono",
        L"Droid Sans Mono",
        L"Ubuntu Mono",
        L"Source Code Pro",
        L"Courier New",
        L"Fira Mono",
        L"IBM Plex Mono",
        L"JetBrains Mono",
        L"Noto Sans Mono",
        L"Roboto Mono",
        NULL
    };

    // Зберігаємо поточний шрифт
    if (g_availableMonospaceFont) {
        delete[] g_availableMonospaceFont;
    }

    // Шукаємо наступний доступний шрифт
    int startIndex = g_currentFontIndex;
    do {
        g_currentFontIndex = (g_currentFontIndex + 1) % (sizeof(MONOSPACE_FONTS) / sizeof(MONOSPACE_FONTS[0]) - 1);
        FontFamily fontFamily(MONOSPACE_FONTS[g_currentFontIndex]);
        if (fontFamily.GetLastStatus() == Ok) {
            size_t len = wcslen(MONOSPACE_FONTS[g_currentFontIndex]) + 1;
            g_availableMonospaceFont = new wchar_t[len];
            wcscpy_s(g_availableMonospaceFont, len, MONOSPACE_FONTS[g_currentFontIndex]);
            
            // Встановлюємо масштаб за замовчуванням для нового шрифту
            g_fontScale = GetDefaultFontScale(g_availableMonospaceFont);
            
            // Зберігаємо вибраний шрифт і його масштаб в setup
            wchar_t wbuf[256];
            wcscpy_s(wbuf, g_availableMonospaceFont);
            set_setup(L"monospace_font", wbuf);
            swprintf_s(wbuf, L"%.2f", g_fontScale);
            set_setup(L"font_scale", wbuf);
            save_setup();
            break;
        }
    } while (g_currentFontIndex != startIndex);
}

// Функція ініціалізації шрифтів
void InitializeFonts() {
    const wchar_t* MONOSPACE_FONTS[] = {
        L"Consolas",
        L"DejaVu Sans Mono",
        L"Liberation Mono",
        L"Droid Sans Mono",
        L"Ubuntu Mono",
        L"Source Code Pro",
        L"Courier New",
        L"Fira Mono",
        L"IBM Plex Mono",
        L"JetBrains Mono",
        L"Noto Sans Mono",
        L"Roboto Mono",
        NULL
    };

    // Спробуємо завантажити збережений шрифт
    wchar_t savedFont[256] = {0};
    wchar_t scaleBuf[32] = {0};
    bool hasSavedFont = get_setup(L"monospace_font", savedFont, 256) && savedFont[0] != 0;
    bool hasSavedScale = get_setup(L"font_scale", scaleBuf, 32) && scaleBuf[0] != 0;

    if (hasSavedFont) {
        FontFamily fontFamily(savedFont);
        if (fontFamily.GetLastStatus() == Ok) {
            size_t len = wcslen(savedFont) + 1;
            g_availableMonospaceFont = new wchar_t[len];
            wcscpy_s(g_availableMonospaceFont, len, savedFont);
            
            // Знаходимо індекс шрифту
            for (int i = 0; MONOSPACE_FONTS[i] != NULL; i++) {
                if (wcscmp(savedFont, MONOSPACE_FONTS[i]) == 0) {
                    g_currentFontIndex = i;
                    break;
                }
            }

            // Встановлюємо масштаб
            if (hasSavedScale) {
                g_fontScale = (float)_wtof(scaleBuf);
                g_fontScale = max(0.5f, min(1.5f, g_fontScale));
            } else {
                g_fontScale = GetDefaultFontScale(savedFont);
                // Зберігаємо масштаб за замовчуванням
                swprintf_s(scaleBuf, L"%.2f", g_fontScale);
                set_setup(L"font_scale", scaleBuf);
                save_setup();
            }
            return;
        }
    }

    // Якщо збережений шрифт не знайдено або він недоступний,
    // шукаємо перший доступний
    for (int i = 0; MONOSPACE_FONTS[i] != NULL; i++) {
        FontFamily fontFamily(MONOSPACE_FONTS[i]);
        if (fontFamily.GetLastStatus() == Ok) {
            size_t len = wcslen(MONOSPACE_FONTS[i]) + 1;
            g_availableMonospaceFont = new wchar_t[len];
            wcscpy_s(g_availableMonospaceFont, len, MONOSPACE_FONTS[i]);
            g_currentFontIndex = i;
            
            // Встановлюємо масштаб за замовчуванням
            g_fontScale = GetDefaultFontScale(g_availableMonospaceFont);
            
            // Зберігаємо вибраний шрифт і його масштаб
            wchar_t wbuf[256];
            wcscpy_s(wbuf, g_availableMonospaceFont);
            set_setup(L"monospace_font", wbuf);
            swprintf_s(wbuf, L"%.2f", g_fontScale);
            set_setup(L"font_scale", wbuf);
            save_setup();
            break;
        }
    }
}

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	ComboBoxProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int DRAW_TEST(Bitmap* bmp, int ak, int xend, int yend, HWND);
WNDPROC ComboBoxDefault;
VOID Example_SaveFile(HDC hdc);
int DRAW_TEST__(HDC hdc, int ak, int xend, int yend, HWND hWnd, BOOL save);
INT GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
int kubik(Bitmap* bmp, int ak, int xend, int yend);
int shmarkli(Bitmap* bmp, int ak, int xend, int yend);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	MSG msg;
	HACCEL hAccelTable;
	GdiplusStartupInput gdiplusStartupInput;//GdiplusStartupInput GdiplusStartupInput
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

#ifdef ___liracalc	
	if(wcscmp(L"/aapchh", lpCmdLine)) {
		GdiplusShutdown(gdiplusToken);
		return 0;
	}
#endif
		
	// Спочатку відкриваємо setup.ini
	if(!open_setup("bin//setup.ini", 0))
		open_setup("setup.ini", 0);
		
	InitializeFonts(); // Тепер ініціалізуємо шрифти після відкриття setup.ini
	
	setup_00();
	
	MyRegisterClass(hInstance);
	
	if(!InitInstance (hInstance, nCmdShow)) {
		return FALSE;
	}
	
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT3));
	
	while(GetMessage(&msg, NULL, 0, 0)) {
		if(!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	wchar_t wbuf[12];
	swprintf_s(wbuf, 12, L"%d", max_total_norm);
	set_setup(L"max_total_norm", wbuf);
	swprintf_s(wbuf, 12, L"%d", max_total_adv);
	set_setup(L"max_total_adv", wbuf);
	save_setup();
	close_setup();
	
	GdiplusShutdown(gdiplusToken);
	KillTimer(hhhwww, IDT_TIMER1);
	KillTimer(hhhwww, IDT_TIMER2);
	KillTimer(hhhwww, IDT_TIMER3);
	KillTimer(hhhwww, IDT_TIMER4);
	KillTimer(hhhwww, IDT_TIMER5);
	
	delete[] g_availableMonospaceFont; // Звільняємо пам'ять
	
	return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wincl;
	
	wincl.hInstance = hInstance;
    wincl.lpszClassName = window_class_name;
    wincl.lpfnWndProc = WndProc;
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT3));
    wincl.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground = (HBRUSH)CreateSolidBrush(COLIR_FONU_2);   /* Створюємо об'єкт, який буде заповняти кольором полотно вікна */
    
	return RegisterClassEx(&wincl);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	
	hhhwww = CreateWindowEx(0, window_class_name, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL); 
	SetWindowPos(hhhwww, NULL, 0, 0, 500, 640, SWP_NOMOVE);
	
	SetUserObjectInformation(GetCurrentProcess(), UOI_TIMERPROC_EXCEPTION_SUPPRESSION, false, 1);
	
	SetTimer(hhhwww, IDT_TIMER1, shvydkist, (TIMERPROC)NULL);
	SetTimer(hhhwww, IDT_TIMER2, pryskorennia, (TIMERPROC)NULL);
	SetTimer(hhhwww, IDT_TIMER3, 200000, (TIMERPROC)NULL);
	SetTimer(hhhwww, IDT_TIMER4, 200000, (TIMERPROC)NULL);
	SetTimer(hhhwww, IDT_TIMER5, 200000, (TIMERPROC)NULL);
	
	wchar_t wbuf[12];
	if(!open_setup("bin//setup.ini", 0))
		open_setup("setup.ini", 0);
	if(!get_setup(L"max_total_norm", wbuf, 12)) {
		set_setup(L"max_total_norm", L"0");
		set_setup(L"max_total_adv", L"0");
		save_setup();
		max_total_norm = 0;
		max_total_adv = 0;
	}else {
		max_total_norm = _wtoi(wbuf);
		get_setup(L"max_total_adv", wbuf, 12);
		max_total_adv = _wtoi(wbuf);
	}
	
	ShowWindow(hhhwww, nCmdShow);
	UpdateWindow(hhhwww);
	
	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if(f_sop_ver == 1)
		SetTimer(hhhwww, IDT_TIMER4, 25, (TIMERPROC)NULL);
	else if(f_sop == 1 && f_sop_ver == 0)
		SetTimer(hhhwww, IDT_TIMER4, 0, (TIMERPROC)NULL);
	if(ready == 4)
		SetTimer(hhhwww, IDT_TIMER5, 1000, (TIMERPROC)NULL);
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static BOOL save = 0;
	switch (message) {
		case WM_TIMER: {
			if(wParam == IDT_TIMER1 && etap == 4 && pause == 0) {
				SendMessage(hhhwww, (UINT)WM_USER_KROK_UNYZ, (WPARAM)0, (LPARAM)0);
			}else
			if(wParam == IDT_TIMER2 && etap == 4 && pause == 0) {
				if (takt > 40) {
					takt--;
					prsc++;
					SetTimer(hhhwww, IDT_TIMER2, prsc, (TIMERPROC)NULL);
				}
				else {
					takt = shvydkist;
					prsc = pryskorennia;
					SetTimer(hhhwww, IDT_TIMER1, takt, (TIMERPROC)NULL);
					SetTimer(hhhwww, IDT_TIMER2, prsc, (TIMERPROC)NULL);
				}
			}else
			if(wParam == IDT_TIMER3 && etap == 4 && pause == 0) {
				SendMessage(hhhwww, (UINT)WM_USER_SHVYDKO_VNYZ, (WPARAM)0, (LPARAM)0);
			}
			if(wParam == IDT_TIMER4 && (f_sop || f_sop_ver) && pause == 0 && ready == 0) {
				InvalidateRect(hWnd,NULL, false);
				UpdateWindow(hWnd);
			}else
			if(wParam == IDT_TIMER5 && etap == 3) {
				InvalidateRect(hWnd,NULL, false);
				UpdateWindow(hWnd);
			}
			return 0;
		}
		case WM_USER_SHVYDKO_VNYZ: {
			if(!fl_s) {
				SetTimer(hhhwww, IDT_TIMER3, 200000, (TIMERPROC)NULL);
				SetTimer(hhhwww, IDT_TIMER1, takt, (TIMERPROC)NULL);
				return 0;
			}
			SetTimer(hhhwww, IDT_TIMER3, 0, (TIMERPROC)NULL);
			if(!f_sop && !f_sop_ver)
				loop(typ_gry, 0);
			InvalidateRect(hWnd,NULL, false);
			UpdateWindow(hWnd);
			return 0;
		}
		case WM_USER_KROK_UNYZ: {
			if(!f_sop && !f_sop_ver)
				loop(typ_gry, 0);
			
			InvalidateRect(hWnd,NULL, false);
			UpdateWindow(hWnd);
			return 0;
		}
		case WM_KEYUP: {
			if(wParam == VK_SNAPSHOT) {
				save = 1;
				InvalidateRect(hWnd,NULL, false);
				UpdateWindow(hWnd);
			}
			return 0;
		}
		case WM_KEYDOWN:
			if(wParam == VK_ESCAPE) {
				DestroyWindow(hhhwww);
				return 0;
			}
			if(etap == 3)
				return 0;
			if(wParam == VK_RETURN) {
				if(etap == 0) {
					setup_0(typ_gry);
					setup_1(typ_gry);
				}else if(etap == 2) {
					setup_2(5);
					SetTimer(hhhwww, IDT_TIMER1, takt, (TIMERPROC)NULL);
					SetTimer(hhhwww, IDT_TIMER2, prsc, (TIMERPROC)NULL);
				}
			}
			if(wParam == VK_PAUSE || wParam == VK_PRIOR || wParam == VK_NEXT) {
				if(etap == 4) {
					pause = pause == 1 ? 0 : 1;
					SetTimer(hhhwww, IDT_TIMER1, takt, (TIMERPROC)NULL);
				}
			}
			if(wParam == VK_DOWN && f_sop == 0 && f_sop_ver == 0) {
				if(etap == 4 && pause == 0 && fl_s == 0) {
					loop(typ_gry, 3);
					SendMessage(hhhwww, WM_USER_SHVYDKO_VNYZ, (WPARAM)0, (LPARAM)0);
				}else if(etap == 2) {
					setup_2(3);
				}else if(etap == 0) {
					typ_gry = 0;
				}
			}
			if(wParam == VK_LEFT && etap == 4 && pause == 0 && fl_s == 0 && f_sop == 0 && f_sop_ver == 0) {
				loop(typ_gry, 2);
			}
			if(wParam == VK_UP && f_sop == 0 && f_sop_ver == 0) {
				if(etap == 4 && pause == 0 && fl_s == 0) {
					loop(typ_gry, 1);
				}else if(etap == 2) {
					setup_2(1);
				}else if(etap == 0) {
					typ_gry = 1;
				}
			}
			if(wParam == VK_RIGHT && etap == 4 && pause == 0 && fl_s == 0 && f_sop == 0 && f_sop_ver == 0) {
				loop(typ_gry, 4);
			}
			if(wParam == 'H' || wParam == 'h') {
				SwitchToNextFont();
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
			}
			else if(wParam == 'P' || wParam == 'p') {
				ChangeFontScale(true);
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
			}
			else if(wParam == 'M' || wParam == 'm') {
				ChangeFontScale(false);
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
			}
			InvalidateRect(hWnd,NULL, false);
			UpdateWindow(hWnd);
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			switch (wmId) {
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			RECT rt;
			GetClientRect(hWnd, &rt);
			ak = DRAW_TEST__(hdc, ak, int(rt.right),int(rt.bottom), hWnd, save);
			save = 0;
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


int kubik(Bitmap* bmp, int ak, int xend, int yend)
{
	xend = yend;
	Graphics graphics(bmp); // създаване на обект от буфера
	graphics.Clear(COLIR_FONU(255));
	
	FontFamily fontFamily(g_availableMonospaceFont);
	Font font(&fontFamily, (Gdiplus::REAL)(Y(1) * g_fontScale), FontStyleRegular, UnitPixel);
	SolidBrush pen_txt(Color(255, 0, 0, 0));
		
	wchar_t wbuf[19];
	draw_txt(L"NEXT", H_LIN + 3, 1);
	
	swprintf_s(wbuf, 18, L"level %d", vaj_mem_2);
	draw_txt(wbuf, H_LIN + 2.4, 8);
	
	swprintf_s(wbuf, 18, L"speed %d", (shvydkist - takt) / 40);
	draw_txt(wbuf, H_LIN + 2.4, 10);
	
	if((shvydkist - takt) / 40 == 23 && etap == 4) {
		swprintf_s(wbuf, 18, L"      %d", takt - 40);
		draw_txt(wbuf, H_LIN + 2.4, 11);
	}
	
	swprintf_s(wbuf, 18, L"% 8d", total);
	draw_txt(L"total", H_LIN + 2.4, 12);
	draw_txt(wbuf, H_LIN + 2.4, 13);
	
	if(etap == 0) {
		get_setup(L"max_total_norm", wbuf, 19);
		int mm = _wtoi(wbuf);
		max_total_norm = (max_total_norm > mm ? max_total_norm : mm);
		get_setup(L"max_total_adv", wbuf, 19);
		mm = _wtoi(wbuf);
		max_total_adv = (max_total_adv > mm ? max_total_adv : mm);
		swprintf_s(wbuf, 18, L"%d", max_total_norm);
		set_setup(L"max_total_norm", wbuf);
		swprintf_s(wbuf, 18, L"%d", max_total_adv);
		set_setup(L"max_total_adv", wbuf);
		save_setup();
	}
	
	swprintf_s(wbuf, 18, L"% 8d", (typ_gry == 1 ? max_total_norm : max_total_adv));
	draw_txt(L"max", H_LIN + 2.4, V_LIN - 1);
	draw_txt(wbuf, H_LIN + 2.4, V_LIN);
	
	Pen Pen1(Color(255, 0, 0, 0)); // дефиниране на син молив
	graphics.DrawLine(&Pen1, X(0.55), Y(0.5), X(0.55), Y(1.45 + V_LIN));
	graphics.DrawLine(&Pen1, X(0.75), Y(0.5), X(0.75), Y(1.25 + V_LIN));
	graphics.DrawLine(&Pen1, X(0.55), Y(0.5), X(0.75), Y(0.5));
	graphics.DrawLine(&Pen1, X(1.25 + H_LIN), Y(0.5), X(1.25 + H_LIN), Y(1.25 + V_LIN));
	graphics.DrawLine(&Pen1, X(1.45 + H_LIN), Y(0.5), X(1.45 + H_LIN), Y(1.45 + V_LIN));
	graphics.DrawLine(&Pen1, X(1.25 + H_LIN), Y(0.5), X(1.45 + H_LIN), Y(0.5));
	graphics.DrawLine(&Pen1, X(0.75), Y(1.25 + V_LIN), X(1.25 + H_LIN), Y(1.25 + V_LIN));
	graphics.DrawLine(&Pen1, X(0.55), Y(1.45 + V_LIN), X(1.45 + H_LIN), Y(1.45 + V_LIN));
	
	GraphicsPath kb1, kb2, kb3, khrest1, khrest2;
	
	kb1.StartFigure();
	kb1.AddArc(X(0.01), Y(0.01), X(0.18), Y(0.18), (REAL)180, (REAL)90);
	kb1.AddArc(X(0.81), Y(0.01), X(0.18), Y(0.18), (REAL)270, (REAL)90);
	kb1.AddArc(X(0.81), Y(0.81), X(0.18), Y(0.18), (REAL)0, (REAL)90);
	kb1.AddArc(X(0.01), Y(0.81), X(0.18), Y(0.18), (REAL)90, (REAL)90);
	kb1.CloseFigure();
	kb2.StartFigure();
	kb2.AddArc(X(0.1), Y(0.1), X(0.16), Y(0.16), (REAL)180, (REAL)90);
	kb2.AddArc(X(0.74), Y(0.1), X(0.16), Y(0.16), (REAL)270, (REAL)90);
	kb2.AddArc(X(0.74), Y(0.74), X(0.16), Y(0.16), (REAL)0, (REAL)90);
	kb2.AddArc(X(0.1), Y(0.74), X(0.16), Y(0.16), (REAL)90, (REAL)90);
	kb2.CloseFigure();
	kb3.StartFigure();
	kb3.AddArc(X(0.33), Y(0.33), X(0.34), Y(0.34), (REAL)0, (REAL)360);
	kb3.CloseFigure();
	khrest1.StartFigure();
	khrest1.AddLine(X(0), Y(0.99), X(2), Y(0.99));
	khrest1.CloseFigure();
	khrest2.StartFigure();
	khrest2.AddLine(X(0.99), Y(0), X(0.99), Y(2));
	khrest2.CloseFigure();
	Matrix myMatrix;//, animatrix;
	myMatrix.Translate((float)X(1), (float)Y(1));
//	animatrix.Translate((float)X(1), (float)Y(1));
//	animatrix.Reset();
//	myMatrix.Reset();
	
/* 	float fl_x, fl_y, fl_x_old, fl_y_old;
	fl_x = (float)x;
	fl_y = (float)y;
	fl_x_old = (float)x_old;
	fl_y_old = (float)y_old;
	
	switch(anim) {
		case 1:{
			if(fl_y_old != fl_y) {
				fl_y_old -= Y(0.1);
				animatrix.Translate((float)X(fl_x_old), (float)Y(fl_y_old));
				animatrix.Reset();
			}
			else {
				anim = 0;
				prnt_podg(1);
			}

			break;
		}
	}
	if(anim) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				ak = fig_next[j][i];
				kb1.Transform(&animatrix);
				kb2.Transform(&animatrix);
				kb3.Transform(&animatrix);
				
				
				if(ak != 0) {
					unsigned char aaa[3];
					aaa[0] = ak & 0xc0;
					aaa[1] = (ak & 0x30) << 2;
					aaa[2] = (ak & 0x6) << 5;
					SolidBrush farb_2(Color(255, aaa[0], aaa[1], aaa[2]));
					
					aaa[0] |= 0x3f;
					aaa[1] |= 0x3f;
					aaa[2] |= 0x3f;
					SolidBrush farb_3(Color(255, aaa[0], aaa[1], aaa[2]));
					
					graphics.FillPath(&farb_2, &kb1);
					graphics.FillPath(&farb_3, &kb2);
					graphics.FillPath(&farb_2, &kb3);
				}
				
				animatrix.Reset();
				animatrix.Translate((float)X(0), (float)Y(1));
				
			}
			animatrix.Translate((float)X(1), (float)Y(-4));
		}
	}
 */	
	Pen farb_1(Color(255, 230, 230, 240));
	
	for(int i = 0; i < H_LIN; i++) {
		for(int j = 0; j < V_LIN; j++) {
			ak = etap == 0 ? mas_preview[j][i] : mas_pr[j][i];
			kb1.Transform(&myMatrix);
			kb2.Transform(&myMatrix);
			kb3.Transform(&myMatrix);
			khrest1.Transform(&myMatrix);
			khrest2.Transform(&myMatrix);
			if(i != H_LIN - 1 && j != V_LIN - 1) {
				graphics.DrawPath(&farb_1, &khrest1);
				graphics.DrawPath(&farb_1, &khrest2);
			}
			if(ak != 0) {
				unsigned char aaa[3];
				aaa[0] = ak & 0xc0;
				aaa[1] = (ak & 0x30) << 2;
				aaa[2] = (ak & 0x0c) << 4;
				SolidBrush farb_2(Color(255, aaa[0], aaa[1], aaa[2]));
				
				aaa[0] |= 0x3f;
				aaa[1] |= 0x3f;
				aaa[2] |= 0x3f;
				SolidBrush farb_3(Color(255, aaa[0], aaa[1], aaa[2]));
				
				graphics.FillPath(&farb_2, &kb1);
				graphics.FillPath(&farb_3, &kb2);
				graphics.FillPath(&farb_2, &kb3);
			}
			
			myMatrix.Reset();
			myMatrix.Translate((float)X(0), (float)Y(1));
			
		}
		myMatrix.Translate((float)X(1), (float)Y(-V_LIN));
	}
	myMatrix.Translate((float)X(2), (float)Y(2));
	
	if(etap >= 3)
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				ak = fig_next[j][i];
				kb1.Transform(&myMatrix);
				kb2.Transform(&myMatrix);
				kb3.Transform(&myMatrix);
				
				
				if(ak != 0) {
					unsigned char aaa[3];
					aaa[0] = ak & 0xc0;
					aaa[1] = (ak & 0x30) << 2;
					aaa[2] = (ak & 0x0c) << 4;
					SolidBrush farb_2(Color(255, aaa[0], aaa[1], aaa[2]));
					
					aaa[0] |= 0x3f;
					aaa[1] |= 0x3f;
					aaa[2] |= 0x3f;
					SolidBrush farb_3(Color(255, aaa[0], aaa[1], aaa[2]));
					
					graphics.FillPath(&farb_2, &kb1);
					graphics.FillPath(&farb_3, &kb2);
					graphics.FillPath(&farb_2, &kb3);
				}
				
				myMatrix.Reset();
				myMatrix.Translate((float)X(0), (float)Y(1));
				
			}
			myMatrix.Translate((float)X(1), (float)Y(-4));
		}
	
	switch(etap) {
		case 0:{
			GraphicsPath kb7, kb6;
			SolidBrush wite(COLIR_FONU(120));
			SolidBrush blue(Color(150, 188, 231, 255));
			
			kb6.AddLine(X(9.81), Y(10 - 0.08), X(9.81), Y(10 + 1.27));
			kb6.AddLine(X(3.22), Y(10 + 1.27), X(3.22), Y(10 - 0.08));
			if(typ_gry == 0)
				graphics.FillPath(&wite, &kb6);
			else
				graphics.FillPath(&blue, &kb6);
			
			draw_txt(L"Normal Game", 3.3, 10);
			
			graphics.DrawLine(&Pen1, X(9.81), Y(10 - 0.08), X(9.81), Y(10 + 1.27));
			graphics.DrawLine(&Pen1, X(9.81), Y(10 + 1.27), X(3.22), Y(10 + 1.27));
			graphics.DrawLine(&Pen1, X(3.22), Y(10 + 1.27), X(3.22), Y(10 - 0.08));
			graphics.DrawLine(&Pen1, X(3.22), Y(10 - 0.08), X(9.81), Y(10 - 0.08));
			
			kb7.AddLine(X(9.28), Y(12 - 0.08), X(9.28), Y(12 + 1.27));
			kb7.AddLine(X(3.72), Y(12 + 1.27), X(3.72), Y(12 - 0.08));
			if(typ_gry == 1)
				graphics.FillPath(&wite, &kb7);
			else
				graphics.FillPath(&blue, &kb7);
			
			draw_txt(L"Adventure", 3.8, 12);
			
			graphics.DrawLine(&Pen1, X(9.28), Y(12 - 0.08), X(9.28), Y(12 + 1.27));
			graphics.DrawLine(&Pen1, X(9.28), Y(12 + 1.27), X(3.72), Y(12 + 1.27));
			graphics.DrawLine(&Pen1, X(3.72), Y(12 + 1.27), X(3.72), Y(12 - 0.08));
			graphics.DrawLine(&Pen1, X(3.72), Y(12 - 0.08), X(9.28), Y(12 - 0.08));
			break;
		}
		case 1:{
			break;
		}
		case 2:{
			GraphicsPath kb5, kb6, kb7;
			SolidBrush wite(COLIR_FONU(120));
			SolidBrush blue(Color(150, 188, 231, 255));
			
			kb5.AddLine(X(8.23), Y(11 - 0.08), X(8.23), Y(11 + 1.27));
			kb5.AddLine(X(4.77), Y(11 + 1.27), X(4.77), Y(11 - 0.08));
			graphics.FillPath(&wite, &kb5);
			
			draw_txt(L"LEVEL", 4.95, 11);
			
			graphics.DrawLine(&Pen1, X(8.23), Y(11 - 0.08), X(8.23), Y(11 + 1.27));
			graphics.DrawLine(&Pen1, X(8.23), Y(11 + 1.27), X(4.77), Y(11 + 1.27));
			graphics.DrawLine(&Pen1, X(4.77), Y(11 + 1.27), X(4.77), Y(11 - 0.08));
			graphics.DrawLine(&Pen1, X(4.77), Y(11 - 0.08), X(8.23), Y(11 - 0.08));
			
			kb6.AddLine(X(6.5), Y(14), X(5.8), Y(13));
			kb6.AddLine(X(5.8), Y(13), X(6.5), Y(13.3));
			kb6.AddLine(X(6.5), Y(13.3), X(7.2), Y(13));
			kb6.AddLine(X(7.2), Y(13), X(6.5), Y(14));
			graphics.FillPath(&blue, &kb6);
			
			graphics.DrawLine(&Pen1, X(6.5), Y(14), X(5.8), Y(13));
			graphics.DrawLine(&Pen1, X(5.8), Y(13), X(6.5), Y(13.3));
			graphics.DrawLine(&Pen1, X(6.5), Y(13.3), X(7.2), Y(13));
			graphics.DrawLine(&Pen1, X(7.2), Y(13), X(6.5), Y(14));
			
			kb7.AddLine(X(6.5), Y(9.15), X(5.8), Y(10.15));
			kb7.AddLine(X(5.8), Y(10.15), X(6.5), Y(9.85));
			kb7.AddLine(X(6.5), Y(9.85), X(7.2), Y(10.15));
			kb7.AddLine(X(7.2), Y(10.15), X(6.5), Y(9.15));
			graphics.FillPath(&blue, &kb7);
			
			graphics.DrawLine(&Pen1, X(6.5), Y(9.15), X(5.8), Y(10.15));
			graphics.DrawLine(&Pen1, X(5.8), Y(10.15), X(6.5), Y(9.85));
			graphics.DrawLine(&Pen1, X(6.5), Y(9.85), X(7.2), Y(10.15));
			graphics.DrawLine(&Pen1, X(7.2), Y(10.15), X(6.5), Y(9.15));
			break;
		}
		case 3:{
			ready--;
			if(ready != 0) {
				GraphicsPath kb7, kb6;
				SolidBrush wite(COLIR_FONU(120));
				SolidBrush blue(Color(150, 188, 231, 255));
				
				kb6.AddLine(X(8.23), Y(10 - 0.08), X(8.23), Y(10 + 1.27));
				kb6.AddLine(X(4.77), Y(10 + 1.27), X(4.77), Y(10 - 0.08));
				graphics.FillPath(&wite, &kb6);
				
				draw_txt(L"READY", 4.95, 10);
				
				graphics.DrawLine(&Pen1, X(8.23), Y(10 - 0.08), X(8.23), Y(10 + 1.27));
				graphics.DrawLine(&Pen1, X(8.23), Y(10 + 1.27), X(4.77), Y(10 + 1.27));
				graphics.DrawLine(&Pen1, X(4.77), Y(10 + 1.27), X(4.77), Y(10 - 0.08));
				graphics.DrawLine(&Pen1, X(4.77), Y(10 - 0.08), X(8.23), Y(10 - 0.08));
				
				kb7.AddLine(X(7.07), Y(12 - 0.08), X(7.07), Y(12 + 1.27));
				kb7.AddLine(X(5.88), Y(12 + 1.27), X(5.88), Y(12 - 0.08));
				graphics.FillPath(&blue, &kb7);
				
				swprintf_s(wbuf, 18, L"%d", ready);
				draw_txt(wbuf, 6.06, 12);
				
				graphics.DrawLine(&Pen1, X(7.07), Y(12 - 0.08), X(7.07), Y(12 + 1.27));
				graphics.DrawLine(&Pen1, X(7.07), Y(12 + 1.27), X(5.88), Y(12 + 1.27));
				graphics.DrawLine(&Pen1, X(5.88), Y(12 + 1.27), X(5.88), Y(12 - 0.08));
				graphics.DrawLine(&Pen1, X(5.88), Y(12 - 0.08), X(7.07), Y(12 - 0.08));
				
			}else {
				setup_3();
				SetTimer(hhhwww, IDT_TIMER5, 200000, (TIMERPROC)NULL);
				SetTimer(hhhwww, IDT_TIMER1, shvydkist, (TIMERPROC)NULL);
				SetTimer(hhhwww, IDT_TIMER2, pryskorennia, (TIMERPROC)NULL);
			}
			break;
		}
		case 4:{
			if(pause == 1) {
				GraphicsPath kb5;
				SolidBrush wite(COLIR_FONU(120));
				
				kb5.AddLine(X(8.23), Y(11 - 0.08), X(8.23), Y(11 + 1.27));
				kb5.AddLine(X(4.77), Y(11 + 1.27), X(4.77), Y(11 - 0.08));
				graphics.FillPath(&wite, &kb5);
				
				draw_txt(L"PAUSE", 4.95, 11);
				
				graphics.DrawLine(&Pen1, X(8.23), Y(11 - 0.08), X(8.23), Y(11 + 1.27));
				graphics.DrawLine(&Pen1, X(8.23), Y(11 + 1.27), X(4.77), Y(11 + 1.27));
				graphics.DrawLine(&Pen1, X(4.77), Y(11 + 1.27), X(4.77), Y(11 - 0.08));
				graphics.DrawLine(&Pen1, X(4.77), Y(11 - 0.08), X(8.23), Y(11 - 0.08));
			}
			break;
		}
		default:{
			break;
		}
	}
	return 0;
}


INT GetEncoderClsid(const WCHAR* format, CLSID* pClsid)  // helper function
{
	UINT  num = 0;          // number of image encoders//помощна функция за извличане на параметри на енкодера
	UINT  size = 0;         // size of the image encoder array in bytes
	ImageCodecInfo* pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure
	GetImageEncoders(num, size, pImageCodecInfo);
	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}    
	}
	free(pImageCodecInfo);
	return -1;  // Failure
}


int DRAW_TEST__(HDC hdc, int ak, int xend, int yend, HWND hWnd, BOOL save)
{
	Graphics graphics(hdc);
	Bitmap bmp(xend, yend, &graphics);
	
	ak = DRAW_TEST(&bmp, ak, xend, yend, hWnd);
	
	graphics.DrawImage(&bmp, 0, 0);
	
	static int im = 0;
	if(save) {
		save = 0;
		im++;
		wchar_t wbuff[20];
		
		CLSID clsid;
		
		swprintf(wbuff, L"Image_%4d_%d.jpg", hc, im);
		EncoderParameters encoderParameters;
		ULONG quality; 
		
		GetEncoderClsid(L"image/jpeg",&clsid);
		encoderParameters.Count = 1;
		encoderParameters.Parameter[0].Guid = EncoderQuality;
		encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
		encoderParameters.Parameter[0].NumberOfValues = 1;
	   // запис на JPEG формат изображение с компресия 99.
		quality = 99;
		encoderParameters.Parameter[0].Value = &quality;
		bmp.Save(wbuff, &clsid, &encoderParameters);	
	}
	return ak;
}


int DRAW_TEST(Bitmap* bmp, int ak, int xend, int yend, HWND hWnd)
{
	if(xend / (H_LIN + 8) > yend / (V_LIN + 2)) {
		yend /= (V_LIN + 2);
		xend = yend;
	}else {
		xend /= (H_LIN + 8);
		yend = xend;
	}
	if(!f_sop && !f_sop_ver)
		kubik(bmp, 0, xend, xend);
	else
		shmarkli(bmp, 0, xend, xend);
	return 0;
}


int shmarkli(Bitmap* bmp, int ak, int xend, int yend)
{
	if(f_sop_ver == 1) {
		for(int i = 0; i < V_LIN; i++)
			sopli[i] = 1 + (i % 2);
		f_sop = 1;
		f_sop_ver = 0;
	}
	xend = yend;
	Graphics graphics(bmp);
	GraphicsPath kb1, kb2;
	kb1.AddLine(X(0.99), Y(0.01), X(0.99), Y(0.99));
	kb1.AddLine(X(0.01), Y(0.99), X(0.01), Y(0.01));
	kb2.AddLine(X(0.99), Y(0.01), X(0.99), Y(0.99));
	kb2.AddLine(X(0.01), Y(0.99), X(0.01), Y(0.01));
	SolidBrush farb_2(COLIR_FONU(255));
	
	Matrix myMatrix1, myMatrix2;
	myMatrix1.Translate((float)X(f_sop), (float)Y(1));
	myMatrix2.Translate((float)X(H_LIN - f_sop + 1), (float)Y(1));
	for(int i = 0; i < V_LIN; i++) {
		kb1.Transform(&myMatrix1);
		kb2.Transform(&myMatrix2);
		if(sopli[i] && f_sop != (H_LIN + 1)) {
			graphics.FillPath(&farb_2, sopli[i] == 1 ? &kb1 : &kb2);
		}
		myMatrix1.Reset();
		myMatrix1.Translate((float)X(0), (float)Y(1));
		myMatrix2.Reset();
		myMatrix2.Translate((float)X(0), (float)Y(1));
	}
//	if(f_sop == 10) {SetTimer(hhhwww, IDT_TIMER4, 200000, (TIMERPROC)NULL);return 0;}
	if(!(f_sop = (f_sop == (H_LIN + 1) ? 0 : f_sop + 1))) {
		SetTimer(hhhwww, IDT_TIMER4, 200000, (TIMERPROC)NULL);
		if(typ_gry == 0 && f_next_level == 1) {
			f_next_level = 0;
			setup_1(typ_gry);
		}
		InvalidateRect(hhhwww,NULL, false);
		UpdateWindow(hhhwww);
	}
	return 0;
}















