#include <time.h>
#include "units.h"

/* typedef nm6UNIT_COW */
typedef struct
{
  UNIT_BASE_FIELDS;
  nm6PRIM Cow;
  VEC Pos;
} nm6UNIT_COW;

/* Cow unit initialization function
* ARGUMENTS:
* - self-pointer to unit object
* nm6UNIT_BALL *Uni;
* - animation context:
* nm6ANIM *Ani;
* RETURNS: None.
*/
static VOID nm6_UnitInit( nm6UNIT_COW *Uni, nm6ANIM *Ani )
{
  NM6_RndPrimLoad(&Uni->Cow, "cow.obj");
}/* End of 'nm6_UnitInit' function */


/* Cow unit inter frame events handle function
* ARGUMENTS:
* - self-pointer to unit object
* nm6UNIT_BALL *Uni;
* - animation context:
* nm6ANIM *Ani;
* RETURNS: None.
*/
static VOID nm6_UnitResponse( nm6UNIT_COW *Uni, nm6ANIM *Ani )
{
}/* End of 'nm6_UnitResponse' function */


/* Bounce ball unit render function
* ARGUMENTS:
* - self-pointer to unit object
* nm6UNIT_BALL *Uni;
* - animation context:
* nm6ANIM *Ani;
* RETURNS: None.
*/
static VOID nm6_UnitRender( nm6UNIT_COW *Uni, nm6ANIM *Ani )
{
  NM6_RndPrimDraw(&Uni->Cow, MatrRotateY(180 * sin(Ani->Time)));
}/* End of 'nm6_UnitRender' function */


/* Unit ball creation function
* ARGUMENTS: None.
* RETURNS:
* (nm6UNIT *) pointer to created unit
*/
/*nm6UNIT * nm6_UnitCreateCow( VOID )
{
  nm6UNIT *Uni;

  if ((Uni = (nm6UNIT *)nm6_AnimUnitCreate(sizeof(nm6UNIT_COW))) == NULL)
    return NULL;

  /* Setup unit methods */
  /*Uni->Init = (VOID *)nm6_UnitInit;
  Uni->Response = (VOID *)nm6_UnitResponse;
  Uni->Render = (VOID *)nm6_UnitRender;

  return Uni;
}/* End of 'nm6_UnitCreateCow' function */