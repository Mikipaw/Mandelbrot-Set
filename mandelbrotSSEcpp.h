//
// Created by mikipaw on 08.04.2022.
// Copyright (c) 2022 MIPT. All rights reserved.
//

#ifndef MANDELBROT_MANDELBROTSSECPP_H
#define MANDELBROT_MANDELBROTSSECPP_H

#include "a8float.h"

const size_t BUFFER_SIZE = 8;
const int    MAX_ITERATIONS = 255;

//Creating Mandelbrot set
void Create_Mandelbrot(float xC, float yC, float dx, float dy);

//Shows fps on the screen
void CalculateFrameRate();


#endif //MANDELBROT_MANDELBROTSSECPP_H
