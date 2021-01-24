#include "Tema1.h"
#include "Transform2D.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

int score = 0;
float shuriken_speed = 200;
float balloon_speed = 100;
float increaseLevel = 0;
vector<bool> new_level;
bool win = false;

glm::vec3 red_color = glm::vec3(1, 0, 0);
glm::vec3 yellow_color = glm::vec3(1, 1, 0);
glm::vec3 white_color = glm::vec3(1, 1, 1);

float arrowhead_X = 4, arrowhead_Y = 2.5f;
float save_arrowheadX, save_arrowheadY;

double r1_bow = 2.5, r2_bow = 2.6;
double r1_balloon = 0.5, r2_balloon = 0.6;

double radius_balloon = 8;
double radius_shuriken = 6.5f;
double radius_bow = 2.6f;

bool rotate_arrow = true;
bool hold_mouse = false;
bool flying = false;

bool restart = false;

float centerX_arrow = 0;
float centerY_arrow = 2.5f;

float centerX_shuriken = 0;
float centerY_shuriken = 0;

int nr_red_balloons = 3;
vector<Balloon::Balloon*> red_balloons;

int nr_yellow_balloons = 3;
vector<Balloon::Balloon*> yellow_balloons;

int nr_shurikens = 3;
vector<Shuriken::Shuriken*> shurikens;

int nr_arrows = 2;

float arrow_speed;
float save_scaleX;

float arrow_distance = 10;
vector<bool> collision_red;
vector<bool> collision_yellow;
vector<bool> collision_arrow_shuriken;
vector<bool> collision_bow_shuriken;

int addToScore = 0;
int lives = 3;
int decreaseLives = 0;
float y_max = 0;


Tema1::Tema1()
{
}

Tema1::~Tema1()
{

}

// Function to create arrow
void Tema1::createArrow(glm::vec3 color){
	vector<VertexFormat> vertices_arrow
	{
		VertexFormat(glm::vec3(3.5f,2.25f,0), color),
		VertexFormat(glm::vec3(3.5f,2.75f,0), color),
		VertexFormat(glm::vec3(arrowhead_X,arrowhead_Y,0), color),

		VertexFormat(glm::vec3(0,2.55f,0), color),
		VertexFormat(glm::vec3(0,2.45f,0), color),
		VertexFormat(glm::vec3(3.5f,2.45f,0), color),
		VertexFormat(glm::vec3(3.5f,2.55f,0),color)
	};

	vector<unsigned short> indices_arrow =
	{
		0,1,2,
		3,4,5,
		5,3,6
	};

	meshes["arrow"] = new Mesh("generated arrow");
	meshes["arrow"]->InitFromData(vertices_arrow, indices_arrow);
	meshes["arrow"]->SetDrawMode(GL_TRIANGLES);

	Mesh* arrow = CreateMesh("arrow", vertices_arrow, indices_arrow);
}

//  ---- Function to create arc circle for bow
void Tema1::createBowArcCircle(glm::vec3 color) {
	vector<VertexFormat> vertices_bow
	{
	};

	double x, y;
	int nr_vertices = 100;

	for (int i = 0; i < nr_vertices; i++) {

		double angle = i * 2 * M_PI / nr_vertices;
		x = (r1_bow * cos(angle));
		y = (r1_bow * sin(angle));

		vertices_bow.push_back(VertexFormat(glm::vec3(x, y, 0), color));

		x = (r2_bow * cos(angle));
		y = (r2_bow * sin(angle));

		vertices_bow.push_back(VertexFormat(glm::vec3(x, y, 0), color));

	}


	vector<unsigned short> indices_bow =
	{
	};

	for (int i = 1 * (nr_vertices * 2) / 4; i < 3 * (nr_vertices * 2) / 4; i++) {
		indices_bow.push_back(i);
		indices_bow.push_back(i + 1);
		indices_bow.push_back(i + 2);
	}


	meshes["bow"] = new Mesh("generated bow");
	meshes["bow"]->InitFromData(vertices_bow, indices_bow);
	meshes["bow"]->SetDrawMode(GL_TRIANGLE_STRIP);

	Mesh* bow = CreateMesh("bow", vertices_bow, indices_bow);
}

//  ---- Function to create line for bow
void Tema1::createBowLine(glm::vec3 color) {
	vector<VertexFormat> vertices_bow2
	{
		VertexFormat(glm::vec3(0, 5, 0), color),
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0.1f, 0, 0), color),
		VertexFormat(glm::vec3(0.1f, 5, 0), color)
	};

	vector<unsigned short> indices_bow2 =
	{
		0,1,2,
		0,2,3
	};

	meshes["bow2"] = new Mesh("generated bow2");
	meshes["bow2"]->InitFromData(vertices_bow2, indices_bow2);
	meshes["bow2"]->SetDrawMode(GL_TRIANGLES);

	Mesh* bow2 = CreateMesh("bow2", vertices_bow2, indices_bow2);
}

