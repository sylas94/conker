#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_80085EB0;
extern f32 D_80085EB4;
extern f32 D_80085EB8;
extern f32 D_80085EBC;
extern f32 D_80098D90[];

// Matches with the help of several register-allocation "forcers" the decomp-permuter
// found (verified load-bearing: removing any regresses the score): bits captures the
// bit-pattern of x, scaledX captures x*D_80085EB0, pysq (=&ysq) reloads ysq through
// memory in the polynomial, and the two `fn = x` / `y = x` copies pin x in a register.
f32 sinf(f32 x)
{
  f32 xsq;
  f32 y;
  f32 ysq;
  f32 scaledX;
  int bits;
  f32 result;
  f32 fn;
  f32 *pysq;
  f32 *c;
  s32 n;
  s32 m;
  pysq = &ysq;
  m = ((bits = *((s32 *) (&x))) >> 22) & 0x1FF;
  fn = x;
  if (m < 0xFF)
  {
    fn = x;
    if (m >= 0xE6)
    {
      xsq = fn * fn;
      c = D_80098D90;
      result = (((((c[4] * xsq) + c[3]) * xsq) + c[2]) * xsq) + c[1];
      return ((fn * xsq) * result) + fn;
    }
    return x;
  }
  if (m < 0x136)
  {
    y = x;
    fn = (scaledX = y * D_80085EB0);
    if (0.0f <= scaledX)
    {
      n = (s32) (fn + 0.5f);
    }
    else
    {
      n = (s32) (scaledX - 0.5f);
    }
    fn = (f32) n;
    y = y - (fn * D_80085EB4);
    y = y - (fn * D_80085EB8);
    ysq = y * y;
    c = D_80098D90;
    result = (((((c[4] * (*pysq)) + c[3]) * (*pysq)) + c[2]) * (*pysq)) + c[1];
    if ((n & 1) == 0)
    {
      return ((y * ysq) * result) + y;
    }
    return -(((y * ysq) * result) + y);
  }
  if (x != x)
  {
    return D_8002C920;
  }
  return D_80085EBC;
}
