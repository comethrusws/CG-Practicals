#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

void swapFloat(GLfloat *a, GLfloat *b) {
    GLfloat temp = *a;
    *a = *b;
    *b = temp;
}

void Draw() {
    GLfloat x1, y1, x2, y2;
    GLfloat dx, dy, p, x, y;
    bool steep = false;

    printf("Enter the coordinates of the first point (x1 y1): ");
    scanf("%f %f", &x1, &y1);
    printf("Enter the coordinates of the second point (x2 y2): ");
    scanf("%f %f", &x2, &y2);

    glClearColor(0.65f, 0.69f, 0.45f, 0.69f);  // rr, g, b, alpha
    glClear(GL_COLOR_BUFFER_BIT);

    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dy) > abs(dx)) {
        swapFloat(&x1, &y1);
        swapFloat(&x2, &y2);
        swapFloat(&dx, &dy);
        steep = true;
    }

    p = 2 * dy - dx;
    x = x1;
    y = y1;

    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(7.0f, 10.0f, 7.0f);

    while (x <= x2) {
        // Swap back if the line was steep
        if (steep) {
            glVertex2f(y, x);
        } else {
            glVertex2f(x, y);
        }

        if (p < 0) {
            p += 2 * dy;
        } else {
            p += 2 * (dy - dx);
            y++;
        }
        x++;
    }

    glEnd();
    glFlush();
}

void MyInit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(620, 520);
    glutCreateWindow("Bresenham's Line Drawing Algorithm");
    MyInit();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}