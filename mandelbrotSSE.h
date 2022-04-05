//
// Created by mikipaw on 04.04.2022.
// Copyright (c) 2022 MIPT. All rights reserved.
//

#ifndef MANDELBROT_MANDELBROTSSE_H
#define MANDELBROT_MANDELBROTSSE_H

#include <GL/gl.h>
#include <GL/freeglut_std.h>
#include <complex>
#include <immintrin.h>

using std::complex;

const size_t BUFFER_SIZE = 8;

void Create_Mandelbrot(float x, float dx, float y, float dy);

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

void Create_Mandelbrot(float x, float dx, float y, float dy) {
    const int MAX_ITERATIONS = 256;

    const int width     = glutGet(GLUT_WINDOW_WIDTH);
    const int height    = glutGet(GLUT_WINDOW_HEIGHT);

    glBegin(GL_POINTS);

    const __m256 MaxRadius = _mm256_set1_ps(100.f);
    const __m256 _63 = _mm256_set1_ps(63.f);
    const __m256 _76543210 = _mm256_set_ps(7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f);

    const __m256 max_iter = _mm256_set1_ps(MAX_ITERATIONS);


    for (int i = 0; i < height; ++i) {

        float x0 = (          - 400.f) * dx + x,
                y0 =((float)i - 300.f) * dy + y;

        for (int j = 0; j < width - 100; j += 8, x0 += dx*8) {
            bool  in_set = false;
            float green  = 0;
            float blue   = 0;
            int   step   = 0;

            __m256 X0 = _mm256_add_ps(_mm256_set1_ps(x0), _mm256_mul_ps(_76543210, _mm256_set1_ps(dx)));
            __m256 Y0 =            _mm256_set1_ps (y0);

            __m256 X = X0, Y = Y0;

            __m256i N = _mm256_setzero_si256();

            __m256  r2;

            for (; ; ++step) {
                __m256  x2 = _mm256_mul_ps (X, X),
                        y2 = _mm256_mul_ps (Y, Y);

                        r2 = _mm256_add_ps (x2, y2);

                __m256  cmp = _mm256_cmp_ps(r2, MaxRadius, _CMP_LE_OQ); // r2 < MaxRadius

                int mask = _mm256_movemask_ps(cmp);
                if (mask) {
                    in_set == true;
                    break;
                }

                N = _mm256_sub_epi32(N, _mm256_castps_si256(cmp));

                __m256 xy = _mm256_mul_ps (X, Y);

                X = _mm256_add_ps(_mm256_sub_ps(x2, y2), X0);
                Y = _mm256_add_ps(_mm256_add_ps(xy, xy), Y0);
                //z = (z * z) + c;
                if (step == MAX_ITERATIONS) {
                    in_set = true;
                    break;
                }
            }
//hash tables методом цепочек. Берем русский текст. Хеш таблица с маленьким размером. Длины списков хеш таблицы должны быть достаточны
//
            __m256 I = _mm256_mul_ps (_mm256_sqrt_ps (_mm256_sqrt_ps (_mm256_div_ps (_mm256_cvtepi32_ps(N), max_iter))), _63);

            for (int k = 0; k < 8; k++) {
              int*   pN = (int*)   &N;
                float* pI = (float*) &I;

          /*      BYTE    c     = (BYTE) pI[i];
                RGBQUAD color = (pn[i] < MAX_ITERATIONS)? RGBQUAD { (BYTE) (255-c), (BYTE) (c%2 * 64), c } : RGBQUAD {};

                glColor3ub(color.rgbRed, color.rgbGreen, color.rgbBlue);
*/
                BYTE c = (BYTE) pI[i];
                RGBQUAD color = (pN[i] < MAX_ITERATIONS)? RGBQUAD { (BYTE) (255-c), (BYTE) (c%2 * 64), c } : RGBQUAD {};
                //blue = (float) step / MAX_ITERATIONS;

                if(in_set) {
                    //green = (float) r2[0] / 4;
                    glColor3f(color.rgbRed, color.rgbGreen, color.rgbBlue);
                }
                else {
                    glColor3f(color.rgbRed, color.rgbGreen, color.rgbBlue);
                }
                glVertex2i(j + k, i);
            }
        }
    }
    glEnd();
}

#endif //MANDELBROT_MANDELBROTSSE_H
