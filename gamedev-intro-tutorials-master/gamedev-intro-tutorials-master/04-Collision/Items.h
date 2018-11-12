#pragma once
#include "GameObject.h"

class Items : public CGameObject
{
	int currentAni = 0;

public:

	Items();
	~Items();

	virtual void LoadResource();
	virtual void Render(float xViewport, float yViewport);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};