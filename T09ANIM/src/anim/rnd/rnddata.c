/* FILE NAME: rnddata.c
 * PROGRAMMER: Nm6
 * DATE: 21.06.2021
 * PURPOSE: WinAPI application sample.
 */

#include "rnd.h"

/* Globle perem */
HWND NM6_hRndWnd;        /* Work window handle */
HDC NM6_hRndDCFrame;     /* Work window memory device context  */
HBITMAP NM6_hRndBmFrame; /* Work window background bitmap handle */
INT NM6_RndFrameW, NM6_RndFrameH; /* Work window size */

DBL
  NM6_RndProjSize,
  NM6_RndProjDist,
  NM6_RndProjFarClip;

MATR
  NM6_RndMatrView,
  NM6_RndMatrProj,
  NM6_RndMatrVP,
  NM6_MatrFrustum;

/* END OF 'rnddata.c' FILE */