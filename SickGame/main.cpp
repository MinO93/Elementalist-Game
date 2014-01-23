#include "Game.h"

#include "MemoryLeak.h"

int main( )
{

	#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif	

	Game game;
	game.Run();

    return 0;
}