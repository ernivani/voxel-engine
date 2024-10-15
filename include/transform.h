#pragma once
#include "math.h"

Matrix4 createTranslationMatrix(float tx, float ty, float tz);
Matrix4 createScaleMatrix(float sx, float sy, float sz);
Matrix4 createRotationXMatrix(float angle);
Matrix4 createRotationYMatrix(float angle);
Matrix4 createRotationZMatrix(float angle);
Matrix4 createPerspectiveProjectionMatrix(float fov, float aspectRatio, float nearPlane, float farPlane);