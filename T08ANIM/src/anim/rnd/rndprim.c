/* FILE NAME: rndPrim.c
 * PROGRAMMER: Nm6
 * DATE: 17.06.2021
 * PURPOSE: 3D animation primitive handle module.
 */


#include <stdio.h>
#include <string.h>

#include "rnd.h"

/***
 * Primrtive support
***/


BOOL NM6_RndPrimCreate( nm6PRIM *Pr, INT NoofV, INT NoofI )
{
  INT size;

  memset(Pr, 0, sizeof(nm6PRIM));   /* <-- <string.h> */
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
  MATR wvp = MatrMulMatr3(Pr->Trans, World, NM6_RndMatrVP);
  POINT *pnts;

  if ((pnts = malloc(sizeof(POINT) * Pr->NumOfV)) == NULL)
    return;

  /* Build projection */
  for (i = 0; i < Pr->NumOfV; i++)
  {
    VEC p = VecMulMatr(Pr->V[i].P, wvp);

    pnts[i].x = (INT)((p.X + 1) * NM6_RndFrameW / 2);
    pnts[i].y = (INT)((-p.Y + 1) * NM6_RndFrameH / 2);
  }

  /* Draw triangles */
  for (i = 0; i < Pr->NumOfI; i += 3)
  {
    MoveToEx(NM6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y, NULL);
    Ellipse(NM6_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y, 200, 200);
    MoveToEx(NM6_hRndDCFrame, 10, 10, NULL);
    LineTo(NM6_hRndDCFrame, pnts[Pr->I[i + 1]].x, 100);
    LineTo(NM6_hRndDCFrame, pnts[Pr->I[i + 1]].x, pnts[Pr->I[i + 1]].y);
    LineTo(NM6_hRndDCFrame, pnts[Pr->I[i + 2]].x, pnts[Pr->I[i + 2]].y);
    LineTo(NM6_hRndDCFrame, pnts[Pr->I[i]].x, pnts[Pr->I[i]].y);
  }
  free(pnts);
}

BOOL NM6_RndPrimCreateGrid( nm6PRIM *Pr, INT SplitW, INT SplitH )
{
  INT i, j, k;

  if (!NM6_RndPrimCreate(Pr, SplitW * SplitH, (SplitW - 1) * (SplitH - 1) *  6))
    return FALSE;
    
  for (k = 0, i = 0; i < SplitH - 1; i++)
    for (j = 0; j < SplitW - 1; j++)
    {
      Pr->I[k++] = i * SplitW + j;
      Pr->I[k++] = i * SplitW + j + 1;
      Pr->I[k++] = (i + 1) * SplitW + j;

      Pr->I[k++] = (i + 1) * SplitW + j;
      Pr->I[k++] = i * SplitW + j + 1;
      Pr->I[k++] = (i + 1) * SplitW + j + 1;
    }   
  return TRUE;
}

BOOL NM6_RndPrimCreateShere( nm6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH )
{
  INT i, j;
  DBL theta, phi;

  if (!NM6_RndPrimCreateGrid(Pr, SplitW, SplitH))
    return FALSE;
  
  for (theta = 0, i = 0; i < SplitH; i++, theta += PI / (SplitH -1))
    for (phi = 0, j = 0; j < SplitW; i++, phi += PI / (SplitW -1))
      Pr->V[i * SplitW + j].P = VecSet(C.X + R * sin(theta) * sin(phi),
                                        C.Y + R * cos(theta),
                                        C.Z + R * sin(theta) * cos(phi));
  return TRUE;
}

/*BOOL NM6_RndPrimCreatePlene( nm6PRIM *Pr, VEC P, VEC Du, INT SplitW, INT SplitH)
{
  INT i, j;

  if (!NM6_RndPrimCreateGrid(Pr, SplitW, SplitH))
    return FALSE;

  for (i = 0; i < SplitH; i++)
    for (j = 0; j < SplitW; j++)
      Pr->V[i * SplitW + j].P = 
        VecAddVec(P, VecDivNum(Du, j / (SplitW - 1.0)), VecMulNum(Dv, i / (SplitH - 1.0)));
  return TRUE;
} */

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       vg4PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL NM6_RndPrimLoad( nm6PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT i, nv = 0, nind = 0;
  static CHAR Buf[1000];

  memset(Pr, 0, sizeof(nm6PRIM));
  if ((F = fopen(FileName, "r")) == NULL)
    return FALSE;

  /* Count vertexes and indexes */
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
      nv++;
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0;

      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
          n++;
      nind += (n - 2) * 3;
    }
  }

  if (!NM6_RndPrimCreate(Pr, nv, nind))
  {
    fclose(F);
    return FALSE;
  }

  /* Load primitive */
  rewind(F);
  nv = 0;
  nind = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      Pr->V[nv++].P = VecSet(x, y, z);
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT n = 0, n0, n1, nc;

      for (i = 1; Buf[i] != 0; i++)
        if (isspace((UCHAR)Buf[i - 1]) && !isspace((UCHAR)Buf[i]))
        {
          sscanf(Buf + i, "%i", &nc);
          if (nc < 0)
            nc = nv + nc;
          else
            nc--;

          if (n == 0)
            n0 = nc;
          else if (n == 1)
            n1 = nc;
          else
          {
            Pr->I[nind++] = n0;
            Pr->I[nind++] = n1;
            Pr->I[nind++] = nc;
            n1 = nc;
          }
          n++;
        }
    }
  }

  fclose(F);
  return TRUE;
} /* End of 'VG4_RndPrimLoad' function */

/* END OF 'rndPrim.c' FILE */