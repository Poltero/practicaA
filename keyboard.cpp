#include "keyboard.h"

// Eventos de teclado
void keyPress( const KeyType key, World& world )
{
	/*if( key == KEY_HALT)
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
	}*/

	switch(key) {
		case KEY_HALT:
			exit(0); //salimos del programa
			break;
		case KEY_LEFT:
			world.states.playerStates = TOLEFT;
			break;
		case KEY_RIGHT:
			world.states.playerStates = TORIGTH;
			break;
		case KEY_FIRE:
			//world.states.playerStates = TOFIRE;
			if(world.states.gameStates == NONE) {
				world.states.gameStates = START;
				world.states.ballStatesX = TOLEFT;
				world.states.ballStatesY = TOTOP;
			}
			break;
	}
}