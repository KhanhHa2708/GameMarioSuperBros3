#pragma once
#pragma once
#include "GameObject.h"

#define LEVEL_PARA_RED_GOOMBA	1
#define LEVEL_RED_GOOMBA	0

#define PARA_RED_GOOMBA_GRAVITY 0.0007f
#define PARA_RED_GOOMBA_WALKING_SPEED 0.05f
#define PARA_RED_GOOMBA_JUMPING_SPEED 0.1f
#define PARA_RED_GOOMBA_FLYING_SPEED 0.25f

#define PARA_RED_GOOMBA_BBOX_WIDTH 16
#define PARA_RED_GOOMBA_BBOX_HEIGHT 14
#define RED_PARA_GOOMBA_BBOX_WIDTH 20
#define RED_PARA_GOOMBA_BBOX_HEIGHT 24
#define RED_PARA_GOOMBA_BBOX_HEIGHT_DIE 7

#define PARA_RED_GOOMBA_DIE_TIMEOUT 500

#define PARA_RED_GOOMBA_STATE_WALKING 100
#define PARA_RED_GOOMBA_STATE_DIE 200
#define PARA_RED_GOOMBA_STATE_JUMPING 101
#define PARA_RED_GOOMBA_STATE_FLYING 102

#define ID_ANI_RED_GOOMBA_WALKING 6000
#define ID_ANI_PARA_RED_GOOMBA_DIE 6001
#define ID_ANI_PARA_RED_GOOMBA_WALKING 6002

#define PARA_RED_GOOMBA_WALK_DURATION 2500
#define PARA_RED_GOOMBA_JUMP_DURATION 2000
#define PARA_RED_GOOMBA_FLY_DURATION 1000


class CParaGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	int level;
	int step;

	ULONGLONG die_start;
	ULONGLONG timeEllapsed;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	int GetLevel() { return level; }
	void SetLevel(int l);
	CParaGoomba(float x, float y, int level = 0);
	virtual void SetState(int state);
	void CalcGoombaMove();
};