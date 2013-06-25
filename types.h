#pragma once

const float SPEEDSHIP = 300.0;
const float SPEEDBALL = 220.0;


enum StatesTypes {
	NONE,
	LOAD_LEVELS,
	START,
	GAMEOVER,

	//States for player
	TOLEFT,
	TORIGTH,
	TODOWN,
	TOTOP,
	TOFIRE
};

struct States
{
	int playerStates;
	int ballStatesX;
	int ballStatesY;
	int gameStates;
};

struct Level
{
	string file;
	Color colorBlocks;
	int lives;
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

struct Block {
	Box form;
	int numberOfImpacts;
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

	vector<Block> blocks;
	vector<Level> levels;

	int numberLevel;
	int lives;
	int score;
};