// Function to create bow
void Tema1::createBow(glm::vec3 color) {
	// Arc circle for bow
	createBowArcCircle(color);
	// Line for bow
	createBowLine(color);
}

// Function to create shuriken star
void Tema1::createShuriken() {
	vector<VertexFormat> vertices_shuriken
	{
		VertexFormat(glm::vec3(0,0,0), glm::vec3(0, 0, 1)),

		VertexFormat(glm::vec3(-5,3,0), glm::vec3(0, 0, 1)),
		VertexFormat(glm::vec3(-1,4,0), glm::vec3(0, 0, 1)),

		VertexFormat(glm::vec3(5,-3,0), glm::vec3(0, 0, 1)),
		VertexFormat(glm::vec3(1,-4,0), glm::vec3(0, 0, 1)),

		VertexFormat(glm::vec3(-3,-5,0), glm::vec3(0, 0, 1)),
		VertexFormat(glm::vec3(-4,-1,0), glm::vec3(0, 0, 1)),

		VertexFormat(glm::vec3(3,5,0), glm::vec3(0, 0, 1)),
		VertexFormat(glm::vec3(4,1,0), glm::vec3(0, 0, 1)),
	};

	vector<unsigned short> indices_shuriken =
	{
		0,1,2,
		0,3,4,
		0,5,6,
		0,7,8
	};

	meshes["shuriken"] = new Mesh("generated shuriken");
	meshes["shuriken"]->InitFromData(vertices_shuriken, indices_shuriken);
	meshes["shuriken"]->SetDrawMode(GL_TRIANGLES);

	Mesh* shuriken = CreateMesh("shuriken", vertices_shuriken, indices_shuriken);
}

// --- Funtion to create balloon elipse
void Tema1::createBalloonElipse(glm::vec3 color) {
	vector<VertexFormat> vertices_balloon
	{
	};

	vector<unsigned short> indices_balloon =
	{
	};


	double x = 0, y = 0;
	int nr_vertices = 100;

	for (int i = 0; i < nr_vertices; i++) {

		double angle = i * 2 * M_PI / nr_vertices;
		x = x + (r1_balloon * cos(angle));
		y = y + (r2_balloon * sin(angle));

		if (y > y_max)
			y_max = y;

		vertices_balloon.push_back(VertexFormat(glm::vec3(0, 0, 0), color));

		vertices_balloon.push_back(VertexFormat(glm::vec3(x, y, 0), color));
	}

	for (int i = 0; i < 2 * nr_vertices - 2; i++) {
		indices_balloon.push_back(i);
		indices_balloon.push_back(i + 1);
		indices_balloon.push_back(i + 2);
	}

	if (color == glm::vec3(1, 0, 0)) {
		meshes["red_balloon_elipse"] = new Mesh("red_balloon_elipse");
		meshes["red_balloon_elipse"]->InitFromData(vertices_balloon, indices_balloon);
		meshes["red_balloon_elipse"]->SetDrawMode(GL_TRIANGLE_FAN);

		Mesh* balloon = CreateMesh("red_balloon_elipse", vertices_balloon, indices_balloon);
	}
	if (color == glm::vec3(1, 1, 0)) {
		meshes["yellow_balloon_elipse"] = new Mesh("yellow_balloon_elipse");
		meshes["yellow_balloon_elipse"]->InitFromData(vertices_balloon, indices_balloon);
		meshes["yellow_balloon_elipse"]->SetDrawMode(GL_TRIANGLE_FAN);

		Mesh* balloon = CreateMesh("yellow_balloon_elipse", vertices_balloon, indices_balloon);

	}
}

// --- Function to create balloon triangle
void Tema1::createBalloonTriangle(glm::vec3 color) {
	vector<VertexFormat> vertices_balloon2
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-2, -4, 0), color),
		VertexFormat(glm::vec3(2, -4, 0), color)
	};

	vector<unsigned short> indices_balloon2 =
	{
		0,1,2,
	};

	if (color == glm::vec3(1, 0, 0)) {
		meshes["red_balloon_triangle"] = new Mesh("red_balloon_triangle");
		meshes["red_balloon_triangle"]->InitFromData(vertices_balloon2, indices_balloon2);
		meshes["red_balloon_triangle"]->SetDrawMode(GL_TRIANGLES);
	}
	if (color == glm::vec3(1, 1, 0)) {
		meshes["yellow_balloon_triangle"] = new Mesh("yellow_balloon_triangle");
		meshes["yellow_balloon_triangle"]->InitFromData(vertices_balloon2, indices_balloon2);
		meshes["yellow_balloon_triangle"]->SetDrawMode(GL_TRIANGLES);
	}
}

