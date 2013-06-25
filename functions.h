#include "init.h"

void paintRectangle(Box box);
void generateStars(const string& nameFile);
void getStars(const string& nameFile, Star*& starFirst);
void addStar(Point point, Star*& starFirst);
void paintStars(Star* starFirst);
void buildTime(string &timeString);
void paintShip(Box ship);
void paintBall(Ball ball);
void getLastTime(World &world);
float spaceMove(float lastime, float speed);
void moveBall(Ball& ball, States states, int lastime);
bool shockWall(Box includesBall, int &wall);
void log(const string msg);
void setSquareIncludesBall(Ball& ball, Box& includesBall);
bool checkCollision(Box includesBall, Box rectangle);
//bool checkCollision2(Box includesBall, Box rectangle);

vector<Block> loadLevel(Level level, vector<Block>& blocks);

Point max(Point p1, Point p2);
Point min(Point p1, Point p2);