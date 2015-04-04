#pragma once
#include "Input.h"
 
using namespace Input::VirtualInput; 
 
namespace Input
{
	namespace Joystick
	{ 
		//typedefs
		typedef unsigned char JoystickButton; 
		//forward declarations
		class JoystickRemapper;
		//constants
		const int JOYSTICK_HARDWARE_BUTTON_MAX = 10; //number of button indices we poll, currently an arbitrary value
		 

		
		class JoystickController : public IController
		{  
		public:
			virtual InputInfo Poll();
			virtual void DebugDraw();
			int HardwareID();
			void HardwareID(int val);
		private:
			int hardwareID;   
			char lastFrameHardwareButtons[JOYSTICK_HARDWARE_BUTTON_MAX];
		};

		class JoystickRemapper
		{
			InputValue remap[FINAL_VIRTUAL_KEY_ENUM_VALUE];
		public:
			int GetRemappedKey(int virtualKeyIdx);
		};


		//Todo add a joystick mapping system so people can write joystick data files to make custom JoystickButtonInfos
	} 
}
