#include "sysinc.h"
#include "qtinc.h"
#include "filereader.h"
#include "glbuffer.h"
#include "vector.h"
#include "matrix.h"
#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "glglobals.h"
#include "texture.h"
#include "object.h"
#include "character_file.h"
/* character file:
 name= should then be synced with server to figure out max health, mvmt speed etc...
 body=name of central body object
 rfoot=name of right foot
 lfoot=name of left foot
 rarm=
 larm=
 crfoot=coords of rfoot relative to body origin
 clfoot
 crarm
 clarm
 tbody=texture for body in tex directory
 trfoot
 tlfoot
 trarm
 tlarm
 */
