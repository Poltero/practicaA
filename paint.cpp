#include "paint.h"
#include "functions.h"

// Utilizamos esta función sólo para pintar en pantalla. La lógica del programa debe ir en logic
void paint( const World& world ) 
{
	// La pantalla tiene unas dimensiones de 500x500
	changeColor(WHITE);
	plot(0, 0);		// Punto inferior izquierdo
	plot(500, 500); // Punto superior derecho
	plot(499, 0);	// Punto inferior derecho
	plot(0, 499);	// Punto superior izquierdo

	/*changeColor(RED);
	drawQuad(100, 100, 25, 50);

	changeColor(GREEN);
	drawCircle(200, 200, 25);*/

	// Cualquier número que se salga de este margen no se mostrará por pantalla

	//dibujar las estrellas
	changeColor(WHITE);

	paintStars(world.stars);

	//dibujar el cuadrado de informacion
	changeColor(world.infoBox.color);

	paintRectangle(world.infoBox);

	//dibujar el area del juego

	changeColor(world.gameBox.color);

	paintRectangle(world.gameBox);

	printText(10, 475, "TIME:", world.colorTime);
	printText(70, 475, world.time, world.colorTime);

	string chivato = int2string(world.ship.position.x);

	printText(200, 475, chivato, world.colorTime);

	//Pinto los bloques

	for(int i = 0; i < world.blocks.size(); i++) {
		if(world.blocks[i].numberOfImpacts > 0) {
		
			changeColor(world.blocks[i].form.color);

			paintShip(world.blocks[i].form);
		}
	}

	//pintar nave
	paintShip(world.ship);

	//paintShip(world.prueba);

	//plot(215 + world.ship.width, 40);
	//plot(0, 499);

	//pintar pelota
	paintBall(world.ball);

	//dump
	/*string coordenadaX = int2string(world.ship.position.x);
	string limitX = int2string(world.ship.position.x + world.ship.width);

	printText(150, 475, coordenadaX, world.colorTime);
	printText(200, 475, limitX, world.colorTime);*/

	plot(world.includesBall.position.x, world.includesBall.position.y);

	/*if(checkCollision2(world.includesBall, world.ship))
	{
		printText(300, 475, "colision!", world.colorTime);
	}*/


}
