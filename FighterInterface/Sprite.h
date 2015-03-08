#pragma once
#include "IRenderable.h"
#include "IUpdatable.h"


namespace Graphics
{ 

	class Sprite : public IRenderable, public IUpdatable
	{
	public:
		Sprite(void);
		~Sprite(void);
	};

	class Animation : public IUpdatable
	{
	public:
		Animation(void);
		~Animation(void); 
	};


	class Frame
	{
	public:
		Frame(void);
		~Frame(void); 
	};

}