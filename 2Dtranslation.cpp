#include<GL/glut.h>
#include<cmath>

// Defining different color 
GLfloat C1[3] = { 1.0f,0.0f,0.0f }; //red 
GLfloat C2[3] = { 0.0f,0.0f,1.0f }; //Blue 
GLfloat C3[3] = { 0.0f,1.0f,0.0f }; //Green 
GLfloat C4[3] = { 1.0f,1.0f,1.0f }; //White
GLfloat C5[3] = { 0.2f,0.75f,0.75f }; // light blue for BG 

// Defining the Createpolygon function 
void CreatePolygon(GLfloat V[3][2], GLfloat Pic_color[3]) {
    glBegin(GL_LINE_LOOP);
    glColor3fv(Pic_color);
    for (int i = 0; i < 3; i++) {
        glVertex2fv(V[i]);
    }
    glEnd();
}

// Defining a Translation Function 
void Translate2D(GLfloat V[3][2], GLfloat Tx, GLfloat Ty) {
    for (int i = 0; i < 3; i++) {
        V[i][0] += Tx;
        V[i][1] += Ty;
    }
}

// Defining Draw Function 
void Draw() {
    glClearColor(0.2f, 0.75f, 0.75f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Defining the Vertex matrix for coordinate
    GLfloat vertex[3][2] = {
        {100, 200},
        {-20, 50},
        {200, 80}
    };

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3fv(C2);
    glVertex2f(-350, 0);
    glVertex2f(350, 0);
    glVertex2f(0, 350);
    glVertex2f(0, -350);
    glEnd();

    // calling a polygon Create Function 
    CreatePolygon(vertex, C1);

    // calling Translation function for translation 
    Translate2D(vertex, 50.0f, 100.0f);

    // Drawing the translated polygon
    CreatePolygon(vertex, C3);

    glFlush();
}

// Defining the MyInit function 
void MyInit() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-350, 350, -350, 350);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(50, 50);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(720, 720);
    glutCreateWindow("2D Translation in OpenGL");
    MyInit();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}
