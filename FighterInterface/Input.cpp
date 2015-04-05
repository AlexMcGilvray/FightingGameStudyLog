#include "Input.h" 
#include "GameSystems.h"
#include <GLFW/glfw3.h>
#include "package\imgui.h" 
#include "KeyboardController.h"
#include "JoystickController.h"

using namespace Input;

namespace
{
	IController * player1Controller = nullptr;
	IController * player2Controller = nullptr; 
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
	Keyboard::KeyboardController * controller = new Keyboard::KeyboardController();
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
	Keyboard::KeyboardController * controller = new Keyboard::KeyboardController();
	controller->MapKeyToVirtualKey(GLFW_KEY_UP,InputValue::UP);
	controller->MapKeyToVirtualKey(GLFW_KEY_DOWN,InputValue::DOWN);
	controller->MapKeyToVirtualKey(GLFW_KEY_LEFT,InputValue::LEFT);
	controller->MapKeyToVirtualKey(GLFW_KEY_RIGHT,InputValue::RIGHT);
	controller->MapKeyToVirtualKey(GLFW_KEY_I,InputValue::BTN1);
	controller->MapKeyToVirtualKey(GLFW_KEY_O,InputValue::BTN2);
	controller->MapKeyToVirtualKey(GLFW_KEY_P,InputValue::START);
	return controller;
} 

IController * Input::CreateDefaultJoystickControllerPlayer1()
{
	Joystick::JoystickController * controller = new Joystick::JoystickController(); 
	Joystick::JoystickRemapper qanba;
	qanba.MapButton(Input::UP,11);
	qanba.MapButton(Input::DOWN,13);
	qanba.MapButton(Input::LEFT,14);
	qanba.MapButton(Input::RIGHT,12);
	qanba.MapButton(Input::BTN1,2);
	qanba.MapButton(Input::BTN2,3);
	qanba.MapButton(Input::START,9);  
	controller->SetRemapper(qanba); 
	return controller;
}

IController * Input::CreateDefaultJoystickControllerPlayer2()
{
	Joystick::JoystickController * controller = new Joystick::JoystickController();
	return controller;
}
