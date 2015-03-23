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
	JoystickButtonInfo currentMappingInfo[FINAL_VIRTUAL_KEY_ENUM_VALUE];

	//algorithm
	//first get the current button state array
	//process inputinfo using the current and previous state arrays
	//copy the current state array into the previous state array 

	for (int i = 0; i < FINAL_VIRTUAL_KEY_ENUM_VALUE; ++i)
	{
		JoystickButtonInfo & buttonInfo = mappingInfo[i];
		bool foundButton = false;

		if (buttonInfo.button == JOYSTICK_BUTTON_UNINITIALIZED)
		{
			buttonInfo.state = BUTTON_NOT_MAPPED;
			continue;
		}
		for (int i = 0; i < buttonCount; ++i)
		{
			if (buttonInfo.button == i)
			{
				unsigned char bState =  glfwButtons[i];
				foundButton = true;
				buttonInfo.state = bState == GLFW_PRESS ? BUTTON_DOWN : BUTTON_UP;
			}
			if (!foundButton)
			{
				buttonInfo.state = BUTTON_NOT_FOUND;
			}
		} 
	}




	//using input info from last frame find the current input state
	for (int i = 0; i < FINAL_VIRTUAL_KEY_ENUM_VALUE; ++i)
	{
		JoystickButtonInfo & buttonInfo = mappingInfo[i];
		bool foundButton = false; 
		if (buttonInfo.button == JOYSTICK_BUTTON_UNINITIALIZED)
		{ 
			continue;
		}
		for (int i = 0; i < buttonCount; ++i)
		{
			if (buttonInfo.button == i)
			{
				unsigned char bState = glfwButtons[i]; 
				if (buttonInfo.state == BUTTON_DOWN)
				{

				}
				if (buttonInfo.state == BUTTON_UP)
				{

				}
			} 
		} 
	}
	
	for (int i = 0; i < FINAL_VIRTUAL_KEY_ENUM_VALUE; ++i)
	{
		JoystickButtonInfo & buttonInfo = mappingInfo[i];
		bool foundButton = false;
		
		if (buttonInfo.button == JOYSTICK_BUTTON_UNINITIALIZED)
		{
			buttonInfo.state = BUTTON_NOT_MAPPED;
			continue;
		}
		for (int i = 0; i < buttonCount; ++i)
		{
			if (buttonInfo.button == i)
			{
				unsigned char bState =  glfwButtons[i];
				foundButton = true;
				buttonInfo.state = bState == GLFW_PRESS ? BUTTON_DOWN : BUTTON_UP;
			}
			if (!foundButton)
			{
				buttonInfo.state = BUTTON_NOT_FOUND;
			}
		} 
	}

	return result;
}

void Input::Joystick::JoystickController::DebugDraw()
{
	/*ImGui::Text("Up key : %s",DrawInputStateField( mappingInfo[UP].state).c_str());
	ImGui::Text("Down key : %s",DrawInputStateField( mappingInfo[DOWN].state).c_str());
	ImGui::Text("Left key : %s",DrawInputStateField( mappingInfo[LEFT].state).c_str());
	ImGui::Text("Right key : %s",DrawInputStateField( mappingInfo[RIGHT].state).c_str());
	ImGui::Text("Btn1 key : %s",DrawInputStateField( mappingInfo[BTN1].state).c_str());
	ImGui::Text("Btn2 key : %s",DrawInputStateField( mappingInfo[BTN2].state).c_str());
	ImGui::Text("Start key : %s",DrawInputStateField( mappingInfo[START].state).c_str());*/
}

bool Input::Joystick::JoystickController::ButtonDown(JoystickButton button)
{
	return false;
}

bool Input::Joystick::JoystickController::ButtonPressed(JoystickButton button)
{
	return false;
}

bool Input::Joystick::JoystickController::ButtonReleased(JoystickButton button)
{
	return false;
}
