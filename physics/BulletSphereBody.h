/*
 * Copyright 2015 Alexander Koch
 * File: BulletSphereBody.h
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

#ifndef BULLET_SPHERE_BODY_H
#define BULLET_SPHERE_BODY_H

#include "BulletBody.h"

class BulletSphereBody : public BulletBody
{
public:
	BulletSphereBody();
	~BulletSphereBody();

	void setRadius(double);
	double getRadius();

	void build(const quat&, const vec3&);
private:
	double m_radius;
	btSphereShape* m_shape;
};

#endif
