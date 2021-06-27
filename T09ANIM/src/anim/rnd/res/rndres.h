/* FILE NAME : rndres.h
 * PROGRAMMER: NM6
 * DATE      : 21.06.2021 
 * PURPOSE   : Rendering declaration module
 */

#ifndef __rndres_h_
#define __rndres_h_
                          
#include "../../../def.h"

#define NM6_STR_MAX 300
#define NM6_MAX_TEXTURES 30

typedef struct tagnm6SHADER
{
  CHAR Name[NM6_STR_MAX]; /* Shader filename prefix */
  INT ProgId;             /* Shader program Id */
} nm6SHADER;

#define NM6_MAX_SHADERS 30
extern nm6SHADER NM6_RndShaders[NM6_MAX_SHADERS];
extern INT NM6_RndShadersSize;


VOID NM6_RndShadersInit( VOID );
VOID NM6_RndShadersClose( VOID );
INT NM6_RndShaderAdd( CHAR *FileNamePrefix );
VOID NM6_RndShadersUpdate( VOID );

#define NM6_MTL_SIZE 100
#define NM6_MAX_MATERIALS 10

typedef struct tagnm6MATERIAL
{
  CHAR Name[NM6_MTL_SIZE];
  VEC Ka, Kd, Ks;
  FLT Ph;
  FLT Trans;
  INT Tex[8];

  /* Shader string */
  CHAR ShaderStr[NM6_MTL_SIZE];
  INT ShdNo;
} nm6MATERIAL;

extern nm6MATERIAL NM6_RndMaterials[NM6_MAX_MATERIALS];
extern INT NM6_RndMaterialsSize;

VOID NM6_RndMtlInit( VOID );
VOID NM6_RndMtlClose( VOID );
INT NM6_RndMtlAdd( nm6MATERIAL *mtl );
INT NM6_RndMtlApply( INT MtlNo );

/***
 * Textures stock functions
 ***/

typedef struct tagnm6TEXTURE
{
  CHAR Name[NM6_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} nm6TEXTURE;

extern nm6TEXTURE NM6_RndTextures[NM6_MAX_TEXTURES];
extern INT NM6_RndTexturesSize;

/***
 * Base textures functions
 ***/

/* Texture stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID NM6_RndTexturesInit( VOID );

/* Texture stock deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID NM6_RndTexturesClose( VOID );

/* Texture add to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size:
 *       INT W, H;
 *   - texture bytes per pixel:
 *       INT C;
 *   - texture pixel colors pointer:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) shader number in stock.
 */
INT NM6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );

#endif