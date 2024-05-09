#include<GL/glut.h>
#include<cmath>
// Defining different color 
GLfloat C1[3] = { 1.0f,0.0f,0.0f }; //red 
GLfloat C2[3] = { 0.0f,0.0f,1.0f }; //Blue 
GLfloat C3[3] = { 0.0f,1.0f,0.0f }; //Green 
GLfloat C4[3] = { 1.0f,1.0f,1.0f }; //White
GLfloat C5[3] = { 0.2f,0.75f,0.75f }; // light blue for BG 

// Defining the Createpolygun function 
void CreatePolygun(GLfloat V[3][2], GLfloat Pic_color[3]) {
    glBegin(GL_LINE_LOOP);
    glColor3fv(Pic_color);
    for (int i = 0; i < 3; i++) {
        glVertex2fv(V[i]);
    }
    glEnd();
}

// Defining a Scalling Function 
void Scale2D(GLfloat V[3][2]) {
    // variables for scaling Factors 
    GLfloat Sx = 1.5;
    GLfloat Sy = 1.75;

    for (int i = 0;i < 3;i++) {
        V[i][0] *= Sx;
        V[i][1] *= Sy;
    }
    //CreatePolygun(V, C3);
}

// defining Rotate2D function for 2d rotation 
void Rotate2D(GLfloat V[3][2], GLfloat angle) {
    GLfloat R_Vertex[3][2];
    angle = angle * 3.14 / 180; // converting angle to radian
    for (int i = 0;i < 3;i++) {
        R_Vertex[i][0] = floor(V[i][0] * cos(angle) - V[i][1] * sin(angle));
        R_Vertex[i][1] = floor(V[i][0] * sin(angle) + V[i][1] * cos(angle));
    }
    // gl library function for rotation 
    //glRotatef(angle, 1.0f, 0.0f, 0.0f);
    //CreatePolygun(V, C3);
    CreatePolygun(R_Vertex, C3);
}
// Defining Draw Function 
void Draw() {
    glClearColor(0.2f, 0.75f, 0.75f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT);


    // Defining the Vertex matrix for co-ordinate
    GLfloat vertex[3][2] = {
                                {100, 200},
                                {-20,50},
                                {200,80}
    };

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3fv(C2);
    glVertex2f(-350, 0);
    glVertex2f(350, 0);
    glVertex2f(0, 350);
    glVertex2f(0, -350);
    glEnd();


    // calling a polygun Create Function 
    CreatePolygun(vertex, C1);
    // calling Scale function for scalling 
   // Scale2D(vertex);
    Rotate2D(vertex, -90.0f);

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
    glutCreateWindow("2D Rotation in Opengl");
    MyInit();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}