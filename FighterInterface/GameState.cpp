#include "GameState.h"
#include "package\imgui.h"
#include "Render.h" 
#include "Input.h"
#include "Character.h"
#include "GameData.h"
#include "Debug.h"

using namespace Input;

//Logic for what happens when an attack hitbox intersects with an opposing character
void HandleCharacterHitInteractions( Character * const character,  Character * const character2);
 
GameState::GameState(void)
{
	State::State(); 
}
 
GameState::~GameState(void)
{
} 

void HandleCharacterHitInteractions( Character * const attackingCharacter,  Character * const hitTestCharacter)
{
	for (int i = 0; i < attackingCharacter->hitboxesAttack.colliders.size(); ++i)
	{
		if (attackingCharacter->hitboxesAttack.colliders[i].Overlaps(hitTestCharacter->hitboxBody))
		{ 
			bool hasEmittedDamage = attackingCharacter->state.CurrentState()->HasEmittedDamage();
			if (!hasEmittedDamage)
			{
				Debug::Logger::Log("Player 2 hit!");
				hitTestCharacter->characterData->MutableData()->health -= attackingCharacter->hitboxesAttack.colliders[i].damage;
				hitTestCharacter->state.PushState(HIT_STUN);
				hitTestCharacter->characterData->MutableData()->knockBack = attackingCharacter->hitboxesAttack.colliders[i].knockback;
				attackingCharacter->state.CurrentState()->HasEmittedDamage(true);
			} 
		}
	}
}

void GameState::Update()
{
	State::Update(); 

	if (character->x > character2->x)
	{
		character->Facing(CharacterFacing::LEFT);
		character2->Facing(CharacterFacing::RIGHT);
	}
	else
	{
		character2->Facing(CharacterFacing::LEFT);
		character->Facing(CharacterFacing::RIGHT);
	}
	character->Update();
	character2->Update();
	if (character->y > GameData::LevelGlobalValues::GroundPlaneY())
	{ 
		character->y = GameData::LevelGlobalValues::GroundPlaneY();
		character->velocityY = 0;
	}

	if (character2->y > GameData::LevelGlobalValues::GroundPlaneY())
	{ 
		character2->y = GameData::LevelGlobalValues::GroundPlaneY();
		character2->velocityY = 0;
	}

	HandleCharacterHitInteractions(character,character2);
	HandleCharacterHitInteractions(character2,character);
}



void GameState::UpdateGUI()
{
	ImGui::Text("Hello, world!"); 
	//raw input debug
	if (Input::GetController(1) != nullptr)
	{
		ImGui::Begin("Raw Input : Player 1",nullptr,ImVec2(194,168));
		character->controller->DebugDraw();
		ImGui::End();
	}
	if (Input::GetController(2) != nullptr)
	{
		ImGui::Begin("Raw Input : Player 2",nullptr,ImVec2(194,168));
		character2->controller->DebugDraw();
		ImGui::End();
	}
	//character current state
	ImGui::Begin("Character State",nullptr,ImVec2(194,168));
	ImGui::Text("Player 1 State  : %s",character->state.CurrentState()->Name());
	ImGui::Text("Player 1 Facing : %s",character->FacingToString());
	ImGui::Text("Player 2 State  : %s",character2->state.CurrentState()->Name());
	ImGui::Text("Player 2 Facing : %s",character2->FacingToString());
	ImGui::End();
}

void GameState::Render()
{
	Primitive_Debug_Quad test(0 ,700,1280,100,0.5f,1.0f,0.5f); 
	Render::DrawDebugQuad(test); 
	character->Render();
	character2->Render();
}

void GameState::Init()
{
	State::Init();
	controller = Input::CreateDefaultKeyboardControllerPlayer1();
	character = new Character(this);
	character->x = 300;
	character->controller = controller;
	Input::SetController(controller,1);

	controller2 = Input::CreateDefaultKeyboardControllerPlayer2();
	character2 = new Character(this);
	character2->x = 800;
	character2->controller = controller2;
	Input::SetController(controller2,2);
}
