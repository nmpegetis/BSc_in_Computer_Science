#include <stdio.h>     // - Just for some ASCII messages
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>

#include "gl/glut.h"   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions

using namespace std;

static int prev_time = glutGet(GLUT_ELAPSED_TIME);
static int cur_time = glutGet(GLUT_ELAPSED_TIME);
static float dt1;

static float tx = 0.0;
static float ty = 0.0;
static float tz = 0.0;
static float rotx = 0.0;
static float roty = 0.0;
static bool animate = false;
static bool insertflag = true;
static float red = 1.0;
static float green = 0.0;
static float blue = 0.0;

model md;

static bool pc_laps_flag = false;
static int pc_laps = 0;
static float pc_car_x = -60.0;
static float pc_car_z = 18.0;
static float pc_car_rot = 0.0;
static float pc_car_v = 2.0;			//8a pairnei eisodo gia eykolo mesaio kai duskolo. 0.2 sto eykolo 0.4 sto mesaio kai 0.6 sto dyskolo
static int pc_car_pos = 1;
static int difficulty = 2;				//1 easy, 2 average, 3 hard

static float pc_car_R = 20.0;
static float pc_car_w;
static float pc_car_t = 1.0;
static float pc_car_f = 0.0;

static bool user_laps_flag = false;
static int user_laps = 0;
static float user_car_x = -60.0;
static float user_car_z = 42.0;
static float user_car_rot = 0.0;
static float user_car_v = 0.0;			//telikh sto 1.0 gia crash se strofh
static float user_car_a = 1.0;
static int user_car_pos = 1;

static float Vmax = 8.0;
static float Vop = 6.0;
static int lifes = 3;

int trafficlight_color = GREEN;			//can be GREEN,RED,ORANGE
float degrees_of_ramp = 0;				//can be from "0" to "30"
bool crash_flag = false;
bool no_pass_flag = false;

int random = 2;
int fakec = 0;
bool temp = false;
bool temp_in = false;
  

void fanari(GLUquadricObj *pObj, int trafficlight_color)
{
  /////vash fanariou
  glPushMatrix();
  glTranslatef(-5.0, 2.0, -53.0);
  glScalef(5,5,5);
  glColor3f(1.0, 1.0, 1.0);
  glFrontFace(GL_CCW);
  glutSolidCube(0.8);
  glFrontFace(GL_CW);
  glPopMatrix();
  /////stylos fanariou
  glPushMatrix();
  glTranslatef(-5.0, 18.0, -53.0);
  glColor3f(1.0, 1.0, 1.0);
  glRotatef(90,1,0,0);
  glFrontFace(GL_CCW);
  gluCylinder(pObj, 1.0f, 1.0f, 15.0, 180.0f, 180.0f);
  glFrontFace(GL_CW);
  glPopMatrix();
  /////kefali fanariou
  glPushMatrix();
  glTranslatef(-5.0, 22.0, -53.0);
  glScalef(5,10,5);
  glColor3f(1.0, 1.0, 1.0);
  glFrontFace(GL_CCW);
  glutSolidCube(0.8);
  glFrontFace(GL_CW);
  glPopMatrix();
  
  float r,g,o;
  if (trafficlight_color == RED){
	  glPushMatrix();
	  glTranslatef(-5.0, 24.5, -51.0);
	  glColor3f(5.0, 0.0, 0.0);
	  glutSolidSphere(5,50,50);
	  glPopMatrix();
	  r = 10.0; g = 1.0; o = 1.0;
  }
  else if (trafficlight_color == ORANGE){
	  glPushMatrix();
	  glTranslatef(-5.0, 22.0, -51.0);
	  glColor3f(5.0, 1.0, 0.0);
	  glutSolidSphere(5,50,50);
	  glPopMatrix();
	  r = 1.0; g = 1.0; o = 10.0;
  }
  else{
	  glPushMatrix();
	  glTranslatef(-5.0, 19.5, -51.0);
	  glColor3f(0.0, 5.0, 0.0);
	  glutSolidSphere(5,50,50);
	  glPopMatrix();
	  r = 1.0; g = 10.0; o = 1.0;
  }
  /////kokkinh lampa
  glPushMatrix();
  glTranslatef(-5.0, 24.5, -51.0);
  glRotatef(180,0,1,0);
  glColor3f(r, 0.0, 0.0);
  gluPartialDisk(pObj, 0.0f, 1.0f, 500, 13, 0.0f, 360.0f);
  glPopMatrix();
  /////portokalh lampa
  glPushMatrix();
  glTranslatef(-5.0, 22.0, -51.0);
  glRotatef(180,0,1,0);
  glColor3f(o, 1.0, 0.0);
  gluPartialDisk(pObj, 0.0f, 1.0f, 500, 13, 0.0f, 360.0f);
  glPopMatrix();
  /////prasinh lampa
  glPushMatrix();
  glTranslatef(-5.0, 19.5, -51.0);
  glRotatef(180,0,1,0);
  glColor3f(0.0, g, 0.0);
  gluPartialDisk(pObj, 0.0f, 1.0f, 500, 13, 0.0f, 360.0f);
  glPopMatrix();
}

