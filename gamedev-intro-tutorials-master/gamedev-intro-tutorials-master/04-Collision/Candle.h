#pragma once
#include "GameObject.h"
#include "OStatis.h"

#define CANDLE_BBOX_WIDTH  32
#define CANDLE_BBOX_HEIGHT 64

class Candle : public COStatic
{
	float timeDelay = 0.0f;
	
public:

	virtual void LoadResource();
	virtual void Render(float xViewport, float yViewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL, vector<LPGAMEOBJECT> *coObjectStatic = NULL);
	void ResetTime() { this->timeDelay = this->timeDelay != 0 ? 90.0f : this->timeDelay; }
};