#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include <glm\gtc\constants.hpp>
#include "LoadOBJ.h"
/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	//x-axis
	v.pos.Set(-lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	//y-axis
	v.pos.Set(0, -lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	//z-axis
	v.pos.Set(0, 0, -lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	// Add the vertices here
	v.pos.Set(-0.5f * length, 0.5f * length, 0.f); v.color.Set(color.r, color.g, color.b); 
	v.normal = glm::vec3(0.f, 0.f, 1.f); v.texCoord = glm::vec2(0.f, 1.f); vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, -0.5f * length, 0.f);	v.color.Set(color.r, color.g, color.b); 
	v.normal = glm::vec3(0.f, 0.f, 1.f); v.texCoord = glm::vec2(0.f, 0.f); vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, 0.5f * length, 0.f); v.color.Set(color.r, color.g, color.b); 
	v.normal = glm::vec3(0.f, 0.f, 1.f); v.texCoord = glm::vec2(1.f, 1.f); vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, -0.5f * length, 0.f); v.color.Set(color.r, color.g, color.b); 
	v.normal = glm::vec3(0.f, 0.f, 1.f); v.texCoord = glm::vec2(1.f, 0.f); vertex_buffer_data.push_back(v);


	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);


	// Create the new mesh
	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string& meshName, Color color, float radius, int numSlice)
{
	Vertex v; // Vertex definition
	std::vector<Vertex> vertex_buffer_data; // Vertex Buffer Objects (VBOs)
	std::vector<GLuint> index_buffer_data; // Element Buffer Objects (EBOs)
	float anglePerSlice = glm::two_pi<float>() / numSlice;
	v.pos.Set(0, 0, 0);
	v.color.Set(color.r, color.g, color.b);
	vertex_buffer_data.push_back(v);
	for (int i = 1; i <= numSlice + 1; i++) {
		float theta = (i - 1) * anglePerSlice;
		v.pos.Set(radius * cosf(theta), 0, radius * sinf(theta));
		v.color.Set(color.r, color.g, color.b);
		vertex_buffer_data.push_back(v);
	}
	for (int i = 1; i <= numSlice + 1; i++) {
		index_buffer_data.push_back(i);
		index_buffer_data.push_back(0);
	}
	// Create the new mesh
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	return mesh;

}

Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, float radius, int numSlice, int numStack)
{
	Vertex v; // Vertex definition
	std::vector<Vertex> vertex_buffer_data; // Vertex Buffer Objects (VBOs)
	std::vector<GLuint> index_buffer_data; // Element Buffer Objects (EBOs)
	float degreePerStack = glm::pi<float>() / numStack;
	float degreePerSlice = glm::two_pi<float>() / numSlice;
	for (unsigned stack = 0; stack < numStack + 1; ++stack) //stack
	{
		float phi = -glm::half_pi<float>() + stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) //slice
		{
			float theta = slice * degreePerSlice;
			v.pos.Set(radius * cos(phi) * cos(theta),
				radius * sin(phi),
				radius * cos(phi) * sin(theta));
			v.color.Set(color.r, color.g, color.b);

			v.normal = glm::vec3(cosf(phi) * cosf(theta), sinf(phi), cosf(phi) * sinf(theta));

			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for (unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			index_buffer_data.push_back((numStack+1) * stack + slice);
			index_buffer_data.push_back((numStack+1) * (stack+1) + slice);
		}
	}
	// Create the new mesh
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	return mesh;

}

