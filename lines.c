#include <windows.h>  // for MS Windows
#include <GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct
{
    float x;
    float y;
}point;

char title[] = "LINES";

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

   // Render a color-cube consisting of 6 quads with different colors
   glLoadIdentity();                 // Reset the model-view matrix
        glColor3f(1,1,1);

        glBegin(GL_LINE_LOOP);
        glVertex3f(-1,0, 0.0);
        glVertex3f(1,0, 0.0);
        glEnd();

        glBegin(GL_LINE_LOOP);
        glVertex3f(0,-1, 0.0);
        glVertex3f(0,1, 0.0);
        glEnd();


        glColor3f(1, 1, 1);
        //drawing the clipping window
        glBegin(GL_LINE_LOOP);
        glVertex3f(-0.25, 0.25, 0.0);
        glVertex3f(-0.25, -0.25, 0.0);
        glVertex3f(-0.75,-0.25,0.0);
        glVertex3f(-0.75,0.25,0.0);
        glEnd();  // End of drawing color-cube

        glColor3f(1, 0, 0);
        // draw the input lines
        FILE *fp;
        fp = fopen("testcases.txt","r");        //open in read mode

        if(!fp)
            printf("Not able to open input file");
        point p1,p2;
        int i;

        while(!feof(fp))
        {
            fscanf(fp,"%f %f %f %f",&p1.x,&p1.y,&p2.x,&p2.y);
            p1.x = (float)(p1.x-125)/100;
            p1.y = (float)(p1.y-75)/100;
            p2.x = (float)(p2.x-125)/100;
            p2.y = (float)(p2.y-75)/100;
            // might need to process p1 and p2 to scale them down
            glBegin(GL_LINE_LOOP);
            glVertex3f(p1.x, p1.y, 0.0);
            glVertex3f(p2.x, p2.y, 0.0);
            glEnd();
            glFlush();
        }
        glFlush();

        // values are read
        fclose(fp);


        //ouput suare
        glColor3f(1, 1, 1);
        glBegin(GL_LINE_LOOP);
        glVertex3f(0.25, 0.25, 0.0);
        glVertex3f(0.25, -0.25, 0.0);
        glVertex3f(0.75,-0.25,0.0);
        glVertex3f(0.75,0.25,0.0);
        glEnd();  // End of drawing color-cube

        glColor3f(1, 0, 0);
        fp;
        fp = fopen("outputpoints.txt","r");        //open in read mode

        if(!fp)
            printf("Not able to open output file");
        while(!feof(fp))
        {
            fscanf(fp,"%f %f %f %f",&p1.x,&p1.y,&p2.x,&p2.y);
            //printf("%f --%f-- %f-- %f--%d \n",p1.x,p1.y,p2.x,p2.y,i);
            p1.x = (float)(p1.x-25)/100;
            p1.y = (float)(p1.y-75)/100;
            p2.x = (float)(p2.x-25)/100;
            p2.y = (float)(p2.y-75)/100;
            // might need to process p1 and p2 to scale them down
            glBegin(GL_LINE_LOOP);
            glVertex3f(p1.x, p1.y, 0.0);
            glVertex3f(p2.x, p2.y, 0.0);
            glEnd();
            glFlush();
        }
        glFlush();
        fclose(fp);

   glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

}



int main(int argc, char** argv) {
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   initGL();                       // Our own OpenGL initialization
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
