#pragma once

namespace DIR
{
	enum DIR	{ LEFT, RIGHT, UP, DOWN, END };
}

namespace OBJID
{
	enum ID { PLAYER, BULLET, MONSTER, MOUSE, SHILED, END };
}

namespace POSITION
{
	enum POS { LEFTTOP, LEFTBOTTOM, RIGHTTOP, RIGHTBOTTOM, END };
}

namespace GAME
{
	enum ID { MENU, STAGEONE, STAGETWO, STAGETHREE, STAGEFOUR, ID_END};
	enum RESULT {NONE, WIN , LOSE, RESULT_END};
}

namespace MENU
{
	enum KIND { START, EXIT, END};
}

namespace SCENE
{
	enum ID {MENU, STAGE, END};
}