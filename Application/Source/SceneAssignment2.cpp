#include "SceneAssignment2.h"
#include "GL\glew.h"



// GLM Headers
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_inverse.hpp>

//Include GLFW
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "Application.h"
#include "MeshBuilder.h"
#include "KeyboardController.h"
#include "LoadTGA.h"

#include "MouseController.h"
#include <iostream>



SceneAssignment2::SceneAssignment2()
{
}

SceneAssignment2::~SceneAssignment2()
{
}

void SceneAssignment2::Init()
{
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Load the shader programs

	glUseProgram(m_programID);

	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");

	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
	m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");

	m_parameters[U_LIGHT5_TYPE] = glGetUniformLocation(m_programID, "lights[5].type");
	m_parameters[U_LIGHT5_POSITION] = glGetUniformLocation(m_programID, "lights[5].position_cameraspace");
	m_parameters[U_LIGHT5_COLOR] = glGetUniformLocation(m_programID, "lights[5].color");
	m_parameters[U_LIGHT5_POWER] = glGetUniformLocation(m_programID, "lights[5].power");
	m_parameters[U_LIGHT5_KC] = glGetUniformLocation(m_programID, "lights[5].kC");
	m_parameters[U_LIGHT5_KL] = glGetUniformLocation(m_programID, "lights[5].kL");
	m_parameters[U_LIGHT5_KQ] = glGetUniformLocation(m_programID, "lights[5].kQ");
	m_parameters[U_LIGHT5_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[5].spotDirection");
	m_parameters[U_LIGHT5_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[5].cosCutoff");
	m_parameters[U_LIGHT5_COSINNER] = glGetUniformLocation(m_programID, "lights[5].cosInner");
	m_parameters[U_LIGHT5_EXPONENT] = glGetUniformLocation(m_programID, "lights[5].exponent");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);

	// Initialise camera properties
	camera.Init(glm::vec3(10,5,0), glm::vec3(0,5,0),glm::vec3(0,1,0));
	 
	// Init VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Light", Color(1.f, 1.f, 1.f), 0.3,10,10);

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//up.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//down.tga");
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//back.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//front.tga");
	//Collider checker
	meshList[GEO_COLLIDER] = MeshBuilder::GenerateCube("Collider", Color(1.f, 1.f, 1.f), 1);
	
	//ROAD
	meshList[GEO_ROAD] = MeshBuilder::GenerateQuad("road", Color(1.f, 1.f, 1.f), 100.f);
	meshList[GEO_ROAD]->textureID = LoadTGA("Image//road.tga");

	meshList[GEO_PLANE] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 100.f);
	meshList[GEO_PLANE]->textureID = LoadTGA("Image//Plane.tga");

	meshList[GEO_ROADEND] = MeshBuilder::GenerateQuad("road", Color(1.f, 1.f, 1.f), 100.f);
	meshList[GEO_ROADEND]->textureID = LoadTGA("Image//roadend.tga");
	//Man
	meshList[GEO_PLAYER] = MeshBuilder::GenerateOBJ("Human", "OBJ//guy_obj.OBJ");
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//guy_obj.tga");
	//tree
	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("Human", "OBJ//tree.obj");
	meshList[GEO_TREE]->textureID = LoadTGA("Image//tree.tga");

	//car
	meshList[GEO_CAR] = MeshBuilder::GenerateOBJ("Car", "OBJ//car.obj");
	meshList[GEO_CAR]->textureID = LoadTGA("Image//car.tga");
	//heli
	meshList[GEO_HELI] = MeshBuilder::GenerateOBJ("helicopter", "OBJ//helicopter.obj");
	meshList[GEO_HELI]->textureID = LoadTGA("Image//helicopter.tga");

	meshList[GEO_LAMP] = MeshBuilder::GenerateOBJ("Human", "OBJ//lamp.obj");
	meshList[GEO_LAMP]->textureID = LoadTGA("Image//lamp.tga");

	meshList[GEO_WHEEL] = MeshBuilder::GenerateOBJ("Human", "OBJ//wheel.obj");
	meshList[GEO_WHEEL]->textureID = LoadTGA("Image//wheel.tga");

	meshList[GEO_BARRIER] = MeshBuilder::GenerateOBJ("Human", "OBJ//Barrier.obj");
	meshList[GEO_BARRIER]->textureID = LoadTGA("Image//Barrier.tga");

	meshList[GEO_VAN] = MeshBuilder::GenerateOBJ("van", "OBJ//van.obj");
	meshList[GEO_VAN]->textureID = LoadTGA("Image//van.tga");

	meshList[GEO_RUSTY] = MeshBuilder::GenerateOBJ("van", "OBJ//rusty.obj");
	meshList[GEO_RUSTY]->textureID = LoadTGA("Image//rusty.tga");

	meshList[GEO_BUTTON] = MeshBuilder::GenerateOBJ("van", "OBJ//button.obj");
	meshList[GEO_BUTTON]->textureID = LoadTGA("Image//button.tga");

	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("van", "OBJ//door.obj");
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//door.tga");

	meshList[GEO_WALL] = MeshBuilder::GenerateQuad("van", Color(1.f, 1.f, 1.f), 1);
	meshList[GEO_WALL]->textureID = LoadTGA("Image//wall.tga");

	meshList[GEO_FLOOR] = MeshBuilder::GenerateQuad("van", Color(1.f, 1.f, 1.f), 10);
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//floor.tga");

	meshList[GEO_CRATE] = MeshBuilder::GenerateOBJ("van", "OBJ//crate.obj");
	meshList[GEO_CRATE]->textureID = LoadTGA("Image//crate.tga");

	meshList[GEO_C4] = MeshBuilder::GenerateOBJ("van", "OBJ//c4.obj");
	meshList[GEO_C4]->textureID = LoadTGA("Image//c4.tga");

	// 16 x 16 is the number of columns and rows for the text​
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_WIN] = MeshBuilder::GenerateQuad("WIN", Color(1.f, 1.f, 1.f), 10);
	meshList[GEO_WIN]->textureID = LoadTGA("Image//win.tga");

	meshList[GEO_LOSE] = MeshBuilder::GenerateQuad("WIN", Color(1.f, 1.f, 1.f), 10);
	meshList[GEO_LOSE]->textureID = LoadTGA("Image//lose.tga");

	meshList[GEO_CELLING] = MeshBuilder::GenerateQuad("WIN", Color(1.f, 1.f, 1.f), 10);
	meshList[GEO_CELLING]->textureID = LoadTGA("Image//celling.tga");

	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);


	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	//light street
	light[0].position = glm::vec3(1.5, 1, 1.5);
	light[0].color.Set(1, 1, 1);
	light[0].type = Light::LIGHT_POINT;
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = 45.f;
	light[0].cosInner = 30.f;
	light[0].exponent = 3.f;
	light[0].spotDirection = glm::vec3(0.f, 1.f,0);

	//light heli
	light[1].position = glm::vec3(-1.1 ,15 ,2.25);
	light[1].color.Set(1, 1, 0);
	light[1].type = Light::LIGHT_SPOT;
	light[1].power = 1;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = 10.f;
	light[1].cosInner = 30.f;
	light[1].exponent = 3.f;
	light[1].spotDirection = glm::vec3(0.f, 1.f, 1.f);

	//moon
	light[2].position = glm::vec3(0, 15, 0);
	light[2].color.Set(1, 1, 1);
	light[2].type = Light::LIGHT_DIRECTIONAL;
	light[2].power = 0.1f;
	light[2].kC = 0.3f;
	light[2].kL = 0.01f;
	light[2].kQ = 0.001f;
	light[2].cosCutoff = 10.f;
	light[2].cosInner = 30.f;
	light[2].exponent = 3.f;
	light[2].spotDirection = glm::vec3(0.f, 1.f, 0);

	light[3].position = glm::vec3(-4.5, 1, -5.5);
	light[3].color.Set(0, 0, 1);
	light[3].type = Light::LIGHT_POINT;
	light[3].power = 1;
	light[3].kC = 1.f;
	light[3].kL = 0.01f;
	light[3].kQ = 0.001f;
	light[3].cosCutoff = 10.f;
	light[3].cosInner = 30.f;
	light[3].exponent = 3.f;
	light[3].spotDirection = glm::vec3(0.f, 1.f, 1.f);

	light[4].position = glm::vec3(0, 2, 0);
	light[4].color.Set(1, 1, 1);
	light[4].type = Light::LIGHT_POINT;
	light[4].power = 0.3f;
	light[4].kC = 1.f;
	light[4].kL = 0.01f;
	light[4].kQ = 0.001f;
	light[4].cosCutoff = 10.f;
	light[4].cosInner = 30.f;
	light[4].exponent = 3.f;
	light[4].spotDirection = glm::vec3(0.f, 1.f, 1.f);

	light[5].position = glm::vec3(-4.2, 0.5, -4.2);
	light[5].color.Set(1, 0, 0);
	light[5].type = Light::LIGHT_POINT;
	light[5].power = 0.1;
	light[5].kC = 1.f;
	light[5].kL = 0.01f;
	light[5].kQ = 0.001f;
	light[5].cosCutoff = 10.f;
	light[5].cosInner = 30.f;
	light[5].exponent = 3.f;
	light[5].spotDirection = glm::vec3(0.f, 1.f, 1.f);

	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], cosf(glm::radians<float>(light[0].cosCutoff)));
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], cosf(glm::radians<float>(light[0].cosInner)));
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);


	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], cosf(glm::radians<float>(light[1].cosCutoff)));
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], cosf(glm::radians<float>(light[1].cosInner)));
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &light[2].color.r);
	glUniform1i(m_parameters[U_LIGHT2_TYPE], light[2].type);
	glUniform1f(m_parameters[U_LIGHT2_POWER], light[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], light[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], light[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], light[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], cosf(glm::radians<float>(light[2].cosCutoff)));
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], cosf(glm::radians<float>(light[2].cosInner)));
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], light[2].exponent);

	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
	glUniform1i(m_parameters[U_LIGHT3_TYPE], light[3].type);
	glUniform1f(m_parameters[U_LIGHT3_POWER], light[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], light[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], light[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], light[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], cosf(glm::radians<float>(light[3].cosCutoff)));
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], cosf(glm::radians<float>(light[3].cosInner)));
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[3].exponent);

	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &light[4].color.r);
	glUniform1i(m_parameters[U_LIGHT4_TYPE], light[4].type);
	glUniform1f(m_parameters[U_LIGHT4_POWER], light[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], light[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], light[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], light[4].kQ);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], cosf(glm::radians<float>(light[4].cosCutoff)));
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], cosf(glm::radians<float>(light[4].cosInner)));
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], light[4].exponent);

	glUniform3fv(m_parameters[U_LIGHT5_COLOR], 1, &light[5].color.r);
	glUniform1i(m_parameters[U_LIGHT5_TYPE], light[5].type);
	glUniform1f(m_parameters[U_LIGHT5_POWER], light[5].power);
	glUniform1f(m_parameters[U_LIGHT5_KC], light[5].kC);
	glUniform1f(m_parameters[U_LIGHT5_KL], light[5].kL);
	glUniform1f(m_parameters[U_LIGHT5_KQ], light[5].kQ);
	glUniform1f(m_parameters[U_LIGHT5_COSCUTOFF], cosf(glm::radians<float>(light[5].cosCutoff)));
	glUniform1f(m_parameters[U_LIGHT5_COSINNER], cosf(glm::radians<float>(light[5].cosInner)));
	glUniform1f(m_parameters[U_LIGHT5_EXPONENT], light[5].exponent);



	glUniform1i(m_parameters[U_NUMLIGHTS], NUM_LIGHTS);
	//collider number
	collider = new gameObject[numofcol];
	camera.playerPosPtr = &playerPosition;

	enableLight = true;

	playerPosition = glm::vec3(0,0,0);

	//material init
	meshList[GEO_ROAD]->material.kAmbient.Set(0,0,0);
	meshList[GEO_ROAD]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_ROAD]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_BARRIER]->material.kAmbient.Set(0,0,0);
	meshList[GEO_BARRIER]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_BARRIER]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_ROADEND]->material.kAmbient.Set(0,0,0);
	meshList[GEO_ROADEND]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_ROADEND]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_TREE]->material.kAmbient.Set(0,0,0);
	meshList[GEO_TREE]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_TREE]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_CAR]->material.kAmbient.Set(0,0,0);
	meshList[GEO_CAR]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_CAR]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_HELI]->material.kAmbient.Set(0,0,0);
	meshList[GEO_HELI]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_HELI]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_LAMP]->material.kAmbient.Set(0,0,0);
	meshList[GEO_LAMP]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_LAMP]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_WHEEL]->material.kAmbient.Set(0,0,0);
	meshList[GEO_WHEEL]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_WHEEL]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_PLANE]->material.kAmbient.Set(0,0,0);
	meshList[GEO_PLANE]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_PLANE]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_PLAYER]->material.kAmbient.Set(0,0,0);
	meshList[GEO_PLAYER]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_PLAYER]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_VAN]->material.kAmbient.Set(0,0,0);
	meshList[GEO_VAN]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_VAN]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_RUSTY]->material.kAmbient.Set(0,0,0);
	meshList[GEO_RUSTY]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_RUSTY]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_BUTTON]->material.kAmbient.Set(0, 0, 0);
	meshList[GEO_BUTTON]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_BUTTON]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_DOOR]->material.kAmbient.Set(0, 0, 0);
	meshList[GEO_DOOR]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_DOOR]->material.kSpecular.Set(0, 0, 0);

	meshList[GEO_WALL]->material.kAmbient.Set(0, 0, 0);
	meshList[GEO_WALL]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_WALL]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_FLOOR]->material.kAmbient.Set(0, 0, 0);
	meshList[GEO_FLOOR]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_FLOOR]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_CRATE]->material.kAmbient.Set(0, 0, 0);
	meshList[GEO_CRATE]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_CRATE]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_C4]->material.kAmbient.Set(0, 0, 0);
	meshList[GEO_C4]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_C4]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_CELLING]->material.kAmbient.Set(0, 0, 0);
	meshList[GEO_CELLING]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_CELLING]->material.kSpecular.Set(0, 0, 0);


	doorMove = 0;
}

