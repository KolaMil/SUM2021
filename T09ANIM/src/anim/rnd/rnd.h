/* FILE NAME : rnd.h
 * PROGRAMMER : NM6
 * DATE : 21.06.2021 
 * PURPOSE : Rendering declaration module
 */

#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
#include <glew.h>


#include "../../def.h"
#include "res/rndres.h"

#include <wglew.h>
#include <gl/wglext.h>

#pragma comment(lib, "opengl32")

typedef struct tagnm6VERTEX
{
  VEC P;  /* Vertex position */
  VEC2 T;
  VEC N;
  VEC4 C;
} nm6VERTEX;

/* Primitive type */
typedef enum tagnm6PRIM_TYPE
{
  NM6_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles */
  NM6_RND_PRIM_TRISTRIP, /* Triangle strip - array of stripped triangles */
  NM6_RND_PRIM_LINES,    /* Line segments (by 2 points) */
  NM6_RND_PRIM_POINTS,   /* Array of points */
} nm6PRIM_TYPE;


/* Primitive representation type */
typedef struct tagnm6PRIM
{
  nm6PRIM_TYPE Type; /* Primitive type */
  INT
    VA,              /* Vertex array Id */
    VBuf,            /* Vertex buffer Id */
    IBuf;            /* Index buffer Id (if 0 - use only vertex buffer) */
  INT NumOfElements; /* Number of indices/vecrtices */

  INT MtlNo; /* Material number in material array */

  MATR Trans;   /* Additional transformation matrix */
} nm6PRIM;

extern HWND NM6_hRndWnd;                 /* Work window handle */
extern HDC NM6_hRndDC;              /* Work window memory device context  */
extern HGLRC NM6_hRndGLRC;
extern INT NM6_RndFrameW, NM6_RndFrameH; /* Work window size */

extern DBL 
  NM6_RndProjSize,     /* Project plane fit square */
  NM6_RndProjDist,     /* Distance to project plane from viewer (near) */
  NM6_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR 
  NM6_RndMatrView, /* View coordinate system matrix */
  NM6_RndMatrProj, /* Projection coordinate system matrix */
  NM6_RndMatrVP;   /* Stored (View * Proj) matrix */

extern VEC 
  NM6_RndCamLoc,
  NM6_RndCamRight,
  NM6_RndCamAt,
  NM6_RndCamDir,
  NM6_RndCamUp;

/* Render resizing function.
 * ARGUMENTS:
 *   - Window size:
 *       INT W, H;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndResize( INT W, INT H );

/* Render initialization function.
 * ARGUMENTS:
 *   - Working window:
 *       HWND hWnd;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndInit( HWND hWnd );

/* Render closing function.
 * ARGUMENTS:
 *   (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndClose( VOID );

/* Render camera setting function.
 * ARGUMENTS:
 *   - Location pos:
 *       VEC Loc;
 *   - Looking at pos:
 *       VEC At;
 *   - Up vec:
 *       VEC Up;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndCamSet( VEC Loc, VEC At, VEC Up );

/* Render frame copying function.
 * ARGUMENTS:
 *   - Device context:
 *       HDC hDC;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndCopyFrame( VOID );

/* Render starting function.
 * ARGUMENTS:
 *   (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndStart( VOID );

/* Render closing function.
 * ARGUMENTS:
 *   (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndEnd( VOID );

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
VOID NM6_RndPrimCreate( nm6PRIM *Pr, nm6PRIM_TYPE Type, nm6VERTEX *V, INT NumOfV, INT *I, INT NumOfI );

/* Primitive free function.
 * ARGUMENTS:
 *   - Primitive ptr:
 *       nm6PRIM *Pr;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndPrimFree( nm6PRIM *Pr );

/* Primitive drawing function.
 * ARGUMENTS:
 *   - Primitive ptr:
 *       nm6PRIM *Pr;
 *   - World matrix:
 *       MATR World;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndPrimDraw( nm6PRIM *Pr, MATR World );

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
VOID NM6_RndPrimCreateSphere( nm6PRIM *Pr, VEC C, DBL R, INT SplitW, INT SplitH );

/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       nm6PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL NM6_RndPrimLoad( nm6PRIM *Pr, CHAR *FileName );

VOID NM6_RndPrimCreatePlane( nm6PRIM *Pr, VEC P, VEC Du, VEC Dv, INT SplitW, INT SplitH );

/* Grid creating function.
 * ARGUMENTS:
 *   - Primitive ptr:
 *       nm6PRIM *Pr;
 *   - Grid size:
 *       INT Grid_W, Grid_H;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_RndPrimCreateGrid( nm6PRIM *Pr, INT Grid_W, INT Grid_H, nm6VERTEX *V );

/***
 * Primitive collection support
 ***/

/* Primitive collection data type */
typedef struct tagnm6PRIMS
{
  INT NumOfPrims; /* Number of primitives in array */  
  nm6PRIM *Prims; /* Array of primitives */
  MATR Trans;     /* Common transformation matrix */
} nm6PRIMS;

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       nm6PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL NM6_RndPrimsCreate( nm6PRIMS *Prs, INT NumOfPrims );

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       nm6PRIMS *Prs;
 * RETURNS: None.
 */
VOID NM6_RndPrimsFree( nm6PRIMS *Prs );

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       nm6PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID NM6_RndPrimsDraw( nm6PRIMS *Prs, MATR World );

/* Load array of primitives from .G3DM file function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       nm6PRIMS *Prs;
 *   - file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL NM6_RndPrimsLoad( nm6PRIMS *Prs, CHAR *FileName );



#endif /* __rnd_h_ */

/* END OF 'rnd.h' FILE */