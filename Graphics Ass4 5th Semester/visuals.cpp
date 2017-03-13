#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include "gl/glut.h"   // - An interface and windows 
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions


float sign=1.0;
float sign2=1.0;
float poslx=0.0;
float posly=0.0;
float poslz=0.0;
	
void Render()
{    
  //CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
	
 

  glTranslatef(0,0,-50);
  glTranslatef(0,0,-50);

	glColor4f(0.0, 1.0, 0.0, 1.0);	//the teapot is of color green
	glutSolidTeapot( 8.0 );

  //(02)             //when enabling depth test this is rendered first
//  glColor3f(0.3, 0.2, 0.9);                            // Set drawing colour
//  glColor4f(0.3, 0.2, 0.9, 0.5);					   // Set drawing colour and transparency
//  glutSolidTeapot( 20.0 );							   // Draw a built-in primitive
  
  //(02)             //when disabling depth test this is rendered first
  //glPushMatrix();
//  glTranslatef(15,0,-35);//metakinei tin 2 kanata gia na fainetai 
//  glColor3f(1.0, 0.5, 0.2);							   // Set drawing colour
//  glutSolidTeapot( 20.0 );							   // Draw a built-in primitive

	glColor4f(1.0, 0.0, 0.0, 0.6);	//the cude is of color red
	glutSolidCube(30.0);
  
	//glPopMatrix();

  //glPushMatrix();
  //glTranslatef(15,0,-35);
//  glColor3f(1.0, 0.5, 0.2);							   // Set drawing colour
//  glutSolidTeapot( 20.0 );							   // Draw a built-in primitive

	glColor4f(0.0, 0.0, 1.0, 0.3);	//the sphere is of color blue
	glutSolidSphere(30.0,30,30);
  
	//glPopMatrix();
 
  glutSwapBuffers();             // All drawing commands applied to the 
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one
}

//-----------------------------------------------------------

void Resize(int w, int h)
{ 
  // define the visible area of the window ( in pixels )
  if (h==0) h=1;
  glViewport(0,0,w,h); 

  // Setup viewing volume

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
 
  gluPerspective(60.0, (float)w/(float)h, 1.0, 500.0);
}

void Idle()
{
	// Light source movement
	if (posly>-500.0 && posly<500.00){ 
		if(poslx>-100.0 && poslx<100.00){ 
			poslx+=0.1*sign2; 
			posly+=0.1*sign; 
			poslz+=0.1*sign; 
		}
		else{
			(sign2==1)?sign2=-1:sign2=1;
			poslx+=0.1*sign2; 
		}
	}
	else{
		(sign==1)?sign=-1:sign =1;
		poslx+=0.1*sign2; 
		posly+=0.1*sign; 
		poslz+=0.1*sign; 
	}
	GLfloat light_position[] = { poslx, posly, poslz, 1.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);
 printf("\t||%lf - %lf||",poslx, posly);
	glutPostRedisplay();	
}

void Setup()  // TOUCH IT !! 
{ 
	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	//(02)
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	//glClearDepth(1);
    
	// (06) // polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	//GLfloat light_position[] = { 0.0, 30.0, 50.0, 0.0 };
	//glLightfv( GL_LIGHT0, GL_POSITION, light_position);
	
	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	//GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	
	//(05)
	/*
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat specref[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,64);
	*/

	//(06) Material Parameters
	//(06a) for Gold
	/*
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat specref[4];
	specref[0] = 0.247; specref[1] = 0.225; specref[2] = 0.065; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_AMBIENT,specref);
	specref[0] = 0.346; specref[1] = 0.314; specref[2] = 0.090; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_DIFFUSE,specref);
	specref[0] = 0.797; specref[1] = 0.724; specref[2] = 0.208; specref[3] = 1.0;
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMaterialf(GL_FRONT,GL_SHININESS,83.2);
	*/

	//(06b) for Ruby
	/*
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularLight);
	GLfloat specref[4];
	specref[0] = 0.175; specref[1] = 0.012; specref[2] = 0.012; specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_AMBIENT,specref);
	specref[0] = 0.614; specref[1] = 0.041; specref[2] = 0.041; specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_DIFFUSE,specref);
	specref[0] = 0.728; specref[1] = 0.308; specref[2] = 0.308; specref[3] = 0.55;
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMaterialf(GL_FRONT,GL_SHININESS,76.8);
	*/

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// (04)
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	
	//(03)
	glEnable(GL_CULL_FACE);	//gia na sxediazetai mono to mprostino kommati kai na kerdizetai xrono
	glFrontFace(GL_CW);
	//glFrontFace(GL_CCW);



	//(01) BLENDING
   glEnable(GL_BLEND);
                 // incoming //  // stored //
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

