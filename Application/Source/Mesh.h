#ifndef MESH_H
#define MESH_H
#include <glm\glm.hpp>

#include <string>
#include "Material.h"
#include <vector>
/******************************************************************************/
/*!
		Class Mesh:
\brief	To store VBO (vertex & color buffer) and IBO (index buffer)
*/
/******************************************************************************/
class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	~Mesh();
	void Render();

	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned indexBuffer;
	unsigned indexSize;
	glm::vec3 normal;

	Material material;
	unsigned textureID;

	void Render(unsigned offset, unsigned count);

	static void SetMaterialLoc(unsigned kA, unsigned kD, unsigned kS, unsigned nS);

	std::vector<Material> materials;
	static unsigned locationKa;
	static unsigned locationKd;
	static unsigned locationKs;
	static unsigned locationNs;

};

#endif