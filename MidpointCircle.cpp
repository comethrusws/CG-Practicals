#include <GL/glut.h>
#include <cmath>

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawCircleMidpoint(int xc, int yc, int radius) {
    int x = radius;
    int y = 0;
    int p = 1 - radius;

    // Plot the initial point in each octant
    drawPixel(x + xc, y + yc);
    drawPixel(-x + xc, y + yc);
    drawPixel(x + xc, -y + yc);
    drawPixel(-x + xc, -y + yc);
    drawPixel(y + xc, x + yc);
    drawPixel(-y + xc, x + yc);
    drawPixel(y + xc, -x + yc);
    drawPixel(-y + xc, -x + yc);

    while (x > y) {
        y++;

        if (p <= 0)
            p = p + 2 * y + 1;
        else {
            x--;
            p = p + 2 * y - 2 * x + 1;
        }

        if (x < y)
            break;

        // All the perimeter points have already been plotted
        drawPixel(x + xc, y + yc);
        drawPixel(-x + xc, y + yc);
        drawPixel(x + xc, -y + yc);
        drawPixel(-x + xc, -y + yc);
        drawPixel(y + xc, x + yc);
        drawPixel(-y + xc, x + yc);
        drawPixel(y + xc, -x + yc);
        drawPixel(-y + xc, -x + yc);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a circle using Midpoint Circle Drawing Algorithm
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    drawCircleMidpoint(250, 250, 100); // Center at (250, 250) with radius 100

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Midpoint Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
