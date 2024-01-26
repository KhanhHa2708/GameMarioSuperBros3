#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10001
//#define BRICK_WIDTH 249
#define BIG_BRICK_BBOX_WIDTH 151
#define BIG_BRICK_BBOX_HEIGHT 31

class CBigBrick : public CGameObject {
public:
	CBigBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};