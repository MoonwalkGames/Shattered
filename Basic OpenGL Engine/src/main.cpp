// Core Libraries
#include <iostream>
#include <string>
#include <math.h>

// 3rd Party Libraries
#include <GLUT/glut.h>

//My Includes
#include "Mesh.h"

// Defines and Core variables
#define FRAMES_PER_SECOND 60
const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND; // Miliseconds per frame

int windowWidth = 800;
int windowHeight = 800;

int mousepositionX;
int mousepositionY;

/* Meshes loaded in from an OBJ file */
Mesh model1("./res/monkey.obj");
Mesh model2("./res/chest.obj");
Mesh model3("./res/sphere.obj");
Mesh model4("./res/crate.obj");

//Can enable and disable the lighting dynamically during runtime
bool lightingEnabled = true;

//Can switch between 1 and 4 viewports dynamically during runtime
bool singleViewport = true;

// A few conversions to know
float radToDeg = 180.f / 3.14159f;
float degToRad = 3.14159f / 180.0f;

//Initializes all of the open gl variables (lighting, back face culling, etc)
void initGLValues(int argc, char **argv)
{
	/* --------- All lighting code below is taken from the internet tutorial for now --------- */
	//Enable the lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	// Create light components
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { -5.0f, 1.0f, -4.0f, 1.0f };

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	// enable color tracking
	glEnable(GL_COLOR_MATERIAL);
	// set material properties which will be assigned by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	/* --------- All lighting code above is taken from the internet tutorial for now --------- */

	//Sets up back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/* initialize the window and OpenGL properly */
	glutInit(&argc, argv);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Game Window");
}

//Allows the user to toggle the lighting engine on and off using a key press
void toggleLighting()
{
	lightingEnabled = !lightingEnabled;
}

//Allows the user to toggle the viewports between 1 and 4
void toggleViewports()
{
	singleViewport = !singleViewport;

	if (singleViewport)
		cout << "Rendering a single viewport!" << endl;
	else
		cout << "Rendering 4 separate viewports!" << endl;
}

/* function DisplayCallbackFunction(void)
* Description:
*  - this is the openGL display routine
*  - this draws the sprites appropriately
*/
void DisplayCallbackFunction(void)
{
	//Clear the screen
	glClearColor(0.2f, 0.2f, 0.2f, 0.8f); //Sets the background colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the colour buffer and the depth buffer (not sure what the depth buffer is)
	glMatrixMode(GL_PROJECTION); //Sets up the projection matrix, will learn more later
	glLoadIdentity(); //Loads an identity matrix to 'wipe' the transformations

					  //Decides whether or not to render the lighting in the scene depending on the user's request
	if (lightingEnabled)
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}

	//Creates either a single viewport or four seperate viewports depending on a key press
	if (singleViewport)
	{
		//Creates a full screen viewport and then draws a solid mesh into it (Mesh = monkey)
		//*****************************************************************************************
		glViewport(0, 0, windowWidth, windowHeight);

		glBegin(GL_TRIANGLES);
		{
			if (lightingEnabled)
				glColor3f(0.33f, 0.22f, 0.78f);

			model3.draw();
		}
		glEnd();
	}
	else
	{
		//Creates viewport 1 (bottom left) and then draws a wireframe mesh into it (Mesh = monkey)
		//*****************************************************************************************
		glViewport(0, 0, windowWidth / 2, windowHeight / 2);

		glBegin(GL_LINES);
		{
			glColor3f(0.33, 0.22f, 0.78f);
			model1.draw();
		}
		glEnd();

		//Creates viewport 2 (top right) and then draws a wireframe mesh into it (Mesh = chest)
		//*****************************************************************************************
		glViewport(windowWidth / 2, windowHeight / 2, windowWidth / 2, windowHeight / 2);

		glBegin(GL_LINES);
		{
			glColor3f(1.0f, 0.5f, 0.33f);
			model2.draw();
		}
		glEnd();

		//Creates viewport 3 (top left) and then draws a solid mesh into it (Mesh = sphere)
		//*****************************************************************************************
		glViewport(0, windowHeight / 2, windowWidth / 2, windowHeight / 2);

		glBegin(GL_TRIANGLES);
		{
			glColor3f(0.5f, 1.0f, 0.33f);
			model3.draw();
		}
		glEnd();

		//Creates viewport 4 (bottom right) and then draws a solid mesh into it (Mesh = crate)
		//*****************************************************************************************
		glViewport(windowWidth / 2, 0, windowWidth / 2, windowHeight / 2);

		glBegin(GL_TRIANGLES);
		{
			glColor3f(0.5f, 0.5f, 1.0f);
			model4.draw();
		}
		glEnd();
	}

	/* Swap Buffers to make it show up on screen */
	glutSwapBuffers();

}



