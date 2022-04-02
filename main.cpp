/*!
 * @mainpage
 *  \brief     MandelbrotSet
 *  \author    Michael Pavlov
 *  \author    Mikhail Pavlov
 *  \version   C++20
 *  \date      04.2022
 *  \pre       First initialize the system.
 *  \bug       No
 *  \warning
 *  \copyright GNU Public License.
 */

#include "mandelbrot.h"


const int       WIDTH     = 800;
const int       HEIGHT    = 600;
const int       ROWS      = 30;
const int       COLUMNS   = 40;


void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    const size_t width  = glutGet( GLUT_WINDOW_WIDTH );
    const size_t height = glutGet( GLUT_WINDOW_HEIGHT );
    glOrtho( 0, width, 0, height, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    Create_Mandelbrot(-2, 3, 1.125, -2.25);

    glutSwapBuffers();
    glFlush();
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Mandelbrot set");

    //glOrtho (0, WIDTH, HEIGHT, 0, -1, 1);
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}
