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
#define		LINE_SAVE			L"../Save/SaveFile.dat"

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

/// EXTERN
extern		HWND				g_hWnd;
extern		float				g_Wheel; // 마우스 휠값 관리