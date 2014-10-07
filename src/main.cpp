#define GLEW_STATIC // Easier debugging
#include <GL/glut.g>
#include <GL/glew.h>
#include <GL/gl.h>
#include "stdafx.h"
#include <SDL2/SDL.h>
#include <unistd.h>
#include <iostream>

void display(void)
{
// clear all pixels
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);  //Defining a colour (1,1,1 = white)
    glBegin(GL_LINE_LOOP);
    glVertex3f(5.0f, 5.0f, 0.0f);
    glVertex3f(25.0f, 5.0f, 0.0f);
    glVertex3f(25.0f, 25.0f, 0.0f);
    glEnd();

    glFlush(); 
}

void init (void)
{
    glClearColor(0.5, 0.5, 0.5, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 30.0, 0.0, 35.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (600, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("TRIANGLE");
    init ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
