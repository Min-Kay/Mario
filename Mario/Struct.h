#pragma once
#include "framework.h"
#include "Enum.h"

typedef struct tagInfo
{
	float		fX;	// 내가 그리고자 하는 물체의 중점 x
	float		fY; // 내가 그리고자 하는 물체의 중점 y
	float		fCX; // 가로 사이즈
	float		fCY; // 세로 사이즈

}INFO;


typedef	struct	tagLinePos	 
{
	float		fX;
	float		fY;

	tagLinePos()
	{
		ZeroMemory(this, sizeof(tagLinePos));
	}
	tagLinePos(float _X, float _Y)
		: fX(_X), fY(_Y)
	{

	}

}LINEPOS;

typedef struct tagLineInfo
{
	LINEPOS		tLeftPos;
	LINEPOS		tRightPos;

	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& _tLeft, LINEPOS& _tRight)
		: tLeftPos(_tLeft), tRightPos(_tRight)
	{	}
}LINEINFO;

typedef struct tagBlockInfo
{
	POINT	pos;
	BLOCK::ID id;

	tagBlockInfo() { ZeroMemory(this, sizeof(tagBlockInfo)); }
	tagBlockInfo(POINT& _pos, BLOCK::ID& _id)
		: pos(_pos), id(_id)
	{	}

}BLOCKINFO;




class CDeleteObj
{
public:
	CDeleteObj() {}
	~CDeleteObj() {}

public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (nullptr != Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

class CDeleteMap
{
public:
	CDeleteMap() {}
	~CDeleteMap() {}

public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (nullptr != Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}
};

class CKillObj
{
public:
	CKillObj() {}
	~CKillObj() {}

public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (!Temp->Get_Dead())
		{
			Temp->Set_Dead(true);
		}
	}
};

class CTagFinder
{
public:
	CTagFinder(const TCHAR* _key)
		:m_Key(_key) {}

public:
	template<typename T>
	bool operator()(T& Temp)
	{
		return !lstrcmp(m_Key,Temp.first);
	}

private:
	const TCHAR* m_Key;
};

template<typename T>
void		Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}


