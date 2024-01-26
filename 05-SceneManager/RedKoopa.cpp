#include "RedKoopa.h"
#include "ColorBlock.h"
#include "debug.h"
#include "PlayScene.h"

CRedKoopa::CRedKoopa(float x, float y, int l) :CGameObject(x, y)
{
	level = l;
	this->ax = 0;
	this->ay = RED_KOOPA_GRAVITY;
	die_start = -1;
	nx = -1;
	SetState(RED_KOOPA_STATE_WALKING);
}


void CRedKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == LEVEL_RED_KOOPA_WING) {
		left = x - RED_KOOPA_WING_BBOX_WIDTH / 2;
		top = y - RED_KOOPA_WING_BBOX_HEIGHT / 2;
		right = left + RED_KOOPA_WING_BBOX_WIDTH;
		bottom = top + RED_KOOPA_WING_BBOX_HEIGHT;
	}
	else if (state == RED_KOOPA_STATE_DIE)
	{
		left = x - RED_KOOPA_BBOX_WIDTH / 2;
		top = y - RED_KOOPA_BBOX_HEIGHT / 2;
		right = left + RED_KOOPA_BBOX_WIDTH;
		bottom = top + RED_KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - RED_KOOPA_BBOX_WIDTH / 2;
		top = y - RED_KOOPA_BBOX_HEIGHT / 2;
		right = left + RED_KOOPA_BBOX_WIDTH;
		bottom = top + RED_KOOPA_BBOX_HEIGHT;
	}
}

void CRedKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CRedKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CRedKoopa*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	if (e->nx != 0)
	{
		vx = nx * vx;
		nx = -nx;
	}

}

void CRedKoopa::SetLevel(int l)
{
	level = l;
}

void CRedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == RED_KOOPA_STATE_DIE) && (GetTickCount64() - die_start > RED_KOOPA_DIE_TIMEOUT))
	{
		isDeleted = false;
		SetState(RED_KOOPA_STATE_SHELL);
		return;
	}

	//if (level == LEVEL_PARA_GOOMBA) CalcGoombaMove();

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CRedKoopa::Render()
{
	int aniId = -1;
	if (level == LEVEL_RED_KOOPA_WING && vx <= 0) {
		aniId = ID_ANI_RED_KOOPA_WING_WALKING_LEFT;
	}
	else if (level == LEVEL_RED_KOOPA_WING && vx > 0)
	{
		aniId = ID_ANI_RED_KOOPA_WING_WALKING_RIGHT;
	}
	else if (level == LEVEL_RED_KOOPA && vx <= 0) {
		aniId = ID_ANI_RED_KOOPA_WALKING_LEFT;
	}
	else if (level == LEVEL_RED_KOOPA && vx > 0)
	{
		aniId = ID_ANI_RED_KOOPA_WALKING_RIGHT;
	}
	if (state == RED_KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_RED_KOOPA_DIE;
	}
	else if (state == RED_KOOPA_STATE_SHELL)
	{
		aniId = ID_ANI_RED_KOOPA_DIE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CRedKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case RED_KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (RED_KOOPA_WING_BBOX_HEIGHT - RED_KOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		nx = 0;
		ay = 0;
		break;
	case RED_KOOPA_STATE_WALKING:
		vx = nx * RED_KOOPA_WALKING_SPEED;
		break;
	case RED_KOOPA_STATE_SHELL:
		vx = nx * RED_KOOPA_WALKING_SPEED;
		break;
	case RED_KOOPA_STATE_SHELL_LEFT:
		vx = -RED_KOOPA_WALKING_SPEED;
		break;
	case RED_KOOPA_STATE_SHELL_RIGHT:
		vx = RED_KOOPA_WALKING_SPEED;
		break;
	}
}