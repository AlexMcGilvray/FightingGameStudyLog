#include "JoystickController.h"
#include "GameSystems.h"
#include <GLFW/glfw3.h>
#include "package\imgui.h"
 
using namespace Input;
using namespace Input::Joystick;
 

Input::InputInfo Input::Joystick::JoystickController::Poll()
{
	InputInfo result;
	int buttonCount = 0;
	auto glfwButtons = glfwGetJoystickButtons	(hardwareID, &buttonCount);
	//take the smaller of the two button arrays so we dont go out of bounds
	int buttonIterations = JOYSTICK_HARDWARE_BUTTON_MAX < buttonCount ? JOYSTICK_HARDWARE_BUTTON_MAX : buttonCount;
	

	//process buttons to get virutal key return
	for (int i = 0; i < buttonIterations; ++i)
	{ 
		 //logic here
	}


	//copy buttons to last frame buttons
	for (int i = 0; i < buttonIterations; ++i)
	{
		lastFrameHardwareButtons[i] = glfwButtons[i];
	}


	return result;
}
 