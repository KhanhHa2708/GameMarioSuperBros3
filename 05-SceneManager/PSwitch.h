#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Item.h"

#define ID_ANI_P_SWITCH 21000

#define	P_SWITCH_WIDTH 10
#define P_SWITCH_BBOX_WIDTH 10
#define P_SWITCH_BBOX_HEIGHT 16

#define P_SWITCH_DEFLECT_GRAVITY 0.15f
#define P_SWITCH_OFFSET 70

#define STATE_P_SWITCH_HIDE 32
#define STATE_P_SWITCH_VISIBLE 20
// Mario only collision with coin when state == VISIBLE
class CPSwitch : public Item {
	int insideBrick;
public:
	CPSwitch(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void SetState(int state);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsColliable() { return 1; }
	
};