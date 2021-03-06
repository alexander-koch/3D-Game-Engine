/*
 * Copyright 2015 Alexander Koch
 * File: FilmCamera.h
 * Description: A GLM-based camera class, creates projection and view matrices.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FILMCAMERA_H
#define FILMCAMERA_H

#include <core/Commons.h>
#include <core/Console.h>
#include <rendering/Frustum.h>

class FilmCamera
{
public:
	enum MovementType { FORWARD, BACKWARD, STRAFE_LEFT, STRAFE_RIGHT, UP, DOWN };

	FilmCamera();

	// Set
	void setFOV(float);
	void setViewport(float, float);
	void setViewport(const vec2&);
	void setClipping(float, float);
	void setClipping(const vec2&);
	void setPosition(const vec3&);
	void setTarget(const vec3&);
	void setTargetRaw(const vec3&);
	void setUpVector(const vec3&);

	// Get
	float getFOV();
	float getAspectRatio();
	vec2 getViewport();
	vec2 getClipping();
	vec3 getPosition();
	vec3 getTarget();
	vec3 getOldPosition();
	virtual mat4 getViewMatrix();
	virtual mat4 getProjectionMatrix();
	Frustum getFrustum();
	bool boxInFrustum(const BoundingBox& bbox);

	void move(const MovementType&);
	void rotate(double, double);
	virtual void update();

	void setFlightMode(bool);
	bool getFlightMode();
protected:
	vec2 m_viewport;
	float m_fovy;
	float m_nearPlane;
	float m_farPlane;
	float m_velocity;
	float m_pitchSensitivity;
	float m_yawSensitivity;

	vec3 m_position;
	vec3 m_rotation;
	vec3 m_upVector;
	vec3 m_target;
	vec3 m_direction;
	vec3 m_oldPosition;

	mat4 m_viewMatrix;
	mat4 m_projectionMatrix;
	Frustum m_frustum;

	bool m_flight;
};

#endif
