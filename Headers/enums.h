#ifndef ENUMS_H_INCLUDED
#define ENUMS_H_INCLUDED

//Déclaration des types
typedef enum movements
{
	MOVE_IDLE = 0,
	MOVE_LEFT = 1,
	MOVE_RIGHT = 2,
	MOVE_UP = 3,
	MOVE_DOWN = 4,

} movements;

typedef enum movedir
{
    MOVE_TOLEFT=0,
    MOVE_TOFACE=1,
    MOVE_TORIGHT=2,
    MOVE_TOLEFTIDLE = 3,
	MOVE_TORIGHTIDLE = 4
} movedir;

typedef enum ennemy_type
{
	TYPE_TANK = 0,
	TYPE_PLANE = 1,
	TYPE_SAUCER = 2,
	X = 0,
	Y = 1
} ennemy_type;

#endif // ENUMS_H_INCLUDED