void pista(GLUquadricObj *pObj, int degrees_of_ramp)
{
  if (degrees_of_ramp < 0){degrees_of_ramp = 0;}
  if (degrees_of_ramp > 30){degrees_of_ramp = 30;}
  /////panw aristerh ey8eia/rampa
  glPushMatrix();
  glTranslatef(-30.0, 0.0, 0.0);
  glRotatef(-degrees_of_ramp,0,0,1);						//EDW PERISTREFETAI H RAMPA!!! apo 0 ews -30 ston z aksona
  glTranslatef(+30.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(-45.0, 0.0, -29.0);
  glScalef(30,0.1,42);
  glColor3f(3.5, 0.6, 3.6);
  glutSolidCube(1.0);
  glPopMatrix();
  glPopMatrix();
  /////panw deksia ey8eia
  glPushMatrix();
  glTranslatef(+15.0, 0.0, -29.0);
  glScalef(90,0.1,42);
  glColor3f(0.5, 0.6, 3.6);
  glutSolidCube(1.0);
  glPopMatrix(); 
  /////katw ey8eia
  glPushMatrix();
  glTranslatef(0.0, 0.0, +29.0);
  glScalef(120,0.1,42);
  glColor3f(0.5, 0.6, 3.6);
  glutSolidCube(1.0);
  glPopMatrix();
  /////aristero mprosta hmikyklio pistas
  glPushMatrix();
  glTranslatef(-60.0, 0.0, 0.0);
  glColor3f(0.5, 0.6, 3.6);
  glRotatef(90,1,0,0);
  gluPartialDisk(pObj, 8.0f, 50.0f, 500, 13, 180.0f, 180.0f);
  glPopMatrix();
  /////aristero pisw hmikyklio pistas
  glPushMatrix();
  glTranslatef(-60.0, 0.0, 0.0);
  glColor3f(0.5, 0.6, 3.6);
  glRotatef(-90,1,0,0);
  gluPartialDisk(pObj, 8.0f, 50.0f, 500, 13, 180.0f, 180.0f);
  glPopMatrix();
  /////deksi mprosta hmikuklio pistas
  glPushMatrix();
  glRotatef(-90,1,0,0);
  glRotatef(180,0,1,0);
  glTranslatef(-60.0, 0.0, 0.0);
  glColor3f(0.5, 0.6, 3.6);
  gluPartialDisk(pObj, 8.0f, 50.0f, 500, 13, 180.0f, 180.0f);
  glPopMatrix();
  /////deksi pisw hmikuklio pistas
  glPushMatrix();
  glRotatef(90,1,0,0);
  glRotatef(180,0,1,0);
  glTranslatef(-60.0, 0.0, 0.0);
  glColor3f(0.5, 0.6, 3.6);
  gluPartialDisk(pObj, 8.0f, 50.0f, 500, 13, 180.0f, 180.0f);
  glPopMatrix();

  /////1h grammh ekkinhshs
  glPushMatrix();
  glColor3f(10.0, 10.0, 10.0);
  glTranslatef(-50.0, 0.1, 9.5);
  glScalef(6,0.1,3);
  glutSolidCube(1.0);
  glPopMatrix();
  /////2h grammh ekkinhshs
  glPushMatrix();
  glColor3f(10.0, 10.0, 10.0);
  glTranslatef(-50.0, 0.1, 15.0);
  glScalef(6,0.1,3);
  glutSolidCube(1.0);
  glPopMatrix();
  /////3h grammh ekkinhshs
  glPushMatrix();
  glColor3f(10.0, 10.0, 10.0);
  glTranslatef(-50.0, 0.1, 20.5);
  glScalef(6,0.1,3);
  glutSolidCube(1.0);
  glPopMatrix();
  /////4h grammh ekkinhshs
  glPushMatrix();
  glColor3f(10.0, 10.0, 10.0);
  glTranslatef(-50.0, 0.1, 26.0);
  glScalef(6,0.1,3);
  glutSolidCube(1.0);
  glPopMatrix();
  /////5h grammh ekkinhshs
  glPushMatrix();
  glColor3f(10.0, 10.0, 10.0);
  glTranslatef(-50.0, 0.1, 31.5);
  glScalef(6,0.1,3);
  glutSolidCube(1.0);
  glPopMatrix();
  /////6h grammh ekkinhshs
  glPushMatrix();
  glColor3f(10.0, 10.0, 10.0);
  glTranslatef(-50.0, 0.1, 37.0);
  glScalef(6,0.1,3);
  glutSolidCube(1.0);
  glPopMatrix();
  /////7h grammh ekkinhshs
  glPushMatrix();
  glColor3f(10.0, 10.0, 10.0);
  glTranslatef(-50.0, 0.1, 42.5);
  glScalef(6,0.1,3);
  glutSolidCube(1.0);
  glPopMatrix();
  /////8h grammh ekkinhshs
  glPushMatrix();
  glColor3f(10.0, 10.0, 10.0);
  glTranslatef(-50.0, 0.1, 48.3);
  glScalef(6,0.1,3);
  glutSolidCube(1.0);
  glPopMatrix();
}

void keimeno(const char *str,float size)
{
  glPushMatrix();
  glScalef(size,size,size);
  for (int i=0;i<strlen(str);i++)
	glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
  glPopMatrix();
}

void crashmessage(bool tflag)
{
  if (tflag){
	  glPushMatrix();
	  glRotatef(-30,1,0,0);
	  glTranslatef(0,15,40);
	  glColor3f(5.0, 0.0, 0.0);
	  glBegin(GL_TRIANGLES);
	  glVertex2f( 7, 15 );
	  glVertex2f( -20, -10 );
	  glVertex2f( -30, 20 );
	  glVertex2f( -3, 26 );
	  glVertex2f( -7, -8 );
	  glVertex2f( -35, 10 );
	  glVertex2f( -20, 27 );
	  glVertex2f( 6, 2 );
	  glVertex2f( -30, -5 );
	  glEnd();
	  glTranslatef(-47,5,2);
	  glColor3f(5.0, 5.0, 0.0);
	  keimeno(" C R A S H ",0.06f);
	  glPopMatrix();
  }
}

void crash(bool tflag){
	if (tflag == true){
		if (animate){lifes--;}//lifeflag = false;}
		animate = false;
		crashmessage(true);
	}
}

void winnermessage(int result){
	glPushMatrix();
	glRotatef(-30,1,0,0);
	glTranslatef(0,15,40);
	glColor3f(5.0, 5.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f( 20, 20 );
    glVertex2f( 20, -20 );
    glVertex2f( -20, -20 );
    glVertex2f( -20, 20 );
    glEnd();
    glTranslatef(-20,8,1);
    glColor3f(5.0, 0.0, 0.0);
    keimeno(" WINNER ",0.06f);
	glTranslatef(5,-10,0);
	if (result == RED){keimeno(" RED ",0.06f);}
	if (result == BLUE){keimeno(" BLUE ",0.06f);}
	glTranslatef(0,-10,0);
	keimeno(" CAR ",0.06f);
    glPopMatrix();
}

void printlaps(int userl, int pcl){
	char buffer [2];
    glPushMatrix();
	glTranslatef(-110.0, 50.0, -53.0);
	glRotatef(-30,1,0,0);
	glColor3f(10.0, 10.0, 10.0);
    keimeno("Player Laps: ", 0.05f);
	itoa (userl,buffer,10);
	glTranslatef(50,0,0);
	keimeno(buffer, 0.05f);
	glTranslatef(-50,0,0);
	glTranslatef(0,-10,0);
	keimeno("Enemy Laps: ", 0.05f);
	itoa (pcl,buffer,10);
	glTranslatef(50,0,0);
	keimeno(buffer, 0.05f);
	glTranslatef(-50,0,0);
	glTranslatef(0,-10,0);
	if (lifes < 0 || pcl >= 3){keimeno("YOU LOSE!!!", 0.05f);}
	else if (userl >= pcl && userl >= 3){keimeno("YOU WIN!!!", 0.05f);}
	else{
		keimeno("Lifes left: ", 0.05f);
		itoa (lifes,buffer,10);
		glTranslatef(50,0,0);
		keimeno(buffer, 0.05f);
	}
	glPopMatrix();
}

void checklaps(float pc_x, float pc_z, float user_x, float user_z){
	if (pc_z >= 15 && pc_x <-60 && pc_x >= -63){
		if (!pc_laps_flag){pc_laps++;}
		pc_laps_flag = true;
	}
	if (pc_z >= 15 && pc_x <=-56 && pc_x >= -59){pc_laps_flag = false;}
	if (user_z >= 30 && user_x <-60 && user_x >= -63){
		if (!user_laps_flag){user_laps++;}
		user_laps_flag = true;
	}
	if (user_z >= 30 && user_x <=-56 && user_x > -59){user_laps_flag = false;}
	if (pc_laps >= 3){animate = false; winnermessage(BLUE);}
	if (user_laps >= 3){animate = false; winnermessage(RED);}
	printlaps(user_laps, pc_laps);
}

void initiate(){
	pc_laps_flag = false;
	pc_laps = 0;
	pc_car_x = -60.0;
	pc_car_z = 18.0;
	pc_car_rot = 0.0;
	pc_car_v = 0.2;
	pc_car_pos = 1;
	
	pc_laps_flag = true;
	user_laps = 0;
	user_car_x = -60.0;
	user_car_z = 42.0;
	user_car_rot = 0.0;
	user_car_v = 0.0;
	if (difficulty == 1){user_car_a = 1.5;}
	else if (difficulty == 2){user_car_a = 1.0;}
	else{user_car_a = 0.5;}
	user_car_pos = 1;
	
	trafficlight_color = GREEN;
	degrees_of_ramp = 0;
	crash_flag = false;
	no_pass_flag = false;

	random = 2;
	fakec = 0;
	temp = false;
	temp_in = false;
}

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void viewcar(float r, float g, float b){
  glPushMatrix();
  glRotatef(90,1,0,0);
  glRotatef(180,0,1,0);
  glColor3f(r, g, b);
  glScalef(0.08, 0.08, 0.08);
  glFrontFace(GL_CCW);
  DisplayModel(md);
  glFrontFace(GL_CW);
  glPopMatrix();
  
}

void Render()
{    
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  
  glTranslatef(0,0,-150);		//gia emfanish kalyterh
  glTranslatef(tx,0.0,0.0);
  glTranslatef(0.0,ty,0.0);
  glTranslatef(0.0,0.0,tz);
  glRotatef(30,1,0,0);			//gia emfanish kalyterh
  glRotatef(rotx,1,0,0);
  glRotatef(roty,0,1,0);
  
  srand ( time(NULL) );

  if(insertflag){
	  cout << "Difficulty represents the acceleration and break of your car" << endl;
	  cout << "(values from 1 to 3)" << endl;
	  cout << "Please insert difficulty: ";
	  cin >> difficulty;
	  if (difficulty >= 3){difficulty = 3;}
	  if (difficulty <= 1){difficulty = 1;}
	  if (difficulty == 1){user_car_a = 1.5;}
	  else if (difficulty == 2){user_car_a = 1.0;}
	  else{user_car_a = 0.5;}
	  cout << endl << "You can change it again from the menu!" << endl;
	  cout << endl << "Vmax is set to 8.0 Give your value: ";
	  cin >> Vmax;
	  cout << endl << "Vop is set to 6.0 Give your value: ";
	  cin >> Vop;
	  cout << endl << "You can put the default again from the menu!" << endl;
	  insertflag = false;
  }

  GLUquadricObj *pObj;
  pObj = gluNewQuadric();
  
  checklaps(pc_car_x, pc_car_z, user_car_x, user_car_z);

  if (!temp){random = rand()%8;}
  if (random == 0){
      temp = true;
	  if (!(pc_car_x >= -74 && pc_car_x <= -14 && pc_car_z <= -18)){
		  if (fakec < 80){
			  trafficlight_color = ORANGE;
			  fakec++;
		  }
		  else{
			  trafficlight_color = RED;
			  no_pass_flag = true;
			  if (degrees_of_ramp < 50 && !temp_in){degrees_of_ramp+=0.3;}
			  else{temp_in = true;}
			  if (temp_in){
				  if (degrees_of_ramp > 0){degrees_of_ramp-=0.3;}
				  else if(degrees_of_ramp <= 0){
					  temp = false;
					  temp_in = false;
					  fakec = 0;
					  trafficlight_color = GREEN;
					  no_pass_flag = false;
				  }
			  }
		  }
	  }
  }
  
  if (no_pass_flag){
	  if (user_car_x >= -74 && user_car_x <= -14 && user_car_z <= -38){crash_flag = true;}
	  if (pc_car_x >= -14.0 && pc_car_x <= -5.0 && pc_car_z == -18.0){pc_car_v = 0.0;}
  }
  else{pc_car_v = 2.0;}
  
  fanari( pObj, trafficlight_color );
  pista( pObj, degrees_of_ramp );
  crash( crash_flag );
  
  //amaksi pc
  glPushMatrix();
  glTranslatef(pc_car_x, 5.0, pc_car_z);
  glRotatef(pc_car_rot,0,1,0);
  viewcar(0.05, 0.06, 0.36);
  glPopMatrix();
  
  //amaksi user
  glPushMatrix();
  glTranslatef(user_car_x, 5.0, user_car_z);
  glRotatef(user_car_rot,0,1,0);
  viewcar(0.35, 0.06, 0.06);
  glPopMatrix();

  glutSwapBuffers();
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

	cur_time = glutGet(GLUT_ELAPSED_TIME);
	dt1 = 3*(cur_time - prev_time)/100.0;
	prev_time = cur_time;
	//pc_car_v = 2.0;

	if(animate){
		//////////////////////////////  PC CAR  //////////////////////////////////////////
		if (pc_car_pos == 1){							/////
			pc_car_x += (pc_car_v * dt1);
			pc_car_z = 18.0;
			pc_car_rot = 0.0;
			if (pc_car_x >= 60.0){pc_car_pos++;pc_car_f=0;}
		}
		else if (pc_car_pos == 2){
			pc_car_w = pc_car_v / pc_car_R;
			pc_car_f += pc_car_w * dt1;
			pc_car_rot = pc_car_f * 60;

			pc_car_x += (pc_car_R * cos(pc_car_f))/(pc_car_v*8);
			pc_car_z -= (pc_car_R * sin(pc_car_f))/(pc_car_v*8);
			if (pc_car_z <= -18.0){pc_car_pos++;}
		}
		else if (pc_car_pos == 3){
			pc_car_x -= pc_car_v;
			pc_car_z = -18.0;
			pc_car_rot = 180.0;
			if (pc_car_x <= -60.0){pc_car_pos++;pc_car_f=0;}
		}
		else if (pc_car_pos == 4){
			pc_car_w = pc_car_v / pc_car_R;
			pc_car_f += pc_car_w * dt1;
			pc_car_rot = (pc_car_f * 60)+180;
			
			pc_car_x -= (pc_car_R * cos(pc_car_f))/(pc_car_v*8);
			pc_car_z += (pc_car_R * sin(pc_car_f))/(pc_car_v*8);
			
			if (pc_car_z >= 18.0){pc_car_pos = 1;}
		}
		//////////////////////////////  USERS CAR  //////////////////////////////////////////
		if (user_car_pos == 1){								/////
			user_car_x += user_car_v;
			user_car_z = 42.0;
			user_car_rot = 0.0;
			if (user_car_x >= 60.0){user_car_pos++;}
			if (user_car_x < -60.0){user_car_pos = 12;}
		}
		else if (user_car_pos == 2){
			user_car_x += (user_car_v*2/3);
			user_car_z -= (user_car_v*1/3);
			user_car_rot = 22.5;
			if (user_car_x >= 87.0){user_car_pos++;}
			if (user_car_x < 60.0){user_car_pos--;}
			if (user_car_v > Vop){crash_flag = true;}
		}
		else if (user_car_pos == 3){
			user_car_x += (user_car_v*1/3);
			user_car_z -= (user_car_v*2/3);
			user_car_rot = 67.5;
			if (user_car_x >= 96.0 || user_car_z <= 8.0){user_car_pos++;}
			if (user_car_x < 87.0){user_car_pos--;}
			if (user_car_v > Vop){crash_flag = true;}
		}
		else if (user_car_pos == 4){						/////
			user_car_x = 96.0;
			user_car_z -= user_car_v;
			user_car_rot = 90.0;
			if (user_car_z <= -9.0){user_car_pos++;}
			if (user_car_z > 9.0){user_car_pos--;}
			if (user_car_v > Vop){crash_flag = true;}
		}
		else if (user_car_pos == 5){
			user_car_x -= (user_car_v*1/3);
			user_car_z -= (user_car_v*2/3);
			user_car_rot = 112.5;
			if (user_car_x <= 87.0){user_car_pos++;}
			if (user_car_x > 96.0 || user_car_z >= -8.0){user_car_pos--;}
			if (user_car_v > Vop){crash_flag = true;}
		}
		else if (user_car_pos == 6){
			user_car_x -= (user_car_v*2)/3;
			user_car_z -= (user_car_v*1)/3;
			user_car_rot = 157.5;
			if (user_car_x <= 60.0){user_car_pos++;}
			if (user_car_x > 87.0){user_car_pos--;}
			if (user_car_v > Vop){crash_flag = true;}
		}
		else if (user_car_pos == 7){						/////
			user_car_x -= user_car_v;
			user_car_z = -42.0;
			user_car_rot = 180.0;
			if (user_car_x <= -60.0){user_car_pos++;}
			if (user_car_x > 60.0){user_car_pos--;}
		}
		else if (user_car_pos == 8){
			user_car_x -= (user_car_v*2/3);
			user_car_z += (user_car_v*1/3);
			user_car_rot = 202.5;
			if (user_car_x <= -87.0){user_car_pos++;}
			if (user_car_x > -60.0){user_car_pos--;}
			if (user_car_v > Vop){crash_flag = true;}
		}
		else if (user_car_pos == 9){
			user_car_x -= (user_car_v*1/3);
			user_car_z += (user_car_v*2/3);
			user_car_rot = 247.5;
			if (user_car_x <= -96.0 || user_car_z >= -8.0){user_car_pos++;}
			if (user_car_x > -87.0){user_car_pos--;}
			if (user_car_v > Vop){crash_flag = true;}
		}
		else if (user_car_pos == 10){						/////
			user_car_x = -96.0;
			user_car_z += user_car_v;
			user_car_rot = 270.0;
			if (user_car_z >= 9.0){user_car_pos++;}
			if (user_car_z < -9.0){user_car_pos--;}
			if (user_car_v > Vop){crash_flag = true;}
		}
		else if (user_car_pos == 11){
			user_car_x += (user_car_v*1/3);
			user_car_z += (user_car_v*2/3);
			user_car_rot = 292.5;
			if (user_car_x >= -87.0){user_car_pos++;}
			if (user_car_x < -96.0 || user_car_z <= 8.0){user_car_pos--;}
			if (user_car_v > Vop){crash_flag = true;}
		}
		else if (user_car_pos == 12){
			user_car_x += (user_car_v*2/3);
			user_car_z += (user_car_v*1/3);
			user_car_rot = 337.5;
			if (user_car_x >= -60.0){user_car_pos = 1;}
			if (user_car_x < -87.0){user_car_pos--;}
			if (user_car_v > Vop){crash_flag = true;}
		}
		////////////////////////////////////////////////////////////////////////
	}
	glutPostRedisplay();
}

void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 'q' : exit(0);break;															//quit
	case 'p' : if (lifes > 0 && !crash_flag){animate = !animate;}break;					//pause/play
	case 'e' : if (lifes > 0){initiate(); animate = false;crash_flag = false;}break;	//enarksh
	case 'r' : initiate(); animate = false;crash_flag = false; lifes = 3;break;			//restart
	case 't' : lifes++;break;															//take life
	case 'a' : tx-=2.5f;break;															//like games "a"
	case 'd' : tx+=2.5f;break;															//like games "d"
	case 'w' : ty += 2.5f;break;														//like games "w"
	case 's' : ty -= 2.5f;break;														//like games "s"
	case '+' : tz += 2.5f;break;														//zoom in
	case '-' : tz -= 2.5f;break;														//zoom out
	case '[' : rotx += 2.5f;break;														//rotate x positive
	case ']' : rotx -= 2.5f;break;														//rotate x negative
	default : break;
	}
	glutPostRedisplay();
}

