#include "logic.h"
#include "functions.h"

// Establecemos la l�gica del programa.
void logic( World& world )
{
	//creo el reloj del juego
	buildTime(world.time);

	if(world.states.gameStates == LOAD_LEVELS) {
		loadLevel(1, world.blocks);
	}

	//Control de los estados del teclado
	switch(world.states.playerStates) {
		case TOLEFT:
			if(world.ship.position.x >= 0)
			{
				world.ship.position.x -= spaceMove(world.lastTime, SPEEDSHIP);
			}

			world.states.playerStates = NONE;

			break;

		case TORIGTH:
			if((world.ship.position.x + world.ship.width) <= 500)
			{
				world.ship.position.x += spaceMove(world.lastTime, SPEEDSHIP);
			}

			world.states.playerStates = NONE;

			break;

	}

	//Control de los estados de la pelota

	if(world.states.gameStates == START) {
		
		if(shockWall(world.includesBall, world.wall)) {
			if(world.wall == Walls::RIGHT) {
				world.states.ballStatesX = TOLEFT;


			}
			else if(world.wall == Walls::LEFT) {
				world.states.ballStatesX = TORIGTH;
			}
			else if(world.wall == Walls::TOP) {
				world.states.ballStatesY = TODOWN;
			}

		}
		
		//Guardo la posicion actual de la pelota y el cuadrado que lo engloba
		Ball ballCurrent = world.ball;
		Box includesBallCurrent = world.includesBall;

		//Muevo la pelota auxiliar a la siguiente posicion y establezco su nuevo includesBall
		moveBall(ballCurrent, world.states, world.lastTime);

		setSquareIncludesBall(ballCurrent, includesBallCurrent);
		
		//Compruebbo si en esa nueva posicion hay colision con la nave
		//En caso afirmativo establezco el estado para que la pelota suba
		if(checkCollision(includesBallCurrent, world.ship)) {
			world.states.ballStatesY = TOTOP;
		}
		
		
		//Gestion de choques con los bloques

		int size = world.blocks.size();

		for(int i = 0; i < size; i++) {
			if(world.blocks[i].numberOfImpacts > 0) {
				if(checkCollision(includesBallCurrent, world.blocks[i].form)) {
					if(world.blocks[i].numberOfImpacts > 1) {
						world.blocks[i].form.color = WHITE;
					}
					world.blocks[i].numberOfImpacts--;

					if(world.states.ballStatesY == TOTOP) {
						world.states.ballStatesY = TODOWN;
					} else {
						world.states.ballStatesY = TOTOP;
					}
				}
			}
		}


		//muevo la pelota
		moveBall(world.ball, world.states, world.lastTime);


		
	
	
	}else {
		world.ball.position.x = world.ship.position.x + (world.ship.width / 2);
	}


	setSquareIncludesBall(world.ball, world.includesBall);	

	getLastTime(world);
}