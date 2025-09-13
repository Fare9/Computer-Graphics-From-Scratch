
#pragma once

#include "raylib.h"
#include "canvas.hpp"

#include <memory>
#include <utility>

namespace graphics {
/**
 * @struct Sphere
 * @brief Represents a sphere in 3D space for ray tracing.
 * 
 * In Chapter 2 theory, spheres are defined by their center point and radius.
 * They serve as the fundamental geometric primitive for ray tracing because
 * ray-sphere intersection has a closed-form mathematical solution using
 * the quadratic formula. The sphere equation is: |P - C|² = r²
 * where P is any point on the sphere, C is the center, and r is the radius.
 */
struct Sphere {
    Vector3 center;  ///< Center point of the sphere in 3D space (C in Chapter 2)
    float radius;    ///< Radius of the sphere (r in Chapter 2) 
    Color color;     ///< Surface color of the sphere for rendering
};

/**
 * @class Raytracer  
 * @brief Implements basic ray tracing algorithm from Chapter 2.
 * 
 * Ray tracing works by casting rays from the camera through each pixel
 * of the viewport and determining what objects they intersect. For each
 * pixel, we compute a ray direction, then find the closest intersection
 * with scene objects. This class implements the core ray tracing loop
 * and sphere intersection calculations described in Chapter 2.
 */
class Raytracer {
    // we need a reference to the canvas
    std::reference_wrapper<Canvas> canvas;
    Sphere spheres[5]{};

    /**
     * @brief Computes ray-sphere intersection using quadratic formula.
     * @param origin Ray origin point (camera position)
     * @param direction Ray direction vector (normalized)
     * @param sphere The sphere to test intersection with
     * @return Pair of intersection distances (t1, t2), or infinity if no intersection
     * 
     * Implements the mathematical solution from Chapter 2. A ray can be
     * parameterized as P(t) = O + t*D where O is origin, D is direction.
     * Substituting into sphere equation |P - C|² = r² gives a quadratic
     * equation in t: at² + bt + c = 0, solved using quadratic formula.
     */
    [[nodiscard]] std::pair<float, float> IntersectRaySphere(const Vector3& origin, const Vector3& direction, const Sphere& sphere) const;
public:
    /**
     * @brief Constructor for Raytracer.
     * @param canvas Reference to the canvas for rendering output
     * 
     * Initializes the raytracer with a predefined scene containing several
     * spheres. In Chapter 2, the scene is kept simple to focus on the
     * core ray tracing algorithm rather than complex scene management.
     */
    explicit Raytracer(Canvas& canvas);

    /**
     * @brief Traces a ray through the scene and returns the color.
     * @param origin Ray starting point (typically camera position)
     * @param direction Ray direction vector (should be normalized)
     * @param t_min Minimum intersection distance (avoids self-intersection)
     * @param t_max Maximum intersection distance (viewing range limit)
     * @return Color of the closest intersected object, or background color
     * 
     * This is the core ray tracing function from Chapter 2. For each ray,
     * it finds the closest intersection with scene objects within the
     * specified distance range. Returns the color of the closest object,
     * implementing the basic visibility algorithm.
     */
    Color TraceRay(const Vector3& origin, const Vector3& direction, float t_min, float t_max);
};

}