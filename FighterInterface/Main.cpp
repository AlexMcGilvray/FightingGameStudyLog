

#include "GameSystems.h"
#include "GameState.h"
 
 

int main()
{ 
	
	GameSystems::InitGameSystems();

	GameState * state = new GameState();
	 
	GameSystems::ChangeState(state); 

	GameSystems::Start();
 
}
 
 