// --- Function to create balloon line
void Tema1::createBalloonLine(glm::vec3 color)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-1.5f, -1.5f, 0), color),
		VertexFormat(glm::vec3(1.5f, -3.0f, 0), color),
		VertexFormat(glm::vec3(-1.5f, -4.5f, 0), color),
		VertexFormat(glm::vec3(1.5f, -6.0f, 0), color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2, 3, 4
	};

	if (color == glm::vec3(1, 0, 0)) {
		Mesh* my_mesh = new Mesh("red_balloon_line");
		my_mesh->InitFromData(vertices, indices);
		my_mesh->SetDrawMode(GL_LINE_STRIP);

		meshes["red_balloon_line"] = my_mesh;
	}

	if (color == glm::vec3(1, 1, 0)) {
		Mesh* mesh = new Mesh("yellow_balloon_line");
		mesh->InitFromData(vertices, indices);
		mesh->SetDrawMode(GL_LINE_STRIP);

		meshes["yellow_balloon_line"] = mesh;
	}
}

// Function to create balloon
void Tema1::createBalloon(glm::vec3 color) {
	// Balloon elipse
	createBalloonElipse(color);
	// Balloon triangle
	createBalloonTriangle(color);
	// Balloon line
	createBalloonLine(color);
}

// Function to power bar
void Tema1::createPowerBar(glm::vec3 color) {
	vector<VertexFormat> vertices_bar
	{
		VertexFormat(glm::vec3(0,1.5f,0), color),
		VertexFormat(glm::vec3(0,1,0), color),
		VertexFormat(glm::vec3(3,1,0), color),
		VertexFormat(glm::vec3(3,1.5f,0), color)
	};

	vector<unsigned short> indices_bar =
	{
		0,1,2,
		0,2,3,
	};

	meshes["power_bar"] = new Mesh("generated power bar");
	meshes["power_bar"]->InitFromData(vertices_bar, indices_bar);
	meshes["power_bar"]->SetDrawMode(GL_TRIANGLES);

	Mesh* power_bar = CreateMesh("power_bar", vertices_bar, indices_bar);
}

// Function to check collision with balloon
bool Tema1::collisionBalloon(int i, glm::vec3 color) {

	if (color == red_color) {
		float dx = arrow->arrowheadX - red_balloons[i]->translateX;
		float dy = arrow->arrowheadY - (red_balloons[i]->translateY + red_balloons[i]->scaleY * (y_max/2)); 
		float distance = sqrt(pow(dx, 2) + pow(dy, 2));

		if (distance < ((radius_balloon+1) * red_balloons[i]->scaleX)) {
			return true;
		}
		return false;
	}
	else {
		float dx = arrow->arrowheadX - yellow_balloons[i]->translateX;
		float dy = arrow->arrowheadY - (yellow_balloons[i]->translateY + yellow_balloons[i]->scaleY * (y_max / 2));
		float distance = sqrt(pow(dx, 2) + pow(dy, 2));

		if (distance < (radius_balloon * yellow_balloons[i]->scaleX)) {
			return true;
		}
		return false;
	}

}

// Function to check collision between shuriken and arrow
bool Tema1::collisionShurikenArrow(int i) {

	float dx = arrow->arrowheadX - shurikens[i]->translateX;
	float dy = arrow->arrowheadY - shurikens[i]->translateY;
		float distance = sqrt(pow(dx, 2) + pow(dy, 2));

		if (distance < ((radius_shuriken + 1) * shurikens[i]->scaleX)) {
			return true;
		}
		return false;
}

// Function to check collision between shuriken and bow
bool Tema1::collisionShurikenBow(int i) {

	float dx = bow->translateX - shurikens[i]->translateX;
	float dy = bow->translateY - shurikens[i]->translateY;
	float distance = sqrt(pow(dx, 2) + pow(dy, 2));

	if (distance < (radius_shuriken * shurikens[i]->scaleX) + (radius_bow * bow->scaleX)) {
		return true;
	}
	return false;
}


