#include "graphics/canvas.hpp"
#include "graphics/raytracing.hpp"
#include "raylib.h"
#include <iostream>
#include <limits>
#include <string>

using namespace graphics;

int main() {
    std::cout << "=== Graphics from Scratch - Simple Version ===" << std::endl;
    std::cout << "Canvas coordinate system: Center origin, Y+ points up" << std::endl;
    std::cout << "Press ESC or close window to exit" << std::endl;
    std::cout << std::endl;

    // Create canvas - this matches the book's typical setup
    const int canvasWidth = 800;
    const int canvasHeight = 600;
    Vector3 CameraPosition{0, 0, 0};
    Canvas canvas(canvasWidth, canvasHeight, "Computer Graphics from Scratch - Simple");
    canvas.SetViewPort(1.0f, 1.0f, 1.0f);
    Raytracer raytracer(canvas);

    std::cout << "Canvas created: " << canvasWidth << "x" << canvasHeight << std::endl;
    std::cout << "ViewWidth: " << canvas.GetViewWidth() << ", ViewHeight: " << canvas.GetViewHeight() << std::endl;
    std::cout << "Starting main rendering loop..." << std::endl;

    canvas.Clear(WHITE);

    for (int x = -canvas.GetWidth()/2; x <= canvas.GetWidth()/2; x += 1) {
        for (int y = -canvas.GetHeight()/2; y <= canvas.GetHeight()/2; y += 1) {
            Vector3 direction = canvas.CanvasToViewPort(x, y);
            Color color = raytracer.TraceRay(CameraPosition, direction, 1, std::numeric_limits<float>::infinity());
            canvas.PutPixelCentered(x, y, color);
        }
    }
    
    canvas.Present();

    // Keep window open for viewing
    while (!canvas.ShouldClose()) {
        canvas.Present();
    }

    std::cout << "Graphics from Scratch project terminated successfully." << std::endl;
    return 0;
}

/*
 * USAGE EXAMPLES:
 *
 * // Basic colors (raylib built-ins)
 * canvas.PutPixel(x, y, RED);
 * canvas.PutPixel(x, y, GREEN);
 * canvas.PutPixel(x, y, BLUE);
 *
 * // Custom colors
 * Color myColor = {255, 128, 0, 255}; // Orange
 * canvas.PutPixel(x, y, myColor);
 *
 * // Centered coordinates (book style)
 * canvas.PutPixelCentered(0, 0, WHITE); // Center of screen
 *
 * This simple canvas is perfect for implementing the book's algorithms!
 */