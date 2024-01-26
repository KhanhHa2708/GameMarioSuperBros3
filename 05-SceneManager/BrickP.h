#pragma once
#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"


#define ID_ANI_BRICKP 850
#define ID_ANI_BRICKP_COIN_STAND_STILL 870


#define BRICKP_WIDTH 48
#define BRICKP_BBOX_WIDTH 48
#define BRICKP_BBOX_HEIGHT 48

#define DEBRIS_DISTANCE 9

#define BRICKP_STATE_IS_HIT 100
#define BRICKP_STATE_COIN 200
#define BRICKP_STATE_BRICK 300

class BrickP : public CGameObject {
public:
	bool is_block = true;
	vector<LPGAMEOBJECT> vec_debris;


	bool is_hit = false;
	BrickP(float x, float y) : CGameObject(x, y) {   }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetState(int state);

	virtual int IsBlocking() { return is_block; }
};