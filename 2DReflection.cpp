#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

#define GRID_SIZE 10

void swapFloat(GLfloat *a, GLfloat *b) {
    GLfloat temp = *a;
    *a = *b;
    *b = temp;
}

void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    GLfloat dx, dy, p, x, y;
    bool steep = false;

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
    glColor3f(1.0f, 1.0f, 1.0f); // White color

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

void drawCoordinateGrid() {
    glColor3f(0.5f, 0.5f, 0.5f); // Gray color
    glBegin(GL_LINES);

    // Draw horizontal lines
    for (int i = 0; i <= 500; i += GRID_SIZE) {
        glVertex2f(0, i);
        glVertex2f(500, i);
    }

    // Draw vertical lines
    for (int i = 0; i <= 500; i += GRID_SIZE) {
        glVertex2f(i, 0);
        glVertex2f(i, 500);
    }

    glEnd();
    glFlush();
}

void drawAxes() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_LINES);
    glVertex2f(0, 250);
    glVertex2f(500, 250);
    glEnd();
    glFlush();

    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    glBegin(GL_LINES);
    glVertex2f(250, 0);
    glVertex2f(250, 500);
    glEnd();
    glFlush();
}

void drawTriangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat r, GLfloat g, GLfloat b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
    glFlush();
}

void Draw() {
    GLfloat x1, y1, x2, y2, x3, y3;

    printf("Enter the coordinates of the triangle (x1 y1 x2 y2 x3 y3): ");
    scanf("%f %f %f %f %f %f", &x1, &y1, &x2, &y2, &x3, &y3);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glClear(GL_COLOR_BUFFER_BIT);

    drawCoordinateGrid();
    drawAxes();

    // Draw the original triangle
    drawTriangle(x1, y1, x2, y2, x3, y3, 1.0f, 1.0f, 0.0f); // Yellow color

    // Draw the triangle reflected about y = x
    drawTriangle(y1, x1, y2, x2, y3, x3, 0.0f, 1.0f, 1.0f); // Cyan color

    // Draw the triangle reflected about y = -x
    //drawTriangle(-y1, x1, -y2, x2, -y3, x3, 1.0f, 0.0f, 1.0f); // Magenta color

    // Draw the triangle reflected about the X-axis
    //drawTriangle(x1, -y1, x2, -y2, x3, -y3, 1.0f, 0.5f, 0.0f); // Orange color
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
    glutCreateWindow("Triangle Reflection");
    MyInit();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}