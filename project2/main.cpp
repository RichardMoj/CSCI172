
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>

#include <math.h>
using namespace std;



bool WireFrame= false;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };



/** All variables initialized during init() function **/

//Flag vars for deciding whether one of the glut solid objects is selected
bool c_flag, t_flag, s_flag;

//vars for the rotation and position of the GLUT objects
int deg;
float pos;

//vars for the initial pos of the objects
float sphereX, sphereY, sphereZ, cubeX, cubeY, cubeZ, tpotX, tpotY, tpotZ;

//vars for the input sizes of glut solid objects
float sphere_radius;
float teapot_size;
float cube_size;



/* GLUT callback Handlers */

static void resize(int width, int height)
{
     double Ratio;

   if(width<=height)
            glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
          glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective (50.0f,1,0.1f, 100.0f);
 }

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,5,10,0.0,0.0,0.0,0.0,1.0,0.0);

    if(WireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		//Draw Our Mesh In Wireframe Mesh
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		//Toggle WIRE FRAME

    // your code here

    //Push sphere onto the window, blue color
    glPushMatrix();
    glColor3f(0, 0, 1);
    glTranslatef(sphereX, sphereY, sphereZ);
    glutSolidSphere(sphere_radius, 100, 100);
    glPopMatrix();

    //Push cube onto the window, green color
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslatef(cubeX, cubeY, cubeZ);
    glutSolidCube(cube_size);
    glPopMatrix();

    //Push teapot onto the window, red color
    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(tpotX, tpotY, tpotZ);
    glutSolidTeapot(teapot_size);
    glPopMatrix();

    //Modify glut solid objects when callback() is initiated
    //And if flags are switched on
    if (c_flag)
    {
    glPushMatrix();
    //do stuff?
    glPopMatrix();
    }

    if (s_flag)
    {
    glPushMatrix();
    //do stuff?
    glPopMatrix();
    }

    if (t_flag)
    {
    glPushMatrix();
    //do stuff?
    glPopMatrix();
    }


    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        // If a user presses a key once, turn the flag on
        // If they press it a second time, turn the flag off, repeat
        case 'c':
            //If c_flag is true, then turn off selection on circle
            if (c_flag) c_flag = false;

            //If c_flag is false, then turn on selection on circle
            if (!c_flag) c_flag = true;
            break;
        case 't':
            if (t_flag) t_flag = false;
            if (!t_flag) t_flag = true;
            break;
        case 's':
            if (s_flag) s_flag = false;
            if (!s_flag) s_flag = true;
            break;
    }

}

void Specialkeys(int key, int x, int y)
{
    switch(key)
    {
    //KEY_UP & KEY_DOWN controls position
        case GLUT_KEY_UP:
            pos += 0.5;
            break;
        case GLUT_KEY_DOWN:
            pos -= 0.5;
            break;
    //KEY LEFT & RIGHT controls rotation around y-axis
        case GLUT_KEY_LEFT:
            deg += 5;
            break;
        case GLUT_KEY_RIGHT:
            deg -= 5;
            break;

   }
  glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

static void init(void)
{
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    //Initialize all vars declared at the top
    sphereX = -3.5;
    sphereZ = -1.0;
    cubeX = 4.0;
    cubeZ = -2.0;
    tpotZ = -3.0;
    sphereY, cubeY, tpotX, tpotY = 0.0;
    c_flag, t_flag, s_flag = false;

    deg = 0 % 360;
    pos = 0;

    sphere_radius = 1.3;
    teapot_size = 1.5;
    cube_size = 2;
}


/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(800,600);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(Specialkeys);

    glutIdleFunc(idle);
    glutMainLoop();

    return EXIT_SUCCESS;
}