void SceneAssignment2::Update(double dt)
{
	HandleKeyPress();
	
	if (KeyboardController::GetInstance()->IsKeyDown('I'))
		light[1].position.z -= static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('K'))
		light[1].position.z += static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('J'))
		light[1].position.x -= static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('L'))
		light[1].position.x += static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('O'))
		light[1].position.y -= static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('P'))
		light[1].position.y += static_cast<float>(dt) * 5.f;
	
		
	//player controller *to change
	if (doorOpen == false)
	{
		//forward
		if (KeyboardController::GetInstance()->IsKeyDown('W'))
		{
			playerPosition += camera.view * speed * static_cast<float>(dt);
			playerPosition.y -= camera.view.y * speed * static_cast<float>(dt);
		}
		//backward
		if (KeyboardController::GetInstance()->IsKeyDown('S'))
		{
			playerPosition += -camera.view * speed * static_cast<float>(dt);
			playerPosition.y += camera.view.y * speed * static_cast<float>(dt);
		}
		//left
		if (KeyboardController::GetInstance()->IsKeyDown('A'))
		{
			playerPosition += -camera.right * speed * static_cast<float>(dt);
			playerPosition.y += -camera.right.y * speed * static_cast<float>(dt);
		}
		//right
		if (KeyboardController::GetInstance()->IsKeyDown('D'))
		{
			playerPosition += camera.right * speed * static_cast<float>(dt);
			playerPosition.y -= -camera.right.y * speed * static_cast<float>(dt);
		}
	}
	

	//player rotation
	playerRotation = glm::degrees(
		atan2(camera.yawView.x, camera.yawView.z)
	);
	camera.Update(dt);

	//collision check
	for (int i = 0; i < numofcol; i++)
	{
		float d1 = fabs(playerPosition.z - collider[i].pos.z);
		float d2 = fabs(playerPosition.x - collider[i].pos.x);
		//scene 1
		if (scene == 1)
		{
			//door
			if (i == 7)
			{
				//for objective
				if (d1 <= (collider[i].scale.z / 2) && d2 <= (collider[i].scale.x / 2))
				{
					render_button = true;
					if (KeyboardController::GetInstance()->IsKeyPressed('E'))
					{
						doorOpen = true;
					}
					
				}
				else
				{
					render_button = false;
				}

			}
			//lamp
			else if (i == 8)
			{
				//lamp on off
				if (d1 <= (collider[i].scale.z / 2) && d2 <= (collider[i].scale.x / 2))
				{
					render_lamptxt = true;
					if (KeyboardController::GetInstance()->IsKeyPressed('E'))
					{
						if (light[0].power == 1)
						{
							light[0].power = 0;
						}
						else
						{
							light[0].power = 1;
						}
						glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
					}
					

				}
				else
				{
					render_lamptxt = false;
				}
			}
			else if (i >= 0 && i < 10)
			{
				//for collider
				if (d1 <= (collider[i].scale.z / 2) && d2 <= (collider[i].scale.x / 2))
				{

					playerPosition = glm::vec3(0,0,0);
				}
			}
		}
		else
		{
			if (i >= 10 && i < numofcol)
			{
				if (i == 25)
				{
					if (d1 <= (collider[i].scale.z / 2) && d2 <= (collider[i].scale.x / 2))
					{
						bomb_diffusable = true;
						//difuse bomb
						if (KeyboardController::GetInstance()->IsKeyPressed('E'))
						{
							bomb_diffused = true;
						}

					}
					else
					{
						bomb_diffusable = false;
					}
				}
				else
				{
					//for collider
					if (d1 <= (collider[i].scale.z / 2) && d2 <= (collider[i].scale.x / 2))
					{

						playerPosition = glm::vec3(-1.4, 0, 4.2);
					}
				}
				
			}
		}
	}
	if (doorOpen == true)
	{
		
		if (doorMove >= 2.5)
		{
			doorMove = 2.5;
			scene = 2;
		}
		else
		{
			doorMove += 0.5 * dt;
		}
	}
	//bomb ticking animation
	if (scene == 2 && condition == 0)
	{
		bomb_timer += 1 * dt;
		if (bomb_timer >= 0 && bomb_timer < 3)
		{
			light[5].power = 0;
			glUniform1f(m_parameters[U_LIGHT5_POWER], light[5].power);
		}
		if (bomb_timer >= 3 && bomb_timer < 4)
		{
			//beep
			light[5].power = 0.3;
			glUniform1f(m_parameters[U_LIGHT5_POWER], light[5].power);
			
		}
		if (bomb_timer >= 4)
		{
			bomb_timer = 0;
		}
		//end
		
		//bomb countdown starts
		if (bomb_diffused == false && condition == 0)
		{
			bomb_countdown -= 1 * (dt);
			if (bomb_countdown < 0)
			{
				condition = 2;
			}
		}
		else if (bomb_diffused == true && condition == 0)
		{
			condition = 1;
		}
		//win
		if (condition == 1)
		{
			bomb_countdown = bomb_countdown;
		}
		//lose
		else if (condition == 2)
		{
			bomb_countdown = bomb_countdown;
		}
	}
	if (scene == 1)
	{
		police_animation += 1 * dt;
		if (police_animation >= 1 && police_animation < 2)
		{
			light[3].color.Set(1, 0, 0);
			glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
		}
		if (police_animation >= 2 && police_animation < 3)
		{
			light[3].color.Set(0, 0, 1);
			glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &light[3].color.r);
		}
		if (police_animation >= 3)
		{
			police_animation = 1;
		}
	}

}

