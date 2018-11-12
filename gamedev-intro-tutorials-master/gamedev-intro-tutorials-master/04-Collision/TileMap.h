#pragma once
#include<d3dx9.h>
#include<d3d9.h>
#include"define.h"

class TileMap
{
	int SCREENW = SCREEN_WIDTH;
	int SCREENH = SCREEN_HEIGHT;

	//settings for the scroller
	const int TILEWIDTH = 64;
	const int TILEHEIGHT = 64;
	const int MAPWIDTH = 24;
	const int MAPHEIGHT = 6;

	//scrolling window size
	const int WINDOWWIDTH = (SCREENW / TILEWIDTH) * TILEWIDTH;
	const int WINDOWHEIGHT = (SCREENH / TILEHEIGHT) * TILEHEIGHT;
	LPCWSTR filename;
	int ViewPortX, ViewPortY;
	int SpeedX, SpeedY;
	long start;
	LPDIRECT3DSURFACE9 scrollbuffer = NULL;
	LPDIRECT3DSURFACE9 tiles = NULL;
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;


	int MAPDATA[24 * 6] = {
		1, 2, 2, 2, 2, 2, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 3, 4, 4, 5,
		6, 7, 7, 7, 7, 7, 8, 8, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 9, 10, 10,
		11, 12, 13, 12, 12, 12, 12, 7, 7, 12, 13, 12, 12, 12, 12, 7, 7, 7, 7,
		14, 14, 15, 16, 17, 18, 13, 19, 13, 13, 13, 13, 13, 13, 13, 19, 13, 13,
		13, 13, 13, 13, 13, 13, 19, 20, 21, 22, 17, 11, 23, 24, 25, 23, 23, 25,
		23, 25, 23, 24, 25, 23, 23, 25, 23, 25, 25, 26, 24, 27, 28, 29, 30, 31,
		32, 33, 34, 32, 32, 34, 32, 34, 32, 33, 34, 32, 32, 34, 32, 34, 34, 35, 33, 36, 37, 38, 39, 40
	};

public:
	TileMap(LPDIRECT3DDEVICE9 dv, LPDIRECT3DSURFACE9 bb, LPCWSTR filename);
	TileMap(LPCWSTR filename);
	~TileMap();
	void DrawTile(LPDIRECT3DSURFACE9 source, // source surface image
		int tilenum, // tile #
		int width, // tile width
		int height, // tile height
		int columns, // columns of tiles
		LPDIRECT3DSURFACE9 dest, // destination surface
		int destx, // destination x
		int desty // destination y
	);
	LPDIRECT3DSURFACE9 LoadSurface(LPCWSTR filename);
	void DrawTiles();

	void DrawScrollWindow(bool scaled = false);
	void ViewPort() { ViewPortX = 20; ViewPortY = 0; }
	void UpdateScrollPosition();
	void SetViewPortY(float y) { ViewPortY += y; }
	void SetViewportX(float x) { ViewPortX = x; }
	float GetViewportX() { return ViewPortX; }
	float GetViewPortY() { return ViewPortY; }
};

