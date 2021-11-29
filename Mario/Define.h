#pragma once
#include "framework.h"

/// WINAPI
#define		WINCX				800
#define		WINCY				600	
#define		PURE				= 0


/// PROGRAM LIFE TIME
#define		OBJ_NOEVENT			0
#define		OBJ_DEAD			1


/// MATH
#define		PI					3.141592f


/// SAVE & LOAD
#define		LOAD_STAGEONE_BLOCK		L"../Save/StageOneBlock.dat"
#define		LOAD_STAGETWO_BLOCK		L"../Save/StageTwoBlock.dat"
#define		LOAD_STAGETHREE_BLOCK	L"../Save/StageThreeBlock.dat"
#define		LOAD_STAGEFOUR_BLOCK	L"../Save/StageFourBlock.dat"


#define		LOAD_STAGEONE		L"../Save/StageOne.dat"
#define		LOAD_STAGETWO		L"../Save/StageTwo.dat"
#define		LOAD_STAGETHREE		L"../Save/StageThree.dat"
#define		LOAD_STAGEFOUR		L"../Save/StageFour.dat"

/// KEY SETTING
#define		VK_MAX				0xff
#define		VK_ATTACK			VK_SPACE
#define		VK_RUN				'R'

/// INGAME
#define		LIFE_COUNT			3
#define		COIN_TO_LIFE		100
#define		PLAYER_POS_X		200
#define		PLAYER_POS_Y		200
#define		FALL_DOWN			15.f

#define		BRICK_SIZE_X		32
#define		BRICK_SIZE_Y		32

/// EXTERN
extern		HWND				g_hWnd;