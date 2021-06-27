/* FILE NAME: u_ctrl.c
  * PROGRAMMER: NM6
  * DATE: 25.06.2021
  * PURPOSE: multimedia module
  */

#include <stdio.h>
#include "units.h"


/* typedef nm6INIT_ctrl */
typedef struct tagnm6UNIT_ctrl
{
  UNIT_BASE_FIELDS;
  DBL AngleSpeed;
  VEC CamLoc;
  VEC At;
  VEC Dir;
  VEC Right;
  INT Speed;

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

  Uni->CamLoc = VecSet(0, 3, 10);
  Uni->Speed = 15;
  Uni->AngleSpeed = 15;
  Uni->At = VecSet1(0);
  Uni->Dir = VecNormalize(VecSubVec(Uni->At, Uni->CamLoc));
  Uni->Right = VecNormalize(VecCrossVec(Uni->Dir, VecSet(0, 1, 0)));

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
  /* wasd */
  if (Ani->Keys['G'] || Ani->Keys['T'])
  {
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['T'] - Ani->Keys['G'])));
    Uni->At = VecAddVec(Uni->At, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['T'] - Ani->Keys['G'])));
  }
  if (Ani->Keys['F'] || Ani->Keys['H'])
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Right, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['H'] - Ani->Keys['F'])));

  /* mouse */

  if (Ani->Mdz)
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * Ani->Mdz * 0.03));

  if (Ani->Keys[VK_LBUTTON])
    Uni->CamLoc = PointTransform(Uni->CamLoc, MatrRotateY(-Ani->Keys[VK_LBUTTON] * Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdx * 30));

  if (Ani->Keys[VK_RBUTTON])
    Uni->CamLoc = PointTransform(Uni->CamLoc, MatrRotateX(-Ani->Keys[VK_RBUTTON] * Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdy * 30));


  /* arrows */

  if (Ani->Keys[VK_DOWN] || Ani->Keys[VK_UP])
  {
    Uni->CamLoc.Y += Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]);
    Uni->At.Y += Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]);
  }
  if (Ani->Keys[VK_RIGHT] || Ani->Keys[VK_LEFT])
  {
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Right, (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * 10 * Ani->GlobalDeltaTime));
    Uni->At = VecAddVec(Uni->At, VecMulNum(Uni->Right, (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * 10 * Ani->GlobalDeltaTime));
  }

  Uni->Dir = VecNormalize(VecSubVec(Uni->At, Uni->CamLoc));
  Uni->Right = VecNormalize(VecCrossVec(Uni->Dir, VecSet(0, 1, 0)));
  NM6_RndCamLoc = Uni->CamLoc;
  NM6_RndCamRight = Uni->Right;
  NM6_RndCamAt = Uni->At;
  NM6_RndCamDir = Uni->Dir;
  NM6_RndCamUp = VecSet(0, 1, 0);

}/* End of 'NM6_UnitResponse' function */


  /* NM6_UnitClose */
static VOID NM6_UnitClose( nm6UNIT_ctrl *Uni, nm6ANIM *Ani )
{
} /* End of 'NM6_UnitResponse' function */


  /* NM6_UnitRender */
static VOID NM6_UnitRender( nm6UNIT_ctrl *Uni, nm6ANIM *Ani )
{
  NM6_RndCamSet(Uni->CamLoc, Uni->At, VecSet(0, 1, 0));
}/* End of 'NM6_UnitRender' function */


  /* NM6_UnitCreateCtrl */
nm6UNIT * NM6_UnitCreateCtrl( VOID )
{
  nm6UNIT *Uni;

  if ((Uni = (nm6UNIT *)NM6_AnimUnitCreate(sizeof(nm6UNIT_ctrl))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)NM6_UnitInit;
  Uni->Response = (VOID *)NM6_UnitResponse;
  Uni->Render = (VOID *)NM6_UnitRender;
  Uni->Close = (VOID *)NM6_UnitClose;

  return Uni;
}/* End of 'NM6_UnitCreateCtrl' function */