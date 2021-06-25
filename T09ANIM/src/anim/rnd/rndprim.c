/* FILE NAME : rndprim.c
 * PROGRAMMER : NM6
 * DATE : 21.06.2021 
 * PURPOSE : WinAPI Animation startup module
 */
#include <stdio.h>
#include <string.h>

#include "../anim.h"

/* Primitive free function.
 * ARGUMENTS:
 *   - Primitive ptr:
 *       nm6PRIM *Pr;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndPrimFree( nm6PRIM *Pr )
{
  memset(Pr, 0, sizeof(nm6PRIM));
}

/* Primitive creation function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       nm6PRIM *Pr;
 *   - vertex attributes array:
 *       nm6VERTEX *V;
 *   - number of vertices:
 *       INT NumOfV;
 *   - index array (for trimesh – by 3 ones, may be NULL)
 *       INT *I;
 *   - number of indices
 *       INT NumOfI;
 * RETURNS: None.
 */
VOID NM6_RndPrimCreate( nm6PRIM *Pr, nm6PRIM_TYPE Type, nm6VERTEX *V, INT NumOfV, INT *I, INT NumOfI )
{
  memset(Pr, 0, sizeof(nm6PRIM));

  if (V != NULL && NumOfV != 0)
  {
    glGenBuffers(1, &Pr->VBuf);
    glGenVertexArrays(1, &Pr->VA);

    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ARRAY_BUFFER, Pr->VBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(nm6VERTEX) * NumOfV, V, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, sizeof(nm6VERTEX),
                          (VOID *)0); /* position */
    glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, sizeof(nm6VERTEX),
                          (VOID *)sizeof(VEC)); /* texture coordinates */
    glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, sizeof(nm6VERTEX),
                          (VOID *)(sizeof(VEC) + sizeof(VEC2))); /* normal */
    glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, sizeof(nm6VERTEX),
                          (VOID *)(sizeof(VEC) * 2 + sizeof(VEC2))); /* color */

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
  }

  if (I != NULL && NumOfI != 0)
  {
    glGenBuffers(1, &Pr->IBuf);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * NumOfI, I, GL_STATIC_DRAW);
    Pr->NumOfElements = NumOfI;
  }
  else
    Pr->NumOfElements = NumOfV;
  Pr->Trans = MatrIdentity();
  Pr->Type = Type;
} /* End of 'NM6_RndPrimCreate' function */

