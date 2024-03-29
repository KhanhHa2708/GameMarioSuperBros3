﻿﻿﻿#pragma once
#pragma once

#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "BulletPlant.h"

#define VENUS_WALKING_SPEED 0.06f;

#define VENUS_BBOX_WIDTH 16
#define VENUS_BBOX_HEIGHT 32

#define GREEN_BBOX_HEIGHT 27
//#define VENUS_BBOX_HEIGHT 27*3

#define VENUS_STATE_GOING_UP			 100
#define VENUS_STATE_GOING_DOWN			 200
#define VENUS_STATE_SHOOTING_UP			 300
#define VENUS_STATE_SHOOTING_DOWN		 400
#define VENUS_STATE_SEEING				 500
#define VENUS_STATE_STANDING_STILL		 600
#define VENUS_STATE_SLEEPING	700
#define VENUS_STATE_DIE 800


#define VENUS_ANI_SCORPION_DOWN_LEFT 725
#define VENUS_ANI_SCORPION_UP_LEFT 726
#define VENUS_ANI_SHOOTING_DOWN_LEFT 727
#define VENUS_ANI_SHOOTING_UP_LEFT 728


#define VENUS_ANI_SCORPION_DOWN_RIGHT 729
#define VENUS_ANI_SCORPION_UP_RIGHT 730
#define VENUS_ANI_SHOOTING_DOWN_RIGHT 731
#define VENUS_ANI_SHOOTING_UP_RIGHT 732




#define GREEN_ANI_SCORPION_DOWN_LEFT 825
#define GREEN_ANI_SCORPION_UP_LEFT 825
#define GREEN_ANI_SHOOTING_DOWN_LEFT 827
#define GREEN_ANI_SHOOTING_UP_LEFT 828




#define GREEN_ANI_SCORPION_DOWN_RIGHT 829
#define GREEN_ANI_SCORPION_UP_RIGHT 830
#define GREEN_ANI_SHOOTING_DOWN_RIGHT 831
#define GREEN_ANI_SHOOTING_UP_RIGHT 832


#define FIRE 1
#define GREEN 2

class VenusFireTrap : public CGameObject
{
protected:

	float l_safe;
	float t_safe;
	float r_safe;
	float b_safe;

	//int type = GREEN;
	int type = FIRE;

	vector<LPGAMEOBJECT> listFireball;

	float min_y = y;
	float max_y = y;


	ULONGLONG time_interval;

	float ax;
	float ay;
	LPGAMEOBJECT player;
	ULONGLONG die_start;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; }; //hàm cha trả về 0
	virtual int IsBlocking() { return 0; } // hàm cha trả về 1
	

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	VenusFireTrap(float x, float y, LPGAMEOBJECT mario, int type);
	virtual void SetState(int state);

	void RenderToType(int type, int& aniId);

	bool CheckInArea(float l, float t, float r, float b);
};