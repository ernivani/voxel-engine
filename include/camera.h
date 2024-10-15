#pragma once
#include "math.h"

class Camera {
public:
    Vector3 position;
    Vector3 target;
    Vector3 up;

    Camera() : position(0, 0, -5), target(0, 0, 0), up(0, 1, 0) {}

    Matrix4 getViewMatrix() const {
        Vector3 zaxis = (target - position).normalize();
        Vector3 xaxis = up.cross(zaxis).normalize();
        Vector3 yaxis = zaxis.cross(xaxis);

        Matrix4 view;
        view.m[0][0] = xaxis.x; view.m[1][0] = xaxis.y; view.m[2][0] = xaxis.z;
        view.m[0][1] = yaxis.x; view.m[1][1] = yaxis.y; view.m[2][1] = yaxis.z;
        view.m[0][2] = zaxis.x; view.m[1][2] = zaxis.y; view.m[2][2] = zaxis.z;
        view.m[3][0] = -xaxis.dot(position);
        view.m[3][1] = -yaxis.dot(position);
        view.m[3][2] = -zaxis.dot(position);
        return view;
    }
};