#include "logic.h"
#include "functions.h"

// Establecemos la lógica del programa.
void logic( World& world )
{
	//creo el reloj del juego
	buildTime(world.time);

	if(world.states.gameStates == LOAD_LEVELS) {
		loadLevel(world.levels[world.numberLevel], world.blocks);
		world.lives = world.levels[world.numberLevel].lives;

		world.ball.position.y = 40;

		world.states.gameStates = NONE;
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
			world.score += 1;
		}
		
		
		//Gestion de choques con los bloques

		int size = world.blocks.size();

		for(int i = 0; i < size; i++) {
			if(world.blocks[i].numberOfImpacts > 0) {
				if(checkCollision(includesBallCurrent, world.blocks[i].form)) {
					if(world.blocks[i].numberOfImpacts > 1) {
						world.blocks[i].form.color = GRAY;
					}
					world.blocks[i].numberOfImpacts--;
					world.score += 10;

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
			else if(world.wall == Walls::DOWN) {
				if(world.lives > 0) {
					world.states.gameStates = NONE;
					world.ball.position.y = 40;
					world.lives--;
				} else {
					world.states.gameStates = GAMEOVER;
				}
			}

		}


		
	
	
	}else if(world.states.gameStates == GAMEOVER) {
		if(world.blocks.size() > 0) {
			world.blocks.erase(world.blocks.begin()+world.blocks.size()-1);
		}

		world.score = 0;
	}
	else {
		world.ball.position.x = world.ship.position.x + (world.ship.width / 2);
	}


	setSquareIncludesBall(world.ball, world.includesBall);	

	getLastTime(world);
}