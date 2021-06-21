/* FILE NAME: rndbase.c
 * PROGRAMMER: NM6
 * DATE: 21.06.2021           
 * PURPOSE: WinAPI application sample.
 */

#include "rnd.h"

VOID NM6_RndInit( HWND hWnd )
{
  HDC hDC;
  
  NM6_hRndWnd = hWnd;
  NM6_hRndBmFrame = NULL;
  
  hDC = GetDC(hWnd);
  NM6_hRndDCFrame = CreateCompatibleDC(hDC);
  ReleaseDC(hWnd, hDC);

  NM6_RndProjSize = 0.1;
  NM6_RndProjDist = NM6_RndProjSize;
  NM6_RndProjFarClip = 300;
  NM6_RndFrameH = 47;
  NM6_RndFrameW = 47;
  /*NM6_RndCamSet(VecSet(0, 0, 30), VecSet(0, 1, 0), VecSet(0, 0, 0));*/
}

VOID NM6_RndClose( VOID )
{
  if(NM6_hRndBmFrame != NULL)
    DeleteObject(NM6_hRndBmFrame);
  DeleteDC(NM6_hRndDCFrame);   
}

VOID NM6_RndResize( INT W, INT H )
{
  HDC hDC = GetDC(NM6_hRndWnd);

  if (NM6_hRndBmFrame)
    DeleteObject(NM6_hRndBmFrame);

  NM6_hRndBmFrame = CreateCompatibleBitmap(hDC, W, H);
  ReleaseDC(NM6_hRndWnd, hDC);		
  
  SelectObject(NM6_hRndDCFrame, NM6_hRndBmFrame);

  /* save w and h */
  NM6_RndFrameW = W;
  NM6_RndFrameH = H;

  /* pereschet proecbz */
  NM6_RndProjSet();
}

VOID NM6_RndCopyFrame( HDC hDC )
{
  BitBlt(hDC, 0, 0, NM6_RndFrameW, NM6_RndFrameH,
    NM6_hRndDCFrame, 0, 0, SRCCOPY);
}

/*VOID NM6_RndCamSet( VOID )
{
  NM6_RndMatrView = MatrView(Loc, At, Up);
  NM6_RndMatrView = MatrMulMatr(NM6_RndMatrView, NM6_RndMatrProj);
} */


VOID NM6_RndStart( VOID )
{
  SelectObject(NM6_hRndDCFrame, GetStockObject(NULL_PEN));
  SelectObject(NM6_hRndDCFrame, GetStockObject(DC_BRUSH));
  SetDCBrushColor(NM6_hRndDCFrame, RGB(95, 199, 95));
  Rectangle(NM6_hRndDCFrame, 0, 0, NM6_RndFrameW + 1, NM6_RndFrameH + 1);

  SelectObject(NM6_hRndDCFrame, GetStockObject(DC_PEN));
  SelectObject(NM6_hRndDCFrame, GetStockObject(NULL_BRUSH));
  SetDCPenColor(NM6_hRndDCFrame, RGB(225, 225, 225));
}

VOID NM6_RndEnd( VOID )
{
}

VOID NM6_RndProjSet ( VOID )
{
    DBL ratio_x, ratio_y;

    ratio_x = ratio_y = NM6_RndProjSize / 2;
    if (NM6_RndFrameW > NM6_RndFrameH)
      ratio_x *= (DBL)NM6_RndFrameW / NM6_RndFrameH;
    else
      ratio_y *= (DBL)NM6_RndFrameW / NM6_RndFrameH;
    NM6_RndMatrProj = 
      MatrFrustum(-ratio_x / 2, ratio_x / 2, -ratio_y / 2, ratio_y / 2,
                  NM6_RndProjDist, NM6_RndProjFarClip);
    NM6_RndMatrVP = MatrMulMatr(NM6_RndMatrView, NM6_RndMatrProj);
}

VOID NM6_RndCamSet ( VEC Loc, VEC At, VEC Up )
{
  NM6_RndMatrView = MatrView(Loc, At, Up);
  NM6_RndMatrVP = MatrMulMatr(NM6_RndMatrView, NM6_RndMatrProj);
}

/* END OF 'rndbase.c' FILE */