#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800BE9A4;
/* Overlay onto struct108 (the camera) at +0x69C: manual (player-driven)
 * orbit state. Camera eye is at +0x2F8, look-at target at +0x2A4. */
typedef struct
{
  u8 pad0[0x24];
  /* 0x24 */ s32 rotateTimer;
  /* 0x28 */ f32 rotateSpeed;
} CameraManualRotate;
extern f32 D_800A36E0;
void func_1508EF80(struct17 *arg0, struct17 *arg1, f32 arg2, struct17 *arg3);
/* Player-driven camera orbit: spins the camera eye around the look-at target
 * on the Y axis while a rotate button is held, and coasts it back to a stop
 * once the button is released. */
void func_1512D390(struct108 *camera)
{
  CameraManualRotate *rot;
  struct17 *eyePos;
  f32 speed;
  f32 clampedSpeed;
  u16 inputFlags;
  inputFlags = *camera->unk36C;
  rot = (CameraManualRotate *) (((s32) camera) + 0x69C);
  if (((inputFlags & 3) != 0) && ((camera->unk84 << 10) >= 0))
  {
    if (camera->unk698 != 0)
    {
      return;
    }
    if (inputFlags & 1)
    {
      camera->unk6B0 = 1;
    }
    else
    {
      camera->unk6B0 = -1;
    }
    clampedSpeed = -10.0f;
    rot->rotateTimer++;
    rot->rotateSpeed += (((f32) camera->unk6B0) * 0.5f) * D_800BE9A4;
    speed = rot->rotateSpeed;
    if (speed < (-10.0f))
    {
      rot->rotateSpeed = clampedSpeed;
    }
    else
    {
      if (10.0f < speed)
      {
        clampedSpeed = 10.0f;
      }
      else
      {
        clampedSpeed = speed;
      }
      rot->rotateSpeed = clampedSpeed;
    }
    if (camera->unk2C & 0x400)
    {
      rot->rotateTimer = 20;
      return;
    }
    eyePos = (struct17 *) (&camera->unk2F8);
    func_1508EF80(eyePos, (struct17 *) (&camera->unk2A4), (rot->rotateSpeed * D_800BE9A4) / 2.5f, eyePos);
  }
  else
  {
    ;
    if (rot->rotateSpeed != 0.0f)
    {
      eyePos = (struct17 *) (&camera->unk2F8);
      rot->rotateSpeed = rot->rotateSpeed - ((rot->rotateSpeed * D_800A36E0) * D_800BE9A4);
      func_1508EF80(eyePos, (struct17 *) (&camera->unk2A4), (rot->rotateSpeed * D_800BE9A4) / 2.5f, eyePos);
    }
  }
}

