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

/* Basic Square to Move Around and Stuff */
float squarePosX = 0, squarePosY = 0, squarePosZ = 0;
float squareSize = 0.25;

/* Mesh loaded in from an OBJ file */
Mesh model("./res/monkey.obj");

// A few conversions to know



/* function DisplayCallbackFunction(void)
* Description:
*  - this is the openGL display routine
*  - this draws the sprites appropriately
*/
void DisplayCallbackFunction(void)
{
	/* clear the screen */
	glViewport(0, 0, windowWidth, windowHeight); //(0,0) is the top left
	glClearColor(0.2f, 0.2f, 0.2f, 0.8f); //Sets the background colour
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears the colour buffer and the depth buffer (not sure what the depth buffer is)
	glMatrixMode(GL_PROJECTION); //Sets up the projection matrix, will learn more later
	glLoadIdentity(); //Loads an identity matrix to 'wipe' the transformations

	/* This is where we draw things */
	glColor3f(0.33, 0.22f, 0.78f);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glBegin(GL_TRIANGLES);
	{
		//OpenGL draws counter-clockwise so start from bottom left and then go around (ie: quadrant III, IV, I, II)
		/*glVertex3f(0.25, -0.25, 0);
		glVertex3f(-0.25, -0.25, 0);
		glVertex3f(0, 0.25, 0);*/

		model.draw();
	}
	glEnd();

	/* Swap Buffers to Make it show up on screen */
	glutSwapBuffers();
}



/* function void KeyboardCallbackFunction(unsigned char, int,int)
* Description:
*   - this handles keyboard input when a button is pressed
*/
void KeyboardCallbackFunction(unsigned char key, int x, int y)
{
	std::cout << "Key Down:" << (int)key << std::endl;

	/* ADDED, moves the square around using WASD for x-axis and y-axis, also X & C move along the z-axis*/
	if (key == 'w')
		squarePosY += 0.02f;
	else if (key == 's')
		squarePosY -= 0.02f;
	else if (key == 'a')
		squarePosX -= 0.02f;
	else if (key == 'd')
		squarePosX += 0.02f;
	else if (key == 'c')
		squarePosZ += 0.02f;
	else if (key == 'x')
		squarePosZ -= 0.02f;

	/* ADDED, scales the square slightly using ',' and '.' */
	if (key == ',')
		squareSize -= 0.01f;
	else if (key == '.')
		squareSize += 0.01f;

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
	model.scale(0.5f);

	/* initialize the window and OpenGL properly */
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Game Window");

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