#include "graphics/canvas.hpp"
#include "raylib.h"

#include <iterator>
#include <iostream>

namespace graphics {
    Canvas::Canvas(int w, int h, const char *title) : CanvasWidth(w), CanvasHeight(h) {
        InitWindow(CanvasWidth, CanvasHeight, title);
        SetTargetFPS(60);

        // Create render texture for double buffering and pixel manipulation
        renderTexture = LoadRenderTexture(CanvasWidth, CanvasHeight);

        // Clear to white initially
        BeginTextureMode(renderTexture);
        ClearBackground(WHITE);
        EndTextureMode();
    }

    Canvas::~Canvas() {
        UnloadRenderTexture(renderTexture);
        CloseWindow();
    }

    void Canvas::SetViewPort(float Vx, float Vy, float d) {
        this->ViewWidth = Vx;
        this->ViewHeight = Vy;
        this->Distance = d;
    }

    /**
     * PutPixel draw a pixel into the canvas using the X, Y coordinates and the color.
     * The Pixels in this DrawPixel are written in the next way:
     * ---------------------------------------------------> X
     * \
     * \
     * \
     * \
     * \
     * \
     * \
     * \
     * \
     * v
     * Y
     * @param x
     * @param y
     * @param color
     */
    std::string ColorToString(const Color& color) {
        if (color.r == 255 && color.g == 0 && color.b == 0) return "RED";
        if (color.r == 0 && color.g == 255 && color.b == 0) return "GREEN";
        if (color.r == 0 && color.g == 0 && color.b == 255) return "BLUE";
        if (color.r == 255 && color.g == 255 && color.b == 255) return "WHITE";
        if (color.r == 0 && color.g == 0 && color.b == 0) return "BLACK";
        if (color.r == 255 && color.g == 255 && color.b == 0) return "YELLOW";

        // For any other color, return RGBA values
        return "RGBA(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")";
    }

    void Canvas::PutPixel(int x, int y, const Color& color) {
        // Standard screen coordinates: (0,0) at top-left
        if (IsInBounds(x, y)) {
            BeginTextureMode(renderTexture);
            DrawPixel(x, y, color);
            EndTextureMode();
        }
    }

    void Canvas::PutPixelCentered(int x, int y, const Color& color) {
        // Convert from book's coordinate system (center origin) to screen coordinates
        int screenX = CanvasWidth / 2 + x;
        int screenY = CanvasHeight / 2 - y; // Flip Y axis (book has Y+ pointing up)

        PutPixel(screenX, screenY, color);
    }

    Vector3 Canvas::CanvasToViewPort(int x, int y) {
        // Match JavaScript exactly: viewport_size = 1
        const Vector3 result{
            static_cast<float>(x) * ViewWidth / static_cast<float>(CanvasWidth),
            -(static_cast<float>(y) * ViewHeight / static_cast<float>(CanvasHeight)),
            Distance};
        return result;
    }

    void Canvas::Clear(Color color) {
        background = color;
        BeginTextureMode(renderTexture);
        ClearBackground(color);
        EndTextureMode();
    }

    void Canvas::Present() {
        BeginDrawing();
        ClearBackground(WHITE);

        // Draw the render texture to screen (try without flipping first)
        DrawTextureRec(
            renderTexture.texture,
            (Rectangle){0, 0, static_cast<float>(CanvasWidth), static_cast<float>(CanvasHeight)},
            (Vector2){0, 0},
            WHITE
        );

        // Optional: Show FPS counter
        DrawFPS(10, 10);

        EndDrawing();
    }

    bool Canvas::ShouldClose() const {
        return WindowShouldClose();
    }

    bool Canvas::IsInBounds(int x, int y) const {
        return x >= 0 && x < CanvasWidth && y >= 0 && y < CanvasHeight;
    }

    bool Canvas::IsInBoundsCentered(int x, int y) const {
        return x >= -CanvasWidth / 2 && x < CanvasWidth / 2 && y >= -CanvasHeight / 2 && y < CanvasHeight / 2;
    }
} // namespace graphics
