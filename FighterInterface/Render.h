#pragma once
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "RenderBuffer.h"

struct Primitive_Debug_Quad
{

	float x,y,z;
	float width,height; 
	float r,g,b;

	Primitive_Debug_Quad(float x, float y,  float width, float height, float z = 0)  :
		x(x),
		y(y),
		z(z),
		width(width),
		height(height) 
	{
		r = g = b = 0;
	}

	Primitive_Debug_Quad(float x, float y, float width, float height,float r,float g,float b, float z = 0)  :
		x(x),
		y(y),
		z(z),
		width(width),
		height(height) ,
		r(r),
		g(g),
		b(b)
	{

	}

};



namespace Render
{  
	//comes in as a ref to avoid 2 copies
	void Init();
	void DrawDebugQuad(Primitive_Debug_Quad & quad); 
	void Render();

}