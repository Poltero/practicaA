#pragma once

const float speed = 150.0;

struct States
{
	string playerStates;
	string gameStates;
};

struct Point
{
	float x;
	float y;
};

struct Box
{
	Point position;
	float width;
	float height;
	Color color;
};

struct Star
{
	Point point;
	Star* next;
};

enum Walls
{
	TOP,
	LEFT,
	RIGHT,
	DOWN
};

struct Ball
{
	Point position;
	float radius;
	Color color;
};

struct World
{
	Box infoBox;
	Box gameBox;

	States states; 

	Star* stars;
	string fileStars;
	string time;
	float lastTime;
	int wall;
	Color colorTime;

	Box ship;

	Box prueba;

	Ball ball;
	Box includesBall;
};
