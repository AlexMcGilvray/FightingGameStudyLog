#pragma once
 
namespace Input
{ 
	typedef int Key; //keyboard key typedef. Right now maps to the GLFW types
	namespace Keyboard
	{
		bool IsKeyDown(Key key);
		bool KeyPressed(Key key);
		bool KeyReleased(Key key);
	}

}