#pragma once

#include "Line.h"
#include "KeyMgr.h"

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(HDC _DC);
	void		Release(void);


public:
	static	CLineMgr* Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CLineMgr;

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
	void	KeyInput();
	void	Set_Pos();
	void	Reset_Pos();
	void	Set_Target();
	void    Undo_Target();
	void	Undo();
	void	Redo();
	void	Save();

public:
	void	Load(const TCHAR* _File);

private:
	bool    Collision_Mouse();
	void	Update_RectPoint();

public:
	void	Set_EditorMode(bool _bool) { is_Editor = _bool; }

private:
	static CLineMgr* m_pInstance;

	LINEPOS				m_tLinePos[2]; // ���� ���� �����ϴ� �� ����Ʈ
	list<CLine*>		m_LineList; // ���� ������� ���� ����Ʈ
	list<CLine*>		m_ReDoList; // �ǵ������ ���� ����Ʈ

	CLine* m_TargetLine;
	INFO				m_MouseInfo;
	RECT				m_MouseRect;

	DWORD				m_DrawPressTime;
	DWORD				m_UndoPressTime;
	DWORD				m_RedoPressTime;

	bool				is_Editor;
};

