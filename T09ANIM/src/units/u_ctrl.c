/* FILE NAME : unit_ctrl.c
 * PROGRAMMER : NM6
 * DATE : 21.06.2021 
 * PURPOSE : Ctrl unit module
 */
#include <stdio.h>

#include "units.h"

typedef struct tagnm6UNIT_CTRL
{
  UNIT_BASE_FIELDS;
  VEC CamLoc;
  VEC Dir;
  VEC Right;
  INT Speed;
  DBL AngleSpeed;

  VEC At;
} nm6UNIT_CTRL;

/* Ctrl unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_CTRL *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitInit( nm6UNIT_CTRL *Uni, nm6ANIM *Ani )
{
  Uni->CamLoc = VecSet(10, 10, 10);
  Uni->Speed = 5;
  Uni->AngleSpeed = 5;
  Uni->At = VecSet1(0);
  Uni->Dir = VecNormalize(VecSubVec(Uni->At, Uni->CamLoc));
  Uni->Right = VecNormalize(VecCrossVec(Uni->Dir, VecSet(0, 1, 0)));
} /* End of 'NM6_UnitInit' function */

/* Ctrl unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_CTRL *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitResponse( nm6UNIT_CTRL *Uni, nm6ANIM *Ani )
{
  if (Ani->Keys['S'] || Ani->Keys['W'])
  {
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['W'] - Ani->Keys['S'])));
    Uni->At = VecAddVec(Uni->At, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['W'] - Ani->Keys['S'])));
  }
  if (Ani->Keys['A'] || Ani->Keys['D'])
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Right, Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys['D'] - Ani->Keys['A'])));
  
  if (Ani->Mdz)
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Dir, Ani->GlobalDeltaTime * Uni->Speed * Ani->Mdz * 0.01));

  if (Ani->Keys[VK_LBUTTON])
    Uni->CamLoc = PointTransform(Uni->CamLoc, MatrRotateY(-Ani->Keys[VK_LBUTTON] * Ani->GlobalDeltaTime * Uni->AngleSpeed * Ani->Mdx * 30));

  if (Ani->Keys[VK_DOWN] || Ani->Keys[VK_UP])
  {
    Uni->CamLoc.Y += Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]) * 18;
    Uni->At.Y += Ani->GlobalDeltaTime * Uni->Speed * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]) * 18;
  }
  if (Ani->Keys[VK_RIGHT] || Ani->Keys[VK_LEFT])
  {
    Uni->CamLoc = VecAddVec(Uni->CamLoc, VecMulNum(Uni->Right, (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * 18 * Ani->GlobalDeltaTime));
    Uni->At = VecAddVec(Uni->At, VecMulNum(Uni->Right, (Ani->Keys[VK_RIGHT] - Ani->Keys[VK_LEFT]) * 18 * Ani->GlobalDeltaTime));
  }
  Uni->Dir = VecNormalize(VecSubVec(Uni->At, Uni->CamLoc));
  Uni->Right = VecNormalize(VecCrossVec(Uni->Dir, VecSet(0, 1, 0)));
  NM6_RndCamLoc = Uni->CamLoc;
  NM6_RndCamRight = Uni->Right;
  NM6_RndCamAt = Uni->At;
  NM6_RndCamDir = Uni->Dir;
  NM6_RndCamUp = VecSet(0, 1, 0);
} /* End of 'NM6_UnitResponse' function */

/* Ctrl unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_CTRL *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitClose( nm6UNIT_CTRL *Uni, nm6ANIM *Ani )
{
} /* End of 'NM6_UnitResponse' function */

/* Ctrl unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_CTRL *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitRender( nm6UNIT_CTRL *Uni, nm6ANIM *Ani )
{
  NM6_RndCamSet(Uni->CamLoc, Uni->At, VecSet(0, 1, 0));
} /* End of 'NM6_UnitRender' function */

/* Unit ctrl creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nm6UNIT *) pointer to created unit.
 */
nm6UNIT * NM6_UnitCreateCtrl( VOID )
{
  nm6UNIT *Uni;

  if ((Uni = (nm6UNIT *)NM6_AnimUnitCreate(sizeof(nm6UNIT_CTRL))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)NM6_UnitInit;
  Uni->Response = (VOID *)NM6_UnitResponse;
  Uni->Render = (VOID *)NM6_UnitRender;
  Uni->Close = (VOID *)NM6_UnitClose;

  return Uni;
} /* End of 'NM6_UnitCreateCtrl' function */


/* END OF 'unit_ctrl.c' FUNCTION */