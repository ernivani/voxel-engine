#pragma once
#include "math.h"
#include <vector>

struct Mesh {
    std::vector<Vector3> vertices;
    std::vector<int> indices;
};

Mesh createCubeMesh() {
    Mesh cube;

    cube.vertices = {
        {-1, -1, -1}, // 0
        { 1, -1, -1}, // 1
        { 1,  1, -1}, // 2
        {-1,  1, -1}, // 3
        // face arriere
        {-1, -1,  1}, // 4
        { 1, -1,  1}, // 5
        { 1,  1,  1}, // 6
        {-1,  1,  1}  // 7
    };

    cube.indices = {
        0, 1, 2,  2, 3, 0,
        5, 4, 7,  7, 6, 5,
        4, 0, 3,  3, 7, 4,
        1, 5, 6,  6, 2, 1,
        3, 2, 6,  6, 7, 3,
        4, 5, 1,  1, 0, 4
    };

    return cube;
}
