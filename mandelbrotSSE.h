//
// Created by mikipaw on 04.04.2022.
// Copyright (c) 2022 MIPT. All rights reserved.
//

#ifndef MANDELBROT_MANDELBROTSSE_H
#define MANDELBROT_MANDELBROTSSE_H

#include <GL/gl.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <immintrin.h>
#include <cstdint>
#include <cstdio>
#include <complex.h>

using std::complex;

const size_t BUFFER_SIZE = 8;
const int    MAX_ITERATIONS = 255;

void Create_Mandelbrot(float xC, float yC, float dx, float dy);

void Create_MandelbrotSSE(float xC, float yC, float dx, float dy);

void CalculateFrameRate();

#endif //MANDELBROT_MANDELBROTSSE_H
