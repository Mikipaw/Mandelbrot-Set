//
// Created by mikipaw on 02.04.2022.
// Copyright (c) 2022 MIPT. All rights reserved.
//

#ifndef MANDELBROT_MANDELBROT_H
#define MANDELBROT_MANDELBROT_H

#include <GL/gl.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <complex>

/*
 * There is the Mandelbrot set program without optimization.
 */


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
    const int MAX_ITERATIONS = 255;

    const int width     = glutGet(GLUT_WINDOW_WIDTH);
    const int height    = glutGet(GLUT_WINDOW_HEIGHT);

    glBegin(GL_POINTS);

    for (int i = 0; i < height; i += 10)
    {
        for (int j = 0; j < width - 100; j += 10)
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
                if (step >= MAX_ITERATIONS) {
                    in_set = true;
                    break;
                }
            }
            green = (float) step * (float) step / MAX_ITERATIONS;

            /*RGBQUAD pixel = (buffer[k] < MAX_ITERATIONS) ?
                            RGBQUAD {u_char (buffer[k]),u_char ((float) buffer[k] / 256 * (float) buffer[k]), u_char (128 - buffer[k]), 1} :
                            RGBQUAD { u_char (step * k) , u_char (k * k), u_char (k * 32), 0 };
            */

            if(in_set) {
                blue = (float) (128 - step);
                glColor3f((float) step / 256.f, green / 256.f, blue / 256.f);
                glVertex2i(j, i);
            }
            else {
                glColor3f((float) (step * (i + j) % 8) / 256.f, ((i + j) % 8) * ((i + j) % 8) / 256.f,  ((i + j) % 8 * 32) / 256.f);
                glVertex2i(j, i);
            }
        }
    }

    glEnd();
}

void Create_MandelbrotSSE(float xC, float yC, float dx, float dy)  {
    glBegin(GL_POINTS);

    const int width     = glutGet(GLUT_WINDOW_WIDTH);
    const int height    = glutGet(GLUT_WINDOW_HEIGHT);

    for (int j = 0; j < height; ++j) {

        float x = ((            - 400.f) * dx) + xC;
        float y = (((float)j    - 300.f) * dy) + yC;

        __m256 _76543210   = _mm256_set_ps(7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f);

        for (int i = 0; i < width; i += 8, x += dx * 8) {
            __m256 x0 = _mm256_add_ps(_mm256_set1_ps(x), _mm256_mul_ps(_76543210, _mm256_set1_ps (dx)));
            __m256 y0 =               _mm256_set1_ps(y);
            __m256 MAX_RADIUS = _mm256_set1_ps(100.f);

            __m256 X = x0;
            __m256 Y = y0;

            __m256i iterations = _mm256_setzero_si256();

            int step = 0;

            for (step = 0; step < MAX_ITERATIONS; step++) {
                __m256 x2  = _mm256_mul_ps(X, X);
                __m256 y2  = _mm256_mul_ps(Y, Y);

                __m256 r2 = _mm256_add_ps(x2, y2);

                auto cmp = _mm256_cmp_ps(r2, MAX_RADIUS, _CMP_LE_OQ);
                int64_t bitMask = _mm256_movemask_ps(cmp);
                if (!bitMask) break;

                iterations = _mm256_sub_epi32(iterations, _mm256_castps_si256(cmp));

                __m256 xy = _mm256_mul_ps(X, Y);

                X = _mm256_add_ps(_mm256_sub_ps(x2, y2), x0);
                Y = _mm256_add_ps(_mm256_add_ps(xy, xy), y0);
            }

            for (int k = 0; k < 8; k++) {
                auto *buffer = (int*) &iterations;

                RGBQUAD pixel = (buffer[k] < MAX_ITERATIONS) ?
                                RGBQUAD {u_char (buffer[k]),u_char ((float) buffer[k] / 256 * (float) buffer[k]), u_char (128 - buffer[k]), 1} :
                                RGBQUAD { u_char (step * k) , u_char (k * k), u_char (k * 32), 0 };

                glColor3f((float) pixel.rgbRed / 256.f, (float) pixel.rgbGreen / 256.f, (float) pixel.rgbBlue / 256.f);
                glVertex2i(i + k, j);
            }
        }
    }
    glEnd();
}


#endif //MANDELBROT_MANDELBROT_H


