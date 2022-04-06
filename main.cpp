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

#include "mandelbrotSSE.h"


const int       WIDTH     = 800;
const int       HEIGHT    = 600;

float   xC = 0,
        yC = 0,
        dx = 1/200.f,
        dy = 1/200.f,
        scx = 1,
        scy = 1,
        sc = 1;

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    const size_t width  = glutGet(GLUT_WINDOW_WIDTH);
    const size_t height = glutGet(GLUT_WINDOW_HEIGHT);
    glOrtho(0, width, 0, height, -1, 1);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    if (GetAsyncKeyState (VK_ESCAPE)) glutLeaveMainLoop();

    if (GetAsyncKeyState (VK_RIGHT)) xC    += dx * (GetAsyncKeyState (VK_SHIFT)? 100.f * sc: 10.f * sc);
    if (GetAsyncKeyState (VK_LEFT))  xC    -= dx * (GetAsyncKeyState (VK_SHIFT)? 100.f * sc: 10.f * sc);
    if (GetAsyncKeyState (VK_DOWN))  yC    -= dy * (GetAsyncKeyState (VK_SHIFT)? 100.f * sc: 10.f * sc);
    if (GetAsyncKeyState (VK_UP))    yC    += dy * (GetAsyncKeyState (VK_SHIFT)? 100.f * sc: 10.f * sc);
    if (GetAsyncKeyState ('A'))      sc    += dx * (GetAsyncKeyState (VK_SHIFT)? 100.f * sc : 10.f * sc);
    if (GetAsyncKeyState ('Z'))      sc    -= dx * (GetAsyncKeyState (VK_SHIFT)? 100.f * sc : 10.f * sc);

    if (GetAsyncKeyState ('K'))      scx    += dx * (GetAsyncKeyState (VK_SHIFT)? 100.f * scx : 10.f * scx);
    if (GetAsyncKeyState ('M'))      scx    -= dx * (GetAsyncKeyState (VK_SHIFT)? 100.f * scx : 10.f * scx);

    if (GetAsyncKeyState ('I'))      scy    += dy * (GetAsyncKeyState (VK_SHIFT)? 100.f * scy : 10.f * scy);
    if (GetAsyncKeyState ('O'))      scy    -= dy * (GetAsyncKeyState (VK_SHIFT)? 100.f * scy : 10.f * scy);

    if (GetAsyncKeyState('F')) glutFullScreen();
    if (GetAsyncKeyState('C')) glutLeaveFullScreen();

    Create_Mandelbrot(xC, yC, dx * sc * scx, dy * sc * scy);
    CalculateFrameRate();

    glutSwapBuffers();
    //glFlush();
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Mandelbrot set");


    //glOrtho (0, WIDTH, HEIGHT, 0, -1, 1);
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutMainLoop();

    return 0;
}
