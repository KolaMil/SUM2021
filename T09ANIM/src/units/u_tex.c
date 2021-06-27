/* FILE NAME : u_gear.c
 * PROGRAMMER: NM6
 * DATE : 21.06.2021 
 * PURPOSE : Ball unit module
 */

#ifdef __u_tex_c_
#define __u_tex_c_

#include <stdio.h>

#include "units.h"

typedef struct tagnm6UNIT_TEXPRIM
{
  UNIT_BASE_FIELDS;
  nm6PRIM Pr;           /* Primitive */
  INT TexId;            /* Texture OpenGL Id */
} nm6UNIT_TEXPRIM;

/* Cow unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_Gear *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitInit( nm6UNIT_TEXPRIM *Uni, nm6ANIM *Ani )
{
  nm6VERTEX V[] =
  {
    {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 0, 0}, {1, 0}, {0, 0, 1}, {1, 1, 1, 1}},
    {{0, 1, 0}, {0, 1}, {0, 0, 1}, {1, 1, 1, 1}},
    {{1, 1, 0}, {1, 1}, {0, 0, 1}, {1, 1, 1, 1}},
  };
  FLT t[2][2] = 
  {
    {0.8, 1},
    {1, 0.3}
  };

  glGenTextures(1, &Uni->TexId);

  glBindTexture(GL_TEXTURE_2D, Uni->TexId);
  glTexImage2D(GL_TEXTURE_2D, 0, 1, 2, 2, 0, GL_LUMINANCE, GL_FLOAT, t);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  NM6_RndPrimCreateGrid(&Uni->Pr, 2, 2, V); 
} /* End of 'NM6_UnitInit' function */

/* Cow unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_Gear *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitResponse( nm6UNIT_TEXPRIM *Uni, nm6ANIM *Ani )
{
} /* End of 'NM6_UnitResponse' function */

/* Cow unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_Gear *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitClose( nm6UNIT_TEXPRIM *Uni, nm6ANIM *Ani )
{
  NM6_RndPrimFree(&Uni->Pr);
} /* End of 'NM6_UnitResponse' function */

/* Cow unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       nm6UNIT_Gear *Uni;
 *   - animation context:
 *       nm6ANIM *Ani;
 * RETURNS: None.
 */
static VOID NM6_UnitRender( nm6UNIT_TEXPRIM *Uni, nm6ANIM *Ani )
{
  glActiveTexture(GL_TEXTURE + 1);
  glBindTexture(GL_TEXTURE_2D, Uni->TexId);

  NM6_RndPrimDraw(&Uni->Pr, MatrIdentity());
} /* End of 'NM6_UnitRender' function */

/* Unit cow creation function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (nm6UNIT *) pointer to created unit.
 */
nm6UNIT * NM6_UnitCreateTEXPRIM( VOID )
{
  nm6UNIT *Uni;

  if ((Uni = (nm6UNIT *)NM6_AnimUnitCreate(sizeof(nm6UNIT_TEXPRIM))) == NULL)
    return NULL;

  /* Setup unit methods */
  Uni->Init = (VOID *)NM6_UnitInit;
  Uni->Response = (VOID *)NM6_UnitResponse;
  Uni->Render = (VOID *)NM6_UnitRender;
  Uni->Close = (VOID *)NM6_UnitClose;

  return Uni;
} /* End of 'NM6_UnitCreateGear' function */


/* END OF 'u_ball.c' FUNCTION */
#endif