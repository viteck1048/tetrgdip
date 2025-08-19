
#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_WIN32PROJECT3_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_WIN32PROJECT3			107
#define IDI_SMALL				108
#define IDC_WIN32PROJECT3			109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif


#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif




#define COLIR_FONU_2 RGB(240, 245, 255)
#define COLIR_FONU(x) Color(x, 240, 245, 255)
//#define YA(a) ((int)((a) * yend) + ycentr)
//#define XA(a) ((int)((a) * xend) + xcentr)
//#define YC(a) ((int)(((a) + 0.5) * yend) + ycentr)
//#define XC(a) ((int)(((a) + 0.5) * xend) + xcentr)
#define Y(a) ((int)((a) * yend))
#define X(a) ((int)((a) * xend))

#define draw_txt(txt, x, y) graphics.DrawString(txt, -1, &font, PointF((Gdiplus::REAL)X((x)), (Gdiplus::REAL)Y(y)), &pen_txt);

#define WM_USER_SHVYDKO_VNYZ 0x8001
#define WM_USER_KROK_UNYZ 0x8002

#define IDT_TIMER1 0x8888
#define IDT_TIMER2 0x8887
#define IDT_TIMER3 0x8886
#define IDT_TIMER4 0x8885
#define IDT_TIMER5 0x8884
#define UOI_TIMERPROC_EXCEPTION_SUPPRESSION 7

