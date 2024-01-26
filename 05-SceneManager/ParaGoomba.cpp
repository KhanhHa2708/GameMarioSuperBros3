#include "ParaGoomba.h"
#include "ColorBlock.h"
#include "debug.h"
#include "PlayScene.h"

CParaGoomba::CParaGoomba(float x, float y, int l) :CGameObject(x, y)
{
	level = l;
	step = 0;
	this->ax = 0;
	this->ay = PARA_RED_GOOMBA_GRAVITY;
	die_start = -1;
	nx = -1;
	SetState(PARA_RED_GOOMBA_STATE_WALKING);
}


void CParaGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == LEVEL_PARA_RED_GOOMBA) {
		left = x - RED_PARA_GOOMBA_BBOX_WIDTH / 2;
		top = y - RED_PARA_GOOMBA_BBOX_HEIGHT / 2;
		right = left + RED_PARA_GOOMBA_BBOX_WIDTH;
		bottom = top + RED_PARA_GOOMBA_BBOX_HEIGHT;
	}
	else if (state == PARA_RED_GOOMBA_STATE_DIE)
	{
		left = x - PARA_RED_GOOMBA_BBOX_WIDTH / 2;
		top = y - PARA_RED_GOOMBA_BBOX_HEIGHT / 2;
		right = left + PARA_RED_GOOMBA_BBOX_WIDTH;
		bottom = top + PARA_RED_GOOMBA_BBOX_HEIGHT;
	}
	else
	{
		left = x - PARA_RED_GOOMBA_BBOX_WIDTH / 2;
		top = y - PARA_RED_GOOMBA_BBOX_HEIGHT / 2;
		right = left + PARA_RED_GOOMBA_BBOX_WIDTH;
		bottom = top + PARA_RED_GOOMBA_BBOX_HEIGHT;
	}
}

void CParaGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CParaGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CParaGoomba*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	if (e->nx != 0)
	{
		vx = nx * vx;
		nx = -nx;
	}
	if (state == PARA_RED_GOOMBA_STATE_JUMPING && level == LEVEL_PARA_RED_GOOMBA)
	{
		if (e->ny < 0) vy = -PARA_RED_GOOMBA_JUMPING_SPEED;
	}
}

void CParaGoomba::SetLevel(int l)
{
	level = l;
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == PARA_RED_GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > PARA_RED_GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	if (level == LEVEL_PARA_RED_GOOMBA) CalcGoombaMove();

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CParaGoomba::Render()
{
	int aniId = -1;
	if (level == LEVEL_PARA_RED_GOOMBA) {
		aniId = ID_ANI_PARA_RED_GOOMBA_WALKING;
	}
	else {
		aniId = ID_ANI_RED_GOOMBA_WALKING;
	}

	if (state == PARA_RED_GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_PARA_RED_GOOMBA_DIE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PARA_RED_GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (PARA_RED_GOOMBA_BBOX_HEIGHT - RED_PARA_GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		nx = 0;
		ay = 0;
		break;
	case PARA_RED_GOOMBA_STATE_WALKING:
		vx = nx * PARA_RED_GOOMBA_WALKING_SPEED;
		break;
	case PARA_RED_GOOMBA_STATE_FLYING:
		vy = -PARA_RED_GOOMBA_FLYING_SPEED;
		break;
	}
}

void CParaGoomba::CalcGoombaMove() {
	// 0: walking	1: jumping	2: flying
	//float a, b;
	//dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(a, b);
	////DebugOut(L"mario - goomba = %0.2f\n", a - x);
	//if (a < x) vx = -vx;
	//

	switch (step) {
	case 0:
	{
		if (timeEllapsed == 0) {
			timeEllapsed = GetTickCount64();
		}
		else if (GetTickCount64() - timeEllapsed > PARA_RED_GOOMBA_WALK_DURATION) {
			timeEllapsed = 0;
			step = 1;
		}
		break;
	}
	case 1: {
		if (timeEllapsed == 0) {
			timeEllapsed = GetTickCount64();
			SetState(PARA_RED_GOOMBA_STATE_JUMPING);
		}
		else if (GetTickCount64() - timeEllapsed > PARA_RED_GOOMBA_JUMP_DURATION) {
			timeEllapsed = 0;
			step = 2;
		}
		break;
	}
	case 2: {
		if (timeEllapsed == 0) {
			timeEllapsed = GetTickCount64();
			SetState(PARA_RED_GOOMBA_STATE_FLYING);
		}
		else if (GetTickCount64() - timeEllapsed > PARA_RED_GOOMBA_FLY_DURATION) {
			timeEllapsed = 0;
			step = 0;
		}
		break;
	}
	}
}