#include "graphics/raytracing.hpp"
#include "raymath.h"

#include <limits>
#include <cmath>


using namespace graphics;

Raytracer::Raytracer(Canvas &canvas)  : canvas(canvas) {
    spheres[0] = {{0, -1, 3}, 1, Color{255, 0, 0, 255}};       // Red sphere
    spheres[1] = {{-2, 0, 4}, 1, Color{0, 255, 0, 255}};       // Green sphere
    spheres[2] = {{2, 0, 4}, 1, Color{0, 0, 255, 255}};        // Blue sphere
    spheres[3] = {{0, -5001, 0}, 5000, Color{255, 255, 0, 255}}; // Yellow ground
    spheres[4] = {{0, 2, 3}, 1, BLACK};
}

std::pair<float, float> Raytracer::IntersectRaySphere(const Vector3& origin, const Vector3& direction, const Sphere& sphere) const {
    Vector3 oc = Vector3Subtract(origin, sphere.center);

    float k1 = Vector3DotProduct(direction, direction);
    float k2 = 2.0f * Vector3DotProduct(oc, direction);
    float k3 = Vector3DotProduct(oc, oc) - sphere.radius * sphere.radius;

    float discriminant = k2*k2 - 4*k1*k3;

    // this is represented behind the camera...
    if (discriminant < 0) {
        return {std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};
    }

    float t1 = (-k2 + sqrt(discriminant)) / (2*k1);
    float t2 = (-k2 - sqrt(discriminant)) / (2*k1);
    return {t1, t2};
}

Color Raytracer::TraceRay(const Vector3& origin, const Vector3& direction, float t_min, float t_max) {
    
    float closest_t = std::numeric_limits<float>::infinity();
    Sphere * closest_sphere = nullptr;

    for (auto & sphere : spheres) {
        auto [fst, snd] = IntersectRaySphere(origin, direction, sphere);

        if (fst < closest_t && t_min < fst && fst < t_max) {
            closest_t = fst;
            closest_sphere = &sphere;
        }
        if (snd < closest_t && t_min < snd && snd < t_max) {
            closest_t = snd;
            closest_sphere = &sphere;
        }
    }

    if (closest_sphere == nullptr)
        return canvas.get().GetBackground();
    return closest_sphere->color;
}

