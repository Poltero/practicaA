#include "functions.h"
#include <fstream>
#include <iostream>

using namespace std;

void paintRectangle(Box box)
{
	float posX;
	float posY = box.position.y;
	float endY = posY - box.height;

	for(;posY >= endY;posY--){
		posX = box.position.x;
		if(posY == endY || posY == box.position.y){
			for(;posX <= box.width;posX++){
				plot(posX,posY);
			}
		}else{
			plot(box.position.x,posY);
			plot(box.width,posY);
		}
	}
}

void generateStars(const string& nameFile)
{
	ofstream file;
	int x, y, i = 0;

	file.open(nameFile);

	if(file.is_open())
	{
		while(i <= 250)
		{
			x = randomInt() % 499;
			y = randomInt() % 499;

			file << x << endl << y;

			if(i != 250) file << endl;

			i++;
		}

		file.close();

	}
}

void getStars(const string& nameFile, Star*& starFirst)
{
	ifstream file;
	Point point;

	file.open(nameFile);

	if(file.is_open())
	{
		while(!file.eof())
		{
			file >> point.x;
			file >> point.y;

			addStar(point, starFirst);
		}

		file.close();
	}
}

void addStar(Point point, Star*& starFirst)
{
	Star* starItem = new Star;
	starItem->point.x = point.x;
	starItem->point.y = point.y;

	if(starFirst != NULL)
	{
		starItem->next = starFirst;
	}
	else
	{
		starItem->next = NULL;
	}

	starFirst = starItem;
}

void paintStars(Star* starFirst)
{
	if(starFirst != NULL)
	{
		Star* ptr = starFirst;

		while(ptr != NULL)
		{
			plot(ptr->point.x, ptr->point.y);

			ptr = ptr->next;
		}
	}
}

void buildTime(string &timeString)
{
	int hours, seconds, minutes;
	string segString, minString, hourString;

	seconds = getTime() / 1000;
	minutes = seconds / 60;
	seconds = seconds % 60;
	hours = minutes / 60;
	minutes = minutes % 60;


	segString = int2string(seconds);
	minString = int2string(minutes);
	hourString = int2string(hours);

	if(seconds < 10)
	{
		segString = "0" + segString;
	}
	if(minutes < 10)
	{
		minString = "0" + minString;
	}
	if(hours < 10)
	{
		hourString = "0" + hourString;
	}

	timeString = hourString + ":" + minString + ":" + segString;
}

vector<Block> loadLevel(int level, vector<Block>& blocks) {
	ifstream file;

	int dato, posicionX = 20, posicionY = 400, lastPosicionY = 0, lastPosicionX = 0;

	string levelFile = "nivel_";
	levelFile.append("1.txt");

	file.open(levelFile);

	if(file.is_open())
	{
		while(!file.eof())
		{
			file >> dato;

			Block block;

			Color color = (Color)((randomInt() % 7) + 2);

			if(dato == 1) {
				block.form.position.x = posicionX;
				block.form.position.y = posicionY;
				block.form.width = 40;
				block.form.height = 20;
				block.numberOfImpacts = 1;
				block.form.color = color;

				posicionX += (block.form.width + 2);

				lastPosicionX = block.form.width;
				lastPosicionY = block.form.height;

				blocks.push_back(block);
			}
			else if(dato == 2) {
				block.form.position.x = posicionX;
				block.form.position.y = posicionY;
				block.form.width = 82;
				block.form.height = 20;
				block.numberOfImpacts = 3;
				block.form.color = color;

				posicionX += (block.form.width + 2);

				lastPosicionX = block.form.width;
				lastPosicionY = block.form.height;

				blocks.push_back(block);
			}
			else if(dato == 0) {
				posicionX += (lastPosicionX + 2);
			}
			else if(dato == 9) {
				posicionY -= (lastPosicionY + 2);
				posicionX = 20;
			}

			
			
		}

		file.close();
	}

	return blocks;
}

void paintShip(Box ship)
{
	changeColor(ship.color);
	drawQuad(ship.position.x, ship.position.y, ship.width, ship.height);
}

void paintBall(Ball ball)
{
	changeColor(ball.color);
	drawCircle(ball.position.x, ball.position.y, ball.radius);
}