void SpecialMovement(int key,int x,int y)
{
	switch(key)
	{
	case GLUT_KEY_UP : ty += 2.5f;break;												//move up
	case GLUT_KEY_DOWN : ty -= 2.5f;break;												//move down
	case GLUT_KEY_LEFT : tx -= 2.5f;break;												//move left
	case GLUT_KEY_RIGHT : tx += 2.5f;break;												//move right
	case GLUT_KEY_PAGE_UP : user_car_v += user_car_a;if(user_car_v > Vmax){user_car_v = Vmax;}break;	//accelerate
	case GLUT_KEY_PAGE_DOWN : user_car_v -= user_car_a;if(user_car_v < -Vmax){user_car_v = -Vmax;}break;//deaccelerate
	case GLUT_KEY_HOME : roty += 2.5f;break;											//rotate y positive
	case GLUT_KEY_END : roty -= 2.5f;break;												//rotate y negative
	default : break;
	}
	glutPostRedisplay();
}

void Mouse(int button,int state,int x,int y)
{
	 if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		animate = !animate;
        glutPostRedisplay();
	 }
}

void Setup()  // TOUCH IT !! 
{ 
	ReadFile(&md);

	//Parameter handling
	glShadeModel (GL_SMOOTH);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);
    
	// polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
  
	//Set up light source
	GLfloat light_position[] = { 0.0, 30.0, 50.0, 0.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	   
	glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
	

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	//01
	//glFrontFace(GL_CCW);	//counterclockwise
	glFrontFace(GL_CW);		//clockwise

	// Black background
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

void MenuSelect(int choice)
{
	switch (choice) {
		case EASY : difficulty = 1;user_car_a = 1.5;break;
		case MEDIUM : difficulty = 2;user_car_a = 1.0;break;
		case HARD : difficulty = 3;user_car_a = 0.5;break;
		case VMAX : Vmax = 2.0; break;
		case VOP : Vop = 1.5;break;
	}

}

void ReadFile(model *md)
{

	ifstream obj_file("clk.obj");                   // Open the file for reading OBJINFO.TXT
   
	if (obj_file.fail()) 
		exit(1);
	
	char objLine[256];

	int v_count=0, v_start=0, v_end=0;
	int f_count=0, f_start=0, f_end=0;
	int line_count=0;

	while(!obj_file.eof()){
		obj_file.getline(objLine, 255);
		line_count++;
		if(objLine[0] == 'v'){
			if(v_count == 0){
				v_start = line_count;
			}
			v_count++;
		}
		else if(objLine[0] == 'f'){
			if(f_count == 0){
				f_start = line_count;
			}
			f_count++;
		}
	}
	v_end = v_start + v_count -1;
	f_end = f_start + f_count -1;

	md->vertices = v_count;								// Get the number of vertices
	md->faces = f_count;								// Get the number of faces

	//dynamic allocations of matrices
	md->obj_points_v = new point[md->vertices];
	md->obj_points_n = new point[md->faces];
	md->obj_faces = new face[md->faces];

	obj_file.close();
	
	ifstream obj_file2("clk.obj");

	if (obj_file2.fail()) 
		exit(1);

	char type;

	//checks again the first letter of each line to be sure and then puts data in matrices
	for (int i = 0; i < md->vertices; i++){                        // Get the vertex coordinates
	    obj_file2 >> type;
		if(type == 'v'){
			obj_file2 >> md->obj_points_v[i].x;
			obj_file2 >> md->obj_points_v[i].y;
			obj_file2 >> md->obj_points_v[i].z;
		}
		else{
			i--;
			obj_file2.getline(objLine, 255);
		}
   }

   for (int i = 0; i < md->faces; i++){                        // Get the face structure
	    obj_file2 >> type;
		if(type == 'f'){
		obj_file2 >> md->obj_faces[i].vtx[0];
		obj_file2 >> md->obj_faces[i].vtx[1];
		obj_file2 >> md->obj_faces[i].vtx[2];
		}
		else{
			i--;
			obj_file2.getline(objLine, 255);
		}
   }

   obj_file2.close();
}

point NormalCalculation(point p1, point p2, point p3){
//type of point
	double v1x,v1y,v1z,v2x,v2y,v2z;
	double nx,ny,nz;
	double vLen;
 
	point Result;
 
	// Calculate vectors
	v1x = p1.x - p2.x;
	v1y = p1.y - p2.y;
	v1z = p1.z - p2.z;
 
	v2x = p2.x - p3.x;
	v2y = p2.y - p3.y;
	v2z = p2.z - p3.z;
 
	// Get cross product of vectors
	nx = (v1y * v2z) - (v1z * v2y);
	ny = (v1z * v2x) - (v1x * v2z);
	nz = (v1x * v2y) - (v1y * v2x);
 
	// Normalise final vector
	vLen = sqrt( (nx * nx) + (ny * ny) + (nz * nz) );
 
	Result.x = (float)(nx / vLen);
	Result.y = (float)(ny / vLen);
	Result.z = (float)(nz / vLen);
 
	return Result;
}

void DisplayModel(model md)
{

	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < md.faces; i++)
	{
		md.obj_points_n[i] = NormalCalculation(md.obj_points_v[md.obj_faces[i].vtx[0]-1], md.obj_points_v[md.obj_faces[i].vtx[1]-1], md.obj_points_v[md.obj_faces[i].vtx[2]-1]); 
		
		glNormal3f(md.obj_points_n[i].x, md.obj_points_n[i].y, md.obj_points_n[i].z);		
		glVertex3f(md.obj_points_v[md.obj_faces[i].vtx[0]-1].x,md.obj_points_v[md.obj_faces[i].vtx[0]-1].y,md.obj_points_v[md.obj_faces[i].vtx[0]-1].z);
		glVertex3f(md.obj_points_v[md.obj_faces[i].vtx[1]-1].x,md.obj_points_v[md.obj_faces[i].vtx[1]-1].y,md.obj_points_v[md.obj_faces[i].vtx[1]-1].z);
		glVertex3f(md.obj_points_v[md.obj_faces[i].vtx[2]-1].x,md.obj_points_v[md.obj_faces[i].vtx[2]-1].y,md.obj_points_v[md.obj_faces[i].vtx[2]-1].z);
	}

	glEnd();
	glPopMatrix();

}