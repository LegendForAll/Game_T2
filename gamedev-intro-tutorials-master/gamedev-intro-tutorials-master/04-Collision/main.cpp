/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"
#include "Candle.h"
#include "Items.h"



CGame *game;
CMario *mario;

TileMap *tilemap;
bool marioInView = false;
CTextures * textures = CTextures::GetInstance();

DWORD dt;
vector<LPGAMEOBJECT> objects;
vector<LPGAMEOBJECT> objecttsStatic;



LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	//Load texture
	//CTextures * textures = CTextures::GetInstance();
	textures->loadResources();

	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	/*
	//load sprite stand and static
	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_SIMON);
	sprites->Add(101, 0, 0, 60, 64, texMario);
	sprites->Add(102, 60, 0, 120, 64, texMario);
	sprites->Add(103, 120, 0, 180, 64, texMario);
	sprites->Add(104, 180, 0, 240, 64, texMario);
	//load sprite sit
	sprites->Add(105, 240, 0, 300, 64, texMario);
	//load sprite jump
	sprites->Add(106, 240, 0, 300, 64, texMario);
	//load sprite stand attack
	sprites->Add(107, 300, 0, 360, 64, texMario);
	sprites->Add(108, 360, 0, 420, 64, texMario);
	sprites->Add(109, 420, 0, 480, 64, texMario);
	//load sptite sit attack
	sprites->Add(110, 420, 66, 480, 132, texMario);
	sprites->Add(111, 0, 132, 60, 198, texMario);
	sprites->Add(112, 60, 132, 120, 198, texMario);
	//load sprite stand up_stair
	sprites->Add(113, 240, 66, 300, 132, texMario);
	//load sprite stand down_stair
	sprites->Add(114, 120, 66, 180, 132, texMario);
	//load sprite go up_stair
	sprites->Add(115, 240, 66, 300, 132, texMario);
	sprites->Add(116, 300, 66, 360, 132, texMario);
	//load sprite go down_stair
	sprites->Add(117, 120, 66, 180, 132, texMario);
	sprites->Add(118, 180, 66, 240, 132, texMario);
	//load sprite attack up_stair
	sprites->Add(119, 300, 132, 360, 198, texMario);
	sprites->Add(120, 360, 132, 420, 198, texMario);
	sprites->Add(121, 420, 132, 480, 198, texMario);
	//load sprite attack down_stair
	sprites->Add(122, 120, 132, 180, 198, texMario);
	sprites->Add(123, 180, 132, 240, 198, texMario);
	sprites->Add(124, 240, 132, 300, 198, texMario);
	//load sprite hurted
	sprites->Add(125, 0, 66, 60, 132, texMario);
	//load sprite invisible
	sprites->Add(126, 180, 198, 240, 264, texMario);
	sprites->Add(127, 0, 0, 60, 64, texMario);
	//load sprite eatItem
	sprites->Add(128, 0, 198, 60, 264, texMario);
	sprites->Add(129, 60, 198, 120, 264, texMario);
	sprites->Add(130, 120, 198, 180, 264, texMario);
	//load sprite die
	sprites->Add(131, 240, 198, 300, 264, texMario);
	//load stand back
	sprites->Add(132, 60, 66, 120, 132, texMario);*/


	//load Tileset sprite
	LPDIRECT3DTEXTURE9 texBG = textures->Get(ID_LEVEL_ONE_BG);
	sprites->Add(200, 0, 0, 640, 256, texBG);

	//Load matrix Map
	//tileMap = new TileMap(1536, 392, sprites->Get(ID_LEVEL_ONE_BG), 64, 64);
	//tileMap->LoadListTileFromFile("Resource\\sprites\\lv1.b");


	LPANIMATION ani;
	/*
	//ani = new CAnimation(100);		// simon stand static
	//ani->Add(101,100);
	//animations->Add(SM_STAND_STATIC, ani);

	//ani = new CAnimation(100);		// simon move left
	//ani->Add(101,170);
	//ani->Add(102,170);
	//ani->Add(103,170);
	//ani->Add(104,170);
	//animations->Add(SM_MOVE_LEFT, ani);

	//ani = new CAnimation(100);		// simon sit
	//ani->Add(105);
	//animations->Add(SM_SIT, ani);

	//ani = new CAnimation(100);		// simon jump
	//ani->Add(106);
	//animations->Add(SM_JUMP, ani);

	//ani = new CAnimation(100);		// simon stand attack (whip)
	//ani->Add(101,200);	//ani important
	//ani->Add(107,200);
	//ani->Add(108,200);
	//ani->Add(109,200);
	//animations->Add(SM_STAND_ATTACK, ani);

	//ani = new CAnimation(100);		// simon stand attack (weapon)
	//ani->Add(107, 170);
	//ani->Add(108, 170);
	//ani->Add(109, 170);
	//animations->Add(SM_THROW_WEAPON, ani);

	//ani = new CAnimation(100);		// simon sit attack (whip)
	//ani->Add(105, 200);
	//ani->Add(110, 200);
	//ani->Add(111, 200);
	//ani->Add(112, 200);
	//animations->Add(SM_SIT_ATTACK, ani);

	//ani = new CAnimation(100);		// simon stand up_stair
	//ani->Add(113);
	//animations->Add(SM_STAND_UP_STAIR, ani);

	//ani = new CAnimation(100);		// simon stand down_stair
	//ani->Add(114);
	//animations->Add(SM_STAND_DOWN_STAIR, ani);

	//ani = new CAnimation(100);		// simon go up_stair
	//ani->Add(115, 170);
	//ani->Add(116, 170);
	//animations->Add(SM_MOVE_UP_STAIR, ani);

	//ani = new CAnimation(100);		// simon go down stair
	//ani->Add(117, 170);
	//ani->Add(118, 170);
	//animations->Add(SM_MOVE_DOWN_STAIR, ani);

	//ani = new CAnimation(100);		// simon attack up_stair
	//ani->Add(119, 170);
	//ani->Add(120, 170);
	//ani->Add(121, 170);
	//animations->Add(SM_ATTACK_UP_STAIR, ani);

	//ani = new CAnimation(100);		// simon attack down_stair
	//ani->Add(122, 170);
	//ani->Add(123, 170);
	//ani->Add(124, 170);
	//animations->Add(SM_ATTACK_DOWN_STAIR, ani);

	//ani = new CAnimation(100);		// simon hurted
	//ani->Add(125);
	//animations->Add(SM_HURTED, ani);

	//ani = new CAnimation(100);		// simon Invisible
	//ani->Add(126, 200);
	//ani->Add(127, 200);
	//animations->Add(SM_INVISIBLE, ani);

	//ani = new CAnimation(100);		// simon eat Item
	//ani->Add(128);
	//ani->Add(129);
	//ani->Add(130);
	//animations->Add(SM_EAT_ITEM, ani);

	//ani = new CAnimation(100);		// fall down
	//ani->Add(101);
	//animations->Add(SM_FALL_DOWN, ani);

	//ani = new CAnimation(100);		// throw weapon
	//ani->Add(107, 170);
	//ani->Add(108, 170);
	//ani->Add(109, 170);
	//animations->Add(SM_THROW_WEAPON, ani);

	//ani = new CAnimation(100);		// die
	//ani->Add(131);
	//animations->Add(SM_DEAD, ani);

	//ani = new CAnimation(100);		// stand back
	//ani->Add(132);
	//animations->Add(SM_STAND_BACK, ani);


	mario = new CMario();
	//mario->AddAnimation(SM_STAND_STATIC);		//simon stand static
	//mario->AddAnimation(SM_MOVE_LEFT);			//simon move left
	//mario->AddAnimation(SM_SIT);				//simon sit
	//mario->AddAnimation(SM_JUMP);				//simon jump
	//mario->AddAnimation(SM_STAND_ATTACK);		//simon stand attack
	//mario->AddAnimation(SM_SIT_ATTACK);			//simon sit attack
	//mario->AddAnimation(SM_STAND_UP_STAIR);		//simon stand up stair
	//mario->AddAnimation(SM_STAND_DOWN_STAIR);	//simon stand down stair
	//mario->AddAnimation(SM_MOVE_UP_STAIR);		//simon move up_stair
	//mario->AddAnimation(SM_MOVE_DOWN_STAIR);	//simon move down_stair
	//mario->AddAnimation(SM_ATTACK_UP_STAIR);	//simon attack up_stair
	//mario->AddAnimation(SM_ATTACK_DOWN_STAIR);	//simon attack down_stair
	//mario->AddAnimation(SM_HURTED);				//simon hurted
	//mario->AddAnimation(SM_INVISIBLE);			//simon invisible
	//mario->AddAnimation(SM_EAT_ITEM);			//simon eatItem
	//mario->AddAnimation(SM_FALL_DOWN);			//simon fall down
	//mario->AddAnimation(SM_THROW_WEAPON);		//simon throw weapon
	//mario->AddAnimation(SM_DEAD);				//simon die
	//mario->AddAnimation(SM_STAND_BACK);			//simon stand back
	*/

	//Simon
	mario = new CMario();
	mario->LoadResource();
	mario->SetPosition(50.0f, 0);			
	mario->SetState(SM_STAND_STATIC);			
	objects.push_back(mario);

	//Groud
	CBrick *brick = new CBrick();
	brick->LoadResource();
	brick->SetPosition(0, 400);
	objects.push_back(brick);					

	CBrick *brick1 = new CBrick();
	brick1->LoadResource();
	brick1->SetPosition(720, 400);
	objects.push_back(brick1);

	//Candle
	Candle *candle = new Candle();
	candle->LoadResource();
	candle->SetPosition(200.0f, 340);
	//objects.push_back(candle);
	objecttsStatic.push_back(candle);

	Candle *candle1 = new Candle();
	candle1->LoadResource();
	candle1->SetPosition(600.0f, 340);
	//objects.push_back(candle1);
	objecttsStatic.push_back(candle1);

	Candle *candle2 = new Candle();
	candle2->LoadResource();
	candle2->SetPosition(800.0f, 340);
	//objects.push_back(candle2);
	objecttsStatic.push_back(candle2);

	Candle *candle3 = new Candle();
	candle3->LoadResource();
	candle3->SetPosition(1000.0f, 340);
	//objects.push_back(candle3);
	objecttsStatic.push_back(candle3);

	Items *_it = new Items();
	_it->LoadResource();
	_it->SetPosition(200, 100);
	_it->SetState(I_MORNING_STAR);
	objects.push_back(_it);

	//Items *_it1 = new Items();
	//_it1->LoadResource();
	//_it1->SetPosition(600, 100);
	//_it1->SetState(I_DOUBLE_SHOT);
	//objects.push_back(_it1);

	//Items *_it3 = new Items();
	//_it3->LoadResource();
	//_it3->SetPosition(800, 100);
	//_it3->SetState(I_BOSS_BAT);
	//objects.push_back(_it3);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> coObjectsStatic;

	//Update enemy vs simon
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	for (int i = 0; i < objecttsStatic.size();i++)
	{
		coObjectsStatic.push_back(objecttsStatic[i]);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,&coObjects, &coObjectsStatic);
	}

	//Update object static


	//for (int i = 0; i < objecttsStatic.size();i++)
	//{
	//	objecttsStatic[i]->Update(dt, &coObjectsStatic);
	//}

	if (mario->x > SCREEN_WIDTH / 2 && !marioInView)
	{
		tilemap->SetViewportX(mario->x - SCREEN_WIDTH / 2);
		marioInView = true;
	}
	if (marioInView)
	{
		tilemap->SetViewportX(mario->x - SCREEN_WIDTH / 2);
	}
	//Check status keyboard
	PollKeyboard();
	mario->KeyEventHandler();

	

	//Update ViewPort
	//viewPort = new ViewPort(posX, 480-25);
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	//thay doi
	tilemap->UpdateScrollPosition();

	if (d3ddv->BeginScene())
	{
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		//d3ddv->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 255, 3660, 100), 0.1f, 0);
		tilemap->DrawScrollWindow();

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 1; i < objects.size(); i++)
			objects[i]->Render(tilemap->GetViewportX(), tilemap->GetViewPortY());

		for (int i = 0; i < objecttsStatic.size(); i++)
		{
			objecttsStatic[i]->Render(tilemap->GetViewportX(), tilemap->GetViewPortY());
		}
		//render Background
		//LPDIRECT3DTEXTURE9 texBG = textures->Get(ID_TEX_WHIP);
		//D3DXVECTOR3 p(50, 50, 0);
		//RECT r;
		//r.left = 0;
		//r.top = 0;
		//r.right = 480;
		//r.bottom = 264;
		//spriteHandler->Draw(texBG, NULL, NULL, &p, D3DCOLOR_XRGB(255,255,255));

		//ve mario
		objects[0]->Render(tilemap->GetViewportX(),tilemap->GetViewPortY());

		spriteHandler->End();
		d3ddv->EndScene();
		spriteHandler->End();

		d3ddv->EndScene();
		d3ddv->Present(NULL, NULL, NULL, NULL);
	}

	// Display back buffer content to the screen
	//d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Init game
	game = CGame::GetInstance();
	game->Init(hWnd);


	tilemap = new TileMap(game->GetDirect3DDevice(), game->GetBackBuffer(), L"textures\\mapA.bmp");
	//tilemap->ViewPort();

	LoadResources();

	//SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}