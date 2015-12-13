#include "Camera.h"


Camera::Camera()
{
	pos = vec3(0, 0, -1);
	pitch = 0.0f;
	yaw = 0.0f;
}


Camera::~Camera()
{
}

void Camera::turn(float dx, float dy)
{
	yaw += dx * .1;
	pitch += dy * .1;

	float pie = (float)M_PI;

	//keep the camera in range for up and down at pi
	clamp(pitch, -pie, pie);

	//keep camera in range for left/right
	if (yaw < pie)
	{
		yaw += 2 * pie;
	}
	else
	{
		yaw -= pie;
	}
}

void Camera::move(vec3 movement)
{
	pos += movement;
}

vec3 Camera::getForward()
{
	vec3 forward;
	float fx = cos(pitch) * sin(yaw);
	float fy = sin(pitch) * 1;
	float fz = -cos(pitch) * cos(yaw);
	forward = vec3(fx, fy, fz);
	//cout << "Forward Vector Magnitude: " << forward.length() << endl; 
	return forward;
}

vec3 Camera::getUp()
{
	vec3 up;
	float pie = (float)M_PI;

	float upX = cos(pitch + pie / 2) * sin(yaw);
	float upY = sin(pitch + pie / 2) * 1;
	float upZ = -cos(pitch + pie / 2) * cos(yaw);
	up = vec3(upX, upY, upZ);
	return up;
}

vec3 Camera::getRight()
{
	vec3 right = cross(getForward(), getUp());
	return right;
}

vec3 Camera::getLocation()
{
	return pos;
}

void Camera::setLocation(vec3 p)
{
	pos = p;
}

vec3 Camera::getLookAt()
{
	vec3 lookat = getLocation() + getForward();
	return lookat;
}

vec3 Camera::normalizeVec(const vec3 &v)
{
	float length_of_v = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	vec3 normalized = vec3(v.x / length_of_v, v.y / length_of_v, v.z / length_of_v);
	return normalized;
}