//Richard Mojarro
//CSCI 172
//Barnsleys Fern
//2019FA


#include <string.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
/* GLUT callback Handlers */

float a,b,c,d,e,f;
float x,y,Xold,Yold;

int n;



void resize(int width, int height)
{
    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);

    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}

void init()
{
 glColor3f(0,1,0);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-2.5,2.75,10.5,0, -1.0, 1.0); // adjusted for suitable viewport
 x=y=Xold=Yold=0.5;
 n = 200000;

}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);        // clear display screen
  // your code here
  int number = 0;

  for(int i = 0; i < n; i++){
    number = rand()%100;

    if(number < 85){
        //f2
        a = 0.85;
        b = -0.04;
        c = 0.04;
        d = 0.85;
        e = 0;
        f = 1.6;

    }
    else if(number < 92){
        //f3
        a = 0.2;
        b = 0.23;
        c = -0.26;
        d = 0.22;
        e = 0;
        f = 1.6;
    }
    else if(number < 99){
        //f4
        a = -0.15;
        b = 0.26;
        c = 0.28;
        d = 0.24;
        e = 0;
        f = 0.44;
    }
    else {
        //f1
        a = 0;
        b = 0;
        c = 0;
        d = 0.16;
        e = 0;
        f = 0;
    }

    x = a*Xold + c*Yold + e;
    y = b*Xold + d*Yold + f;


    glBegin(GL_POINTS);
    glVertex3f(x,y,0);
    glEnd();
    Xold = x;
    Yold = y;

  }// End of For Loop
  glFlush ();                           // clear buffer
}


void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (600, 800);                //window screen
   glutInitWindowPosition (100,100);            //window position
   glutCreateWindow ("Program1");                //program title
   init();
   glutDisplayFunc(display);                     //callback function for display
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   glutMainLoop();                               //loop

    return EXIT_SUCCESS;
}
