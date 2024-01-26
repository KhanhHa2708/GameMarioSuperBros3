#pragma once
#pragma once
#pragma once
#include "GameObject.h"

#define LEVEL_RED_KOOPA_WING	1
#define LEVEL_RED_KOOPA	0

#define RED_KOOPA_GRAVITY 0.0007f
#define RED_KOOPA_WALKING_SPEED 0.05f
#define RED_KOOPA_JUMPING_SPEED 0.1f
#define RED_KOOPA_FLYING_SPEED 0.25f

#define RED_KOOPA_BBOX_WIDTH 16
#define RED_KOOPA_BBOX_HEIGHT 27
#define RED_KOOPA_WING_BBOX_WIDTH 20
#define RED_KOOPA_WING_BBOX_HEIGHT 27
#define RED_KOOPA_BBOX_HEIGHT_DIE 7

#define RED_KOOPA_DIE_TIMEOUT 500

#define RED_KOOPA_STATE_WALKING 100
#define RED_KOOPA_STATE_DIE 200
#define RED_KOOPA_STATE_JUMPING 101
#define RED_KOOPA_STATE_FLYING 102
#define	RED_KOOPA_STATE_SHELL 103

#define	RED_KOOPA_STATE_SHELL_LEFT 104
#define	RED_KOOPA_STATE_SHELL_RIGHT 105

#define ID_ANI_RED_KOOPA_WALKING_LEFT 7000
#define ID_ANI_RED_KOOPA_WALKING_RIGHT 7001
#define ID_ANI_RED_KOOPA_DIE 7002
#define ID_ANI_RED_KOOPA_WING_WALKING_LEFT 7003
#define ID_ANI_RED_KOOPA_WING_WALKING_RIGHT 7004


#define RED_KOOPA_WALK_DURATION 2500
#define RED_KOOPA_JUMP_DURATION 2000
#define RED_KOOPA_FLY_DURATION 1000



class CRedKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	int level;

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
	CRedKoopa(float x, float y, int level = 0);
	virtual void SetState(int state);

};