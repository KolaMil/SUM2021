/* FILE NAME : rnddata.c
 * PROGRAMMER : NM6
 * DATE : 21.06.2021 
 * PURPOSE : WinAPI Animation startup module
 */
#include "rnd.h"

HWND NM6_hRndWnd;                 /* Work window handle */
HDC NM6_hRndDC;
INT NM6_RndFrameW, NM6_RndFrameH; /* Work window size */
HGLRC NM6_hRndGLRC;

VEC 
  NM6_RndCamLoc,
  NM6_RndCamRight,
  NM6_RndCamAt,
  NM6_RndCamDir,
  NM6_RndCamUp;

DBL
  NM6_RndProjSize,  /* Project plane fit square */
  NM6_RndProjDist,  /* Distance to project plane from viewer (near) */
  NM6_RndProjFarClip;  /* Distance to project far clip plane (far) */

MATR
  NM6_RndMatrView, /* View coordinate system matrix */
  NM6_RndMatrProj, /* Projection coordinate system matrix */
  NM6_RndMatrVP;   /* Stored (View * Proj) matrix */


/* END OF 'rnddata.c' FILE */