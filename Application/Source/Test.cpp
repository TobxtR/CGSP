#include "Test.h"
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
SceneTest::SceneTest()
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::Init()
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
	m_programID = LoadShaders("Shader//Texture.vertexshader",
		"Shader//Blending.fragmentshader");
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
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT],
		m_parameters[U_MATERIAL_DIFFUSE],
		m_parameters[U_MATERIAL_SPECULAR],
		m_parameters[U_MATERIAL_SHININESS]);

	// Initialise camera properties
	camera.Init(glm::vec3(10,0,0), glm::vec3(0,0,0),glm::vec3(0,1,0));
	 
	// Init VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("Axes", 10000.f, 10000.f, 10000.f);
	meshList[GEO_PLANE] = MeshBuilder::GenerateQuad("Plane", Color(1.f, 1.f, 1.f), 10.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Light", Color(1.f, 1.f, 1.f), 0.3,10,10);
	meshList[GEO_PLANE]->textureID = LoadTGA("Image//color.tga");
	meshList[GEO_GUI] = MeshBuilder::GenerateQuad("GUI", Color(1.f, 1.f, 1.f), 10.f);
	meshList[GEO_GUI]->textureID = LoadTGA("Image//NYPTransparent.tga");
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
	meshList[GEO_BLEND] = MeshBuilder::GenerateQuad("NYP", Color(1.f, 1.f, 1.f), 100.f);
	meshList[GEO_BLEND]->textureID = LoadTGA("Image//NYPTransparent.tga");

	//Car
	meshList[GEO_CAR] = MeshBuilder::GenerateOBJ("Car", "OBJ//Car.OBJ");
	meshList[GEO_CAR]->textureID = LoadTGA("Image//Car.tga");
	//Man
	meshList[GEO_PLAYER] = MeshBuilder::GenerateOBJ("Human", "OBJ//guy_obj.OBJ");
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//guy_obj.tga");

	// 16 x 16 is the number of columns and rows for the text​
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	//meshList[GEO_SPHERE_BLUE] = MeshBuilder::GenerateSphere("Earth", Color(0.4f, 0.2f, 0.8f), 1.f, 12, 12);
	//meshList[GEO_SPHERE_GREY] = MeshBuilder::GenerateSphere("Moon", Color(0.5f, 0.5f, 0.5f), 1.f, 4, 4);

	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);


	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	light[0].position = glm::vec3(0, 5, 0);
	light[0].color.Set(1, 1, 1);
	light[0].type = Light::LIGHT_POINT;
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = 45.f;
	light[0].cosInner = 30.f;
	light[0].exponent = 3.f;
	light[0].spotDirection = glm::vec3(0.f, 1.f, 0.f);

	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], cosf(glm::radians<float>(light[0].cosCutoff)));
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], cosf(glm::radians<float>(light[0].cosInner)));
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	glUniform1i(m_parameters[U_NUMLIGHTS], NUM_LIGHTS);


	enableLight = true;


}

void SceneTest::Update(double dt)
{
	HandleKeyPress();

	if (KeyboardController::GetInstance()->IsKeyDown('I'))
		light[0].position.z -= static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('K'))
		light[0].position.z += static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('J'))
		light[0].position.x -= static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('L'))
		light[0].position.x += static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('O'))
		light[0].position.y -= static_cast<float>(dt) * 5.f;
	if (KeyboardController::GetInstance()->IsKeyDown('P'))
		light[0].position.y += static_cast<float>(dt) * 5.f;

	if (firstperson == true)
	{
		playerPosition = camera.position;
	}
	else
	{
		playerPosition = camera.target;
		
	}

	camera.Update(dt);


}

void SceneTest::Render()
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

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		glm::vec3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		glm::vec3 lightDirection_cameraspace = viewStack.Top() * glm::vec4(lightDir, 0);
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, glm::value_ptr(lightDirection_cameraspace));
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		glm::vec3 lightPosition_cameraspace = viewStack.Top() * glm::vec4(light[0].position, 1);
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, glm::value_ptr(lightPosition_cameraspace));
		glm::vec3 spotDirection_cameraspace = viewStack.Top() * glm::vec4(light[0].spotDirection, 0);
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, glm::value_ptr(spotDirection_cameraspace));
	}
	else {
		// Calculate the light position in camera space
		glm::vec3 lightPosition_cameraspace = viewStack.Top() * glm::vec4(light[0].position, 1);
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, glm::value_ptr(lightPosition_cameraspace));
	}
	//light sphere
	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_SPHERE], false);
	modelStack.PopMatrix();

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

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0, 10);
	RenderMesh(meshList[GEO_BLEND], false);
	modelStack.PopMatrix();
	//No transform needed
	RenderMeshOnScreen(meshList[GEO_GUI], 50, 50, 10, 10);
	//scale, translate, rotate
	modelStack.PushMatrix();
	//scale, translate, rotate

	modelStack.Scale(1.f, 1, 1);
	modelStack.Translate(0.f, 0, -10);
	modelStack.Rotate(0.f, 0, 10,0);
	RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));

	modelStack.PopMatrix();
	//No transform needed

	//player
	modelStack.PushMatrix();
	modelStack.Translate(playerPosition.x, playerPosition.y, playerPosition.z);
	modelStack.Scale(0.01, 0.01, 0.01);

	//texture properties
	meshList[GEO_PLAYER]->material.kAmbient.Set(1, 1, 1);
	meshList[GEO_PLAYER]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_PLAYER]->material.kSpecular.Set(0,0,0);
	if (firstperson == false)
	{

		RenderMesh(meshList[GEO_PLAYER], true);
	}

	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_TEXT], "Poop", Color(0, 1, 0), 40, 0, 0);
}

void SceneTest::RenderMesh(Mesh* mesh, bool enableLight)
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

void SceneTest::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey)
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

void SceneTest::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneTest::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

					glm::vec3(0.5f + i * 1.0f, 0.5f, 0));
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

void SceneTest::Exit()
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

void SceneTest::HandleKeyPress()
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
	

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
	{
		// Change to black background
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_0))
	{
		// Toggle light on or off
	/*	enableLight = !enableLight;*/

		if (light[0].power <= 0.1f)
			light[0].power = 1.f;
		else
			light[0].power = 0.1f;
		glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_9))
	{
		// Toggle light on or off
		//enableLight = !enableLight;

		light[0].color.Set(0.5f, 0.f, 0.f);
		glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_8))
	{
		// Toggle light on or off
		//enableLight = !enableLight;

		light[0].color.Set(1.f, 1.f, 1.f);
		glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(GLFW_KEY_TAB))
	{
		if (light[0].type == Light::LIGHT_POINT) {
			light[0].type = Light::LIGHT_DIRECTIONAL;
		}
		else if (light[0].type == Light::LIGHT_DIRECTIONAL) {
			light[0].type = Light::LIGHT_SPOT;
		}
		else {
			light[0].type = Light::LIGHT_POINT;
		}

		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	//change camera view

	if (KeyboardController::GetInstance()->IsKeyPressed('V'))
	{
		if (firstperson == true)
		{
			firstperson = false;
		}
		else
		{
			firstperson = true;
		}
	}
	
}

void SceneTest::HandleMouseInut()
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
