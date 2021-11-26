#pragma once

#include "Include.h"

class CScene abstract
{
public:	
	
	virtual void		Initialize(void)PURE;
	virtual int			Update(void)PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release(void)PURE;

public:
	CScene();
	virtual ~CScene();
};

