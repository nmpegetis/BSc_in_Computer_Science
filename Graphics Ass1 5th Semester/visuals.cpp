#include <stdio.h>     // - Just for some ASCII messages
#include "gl/glut.h"   // - An interface and windows 
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions


void Render()
{    
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
  glMatrixMode(GL_MODELVIEW); //fortwnoume to monadiaio pinaka GL_MODELVIEW opws kaname kai pio katw me to resize
  glLoadIdentity();

  //oi parametroi gia to parakatw einai apo 0.0 - 1.0 kai prokeitai gia ta RGB(Red-Green-Blue)
  glColor3f(1.0, 0.0, 0.0);							   // Set drawing colour = orange
  //glutSolidTeapot( 20.0 );							   // Draw a built-in primitive
  //i parapanw sunartisi anikei stin bibliothiki glut
  
  //glutWireTeapot(20.0);		
  glutSolidSphere(150.0,30,30);	//to 2o orisma einai ta slices kai to 3o orisma ta stacks...kati dld san mesimbrinous kai parallilous

  //i parakatw einai i entoli pou allazei tous 2 buffers metaksu tous
  glutSwapBuffers();             // All drawing commands applied to the 
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one
}

//-----------------------------------------------------------

void Resize(int w, int h)
{ // w and h are window sizes returned by glut
  // define the visible area of the window ( in pixels )
  
  if (h==0) h=1;
  glViewport(w/2,0,w/2,h/2);//edw kaname kapoies allages kai tropopoiiseis sto ergastirio
  //glViewport(100,100,400,400);//auti i morfi dinei static diastaseis

  // Setup viewing volume
  glMatrixMode(GL_PROJECTION); //san orisma bazoume ton ena apo tous 3 pinakes opou tha ginoun oi metasximatismoi pou tha akolouthisoun..
  //ta pithana orismata gia parapanw einai:GL_PROJECTION, GL_MODELVIEW, GL_TEXTURE
  glLoadIdentity();//fortwsi kai arxikopoiisi tou parapanw pinaka
 
 
  //         L,      R,      B,     T,     N,      F
  glOrtho (-300.0f, 300.0f, -300.0f, 300.0f, 300.0f, -300.0f);
  //		Left,	Right,	Bottom,	top,	Near,	Far
  //to parapanw prokeitai gia orthografiki proboli
}


void Setup()  // DON'T TOUCH IT 
{ 
	//Parameter handling
	glShadeModel (GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { 0.0, 30.0,-50.0,0.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

