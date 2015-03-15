#include "Input.h"

#include "GameSystems.h"
#include <GLFW/glfw3.h>
#include "package\imgui.h"
#include <gamepad/Gamepad.h>

using namespace Input;

namespace
{
	IController * player1Controller = nullptr;
	IController * player2Controller = nullptr; 
}

Input::InputInfo Input::KeyboardController::Poll()
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

bool Input::KeyboardController::KeyDown(Key key)
{
	int idxToKey = GetVirtualKeyMappingToKey(key);
	if (idxToKey == KEY_NOT_MAPPED || idxToKey == KEY_NOT_FOUND)
	{
		return false;	 
	}
	return glfwGetKey(GameSystems::GetWindow(),key);
}

bool Input::KeyboardController::KeyPressed(Key key)
{
	int idxToKey = GetVirtualKeyMappingToKey(key);
	if (idxToKey == KEY_NOT_MAPPED || idxToKey == KEY_NOT_FOUND)
	{
		return false;	 
	} 
	return glfwGetKey(GameSystems::GetWindow(),key) && !mappingInfo[idxToKey].state;
}

bool Input::KeyboardController::KeyReleased(Key key)
{
	int idxToKey = GetVirtualKeyMappingToKey(key);
	if (idxToKey == KEY_NOT_MAPPED || idxToKey == KEY_NOT_FOUND)
	{
		return false;	 
	}
	return !glfwGetKey(GameSystems::GetWindow(),key) && mappingInfo[idxToKey].state;
}

Input::KeyboardController::KeyboardController()
{
	for (int i = 0; i < FINAL_VIRTUAL_KEY_ENUM_VALUE; ++i)
	{
		KeyboardInfo pair(KEY_NOT_MAPPED,KEY_NOT_MAPPED);
		mappingInfo[i] = pair;
	}
}

int Input::KeyboardController::GetVirtualKeyMappingToKey(Key key,bool previousInfo)
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

std::string Input::KeyboardController::DrawInputStateField(KeyboardController::KeyState state)
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

void Input::KeyboardController::DebugDraw()
{ 
	  ImGui::Text("Up key : %s",DrawInputStateField( mappingInfo[UP].state).c_str());
	  ImGui::Text("Down key : %s",DrawInputStateField( mappingInfo[DOWN].state).c_str());
	  ImGui::Text("Left key : %s",DrawInputStateField( mappingInfo[LEFT].state).c_str());
	  ImGui::Text("Right key : %s",DrawInputStateField( mappingInfo[RIGHT].state).c_str());
	  ImGui::Text("Btn1 key : %s",DrawInputStateField( mappingInfo[BTN1].state).c_str());
	  ImGui::Text("Btn2 key : %s",DrawInputStateField( mappingInfo[BTN2].state).c_str());
	  ImGui::Text("Start key : %s",DrawInputStateField( mappingInfo[START].state).c_str());
}



void Input::KeyboardController::MapKeyToVirtualKey(Key key, InputValue vaule)
{
	mappingInfo[vaule].key = key;
}

IController * Input::GetController(int playerNum)
{
	if (playerNum == 1)
	{
		return player1Controller; 
	}
	if (playerNum == 2)
	{
		return player2Controller;
	}
	else
	{
		return nullptr;
	}
}

void Input::SetController(IController * controller, int playerNum) 
{ 
	if (playerNum == 1)
	{ 
		if (player1Controller != nullptr)
		{
			delete player1Controller;
		}
		player1Controller = controller; 
	}
	if (playerNum == 2)
	{	
		if (player2Controller != nullptr)
		{
			delete player2Controller;
		}
		player2Controller = controller;
	}  
}

IController * Input::CreateDefaultKeyboardControllerPlayer1()
{
	KeyboardController * controller = new KeyboardController();
	controller->MapKeyToVirtualKey(GLFW_KEY_W,InputValue::UP);
	controller->MapKeyToVirtualKey(GLFW_KEY_S,InputValue::DOWN);
	controller->MapKeyToVirtualKey(GLFW_KEY_A,InputValue::LEFT);
	controller->MapKeyToVirtualKey(GLFW_KEY_D,InputValue::RIGHT);
	controller->MapKeyToVirtualKey(GLFW_KEY_G,InputValue::BTN1);
	controller->MapKeyToVirtualKey(GLFW_KEY_H,InputValue::BTN2);
	controller->MapKeyToVirtualKey(GLFW_KEY_J,InputValue::START);
	return controller;
}

IController * Input::CreateDefaultKeyboardControllerPlayer2()
{
	KeyboardController * controller = new KeyboardController();
	controller->MapKeyToVirtualKey(GLFW_KEY_UP,InputValue::UP);
	controller->MapKeyToVirtualKey(GLFW_KEY_DOWN,InputValue::DOWN);
	controller->MapKeyToVirtualKey(GLFW_KEY_LEFT,InputValue::LEFT);
	controller->MapKeyToVirtualKey(GLFW_KEY_RIGHT,InputValue::RIGHT);
	controller->MapKeyToVirtualKey(GLFW_KEY_I,InputValue::BTN1);
	controller->MapKeyToVirtualKey(GLFW_KEY_O,InputValue::BTN2);
	controller->MapKeyToVirtualKey(GLFW_KEY_P,InputValue::START);
	return controller;
}




//Input::InputInfo Input::JoystickController::Poll()
//{
//
//}

Input::VirtualInput::InputInfo Input::JoystickController::Poll()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Input::JoystickController::DebugDraw()
{
	throw std::logic_error("The method or operation is not implemented.");
}
