/* FILE NAME: u_cow.c
* PROGRAMMER: NM6
* DATE: 21.06.2021
* PURPOSE:
*/

#include <time.h>
#include "../anim/anim.h"

/* typedef nm6INIT_ctrl */
typedef struct tagnm6UNIT_ctrl
{
  NM6_NM6_UNIT_BASE_FIELDS;
  DBL Speed;
  VEC CamLoc, CamDir;
} nm6UNIT_ctrl;

/* Cow unit initialization function
* ARGUMENTS:
* - self-pointer to unit object
* nm6UNIT_BALL *Uni;
* - animation context:
* nm6ANIM *Ani;
* RETURNS: None.
*/
static VOID NM6_UnitInit( nm6UNIT_ctrl *Uni, nm6ANIM *Ani )
{
  Uni->CamLoc = VecSet(0, 0, 30);
  Uni->CamDir = VecSet(0, 1, 0);
  Uni->Speed = 10;
}/* End of 'NM6_UnitInit' function */


/* Cow unit inter frame events handle function
* ARGUMENTS:
* - self-pointer to unit object
* nm6UNIT_BALL *Uni;
* - animation context:
* nm6ANIM *Ani;
* RETURNS: None.
*/
static VOID NM6_UnitResponse( nm6UNIT_ctrl *Uni, nm6ANIM *Ani )
{
  Uni->CamLoc =
    VecAddVec(Uni->CamLoc,
      VecMulNum(Uni->CamDir, Ani->GlobalDeltaTime * Uni->Speed *
        (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN])));
}/* End of 'NM6_UnitResponse' function */


/* Bounce ball unit render function
* ARGUMENTS:
* - self-pointer to unit object
* nm6UNIT_BALL *Uni;
* - animation context:
* nm6ANIM *Ani;
* RETURNS: None.
*/
static VOID NM6_UnitRender( VOID )
{
}/* End of 'NM6_UnitRender' function */


/* Unit ball creation function
* ARGUMENTS: None.
* RETURNS:
* (nm6UNIT *) pointer to created unit
*/
nm6UNIT * NM6_UnitCreateCtrl( VOID )
{
  nm6UNIT *Uni;

  if ((Uni = (nm6UNIT *)NM6_AnimUnitCreate(sizeof(nm6UNIT_ctrl))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)NM6_UnitInit;
  Uni->Response = (VOID *)NM6_UnitResponse;
  Uni->Render = (VOID *)NM6_UnitRender;

  return Uni;
}/* End of 'NM6_UnitCreateCtrl' function */