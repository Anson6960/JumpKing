#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CGameMap.h"

namespace game_framework {

	CGameMap::CGameMap()
	{
		this->Initialize();
	}

	CGameMap::~CGameMap()
	{
	}

	void CGameMap::LoadBitmap()
	{
		char path[100] = "";
		for (int i = 1; i <= MAX_LEVEL; i++)
		{
			strcpy(path, ("RES/midground/mg" + to_string(i) + ".bmp").c_str());
			midground.AddBitmap(path, RGB(255, 255, 255));
		}
		for (int i = 1; i <= MAX_LEVEL; i++)
		{
			strcpy(path, ("RES/background/bg" + to_string(i) + ".bmp").c_str());
			background.AddBitmap(path, RGB(255, 255, 255));
		}
		midground.SetTopLeft(0, 0);
		background.SetTopLeft(0, 0);

		test.LoadBitmap(IDB_BITMAP2);
	}

	void CGameMap::Initialize()
	{
		levelIndex = 0;
		this->OnLoad();
	}

	void CGameMap::OnLoad()
	{
		for (int row = 0; row < 60; row++)
			for (int col = 0; col < 80; col++)
				levelGrid[col][row] = levels[levelIndex][row][col];
	}

	void CGameMap::OnShow()
	{
		background.OnShow();
		midground.OnShow();
		for (int i = 0; i < 80; i++)
		{
			for (int j = 0; j < 60; j++)
			{
				switch (levelGrid[i][j])
				{
					case 0:
						break;
					case 1:
						test.SetTopLeft(10 * i, 10 * j);
						test.ShowBitmap();
						break;
					default:
						break;
				}
			}
		}
	}

	void CGameMap::NextStage()
	{
		levelIndex++;
		background.SetBitmapNumber(levelIndex);
		midground.SetBitmapNumber(levelIndex);
		this->OnLoad();
	}

	void CGameMap::BackStage()
	{
		levelIndex--;
		background.SetBitmapNumber(levelIndex);
		midground.SetBitmapNumber(levelIndex);
		this->OnLoad();
	}

	bool CGameMap::isEmpty(int mapX, int mapY)
	{
		int gridX = mapX / 10;
		int gridY = mapY / 10;
		return levelGrid[gridX][gridY] == 0;
	}
}