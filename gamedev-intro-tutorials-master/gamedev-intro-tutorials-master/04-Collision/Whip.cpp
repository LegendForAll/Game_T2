#include "Whip.h"

Whip::Whip()
{

}

Whip::~Whip()
{

}


void Whip::SetPositionLR(float _x, float _y, bool isStand, bool _isLeft)
{
	//position whip vs simon
	this->curX = _isLeft ? _x - 15.0f : _x - 75.0f;
	this->curY = !(isStand) ? _y + 16.5f : _y;

	this->isLeft = _isLeft;
	//theo phan tich da tao ra whip tren viewport
	//_x, _y la toa do viewport cua simon
	this->SetPosition(curX, curY);
	this->isStand = isStand;
}

void Whip::LoadResource()
{
	//load resource
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_WHIP, L"Resource\\sprites\\Weapons\\WHIP.png", D3DCOLOR_XRGB(255, 0, 255));

	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);

	CSprites * sprites = CSprites::GetInstance();
	sprites->Add(300, 22, 199, 173, 266, texWhip);
	sprites->Add(301, 22, 266, 173, 325, texWhip);
	sprites->Add(302, 260, 329, 396, 410, texWhip);
	sprites->Add(305, 170, 0, 376, 66, texWhip);

	LPANIMATION ani;
	CAnimations * animations = CAnimations::GetInstance();

	ani = new CAnimation(100);		//whip stand left
	ani->Add(305, 90);
	ani->Add(300, 90);
	ani->Add(301, 90);
	ani->Add(302, 90);
	animations->Add(WP_WHIP_STAND_LEFT, ani);

	ani = new CAnimation(100);		//whip sit left
	ani->Add(305, 90);
	ani->Add(300, 90);
	ani->Add(301, 90);
	ani->Add(302, 90);
	animations->Add(WP_WHIP_SIT_LEFT, ani);

	this->AddAnimation(WP_WHIP_STAND_LEFT);
	this->AddAnimation(WP_WHIP_SIT_LEFT);

}

//de xu ly va cham chu khong phai box mau hong de ve
void Whip::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (!(this->isDead))
	{
		l = x;
		t = y;
		r = this->isLeft ? x + PROP_BBOX_WIDTH + PROP_BBOX_CHANGE : x + PROP_BBOX_WIDTH;
		b = y + PROP_BBOX_HEIGHT;
	}
}

void Whip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	vector<LPGAMEOBJECT> coEvent;
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if(this->AABB_BOX(this, coObjects->at(i)))
		{
			coEvent.push_back(coObjects->at(i));
		}
	}

	if (coEvent.size() == 0)
	{
		animations[currentAni]->SetDoAllFrame(false);
	}
	else
	{
		//current animation render finish
		if (animations[currentAni]->CheckDoAllFrame())
		{
			for (int i = 0; i < coEvent.size(); i++)
			{
				if (dynamic_cast<Candle *>(coEvent[i]))
				{
					{
						//xu ly cho object
						Candle *_candle = dynamic_cast<Candle *>(coEvent[i]);
						_candle->SetState(CANDLE_STATE_DIE);
						_candle->SetDead(true);
						_candle->SetInvisible(true);
						animations[currentAni]->SetDoAllFrame(false);
						this->oneHIT = false;
						//xu ly cho item
					}
				}
			}
		}
	}
}

void Whip::Render(float xViewport, float yViewport)
{
	int alpha = 255;
	////animation whip left or right
	this->isLeft = nx > 0 ? nx > 0 : false;

	////choose animation whip stand or sit
	this->currentAni = isStand ? 0 : 1;
	animations[currentAni]->Render(this->curX , this->curY , alpha, isLeft);//theo phan tich no la ve tren viewport


	//Render boundingBox at end frame of currentAnimation
	RenderBoundingBox();
}