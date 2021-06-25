/* FILE NAME : input.c
 * PROGRAMMER: NM6
 * DATE      : 21.06.2021 
 * PURPOSE   : Unit declaration module
 */
#include <string.h>

#include "anim.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm")

/* Mouse wheel state global data */
INT NM6_MouseWheel;

/* Keyboard initialization function.
 * ARGUMENTS:
 *   - None.
 * RETURNS:
 *   (VOID) None.
*/
static VOID NM6_AnimKeyboardInit( VOID )
{
  INT i;

  for (i = 0; i < 256; i++)
  {
    NM6_Anim.Keys[i] = 0;
    NM6_Anim.KeysClick[i] = 0;
    NM6_Anim.KeysOld[i] = 0;
  }
} /* End of 'NM6_AnimKeyboardInit' function */

/* Keyboard response function.
 * ARGUMENTS:
 *   - None.
 * RETURNS:
 *   (VOID) None.
*/
static VOID NM6_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(NM6_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    NM6_Anim.Keys[i] >>= 7;
    NM6_Anim.KeysClick[i] = NM6_Anim.Keys[i] && !NM6_Anim.KeysOld[i];
  }

  memcpy(NM6_Anim.KeysOld, NM6_Anim.Keys, 256);
} /* End of 'NM6_AnimKeyboardResponse' function */

/* Mouse initialization function.
 * ARGUMENTS:
 *   - None.
 * RETURNS:
 *   (VOID) None.
*/
static VOID NM6_AnimMouseInit( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(NM6_Anim.hWnd, &pt);

  NM6_Anim.Mdx = pt.x - NM6_Anim.Mx;
  NM6_Anim.Mdy = pt.y - NM6_Anim.My;

  NM6_Anim.Mx = pt.x;
  NM6_Anim.My = pt.y;

  NM6_Anim.Mdz = NM6_MouseWheel;
  NM6_Anim.Mz += NM6_MouseWheel;
  NM6_MouseWheel = 0;
} /* End of 'NM6_AnimMouseInit' function */

/* Mouse response function.
 * ARGUMENTS:
 *   - None.
 * RETURNS:
 *   (VOID) None.
*/
static VOID NM6_AnimMouseResponse( VOID )
{
  POINT pt;

  GetCursorPos(&pt);
  ScreenToClient(NM6_Anim.hWnd, &pt);

  NM6_Anim.Mdx = pt.x - NM6_Anim.Mx;
  NM6_Anim.Mdy = pt.y - NM6_Anim.My;

  NM6_Anim.Mx = pt.x;
  NM6_Anim.My = pt.y;

  NM6_Anim.Mdz = NM6_MouseWheel;
  NM6_Anim.Mz += NM6_MouseWheel;
  NM6_MouseWheel = 0;
} /* End of 'NM6_AnimMouseResponse' function */

/* Input initialization function.
 * ARGUMENTS:
 *   - None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimInputInit( VOID )
{
  NM6_AnimKeyboardInit();
  NM6_AnimMouseInit();
} /* End of 'NM6_AnimInputInit' function */

/* Input response function.
 * ARGUMENTS:
 *   - None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimInputResponse( VOID )
{
  NM6_AnimKeyboardResponse();
  NM6_AnimMouseResponse();
} /* End of 'NM6_AnimInputResponse' function */

/* END OF 'input.c' FILE*/