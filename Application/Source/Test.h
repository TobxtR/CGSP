#ifndef SCENE_TEST_H
#define SCENE_TEST_H

#include "Scene.h"
#include "Mesh.h"
#include "CameraFPS.h"
#include "MatrixStack.h"
#include "Light.h"

class SceneTest : public Scene
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_SPHERE,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_GUI,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_TEXT,
		GEO_FRONT,
		GEO_BACK,
		GEO_PLANE,
		GEO_BLEND,
		GEO_PLAYER,
		GEO_CAR,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_LIGHTENABLED,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	SceneTest();
	~SceneTest();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	
private:
	void HandleKeyPress();
	void HandleMouseInut();

	void RenderMesh(Mesh* mesh, bool enableLight);

	glm::vec3 playerPosition;
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	bool firstperson = true;

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	CameraFPS camera;
	int projType = 1; // fix to 0 for orthographic, 1 for projection

	MatrixStack modelStack, viewStack, projectionStack;

	static const int NUM_LIGHTS = 1;
	Light light[NUM_LIGHTS];
	bool enableLight;
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizex, float sizey);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
};

#endif