//
// Created by mikipaw on 08.04.2022.
// Copyright (c) 2022 MIPT. All rights reserved.
//

#include "mandelbrotSSEcpp.h"


void Create_Mandelbrot(float xC, float yC, float dx, float dy)  {
    glBegin(GL_POINTS);

    const int width     = glutGet(GLUT_WINDOW_WIDTH);
    const int height    = glutGet(GLUT_WINDOW_HEIGHT);

    for (int j = 0; j < height; ++j) {

        float x = ((            - 400.f) * dx) + xC;
        float y = (((float)j    - 300.f) * dy) + yC;

        for (int i = 0; i < width; i += 8, x += dx * 8) {
            a8float _76543210(7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f);
            a8float x0 = a8float(x) + _76543210 * a8float(dx);
            a8float y0 (y);
            a8float MAX_RADIUS (100.f);

            a8float X = x0;
            a8float Y = y0;

            a8int iterations;

            int step = 0;

            for (step = 0; step < MAX_ITERATIONS; step++) {
                a8float x2  = X * X;
                a8float y2  = Y * Y;

                a8float r2 = x2 + y2;

                a8float cmp = r2 <= MAX_RADIUS;
                if (! +cmp) break;

                iterations = iterations - (a8int) (cmp);

                a8float xy = X * Y;

                X = x2 - y2 + x0;
                Y = xy + xy + y0;
            }

            for (int k = 0; k < 8; k++) {
                auto *buffer = (int*) &iterations;
                RGBQUAD pixel = (buffer[k] < MAX_ITERATIONS) ? RGBQUAD {u_char (buffer[k]), u_char ((float) buffer[k] / 256 * (float) buffer[k]), u_char (128 - buffer[k]), 1} : RGBQUAD { u_char (step * k) , u_char (k * k), u_char (k * 32), 0 };
                glColor3f((float) pixel.rgbRed / 256.f, (float) pixel.rgbGreen / 256.f, (float) pixel.rgbBlue / 256.f);
                glVertex2i(i + k, j);
            }
        }
    }
    glEnd();
}

void CalculateFrameRate() {
    char* source = new char[BUFFER_SIZE];

    static float    framesPerSecond = 0.0f;
    static int      fps             = 0;
    static float    lastTime        = 0.0f;

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


