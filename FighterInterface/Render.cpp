
#include "Render.h"

struct Primitive_Vertex
{
	GLfloat x,y,z; 
	Primitive_Vertex(float x, float y, float z)  :
		x(x),
		y(y),
		z(z) 
	{ }
	 
	Primitive_Vertex() 
	{
		x = y = z = 0; 
	}
};

struct Primitive_Color
{
	GLfloat x,y,z; 
	Primitive_Color(float x, float y, float z)  :
		x(x),
		y(y),
		z(z) 
	{ }
	 
	Primitive_Color() 
	{
		x = y = z = 0; 
	}
};



namespace Render
{
	RenderBuffer<Primitive_Vertex> mDebugBufferVerts(1000);
	RenderBuffer<Primitive_Color> mDebugBufferColors(1000);


	void Render::Init()
	{
	}
	//comes in as a ref to avoid 2 copies
	void Render::DrawDebugQuad(Primitive_Debug_Quad & quad)
	{
		Primitive_Vertex v0,v1,v2,v3;

		v0.x = quad.x;
		v0.y = quad.y;
		v0.z = quad.z;

		v1.x = quad.x + quad.width;
		v1.y = quad.y;
		v1.z = quad.z;

		v2.x = quad.x;
		v2.y = quad.y + quad.height;
		v2.z = quad.z;

		v3.x = quad.x + quad.width;
		v3.y = quad.y + quad.height;
		v3.z = quad.z; 

		mDebugBufferVerts.Add(v3);
		mDebugBufferVerts.Add(v2);
		mDebugBufferVerts.Add(v1);

		mDebugBufferVerts.Add(v1);
		mDebugBufferVerts.Add(v2);
		mDebugBufferVerts.Add(v0);

		Primitive_Color color;
		color.x = quad.r;
		color.y = quad.g;
		color.z = quad.b;

		mDebugBufferColors.Add(color);
		mDebugBufferColors.Add(color);
		mDebugBufferColors.Add(color);
		mDebugBufferColors.Add(color);
		mDebugBufferColors.Add(color);
		mDebugBufferColors.Add(color);
	}




	void Render::Render()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, 1280, 720, 0.0f, -1.0f, +1.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		glEnableClientState( GL_VERTEX_ARRAY );	// Enable Vertex Arrays 
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer( 3, GL_FLOAT, 0, mDebugBufferVerts.GetData() ); 
		glColorPointer(3,GL_FLOAT,0,mDebugBufferColors.GetData());
		glDrawArrays( GL_TRIANGLES, 0, mDebugBufferVerts.GetMarkerPosition() );
		glDisableClientState( GL_VERTEX_ARRAY );	
		glDisableClientState( GL_COLOR_ARRAY );	
		mDebugBufferVerts.Clear();
		mDebugBufferColors.Clear();
	}

}