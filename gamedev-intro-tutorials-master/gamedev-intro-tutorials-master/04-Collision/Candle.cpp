#include "Candle.h"

void Candle::LoadResource()
{
	//load resource
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_CANDLE, L"Resource\\sprites\\Ground\\0.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DEAD, L"Resource\\sprites\\Effect\\DEAD.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites * sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 texCandel = textures->Get(ID_TEX_CANDLE);
	sprites->Add(303, 0, 0, 32, 64, texCandel);
	sprites->Add(304, 32, 0, 64, 64, texCandel);

	LPDIRECT3DTEXTURE9 texdead = textures->Get(ID_TEX_DEAD);
	//dead object
	sprites->Add(6000, 0, 0, 42, 44, texdead);
	sprites->Add(6001, 42, 0, 84, 44, texdead);
	sprites->Add(6002, 84, 0, 128, 44, texdead);

	LPANIMATION ani;
	CAnimations * animations = CAnimations::GetInstance();

	ani = new CAnimation(100);		//candle
	ani->Add(303);
	ani->Add(304);
	animations->Add(401, ani);

	ani = new CAnimation(100);	// dead
	ani->Add(6000);
	ani->Add(6001);
	ani->Add(6002);
	animations->Add(901, ani);

	this->AddAnimation(401);
	this->AddAnimation(901);
	this->SetState(CANDLE_STATE_NO);
}

void Candle::Render(float xViewport, float yViewport)
{
	this->X_view = x - xViewport;
	this->Y_view = y - yViewport;

	if (!(isvisible && isDead)) //Kiem tra object co ton tai tren game sau khi va cham
	{
		animations[0]->Render(x - xViewport, y - yViewport);
		RenderBoundingBox();
	}

	if (timeDelay > 90.0f)
	{
		if (isDead && state == CANDLE_STATE_DIE && !(animations[1]->CheckDoAllFrame()))
		{
			animations[1]->Render(x - xViewport, y - yViewport);
			if (animations[1]->CheckDoAllFrame())
			{
				this->SetState(CANDLE_STATE_NO);
				animations[1]->SetDoAllFrame(false);
				this->ResetTime();
			}

		}
	}
}

void Candle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (!(isvisible && isDead)) //Kiem tra object co con ton tai tren game sau khi va cham
	{
		l = X_view;
		t = Y_view;
		r = X_view + CANDLE_BBOX_WIDTH;
		b = Y_view + CANDLE_BBOX_HEIGHT;
	}
}

void Candle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == CANDLE_STATE_DIE)
	{
		timeDelay += dt * 0.5f;
	}
}

