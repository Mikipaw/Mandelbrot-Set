//
// Created by mikipaw on 02.04.2022.
// Copyright (c) 2022 MIPT. All rights reserved.
//

#ifndef MANDELBROT_MANDELBROT_H
#define MANDELBROT_MANDELBROT_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <complex>

using std::complex;

void Create_Mandelbrot(double x, double dx, double y, double dy);


void Create_Mandelbrot(double x, double dx, double y, double dy) {
    const int MAX_ITERATIONS = 250;

    const int width = glutGet( GLUT_WINDOW_WIDTH );
    const int height = glutGet( GLUT_WINDOW_HEIGHT );

    glBegin( GL_POINTS );

    for( int i = 0; i < height; ++i )
    {
        for( int j = 0; j < width; ++j )
        {
            complex<double> c( x + ( j * dx / width ),
                               y + ( i * dy / height ) );

            complex<double> z( 0.0, 0.0 );

            bool in_set = false;

            for (int step = 0; abs(z) < 2; ++step) {
                z = (z * z) + c;
                if (step == MAX_ITERATIONS) {
                    in_set = true;
                    break;
                }
            }

            if(in_set) {
                glColor3f( 0.0, 1.0, 0.0 );
                glVertex2i( j, i );
            }
            else {
                glColor3f( 0.0, 0.0, 0.0 );
                glVertex2i( j, i );
            }
        }
    }

    glEnd();
}

#endif //MANDELBROT_MANDELBROT_H
