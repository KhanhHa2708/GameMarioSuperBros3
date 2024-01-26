#include "PiranhaPlant.h" 



void CPiranhaPlant::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_PIRANHA_PLANT)->Render(x, y);
	if (this->GetState() == PIRANHA_STATE_HIDE) {
		return;
	}
	
	RenderBoundingBox();
}



void CPiranhaPlant::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
	
	l = x - PIRANHA_BOX_WIDTH / 2;
	t = y - PIRANHA_BOX_HEIGHT / 2;
	r = l + PIRANHA_BOX_WIDTH;
	b = t + PIRANHA_BOX_HEIGHT;
}


void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//hide not update 
	if (this->GetState() == PIRANHA_STATE_HIDE) {
		return;
	}

	CGameObject::Update(dt, coObjects);

	x += PIRANHA_BOX_WIDTH;
	y += PIRANHA_BOX_HEIGHT;

	//Navigator top to bottom
	if (vy < 0 && y < this->min_y) {
		y = min_y;
		vy = -vy;
	}
	//[condition hidden coin]
	if (y >= max_y)
	{
		this->SetState(PIRANHA_STATE_MOVING);
	}


}


void CPiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	vx = 0;
	switch (state)
	{
	case PIRANHA_STATE_MOVING:
		vy = -PIRANHA_SPEED;//bottom -> top
		break;
	case PIRANHA_STATE_HIDE:
		vy = 0;
		break;
	}
}