#pragma once

#include <vector>
#include "IRenderable.h"

namespace Collision
{


	class Collider : IRenderable
	{
	public:
		Collider(void);
		Collider(float x, float y, float width, float height,float r = 1, float g = 1, float b = 1);
		~Collider(void);
		virtual void Render() override;
		bool Overlaps(Collider const & collider) const;

		float x,y,width,height;
		float r,g,b;
		float localX,localY;

		//if this is an attack hitbox then this is how much damage the attack hitbox does
		float damage;

		float knockback;

	private:
		
	};

	class CollisionSet
	{
	public:
		CollisionSet(void);
		~CollisionSet(void);

 
		void AddCollider(Collider collider);
		std::vector<Collider> colliders;
	

	
	};
}