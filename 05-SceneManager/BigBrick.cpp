#include "BigBrick.h"

void CBigBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CBigBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BIG_BRICK_BBOX_WIDTH / 2;
	t = y - BIG_BRICK_BBOX_HEIGHT / 2;
	r = l + BIG_BRICK_BBOX_WIDTH;
	b = t + BIG_BRICK_BBOX_HEIGHT;
}