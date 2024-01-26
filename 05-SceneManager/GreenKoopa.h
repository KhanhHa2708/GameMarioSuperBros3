#pragma once
#pragma once
#include "GameObject.h"

#define LEVEL_GREEN_KOOPA_WING	1
#define LEVEL_GREEN_KOOPA	0

#define GREEN_KOOPA_GRAVITY 0.0007f
#define GREEN_KOOPA_WALKING_SPEED 0.05f
#define GREEN_KOOPA_JUMPING_SPEED 0.1f
#define GREEN_KOOPA_FLYING_SPEED 0.25f

#define GREEN_KOOPA_BBOX_WIDTH 16
#define GREEN_KOOPA_BBOX_HEIGHT 27
#define GREEN_KOOPA_WING_BBOX_WIDTH 20
#define GREEN_KOOPA_WING_BBOX_HEIGHT 27
#define GREEN_KOOPA_BBOX_HEIGHT_DIE 7

#define GREEN_KOOPA_DIE_TIMEOUT 500

#define GREEN_KOOPA_STATE_WALKING 100
#define GREEN_KOOPA_STATE_DIE 200
#define GREEN_KOOPA_STATE_JUMPING 101
#define GREEN_KOOPA_STATE_FLYING 102

#define ID_ANI_GREEN_KOOPA_WALKING_LEFT 8000
#define ID_ANI_GREEN_KOOPA_WALKING_RIGHT 8001
#define ID_ANI_GREEN_KOOPA_DIE 8002
#define ID_ANI_GREEN_KOOPA_WING_WALKING_LEFT 8003
#define ID_ANI_GREEN_KOOPA_WING_WALKING_RIGHT 8004


#define GREEN_KOOPA_WALK_DURATION 2500
#define GREEN_KOOPA_JUMP_DURATION 2000
#define GREEN_KOOPA_FLY_DURATION 1000



class CGreenKoopa : public CGameObject
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
	CGreenKoopa(float x, float y, int level = 0);
	virtual void SetState(int state);
	
};