void Tema1::Init()
{
	cullFace = GL_BACK;
	polygonMode = GL_FILL;

	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// Starting game message
	{
		printf("--------------------------------------------------------------------------------\n");
		printf("	  BOW AND ARROW GAME      \n");
		printf("--------------------------------------------------------------------------------\n");
		printf("Instructions: Press 'W' and 'S' to move the bow upward and downward.\n");
		printf("              Move the mouse to set the direction for the arrow.\n");
		printf("              Hold the left button of the mouse to set the arrow speed.\n");
		printf("Tip #1: Hit the red balloons and the shurikens (+10points).\n");
		printf("Tip #2: Avoid the yellow balloons (-10points).\n");
		printf("Tip #3: You have 3 lives. When the shuriken hits the bow, you lose one.\n");
		printf("Good luck!\n");
		printf("--------------------------------------------------------------------------------\n");
	}

	// Create the arrow
	{
		createArrow(white_color);
	}

	// Initialize an arrow object
	{
		translateX = 10; translateY = 150;
		scaleX = 25; scaleY = 25;
		angularStep = 0;

		float centerX = scaleX * centerX_arrow + translateX;
		float centerY = scaleY * centerY_arrow + translateY;

		float arrowheadX = scaleX * arrowhead_X + translateX;
		float arrowheadY = scaleY * arrowhead_Y + translateY;

		arrow_distance = arrowheadX - centerX;

		save_arrowheadX = arrowheadX;
		save_arrowheadY = arrowheadY;

		arrow = new Arrow::Arrow(translateX, translateY, scaleX, scaleY, angularStep, centerX, centerY, arrowheadX, arrowheadY);
		arrow_speed = 100.0f;
	}

	// Create the bow
	{		
		createBow(white_color);
	}

	// Initialize a bow from 2 objects(bow = circle arc; bow2 = line)
	{
		translateX = 10; translateY = 212;
		scaleX = 25; scaleY = 25;
		angularStep = RADIANS(180.0f);

		float centerX = scaleX * centerX_arrow + translateX;
		float centerY = scaleY * centerY_arrow + 150;

		bow = new Bow::Bow1(translateX, translateY, scaleX, scaleY, angularStep, centerX, centerY);

		translateX = 10; translateY = 150;
		scaleX = 25; scaleY = 25;
		angularStep = 0;

		centerX = scaleX * centerX_arrow + translateX;
		centerY = scaleY * centerY_arrow + translateY;

		bow2 = new Bow::Bow2(translateX, translateY, scaleX, scaleY, angularStep, centerX, centerY);
	}

	// Create the shuriken
	{
		createShuriken();
	}

	// Initialize 3 shuriken objects and add them to a shurikens vector
	{
		translateX = 1500; translateY = 250;
		scaleX = 8; scaleY = 8;
		angularStep = 0;

		float centerX = scaleX * centerX_shuriken + translateX;
		float centerY = scaleY * centerY_shuriken + translateY;

		for (int i = 0; i < nr_shurikens; i++) {
			shurikens.push_back(new Shuriken::Shuriken(translateX, translateY, scaleX, scaleY, angularStep, centerX, centerY));
			translateX += 500;
			translateY = rand() % 700;
			collision_arrow_shuriken.push_back(false);
			collision_bow_shuriken.push_back(false);
		}
	}

	// Create the red balloon
	{	
		glm::vec3 color = glm::vec3(1, 0, 0);
		createBalloon(color);
	}

	// Create the yellow balloon
	{
		glm::vec3 color = glm::vec3(1, 1, 0);
		createBalloon(color);
	}

	// Initialize 3 red balloon and 3 yellow balloons objects and add them to a ballons vector
	{
		red_balloons = {};

		translateX = 950; translateY = 0;
		scaleX = 5; scaleY = 5;
		angularStep = 0;

		for (int i = 0; i < nr_red_balloons + nr_yellow_balloons; i++) {
			if (i % 2 == 0)
				red_balloons.push_back(new Balloon::Balloon(translateX, translateY, scaleX, scaleY, angularStep));
			else
				yellow_balloons.push_back(new Balloon::Balloon(translateX, translateY, scaleX, scaleY, angularStep));
			translateY -= 300;
			translateX = rand() % 900 + 300;

			collision_red.push_back(false);
		}

		for (int i = 0; i < nr_red_balloons; i++) {
			collision_red.push_back(false);
		}

		for (int i = 0; i < nr_yellow_balloons; i++) {
			collision_yellow.push_back(false);
		}

		//printf("%f %f \n", red_balloons[0]->translateX, red_balloons[0]->translateY);
	}

	// Create the power bar
	{
		createPowerBar(glm::vec3(1, 1, 1));
	}

	// Initialize power bar
	{
		translateX = 10; translateY = 0.05f;
		scaleX = 2; scaleY = 50;
		angularStep = 0;

		save_scaleX = scaleX;

		power_bar = new PowerBar::PowerBar(translateX, translateY, scaleX, scaleY, angularStep);
	}

	for (int i = 0; i < 3; i++) {
		new_level.push_back(true);
	}

}

