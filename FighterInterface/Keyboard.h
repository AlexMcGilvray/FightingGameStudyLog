#pragma once
#include "Input.h"

namespace Input
{  
	namespace Keyboard
	{ 
		void PrepareForPolling();
		void AddKeyDownState(Key key);
		bool IsKeyDown(Key key);
		bool KeyPressed(Key key);
		bool KeyReleased(Key key);
	} 
}