#include <iostream>
#include "ShaderHelpers.h"
#include "ModelHelper.h"
#include "ProceduralModels.h"
#include "Shape.h"
#include "Entity.h"
#include "Camera.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <glm\glm.hpp> 
#include <glm\gtx\transform.hpp>
#include <glew.h>
#include <vector>
#define GLFW_INCLUDE_GLU
#include <glfw3.h>
#include <SOIL.h>
using namespace std;
using namespace glm;

//Global Variables
GLuint VBO = 1;
GLuint VBO_color = 1;
GLuint VAO = 1;
float previousTime;


//default axis
vec3 rotAxis;

ShaderHelpers helper;
//ModelHelper mhelper; 
GLuint program;
ProceduralModels pm;


//misc 
float rotationAmount;

//current position vector for mouse. 
vec3 currentPos;

//height and width of window 
int height;
int width;

//random variables
float randX;
float randRotspeed;
float randRed;
float randGreen;
float randBlue;

//check if mouse button is held 
bool mouseHeld;
//check if keys are held
bool movingLeft;
bool movingRight;
bool movingForward;
bool movingBack;

//global reference to window
GLFWwindow* window;

Camera* cam;

// counter for vector update 
int counter;

//head Model
Shape* Model;
Entity PaddleA; 
Entity PaddleB; 
Entity Ball; 

//model helper
ModelHelper mhelper; 

static float RandomFloat(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

//mouse response 
void mouseResponse(Entity* triangle)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	//put mouse input in opengl coordinates
	float x = (xpos / width) * 2 - 1;
	float y = (1 - (ypos / height) * 2);

	//set obj pos to mouse pos for triangle

	if (triangle != NULL && triangle->isActive() == false)
	{
		currentPos.x = x;
		currentPos.y = y;
		triangle->setCurrentPos(currentPos);
		triangle->setActive(true);
	}


}



void init()
{
	//disable cursor 
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	program = helper.loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (program != 0)
	{
		glUseProgram(program);
	}
	//helper.setShaderColor(program, "uniformColor", 1.0f, 1.0f, .0f);

	cout << "Initializing" << endl;

	//initialize random variables
	randX = 0.0f;
	randRotspeed = 0.0f;
	randRed = 1.0f;
	randGreen = 0.0f;
	randBlue = 0.0f;
	//set currentPos
	currentPos = vec3(0.0f, 0.0f, 0.0f);
	//set axis 
	rotAxis = vec3(1.0f, 1.0f, 0.0f);

	//set mouse and key state
	mouseHeld = false;
	movingLeft = false;
	movingRight = false;
	movingForward = false;
	movingBack = false;

	counter = 0;

	rotationAmount = 0.0;
	//Create the Shapes/Models

	//load model
	// Read our .obj file
	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals; 
	
	string file = "Models/Cube.obj"; 
	bool res = mhelper.loadModelFile("Models/Cube.obj", vertices, uvs, normals);
	if (res == true)
	{
	cout << "Model loaded successfully!" << endl;
	}
	else
	{
	cout << "Model could not be loaded!" << endl;
	}

	vec3 initialPosition = vec3(0, 0, -1.3f); 
	vec3 scale = vec3(0.5f, 0.5f, 0.5f); 
	vec3 rotAxis = vec3(0, 0, 1.0f); 
	float rotAmt = 1.2f;
	float rotSpeed = 0.1f; 
	const GLsizei size = vertices.size();
	Shape* tempShape = new Shape(vertices, size, normals, uvs, program); 
	PaddleA = Entity(tempShape, initialPosition, scale, rotAxis, rotAmt, rotSpeed); 


	//pm.makeTorus(128, 128);

	/*vector<vector<vec3>> k =
	{
		{ vec3(1, -1, -1), vec3(1, -1, 1), vec3(1,1,1) },
		{ vec3(-1, 1, -1), vec3(-1, 1, 1), vec3(-1,-1, 1) },
		{ vec3(-1, -1, 1), vec3(-1, -1, -1), vec3(-1, 1, -1) },
		{ vec3(1, 1, -1), vec3(1, 1, 1), vec3(1, -1, 1) },
	};*/
	

	//pm.makeBezierSurface(16, 16, k);
	//pm.makeSphere(10, 10, 1.0f);
	//pm.makeCube(1.0f); 
	//pm.makeCylinder(10, 1.0f); 

	//vertices = pm.positions;
	//uvs = pm.uvs;
	//normals = pm.normals;

	 //size = vertices.size();
	//Model = new Shape(vertices, size, normals, uvs, program);










	//glClearColor(0.392f,0.584f,0.929f,1.0f); 
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	//Draw in wireframe 
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//add depth
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearDepth(1.0f);

	cam = new Camera();

}