Mesh* Tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Create the IBO and bind it
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	// Game actions
	if (lives > 0 && win == false) {
		glLineWidth(3);
		glPointSize(5);
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

		// clears the color buffer (using the previously set color) and depth buffer
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::ivec2 resolution = window->GetResolution();
		// sets the screen area where to draw
		glViewport(0, 0, resolution.x, resolution.y);


		// Draw arrow
		{
			modelMatrix = glm::mat3(1);

			for (int i = 0; i < nr_arrows; i++) {
				// Rotation movement for the arrow
				modelMatrix *= Transform2D::Translate(arrow->centerX, arrow->centerY);
				modelMatrix *= Transform2D::Rotate(arrow->angularStep);
				modelMatrix *= Transform2D::Translate(-(arrow->centerX), -(arrow->centerY));

				modelMatrix *= Transform2D::Translate(arrow->translateX, arrow->translateY);
				modelMatrix *= Transform2D::Scale(arrow->scaleX, arrow->scaleY);

				RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);

				// Action when you hold the mouse button
				if (hold_mouse) {
					rotate_arrow = false;

					// Verify if the arrow speed reaches the limit
					if (arrow_speed < 1000) {
						arrow_speed += 20; // update the arrow speed
						power_bar->scaleX += 60 * deltaTimeSeconds; // increase the power bar
					}
					// update the power bar
					{
						modelMatrix = glm::mat3(1);
						modelMatrix *= Transform2D::Translate(power_bar->translateX, power_bar->translateY);
						modelMatrix *= Transform2D::Scale(power_bar->scaleX, power_bar->scaleY);

						RenderMesh2D(meshes["power_bar"], shaders["VertexColor"], modelMatrix);
					}

				}

				// If the arrow is flying
				if (hold_mouse == false && rotate_arrow == false) {
					arrow->translateX += deltaTimeSeconds * arrow_speed; // update the arrow position

					flying = true;
					arrow_distance += deltaTimeSeconds * arrow_speed; // update the arrow distance

					// Modify arrowhead positions
					arrow->arrowheadX = arrow->centerX + arrow_distance * cos(arrow->angularStep); 
					arrow->arrowheadY = arrow->centerY + arrow_distance * sin(arrow->angularStep);

					// If the arrow reaches the distance limit
					if (arrow->translateX > 1500) {
						flying = false;
						arrow->translateX = 10; // return the arrow to its initial position

						arrow_distance = arrow->centerX;

						arrow_speed = 100.0f; // set the arrow speed to its initial value
						rotate_arrow = true; // the arrow can be rotated

						power_bar->scaleX = save_scaleX; // set the scale vector for the power bar to its initial value

						// update the power bar
						{
							modelMatrix = glm::mat3(1);
							modelMatrix *= Transform2D::Translate(power_bar->translateX, power_bar->translateY);
							modelMatrix *= Transform2D::Scale(power_bar->scaleX, power_bar->scaleY);

							RenderMesh2D(meshes["power_bar"], shaders["VertexColor"], modelMatrix);
						}
					}
				}

			}

		}

		// Draw bow
		{

			modelMatrix = glm::mat3(1);

			// Rotation movement for the bow
			modelMatrix *= Transform2D::Translate(bow->centerX, bow->centerY);
			modelMatrix *= Transform2D::Rotate(arrow->angularStep);
			modelMatrix *= Transform2D::Translate(-(bow->centerX), -(bow->centerY));

			modelMatrix *= Transform2D::Translate(bow->translateX, bow->translateY);
			modelMatrix *= Transform2D::Scale(bow->scaleX, bow->scaleY);
			modelMatrix *= Transform2D::Rotate(bow->angularStep);

			RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

			modelMatrix = glm::mat3(1);

			// Rotation movement for the bow
			modelMatrix *= Transform2D::Translate(bow2->centerX, bow2->centerY);
			modelMatrix *= Transform2D::Rotate(arrow->angularStep);
			modelMatrix *= Transform2D::Translate(-(bow2->centerX), -(bow2->centerY));

			modelMatrix *= Transform2D::Translate(bow2->translateX, bow2->translateY);
			modelMatrix *= Transform2D::Scale(bow2->scaleX, bow2->scaleY);
			RenderMesh2D(meshes["bow2"], shaders["VertexColor"], modelMatrix);
		}

		// Draw shuriken
		{

			for (int i = 0; i < nr_shurikens; i++) {
				shurikens[i]->translateX -= deltaTimeSeconds * shuriken_speed;

				// If the shuriken reaches the distance limit or it s destroyed
				if (shurikens[i]->translateX < 0 || shurikens[i]->scaleX < 0) {
					// Respawn to its initial position
					shurikens[i]->translateX = 1500;
					shurikens[i]->translateY = rand() % 700;

					// Set scaleX and scaleY to their initial values
					shurikens[i]->scaleX = 8;
					shurikens[i]->scaleY = 8;

					collision_arrow_shuriken[i] = false;
					collision_bow_shuriken[i] = false;
					addToScore = 0;
					decreaseLives = 0;
				}

				modelMatrix = glm::mat3(1);

				// Rotation movement around the center	
				{
					shurikens[i]->centerX = shurikens[i]->scaleX * centerX_shuriken + shurikens[i]->translateX;
					shurikens[i]->centerY = shurikens[i]->scaleY * centerY_shuriken + shurikens[i]->translateY;

					shurikens[i]->angularStep += deltaTimeSeconds;

					modelMatrix *= Transform2D::Translate(shurikens[i]->centerX, shurikens[i]->centerY);
					modelMatrix *= Transform2D::Rotate(shurikens[i]->angularStep);
					modelMatrix *= Transform2D::Translate(-(shurikens[i]->centerX), -(shurikens[i]->centerY));
				}

				// Movement for the shuriken
				{
					modelMatrix *= Transform2D::Translate(shurikens[i]->translateX, shurikens[i]->translateY);
					modelMatrix *= Transform2D::Scale(shurikens[i]->scaleX, shurikens[i]->scaleY);
				}

				RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);

				// If the shuriken collides with the bow
				if (collisionShurikenBow(i) == true) {
					decreaseLives++;

					// Decrease the number of lives
					if (decreaseLives == 1) {
						lives -= 1;
						printf("Lives left: %d\n", lives);
					}

					// Return the arrow to its initial position
					arrow->translateX = 10;
					arrow_distance = arrow->centerX;
					arrow_speed = 100.0f; // set the arrow speed to its initial value

					flying = false;
					rotate_arrow = true;
					collision_bow_shuriken[i] = true;

					power_bar->scaleX = save_scaleX; // set the scale vector for the power bar to its initial value

					// update the power bar
					{
						modelMatrix = glm::mat3(1);
						modelMatrix *= Transform2D::Translate(power_bar->translateX, power_bar->translateY);
						modelMatrix *= Transform2D::Scale(power_bar->scaleX, power_bar->scaleY);

						RenderMesh2D(meshes["power_bar"], shaders["VertexColor"], modelMatrix);
					}
				}
				// If the shuriken collides with the arrow instead
				else {
					if (collisionShurikenArrow(i) == true) {
						addToScore++;
						// Add 10 points to the score
						if (addToScore == 1) {
							score += 10;
							printf("Score: %d\n", score);
						}

						arrow->translateX = 10;
						arrow_distance = arrow->centerX;
						arrow_speed = 100.0f; // set the arrow speed to its initial value

						flying = false;
						rotate_arrow = true;
						collision_arrow_shuriken[i] = true;

						power_bar->scaleX = save_scaleX; // set the scale vector for the power bar to its initial value
						// update the power bar
						{
							modelMatrix = glm::mat3(1);
							modelMatrix *= Transform2D::Translate(power_bar->translateX, power_bar->translateY);
							modelMatrix *= Transform2D::Scale(power_bar->scaleX, power_bar->scaleY);

							RenderMesh2D(meshes["power_bar"], shaders["VertexColor"], modelMatrix);
						}
					}

					// Destroying shuriken animation
					if (collision_arrow_shuriken[i] == true) {

						if (shurikens[i]->scaleX >= 0) {
							shurikens[i]->scaleX -= 10 * deltaTimeSeconds;
						}

						if (shurikens[i]->scaleY >= 0) {
							shurikens[i]->scaleY -= 10 * deltaTimeSeconds;
						}
					}
				}
				

				
			}

			if (lives == 0) {
				printf("Game Over! Score: %d Press R to restart.\n", score);
				printf("----------------------------------------\n");
			}
		}

		// Draw red balloon
		{
			for (int i = 0; i < nr_red_balloons; i++) {
				red_balloons[i]->translateY += deltaTimeSeconds * balloon_speed;
				// If the ballon reaches the distance limit or it s destroyed
				if (red_balloons[i]->translateY > 900 || red_balloons[i]->scaleY < 0) {
					// Respawn the ballon to a random position
					red_balloons[i]->translateY = 0;
					red_balloons[i]->translateX = rand() % 900 + 300;

					// Set scaleX and scaleY to their initial values
					red_balloons[i]->scaleX = 5;
					red_balloons[i]->scaleY = 5;

					collision_red[i] = false;
					addToScore = 0;
				}

				// Movement for the balloon elipse
				{
					modelMatrix = glm::mat3(1);
					modelMatrix *= Transform2D::Translate(red_balloons[i]->translateX, red_balloons[i]->translateY);
					modelMatrix *= Transform2D::Scale(red_balloons[i]->scaleX, red_balloons[i]->scaleY);
					RenderMesh2D(meshes["red_balloon_elipse"], shaders["VertexColor"], modelMatrix);
				}

				// Movement for the balloon triangle
				{
					modelMatrix = glm::mat3(1);
					modelMatrix *= Transform2D::Translate(red_balloons[i]->translateX, red_balloons[i]->translateY + 10);
					modelMatrix *= Transform2D::Scale(red_balloons[i]->scaleX, red_balloons[i]->scaleY);
					RenderMesh2D(meshes["red_balloon_triangle"], shaders["VertexColor"], modelMatrix);
				}

				// Movement for the balloon line
				{
					modelMatrix = glm::mat3(1);
					modelMatrix *= Transform2D::Translate(red_balloons[i]->translateX, red_balloons[i]->translateY);
					modelMatrix *= Transform2D::Scale(red_balloons[i]->scaleX, red_balloons[i]->scaleY);
					RenderMesh2D(meshes["red_balloon_line"], shaders["VertexColor"], modelMatrix);
				}

				// If the ballon collides with an arrow
				if (collisionBalloon(i, red_color) == true) {
					addToScore++;
					// Add 10 points to score
					if (addToScore == 1) {
						score += 10;
						printf("Score: %d\n", score);
					}

					// Return the arrow to its initial position
					arrow->translateX = 10;
					arrow_distance = arrow->centerX;
					arrow_speed = 100.0f; // set the arrow speed to its initial value

					flying = false;
					rotate_arrow = true;
					collision_red[i] = true;

					power_bar->scaleX = save_scaleX; // set the scale vector for the power bar to its initial value
					// update the power bar
					{
						modelMatrix = glm::mat3(1);
						modelMatrix *= Transform2D::Translate(power_bar->translateX, power_bar->translateY);
						modelMatrix *= Transform2D::Scale(power_bar->scaleX, power_bar->scaleY);

						RenderMesh2D(meshes["power_bar"], shaders["VertexColor"], modelMatrix);
					}
				}

				// Destroying balloon animation 
				if (collision_red[i] == true) {

					if (red_balloons[i]->scaleX >= 0) {
						red_balloons[i]->scaleX -= 10 * deltaTimeSeconds;
					}

					if (red_balloons[i]->scaleY >= 0) {
						red_balloons[i]->scaleY -= 10 * deltaTimeSeconds;
					}
				}
			}
		}

		// Draw yellow balloon
		{
			for (int i = 0; i < nr_yellow_balloons; i++) {
				yellow_balloons[i]->translateY += deltaTimeSeconds * balloon_speed;
				// If the ballon reaches the distance limit or it s destroyed
				if (yellow_balloons[i]->translateY > 900 || yellow_balloons[i]->scaleY < 0) {
					// Respawn the ballon to a random position
					yellow_balloons[i]->translateY = 0;
					yellow_balloons[i]->translateX = rand() % 900 + 300;

					// Set scaleX and scaleY to their initial values
					yellow_balloons[i]->scaleX = 5;
					yellow_balloons[i]->scaleY = 5;

					collision_yellow[i] = false;
					addToScore = 0;
				}

				// Movement for the balloon elipse
				{
					modelMatrix = glm::mat3(1);
					modelMatrix *= Transform2D::Translate(yellow_balloons[i]->translateX, yellow_balloons[i]->translateY);
					modelMatrix *= Transform2D::Scale(yellow_balloons[i]->scaleX, yellow_balloons[i]->scaleY);
					RenderMesh2D(meshes["yellow_balloon_elipse"], shaders["VertexColor"], modelMatrix);
				}

				// Movement for the balloon triangle
				{
					modelMatrix = glm::mat3(1);
					modelMatrix *= Transform2D::Translate(yellow_balloons[i]->translateX, yellow_balloons[i]->translateY + 10);
					modelMatrix *= Transform2D::Scale(yellow_balloons[i]->scaleX, yellow_balloons[i]->scaleY);
					RenderMesh2D(meshes["yellow_balloon_triangle"], shaders["VertexColor"], modelMatrix);
				}

				// Movement for the balloon line
				{
					modelMatrix = glm::mat3(1);
					modelMatrix *= Transform2D::Translate(yellow_balloons[i]->translateX, yellow_balloons[i]->translateY);
					modelMatrix *= Transform2D::Scale(yellow_balloons[i]->scaleX, yellow_balloons[i]->scaleY);
					RenderMesh2D(meshes["yellow_balloon_line"], shaders["VertexColor"], modelMatrix);
				}

				// If the ballon collides with an arrow
				if (collisionBalloon(i, yellow_color) == true) {

					addToScore++;
					// Substract 10 points from the score
					if (addToScore == 1) {
						score -= 10;
						printf("Score: %d\n", score);
					}

					// Return the arrow to its initial position
					arrow->translateX = 10;
					arrow_distance = arrow->centerX;
					arrow_speed = 100.0f; // set the arrow speed to its initial value

					flying = false;
					rotate_arrow = true;
					collision_yellow[i] = true;

					power_bar->scaleX = save_scaleX; // set the scale vector for the power bar to its initial value
					// update the power bar
					{
						modelMatrix = glm::mat3(1);
						modelMatrix *= Transform2D::Translate(power_bar->translateX, power_bar->translateY);
						modelMatrix *= Transform2D::Scale(power_bar->scaleX, power_bar->scaleY);

						RenderMesh2D(meshes["power_bar"], shaders["VertexColor"], modelMatrix);
					}
				}

				// Destroying balloon animation 
				if (collision_yellow[i] == true) {
					if (yellow_balloons[i]->scaleX >= 0) {
						yellow_balloons[i]->scaleX -= 10 * deltaTimeSeconds;
					}

					if (yellow_balloons[i]->scaleY >= 0) {
						yellow_balloons[i]->scaleY -= 10 * deltaTimeSeconds;
					}
				}
			}
		}

		// Draw power bar
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(power_bar->translateX, power_bar->translateY);
			modelMatrix *= Transform2D::Scale(power_bar->scaleX, power_bar->scaleY);

			RenderMesh2D(meshes["power_bar"], shaders["VertexColor"], modelMatrix);
		}
		
		// Bonus: Adding difficulty levels
		{
			if (score == 50 && new_level[0]) {
				increaseLevel += 1;
				if (increaseLevel == 1) {
					printf("Level 1 reached\n");
					new_level[0] = false;
					balloon_speed += 50;
					shuriken_speed += 50;
				}
			}

			if (score == 60) {
				increaseLevel = 0;
			}

			if (score == 100 && new_level[1]) {
				increaseLevel += 1;
				if (increaseLevel == 1) {
					printf("Level 2 reached\n");
					new_level[1] = false;
					balloon_speed += 50;
					shuriken_speed += 50;
				}
			}

			if (score == 110) {
				increaseLevel = 0;
			}

			if (score == 150 && new_level[2]) {
				increaseLevel += 1;
				if (increaseLevel == 1) {
					printf("Congrats! You win! Score: %d\n", score);
					printf("--------------------------------------------------------------------------------\n");
					new_level[2] = false;
					win = true;
				}
			}
		}
	
	}
	else {
	// Game over action
		glLineWidth(3);
		glPointSize(5);
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

		// clears the color buffer (using the previously set color) and depth buffer
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::ivec2 resolution = window->GetResolution();
		// sets the screen area where to draw
		glViewport(0, 0, resolution.x, resolution.y);

		// If 'R' is pressed -> restart = true
		if (restart) {
			shuriken_speed = 200;
			balloon_speed = 100;
			increaseLevel = 0;
			lives = 3;
			score = 0;
			win = false;
			for (int i = 0; i < 3; i++) {
				new_level[i] = true;
			}
			printf("New Game started. Good luck!\n");
			printf("--------------------------------------------------------------------------------\n");
		}
	}
}