float spaceMove(float lastime)
{
	float timepassed = getTime() - lastime;

	timepassed = timepassed / 1000;

	return (speed * timepassed);
}

void getLastTime(World &world)
{
	world.lastTime = getTime();
}

bool shockWall(Box includesBall, int &wall)
{
	bool shock = false;

	if((includesBall.position.x + includesBall.width) > 500)
	{
		wall = Walls::RIGHT;
		shock = true;
	}
	else if(includesBall.position.x < 0)
	{
		wall = Walls::LEFT;
		shock = true;
	}
	else if(includesBall.position.y > 460)
	{
		wall = Walls::TOP;
		shock = true;
	}

	else if(includesBall.position.y < 0)
	{
		wall = Walls::DOWN;
		shock = true;
	}

	return shock;
}

void moveBall(Ball& ball, States states, int lastime)
{
	float space = spaceMove(lastime);

	switch(states.ballStatesX) {
		case TOLEFT:
			ball.position.x -= space;
			break;
		case TORIGTH:
			ball.position.x += space;
			break;
	}

	switch(states.ballStatesY) {
		case TOTOP:
			ball.position.y += space;
			break;
		case TODOWN:
			ball.position.y -= space;
			break;
	}
}

void setSquareIncludesBall(Ball& ball, Box& includesBall)
{
	includesBall.position.x = ball.position.x - ball.radius;
	includesBall.position.y = ball.position.y + ball.radius;
}

bool checkCollision(Box includesBall, Box rectangle)
{
	//Lados de los rectangulos
	float leftIncludesBall, leftRectangle;
	float rightIncludesBall, rightRectangle;
	float topIncludesBall, topRectangle;
	float bottomIncludesBall, bottomRectangle;

	//Calcular los lados del includesBall
	leftIncludesBall = includesBall.position.x;
	rightIncludesBall = includesBall.position.x + includesBall.width;
	topIncludesBall = includesBall.position.y;
	bottomIncludesBall = includesBall.position.y + includesBall.height;

	//calcular los lados del rectangle
	leftRectangle = rectangle.position.x;
	rightRectangle = rectangle.position.x + rectangle.width;
	topRectangle = rectangle.position.y;
	bottomRectangle = rectangle.position.y + rectangle.height;

	if(bottomIncludesBall <= topRectangle) {
		return false;
	}
	if(topIncludesBall >= bottomRectangle) {
		return false;
	}
	if(rightIncludesBall <= leftRectangle) {
		return false;
	}
	if(leftIncludesBall >= rightRectangle) {
		return false;
	}


	return true;

}

/*bool checkCollision2(Box includesBall, Box rectangle)
{
	Point maxIncludesBall, minIncludesBall, maxRectangle, minRectangle, maxPointCollision, minPointCollision;

	minIncludesBall = includesBall.position;
	maxIncludesBall.x = includesBall.position.x + includesBall.width;
	maxIncludesBall.y = includesBall.position.y - includesBall.height;

	minRectangle = rectangle.position;
	maxRectangle.x = rectangle.position.x + rectangle.width;
	maxRectangle.y = rectangle.position.y - rectangle.height;

	maxPointCollision = max(minIncludesBall, minRectangle);
	minPointCollision = min(maxIncludesBall, maxRectangle);

	/*if(minIncludesBall.x < maxRectangle.x && maxIncludesBall.x > minRectangle.x)
	{
		if(minIncludesBall.y > maxRectangle.y && minIncludesBall.y < maxRectangle.y)
		{
			return true;
		}
	}

	if(maxPointCollision.x < minPointCollision.x)
	{
		return true;
	}

	return false;
	
}*/

Point max(Point p1, Point p2)
{
	if(p1.x <= p2.x || p1.y <= p2.y)
	{
		return p2;
	}
	else
	{
		return p1;
	}
}

Point min(Point p1, Point p2)
{
	if(p1.x >= p2.x || p1.y >= p2.y)
	{
		return p2;
	}
	else
	{
		return p1;
	}
}

void log(const string msg)
{    
    ofstream out;

	out.open("logfile.txt",ios::ate);

	if(out.is_open())
	{
		out << msg << "\n";

		out.close();
	}
}