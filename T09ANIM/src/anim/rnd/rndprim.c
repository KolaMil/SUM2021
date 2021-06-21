/* FILE NAME: rndPrim.c
 * PROGRAMMER: Nm6
 * DATE: 21.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */

#include <string.h>

#include "rnd.h"

/***
 * Primrtive support
***/


BOOL NM6_RndPrimCreate( nm6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(nm6PRIM));
  size = sizeof(nm6VERTEX) * NoofV + sizeof(INT) * NoofI;

  if ((Pr->V = malloc(size)) == NULL)
    return FALSE;
  Pr->I = (INT *)(Pr->V + NoofV);
  Pr->NumOfV = NoofV;
  Pr->NumOfI = NoofI;
  Pr->Trans = MatrIdentity();
  memset(Pr->V, 0, size);

  return TRUE;
}

VOID NM6_RndPrimFree( nm6PRIM *Pr )
{
  if (Pr->V != NULL)
    free(Pr->V);
  memset(Pr, 0, sizeof(nm6PRIM));
} /* End of "NM6_RndPrimFree" function */

VOID NM6_RndPrimDraw( nm6PRIM *Pr, MATR World )
{
  INT i;
  MATR wvp = MatrMulMart3(Pr->Trans, World, NM6_RndMatrVP);
  POINT *pnts;

  if ((pnts = malloc(sizeof(POINT) * Pr->NumOfV)) == NULL)
    return;

  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC p = VecMulMatr(Pr->V[i].P, wvp);

    pnts[i].x = (INT)((p.X + 1) * NM6_RndFrameW / 2);
    pnts[i].x = (INT)((-p.Y + 1) * NM6_RndFrameH / 2);
  }

  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(NM6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y, NULL);
    SelectObject(NM6_hRndDCFrame, GetStockObject(NULL_PEN));
    SelectObject(NM6_hRndDCFrame, GetStockObject(DC_BRUSH));
    SetDCBrushColor(NM6_hRndDCFrame, RGB(0, 0, 0));
    LineTo(NM6_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y);
    LineTo(NM6_hRndDCFrame, pnts[Pr->I[i + 2]].x, pnts[Pr->I[i + 2]].y);
    LineTo(NM6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y);
  }
  free(pnts);
} /* End of "NM6_RndPrimDraw" function */

/*BOOL NM6_RndPrimCreateGrid( nm6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH )
{
  INT i, j, k;
  DBL theta, phi;

  if (!NM6_RndPrimCreate(Pr, SplitW * SplitH, (SplitW - 1) * (SplitH - 1) *  6))
  for (k = 0, i = 0; i < SplitH - 1; i++)
    for (j = 0; j < SplitW - 1; j++)
    {
      Pr->I
    }   
  return TRUE;
}

BOOL NM6_RndPrimCreateShere( nm6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH )
{
  INT i, j;
  DBL theta, phi;

  if (!NM6_RndPrimCreateGrid(Pr, SplitW, SplitH, ))
    return FALSE;
  
  for (theta = 0, i = 0; i < SplitH; i++, theta += PI / (SplitH -1))
    for (phi = 0, j = 0; j < SplitW; i++, phi += PI / (SplitW -1))
      Pr->V[i * SplitW + j].P = VecSet(C.X + R * sin(theta) * sin(phi),
                                        C.Y + R * cos(theta),
                                        C.Z + R * sin(theta) * cos(phi));
  return TRUE;
}

BOOL NM6_RndPrimCreatePlene( nm6PRIM *Pr, VEC P, VEC Du, INT SplitW, INT SplitH)
{
  INT i, j;

  if (!NM6_RndPrimCreateGrid(Pr, SplitW, SplitH))
    return FALSE;

  for (i = 0; i < SplitH; i++)
    for (j = 0; j < SplitW; j++)
      Pr->V[i * SplitW + j].P = 
        VecAddVec3(P, VecMulNum(Du, j / (SplitW - 1.0)), VecMulNum(Dv, i / (SplitH - 1.0)));
  return TRUE;
}
*/
/* END OF 'rndPrim.c' FILE */