/*
 * Copyright 2015 Alexander Koch
 * File: Property.cpp
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

#include "Property.h"

Property::Property(const string& key) : m_key(key) {}

Property::operator bool()
{
	bool value = false;
	PropertyParser::getInstance().getProperty(m_key, value);
	return value;
}

Property::operator int()
{
	int value = 0;
	PropertyParser::getInstance().getProperty(m_key, value);
	return value;
}

Property::operator float()
{
	float value = 0;
	PropertyParser::getInstance().getProperty(m_key, value);
	return value;
}

Property::operator string()
{
	string value = "";
	PropertyParser::getInstance().getProperty(m_key, value);
	return value;
}
