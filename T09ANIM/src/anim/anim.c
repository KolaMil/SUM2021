/* FILE NAME : anim.c
 * PROGRAMMER: NM6
 * DATE      : 21.06.2021 
 * PURPOSE   : Animation module
 */

#include "anim.h"

/* Global animation data */
nm6ANIM NM6_Anim;

/* Animation initialization function.
 * ARGUMENTS:
 *   - Working window:
 *       HWND hWnd;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimInit( HWND hWnd )
{
  NM6_Anim.hWnd = hWnd;
  NM6_RndInit(hWnd);
  NM6_Anim.hDC = NM6_hRndDC;
  NM6_TimerInit();
  NM6_AnimInputInit();
} /* End of 'NM6_AnimInit' function */

/* Animation close function.
 * ARGUMENTS:
 *   (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < NM6_Anim.NumOfUnits; i++)
  {
    NM6_Anim.Units[i]->Close(NM6_Anim.Units[i], &NM6_Anim);
    free(NM6_Anim.Units[i]);
    NM6_Anim.Units[i] = NULL;
  }
  NM6_Anim.NumOfUnits = 0;
  NM6_RndClose();
} /* End of 'NM6_AnimClose' function */

/* Animation resize function.
 * ARGUMENTS:
 *   - New window size:
 *       INT W, H;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimResize( INT W, INT H )
{
  NM6_Anim.W = W;
  NM6_Anim.H = H;
  NM6_RndResize(W, H);
} /* End of 'NM6_AnimResize' function. */

/* Animation frame copying function.
 * ARGUMENTS:
 *   - Device context:
 *       HDC hDC;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimCopyFrame( VOID )
{
  NM6_RndCopyFrame();
} /* End of 'NM6_AnimCopyFrame' function */

/* Animation render function.
 * ARGUMENTS:
 *   - (VOID) None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimRender( VOID )
{
  INT i;

  for (i = 0; i < NM6_Anim.NumOfUnits; i++)
    NM6_Anim.Units[i]->Response(NM6_Anim.Units[i], &NM6_Anim);

  NM6_RndStart();
  NM6_TimerResponse();
  NM6_AnimInputResponse();
  for (i = 0; i < NM6_Anim.NumOfUnits; i++)
    NM6_Anim.Units[i]->Render(NM6_Anim.Units[i], &NM6_Anim);

  NM6_RndEnd();
} /* End of 'NM6_AnimRender' function */

/* Unit adding function.
 * ARGUMENTS:
 *   - Unit pointer:
 *       nm6UNIT *Uni;
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimAddUnit( nm6UNIT *Uni )
{
  if (NM6_Anim.NumOfUnits < NM6_MAX_UNITS)
    NM6_Anim.Units[NM6_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &NM6_Anim);
} /* End of 'NM6_AnimAddUnit' function */

/* Animation exiting function.
 * ARGUMENTS:
 *   - None.
 * RETURNS:
 *   (VOID) None.
*/
VOID NM6_AnimExit( VOID )
{

} /* End of 'NM6_AnimExit' function */

/* END OF 'anim.c' FILE */