void SceneAssignment2::Render()
{
	// Clear color buffer every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Load view matrix stack and set it with camera position, target position and up direction
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);

	// Load identity matrix into the model stack
	modelStack.LoadIdentity();
	//light properties
	for (int i = 0; i < NUM_LIGHTS; i++)
	{
		//Spot light
		if (light[i].type == Light::LIGHT_DIRECTIONAL)
		{
			glm::vec3 lightDir(light[i].position.x, light[i].position.y, light[i].position.z);
			glm::vec3 lightDirection_cameraspace = viewStack.Top() * glm::vec4(lightDir, 0);
			glUniform3fv(m_parameters[U_LIGHT0_POSITION + (11 * i)], 1, glm::value_ptr(lightDirection_cameraspace));

		}
		//Directional light
		if (light[i].type == Light::LIGHT_SPOT)
		{
			glm::vec3 lightPosition_cameraspace = viewStack.Top() * glm::vec4(light[i].position, 1);
			glUniform3fv(m_parameters[U_LIGHT0_POSITION + (11 * i)], 1, glm::value_ptr(lightPosition_cameraspace));
			glm::vec3 spotDirection_cameraspace = viewStack.Top() * glm::vec4(light[i].spotDirection, 0);
			glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION + (11 * i)], 1, glm::value_ptr(spotDirection_cameraspace));

		}
		//point light
		
		else
		{
			glm::vec3 lightPosition_cameraspace = viewStack.Top() * glm::vec4(light[i].position, 1);
			glUniform3fv(m_parameters[U_LIGHT0_POSITION + (11 * i)], 1, glm::value_ptr(lightPosition_cameraspace));

		}
	}
	//player
	modelStack.PushMatrix();

	modelStack.Translate(playerPosition.x, playerPosition.y, playerPosition.z);
	modelStack.Rotate(playerRotation + -90, 0, 1, 0);

	modelStack.Scale(0.005, 0.005, 0.005);

	//texture properties


	if (camera.firstperson == false)
	{

		RenderMesh(meshList[GEO_PLAYER], true);
	}

	modelStack.PopMatrix();

	//scene 1
	if (scene == 1)
	{
		//disable all scene 2 lights
		for (int i = 4; i < 6; i++)
		{
			light[i].power = 0;
			glUniform1f(m_parameters[U_LIGHT0_POWER + (i * 11)], light[i].power);
		}

		//skybox
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, -50.f);
		RenderMesh(meshList[GEO_FRONT], false);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 0.f, 50.f);
		modelStack.Rotate(180.f, 0, 1, 0);
		RenderMesh(meshList[GEO_BACK], false);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(-50.f, 0.f, 0.f);
		modelStack.Rotate(90.f, 0, 1, 0);
		RenderMesh(meshList[GEO_LEFT], false);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(50.f, 0.f, 0.f);
		modelStack.Rotate(-90.f, 0, 1, 0);
		RenderMesh(meshList[GEO_RIGHT], false);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(0.f, 50.f, 0.f);
		modelStack.Rotate(-90.f, 0, 1, 0);
		modelStack.Rotate(90.f, 1, 0, 0);
		RenderMesh(meshList[GEO_TOP], false);
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(0.f, -50.f, 0.f);
		modelStack.Rotate(-90.f, 0, 1, 0);
		modelStack.Rotate(-90.f, 1, 0, 0);
		RenderMesh(meshList[GEO_BOTTOM], false);
		modelStack.PopMatrix();
		//end of skybox
		// 
		//Ground
		modelStack.PushMatrix();

		modelStack.Translate(0, 0, 0);

		modelStack.PushMatrix();
		//road
		modelStack.PushMatrix();
		modelStack.Translate(0, 0.001, 0);
		modelStack.Rotate(-90.f, 1, 0, 0);
		modelStack.Scale(0.03, 0.03, 0.03);
		modelStack.PushMatrix();

		for (int i = 0; i < 5; i++)
		{

			modelStack.Translate(0, -100, 0);

			RenderMesh(meshList[GEO_ROAD], true);
		}
		modelStack.PopMatrix();


		modelStack.PopMatrix();

		modelStack.PushMatrix();





		modelStack.PopMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(0, 0.001, 0);
		modelStack.Rotate(-90.f, 1, 0, 0);
		modelStack.Scale(0.03, 0.03, 0.03);

		RenderMesh(meshList[GEO_ROADEND], true);
		modelStack.PopMatrix();

		//car
		modelStack.PushMatrix();
		spawnCollider(glm::vec3(2, 0, 0), glm::vec3(1, 1, 3), 0, false);
		modelStack.Translate(2, 0, 0);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_CAR], true);
		modelStack.PopMatrix();
		//car 2
		modelStack.PushMatrix();
		spawnCollider(glm::vec3(-2, 0, -0.2), glm::vec3(1, 1, 3), 2, false);
		modelStack.Translate(-2, 0, -0.4);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_CAR], true);
		modelStack.PopMatrix();

		//barrier
		modelStack.PushMatrix();
		spawnCollider(glm::vec3(0, 0, 1.5), glm::vec3(10, 1, 0.3), 1, false);
		modelStack.Translate(-2, 0, 1.5);
		modelStack.Rotate(-90.f, 0, 1, 0);
		modelStack.Scale(0.3, 0.3, 0.3);
		RenderMesh(meshList[GEO_BARRIER], true);
		modelStack.PopMatrix();

		//barrier
		modelStack.PushMatrix();
		spawnCollider(glm::vec3(-3.5, 0, -2), glm::vec3(3, 0.3, 0.3), 3, false);
		modelStack.Translate(-3.5, 0, -2);
		modelStack.Rotate(-90.f, 0, 1, 0);
		modelStack.Scale(0.3, 0.3, 0.3);
		RenderMesh(meshList[GEO_BARRIER], true);
		modelStack.PopMatrix();

		//heli
		modelStack.PushMatrix();
		spawnCollider(glm::vec3(3, 0, -4), glm::vec3(1, 1, 5), 4, false);
		modelStack.Translate(3, 0, -3);
		modelStack.Scale(0.5, 0.5, 0.5);
		modelStack.Rotate(90.f, 0, 1, 0);
		RenderMesh(meshList[GEO_HELI], true);
		modelStack.PopMatrix();

		//barrier
		modelStack.PushMatrix();
		spawnCollider(glm::vec3(-4, 0, -8.5), glm::vec3(0.3, 0.3, 13), 5, false);

		modelStack.Translate(-4, 0, -3.5);
		modelStack.Scale(0.3, 0.3, 0.3);
		RenderMesh(meshList[GEO_BARRIER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-4.2, 0, -8);
		modelStack.Scale(0.3, 0.3, 0.3);
		RenderMesh(meshList[GEO_BARRIER], true);
		modelStack.PopMatrix();


		modelStack.PushMatrix();
		modelStack.Translate(-4.5, 0, -5.5);
		modelStack.Rotate(76, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_CAR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(2.3, 0, 4);
		modelStack.Rotate(24, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_VAN], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 4.3);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_VAN], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-4.1, 0, -10.5);
		modelStack.Rotate(12, 0, 1, 0);
		modelStack.Scale(0.3, 0.3, 0.3);
		RenderMesh(meshList[GEO_BARRIER], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-4, 0, -13);
		modelStack.Scale(0.3, 0.3, 0.3);
		RenderMesh(meshList[GEO_BARRIER], true);
		modelStack.PopMatrix();

		spawnCollider(glm::vec3(3, 0, -9), glm::vec3(1, 1, 13), 6, false);

		modelStack.PushMatrix();
		modelStack.Translate(3, 0, -13.5);
		modelStack.Rotate(180, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_RUSTY], true);
		modelStack.PopMatrix();

		for (int i = 0; i < 3; i++)
		{
			modelStack.PushMatrix();
			switch (i)
			{
			case 0:
				modelStack.Translate(3.2, 0, -11);
				break;
			case 1:
				modelStack.Translate(3, 0, -8);
				break;
			case 2:
				modelStack.Translate(3.1, 0, -6);
				break;
			}

			modelStack.Scale(0.3, 0.3, 0.3);
			RenderMesh(meshList[GEO_BARRIER], true);
			modelStack.PopMatrix();
		}

		modelStack.PushMatrix();
		modelStack.Translate(0, 15, -10);
		modelStack.Rotate(-90, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderMesh(meshList[GEO_HELI], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		spawnCollider(glm::vec3(-2.8, 1, -13), glm::vec3(1, 0.3, 1), 7, false);
		spawnCollider(glm::vec3(0,0,0), glm::vec3(2, 0.3, 2), 8, false);
		modelStack.Translate(1.5, 0, 1);
		RenderMesh(meshList[GEO_LAMP], true);
		modelStack.PopMatrix();


		modelStack.PushMatrix();
		modelStack.Translate(0, -25, -20);
		modelStack.Rotate(90, 0, 1, 0);
		modelStack.Scale(100,100,100);
		RenderMesh(meshList[GEO_WHEEL], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();

		modelStack.Translate(-2.8, 1, -13.15);
		modelStack.Scale(0.2, 0.2, 0.2);
		modelStack.Rotate(90, 1, 0, 0);
		RenderMesh(meshList[GEO_BUTTON], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1, doorMove, -14.5);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_DOOR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(-1, 1, -15);
		modelStack.Scale(3.5, 3, 0.5);
		RenderMesh(meshList[GEO_COLLIDER], true);
		modelStack.PopMatrix();

		modelStack.PopMatrix();
		modelStack.Translate(0, 0, -8.5f);
		modelStack.Rotate(-90.f, 1, 0, 0);

		modelStack.Scale(0.5, 0.5, 0.5);

		RenderMesh(meshList[GEO_PLANE], true);
		modelStack.PopMatrix();
		
		//tree
		for (int i = 0; i < 10; i++)
		{
			modelStack.PushMatrix();
			switch (i)
			{
			case 0:
				modelStack.Translate(1, 0.6, 3);
				break;
			case 1:
				modelStack.Translate(6, 0.2, -19);
				break;
			case 2:
				modelStack.Translate(2, 0.1, -8);
				break;
			case 3:
				modelStack.Translate(3, 0, 12);
				break;
			case 4:
				modelStack.Translate(4, 0.4, -12);
				break;
			case 5:
				modelStack.Translate(-22, 0, 3);
				break;
			case 6:
				modelStack.Translate(-29, 0.8, -19);
				break;
			case 7:
				modelStack.Translate(-33, 0.2, -8);
				break;
			case 8:
				modelStack.Translate(-38, 0.4, 5);
				break;
			case 9:
				modelStack.Translate(-35, 0.6, -12);
				break;
			}



			RenderMesh(meshList[GEO_TREE], true);
			modelStack.PopMatrix();
		}
		
		if (renderLightPos == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
			RenderMesh(meshList[GEO_SPHERE], true);
			modelStack.PopMatrix();

		}
		
		//UI elements must be last
		modelStack.PushMatrix();
		modelStack.Translate(-2.9, 1.3, -13.15);
		modelStack.Scale(0.1, 0.1, 0.1);
		RenderText(meshList[GEO_TEXT], "OPEN", Color(0, 1, 0));
		modelStack.PopMatrix();

		RenderTextOnScreen(meshList[GEO_TEXT], "Objective:", Color(0, 1, 0), 40, 0, 45);
		if (doorOpen == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Awaiting order...", Color(0, 1, 0), 40, 0, 5);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Enter the building", Color(0, 1, 0), 40, 0, 5);
		}
		if (render_button == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press E to open the door", Color(0, 1, 0), 40, 200, 75);
		}
		if (render_lamptxt == true)
		{
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Press E to turn off the lamp", Color(0, 1, 0), 40, 125, 75);
			modelStack.PopMatrix();
		}
		
		
	}
	//scene 2
	else if (scene == 2)
	{

		//teleport to new spawn
		if (doorOpen == true)
		{
			camera.firstperson = true;
			playerPosition = glm::vec3(-1.4, 0, 4.2);
			doorOpen = false;
		}
		//loop all scene 1 light and disable them
		for (int i = 0; i < 4; i++)
		{
			light[i].power = 0;
			glUniform1f(m_parameters[U_LIGHT0_POWER + (i * 11)], light[i].power);
		}
		//enable all scene 2 light
		if (scene2loaded == false)
		{
			for (int i = 4; i < 6; i++)
			{
				switch (i)
				{
				case 4:
					light[i].power = 0.3;
					break;
				case 5:
					light[i].power = 0.1;
					break;
				}

				glUniform1f(m_parameters[U_LIGHT0_POWER + (i * 11)], light[i].power);
			}
			scene2loaded = true;
		}
		



		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 0);
		modelStack.Scale(1, 1, 1);
		modelStack.Rotate(-90.f, 1, 0, 0);
		RenderMesh(meshList[GEO_FLOOR], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(0, 4, 0);
		modelStack.Scale(1, 1, 1);
		modelStack.Rotate(90, 1, 0, 0);
		RenderMesh(meshList[GEO_CELLING], true);
		modelStack.PopMatrix();
		for (int i = 0; i < 4; i++)
		{
			modelStack.PushMatrix();
			switch (i)
			{
			case 0:
				//front
				modelStack.Translate(0, 3, -5);

				break;
			case 1:
				//
				modelStack.Translate(-5, 3, 0);
				modelStack.Rotate(90,0, 1, 0);
				break;
			case 2:
				modelStack.Translate(0, 3, 5);
				modelStack.Rotate(180, 0, 1,0);
				break;
			case 3:
				modelStack.Translate(5, 3, 0);
				modelStack.Rotate(270, 0,1, 0);
				break;
			}
			modelStack.Scale(11, 6, 11);
			RenderMesh(meshList[GEO_WALL], true);
			modelStack.PopMatrix();
		}

		for (int i = 0; i < 16; i++)
		{
			modelStack.PushMatrix();
			switch (i)
			{
			case 0:
				spawnCollider(glm::vec3(-1.4, 0, 2.8), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(-1.4, 0, 2.8);
				modelStack.PushMatrix();
				modelStack.Translate(0,1.4,0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CRATE], true);
				modelStack.PopMatrix();
				break;
			case 1:
				spawnCollider(glm::vec3(-4.2, 0, 1.4), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(-4.2, 0,1.4);
				break;
			case 2:
				spawnCollider(glm::vec3(1.4, 0, 1.4), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(1.4, 0, 1.4);
				break;
			case 3:
				spawnCollider(glm::vec3(-4.2, 0, 0), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(-4.2, 0, 0);
				break;
			case 4:
				spawnCollider(glm::vec3(-2.8, 0, 0), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(-2.8, 0, 0);
				modelStack.PushMatrix();
				modelStack.Translate(0, 1.4, 0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CRATE], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(0, 2.8, 0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CRATE], true);
				modelStack.PopMatrix();
				break;
			case 5:
				spawnCollider(glm::vec3(-1.4, 0, 0), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(-1.4, 0, 0);
				modelStack.PushMatrix();
				modelStack.Translate(0, 1.4, 0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CRATE], true);
				modelStack.PopMatrix();
				break;
			case 6:
				spawnCollider(glm::vec3(1.4, 0, 0), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(1.4, 0, 0);
				break;
			case 7:
				spawnCollider(glm::vec3(1.4, 0, -1.4), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(1.4, 0, -1.4);
				break;
			case 8:
				spawnCollider(glm::vec3(-4.2, 0, -2.8), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(-4.2, 0, -2.8);
				modelStack.PushMatrix();
				modelStack.Translate(0, 1.4, 0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CRATE], true);
				modelStack.PopMatrix();
				break;
			case 9:
				spawnCollider(glm::vec3(-1.4, 0, -2.8), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(-1.4, 0, -2.8);
				break;
			case 10:
				spawnCollider(glm::vec3(0, 0, -4.2), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(0, 0, -4.2);
				break;
			case 11:
				spawnCollider(glm::vec3(2.8, 0, -4.2), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(2.8, 0, -4.2);
				modelStack.PushMatrix();
				modelStack.Translate(0, 1.4, 0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CRATE], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(0, 2.8, 0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CRATE], true);
				modelStack.PopMatrix();
				break;
			case 12:
				spawnCollider(glm::vec3(-2.8, 0, 4.2), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(-2.8, 0, 4.2);
				break;
			case 13:
				spawnCollider(glm::vec3(1.4, 0, 4.2), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(1.4, 0, 4.2);
				modelStack.PushMatrix();
				modelStack.Translate(0, 1.4, 0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CRATE], true);
				modelStack.PopMatrix();
				break;
			case 14:
				spawnCollider(glm::vec3(4.2, 0, 1.4), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(4.2, 0, 1.4);
				break;
			case 15:
				spawnCollider(glm::vec3(4.2, 0, -1.4), glm::vec3(1.5, 1.5, 1.5), 10 + i, false);
				modelStack.Translate(4.2, 0, -1.4);
				modelStack.PushMatrix();
				modelStack.Translate(0, 1.4, 0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CRATE], true);
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(0, 2.8, 0);
				modelStack.Scale(0.7, 0.7, 0.7);
				RenderMesh(meshList[GEO_CRATE], true);
				modelStack.PopMatrix();
				break;
			}
			modelStack.Scale(0.7, 0.7, 0.7);
			RenderMesh(meshList[GEO_CRATE], true);
			modelStack.PopMatrix();
		}

		modelStack.PushMatrix();
		spawnCollider(glm::vec3(-4.2, 0, -4.2), glm::vec3(1.5, 1.5, 1.5), 25, false);
		modelStack.Translate(-4.2, 0, -4.2);
		modelStack.Scale(0.001,0.001,0.001);
		RenderMesh(meshList[GEO_C4], true);
		modelStack.PopMatrix();

		//side wall collider
		spawnCollider(glm::vec3(0, 0, -5.5), glm::vec3(10, 1.5,1), 26, false);
		spawnCollider(glm::vec3(-5.5, 0, 0), glm::vec3(1, 1.5, 10), 27, false);
		spawnCollider(glm::vec3(0, 0, 5.5), glm::vec3(10, 1.5, 1), 28, false);
		spawnCollider(glm::vec3(5.5, 0, 0), glm::vec3(1, 1.5, 10), 29, false);
		if (bomb_diffusable == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press E to diffuse the bomb", Color(0, 1, 0), 40, 180, 75);
		}
		RenderTextOnScreen(meshList[GEO_TEXT], "Objective:", Color(0, 1, 0), 40, 0, 45);
		if (bomb_diffused == false)
		{	
			std::string temp("Diffuse the bomb in " + std::to_string(bomb_countdown));
			RenderTextOnScreen(meshList[GEO_TEXT], temp.substr(0,22), Color(0, 1, 0), 40, 0, 5);
			std::string temp1(std::to_string(bomb_countdown));
			viewStack.PushMatrix();
			modelStack.Translate(-4.2, 1, -4);
			modelStack.Scale(0.1, 0.1, 0.1);
			modelStack.Rotate(90,0, 1, 0);
			RenderText(meshList[GEO_TEXT], "Time left", Color(0, 1, 0));
				viewStack.PushMatrix();
				modelStack.Translate(0, -1, 0);
				RenderText(meshList[GEO_TEXT], temp1.substr(0, 4), Color(0, 1, 0));
				viewStack.PopMatrix();
			viewStack.PopMatrix();
		}
		//render win screen
		if (condition == 1)
		{
			RenderMeshOnScreen(meshList[GEO_WIN], 400, 300, 80 , 60);
		}
		else if (condition == 2)
		{
			RenderMeshOnScreen(meshList[GEO_LOSE], 400, 300, 80, 60);
		}
	}
}

void SceneAssignment2::RenderMesh(Mesh* mesh, bool enableLight)
{
	glm::mat4 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, glm::value_ptr(MVP));
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, glm::value_ptr(modelView));
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = glm::inverseTranspose(modelView);
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, glm::value_ptr(modelView_inverse_transpose));

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();

	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}


}

void SceneAssignment2::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
{
	glDisable(GL_DEPTH_TEST);
	glm::mat4 ortho = glm::ortho(0.f, 800.f, 0.f, 600.f, -1000.f, 1000.f); // dimension of screen UI​

	projectionStack.PushMatrix();

	projectionStack.LoadMatrix(ortho);

	viewStack.PushMatrix();

	viewStack.LoadIdentity();//No need camera for ortho mode​

	modelStack.PushMatrix();

	modelStack.LoadIdentity();
	//position
	modelStack.Translate(x,y,1);

	//scale
	modelStack.Scale(sizex,sizey,1);

	RenderMesh(mesh, false);

	projectionStack.PopMatrix();

	viewStack.PopMatrix();

	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void SceneAssignment2::RenderText(Mesh* mesh, std::string text, Color color)
{	
	if (!mesh || mesh->textureID <= 0)
		return;
	
	// Disable back face cullin

		glDisable(GL_CULL_FACE);

		glUniform1i(m_parameters[U_TEXT_ENABLED], 1);

		glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);

		glUniform1i(m_parameters[U_LIGHTENABLED], 0);

		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);

		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, mesh->textureID);

		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

		for (unsigned i = 0; i < text.length(); ++i)

		{

			glm::mat4 characterSpacing = glm::translate(

				glm::mat4(1.f),

				glm::vec3(i * 1.0f, 0, 0));

			glm::mat4 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;

			glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, glm::value_ptr(MVP));
			
			mesh->Render((unsigned)text[i] * 6, 6);

		}

			glBindTexture(GL_TEXTURE_2D, 0);

			glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

			glEnable(GL_CULL_FACE);
}

void SceneAssignment2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0)//Proper error chec
	{
		return;
	}

		glDisable(GL_DEPTH_TEST);

		glm::mat4 ortho = glm::ortho(0.f, 800.f, 0.f, 600.f, -100.f, 100.f); // dimension of screen UI​

	projectionStack.PushMatrix();

		projectionStack.LoadMatrix(ortho);

		viewStack.PushMatrix();

		viewStack.LoadIdentity();//No need camera for ortho mod

		modelStack.PushMatrix();
		
		modelStack.LoadIdentity(); //Reset modelStack

	modelStack.Translate(x, y, 0);

		modelStack.Scale(size, size, size);
		glUniform1i(m_parameters[U_TEXT_ENABLED], 1);

			glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);

			glUniform1i(m_parameters[U_LIGHTENABLED], 0); 

			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1); 

			glActiveTexture(GL_TEXTURE0); 

			glBindTexture(GL_TEXTURE_2D, mesh->textureID); 

			glUniform1i(m_parameters[U_COLOR_TEXTURE], 0); 

			for (unsigned i = 0; i < text.length(); ++i)

			{

				glm::mat4 characterSpacing = glm::translate(

					glm::mat4(1.f),

					glm::vec3(0.5f + i * 0.5f, 0.5f, 0));
				glm::mat4 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
				
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, glm::value_ptr(MVP));
				
				mesh->Render((unsigned)text[i] * 6, 6);
			}

				glBindTexture(GL_TEXTURE_2D, 0); 

				glUniform1i(m_parameters[U_TEXT_ENABLED], 0); 

				projectionStack.PopMatrix(); 

				viewStack.PopMatrix(); 

				modelStack.PopMatrix();
				
				glEnable(GL_DEPTH_TEST);
}

