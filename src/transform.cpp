#include "transform.h"

Matrix4 createTranslationMatrix(float tx, float ty, float tz) {
    Matrix4 mat;
    mat.m[3][0] = tx;
    mat.m[3][1] = ty;
    mat.m[3][2] = tz;
    return mat;
}

Matrix4 createScaleMatrix(float sx, float sy, float sz) {
    Matrix4 mat;
    mat.m[0][0] = sx;
    mat.m[1][1] = sy;
    mat.m[2][2] = sz;
    return mat;
}

Matrix4 createRotationXMatrix(float angle) {
    Matrix4 mat;
    float c = cos(angle);
    float s = sin(angle);
    mat.m[1][1] = c;
    mat.m[1][2] = s;
    mat.m[2][1] = -s;
    mat.m[2][2] = c;
    return mat;
}

Matrix4 createRotationYMatrix(float angle) {
    Matrix4 mat;
    float c = cos(angle);
    float s = sin(angle);
    mat.m[0][0] = c;
    mat.m[0][2] = -s;
    mat.m[2][0] = s;
    mat.m[2][2] = c;
    return mat;
}

Matrix4 createRotationZMatrix(float angle) {
    Matrix4 mat;
    float c = cos(angle);
    float s = sin(angle);
    mat.m[0][0] = c;
    mat.m[0][1] = s;
    mat.m[1][0] = -s;
    mat.m[1][1] = c;
    return mat;
}

Matrix4 createPerspectiveProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane) {
    Matrix4 mat;
    float f = 1.0f / tan(fov / 2.0f);
    mat.m[0][0] = f / aspectRatio;
    mat.m[1][1] = f;
    mat.m[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
    mat.m[2][3] = -1.0f;
    mat.m[3][2] = (2 * farPlane * nearPlane) / (nearPlane - farPlane);
    mat.m[3][3] = 0.0f;
    return mat;
}