Mesh* MeshBuilder::GenerateTorus(const std::string& meshName, Color color, float innerR, float outerR, int numSlice, int numStack)
{
	Vertex v; // Vertex definition
	std::vector<Vertex> vertex_buffer_data; // Vertex Buffer Objects (VBOs)
	std::vector<GLuint> index_buffer_data; // Element Buffer Objects (EBOs)
	float degreePerStack = glm::two_pi<float>() / numStack;
	float degreePerSlice = glm::two_pi<float>() / numSlice;
	for (unsigned stack = 0; stack < numStack + 1; ++stack) //stack
	{
		float phi = stack * degreePerStack;
		for (unsigned slice = 0; slice < numSlice + 1; ++slice) //slice
		{
			float theta = slice * degreePerSlice;
			v.pos.Set((outerR + innerR * cos(theta)) * sin(phi), innerR * sin(theta), (outerR + innerR * cos(theta)) * cos(phi));
			v.color.Set(color.r, color.g, color.b);
			vertex_buffer_data.push_back(v);
		}
	}
	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for (unsigned slice = 0; slice <= numSlice + 1; ++slice)
		{
			index_buffer_data.push_back((numStack + 1) * stack + slice);
			index_buffer_data.push_back((numStack + 1) * (stack + 1) + slice);
		}
	}
	// Create the new mesh
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex),
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint),
		&index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	return mesh;

}

Mesh* MeshBuilder::GenerateCube(const std::string& meshName, Color color, float length)
{
	Vertex v;
	v.color = color;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.normal = glm::vec3(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.normal = glm::vec3(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.normal = glm::vec3(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.normal = glm::vec3(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.normal = glm::vec3(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.normal = glm::vec3(0, 0, 1);	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.normal = glm::vec3(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.normal = glm::vec3(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.normal = glm::vec3(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.normal = glm::vec3(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.normal = glm::vec3(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.normal = glm::vec3(1, 0, 0);	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.normal = glm::vec3(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.normal = glm::vec3(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.normal = glm::vec3(0, 1, 0);	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, 0, -1);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, 0, -1);	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.normal = glm::vec3(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.normal = glm::vec3(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.normal = glm::vec3(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.normal = glm::vec3(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.normal = glm::vec3(-1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.normal = glm::vec3(-1, 0, 0);	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.normal = glm::vec3(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.normal = glm::vec3(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.normal = glm::vec3(0, -1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.normal = glm::vec3(0, -1, 0);	vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i + 1);
	}

	// Crate Mesh code here
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), 
		&vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), 
		&index_buffer_data[0], GL_STATIC_DRAW);
	// Set draw mesh to triangles
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string& meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;

	std::vector<Vertex> vertex_buffer_data;

	std::vector<unsigned> index_buffer_data;

	float width = 1.f / numCol;

	float height = 1.f / numRow;

	unsigned offset = 0;

	for (unsigned row = 0; row < numRow; ++row)

	{

		for (unsigned col = 0; col < numCol; ++col)
		{

			v.pos.Set(0.5f, 0.5f, 0.f);

			v.normal = glm::vec3(0, 0, 1);

			v.texCoord = glm::vec2(width * (col + 1), height * (numRow - row));

			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.5f, 0.f);

			v.normal = glm::vec3(0, 0, 1);

			v.texCoord = glm::vec2(width * (col + 0), height * (numRow - row));

			vertex_buffer_data.push_back(v);
			
			v.pos.Set(-0.5f, -0.5f, 0.f);

			v.normal = glm::vec3(0, 0, 1);

			v.texCoord = glm::vec2(width * (col + 0), height * (numRow - 1 - row));

			vertex_buffer_data.push_back(v);
			
			v.pos.Set(0.5f, -0.5f, 0.f);

			v.normal = glm::vec3(0, 0, 1);

			v.texCoord = glm::vec2(width * (col + 1), height * (numRow - 1 - row));

			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back(0 + offset);

			index_buffer_data.push_back(1 + offset);

			index_buffer_data.push_back(2 + offset);

			index_buffer_data.push_back(0 + offset);

			index_buffer_data.push_back(2 + offset);

			index_buffer_data.push_back(3 + offset);

			offset += 4;
		}

	}
	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLES;

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string& meshName, const std::string& file_path)
{
	// Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);

	if (!success) { return NULL; }

	// Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;

}

Mesh* MeshBuilder::GenerateOBJMTL(const std::string& meshName, const std::string& file_path, const std::string& mtl_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<Material> materials;
	bool success = LoadOBJMTL(file_path.c_str(), mtl_path.c_str(), vertices, uvs, normals, materials);
	if (!success) return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	Mesh* mesh = new Mesh(meshName);
	for (Material& material : materials)
		mesh->materials.push_back(material);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0],
		GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0],
		GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	return mesh;
}
