#include "MenuState.h"
#include "package\imgui.h"
#include "Render.h"

namespace
{
	bool showWindow = true; 
}

MenuState::MenuState(void) { }
 
MenuState::~MenuState(void) { }

void MenuState::Update() { }

void MenuState::UpdateGUI()
{
	ImGui::Text("Hello, world!");  
	ImGui::Begin("Another Window", &showWindow, ImVec2(200,100));
	ImGui::Text("Hello");
	ImGui::End();
}

void MenuState::Render()
{
	Primitive_Debug_Quad test(10 ,10,0,100,100,0.5f,1.0f,0.5f);
	Primitive_Debug_Quad test2(200 ,200,0,100,100,0.5f,0.3f,0.1f);
	Render::DrawDebugQuad(test);
	Render::DrawDebugQuad(test2);
}
