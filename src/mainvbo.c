/*
*   spinnydonut
*
*   fun lil excercise in opengl stuff.
*
*   basically spin a donut around and change its colours
*   
*/

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//scale of the donut in createvertices()
#define SCALE 0.7
//rotation speed
#define SPEED 0.9

// Global variables for VBO
GLuint vbo;
GLfloat *vertices;
int numVertices = 0;
double angleX = 0.0;
double angleY = 0.0;
double angleZ = 0.0;

// Function to convert HSV to RGB for interpolations, kinda soy implementation, but it werks
void hsvToRgb(float h, float s, float v, float* r, float* g, float* b) {
    int i;
    float f, p, q, t;
    if (s == 0) {
        // achromatic (grey)
        *r = *g = *b = v;
        return;
    }
    h /= 60;            // sector 0 to 5
    i = floor(h);
    f = h - i;          // factorial part of h
    p = v * (1 - s);
    q = v * (1 - s * f);
    t = v * (1 - s * (1 - f));
    switch (i) {
        case 0:
            *r = v;
            *g = t;
            *b = p;
            break;
        case 1:
            *r = q;
            *g = v;
            *b = p;
            break;
        case 2:
            *r = p;
            *g = v;
            *b = t;
            break;
        case 3:
            *r = p;
            *g = q;
            *b = v;
            break;
        case 4:
            *r = t;
            *g = p;
            *b = v;
            break;
        default:        // case 5:
            *r = v;
            *g = p;
            *b = q;
            break;
    }
}

//initialize VBO with vertex data
void initVBO() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, numVertices * 3 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    free(vertices);
}

//Generates vertex data for the donut
void createVertices() {
    int count = 0;
    for (double t = 0; t < 2 * M_PI; t += 0.01) {
        for (double phi = 0; phi < 2 * M_PI; phi += 0.05) {
            count++;
        }
    }
    numVertices = count;
    vertices = (GLfloat*)malloc(numVertices * 3 * sizeof(GLfloat));
    
    int idx = 0;
    for (double t = 0; t < 2 * M_PI; t += 0.01) {
        for (double phi = 0; phi < 2 * M_PI; phi += 0.05) {
            double x = SCALE * cos(t) * (2.5 + cos(phi));
            double y = SCALE * sin(t) * (2.5 + cos(phi));
            double z = SCALE * sin(phi);
            vertices[idx++] = x;
            vertices[idx++] = y;
            vertices[idx++] = z;
        }
    }
}

//show the donut lol
//Now uses VBO to draw the vertices
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double cycleTime = 6.0;
    double t = fmod(time, cycleTime) / cycleTime;
    float hue = t * 360.0f;
    float r, g, b;
    hsvToRgb(hue, 1.0f, 1.0f, &r, &g, &b);
    glColor3f(r, g, b);

    glPushMatrix();
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_POINTS, 0, numVertices);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();

    glutSwapBuffers();
}

//forget what this does lol
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

//important function, deals with the rotation and the colour change
void idle() {
    // Calculate interpolation factor (e.g., based on elapsed time)
    double time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double cycleTime = 15; // Cycle through colors every 15 seconds
    double t = fmod(time, cycleTime) / cycleTime; // Normalize time to a [0, 1] range

    // Calculate the hue value
    float hue = t * 360.0f; // Hue varies from 0 to 360 degrees
    float r, g, b;
    hsvToRgb(hue, 1.0f, 1.0f, &r, &g, &b);

    // Set the interpolated color
    glColor3f(r, g, b);

    // Update rotation angles and trigger redraw,
    // change these values to control speed
    angleX += SPEED;
    angleY += SPEED;
    angleZ += SPEED;
    glutPostRedisplay();
}




//driver code
int main(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Enable double buffering
    glutInitWindowSize(800, 600);
    glutCreateWindow("SpinnyDonut!");

    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //background colour for the window
    glClearColor(0.18, 0.18, 0.18, 1.0);

    createVertices();
    initVBO();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
