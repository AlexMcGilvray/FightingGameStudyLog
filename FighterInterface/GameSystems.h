#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "IUpdatable.h"
#include "IRenderable.h"
#include <vector>


namespace GameSystems
{
	GLFWwindow * GetWindow();

	class State : public IUpdatable, public IRenderable
	{
	public:
		State(void);
		virtual ~State(void);
		virtual void Init();
		virtual void Update();
		virtual void UpdateGUI();
		virtual void Render(); 

	private : 
		bool firstUpdate;
	};

	void ChangeState(State * newState);
	void InitGameSystems();
	void Start();
}

