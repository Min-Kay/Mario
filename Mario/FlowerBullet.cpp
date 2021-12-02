#include "FlowerBullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

void CFlowerBullet::Initialize(void)
{
    parentId = OBJ::MONSTER;
    m_eID = OBJ::BULLET;
    m_bDead = false; 

    m_tInfo.fCX = 16.f;
    m_tInfo.fCY = 16.f;

    m_fSpeed = 1.f;

    CBmpMgr::Get_Instance()->Insert_Bmp(FLOWER_BULLET_BMP,FLOWER_BULLET_KEY);
}

int CFlowerBullet::Update(void)
{
    if (m_bDead)
        return OBJ_DEAD;

    m_tInfo.fY -= m_fSpeed;
    Update_Rect();
    return OBJ_NOEVENT;
}

void CFlowerBullet::Late_Update(void)
{
    if (m_tInfo.fY < 0)
        Set_Dead(true);
}

void CFlowerBullet::Render(HDC hDC)
{
    HDC mMemDC = CBmpMgr::Get_Instance()->Find_Image(FLOWER_BULLET_KEY);
    float ScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
    GdiTransparentBlt(hDC, int(m_tRect.left + ScrollX), int(m_tRect.top), (int)m_tInfo.fCX, (int)m_tInfo.fCY, mMemDC, 0, 0, 16, 16, RGB(255, 255, 255));

}

void CFlowerBullet::Release(void)
{
}

void CFlowerBullet::Set_Collision(OBJ::ID _eID, DIR::DIR _eDIR)
{
    if (_eID == OBJ::PLAYER)
        Set_Dead(true);
    else if (_eID == OBJ::OBSTACLE)
    {
        Set_Dead(true);
    }
}


