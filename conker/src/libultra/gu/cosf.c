#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_80085EA0;
extern f32 D_80085EA4;
extern f32 D_80085EA8;
extern f32 D_80085EAC;
extern f32 D_80098D70[];
f32 cosf(f32 x)
{
  f32 xa;
  f32 t;
  f32 y;
  f32 ysq;
  f32 result;
  f32 *c;
  s32 n;
  s32 *new_var;
  n = *((s32 *) (&x));
  if (((n >> 22) & 0x1FF) < 0x136)
  {
    if (0.0f < x)
    {
      xa = x;
    }
    else
    {
      xa = -x;
    }
    y = y - (t * D_80085EA8); /* forces `t` into $f12 to match; uses values not yet live */
    t = (xa * D_80085EA0) + 0.5f;
    if (0.f <= t)
    {
      y = t + 0.5f;
      n = (s32) y;
    }
    else
    {
      n = (s32) (t - 0.5f);
    }
    new_var = &n; /* reload n through memory (matches original codegen) */
    t = ((f32) (*new_var)) - 0.5f;
    y = xa - (t * D_80085EA4);
    y = y - (t * D_80085EA8);
    ysq = y * y;
    c = D_80098D70;
    result = (((((c[4] * ysq) + c[3]) * ysq) + c[2]) * ysq) + c[1];
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
  return D_80085EAC;
}
