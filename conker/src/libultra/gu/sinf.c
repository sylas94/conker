#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_80085EB0;
extern f32 D_80085EB4;
extern f32 D_80085EB8;
extern f32 D_80085EBC;
extern f32 D_80098D90[];

// Matches with the help of several register-allocation "forcers" the decomp-permuter
// found (verified load-bearing: removing any regresses the score): new_var2 captures the
// bit-pattern of x, new_var3 captures x*D_80085EB0, new_var (=&ysq) reloads ysq through
// memory in the polynomial, and the two `fn = x` / `y = x` copies pin x in a register.
f32 sinf(f32 x)
{
  f32 xsq;
  f32 y;
  f32 ysq;
  f32 new_var3;
  int new_var2;
  f32 result;
  f32 fn;
  f32 *new_var;
  f32 *c;
  s32 n;
  s32 m;
  new_var = &ysq;
  m = ((new_var2 = *((s32 *) (&x))) >> 22) & 0x1FF;
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
    fn = (new_var3 = y * D_80085EB0);
    if (0.0f <= new_var3)
    {
      n = (s32) (fn + 0.5f);
    }
    else
    {
      n = (s32) (new_var3 - 0.5f);
    }
    fn = (f32) n;
    y = y - (fn * D_80085EB4);
    y = y - (fn * D_80085EB8);
    ysq = y * y;
    c = D_80098D90;
    result = (((((c[4] * (*new_var)) + c[3]) * (*new_var)) + c[2]) * (*new_var)) + c[1];
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
