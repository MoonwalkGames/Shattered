#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <string>
#include <GLUT\glut.h>
#include <vector>
#include <fstream>

using namespace std;

struct Vec3
{
	float x, y, z;

	Vec3(float _X = 0, float _Y = 0, float _Z = 0)
	{
		x = _X;
		y = _Y;
		z = _Z;
	}

	void scale(float scaler)
	{
		x *= scaler;
		y *= scaler;
		z *= scaler;
	}
};

/*
	Simple Vertex struct that basically just has an ordered-triplet. Struct instead of class due to just holding some data & ease of access
*/
struct Vertex
{
	Vertex()
	{
		position = Vec3();
		uvCoord = Vec3();
		normal = Vec3();
	}

	Vertex(Vec3 pos, Vec3 uv, Vec3 n)
	{
		position = pos;
		uvCoord = uv;
		normal = n;
	}

	void output()
	{
		cout << "Vertex === " << endl;
		cout << "POS: " << position.x << ", " << position.y << ", " << position.z << endl;
		cout << "UV: " << uvCoord.x << ", " << uvCoord.y << ", " << uvCoord.z << endl;
		cout << "Normal: " << normal.x << ", " << normal.y << ", " << normal.z << endl << endl;
	}

	Vec3 position;
	Vec3 uvCoord; //Z will always be 0
	Vec3 normal;
};

/*
	Simple Face struct, contains 3 vertices
*/
struct Face
{
	Face() 
	{
		vertices = new Vertex[3];
	}

	Face(Vertex a, Vertex b, Vertex c)
	{
		vertices = new Vertex[3];
		vertices[0] = a;
		vertices[1] = b;
		vertices[2] = c;
	}

	~Face()
	{
		//delete[] vertices;
		//vertices = 0;
	}

	void draw() const
	{
		for (int i = 0; i < 3; i++)
			glVertex3f(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z);
	}

	void output() const
	{
		cout << "FACE -------------------" << endl;

		for (int i = 0; i < 3; i++)
			vertices[i].output();

		cout << "\n\n";
	}

	Vertex* vertices;
};

/*
	Mesh class that is basically just currently an array of faces
	Takes in a string for the fileName to load the faces from
*/
class Mesh
{
public:
	Mesh(const string& fileName); //The mesh takes a string for the fileName that it is loading in OBJ format, this will be passed to the OBJLoader in order to get the vertices from it
	~Mesh() {};

	void draw() const; //Called every frame...passes the vertices to immediate openGl in the main screen callback function
	void output() const;
	void scale(float scaleFactor);

private:
	std::vector<Face> faces; //Vector of faces
	int numFaces; //How many vertices are in the mesh, calculated when the obj is loaded

	void loadOBJ(const string& fileName); //private utility functions that actually loads the obj passed to the mesh in the constructor
	void orderVertices();
};

#endif
