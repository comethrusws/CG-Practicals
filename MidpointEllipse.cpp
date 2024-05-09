#include <GL/glut.h>
#include <cmath>

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawEllipseMidpoint(int xc, int yc, int rx, int ry) {
    float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;

    // Initial decision parameter of region 1
    d1 = (ry * ry) - (rx * rx * ry) + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    // For region 1
    while (dx < dy) {
        // Print points based on 4-way symmetry
        drawPixel(x + xc, y + yc);
        drawPixel(-x + xc, y + yc);
        drawPixel(x + xc, -y + yc);
        drawPixel(-x + xc, -y + yc);

        // Checking and updating value of decision parameter
        if (d1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        } else {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }

    // Decision parameter of region 2
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5))) + ((rx * rx) * ((y - 1) * (y - 1))) - (rx * rx * ry * ry);

    // For region 2
    while (y >= 0) {
        // Print points based on 4-way symmetry
        drawPixel(x + xc, y + yc);
        drawPixel(-x + xc, y + yc);
        drawPixel(x + xc, -y + yc);
        drawPixel(-x + xc, -y + yc);

        // Checking and updating parameter value of decision parameter
        if (d2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        } else {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw an ellipse using Midpoint Ellipse Drawing Algorithm
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    drawEllipseMidpoint(250, 250, 150, 100); // Center at (250, 250) with semi-major axis 150 and semi-minor axis 100

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
    glutCreateWindow("Midpoint Ellipse Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
