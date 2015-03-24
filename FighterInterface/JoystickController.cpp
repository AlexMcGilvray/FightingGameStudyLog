#include "JoystickController.h"
#include "GameSystems.h"
#include <GLFW/glfw3.h>
#include "package\imgui.h"
 
using namespace Input;
using namespace Input::Joystick;
 

Input::InputInfo Input::Joystick::JoystickController::Poll()
{
	InputInfo result;
 

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
 