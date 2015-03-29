#include "KeyboardController.h"
#include "GameSystems.h"
#include <GLFW/glfw3.h>
#include "package\imgui.h"

using namespace Keyboard;

Input::InputInfo KeyboardController::Poll()
{
	InputInfo result;
	//TODO : This algorithm only really works for button presses. I need to handle holding down the button too.

	for (int i = 0; i < FINAL_VIRTUAL_KEY_ENUM_VALUE; ++i)
	{
		Key key = mappingInfo[i].key;
		int idxToKey = GetVirtualKeyMappingToKey(key);
		if (idxToKey == KEY_NOT_MAPPED || idxToKey == KEY_NOT_FOUND)
		{
			result.inputMapping[i] = VirtualInput::InputState::VIRTUAL_KEY_NOT_POLLED;
			mappingInfo[i].state = KEY_UP; 
		}
		else
		{
			//we consider it pressed if one the press or release
			bool pressed = KeyPressed(key) ;
			bool released = KeyReleased(key);
			bool down = KeyDown(key);
			if (pressed)
			{
				result.inputMapping[i] = VirtualInput::InputState::VIRTUAL_KEY_PRESSED;
				mappingInfo[i].state = KEY_DOWN; 

			}
			else if (released)
			{ 
				result.inputMapping[i] = VirtualInput::InputState::VIRTUAL_KEY_RELEASED;
				mappingInfo[i].state = KEY_UP;
			}
			else if (down)
			{ 
				result.inputMapping[i] = VirtualInput::InputState::VIRTUAL_KEY_DOWN;
				mappingInfo[i].state = KEY_DOWN;
			}
			else 
			{ 
				result.inputMapping[i] = VirtualInput::InputState::VIRTUAL_KEY_UP;
				mappingInfo[i].state = KEY_UP;
			}
		} 
	} 
	return result;
}

bool KeyboardController::KeyDown(Key key)
{
	int idxToKey = GetVirtualKeyMappingToKey(key);
	if (idxToKey == KEY_NOT_MAPPED || idxToKey == KEY_NOT_FOUND)
	{
		return false;	 
	}
	return glfwGetKey(GameSystems::GetWindow(),key);
}

bool KeyboardController::KeyPressed(Key key)
{
	int idxToKey = GetVirtualKeyMappingToKey(key);
	if (idxToKey == KEY_NOT_MAPPED || idxToKey == KEY_NOT_FOUND)
	{
		return false;	 
	} 
	return glfwGetKey(GameSystems::GetWindow(),key) && !mappingInfo[idxToKey].state;
}

bool KeyboardController::KeyReleased(Key key)
{
	int idxToKey = GetVirtualKeyMappingToKey(key);
	if (idxToKey == KEY_NOT_MAPPED || idxToKey == KEY_NOT_FOUND)
	{
		return false;	 
	}
	return !glfwGetKey(GameSystems::GetWindow(),key) && mappingInfo[idxToKey].state;
}

KeyboardController::KeyboardController()
{
	for (int i = 0; i < FINAL_VIRTUAL_KEY_ENUM_VALUE; ++i)
	{
		KeyboardInfo pair(KEY_NOT_MAPPED,KEY_NOT_MAPPED);
		mappingInfo[i] = pair;
	}
}

int KeyboardController::GetVirtualKeyMappingToKey(Key key,bool previousInfo)
{
	KeyboardInfo * mapInfo; 

	mapInfo = mappingInfo; 
	for (int i = 0; i < FINAL_VIRTUAL_KEY_ENUM_VALUE; ++i)
	{
		if (mapInfo[i].key == key)
		{
			return i;
		}
	}
	return KEY_NOT_MAPPED;
}

std::string KeyboardController::DrawInputStateField(KeyboardController::KeyState state)
{
	std::string stateName; 
	switch (state)
	{ 
	case KEY_UP:
		stateName = "Up";
		break;
	case KEY_DOWN:
		stateName = "Down";
		break;
	default:
		stateName = "Not Polled";
		break;
	}
	return stateName;
}

void KeyboardController::DebugDraw()
{ 
	ImGui::Text("Up key : %s",DrawInputStateField( mappingInfo[UP].state).c_str());
	ImGui::Text("Down key : %s",DrawInputStateField( mappingInfo[DOWN].state).c_str());
	ImGui::Text("Left key : %s",DrawInputStateField( mappingInfo[LEFT].state).c_str());
	ImGui::Text("Right key : %s",DrawInputStateField( mappingInfo[RIGHT].state).c_str());
	ImGui::Text("Btn1 key : %s",DrawInputStateField( mappingInfo[BTN1].state).c_str());
	ImGui::Text("Btn2 key : %s",DrawInputStateField( mappingInfo[BTN2].state).c_str());
	ImGui::Text("Start key : %s",DrawInputStateField( mappingInfo[START].state).c_str());
} 

void KeyboardController::MapKeyToVirtualKey(Key key, InputValue vaule)
{
	mappingInfo[vaule].key = key;
}