void update()
{
	//cout << "Updating" << endl;
	float currentTime = glfwGetTime();
	float dt = currentTime - previousTime;
	previousTime = currentTime;


	//update paddles
	PaddleA.Update();

	//check if mouse is being held
	if (mouseHeld == true)
	{
		rotationAmount += 0.5f * dt;
	}
	else
	{
		rotationAmount = 0;
	}

	//turn camera here 
	//make an update camera 
	//move laterally
	//get cursor position
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	//get current position - 400
	//reset cursor postion with glfw set cursor pos to center of screen
	glfwSetCursorPos(window, 500, 300);



	//movement speeds 
	float strafeSpeed = 1.5f;
	float speed = 1.5f;
	//step 1 & 2 - check if keys are being held and move
	if (movingLeft == true)
	{
		//move camera left 

		//get normalized left vec
		vec3 left = -cam->getRight();
		//scale
		left = left * dt * strafeSpeed;
		cam->move(left);
	}
	if (movingRight == true)
	{
		//move camera right

		//get normalized left vec
		vec3 right = cam->getRight();
		//scale
		right = right * dt * strafeSpeed;
		cam->move(right);
	}
	if (movingForward == true)
	{
		//move camera forward
		vec3 forward = cam->getForward();
		glm::normalize(forward);
		forward = forward * dt * speed;
		cam->move(forward);
	}
	if (movingBack == true)
	{
		//move camera forward
		vec3 back = -cam->getForward();
		glm::normalize(back);
		back = back * dt * speed;
		cam->move(back);
	}


	//step 3 & 4 - get view matrix from cam's position
	float fov = M_PI * 0.4f;
	mat4 camMatrix = perspective(fov, 1.0f, .01f, 1000.f) *
		lookAt(
			cam->getLocation(),
			cam->getLookAt(),
			cam->getUp()
			);

	//step 5 - upload camera matrix
	glProgramUniformMatrix4fv(
		program,
		glGetUniformLocation(program, "camMatrix"),
		1,
		GL_FALSE,
		&camMatrix[0][0]);


	//step 6 -set cursor to center of screen 
	glfwSetCursorPos(window, 500, 300);

}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//draw entities  
	//helper.setShaderColor(program, "color", 1.0f, 1.0f, 0.0f);

	//te.Draw(); 
	//Model->Draw(vec3(0.0f, 0.0f, -4.0f), vec3(1.0f, 1.0f, 1.0f), rotAxis, rotationAmount);
	PaddleA.Draw(); 

	//Triangle->Draw(vec3(0, 0, 0), vec3(1.0f, 1.0f, 1.0f), zRotAxis, rotationAmount);

	glFlush();
	//cout << "Drawing" << endl;

}



void mouse_button_callback(GLFWwindow* windowPtr, int button, int action, int mods)
{
	//LEFT Mouse Button Pressed 
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//Check if mouse boolean is held == true. Then do mouse response method is update if held == true 

		mouseHeld = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		mouseHeld = false;
	}





}


void keyCallback(GLFWwindow* windowPtr, int key, int scancode, int action, int mods)
{
	//Step 1 - detect WASD input and Q to quit 
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(windowPtr, GL_TRUE);
	}
	else if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		//move forward
		movingForward = true;

	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		movingForward = false;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		//move left 
		movingLeft = true;

	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		movingLeft = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		//move back
		movingBack = true;

	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		movingBack = false;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		//move right
		movingRight = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		movingRight = false;
	}


}

void mouseMove(GLFWwindow* windowPtr, double x, double y)
{
	double xpos, ypos;
	glfwGetCursorPos(windowPtr, &xpos, &ypos);

	int width, height;
	glfwGetWindowSize(windowPtr, &width, &height);

	//put mouse input in opengl coordinates
	float x1 = (xpos / width) * 2 - 1;
	float y1 = (1 - (ypos / height) * 2);

	//multiplying to speed up looking movement
	float lookSpeed = 2.5f;
	//cam->turn(-x1 * lookSpeed, y1 * lookSpeed); 
	//cam->turn(-x1, y1);
}


int main(int argc, char** argv)
{

	//seed random 
	//srand(time(0));
	srand((unsigned)time(NULL));

	//run init
	if (!glfwInit())
	{
		return -1;
	}
	//create window
	window = glfwCreateWindow(1000, 600, "OpenGL Game and Physics Engine Review", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//make window current context
	glfwMakeContextCurrent(window);

	//call glew init and init
	glewInit();
	init();

	//callbacks
	//check for input 
	//glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseMove);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) { return -1; }

	//main loop until user closes window
	while (!glfwWindowShouldClose(window))
	{
		//Poll events
		glfwPollEvents();

		//render
		update();
		draw();
		glfwSwapBuffers(window);
	}


	return 0;
}

