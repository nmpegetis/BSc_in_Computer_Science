#include <stdio.h>     // - Just for some ASCII messages
#include <time.h>
#include "gl/glut.h"   // - An interface and windows 
                       //   management library
#include "visuals.h"   // Header file for our OpenGL functions
#include <math.h>


//float TranslateY=0.0f;
//gia tin ergastiriaki askisi sxoliasa tin parapanw grammi kai egprapsa tin parakatw
float TranslateX=0.0f;
float v=70.0;

void axes()
{
  glColor3f(0.6, 0.6, 0.6);
  glPushMatrix();
  glTranslatef(0, 0, -1.0);
  glBegin(GL_LINES);
	glVertex2f(0.0,0.0);
	glVertex2f(100.0,0.0);
	glVertex2f(0.0,0.0);
	glVertex2f(0.0,100.0);
  glEnd();
  glPopMatrix(); 
}


//void karotsi(float Ypos)
//gia tin ergastiriaki askisi sxoliasa tin parapanw grammi kai egprapsa tin parakatw
void karotsi(float Mikos)
{
	
	//glTranslatef(0,Ypos,0);
	glTranslatef(Mikos,0,0);

//Body
	glPushMatrix();
	glColor3f(1.0, 0.5, 0.0);
	glScalef(80,10,40);			//gia na einai strammeno pros ton aksona xx'
	glutSolidCube(1.0);
	glPopMatrix(); 
	
//driving wheel
	glPushMatrix();
	//			35  25  -10 gia na brisketai akribws mprosta apo ti thesi tou odigou tou oximatos, ligo panw apo to kentriko amaksoma
	glTranslatef(35, 25, -8);
	//to prwto orisma einai -90 gia na einai strammeno to timoni pros tin pleura tou odigou
	glRotatef(-90,0,1,0);//gia na einai pros xx'
	glColor3f(0.3, 0.3, 0.3);//grey
	glScalef(0.8,0.8,0.5);	//sto scale to: 1 1 1 einai to fusiologiko megethos pou exoun kai oi rodes
	glutSolidTorus( 3.0, 10.0, 8, 24);	//ligotero paxu ap oti oi rodes
	glPopMatrix();

// driver's seat
	glPushMatrix(); 
	//			14  5  -8 gia na brisketai sto mrostino tou meros ligo panw apo to kentriko amakswma kai ligo aristera 
	glTranslatef(14, 5, -8);
	glColor3f(0.8, 0.8, 0.8);
	glScalef(20,5,14);
	glutSolidCube(1.0);
	glPopMatrix(); 

//co-driver's seat
	glPushMatrix(); 
	//			14  5  -8 gia na brisketai sto mrostino tou meros ligo panw apo to kentriko amakswma kai ligo deksia
	glTranslatef(14, 5, 8);
	glColor3f(0.8, 0.8, 0.8);
	glScalef(20,5,14);
	glutSolidCube(1.0);
	glPopMatrix(); 
	

//Wheels	//tis exw xrwmatisei me diaforetika xrwmata gia na ksexwrizei i kathemia
//1st wheel mprosta deksia
	glPushMatrix();
	glTranslatef(20, -5, 25);
	glRotatef(-3*Mikos,0,0,90);
	glColor3f(1.0, 1.0, 1.0);//white
	glutSolidTorus( 5.0, 10.0, 8, 8);	//to teleutaio orisma to mikrainoume gia na fainetai i kinisi stis rodes
	glPopMatrix();
	     
//2nd wheel pisw deksia
	glPushMatrix();
	glTranslatef(-20, -5, 25);
	glRotatef(-3*Mikos,0,0,90);
	glColor3f(1.0, 0.0, 0.0);//red
	glutSolidTorus( 5.0, 10.0, 8, 8);
	glPopMatrix();

//3rd wheel mprosta aristera
	glPushMatrix();
	glTranslatef(20, -5, -25);
	glRotatef(-3*Mikos,0,0,90);
	glColor3f(0.0, 1.0, 0.0);//green
	glutSolidTorus( 5.0, 10.0, 8, 8);
	glPopMatrix();
	  
//4th wheel pisw aristera
	glPushMatrix();
	glTranslatef(-20, -5, -25);
	glRotatef(-3*Mikos,0,0,90);
	glColor3f(0.0, 0.0, 1.0);//blue
	glutSolidTorus( 5.0, 10.0, 8, 8);
	glPopMatrix();
//epipleon allages pou aforoun tin ergasrtitiako askisi briskontai sto bima 05 kai sti sunartisi Idle
}


