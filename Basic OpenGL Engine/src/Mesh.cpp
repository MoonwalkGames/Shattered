#include "Mesh.h"

Mesh::Mesh(const string& fileName)
{
	float* rawVertices = ObjLoader::loadOBJ(fileName); //Gets the floating point data from the OBJ loader as an array of floats, this function converts that into vertices

	numVertices = (sizeof(rawVertices[0]) / sizeof(rawVertices)) / 3; //Calculates the number of vertices by finding the number of floats and then dividing that by 3

	try
	{
		vertices = new Vertex[numVertices];
	}
	catch (...)
	{
		cerr << "Could not allocate the memory for the mesh's vertices. Exiting" << endl;
		exit(1);
	}
	
	for (int i = 0; i < numVertices; i++)
		vertices[i] = Vertex(rawVertices[i * 3], rawVertices[1 + (i * 3)], rawVertices[2 + (i * 3)]); //Has to offset each piece of data since vertices use 3 at a time

	delete rawVertices;
	rawVertices = 0;
}


void Mesh::draw() const
{
	glBegin(GL_TRIANGLE_FAN);
	{
		for (int i = 0; i < numVertices; i++)
			glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	}
	glEnd();
}