/* Primitive drawing function.
 * ARGUMENTS:
 *   - Primitive ptr:
 *       nm6PRIM *Pr;
 *   - World matrix:
 *       MATR World;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndPrimDraw( nm6PRIM *Pr, MATR World )
{
  MATR wvp = MatrMulMatr3(Pr->Trans, World, NM6_RndMatrVP),
    w = MatrMulMatr(Pr->Trans, World),
    winv = MatrTranspose(MatrInverse(w));
  INT ProgId = NM6_RndShaders[0].ProgId, loc;
  INT gl_prim_type = Pr->Type == NM6_RND_PRIM_LINES ? GL_LINES :
                   Pr->Type == NM6_RND_PRIM_TRIMESH ? GL_TRIANGLES :
                   Pr->Type == NM6_RND_PRIM_TRISTRIP ? GL_TRIANGLE_STRIP :
                   GL_POINTS;

  /* Send matrix to OpenGL /v.1.0 */
  glLoadMatrixf(wvp.M[0]);

  glUseProgram(ProgId);

  if ((loc = glGetUniformLocation(ProgId, "Time")) != -1)
    glUniform1f(loc, NM6_Anim.Time);
  if ((loc = glGetUniformLocation(ProgId, "MatrWVP")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, wvp.M[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrW")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, w.M[0]);
  if ((loc = glGetUniformLocation(ProgId, "MatrWInv")) != -1)
    glUniformMatrix4fv(loc, 1, FALSE, winv.M[0]);
  if ((loc = glGetUniformLocation(ProgId, "CamLoc")) != -1)
    glUniform3fv(loc, 1, &NM6_RndCamLoc.X);
  if ((loc = glGetUniformLocation(ProgId, "Tex")) != -1)
    glUniform1i(loc, 1);

  if (Pr->IBuf == 0)
  {
    glBindVertexArray(Pr->VA);
    glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
    glBindVertexArray(0);
  }
  else
  {
    glBindVertexArray(Pr->VA);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
    glDrawElements(gl_prim_type, Pr->NumOfElements, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  glUseProgram(0);
} /* End of 'NM6_RndPrimDraw' function */

/* Grid creating function.
 * ARGUMENTS:
 *   - Primitive ptr:
 *       nm6PRIM *Pr;
 *   - Grid size:
 *       INT Grid_W, Grid_H;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndPrimCreateGrid( nm6PRIM *Pr, INT Grid_W, INT Grid_H, nm6VERTEX *V )
{
  INT i, j, k;
  INT *Ind;

  if ((Ind = malloc(sizeof(INT) * (Grid_W - 1) * (Grid_H - 1) * 6)) == NULL)
    return;

  for (k = 0, i = 0; i < Grid_H - 1; i++)
    for (j = 0; j < Grid_W - 1; j++)
    {
      Ind[k++] = i * Grid_W + j;
      Ind[k++] = i * Grid_W + j + 1;
      Ind[k++] = (i + 1) * Grid_W + j;

      Ind[k++] = (i + 1) * Grid_W + j;
      Ind[k++] = i * Grid_W + j + 1;
      Ind[k++] = (i + 1) * Grid_W + j + 1;
    }

  //NM6_RndPrimGridEvalNormals(Grid_W, Grid_H, V);
  NM6_RndPrimCreate(Pr, NM6_RND_PRIM_TRIMESH, V, Grid_W * Grid_H, Ind, (Grid_W - 1) * (Grid_H - 1) * 6);
  free(Ind);
} /* End of 'NM6_RndPrimCreateGrid' function */

/* Sphere creation function.
 * ARGUMENTS:
 *   - Primitive ptr:
 *       nm6PRIM *Pr;
 *   - Center position:
 *       VEC C;
 *   - Sphere radius:
 *       DBL R;
 *   - Medians and parallels:
 *       INT SplitW, SplitH;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndPrimCreateSphere( nm6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH )
{
  DBL theta, phi;
  INT i, j;
  nm6VERTEX *V;

  if ((V = malloc(sizeof(nm6VERTEX) * SplitW * SplitH)) == NULL)
    return;

  for (i = 0, theta = 0; i < SplitH; i++, theta += PI / (SplitH - 1))
    for (j = 0, phi = 0; j < SplitW; j++, phi += 2 * PI / (SplitW - 1))
    {
      DBL x = sin(theta) * sin(phi),
        y = cos(theta),
        z = sin(theta) * cos(phi);

      V[i * SplitW + j].N = VecSet(x, y, z);
      V[i * SplitW + j].P = VecAddVec(C, VecSet(R * x, R * y, R * z));
    }
  NM6_RndPrimCreateGrid(Pr, SplitW, SplitH, V);
  free(V);
} /* End of 'NM6_RndPrimCreateSphere' function */

VOID NM6_RndPrimCreatePlane( nm6PRIM *Pr, VEC P, VEC Du, VEC Dv, INT SplitW, INT SplitH )
{
  INT i, j;
  nm6VERTEX *V;

  if ((V = malloc(sizeof(nm6VERTEX) * SplitW * SplitH)) == NULL)
    return;

  for (i = 0; i < SplitH; i++)
    for (j = 0; j < SplitW; j++)
      V[i * SplitW + j].P = VecAddVec3(P, VecMulNum(Du, j / (SplitW - 1.0)), VecMulNum(Dv, i / SplitH - 1.0));

  NM6_RndPrimCreateGrid(Pr, SplitW, SplitH, V);
  free(V);
}

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       nm6PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL NM6_RndPrimLoad( nm6PRIM *Pr, CHAR *FileName )
{
  FILE *F;
  INT i, nv = 0, nind = 0, size;
  nm6VERTEX *V;
  INT *Ind;
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

  size = sizeof(nm6VERTEX) * nv + sizeof(INT) * nind;
  if ((V = malloc(size)) == NULL)
    return FALSE;
  Ind = (INT *)(V + nv);
  memset(V, 0, size);

  /* Load primitive */
  rewind(F);
  nv = 0;
  nind = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;
      VEC4 c = {rand() % 255 / 255.0, rand() % 255 / 255.0, rand() % 255 / 255.0, 0.1};

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
      V[nv].C = c;
      V[nv++].P = VecSet(x, y, z);
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
            Ind[nind++] = n0;
            Ind[nind++] = n1;
            Ind[nind++] = nc;
            n1 = nc;
          }
          n++;
        }
    }
  }
  
  for (i = 0; i < nv; i++)
      V[i].N = VecSet(0, 0, 0);
  for (i = 0; i < nind; i += 3)
    {
      VEC
        p0 = V[Ind[i]].P,
        p1 = V[Ind[i + 1]].P,
        p2 = V[Ind[i + 2]].P,
        N = VecNormalize(VecCrossVec(VecSubVec(p1, p0), VecSubVec(p2, p0)));

      V[Ind[i]].N = VecAddVec(V[Ind[i]].N, N);
      V[Ind[i + 1]].N = VecAddVec(V[Ind[i + 1]].N, N);
      V[Ind[i + 2]].N = VecAddVec(V[Ind[i + 2]].N, N);
    }
  for (i = 0; i < nv; i++)
    V[i].N = VecNormalize(V[i].N);

  fclose(F);
  NM6_RndPrimCreate(Pr, NM6_RND_PRIM_TRIMESH, V, nv, Ind, nind);
  free(V);
  return TRUE;
} /* End of 'NM6_RndPrimLoad' function */




/* END OF 'rndprim.c' FILE */