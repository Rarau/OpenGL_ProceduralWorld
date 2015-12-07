#include "Engine.h"

int main(int argc, char **argv)
{	
	engine::GameManager *gameManager = &(engine::GameManager::GetGameManager());	
	gameManager->RunGameLoop();
	engine::GameManager::DestroyGameManager();
}