void SceneAssignment2::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
		{
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SceneAssignment2::spawnCollider(glm::vec3 pos, glm::vec3 scale, int number, bool spawn)
{
	modelStack.PushMatrix();
	collider[number].pos = glm::vec3(pos.x, pos.y, pos.z);
	collider[number].scale = glm::vec3(scale.x, scale.y, scale.z);
	modelStack.Translate(collider[number].pos.x, collider[number].pos.y, collider[number].pos.z);
	modelStack.Scale(collider[number].scale.x, collider[number].scale.y, collider[number].scale.z);

	if(spawn == true)
	RenderMesh(meshList[GEO_COLLIDER], true);
	modelStack.PopMatrix();
}


void SceneAssignment2::HandleKeyPress()
{
	if (KeyboardController::GetInstance()->IsKeyPressed(0x31))
	{
		// Key press to enable culling
		glEnable(GL_CULL_FACE);
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(0x32))
	{
		// Key press to disable culling
		glDisable(GL_CULL_FACE);
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(0x33))
	{
		// Key press to enable fill mode for the polygon
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	}
	if (KeyboardController::GetInstance()->IsKeyPressed(0x34))
	{
		// Key press to enable wireframe mode for the polygon
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}
	//switch light type
	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_TAB))
	{
		if (light[1].type == Light::LIGHT_SPOT)
		{
			light[1].type = Light::LIGHT_DIRECTIONAL;
		}

		else if (light[1].type == Light::LIGHT_DIRECTIONAL)
		{
			light[1].type = Light::LIGHT_POINT;
		}
		else
		{
			light[1].type = Light::LIGHT_SPOT;
		}
		glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
		
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_CAPS_LOCK))
	{
		if (renderLightPos == false)
		{

			renderLightPos = true;
		}
		else
		{
			renderLightPos = false;

		}
	}
	
	
}

void SceneAssignment2::HandleMouseInut()
{
	static bool isLeftUp = false;
	static bool isRightUp = false;
	// Process Left button​

		if (!isLeftUp && MouseController::GetInstance()->IsButtonDown(GLFW_MOUSE_BUTTON_LEFT))
		{
			isLeftUp = true;
		}
		else if(isLeftUp && MouseController::GetInstance()->IsButtonUp(GLFW_MOUSE_BUTTON_LEFT))
		{
			isLeftUp = false;
		}
		// Continue to do for right button
		if (!isRightUp && MouseController::GetInstance()->IsButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
		{
			isRightUp = true;
		}
		else if (isRightUp && MouseController::GetInstance()->IsButtonUp(GLFW_MOUSE_BUTTON_RIGHT))
		{
			isRightUp = false;
		}
		
}
