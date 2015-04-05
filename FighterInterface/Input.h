#pragma once 
#include <map>
#include <string>
 
namespace Input
{  
	namespace VirtualInput
	{
		enum InputState
		{
			VIRTUAL_KEY_NOT_POLLED = -1, 
			VIRTUAL_KEY_UP = 0,
			VIRTUAL_KEY_DOWN = 1,
			VIRTUAL_KEY_RELEASED = 2,
			VIRTUAL_KEY_PRESSED = 3
		};
	
		enum InputValue
		{
			UP = 0,
			DOWN,
			LEFT,
			RIGHT,
			BTN1,
			BTN2,
			START,
			FINAL_VIRTUAL_KEY_ENUM_VALUE,//this value is used to represent the number of items in this enum  
			NOT_MAPPED //We dont include this in the count
		};

		struct InputInfo
		{ 
			InputState inputMapping[FINAL_VIRTUAL_KEY_ENUM_VALUE]; 
			//timestamp
			//framestamp 
		};
	}
	using namespace VirtualInput;   

	class IController
	{
	public: 
		virtual InputInfo Poll() = 0; 
		virtual	void DebugDraw(){}
	};

	namespace Keyboard
	{
		typedef int Key; //keyboard key typedef. Right now maps to the GLFW types
	}
	
	void Init(); 
	IController * GetController(int playerNum);
	void SetController(IController * controller, int playerNum);
	//quick factory methods to create various types of controllers 
	IController * CreateDefaultKeyboardControllerPlayer1();
	IController * CreateDefaultKeyboardControllerPlayer2();

	IController * CreateDefaultJoystickControllerPlayer1();
	IController * CreateDefaultJoystickControllerPlayer2();
}