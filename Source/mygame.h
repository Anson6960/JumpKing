/*
 * mygame.h: ���ɮ��x�C��������class��interface
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *   2006-02-08 V4.2
 *      1. Rename OnInitialUpdate() -> OnInit().
 *      2. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      3. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
*/

//#include "CEraser.h"
#include "CBall.h"
#include "CBouncingBall.h"
#include "King.h"

namespace game_framework {

	//class CGameMap {
	//public:
	//	CGameMap();
	//	void LoadBitmap();
	//	void OnShow();
	//	void OnMove();
	//	//bool isEmpty(int, int);
	//	void OnKeyDown(UINT);
	//	void RandomBouncingBall();
	//	void InitializeBouncingBall(int, int, int);
	//	~CGameMap();
	//protected:
	//	//CMovingBitmap blue, green;
	//	int map[4][5];
	//	const int X, Y;
	//	const int MW, MH;
	//	CBouncingBall* balls;
	//	int random_num;
	//};

	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		MENU_INTRO,
		PRESS_START,
		SELECT,
		MENU_FAIL,
		OPENING_THEME,
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyDown(UINT, UINT, UINT); 				// �B�z��LDown���ʧ@
	protected:
		void OnMove();
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap title_logo;
		CAnimation	  press_space;
	};

	enum ACTION_ID
	{
		CONTINUE,
		NEW_GAME,
		OPTIONS,
		EXTRAS,
		QUIT,
		ACTION_AMOUNT = 5
	};

	//enum NEW_GAME_ID
	//{
	//	NO,
	//	DELETE_SAVE
	//};

	//enum OPTIONS_ID
	//{
	//	GRAPHICS,
	//	CONTROLS,
	//	AUDIO,
	//	OPTIONS_CANCEL,
	//	OPTIONS_AMOUNT = 4
	//};

	//enum GRAPHICS_ID
	//{
	//	FULLSCREEN,
	//	GRAPHICS_CANCEL
	//};

	//enum EXTRAS_ID
	//{
	//	CREDITS,
	//	ATTRIBUTION,
	//	TOTAL_STATS,
	//	EXTRAS_CANCEL,
	//	EXTRAS_AMOUNT = 4
	//};

	enum QUIT_ID
	{
		NO,
		YES,
		QUIT_AMOUNT = 2
	};

	struct MenuAction
	{
		bool isSelected;
		CMovingBitmap figure;
	};

	class CGameStateMenu : public CGameState {
	public:
		CGameStateMenu(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyDown(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void openMenu_newGame();
		void openMenu_options();
		void openMenu_extras();
		void openMenu_quit();
		void moveCursor_action();
		void moveCursor_newGame();
		void moveCursor_options();
		void moveCurosr_extras();
		void moveCursor_quit();
		//void handleMenuContinue();
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		MenuAction action[ACTION_AMOUNT];
		MenuAction quit[QUIT_AMOUNT];
		CMovingBitmap title_logo;
		CMovingBitmap cursor;
		CMovingBitmap frame_action;
		CAnimation frame_quit, title_quit;
		CMovingBitmap record;
		CMovingBitmap hint;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@ 
		void OnRButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnRButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		const int		NUMBALLS;	// �y���`��
		CMovingBitmap	background;	// �I����
		CMovingBitmap	help;		// ������
		CBall			*ball;		// �y���}�C
		CMovingBitmap	corner;		// ������
		//CEraser			eraser;		// ��l
		CInteger		hits_left;	// �ѤU��������
		CBouncingBall   bball;		// ���мu�����y
		//CMovingBitmap	practice;
		int				picX, picY;
		King			king;
		//list<Map>		maps;
		//CGameMap		gamemap;
		Map				map;
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;	// �˼Ƥ��p�ƾ�
	};

}