/* FILE NAME : units.h
 * PROGRAMMER: NM6
 * DATE      : 21.06.2021 
 * PURPOSE   : Unit declaration module
 */

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitInit( nm6UNIT *Uni, nm6ANIM *Ani )
{
} /* End of 'NM6_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitClose( nm6UNIT *Uni, nm6ANIM *Ani )
{
} /* End of 'NM6_UnitClose' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitResponse( nm6UNIT *Uni, nm6ANIM *Ani )
{
} /* End of 'NM6_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitRender( nm6UNIT *Uni, nm6ANIM *Ani )
{
} /* End of 'NM6_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (nm6UNIT *) pointer to created unit.
 */
nm6UNIT * NM6_AnimUnitCreate( INT Size )
{
  nm6UNIT *Uni;


  /* Memory allocation */
  if (Size < sizeof(nm6UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = NM6_UnitInit;
  Uni->Close = NM6_UnitClose;
  Uni->Response = NM6_UnitResponse;
  Uni->Render = NM6_UnitRender;

  return Uni;
} /* End of 'NM6_AnimUnitCreate' function */

/* END OF 'unit.c' function */