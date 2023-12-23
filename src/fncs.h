#ifndef RAYCASTER_FNCS_H
#define RAYCASTER_FNCS_H

#include "raylib.h"
#include <stdio.h>
#include <math.h>

double distance(Vector3 v1, Vector3 v2)
{
    double dx = v1.x - v2.x;
    double dy = v1.y - v2.y;
    double dz = v1.z - v2.z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

#endif
