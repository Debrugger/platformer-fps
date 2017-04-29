#include "sysinc.h"
#include "defines.h"
#include "vector.h"
#include "shader.h"
#include "glbuffer.h"
#include "mesh.h"
#include "texture.h"
#include "matrix.h"
#include "object.h"
#include "platform.h"
#include "glglobals.h"
#include "playercontrols.h"

Vector cam_pos, cam_to;
Vector cam_velocity;
Platform* landed_platform;

void PlayerControls()
{
    double p;
    double diff;
	 Vector v, up;

    if (key_w ^ key_s) /* entweder w oder s sind gedr?ckt, aber NICHT beide!!!! */
    {
        v = cam_to - cam_pos;
        v.Normalize();

        v *= CAM_SPEED;
        if (key_s)
            v *= -1.0;
        cam_to.x += v.x;
        cam_to.z += v.z;
        cam_pos.x += v.x;
        cam_pos.z += v.z;
    }

    if (key_a ^ key_d)
    {
        v = cam_to - cam_pos;
        v.Normalize();

        up.Set(0.0, 1.0, 0.0);

        v = Cross(v, up);
        v.Normalize();

        v *= CAM_SPEED;
        if (key_a)
            v *= -1.0;
        cam_to += v;
        cam_pos += v;
    }

    if (key_q ^ key_e)
    {
        if (key_e)
        {
            cam_to.y += CAM_SPEED;
            cam_pos.y += CAM_SPEED;
        }
        else
        {
            cam_to.y -= CAM_SPEED;
            cam_pos.y -= CAM_SPEED;
        }
    }

    if (cheat_mode)
        return;
    if (landed_platform)
    {
        if (!landed_platform->Collision())
            landed_platform = 0;
        else
        {
            p = landed_platform->matrix.m[3][1] + landed_platform->mesh->max_y + PLAYER_HEIGHT;
            diff = p - cam_pos.y;
            cam_pos.y = p;
            cam_to.y += diff;
        }
    }
    else
    {
        cam_to += cam_velocity;
        cam_pos += cam_velocity;
        cam_velocity.y -= GRAVITY;
        if (cam_velocity.y < 0.0)
        {
            for (Platform* platform = Platform::FirstPlatform(); platform; platform = platform->NextPlatform())
            {
                if (platform->Collision())
                {
                    platform->Land();
                    printf("landed on a platform\n");
                }
            }
        }
    }
}

void Jump()
{
    if (landed_platform)
    {
        cam_velocity.y = 0.6;
        landed_platform = 0;
    }
}
