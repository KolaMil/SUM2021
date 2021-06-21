/* FILE NAME: u_ball.c
 * PROGRAMMER: Nm6
 * DATE: 19.06.2021
 * PURPOSE: Unit samples cretion funtions.
 */

#include <time.h>

#include "units.h"

typedef struct tagnm6UNIT_BALL
{
  NM6_UNIT_BASE_FIELDS;
  nm6PRIM Ball;
  DBL timeShift, TimeScale;
} nm6UNIT_BALL

static VOID NM6_UnitInit( nm6UNIT_BALL *Uni, nm6ANIM *Ani )
{
  NM6_RndPrimCreateSphere(&Uni->Ball, VecSet(0, 0, 0), 1, 18, 8);
  Uni->Ball.Trans = MatrTranslete(VecSet(Rnd1() * 8, 0, Rnd1() * 8));
  Uni->timeShift = rand() % 50 + 102;
}

static VOID NM6_UnitRender( nm6UNIT_BALL *Uni, nm6ANIM *Ani )
{
  DBL t = clock() / 1000.0;

  NM6_RndPrimDraw(&Uni->Ball,
    MatrTranslete(VecSet(0, 3 * fabs(sin(Uni ->TimeShift + Uni->TimeSlace * 8 * t)), 0)));
} /* End of 'NM6_UnitRender' fuction */


static VOID NM6_UnitClose( nm6UNIT_BALL *Unit, nm6ANIM *Ani )
{
  NM6_RndPrimFree(&Uni->Ball);
}

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  VOID (*Init)( UNIT *Uni, ANIM *Ani );
  VOID (*Close)( UNIT *Uni, ANIM *Ani );
  VOID (*Response)( UNIT *Uni, ANIM *Ani );
  VOID (*Render)( UNIT *Uni, ANIM *Ani );
};

nm6UNIT * NM6_UnitCreateBounceBall( VOID )
{
  nm6UNIT *Uni;

  if ((Uni = NM6_AnimUnitCreate(sizeof(nm6UNIT_BALL))) == NULL)
    return NULL;

  Uni->Init = (VOID *)NM6_UnitInit;
  Uni->Close = (VOID *)NM6_UnitClose;
  Uni->Response = (VOID *)NM6_UnitResponse;
  Uni->Render = (VOID *)NM6_UnitRender;
  return Uni;
} /* End of 'NM6_UnitCreateBounceBall' fuction*/

/* END OF 'u_ball.c' FILE */

