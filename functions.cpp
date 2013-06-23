#include "functions.h"
#include <fstream>

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

bool shockWall(Ball ball, int &wall)
{
	bool shock = false;

	if(ball.position.x > 499)
	{
		wall = Walls::RIGHT;
		shock = true;
	}
	else if(ball.position.x < 1)
	{
		wall = Walls::LEFT;
		shock = true;
	}
	else if(ball.position.y > 459)
	{
		wall = Walls::TOP;
		shock = true;
	}

	else if(ball.position.y < 1)
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
		ball.position.x += space;
		break;
	case TORIGTH:
		ball.position.x -= space;
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

	/*if(!states.stateGameOver)
	{
		if(states.stateBallDirectionX && states.stateBallDirectionY)
		{
			ball.position.x += space;
			ball.position.y += space;
		}
		else
		{
			if(states.stateBallDirectionX)
			{
				ball.position.x += space;
			}
			else
			{
				ball.position.x -= space;
			}

			if(states.stateBallDirectionY)
			{
				ball.position.y += space;
			}
			else
			{
				ball.position.y -= space;
			}
		}
	}*/
}

void setSquareIncludesBall(Ball& ball, Box& includesBall)
{
	includesBall.position.x = ball.position.x - ball.radius;
	includesBall.position.y = ball.position.y + ball.radius;
}

bool checkCollision(Box includesBall, Box rectangle)
{
	float ballCooInicial, ballCooFinal, rectangleCooInicial, rectangleCooFinal;

	//eje X
	ballCooInicial = includesBall.position.x;
	ballCooFinal = includesBall.position.x + includesBall.width;

	rectangleCooInicial = rectangle.position.x;
	rectangleCooFinal = rectangle.position.x + rectangle.width;

	if(rectangleCooFinal < ballCooInicial || rectangleCooInicial > ballCooFinal)
	{
		return false;
	}

	//eje Y
	ballCooInicial = includesBall.position.y;
	ballCooFinal = includesBall.position.y + includesBall.width;

	rectangleCooInicial = rectangle.position.y;
	rectangleCooFinal = rectangle.position.y + rectangle.height;

	if(rectangleCooFinal < ballCooInicial || rectangleCooInicial > ballCooFinal)
	{
		return false;
	}

	return true;
}

bool checkCollision2(Box includesBall, Box rectangle)
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
	}*/

	if(maxPointCollision.x < minPointCollision.x)
	{
		return true;
	}

	return false;
	
}

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