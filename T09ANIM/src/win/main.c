/* FILE NAME: main.c
 * PROGRAMMER: Nm6
 * DATE: 21.06.2021
 * PURPOSE: WinAPI application sample.
 */

#include "../anim/rnd/rnd.h"

/* Window class name */
#define NM6_WND_CLASS_NAME "My Window Class Name"

/* Forward declaration */
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  HWND hWnd;
  WNDCLASS wc;
  MSG msg;

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
  wc.lpfnWndProc = WinFunc;


  /* Register window class */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error regoister window class", "Error", MB_OK | MB_ICONEXCLAMATION);
    return 0;
  }

  hWnd =
    CreateWindow(NM6_WND_CLASS_NAME,
      "Kola07ah",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      NULL,
      NULL,
      hInstance,                                                                        
      NULL);
  /**/
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  /* Window creation */
  hWnd = CreateWindow(NM6_WND_CLASS_NAME, "CGSG Primary Practice Group First Window",
    WS_OVERLAPPEDWINDOW,
    /* CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, */
    1920 * 2, 0, 1100, 700,
    NULL, NULL, hInstance, NULL);

  ShowWindow(hWnd, CmdShow);

  /* Message loop */
  while (TRUE)
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      DispatchMessage(&msg);
    }
    else
      SendMessage(hWnd, WM_TIMER, 30, 0);
  return 30;
} /* End of 'WinMain' function */

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *      HWND hWnd;
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */     
LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static nm6PRIM Pr; 


  switch (Msg)
  {
   case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y = 
      GetSystemMetrics(SM_CYMAXTRACK) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYBORDER);
    return 0;

  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);
    NM6_RndInit(hWnd);
    NM6_RndPrimCreate(&Pr, 3, 3);
    Pr.V[0].P = VecSet(0, 0, 0);
    Pr.V[1].P = VecSet(2, 0, 0);
    Pr.V[2].P = VecSet(0, 3, 0);
    Pr.I[0] = 0;
    Pr.I[1] = 1;
    Pr.I[2] = 2;
    return 0;
   
  case WM_SIZE:
    /* Redraw frame */
    NM6_RndResize(LOWORD(lParam), HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 0, 0);
    return 0;

  case WM_TIMER:
    /* Draw content */
    NM6_RndStart();
    Ellipse(NM6_hRndDCFrame, 30, 100, 200, 200);
    /* Draw primtive */
    NM6_RndPrimDraw(&Pr, MatrIdentity());
    NM6_RndEnd();

    hDC = GetDC(hWnd);

    NM6_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    ReleaseDC(hWnd, hDC);
    return 0;
 
  case WM_ERASEBKGND:
    return 1;

  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    NM6_RndCopyFrame(hDC);
    EndPaint(hWnd, &ps);
    return 0;

  case WM_DESTROY:
    NM6_RndPrimFree(&Pr);
    NM6_RndClose();
    KillTimer(hWnd, 30);
    PostMessage(hWnd, WM_QUIT, 0, 0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'NM6_WinFunc' function */

/* END OF 'pattern.c' FILE */