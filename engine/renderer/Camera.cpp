#include "Camera.h"
#include <cstring>
#include <algorithm>

Camera::Camera() {
    setIdentity(projection);
    setIdentity(view);
    setIdentity(viewProjection);
    updateCameraVectors();
}

void Camera::setPosition(float x, float y, float z) {
    posX = x;
    posY = y;
    posZ = z;
    recalculateViewMatrix();
}

void Camera::getPosition(float& x, float& y, float& z) const {
    x = posX;
    y = posY;
    z = posZ;
}

void Camera::moveForward(float amount) {
    posX += frontX * amount;
    posY += frontY * amount;
    posZ += frontZ * amount;
    recalculateViewMatrix();
}

void Camera::moveRight(float amount) {
    posX += rightX * amount;
    posY += rightY * amount;
    posZ += rightZ * amount;
    recalculateViewMatrix();
}

void Camera::moveUp(float amount) {
    // Move along camera's local up vector (screen space up/down)
    posX += upX * amount;
    posY += upY * amount;
    posZ += upZ * amount;
    recalculateViewMatrix();
}

void Camera::setRotation(float newYaw, float newPitch) {
    yaw = newYaw;
    // Clamp pitch to avoid gimbal lock
    pitch = std::max(-89.0f, std::min(89.0f, newPitch));
    updateCameraVectors();
    recalculateViewMatrix();
}

void Camera::processMouseMovement(float deltaX, float deltaY, float sensitivity) {
    yaw += deltaX * sensitivity;
    pitch -= deltaY * sensitivity;  // Inverted Y for natural feel
    
    // Clamp pitch to avoid flipping
    pitch = std::max(-89.0f, std::min(89.0f, pitch));
    
    updateCameraVectors();
    recalculateViewMatrix();
}

void Camera::recalculateViewMatrix() {
    // Calculate camera basis vectors
    float zAxisX = -frontX;
    float zAxisY = -frontY;
    float zAxisZ = -frontZ;
    
    float xAxisX = rightX;
    float xAxisY = rightY;
    float xAxisZ = rightZ;
    
    float yAxisX = upX;
    float yAxisY = upY;
    float yAxisZ = upZ;
    
    // Build view matrix (rotation part)
    view[0] = xAxisX;
    view[1] = yAxisX;
    view[2] = zAxisX;
    view[3] = 0.0f;
    
    view[4] = xAxisY;
    view[5] = yAxisY;
    view[6] = zAxisY;
    view[7] = 0.0f;
    
    view[8] = xAxisZ;
    view[9] = yAxisZ;
    view[10] = zAxisZ;
    view[11] = 0.0f;
    
    // Translation part (dot products)
    view[12] = -(xAxisX * posX + xAxisY * posY + xAxisZ * posZ);
    view[13] = -(yAxisX * posX + yAxisY * posY + yAxisZ * posZ);
    view[14] = -(zAxisX * posX + zAxisY * posY + zAxisZ * posZ);
    view[15] = 1.0f;
    
    // viewProjection = projection * view
    multiplyMatrices(projection, view, viewProjection);
}

void Camera::updateCameraVectors() {
    // Calculate front vector from yaw and pitch
    float yawRad = toRadians(yaw);
    float pitchRad = toRadians(pitch);
    
    frontX = std::cos(yawRad) * std::cos(pitchRad);
    frontY = std::sin(pitchRad);
    frontZ = std::sin(yawRad) * std::cos(pitchRad);
    normalize(frontX, frontY, frontZ);
    
    // Calculate right vector = cross(front, worldUp)
    cross(frontX, frontY, frontZ, worldUpX, worldUpY, worldUpZ, rightX, rightY, rightZ);
    normalize(rightX, rightY, rightZ);
    
    // Calculate up vector = cross(right, front)
    cross(rightX, rightY, rightZ, frontX, frontY, frontZ, upX, upY, upZ);
    normalize(upX, upY, upZ);
}

