#include "framework.h"
#include "SceneMgr.h"

CSceneMgr*			CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr()
	: m_pScene(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENE::ID eScene)
{
	if(nullptr != m_pScene)		// 왜 지우는지 생각을 합시다!
		Safe_Delete(m_pScene);

	switch (eScene)
	{
	case SCENE::MENU:
		//m_pScene = new CLogo;
		break;

	case SCENE::STAGE:
		break;

	case SCENE::END:
		break;
	}

	m_pScene->Initialize();
}

void CSceneMgr::Update(void)
{
	if (nullptr != m_pScene)
		m_pScene->Update();
}

void CSceneMgr::Late_Update(void)
{
	if (nullptr != m_pScene)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC _DC)
{
	if (nullptr != m_pScene)
		m_pScene->Render(_DC);
}

void CSceneMgr::Release(void)
{
	Safe_Delete(m_pScene);
}
