/* Header for the Time class (Time.h) */
#include "cocos2d.h"
#include "GameOverScene.h"
USING_NS_CC;
#ifndef BALL_H  
#define BALL_H   
//  this header will not get included more than once
class Ball {
private:  // private section
	// private data members
	//Sprite image
	Sprite* sprite;   
	//Image File Path
	char *filename;
	//Ball tag
	int tag;   
	//Ball name
	String name; 

public:   // public section
	// public member function prototypes
	Ball(char *filename, int tag, String name);
	Sprite* getSprite() const;   
	int getTag() const; 
	void setTag1(int m); 
	String getName() const; 
	void setName(String name); 
	void setBall(char *filename, int tag, String name);
	void print() const; 
	//void doSomething(void (GameOverScene::*function)());
};  

#endif  // end of "#ifndef" block