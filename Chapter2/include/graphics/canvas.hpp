#pragma once

#include "raylib.h"

namespace graphics {

    /**
     * @class Canvas
     * @brief Represents a 2D canvas for computer graphics operations.
     * 
     * This class implements the canvas concept from Chapter 2, which serves as the 
     * fundamental drawing surface for computer graphics. In Chapter 2 theory, the canvas
     * is defined as a 2D grid of pixels with coordinate system transformations between
     * canvas coordinates (pixel space) and viewport coordinates (world space).
     * 
     * The canvas abstracts the concept of a raster display where each position
     * corresponds to a pixel that can be assigned a color value.
     */
    class Canvas {
        // Cx
        int CanvasWidth;
        // Cy
        int CanvasHeight;
        // Vx
        float ViewWidth;
        // Vy
        float ViewHeight;
        // d(istance)
        float Distance;
        // Color of the background
        Color background;


        RenderTexture2D renderTexture;

    public:
        /**
         * @brief Constructor for Canvas class.
         * @param w Canvas width in pixels (Cx in Chapter 2 notation)
         * @param h Canvas height in pixels (Cy in Chapter 2 notation)  
         * @param title Window title for the display
         * 
         * Creates a canvas with the specified dimensions. In Chapter 2 theory, the canvas
         * dimensions define the resolution of our raster display. The canvas uses a 
         * coordinate system where (0,0) is at the top-left corner, with X increasing
         * rightward and Y increasing downward (standard screen coordinates).
         */
        Canvas(int w, int h, const char* title = "Graphics from Scratch");
        
        /**
         * @brief Destructor for Canvas class.
         * 
         * Cleans up graphics resources and closes the display window.
         * Essential for proper resource management in graphics applications.
         */
        ~Canvas();

        /**
         * @brief Sets the viewport parameters for 3D to 2D projection.
         * @param Vx Viewport width (Vw in Chapter 2)
         * @param Vy Viewport height (Vh in Chapter 2)
         * @param d Distance from camera to projection plane
         * 
         * In Chapter 2 theory, the viewport represents the 3D window through which
         * we view the scene. It acts as the projection plane where 3D points are
         * mapped to 2D canvas coordinates. The distance 'd' determines the field
         * of view - smaller values create wider angles (fish-eye effect).
         */
        void SetViewPort(float Vx, float Vy, float d);

        // Core functions - use raylib's Color directly
        /**
         * @brief Sets a pixel color at the specified canvas coordinates.
         * @param x X coordinate in canvas space (0 to width-1)
         * @param y Y coordinate in canvas space (0 to height-1)
         * @param color RGB color value to set
         * 
         * This is the fundamental rasterization operation from Chapter 2 theory.
         * It directly maps a color value to a discrete pixel location in the
         * canvas buffer. Uses standard screen coordinates with (0,0) at top-left.
         */
        void PutPixel(int x, int y, const Color& color);
        
        /**
         * @brief Sets a pixel using centered coordinate system.
         * @param x X coordinate relative to canvas center
         * @param y Y coordinate relative to canvas center (positive Y points up)
         * @param color RGB color value to set
         * 
         * Implements the coordinate system used in Chapter 2, where the origin
         * is at the canvas center and positive Y points upward. This matches
         * the mathematical convention used in the book's examples and makes
         * 3D-to-2D projection calculations more intuitive.
         */
        void PutPixelCentered(int x, int y, const Color& color);

        /**
         * @brief Converts canvas coordinates to viewport coordinates.
         * @param x Canvas X coordinate (pixel space)
         * @param y Canvas Y coordinate (pixel space)
         * @return Vector3 representing viewport coordinates (Vx, Vy, d)
         * 
         * This implements the fundamental coordinate transformation from Chapter 2.
         * Canvas coordinates are discrete pixel positions, while viewport coordinates
         * are continuous world space coordinates. The transformation maps:
         * - Canvas space: [0, Cw-1] × [0, Ch-1] (discrete pixels)  
         * - Viewport space: [-Vw/2, Vw/2] × [-Vh/2, Vh/2] × d (continuous world)
         */
        Vector3 CanvasToViewPort(int x, int y);

        // Canvas management
        /**
         * @brief Clears the entire canvas to a solid color.
         * @param color The color to fill the canvas with (default: BLACK)
         * 
         * This operation resets all pixels in the canvas buffer to the specified
         * color value. Essential for clearing the frame buffer between renders
         * in real-time graphics applications.
         */
        void Clear(Color color = BLACK);
        
        /**
         * @brief Presents the canvas contents to the display.
         * 
         * Copies the canvas buffer to the actual display device. This implements
         * double buffering - we draw to an off-screen buffer and then present
         * the complete frame all at once to avoid visual artifacts.
         */
        void Present();
        
        /**
         * @brief Checks if the display window should be closed.
         * @return true if window close was requested, false otherwise
         * 
         * Used in the main render loop to detect when the user wants to
         * terminate the graphics application.
         */
        [[nodiscard]] bool ShouldClose() const;

        // Getters
        /**
         * @brief Gets the canvas width in pixels.
         * @return Canvas width (Cw in Chapter 2 notation)
         */
        [[nodiscard]] int GetWidth() const { return CanvasWidth; }
        
        /**
         * @brief Gets the canvas height in pixels.  
         * @return Canvas height (Ch in Chapter 2 notation)
         */
        [[nodiscard]] int GetHeight() const { return CanvasHeight; }

        /**
         * @brief Gets the viewport width.
         * @return Viewport width (Vw in Chapter 2 notation)
         */
        [[nodiscard]] float GetViewWidth() const { return ViewWidth; }
        
        /**
         * @brief Gets the viewport height.
         * @return Viewport height (Vh in Chapter 2 notation)  
         */
        [[nodiscard]] float GetViewHeight() const { return ViewHeight; }

        [[nodiscard]] Color& GetBackground() { return background; }

        // Bounds checking
        /**
         * @brief Checks if coordinates are within canvas bounds (screen coordinates).
         * @param x X coordinate to check
         * @param y Y coordinate to check  
         * @return true if (x,y) is within [0, width-1] × [0, height-1]
         * 
         * Essential for preventing buffer overruns when drawing pixels.
         * Uses standard screen coordinate system with origin at top-left.
         */
        [[nodiscard]] bool IsInBounds(int x, int y) const;
        
        /**
         * @brief Checks if coordinates are within canvas bounds (centered coordinates).
         * @param x X coordinate relative to center
         * @param y Y coordinate relative to center
         * @return true if (x,y) is within centered coordinate bounds
         * 
         * Bounds checking for the Chapter 2 coordinate system where origin
         * is at canvas center. Used with PutPixelCentered function.
         */
        [[nodiscard]] bool IsInBoundsCentered(int x, int y) const;
    };

} // namespace graphics