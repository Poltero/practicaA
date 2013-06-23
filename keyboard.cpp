#include "keyboard.h"

// Eventos de teclado
void keyPress( const KeyType key, World& world )
{
	if( key == KEY_HALT)
	{
		exit(0); // Salimos del programa
	}
	else if(key == KEY_LEFT)
	{
		world.states.stateMoveLeft = true;
	}
	else if(key == KEY_RIGHT)
	{
		world.states.stateMoveRight = true;
	}
	else if(key == KEY_FIRE)
	{
		world.states.stateStartGame = true;
	}
}