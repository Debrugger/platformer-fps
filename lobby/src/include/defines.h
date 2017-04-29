#ifndef __DEFINES_H
#define __DEFINES_H

#define GRAVITY               0.3
#define CAM_SPEED_HI          0.1
#define CAM_SPEED_NO          0.05
#define CAM_SPEED_LO          0.02
#define CAM_SPEED             (key_shift ? CAM_SPEED_HI : (key_ctrl ? CAM_SPEED_LO : CAM_SPEED_NO))
#define MOUSE_SENSITIVITY   0.002
#define PLAYER_HEIGHT           0.2

#endif //__DEFINES_H
