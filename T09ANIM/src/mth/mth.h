/* FILENAME: T07GLOBE
* PROGRAMMER: NM6
* DATE: 21.06.2021
* PURPOSE: Math.h
*/


#ifndef __mth_h_
#define __mth_h_

#include <math.h>

#include <windows.h>

#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

#define MatrMulMart3(A, B ,C) MatrMulMatr(MatrMulMatr(A, B), C)

#define UnitMatrix \
{                  \
  {                \
    {1, 0, 0, 0},  \
    {0, 1, 0, 0},  \
    {0, 0, 1, 0},  \
    {0, 0, 0, 1}   \
  }                \
}

typedef double DBL;
typedef float FLT;


typedef struct tagVEC
{
  FLT X, Y, Z;
} VEC;

typedef struct tagMATR
{
  FLT A[4][4];
} MATR;


__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v = {X, Y, Z};

  return v;
} /* End of 'VecSet' function */

__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}


__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}

__inline VEC VecMulNum( VEC V1, FLT N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
}

__inline VEC VecDivNum( VEC V1, FLT N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return (V1.X * V2.X + V1.Y * V2.Y + V1.Y * V2.Y) / (sqrt(V1.X * V1.X + V1.Y * V1.Y + V1.Z * V1.Z) + sqrt(V2.X * V2.X + V2.Y * V2.Y + V2.Z * V2.Z));
}

__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}

__inline FLT VecLen2( VEC V1 )
{
  return V1.X * V1.X, V1.Y * V1.Y, V1.Z * V1.Z;
}

__inline FLT VecLen( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

__inline VEC VecNormalize( VEC V )
{
  FLT len = VecDotVec(V, V);

  if (len == 1 || len == 0)
   return V;
  return VecDivNum(V, sqrt(len));
}

__inline VEC PointTransform( VEC V, MATR M ) /*V * M4x3*/
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + w * M.A[3][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + w * M.A[3][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + w * M.A[3][2]);
}
__inline VEC VectorTransform( VEC V, MATR M ) /*V * M3x3*/
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
                V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
                V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
}
__inline VEC VecMulMatr( VEC V, MATR M ) /* V * M4x4 / w */ /*!!!*/
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
}

/* realisation */
__inline MATR MatrIdentity( VOID )
{
  MATR I = UnitMatrix;

  return I;
}


__inline MATR MatrTranslate( VEC T )
{
  MATR m =
          {
            {
              {1, 0, 0, 0},
              {0, 1, 0, 0},
              {0, 0, 1, 0},
              {T.X, T.Y, T.Z, 1}
            }
          };

  return m;
}

__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  MATR m =
          {
            {
              {1, 0, 0, 0},
              {0, c, s, 0},
              {0, -s, c, 0},
              {0, 0, 0, 1}
            }
          };

  return m;
}

__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  MATR m =
    {
      {
        {c, 0, -s, 0},
        {0, 1, 0, 0},
        {s, 0, c, 0},
        {0, 0, 0, 1}
      }
    };

  return m;
}
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  MATR m =
    {
      {
      {c, s, 0, 0},
      {-s, c, 0, 0},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
      }
    };

  return m;
}

__inline MATR MatrRotate( FLT AngleInDegree, VEC V )
{
  FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
  VEC A = VecNormalize(V);

  MATR m =
          {
            {
              {c + A.X * A.X * (1 - c), A.X * A.Y * (1 - c) + A.Z * s, A.X * A.Z * (1 - c) - (A.Y * s), 0},
              {A.X * A.Y * (1 - c) - A.Z * s, c + A.Y * A.Y * (1 - c), A.Y * A.Z * (1 - c) + (A.X * c), 0},
              {A.X * A.Z * (1 - c) + A.Y * s, A.Z * A.Y * (1 - c) + A.X * s, c + A.Z * A.Z * (1 - c), 0},
              {0, 0, 0, 1}
            }
          };

  return m;
}

/* Matrix look-at viewer setup function.
 * ARGUMENTS:
 *   - viewer position, look-at point, approximate up direction:
 *       VEC Loc, At, Up1;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecNormalize(VecCrossVec(Right, Dir));
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0}, {Right.Y, Up.Y, -Dir.Y, 0}, {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), -VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };

  return m;
} /* End of 'MatrView' function */


__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r;
  INT i, j, k;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.A[i][j] = 0, k = 0; k < 4; k++)
  r.A[i][j] += M1.A[i][k] * M2.A[k][j];

  return r;
}

__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13,
                   FLT A21, FLT A22, FLT A23,
                   FLT A31, FLT A32, FLT A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}

