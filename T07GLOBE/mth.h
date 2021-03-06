/* FILENAME: T07GLOBE
* PROGRAMMER: NM6
* DATE: 15.06.2021
* PURPOSE: Math.h
*/

#define __mth_h_
#ifdef __mth_h_

#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

#define MatrMulMatr3(A, B ,C) MatrMulMatr(MatrMulMatr(A, B), C)

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
typedef double FLT;


typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

typedef struct tagMATR
{
  DBL A[4][4];
} MATR;


__inline VEC VecSet( DBL X, DBL Y, DBL Z )
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

__inline VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
}

__inline VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return (V1.X * V2.X + V1.Y * V2.Y + V1.Y * V2.Y) / (sqrt(V1.X * V1.X + V1.Y * V1.Y + V1.Z * V1.Z) + sqrt(V2.X * V2.X + V2.Y * V2.Y + V2.Z * V2.Z));
}

__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}

__inline DBL VecLen2( VEC V1 )
{
  return V1.X * V1.X, V1.Y * V1.Y, V1.Z * V1.Z;
}

__inline DBL VecLen( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

__inline VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V);

  if (len == 1 || len == 0)
   return V;
  return VecDivNum(V, sqrt(len));
}

__inline VEC PointTransform( VEC V, MATR M ) /*V * M4x3*/
{
  DBL w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

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
  DBL w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3];

  return VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
                (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
                (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
}

/* realisation */
/*__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}
*/
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

__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);
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

__inline MATR MatrRotateY( DBL AngleInDegree )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);
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
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);
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

__inline MATR MatrRotate( DBL AngleInDegree, VEC V )
{
  DBL a = D2R(AngleInDegree), s = sin(a), c = cos(a);
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

__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
         A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}

__inline DBL MatrDeterm( MATR M )
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
  DBL det = MatrDeterm(M);
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
 
__inline MATR MatrSet( DBL A00, DBL A01, DBL A02 )
{
MATR r =
      {
        {
          {A00, A01, A02}
        }
      };

return r;
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