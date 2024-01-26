#include "PSwitch.h"
#include "debug.h"

CPSwitch::CPSwitch(float x, float y) : Item(x, y, 0)
{
	itemType = ItemType::PSwitch;
	baseY = y;
	ay = 0;
	SetState(STATE_P_SWITCH_VISIBLE);
}
void CPSwitch::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_P_SWITCH)->Render(x, y);

	//RenderBoundingBox();
}

// Make the coin bouncing before die
void CPSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (insideBrick) {
		if (state == STATE_ITEM_VISIBLE) {
		//	y -= P_SWITCH_DEFLECT_GRAVITY * dt;
			vy = 0;
		}
		else if (state == STATE_ITEM_SPAWN) {
			y += P_SWITCH_DEFLECT_GRAVITY * dt;
			if (y >= baseY - 20) {
				SetState(STATE_ITEM_DIE);
			}
		}
	
	}
	else {
		SetState(STATE_P_SWITCH_HIDE);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPSwitch::SetState(int state) {
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_ITEM_INVISIBLE:
		vy = 0;
		break;
	case STATE_ITEM_VISIBLE:
		vy = 0;
		break;
	case STATE_ITEM_SPAWN:
		break;
	case STATE_ITEM_DIE:
		this->Delete();
		break;
	default:
		break;
	}
}

void CPSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - P_SWITCH_BBOX_WIDTH / 2;
	t = y - P_SWITCH_BBOX_HEIGHT / 2;
	r = l + P_SWITCH_BBOX_WIDTH;
	b = t + P_SWITCH_BBOX_HEIGHT;
}