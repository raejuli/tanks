#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include <glad/glad.h>
#include <cmath>
#include <cstring>
#include <algorithm>

// Base camera class for 3D rendering
// Provides common functionality for all camera types
class Camera {
public:
    Camera();
    virtual ~Camera() = default;

    // Get the view-projection matrix (combined for efficiency)
    const float* getViewProjectionMatrix() const { return viewProjection; }
    
    // Get separate matrices
    const float* getProjectionMatrix() const { return projection; }
    const float* getViewMatrix() const { return view; }

    // Camera position in world space
    void setPosition(float x, float y, float z);
    void getPosition(float& x, float& y, float& z) const;
    
    // Move camera relative to its current orientation
    void moveForward(float amount);
    void moveRight(float amount);
    void moveUp(float amount);  // World up (Y axis)

    // Rotation (Euler angles in degrees)
    void setRotation(float yaw, float pitch);
    float getYaw() const { return yaw; }
    float getPitch() const { return pitch; }
    
    // Process mouse movement (like Unity FPS controller)
    void processMouseMovement(float deltaX, float deltaY, float sensitivity = 0.1f);

    // Recalculate view matrix after position/rotation changes
    void recalculateViewMatrix();

    // Get camera direction vectors
    void getForward(float& x, float& y, float& z) const;
    void getRight(float& x, float& y, float& z) const;
    void getUp(float& x, float& y, float& z) const;

protected:
    float projection[16];
    float view[16];
    float viewProjection[16];

    // Position
    float posX = 0.0f;
    float posY = 0.0f;
    float posZ = 0.0f;

    // Rotation (degrees)
    float yaw = -90.0f;    // Looking along -Z by default
    float pitch = 0.0f;

    // Direction vectors (calculated from yaw/pitch)
    float frontX = 0.0f, frontY = 0.0f, frontZ = -1.0f;
    float rightX = 1.0f, rightY = 0.0f, rightZ = 0.0f;
    float upX = 0.0f, upY = 1.0f, upZ = 0.0f;

    // World up vector
    static constexpr float worldUpX = 0.0f;
    static constexpr float worldUpY = 1.0f;
    static constexpr float worldUpZ = 0.0f;

    // Helper functions
    void setIdentity(float* matrix);
    void multiplyMatrices(const float* a, const float* b, float* result);
    void updateCameraVectors();
    
    // Math helpers
    static float toRadians(float degrees) { return degrees * 3.14159265358979323846f / 180.0f; }
    static void normalize(float& x, float& y, float& z);
    static void cross(float ax, float ay, float az, float bx, float by, float bz, float& rx, float& ry, float& rz);
};


// 3D Perspective camera
class PerspectiveCamera : public Camera {
public:
    PerspectiveCamera(float fov, float aspectRatio, float nearPlane = 0.1f, float farPlane = 1000.0f);
    
    // Update perspective projection (e.g., on window resize)
    void setPerspective(float fov, float aspectRatio, float nearPlane = 0.1f, float farPlane = 1000.0f);
    
    float getFOV() const { return fovValue; }
    float getAspectRatio() const { return aspectRatioValue; }

private:
    float fovValue;
    float aspectRatioValue;
    float nearPlaneValue;
    float farPlaneValue;
};


// 3D Orthographic camera
class OrthographicCamera : public Camera {
public:
    // Create with orthographic bounds
    // left, right, bottom, top define the view volume
    OrthographicCamera(float left, float right, float bottom, float top, float nearPlane = -100.0f, float farPlane = 100.0f);
    
    // Update orthographic projection
    void setOrthographic(float left, float right, float bottom, float top, float nearPlane = -100.0f, float farPlane = 100.0f);
    
    // Zoom (scales the view volume)
    void setZoom(float zoom);
    float getZoom() const { return zoomValue; }

private:
    float leftValue, rightValue, bottomValue, topValue;
    float nearPlaneValue, farPlaneValue;
    float zoomValue = 1.0f;
    
    void updateProjection();
};

#endif //ENGINE_CAMERA_H