void Tema1::FrameEnd()
{
	DrawCoordinatSystem();
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	// Translate bow upward
	if (window->KeyHold(GLFW_KEY_W)) {
		float speed = 150.0f;
		if (bow->translateY < 585) {
			bow->translateY += deltaTime * speed;
			bow2->translateY += deltaTime * speed;

			bow->centerY += deltaTime * speed;
			bow2->centerY += deltaTime * speed;

			// Also translate the arrow center
			arrow->translateY += deltaTime * speed;
			arrow->centerY += deltaTime * speed;
		}
	}
	// Translate bow downward
	if (window->KeyHold(GLFW_KEY_S)) {
		float speed = 100.0f;
		if (bow->translateY > 135) {
			bow->translateY -= deltaTime * speed;
			bow2->translateY -= deltaTime * speed;

			bow->centerY -= deltaTime * speed;
			bow2->centerY -= deltaTime * speed;

			// Also translate the arrow center
			arrow->translateY -= deltaTime * speed;
			arrow->centerY -= deltaTime * speed;
		}
	}
}

void Tema1::OnKeyPress(int key, int mods)
{
	// If 'R' is pressed -> restart
	if (key == GLFW_KEY_R)
	{
		restart = true;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	if (key == GLFW_KEY_R)
	{
		restart = false;
	}
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// If the arrow can be rotated(if not flying)
	if (rotate_arrow == true) {
		// Rotate the arrow
		arrow->centerX = arrow ->scaleX * centerX_arrow + arrow ->translateX;
		arrow->centerY = arrow ->scaleY * centerY_arrow + arrow->translateY;

		// Rotate the bow
		bow->centerX = bow->scaleX * centerX_arrow + arrow->translateX;
		bow->centerY = bow->scaleY * centerY_arrow + arrow->translateY;

		bow2->centerX = bow2->scaleX * centerX_arrow + arrow->translateX;
		bow2->centerY = bow2->scaleY * centerY_arrow + arrow->translateY;

		// Modify the angle
		arrow->angularStep = atan((bow->translateY - window->GetResolution().y + mouseY) / (bow->translateX - mouseX));

		// Update arrowhead position
		arrow->arrowheadX = arrow->centerX + arrow_distance * cos(arrow->angularStep);
		arrow->arrowheadY = arrow->centerY + arrow_distance * sin(arrow->angularStep);
	}		
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// If mouse button is pressed and the arrow is not flying
	if(!flying)
		hold_mouse = true;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	rotate_arrow = false;
	hold_mouse = false;
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