/* function void KeyboardCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is pressed
*/
void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	std::cout << "Key Down:" << (int)key << std::endl;

	//Keys that were added by us
	if (key == 'l')
		toggleLighting();
	else if (key == 'v')
		toggleViewports();

	//Keys that were set up when Mike and Thomas made this engine
	switch (key)
	{
	case 32: // the space bar
		break;
	case 27: // the escape key
	case 'q': // the 'q' key
		exit(0);
		break;
	}
}

/* function void KeyboardUpCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is lifted
*/
void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{
}

/* function TimerCallbackFunction(int value)
* Description:
*  - this is called many times per second
*  - this enables you to animate things
*  - no drawing, just changing the state
*  - changes the frame number and calls for a redisplay
*  - FRAME_DELAY is the number of milliseconds to wait before calling the timer again
*/
void TimerCallbackFunction(int value)
{
	/* this call makes it actually show up on screen */
	glutPostRedisplay();

	/* this call gives it a proper frame delay to hit our target FPS */
	glutTimerFunc(FRAME_DELAY, TimerCallbackFunction, 0);
}

/* function WindowReshapeCallbackFunction()
* Description:
*  - this is called whenever the window is resized
*  - and sets up the projection matrix properly
*  - currently set up for an orthographic view (2D only)
*/
void WindowReshapeCallbackFunction(int w, int h)
{
	// switch to projection because we're changing projection
	float aspectRatio = float(w) / float(h); //New aspect ration, w & h are supplied by OpenGL
	glMatrixMode(GL_PROJECTION); //Resets the projection matrix
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h); //Will be explained later
	windowWidth = w; //Sets the windowWidth & Height from above to the new values
	windowHeight = h;

	//switch back to modelview
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	// Handle mouse clicks
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
			std::cout << "LEFT CLICK \t Mouse X: " << x << "\tMouse Y: " << y << std::endl;
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
			std::cout << "RIGHT CLICK \t Mouse X: " << x << "\tMouse Y: " << y << std::endl;
	}
	else if (button == GLUT_MIDDLE_BUTTON)
	{
		if (state == GLUT_DOWN)
			std::cout << "MIDDLE CLICK \t Mouse X: " << x << "\tMouse Y: " << y << std::endl;
	}

}


/* function MouseMotionCallbackFunction()
* Description:
*   - this is called when the mouse is clicked and moves
*/
void MouseMotionCallbackFunction(int x, int y)
{
}

/* function MousePassiveMotionCallbackFunction()
* Description:
*   - this is called when the mouse is moved in the window
*/
void MousePassiveMotionCallbackFunction(int x, int y)
{
	mousepositionX = x;
	mousepositionY = y;
}

/* function main()
* Description:
*  - this is the main function
*  - does initialization and then calls glutMainLoop() to start the event handler
*/
int main(int argc, char **argv)
{
	//Sets up all of the opengl stuff, passes on argc and argv because gluInit needs them
	initGLValues(argc, argv);

	//Scales the models to a good view size
	model1.scale(0.5f);
	model2.scale(0.5f);
	model3.scale(0.5f);
	model4.scale(1.0f);

	/* set up our function callbacks */
	glutDisplayFunc(DisplayCallbackFunction); //Draw
	glutKeyboardFunc(KeyboardCallbackFunction); //Key Down
	glutKeyboardUpFunc(KeyboardUpCallbackFunction); //Key Up
	glutReshapeFunc(WindowReshapeCallbackFunction); //Window resized
	glutMouseFunc(MouseClickCallbackFunction); //Mouse Clicked
	glutMotionFunc(MouseMotionCallbackFunction); //Mouse Moved (ie: move with clicking)
	glutPassiveMotionFunc(MousePassiveMotionCallbackFunction); //Mouse move passive (ie: move without clicking)
	glutTimerFunc(1, TimerCallbackFunction, 0); //Timer Function / Clock tick function / Time step

												/* start the event handler */
	glutMainLoop();

	return 0;
}