#include <GL/glut.h>
#include <cmath>

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLineDDA(int x1, int y1, int x2, int y2) {
    // Calculate dx and dy
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Calculate steps needed for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // Calculate increment in x and y for each step
    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;

    // Put pixel for each step
    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++) {
        drawPixel(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a line using DDA algorithm
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    drawLineDDA(100, 100, 300, 300);

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
    glutCreateWindow("DDA Line Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
