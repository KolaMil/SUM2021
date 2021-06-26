/* FILE NAME : rndtex.c
 * PROGRAMMER : NM6
 * DATE : 21.06.2021 
 * PURPOSE : Ball unit module
 */

#include <string.h>

#include "../rnd.h"

/***
 * Textures stock functions
 ***/

/* Textures stock array and it size */
nm6TEXTURE NM6_RndTextures[NM6_MAX_TEXTURES];
INT NM6_RndTexturesSize;

/***
 * Base textures functions
 ***/

/* Texture stock initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID NM6_RndTexturesInit( VOID )
{
  NM6_RndTexturesSize = 0;
} /* End of 'NM6_RndTexturesInit' function */

/* Texture stock deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID NM6_RndTexturesClose( VOID )
{
  INT i;

  for (i = 0; i < NM6_RndTexturesSize; i++)
    glDeleteTextures(1, &NM6_RndTextures[i].TexId);
  NM6_RndTexturesSize = 0;
} /* End of 'NM6_RndTexturesInit' function */

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
INT NM6_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits )
{
  INT MipLevels;

  if (NM6_RndTexturesSize >= NM6_MAX_SHADERS)
    return 0;
  strncpy(NM6_RndTextures[NM6_RndTexturesSize].Name, Name, NM6_STR_MAX - 1);
  NM6_RndTextures[NM6_RndTexturesSize].W = W;
  NM6_RndTextures[NM6_RndTexturesSize].H = H;
  
  /* Move image to GPU memory */
  glGenTextures(1, &NM6_RndTextures[NM6_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, NM6_RndTextures[NM6_RndTexturesSize].TexId);

  MipLevels = log(W < H ? W : H) / log(2);
  MipLevels = MipLevels < 1 ? 1 : MipLevels;
  glTexStorage2D(GL_TEXTURE_2D, MipLevels, C == 4 ? GL_RGBA8 : C == 3 ? GL_RGB8 : GL_R8, W, H);
  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H,
    C == 4 ? GL_RGBA : C == 3 ? GL_RGB : GL_LUMINANCE, GL_UNSIGNED_BYTE, Bits);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glBindTexture(GL_TEXTURE_2D, 0);

  return NM6_RndTexturesSize++;
} /* End of 'NM6_RndTexturesAdd' function */

/* END OF 'rndtex.c' FILE */
