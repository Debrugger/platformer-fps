#ifndef __PLAYERCONTROLS_H
#define __PLAYERCONTROLS_H
extern Vector cam_pos, cam_to;
extern Vector cam_velocity;
extern Platform* landed_platform;

void PlayerControls();
void Jump();
#endif //__PLAYERCONTROLS_H
