#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

GLvoid drawTriangle( GLfloat red, GLfloat green, GLfloat blue ) {
    glColor3f( red, green, blue );
    glBegin( GL_TRIANGLES );
        glVertex2f( -0.5, -0.5 );
        glVertex2f( 0.5, -0.5 );
        glVertex2f( 0.0, 0.5 );
    glEnd();
}
GLvoid drawScene( GLvoid ) {
    glClearColor(100,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    drawTriangle( 0.0, 0.0, 0.0 );
    glTranslatef( 0.5, 0.0, 0.0 );
    drawTriangle( 0.3, 0.3, 0.3 );
    glTranslatef( 0.5, 0.0, 0.0 );
    glRotatef( -15.0, 0.0, 0.0, 1.0 );
    drawTriangle( 0.7, 0.7, 0.7 );
    glTranslatef( 0.5, 0.0, 0.0 );
    glScalef( -0.5, 0.5, 0.5 );
    drawTriangle( 1.0, 1.0, 1.0 ); 
    glFlush();
}

void redraw() {
    drawScene();
}


int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(500,500);
    int windowId = glutCreateWindow(argv[0]);
    printf("window id %d\n", windowId);
    glutDisplayFunc(redraw);
    glutMainLoop();
    return 0;
}