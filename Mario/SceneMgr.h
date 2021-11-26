#pragma once

#include "Scene.h"

//#include "Logo.h"

class CSceneMgr
{

private:
	CSceneMgr();
	~CSceneMgr();

public:
	void		Scene_Change(SCENE::ID eScene);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC _DC);
	void		Release(void);

public:
	static	CSceneMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSceneMgr;

		return m_pInstance;
	}

	static	void		Destroy_Intance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CSceneMgr*			m_pInstance;
	CScene*						m_pScene;
};

