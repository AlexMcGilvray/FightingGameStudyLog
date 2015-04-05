#include "Keyboard.h"
#include "GameSystems.h"
#include <GLFW/glfw3.h> 
#include "Input.h"
#include <set>
#include <algorithm>


//todo we need to use the callback method to get the data we need on keys

namespace 
{ 
	std::set<Input::Keyboard::Key> previousFramePressedButtons;
	std::set<Input::Keyboard::Key> currentFramePressedButtons;
}

bool Input::Keyboard::IsKeyDown(Key key)
{
	bool keyDown = glfwGetKey(GameSystems::GetWindow(),key) == GLFW_PRESS;
	currentFramePressedButtons.insert(key); 
	return keyDown; 
}

bool Input::Keyboard::KeyPressed(Key key)
{
	bool keyDown = glfwGetKey(GameSystems::GetWindow(),key) == GLFW_PRESS;
	if (previousFramePressedButtons.find(key) != previousFramePressedButtons.end())
	{
		keyDown = false;
	}
	currentFramePressedButtons.insert(key); 
	return keyDown; 
}

bool Input::Keyboard::KeyReleased(Key key)
{
	bool keyUp = glfwGetKey(GameSystems::GetWindow(),key) == GLFW_RELEASE;
	bool wasReleased = false;
	if (previousFramePressedButtons.size() > 0)
	{
		int x = 0;
	}
	if (previousFramePressedButtons.find(key) != previousFramePressedButtons.end())
	{
		wasReleased = true;
	} 
	return wasReleased; 
}

void Input::Keyboard::PrepareForPolling()
{
	//std::set<Input::Keyboard::Key> intersect;
	//std::set_intersection(currentFramePressedButtons.begin(),currentFramePressedButtons.end(),previousFramePressedButtons.begin(),previousFramePressedButtons.end(), std::inserter(intersect,intersect.begin()));
	previousFramePressedButtons = currentFramePressedButtons;
	currentFramePressedButtons.clear();
}

void Input::Keyboard::AddKeyDownState(Key key)
{
	currentFramePressedButtons.insert(key); 
}

