#pragma once
#include "Input.h"

namespace Input
{  
	namespace Keyboard
	{
		bool IsKeyDown(Key key);
		bool KeyPressed(Key key);
		bool KeyReleased(Key key);
	} 
}