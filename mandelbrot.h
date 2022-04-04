//
// Created by mikipaw on 02.04.2022.
// Copyright (c) 2022 MIPT. All rights reserved.
//

#ifndef MANDELBROT_MANDELBROT_H
#define MANDELBROT_MANDELBROT_H

#include <GL/gl.h>
#include <complex>
#include <GL/freeglut_std.h>

using std::complex;

const size_t BUFFER_SIZE = 8;

void Create_Mandelbrot(double x, double dx, double y, double dy);

void CalculateFrameRate() {
    char* source = new char[BUFFER_SIZE];
    static float framesPerSecond = 0.0f;
    static int fps;
    static float lastTime = 0.0f;

    float currentTime = GetTickCount() * 0.001f;
    ++framesPerSecond;

    sprintf(source, "FPS: %d\n", fps);
    glColor3f(0.0f, 1.0f, 0.0f);  //RGBA values of text color
    glRasterPos2f(100, 120);
    size_t str_size = strlen(source);

    for (size_t i = 0; i < str_size; ++i) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, source[i]);

    if (currentTime - lastTime > 1.0f) {
        lastTime = currentTime;
        fps = (int)(framesPerSecond * 2);
        framesPerSecond = 0;
    }

    delete[] source;
}

void Create_Mandelbrot(double x, double dx, double y, double dy) {
    const int MAX_ITERATIONS = 64;

    const int width     = glutGet(GLUT_WINDOW_WIDTH);
    const int height    = glutGet(GLUT_WINDOW_HEIGHT);

    glBegin(GL_POINTS);

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width - 100; ++j)
        {
            complex<double> c(x + (j * dx / width),
                              y + (i * dy / height));

            complex<double> z(0.0, 0.0);

            bool  in_set = false;
            float green  = 0;
            float blue   = 0;
            int   step   = 0;

            for (; abs(z) < 2; ++step) {
                z = (z * z) + c;
                if (step == MAX_ITERATIONS) {
                    in_set = true;
                    break;
                }
            }
            blue = (float) step / MAX_ITERATIONS;

            if(in_set) {
                green = (float) abs(z) / 2;
                glColor3f(0.0, green, blue);
                glVertex2i(j, i);
            }
            else {
                glColor3f(0.0, 0.0, 0.0);
                glVertex2i(j, i);
            }
        }
    }

    glEnd();
}

#endif //MANDELBROT_MANDELBROT_H
