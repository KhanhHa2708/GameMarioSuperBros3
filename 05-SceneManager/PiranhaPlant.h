#pragma once
#pragma once
#include "GameObject.h"

#define PIRANHA_BOX_WIDTH  18
#define PIRANHA_BOX_HEIGHT 28

#define PIRANHA_DEFAULT_ZONE_UP 5
#define  PIRANHA_SPEED 0.009f

#define  PIRANHA_STATE_HIDE 0
#define  PIRANHA_STATE_MOVING 1

#define	ID_ANI_PIRANHA_PLANT 75000

class CPiranhaPlant : public CGameObject
{

public:
	CPiranhaPlant(float x, float y) : CGameObject(x, y) {}
	int min_y = -1; //move min y
	int max_y = -1;//move max y default
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);

};