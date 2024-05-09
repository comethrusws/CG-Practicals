#include <GL/glut.h>
#include <iostream>
#include <cmath>

GLfloat win_left = 100, win_right = 300, win_bottom = 100, win_top = 300;

struct Point {
    GLfloat x, y;
};

// Function to clip the line segment against a single edge of the window
Point clip(Point P1, Point P2, GLfloat edge[4]) {
    Point result;
    GLfloat m = (P2.y - P1.y) / (P2.x - P1.x);

    if (edge == win_left) {
        result.x = win_left;
        result.y = P1.y + m * (win_left - P1.x);
    } else if (edge == win_right) {
        result.x = win_right;
        result.y = P1.y + m * (win_right - P1.x);
    } else if (edge == win_bottom) {
        result.y = win_bottom;
        result.x = P1.x + (win_bottom - P1.y) / m;
    } else if (edge == win_top) {
        result.y = win_top;
        result.x = P1.x + (win_top - P1.y) / m;
    }

    return result;
}

// Function to clip the line segment against all edges of the window
void sutherland_hodgman(Point P1, Point P2) {
    Point new_P1 = P1, new_P2 = P2;

    GLfloat edge_left[4] = { win_left, win_bottom, win_left, win_top };
    GLfloat edge_right[4] = { win_right, win_top, win_right, win_bottom };
    GLfloat edge_bottom[4] = { win_left, win_bottom, win_right, win_bottom };
    GLfloat edge_top[4] = { win_right, win_top, win_left, win_top };

    // Clip against left edge
    new_P1 = clip(new_P1, new_P2, edge_left);
    new_P2 = clip(new_P2, new_P1, edge_left);

    // Clip against right edge
    new_P1 = clip(new_P1, new_P2, edge_right);
    new_P2 = clip(new_P2, new_P1, edge_right);

    // Clip against bottom edge
    new_P1 = clip(new_P1, new_P2, edge_bottom);
    new_P2 = clip(new_P2, new_P1, edge_bottom);

    // Clip against top edge
    new_P1 = clip(new_P1, new_P2, edge_top);
    new_P2 = clip(new_P2, new_P1, edge_top);

    // Draw the clipped line segment
    glBegin(GL_LINES);
    glVertex2f(new_P1.x, new_P1.y);
    glVertex2f(new_P2.x, new_P2.y);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping window
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(win_left, win_bottom);
    glVertex2f(win_right, win_bottom);
    glVertex2f(win_right, win_top);
    glVertex2f(win_left, win_top);
    glEnd();

    // Define the line segment to be clipped
    Point P1 = {50, 150};
    Point P2 = {250, 350};

    // Draw the original line segment
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(P1.x, P1.y);
    glVertex2f(P2.x, P2.y);
    glEnd();

    // Clip and draw the line segment
    glColor3f(0.0, 1.0, 0.0);
    sutherland_hodgman(P1, P2);

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Sutherland-Hodgman Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
