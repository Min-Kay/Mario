#pragma once

namespace DIR
{
	enum DIR	{ LEFT, RIGHT, UP, DOWN, END };
}

namespace OBJ
{
	enum ID { OBSTACLE, ITEM, BULLET, MONSTER, PLAYER, END };
}

namespace STATE
{
	enum ID { IDLE, RUN, JUMP, ATTACK, DIE , END};
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

namespace MONSTER
{
	enum ID { GOOMBA, CHICKEN, KOOPA, SQUID, FLOWER, END };
}


namespace BULLET
{
	enum ID {BULLET, KOOPA_BULLET,FLOWER_BULLET, END};
}

namespace ITEM
{
	enum ID { COIN, MUSHROOM, FLOWER, END };
}

namespace BLOCK
{
	enum ID { DEFAULT, ITEM , INVISIBLE, BREAKABLE, PIPE, END};
}