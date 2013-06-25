#include "init.h"
#include "functions.h"

// Inicialización de variables
void init( World& world )
{
	//inicializar infoBox
	world.infoBox.position.x = 0;
	world.infoBox.position.y = 500;
	world.infoBox.width = 500;
	world.infoBox.height = 40;
	world.infoBox.color = GREEN;

	//inicializar gameBox
	world.gameBox.position.x = 0;
	world.gameBox.position.y = 460;
	world.gameBox.width = 500;
	world.gameBox.height = 460;
	world.gameBox.color = YELLOW;

	//inicializar color time
	world.colorTime = GREEN;

	//inicializar posicion y valores de la nave
	world.ship.position.x = 215;
	world.ship.position.y = 10;
	world.ship.width = 65;
	world.ship.height = 20;
	world.ship.color = GREEN;

	//inicializar posicion y radio de la pelota
	world.ball.radius = 10;
	world.ball.color = BLUE;

	//inicializo el puntero a la coleccion de estrellas
	world.stars = NULL;
	//inicializo el nombre del fichero de las estrellas
	world.fileStars = "stars.txt";

	//llenar la coleccion de estrellas desde el fichero

	generateStars(world.fileStars);
	
	getStars(world.fileStars, world.stars);

	world.lastTime = 0;

	world.includesBall.width = world.ball.radius * 2;

	//estados del juego

	/*world.states.stateMoveLeft = false;
	world.states.stateMoveRight = false;
	world.states.stateStartGame = false;
	world.states.stateMoveBallTopLeft = false;
	world.states.stateMoveBallTopRight = false;
	world.states.stateMoveBallBottomLeft = false;
	world.states.stateMoveBallBottomRight = false;
	world.states.stateGameOver = false;

	// true es derecha y false es izquierda

	world.states.stateBallDirectionX = true;

	//true el arriba y false es abajo
	world.states.stateBallDirectionY = true;*/

	world.prueba.position.x = 150;
	world.prueba.position.y = 200;
	world.prueba.width = 65;
	world.prueba.height = 20;
	world.prueba.color = RED;




	world.states.gameStates = LOAD_LEVELS;

	Level level1, level2, level3, level4;

	level1.file = "nivel_1.txt";
	level1.colorBlocks = (Color) -1;
	level1.lives = 2;
	world.levels.push_back(level1);
	
	
	world.numberLevel = 0;
}