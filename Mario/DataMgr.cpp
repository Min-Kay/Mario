#include "DataMgr.h"
#include "Define.h"

CDataMgr* CDataMgr::pInstance = nullptr;

CDataMgr::CDataMgr()
	:coin(0), score(0), init_Life(LIFE_COUNT),  life(init_Life)
{
}

CDataMgr::~CDataMgr()
{
}

void CDataMgr::Initialize()
{
	coin = 0;
	score = 0;
	init_Life = LIFE_COUNT;
	life = init_Life;
}

void CDataMgr::Late_Update()
{
	if (coin >= COIN_TO_LIFE)
	{
		coin -= COIN_TO_LIFE;
		++life;
	}
}

void CDataMgr::Release()
{
	Initialize();
}
