/* FILE NAME : anim.h
 * PROGRAMMER : NM6
 * DATE : 21.06.2021 
 * PURPOSE : Anim declaration module
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

#define NM6_MAX_UNITS 30000

#define UNIT_BASE_FIELDS \
  VOID (*Init)( nm6UNIT *Uni, nm6ANIM *Ani );    \
  VOID (*Close)( nm6UNIT *Uni, nm6ANIM *Ani );   \
  VOID (*Response)( nm6UNIT *Uni, nm6ANIM *Ani );\
  VOID (*Render)( nm6UNIT *Uni, nm6ANIM *Ani )   \

typedef struct tagnm6UNIT nm6UNIT;
typedef struct tagnm6ANIM
{
  HWND hWnd;
  HDC hDC;
  INT W, H;


  nm6UNIT *Units[NM6_MAX_UNITS];
  INT NumOfUnits;

  DBL
    GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
    Time, DeltaTime,             /* Time with pause and interframe interval */
    FPS;                         /* Frames per second value */
  BOOL
    IsPause;                     /* Pause flag */

  BYTE Keys[256];      /* Button state */
  BYTE KeysClick[256]; /* Button one click state */
  BYTE KeysOld[256];   /* Old button state */

  INT Mx, My, Mz, Mdx, Mdy, Mdz; /* Mouse data */

  /*BYTE
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button states */
  /*INT JPov;                               /* Joystick point-of-view control [-1,0..7] */
  /*DBL
    JX, JY, JZ, JR;                       /* Joystick axes */

} nm6ANIM;

struct tagnm6UNIT
{
  UNIT_BASE_FIELDS;
};

/* Global animation data */
extern nm6ANIM NM6_Anim;

extern INT NM6_MouseWheel;

/* Unit adding function.
 * ARGUMENTS:
 *   - Unit pointer:
 *       nm6UNIT *Uni;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimAddUnit( nm6UNIT *Uni );

/* Animation render function.
 * ARGUMENTS:
 *   - (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimRender( VOID );

/* Animation frame copying function.
 * ARGUMENTS:
 *   - Device context:
 *       HDC hDC;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimCopyFrame( VOID );

/* Animation initialization function.
 * ARGUMENTS:
 *   - Working window:
 *       HWND hWnd;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimInit( HWND hWnd );

/* Animation close function.
 * ARGUMENTS:
 *   (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimClose( VOID );

/* Animation resize function.
 * ARGUMENTS:
 *   - New window size:
 *       INT W, H;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimResize( INT W, INT H );

/* Animation exiting function.
 * ARGUMENTS:
 *   - None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimExit( VOID );

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (nm6UNIT *) pointer to created unit.
 */
nm6UNIT * NM6_AnimUnitCreate( INT Size );

VOID NM6_TimerInit( VOID );

VOID NM6_TimerResponse( VOID );

VOID NM6_AnimInputInit( VOID );

VOID NM6_AnimInputResponse( VOID );

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */