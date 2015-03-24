#pragma once
#include "Input.h"
 
using namespace Input::VirtualInput; 
 
namespace Input
{
	namespace Joystick
	{ 
		const int JOYSTICK_HARDWARE_BUTTON_MAX = 10; //number of button indices we poll, currently an arbitrary value
		typedef unsigned char JoystickButton;  
		class JoystickController : public IController
		{  
		public:
			virtual InputInfo Poll();
			virtual void DebugDraw();
			int HardwareID();
			void HardwareID(int val);
		private:
			int hardwareID;   
			char hardwareButtons[JOYSTICK_HARDWARE_BUTTON_MAX];
		};  

		//Todo add a joystick mapping system so people can write joystick data files to make custom JoystickButtonInfos
	} 
}
