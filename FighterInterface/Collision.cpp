#include "Collision.h"
#include "Render.h"

namespace Collision
{ 

	Collider::Collider(void)
	{
		
	}

 
	Collider::Collider(float x, float y, float width, float height,float r /*= 1*/, float g /*= 1*/, float b /*= 1*/):
		x(x),
		y(y),
		localX(x),
		localY(y),
		width(width),
		height(height),
		r(r),
		g(g),
		b(b),
		damage(0)
	{

	}


	Collider::~Collider(void)
	{
	}

	void Collider::Render() 
	{
		Primitive_Debug_Quad quad(x,y,width,height,r,g,b);
		Render::DrawDebugQuad(quad);
	}

	bool Collider::Overlaps(Collider const & collider) const
	{
		float sourceMinX = this->x;
		float sourceMinY = this->y;
		float sourceMaxX = this->x + this->width;
		float sourceMaxY = this->y + this->height;
		float targetMinX = collider.x;
		float targetMinY = collider.y;
		float targetMaxX = collider.x + collider.width;
		float targetMaxY = collider.y + collider.height;
		 
		if (sourceMaxX < targetMinX || sourceMinX > targetMaxX) return false;
		if (sourceMaxY < targetMinY || sourceMinY > targetMaxY) return false;

		return true; 
	}


	CollisionSet::CollisionSet(void)
	{
	}


	CollisionSet::~CollisionSet(void)
	{
	}

	void CollisionSet::AddCollider(Collider collider)
	{
		colliders.push_back(collider);
	}



}

