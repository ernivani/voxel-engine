#include "window.h"
#include "renderer.h"
#include "math.h"
#include "transform.h"
#include "mesh.h"
#include "camera.h"
#include <SDL2/SDL.h>

void handleEvent(bool &isRunning, Camera &camera);

int main(int argc,char* argv[]) {

	Window window("3d Engine", 800, 600);
	Renderer renderer(&window);
	Camera camera;

    Mesh cube = createCubeMesh();


    float fov = 90.0f * M_PI / 180.0f;
    float aspectRatio = 800.0f / 600.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    Matrix4 projectionMatrix = createPerspectiveProjectionMatrix(fov, aspectRatio, nearPlane, farPlane);

    float angle = 0.0f;

    bool isRunning = true;

	while (isRunning) {

		handleEvent(isRunning, camera);

		renderer.clear();




        angle += 0.01f;

        Matrix4 rotation = createRotationYMatrix(angle);
        Matrix4 modelMatrix = rotation;

		Matrix4 viewMatrix = camera.getViewMatrix();

        Matrix4 mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;

        renderer.clear();

        for (size_t i = 0; i < cube.indices.size(); i += 3) {
            Vector3 v0 = cube.vertices[cube.indices[i]];
            Vector3 v1 = cube.vertices[cube.indices[i + 1]];
            Vector3 v2 = cube.vertices[cube.indices[i + 2]];

            renderer.drawTriangle3D(v0, v1, v2, mvpMatrix, 0x0000FFFF);
        }

		renderer.displayFps();
		renderer.present();
	}

}
void handleEvent(bool &isRunning, Camera &camera)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				isRunning = false;
				break;
			case SDLK_z:
				camera.position.z += 0.1f;
				break;
			case SDLK_s:
				camera.position.z -= 0.1f;
				break;
			case SDLK_q:
				camera.position.x -= 0.1f;
				break;
			case SDLK_d:
				camera.position.x += 0.1f;
				break;
			}
		}

	}
	
}