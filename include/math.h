#pragma once
#include <cmath>


struct Vector2 {
    float x, y;
};

struct Vector3 {
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    float dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3 cross(const Vector3& v) const {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }

    Vector3 normalize() const {
        float length = std::sqrt(x * x + y * y + z * z);
        if (length == 0) return Vector3(0, 0, 0);
        return Vector3(x / length, y / length, z / length);
    }
};

struct Matrix4 {
    float m[4][4];

    Matrix4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = (i == j) ? 1.0f : 0.0f;
    }

    Matrix4 operator*(const Matrix4& other) const {
        Matrix4 result;
        for (int row = 0; row < 4; ++row)
            for (int col = 0; col < 4; ++col) {
                result.m[row][col] = 0;
                for (int k = 0; k < 4; ++k)
                    result.m[row][col] += m[row][k] * other.m[k][col];
            }
        return result;
    }

    Vector3 transform(const Vector3& v) const {
        float x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
        float y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
        float z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];
        float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];

        if (w != 0.0f) {
            x /= w;
            y /= w;
            z /= w;
        }

        return Vector3(x, y, z);
    }
};
