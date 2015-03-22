#include "Keyboard.h"
#include "GameSystems.h"
#include <GLFW/glfw3.h> 

bool Input::Keyboard::IsKeyDown(Key key)
{
	if (glfwGetKey(GameSystems::GetWindow(),key) == GLFW_REPEAT )
		return true;
	return false; 
}

bool Input::Keyboard::KeyPressed(Key key)
{
	if (glfwGetKey(GameSystems::GetWindow(),key) == GLFW_PRESS )
		return true;
	return false; 
}

bool Input::Keyboard::KeyReleased(Key key)
{
	if (glfwGetKey(GameSystems::GetWindow(),key) == GLFW_RELEASE )
		return true;
	return false; 
}

