#include "renderer.h"
#include <cstring>
#include <algorithm>
#include <iostream>

Renderer::Renderer(Window* window) : window_(window) {
    SDL_Renderer* renderer = window_->getRenderer();
    SDL_GetRendererOutputSize(renderer, &width_, &height_);
    
    texture_ = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width_, height_);

    pixelsBuffer_ = new Uint32[width_ * height_];
    depthBuffer_ = new float[width_ * height_];

}

Renderer::~Renderer() {
    delete[] depthBuffer_;
    delete[] pixelsBuffer_;
    SDL_DestroyTexture(texture_);
}

void Renderer::clear() {
    memset(pixelsBuffer_, 0, width_ * height_ * sizeof(Uint32));
    std::fill(depthBuffer_, depthBuffer_ + width_ * height_, std::numeric_limits<float>::infinity());

}

void Renderer::present() {
    SDL_UpdateTexture(texture_, nullptr, pixelsBuffer_, width_ * sizeof(Uint32));
    
    SDL_Renderer* sdlRenderer = window_->getRenderer();
    SDL_RenderClear(sdlRenderer);
    SDL_RenderCopy(sdlRenderer, texture_, nullptr, nullptr);
    SDL_RenderPresent(sdlRenderer);
}

void Renderer::drawPixel(int x, int y, float depth, Uint32 color) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) return;
    int index = y * width_ + x;
    if (depth < depthBuffer_[index]) {
        depthBuffer_[index] = depth;
        pixelsBuffer_[index] = color;
    }
}


void Renderer::drawPixel(int x, int y, Uint32 color) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) return;
    pixelsBuffer_[y * width_ + x] = color;
}

void Renderer::drawLine(int x0, int y0, int x1, int y1, Uint32 color) {
    int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; 

    for (;;) {
        drawPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; } 
        if (e2 <= dx) { err += dx; y0 += sy; } 
    }
}

void Renderer::drawTriangle(const Vector2& v1, const Vector2& v2, const Vector2& v3, Uint32 color) {
    drawLine(v1.x, v1.y, v2.x, v2.y, color);
    drawLine(v2.x, v2.y, v3.x, v3.y, color);
    drawLine(v3.x, v3.y, v1.x, v1.y, color);
}
void Renderer::fillTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2, Uint32 color) {
    Vector2 vertices[3] = {v0, v1, v2};
    if (vertices[1].y < vertices[0].y) std::swap(vertices[0], vertices[1]);
    if (vertices[2].y < vertices[1].y) std::swap(vertices[1], vertices[2]);
    if (vertices[1].y < vertices[0].y) std::swap(vertices[0], vertices[1]);

    float invslope1 = 0;
    float invslope2 = 0;

    int yStart = vertices[0].y;
    int yEnd = vertices[2].y;

    for (int y = yStart; y <= yEnd; y++) {
        bool secondHalf = y > vertices[1].y || vertices[1].y == vertices[0].y;
        int segmentHeight = secondHalf ? vertices[2].y - vertices[1].y : vertices[1].y - vertices[0].y;

        if (segmentHeight == 0) continue;

        invslope1 = secondHalf ? (float)(vertices[2].x - vertices[1].x) / (vertices[2].y - vertices[1].y)
                               : (float)(vertices[1].x - vertices[0].x) / (vertices[1].y - vertices[0].y);
        invslope2 = (float)(vertices[2].x - vertices[0].x) / (vertices[2].y - vertices[0].y);

        float x1 = secondHalf ? vertices[1].x + (y - vertices[1].y) * invslope1
                              : vertices[0].x + (y - vertices[0].y) * invslope1;
        float x2 = vertices[0].x + (y - vertices[0].y) * invslope2;

        if (x1 > x2) std::swap(x1, x2);

        for (int x = (int)x1; x <= (int)x2; x++) {
            drawPixel(x, y, color);
        }
    }
}


void Renderer::drawTriangle3D(const Vector3& v0, const Vector3& v1, const Vector3& v2, const Matrix4& mvpMatrix, Uint32 color) {
    Vector3 p0 = mvpMatrix.transform(v0);
    Vector3 p1 = mvpMatrix.transform(v1);
    Vector3 p2 = mvpMatrix.transform(v2);

    auto ndcToScreen = [this](const Vector3& ndc) {
        return Vector2{
            (ndc.x + 1.0f) * 0.5f * width_,
            (1.0f - ndc.y) * 0.5f * height_ 
        };
    };

    Vector2 screenP0 = ndcToScreen(p0);
    Vector2 screenP1 = ndcToScreen(p1);
    Vector2 screenP2 = ndcToScreen(p2);

    drawTriangle(screenP0, screenP1, screenP2, color);
}

void Renderer::displayFps() {
    static int frameCount = 0;
    static Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime = SDL_GetTicks();
    frameCount++;

    if (currentTime - lastTime >= 1000) {
        std::cout << "FPS: " << frameCount << std::endl;
        frameCount = 0;
        lastTime = currentTime;
    }
}