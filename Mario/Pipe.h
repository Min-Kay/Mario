#pragma once

#ifndef __PIPE_H__
#define __PIPE_H__

#include "Block.h"

class CPipe : public CBlock
{
public:
	CPipe();
	virtual ~CPipe();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Render(HDC hDC) override;
};

#endif