void Camera::getForward(float& x, float& y, float& z) const {
    x = frontX;
    y = frontY;
    z = frontZ;
}

void Camera::getRight(float& x, float& y, float& z) const {
    x = rightX;
    y = rightY;
    z = rightZ;
}

void Camera::getUp(float& x, float& y, float& z) const {
    x = upX;
    y = upY;
    z = upZ;
}

void Camera::setIdentity(float* matrix) {
    std::memset(matrix, 0, 16 * sizeof(float));
    matrix[0] = 1.0f;
    matrix[5] = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;
}

void Camera::multiplyMatrices(const float* a, const float* b, float* result) {
    float temp[16];
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            temp[col * 4 + row] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                temp[col * 4 + row] += a[k * 4 + row] * b[col * 4 + k];
            }
        }
    }
    std::memcpy(result, temp, 16 * sizeof(float));
}

void Camera::normalize(float& x, float& y, float& z) {
    float length = std::sqrt(x * x + y * y + z * z);
    if (length > 0.0001f) {
        x /= length;
        y /= length;
        z /= length;
    }
}

void Camera::cross(float ax, float ay, float az, float bx, float by, float bz, float& rx, float& ry, float& rz) {
    rx = ay * bz - az * by;
    ry = az * bx - ax * bz;
    rz = ax * by - ay * bx;
}


// ==================== Perspective Camera ====================

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane)
    : fovValue(fov), aspectRatioValue(aspectRatio), nearPlaneValue(nearPlane), farPlaneValue(farPlane) {
    setPerspective(fov, aspectRatio, nearPlane, farPlane);
    recalculateViewMatrix();
}

void PerspectiveCamera::setPerspective(float fov, float aspectRatio, float nearPlane, float farPlane) {
    fovValue = fov;
    aspectRatioValue = aspectRatio;
    nearPlaneValue = nearPlane;
    farPlaneValue = farPlane;
    
    setIdentity(projection);
    
    float tanHalfFov = std::tan(toRadians(fov) / 2.0f);
    
    projection[0] = 1.0f / (aspectRatio * tanHalfFov);
    projection[5] = 1.0f / tanHalfFov;
    projection[10] = -(farPlane + nearPlane) / (farPlane - nearPlane);
    projection[11] = -1.0f;
    projection[14] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
    projection[15] = 0.0f;
    
    recalculateViewMatrix();
}


// ==================== Orthographic Camera ====================

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float nearPlane, float farPlane)
    : leftValue(left), rightValue(right), bottomValue(bottom), topValue(top), 
      nearPlaneValue(nearPlane), farPlaneValue(farPlane), zoomValue(1.0f) {
    updateProjection();
    recalculateViewMatrix();
}

void OrthographicCamera::setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    leftValue = left;
    rightValue = right;
    bottomValue = bottom;
    topValue = top;
    nearPlaneValue = nearPlane;
    farPlaneValue = farPlane;
    
    updateProjection();
    recalculateViewMatrix();
}

void OrthographicCamera::setZoom(float zoom) {
    zoomValue = std::max(0.01f, zoom);  // Prevent zero or negative zoom
    updateProjection();
    recalculateViewMatrix();
}

void OrthographicCamera::updateProjection() {
    setIdentity(projection);
    
    // Apply zoom by scaling the bounds
    float l = leftValue / zoomValue;
    float r = rightValue / zoomValue;
    float b = bottomValue / zoomValue;
    float t = topValue / zoomValue;
    
    projection[0] = 2.0f / (r - l);
    projection[5] = 2.0f / (t - b);
    projection[10] = -2.0f / (farPlaneValue - nearPlaneValue);
    
    projection[12] = -(r + l) / (r - l);
    projection[13] = -(t + b) / (t - b);
    projection[14] = -(farPlaneValue + nearPlaneValue) / (farPlaneValue - nearPlaneValue);
    projection[14] = -(farPlaneValue + nearPlaneValue) / (farPlaneValue - nearPlaneValue);
    projection[15] = 1.0f;
}
