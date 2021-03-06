/*
 * Copyright 2015 Alexander Koch
 * File: StringUtils.h
 * Description: Utility functions for strings.
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

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <cstdarg>
#include <algorithm>
#include <cstdio>
#include <string>
using std::string;

namespace StringUtils
{
	/**
	 *	Format a string (vaargs to string)
	 * 	@param format Format to use
	 *	@return formatted string
	 */
	string format_str(const char* format, ...);

	/**
	 *	Simplify:
	 *	replaces spaces with underscores and
	 * 	converts every character to lowercase
	 *	@param source Source input
	 *	@return simplified string
	 */
	string simplify(const string& source);

	/**
	 *	Converts a whole string to lowercase
	 *  @param str Source input
	 *	@return lowercase string
	 */
	string toLower(const string& str);
}

#endif
