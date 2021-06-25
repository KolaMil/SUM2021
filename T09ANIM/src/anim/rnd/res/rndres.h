/* FILE NAME : rndres.h
 * PROGRAMMER: NM6
 * DATE      : 21.06.2021 
 * PURPOSE   : Rendering declaration module
 */

#ifndef __rndres_h_
#define __rndres_h_

#include "../../anim.h"

#define NM6_STR_MAX  300    
#define NM6_MAX_SHADERS  47 

typedef struct tagnm6SHADER
{
  INT ProgId;
  CHAR Name[NM6_STR_MAX];
} nm6SHADER;

/* Shader stock array and it size */
extern nm6SHADER NM6_RndShaders[NM6_MAX_SHADERS];
extern INT NM6_RndShadersSize;

/* Shader add to stock function.
 * ARGUMENTS:
 *   - shader folder prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader number in stock.
 */
INT NM6_RndShaderAdd( CHAR *FileNamePrefix );

/* Shader add to stock function.
 * ARGUMENTS:
 *   - shader folder prefix:
 *       CHAR *FileNamePrefix;
 * RETURNS:
 *   (INT) shader number in stock.
 */
INT NM6_RndShaderAdd( CHAR *FileNamePrefix );

/* Shader stock deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID NM6_RndShadersClose( VOID );

/* Shader stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID NM6_RndShadersInit( VOID );

/* Delete shader program function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETUNS: None.
 */
VOID NM6_RndShdFree( INT ProgId );

/* Load shader program function.
 * ARGUMENTS:
 *   - shader folder prefix (in 'BIN/SHADERS/***'):
 *       CHAR *FileNamePrefix;
 * RETUNS:
 *   (INT) load shader program Id.
 */
INT NM6_RndShdLoad( CHAR *FileNamePrefix );

/* Shader stock update function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID NM6_RndShadersUpdate( VOID );


#endif /* __rndres_h_ */