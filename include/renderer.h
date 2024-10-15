#pragma once 
#include "math.h"
#include "window.h"
#include "SDL2/SDL.h"

class Renderer {
public:
	Renderer(Window* window);
	~Renderer();

	void clear();
	void present();

    void drawPixel(int x, int y, float depth, Uint32 color);

    void drawPixel(int x, int y, Uint32 color);
	void drawLine(int x1, int y1, int x2, int y2, Uint32 color);
	void drawTriangle(const Vector2& v1, const Vector2& v2, const Vector2& v3, Uint32 color);
    void fillTriangle(const Vector2 &v1, const Vector2 &v2, const Vector2 &v3, Uint32 color);

    void drawTriangle3D(const Vector3 &v0, const Vector3 &v1, const Vector3 &v2, const Matrix4 &mvpMatrix, Uint32 color);

	void displayFps();

private:
	Window* window_;
	SDL_Texture* texture_;
	Uint32* pixelsBuffer_;
	int width_;
	int height_;
    float* depthBuffer_;
};