__inline FLT MatrDeterm( MATR M )
{

return M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3], M.A[2][1], M.A[2][2], M.A[2][3], M.A[3][1], M.A[3][2], M.A[3][3]) -
                    M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3], M.A[2][0], M.A[2][2], M.A[2][3],M.A[3][0], M.A[3][2], M.A[3][3]) +
                    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3], M.A[2][0], M.A[2][1], M.A[2][3], M.A[3][0], M.A[3][1], M.A[3][3]) -
                    M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2], M.A[2][0], M.A[2][1], M.A[2][2], M.A[3][0], M.A[3][1], M.A[3][2]) +
                    M.A[1][0] * MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3], M.A[2][1], M.A[2][2], M.A[2][3], M.A[3][1], M.A[3][2], M.A[3][3]) -
                    M.A[1][1] * MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3], M.A[2][0], M.A[2][2], M.A[2][3], M.A[3][0], M.A[3][2], M.A[3][3]) +
                    M.A[1][2] * MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3], M.A[2][0], M.A[2][1], M.A[2][3], M.A[3][0], M.A[3][1], M.A[3][3]) -
                    M.A[1][3] * MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2], M.A[2][0], M.A[2][1], M.A[2][2], M.A[3][0], M.A[3][1], M.A[3][2]) +
                    M.A[2][0] * MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3], M.A[1][1], M.A[1][2], M.A[1][3], M.A[3][1], M.A[3][2], M.A[3][3]) -
                    M.A[2][1] * MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3], M.A[1][0], M.A[1][2], M.A[1][3], M.A[3][0], M.A[3][2], M.A[3][3]) +
                    M.A[2][2] * MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3], M.A[1][0], M.A[1][1], M.A[1][3], M.A[3][0], M.A[3][1], M.A[3][3]) -
                    M.A[2][3] * MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2], M.A[1][0], M.A[1][1], M.A[1][2], M.A[3][0], M.A[3][1], M.A[3][2]) +
                    M.A[3][0] * MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3], M.A[1][1], M.A[1][2], M.A[1][3], M.A[2][1], M.A[2][2], M.A[2][3]) -
                    M.A[3][1] * MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3], M.A[1][0], M.A[1][2], M.A[1][3], M.A[2][0], M.A[2][2], M.A[2][3]) +
                    M.A[3][2] * MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][3], M.A[1][0], M.A[1][1], M.A[1][3], M.A[3][0], M.A[2][1], M.A[2][3]) -
                    M.A[3][3] * MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2], M.A[1][0], M.A[1][1], M.A[1][2], M.A[2][0], M.A[2][1], M.A[2][2]);
}

__inline MATR MatrInverse( MATR M )
{
  MATR r;
  FLT det = MatrDeterm(M);
  INT s, i, j, P[][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};

  if (det == 0)
  return MatrIdentity();

  for (s = 1, i = 0; i < 4; i++)
    for (j = 0; j < 4; j++, s = -s)
      r.A[j][i] =
                s * MatrDeterm3x3(M.A[P[i][0]][P[j][0]], M.A[P[i][0]][P[j][1]], M.A[P[i][0]][P[j][2]],
                M.A[P[i][1]][P[j][0]], M.A[P[i][1]][P[j][1]], M.A[P[i][1]][P[j][2]],
                M.A[P[i][2]][P[j][0]], M.A[P[i][2]][P[j][1]], M.A[P[i][2]][P[j][2]]) / det;
  return r;
}

__inline void Swap1( double *a, double *b )
{
  double tmp = *a;

  *a = *b;
  *b = tmp;
}

/* Add two vectors function.
* ARGUMENTS:
* - vectors to be add:
* VEC V1, V2;
* RETURNS:
* (VEC) result vector.
*/

__inline MATR MatrSet( FLT A00, FLT A01, FLT A02, FLT A03,
                      FLT A10, FLT A11, FLT A12, FLT A13,
                      FLT A20, FLT A21, FLT A22, FLT A23,
                      FLT A30, FLT A31, FLT A32, FLT A33)
{
  MATR r =
  {
    {
          {A00, A01, A02, A03},
          {A10, A11, A12, A13},
          {A20, A21, A22, A23},
          {A30, A31, A32, A33}
    }
  };

  return r;
}

__inline MATR MatrFrustum( FLT Left, FLT Right,
                            FLT Bottom, FLT Top,
                            FLT Near, FLT Far )
{
  return MatrSet(2 *Near / (Right - Left), 0, 0, 0,
                  0, 2 * Near / (Top - Bottom), 0, 0,
                  (Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom),
                  (Far + Left) / (Right - Left), -1, 
                  0, 0, -2 * Near * Far / (Far - Near), 0);
}


/*!!! ВО ВСЕ ЗАГОЛОВОЧНЫЕ ФАЙЛЫ ДОБАВЛЯЕМ ИСКЛЮЧЕНИЕ ПОВТОРНОГО ВКЛЮЧЕНИЯ: (см. п.7 основного конспекта по Си)



пример в GLOBE

MATR m = MatrMulMatr(MatrRotateY(GLB_Time * 30), MatrRotate(sin(GLB_Time) * 8, VecSet(1, 1, 1)));

for (...
for (...
{
VEC v = PointTransform(Geom[i][i], m);


pnts[i][j].x = WinW / 2 + (INT)v.X;
pnts[i][j].y = WinH / 2 - (INT)v.Y;
}
*/
#endif