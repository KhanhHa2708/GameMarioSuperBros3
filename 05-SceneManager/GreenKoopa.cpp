#include "GreenKoopa.h"
#include "ColorBlock.h"
#include "debug.h"
#include "PlayScene.h"

CGreenKoopa::CGreenKoopa(float x, float y, int l) :CGameObject(x, y)
{
	level = l;
	this->ax = 0;
	this->ay = GREEN_KOOPA_GRAVITY;
	die_start = -1;
	nx = -1;
	SetState(GREEN_KOOPA_STATE_WALKING);
}


void CGreenKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == LEVEL_GREEN_KOOPA_WING) {
		left = x - GREEN_KOOPA_WING_BBOX_WIDTH / 2;
		top = y - GREEN_KOOPA_WING_BBOX_HEIGHT / 2;
		right = left + GREEN_KOOPA_WING_BBOX_WIDTH;
		bottom = top + GREEN_KOOPA_WING_BBOX_HEIGHT;
	}
	else if (state == GREEN_KOOPA_STATE_DIE)
	{
		left = x - GREEN_KOOPA_BBOX_WIDTH / 2;
		top = y - GREEN_KOOPA_BBOX_HEIGHT / 2;
		right = left + GREEN_KOOPA_BBOX_WIDTH;
		bottom = top + GREEN_KOOPA_BBOX_HEIGHT;
	}
	else
	{
		left = x - GREEN_KOOPA_BBOX_WIDTH / 2;
		top = y - GREEN_KOOPA_BBOX_HEIGHT / 2;
		right = left + GREEN_KOOPA_BBOX_WIDTH;
		bottom = top + GREEN_KOOPA_BBOX_HEIGHT;
	}
}

void CGreenKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGreenKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGreenKoopa*>(e->obj)) return;
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

void CGreenKoopa::SetLevel(int l)
{
	level = l;
}

void CGreenKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GREEN_KOOPA_STATE_DIE) && (GetTickCount64() - die_start > GREEN_KOOPA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	//if (level == LEVEL_PARA_GOOMBA) CalcGoombaMove();

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGreenKoopa::Render()
{
	int aniId = -1;
	if (level == LEVEL_GREEN_KOOPA_WING && vx<=0) {
		aniId = ID_ANI_GREEN_KOOPA_WING_WALKING_LEFT;
	}
	else if (level == LEVEL_GREEN_KOOPA_WING && vx > 0)
	{
		aniId = ID_ANI_GREEN_KOOPA_WING_WALKING_RIGHT;
	}
	else if(level== LEVEL_GREEN_KOOPA &&vx<=0){
		aniId = ID_ANI_GREEN_KOOPA_WALKING_LEFT;
	}
	else if (level == LEVEL_GREEN_KOOPA && vx > 0)
	{
		aniId = ID_ANI_GREEN_KOOPA_WALKING_RIGHT;
	}
	if (state == GREEN_KOOPA_STATE_DIE)
	{
		aniId = ID_ANI_GREEN_KOOPA_DIE;
	}
	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGreenKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GREEN_KOOPA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GREEN_KOOPA_BBOX_HEIGHT - GREEN_KOOPA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		nx = 0;
		ay = 0;
		break;
	case GREEN_KOOPA_STATE_WALKING:
		vx = nx * GREEN_KOOPA_WALKING_SPEED;
		break;
	}
}