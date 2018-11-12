#pragma once
#include "GameObject.h"

#define GROUND_BBOX_WIDTH  768
#define GROUND_BBOX_HEIGHT 32

class CBrick : public CGameObject
{
public:
	virtual void LoadResource();
	virtual void Render(float xViewport, float yViewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};