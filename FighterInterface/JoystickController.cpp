#include "JoystickController.h"
#include "GameSystems.h"
#include <GLFW/glfw3.h>
#include "package\imgui.h"
#include <exception>
 
using namespace Input;
using namespace Input::Joystick;
 

//Input::InputInfo Input::Joystick::JoystickController::Poll()
//{
//	InputInfo result;
//	int buttonCount = 0;
//	auto glfwButtons = glfwGetJoystickButtons	(1, &buttonCount);
//	//take the smaller of the two button arrays so we dont go out of bounds
//	int buttonIterations = JOYSTICK_HARDWARE_BUTTON_MAX < buttonCount ? JOYSTICK_HARDWARE_BUTTON_MAX : buttonCount;
//	buttonIterations = buttonIterations < FINAL_VIRTUAL_KEY_ENUM_VALUE ? buttonIterations : FINAL_VIRTUAL_KEY_ENUM_VALUE;
//	//zero out the result 
//	for (int i = 0; i < FINAL_VIRTUAL_KEY_ENUM_VALUE; ++i)
//	{
//		result.inputMapping[i] = VirtualInput::InputState::VIRTUAL_KEY_NOT_POLLED;
//	} 
//	//process buttons to get virtual key return
//	for (int i = 0; i < buttonIterations; ++i)
//	{ 
//		 //logic here
//		if (lastFrameHardwareButtons[i] == GLFW_PRESS && glfwButtons[i] == GLFW_RELEASE)
//		{
//			result.inputMapping[i] = VIRTUAL_KEY_RELEASED;
//		}
//		else if (lastFrameHardwareButtons[i] == GLFW_RELEASE && glfwButtons[i] == GLFW_PRESS)
//		{
//			result.inputMapping[i] = VIRTUAL_KEY_PRESSED;
//		}
//		else if (lastFrameHardwareButtons[i] == GLFW_PRESS && glfwButtons[i] == GLFW_PRESS)
//		{
//			result.inputMapping[i] = VIRTUAL_KEY_DOWN;
//		}
//		else if (lastFrameHardwareButtons[i] == GLFW_PRESS && glfwButtons[i] == GLFW_PRESS)
//		{
//			result.inputMapping[i] = VIRTUAL_KEY_UP;
//		}
//	} 
//	//copy buttons to last frame buttons
//	for (int i = 0; i < buttonIterations; ++i)
//	{
//		lastFrameHardwareButtons[i] = glfwButtons[i];
//	} 
//	return result;
//}

Input::InputInfo Input::Joystick::JoystickController::Poll()
{
	InputInfo result;
	int buttonCount = 0;
	auto glfwButtons = glfwGetJoystickButtons	(1, &buttonCount);
	//go through all glfw buttons and if the button is mapped then perform logic


	//zero out the result 
	for (int i = 0; i < FINAL_VIRTUAL_KEY_ENUM_VALUE; ++i)
	{
		result.inputMapping[i] = VirtualInput::InputState::VIRTUAL_KEY_NOT_POLLED;
	} 

	return result;
}

void Input::Joystick::JoystickController::DebugDraw()
{

}

int Input::Joystick::JoystickController::HardwareID()
{
	throw std::exception("not implemented");
	return 1;
}

void Input::Joystick::JoystickController::HardwareID(int val)
{

}
 
int Input::Joystick::JoystickRemapper::GetRemappedKey(int virtualKeyIdx)
{
	if (virtualKeyIdx > 0 && virtualKeyIdx < FINAL_VIRTUAL_KEY_ENUM_VALUE)
	{
		return remap[virtualKeyIdx];
	}
	else
	{
		//todo make assert interface
		throw std::exception("bwar, make an assert interface");
		return 0;
	}
}

Input::Joystick::JoystickRemapper::JoystickRemapper()
{
	 remap[UP] = 0;
	 remap[DOWN] = 1;
	 remap[LEFT] = 2;
	 remap[RIGHT] = 3;
	 remap[BTN1] = 4;
	 remap[BTN2] = 5;
	 remap[START] = 6; 
}

bool Input::Joystick::JoystickRemapper::IsButtonMapped(char glfwButton)
{
	for (int i = 0; i < FINAL_VIRTUAL_KEY_ENUM_VALUE;++i )
	{
		if (remap[i] == glfwButton)
		{
			return true;
		}
	}
	return false;
}