void Render()
{    
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	axes();
  
//(02a)
	//aposxoliazoume to parakatw kai i kolokutha metaferetai kata 200 monades makria mas diladi pisw apo tous aksones...
	glTranslatef(0.0, 0.0, -200.0);

////(00)

//sxoliazoume auto to kommati sto prwto bima
//	glColor3f(0.5, 0.5, 0.8);
//	glutSolidTorus( 8.0, 24.0, 12, 24);


////(01)-pumpkin
	//kai aposxoliazoume to parakatw gia na ftiaxtei mia kolokutha
	//sto 4o bima to ksanasxoliazoume to parakatw
/*	glColor3f(1.0, 0.5, 0.2);
	//ftiaxnontai 9 tori, to kathena periestrameno kata 20 moires ston aksona yy' kai sximatizetai mia kolokutha
	for (int i=0;i<9;i++)
	{
		glRotatef(20.0, 0.0, 1.0, 0.0);
		glutSolidTorus(6.0, 24.0, 12, 24);
	}
*/

////(03)
//sto 4o bima asposxoliazoume auto to kommati
/*
//sto telos tou bimatos 4 sxoliazoume ksana auto to kommati
	//metakinei to antikeimeno kata 30 monades deksia
	glTranslatef(30.0, 0.0, 0.0);
	glColor3f(0.5, 0.5, 0.8);
	glutSolidTorus(6.0, 24.0, 12, 24);

	//metakinei to atnikeimeno kata 30 monades aristera...dld 30 monades aristera apo tis 30 monades deksia pou eginan parapanw ara sto kentro
	glTranslatef(-30.0, 0.0, 0.0);
	glColor3f(0.8, 0.1, 0.2);
	glutSolidTorus(6.0, 24.0, 12, 24);

*/
////// Versus


////(04)
	/*
	//edw kathe metafora antikeimenou ginetai me basi to kentro kai oxi tin metafora tou proigoumenou antikeimenou
	glPushMatrix();
	//sinepws to parakatw metakineitai 30 monades deksia apo to kentro 
		glTranslatef(30.0, 0.0, 0.0);
		glColor3f(0.5, 0.5, 0.8);
		glutSolidTorus(6.0, 24.0, 12, 24);
	glPopMatrix();

	glPushMatrix();
	//kai to parakatw metakineitai 30 monades aristera apo to kentro
		glTranslatef(-30.0, 0.0, 0.0);
		glColor3f(0.8, 0.1, 0.2);
		glutSolidTorus(6.0, 24.0, 12, 24);
	glPopMatrix();
	*/

	//(05)
	//(05a)
	//aposxoliazoume to parakatw
	//glRotatef(30, 0, 1, 0);

	//peristrofi ston x y z

	
//auto na to allazw gia na blepw tis allages
	glRotatef(90, 0.1, 1, 0);	//ebala to x=0.1 gia na fainontai kalutera ta kathismata kai oi rodes
	//(05b)

	//	karotsi(TranslateY);
//gia tin ergastiriaki askisi sxoliasa tin parapanw grammi kai egprapsa tin parakatw
	karotsi(TranslateX);
	//(05c)
    //aposxoliazoume kai to parakatw se sinexeia twn parapanw aposxoliasmwn
	//kai otan sxoliazoume to parapanw ksanasxoliazoume kai auto
	//axes();


	glutSwapBuffers();
}

//-----------------------------------------------------------


void Idle()
{

	//(05)
	//aposxoliazoume sto 5o bima
	/*
	float g = 10;
	float dt = 0.01;
	if (TranslateY<0)		v=-v;
				else		v=v-g*dt;
	TranslateY=TranslateY + v*dt;
	

    glutPostRedisplay(); 
	*/
	//gia tin ergastiriaki askisi sxoliasa tin parapanw grammi kai egprapsa tin parakatw

	float g = 10;
	//to epibraduna ligo parapanw gia na fainetai i kinisi
	float dt = 0.001;
	if (TranslateX<0)
		v=-v;
	else
		v=v-g*dt;
	TranslateX=TranslateX + v*dt;
	

    glutPostRedisplay();

	//to angle genika paei aristerostrofa...allaksame to + se - apo katw wste na pigainei aristerostrofa
	//angle-=1.0f;
	//glutPostRedisplay();

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
	 
////(02b)
	          // L     R       B      T      N      F
	//glOrtho (-50.0f, 50.0f, -50.0f, 50.0f,-500.0f,500.0f);
	//sxoliazoume to parapanw kai aposxoliazoume to gluPerspective...

	float aspect = (float)w/(float)h;             /// aspect ratio
	//					è	w/h		near	far
	gluPerspective(60.0, aspect, 1.0, 500.0);
	//to parapanw afora tin prooptiki proboli, dld oso pio makria pigainei kati toso pio mikro fainetai
	//to aspect ratio krataei analoites tis analogies stous aksones x-y
}


//-----------------------------------------------------------

void Setup()  
{ 

   glEnable( GL_CULL_FACE );

   glShadeModel( GL_SMOOTH );

   glEnable(GL_DEPTH_TEST);
   glDepthFunc( GL_LEQUAL );      
   glClearDepth(1.0); 		      


   //Set up light source
   GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
   GLfloat lightPos[] = { -20.0, 20.0, 150.0, 1.0 };

   glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
   glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
   glLightfv( GL_LIGHT0, GL_POSITION,lightPos );

 
	// polygon rendering mode and material properties
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
   
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0);



	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	
	// White background
//	glClearColor(1.0f,1.0f,1.0f,1.0f);
}





