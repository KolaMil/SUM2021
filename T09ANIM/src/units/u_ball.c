/* FILE NAME : u_ball.c
 * PROGRAMMER: NM6
 * DATE : 21.06.2021 
 * PURPOSE : Ball unit module
 */

#include <stdio.h>

#include "units.h"

typedef struct tagnm6UNIT_COW
{
  UNIT_BASE_FIELDS;
  nm6PRIMS Cow;
  FLT AngleToRotY;
  VEC Pos;
  INT TexNo;
} nm6UNIT_COW;

/* Cow unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_COW *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitInit( nm6UNIT_COW *Uni, nm6ANIM *Ani )
{
  NM6_RndPrimsLoad(&Uni->Cow, "BIN/MODELS/BTR.g3dm");
} /* End of 'NM6_UnitInit' function */

/* Cow unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_COW *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitResponse( nm6UNIT_COW *Uni, nm6ANIM *Ani )
{
} /* End of 'NM6_UnitResponse' function */

/* Cow unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_COW *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitClose( nm6UNIT_COW *Uni, nm6ANIM *Ani )
{
  NM6_RndPrimsFree(&Uni->Cow);
} /* End of 'NM6_UnitResponse' function */

/* Cow unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_COW *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitRender( nm6UNIT_COW *Uni, nm6ANIM *Ani )
{
  NM6_RndPrimsDraw(&Uni->Cow, MatrMulMatr3(MatrScale(VecSet1(0.006)), MatrRotateY(30), MatrTranslate(VecSet(0, 0, 3))));
  /*MatrMulMatr3(MatrScale(VecSet1(0.1)), MatrRotateY(30), MatrTranslate(VecSet(-10, 0, -35)))*/
} /* End of 'NM6_UnitRender' function */

/* Unit cow creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nm6UNIT *) pointer to created unit.
 */
nm6UNIT * NM6_UnitCreateCow( VOID )
{
  nm6UNIT *Uni;

  if ((Uni = (nm6UNIT *)NM6_AnimUnitCreate(sizeof(nm6UNIT_COW))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)NM6_UnitInit;
  Uni->Response = (VOID *)NM6_UnitResponse;
  Uni->Render = (VOID *)NM6_UnitRender;
  Uni->Close = (VOID *)NM6_UnitClose;

  return Uni;
} /* End of 'NM6_UnitCreateCow' function */


/* END OF 'u_ball.c' FUNCTION */