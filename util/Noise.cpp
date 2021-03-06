/*
 * Copyright 2015 Alexander Koch
 * File: Noise.cpp
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

#include "Noise.h"

const static float GRAD3[16][3] = {
	{ 1, 1, 0}, {-1, 1, 0}, { 1,-1, 0}, {-1,-1, 0},
	{ 1, 0, 1}, {-1, 0, 1}, { 1, 0,-1}, {-1, 0,-1},
	{ 0, 1, 1}, { 0,-1, 1}, { 0, 1,-1}, { 0,-1,-1},
	{ 1, 0,-1}, {-1, 0,-1}, { 0,-1, 1}, { 0, 1, 1}
};

static unsigned char PERM[] = {
	151, 160, 137,  91,  90,  15, 131,  13,
	201,  95,  96,  53, 194, 233,   7, 225,
	140,  36, 103,  30,  69, 142,   8,  99,
	37, 240,  21,  10,  23, 190,   6, 148,
	247, 120, 234,  75,   0,  26, 197,  62,
	94, 252, 219, 203, 117,  35,  11,  32,
	57, 177,  33,  88, 237, 149,  56,  87,
	174,  20, 125, 136, 171, 168,  68, 175,
	74, 165,  71, 134, 139,  48,  27, 166,
	77, 146, 158, 231,  83, 111, 229, 122,
	60, 211, 133, 230, 220, 105,  92,  41,
	55,  46, 245,  40, 244, 102, 143,  54,
	65,  25,  63, 161,   1, 216,  80,  73,
	209,  76, 132, 187, 208,  89,  18, 169,
	200, 196, 135, 130, 116, 188, 159,  86,
	164, 100, 109, 198, 173, 186,   3,  64,
	52, 217, 226, 250, 124, 123,   5, 202,
	38, 147, 118, 126, 255,  82,  85, 212,
	207, 206,  59, 227,  47,  16,  58,  17,
	182, 189,  28,  42, 223, 183, 170, 213,
	119, 248, 152,   2,  44, 154, 163,  70,
	221, 153, 101, 155, 167,  43, 172,   9,
	129,  22,  39, 253,  19,  98, 108, 110,
	79, 113, 224, 232, 178, 185, 112, 104,
	218, 246,  97, 228, 251,  34, 242, 193,
	238, 210, 144,  12, 191, 179, 162, 241,
	81,  51, 145, 235, 249,  14, 239, 107,
	49, 192, 214,  31, 181, 199, 106, 157,
	184,  84, 204, 176, 115, 121,  50,  45,
	127,   4, 150, 254, 138, 236, 205,  93,
	222, 114,  67,  29,  24,  72, 243, 141,
	128, 195,  78,  66, 215,  61, 156, 180,
	151, 160, 137,  91,  90,  15, 131,  13,
	201,  95,  96,  53, 194, 233,   7, 225,
	140,  36, 103,  30,  69, 142,   8,  99,
	37, 240,  21,  10,  23, 190,   6, 148,
	247, 120, 234,  75,   0,  26, 197,  62,
	94, 252, 219, 203, 117,  35,  11,  32,
	57, 177,  33,  88, 237, 149,  56,  87,
	174,  20, 125, 136, 171, 168,  68, 175,
	74, 165,  71, 134, 139,  48,  27, 166,
	77, 146, 158, 231,  83, 111, 229, 122,
	60, 211, 133, 230, 220, 105,  92,  41,
	55,  46, 245,  40, 244, 102, 143,  54,
	65,  25,  63, 161,   1, 216,  80,  73,
	209,  76, 132, 187, 208,  89,  18, 169,
	200, 196, 135, 130, 116, 188, 159,  86,
	164, 100, 109, 198, 173, 186,   3,  64,
	52, 217, 226, 250, 124, 123,   5, 202,
	38, 147, 118, 126, 255,  82,  85, 212,
	207, 206,  59, 227,  47,  16,  58,  17,
	182, 189,  28,  42, 223, 183, 170, 213,
	119, 248, 152,   2,  44, 154, 163,  70,
	221, 153, 101, 155, 167,  43, 172,   9,
	129,  22,  39, 253,  19,  98, 108, 110,
	79, 113, 224, 232, 178, 185, 112, 104,
	218, 246,  97, 228, 251,  34, 242, 193,
	238, 210, 144,  12, 191, 179, 162, 241,
	81,  51, 145, 235, 249,  14, 239, 107,
	49, 192, 214,  31, 181, 199, 106, 157,
	184,  84, 204, 176, 115, 121,  50,  45,
	127,   4, 150, 254, 138, 236, 205,  93,
	222, 114,  67,  29,  24,  72, 243, 141,
	128, 195,  78,  66, 215,  61, 156, 180
};

void seed(unsigned int x) {
	srand(x);
	for(auto i = 0; i < 256; i++) PERM[i] = i;
	for(auto i = 255; i > 0; i--) {
		int j;
		int n = i + 1;
		while (n <= (j = rand() / (RAND_MAX / n)));
		unsigned char a = PERM[i];
		unsigned char b = PERM[j];
		PERM[i] = b;
		PERM[j] = a;
	}
	memcpy(PERM + 256, PERM, sizeof(unsigned char) * 256);
}

float noise2(float x, float y) {
	float s = (x + y) * F2;
	float i = floorf(x + s);
	float j = floorf(y + s);
	float t = (i - j) * G2;

	float xx[3], yy[3], f[3];
	float noise[3] = {0.0, 0.0, 0.0};
	int g[3];

	xx[0] = x - (i - t);
	yy[0] = y - (j - t);

	int i1 = xx[0] > yy[0];
	int j1 = xx[0] <= yy[0];

	xx[2] = xx[0] + G2 * 2.0 - 1.0;
	yy[2] = yy[0] + G2 * 2.0 - 1.0;
	xx[1] = xx[0] - i1 + G2;
	yy[1] = yy[0] - j1 + G2;

	int I = (int) i & 255;
	int J = (int) j & 255;

	g[0] = PERM[I + PERM[J]] % 12;
	g[1] = PERM[I + i1 + PERM[J + j1]] % 12;
	g[2] = PERM[I + 1 + PERM[J + 1]] % 12;

	for(auto c = 0; c <= 2; c++) {
		f[c] = 0.5f - xx[c]*xx[c] - yy[c]*yy[c];
	}

	for(auto c = 0; c <= 2; c++) {
		if(f[c] > 0) {
			noise[c] = f[c] * f[c] * f[c] * f[c] * (GRAD3[g[c]][0] * xx[c] + GRAD3[g[c]][1] * yy[c]);
		}
	}

	return (noise[0] + noise[1] + noise[2]) * 70.0f;
}

float simplex2(float x, float y, float octaves, float persistence, float lacunarity) {
	float freq = 1.0;
	float amp = 1.0;
	float max = 1.0;
	float total = noise2(x,y);
	for(auto i = 1; i < octaves; i++) {
		freq *= lacunarity;
		amp *= persistence;
		max += amp;
		total += noise2(x * freq, y * freq) * amp;
	}
	return (1 + total / max) * 0.5;
}
