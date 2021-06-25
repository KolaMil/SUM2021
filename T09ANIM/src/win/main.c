/* FILE NAME : main.c
 * PROGRAMMER: NM6
 * DATE: 21.06.2021 
 * PURPOSE : WinAPI Animation startup module
 */
#include "../units/units.h"

#define NM6_WND_CLASS_NAME "My Window Class Name"

/* Callback window fuction */
LRESULT CALLBACK NM6_WinFunc( HWND hWnd, UINT Msg,  WPARAM wParam, LPARAM lParam );

/* The main program function.
* ARGUMENTS:
* - handle of application instance:
* HINSTANCE hInstance;
* - dummy handle of previous application instance (not used):
* HINSTANCE hPrevInstance;
* - command line string:
* CHAR *CmdLine;
* - show window command parameter (see SW_***):
* INT CmdShow;
* RETURNS:
* (INT) Error level for operation system (0 for success).
*/
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  HWND hWnd;
  MSG msg;
  WNDCLASS wc;

  SetDbgMemHooks();

  /* Fill window class structure */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_HAND);
  wc.hIcon = LoadIcon(NULL, IDI_SHIELD);
  wc.hInstance = hInstance;
  wc.lpszClassName = NM6_WND_CLASS_NAME;
  wc.lpszMenuName = NULL;
  wc.lpfnWndProc = NM6_WinFunc;

  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "Error", MB_OK | MB_ICONERROR);
    return 0;
  }

  hWnd =
  CreateWindow(NM6_WND_CLASS_NAME,
  "RRYTAY GRYPPA",
  WS_OVERLAPPEDWINDOW,
  CW_USEDEFAULT, CW_USEDEFAULT,
  CW_USEDEFAULT, CW_USEDEFAULT,
  NULL,
  NULL,
  hInstance,
  NULL);

  /* Show window */
  ShowWindow(hWnd, ShowCmd);
  UpdateWindow(hWnd);

  /* Create Cow */
  NM6_AnimAddUnit(NM6_UnitCreateCow());
  NM6_AnimAddUnit(NM6_UnitCreateCtrl());

  /* Message loop */
  while (GetMessage(&msg, NULL, 0, 0))
    DispatchMessage(&msg);

  return 30;
} /* End of 'WinMain' function */
/* Window handle function.
* ARGUMENTS:
* - window handle:
* HWND hWnd;
* - message type (see WM_***):
* UINT Msg;
* - message 'word' parameter:
* WPARAM wParam;
* - message 'long' parameter:
* LPARAM lParam;
* RETURNS:
* (LRESULT) message depende return value.
*/
LRESULT CALLBACK NM6_WinFunc( HWND hWnd, UINT Msg, 
                     WPARAM wParam, LPARAM lParam )
{
  PAINTSTRUCT ps;

  switch (Msg)
  {
    /* GETMINMAXINFO */
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + 2 * GetSystemMetrics(SM_CYBORDER);
    return 0;
    /* CREATE */
  case WM_CREATE:
    NM6_AnimInit(hWnd);
    SetTimer(hWnd, 30, 1, NULL);
    return 0;
    /* SIZE */
  case WM_SIZE:
    NM6_AnimResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 30, 0);
    return 0;
    /* TIMER */
  case WM_TIMER:
    NM6_AnimRender();
    NM6_AnimCopyFrame();
    return 0;
    /* KEYDOWN */
  case WM_KEYDOWN:
    if (wParam == 27)
      SendMessage(hWnd, WM_CLOSE, 0, 0);
    else if (wParam == 'Q')
      NM6_Anim.IsPause = !NM6_Anim.IsPause;
    return 0;
    /*  */
  case WM_CLOSE:
    if (MessageBox(hWnd, "You sure?", "Exit", MB_YESNO | MB_ICONQUESTION) == IDYES)
      break;
    return 0;
    /*  */
  case WM_LBUTTONDOWN:
    SetCapture(hWnd);
    return 0;
    /*  */
  case WM_LBUTTONUP:
    ReleaseCapture();
    return 0;
    /*  */
  case WM_MOUSEWHEEL:
    NM6_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;
    /*  */
  case WM_PAINT:
    BeginPaint(hWnd, &ps);
    NM6_AnimCopyFrame();
    EndPaint(hWnd, &ps);
    return 0;
    /*  */
  case WM_ERASEBKGND:
    return 1;
  case WM_DESTROY:
    NM6_AnimClose();
    KillTimer(hWnd, 30);
    PostQuitMessage(27);
    return 0;
  }

  return DefWindowProc(hWnd, Msg, wParam, lParam);

} /* End of 'NM6_WinFunc' function */

/* END OF 'main.c' FILE */