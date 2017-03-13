#define EASY 1
#define MEDIUM 2
#define HARD 3
#define VMAX 4
#define VOP 5

#define RED 6
#define BLUE 7
#define ORANGE 8
#define GREEN 9

struct point 
{
	float x; 
	float y; 
	float z; 
};

struct face
{
	int vtx[3];
};

struct model
{
	point* obj_points_v;
	point* obj_points_n;
	face* obj_faces;
	int vertices;
	int faces;
};

//-------- MY Functions --------------------------------

void fanari(GLUquadricObj *pObj, int trafficlight_color);

void pista(GLUquadricObj *pObj, int degrees_of_ramp);

void keimeno(const char *str,float size);

void crashmessage(bool tflag);

void crash(bool tflag);

void winnermessage(int result);

void printlaps(int userl, int pcl);

void checklaps(float pc_x, float pc_z, float user_x, float user_z);

void initiate();

void sleep(unsigned int mseconds);

void viewcar(float r, float g, float b);

void ReadFile(model *md);

point NormalCalculation(point p1, point p2, point p3);

//-------- Clasic Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();

void ReadFile(model*);
//Function for reading a model file

void DisplayModel(model);
// Function for displaying a model

void Keyboard(unsigned char key,int x,int y);
// Function for handling keyboard events.

void Mouse(int button,int state,int x,int y); 
// Function for handling mouse events

void SpecialMovement(int key,int x,int y);

void MenuSelect(int choice);

