#include "Enemy.hpp"
#include "time.h"

Enemy::Enemy( int x, int y) : Entity(x, y), Weapon('+') { this->sprite(); }
Enemy::Enemy( void ) : Entity(60, 60), Weapon('+'){ }
Enemy::Enemy( Enemy const & cp ) { *this = cp; }
Enemy::~Enemy( void ) { }
Enemy& Enemy::operator=( Enemy const & e ) {
	_x = e.getX();
	_y = e.getY();
	return *this;
}

void	Enemy::sprite( void ) {
	attron(RED);
	if (_y < 0)
		_y = 0;
	if (_x < 0)
		_x = _xmax;
	if (_y > _ymax - 1)
		_y = _ymax - 2;
	if (_x > _xmax - 2)
		_x = _xmax - 2;
	mvprintw(_y, _x, "++");
	attroff(RED);
	refresh();
}

void	Enemy::left( void ) { _x--; }
void	Enemy::right( void ) { _x++; }
void	Enemy::up( void ) { _y--; }
void	Enemy::down( void ) { _y++; }
void	Enemy::update( void ) {
// Hydra behavior?
	if ((mvinch(_y, _x) & A_CHARTEXT) == '*' || (mvinch(_y, _x + 1) & A_CHARTEXT) == '*' ||
		(mvinch(_y, _x - 1) & A_CHARTEXT) == '*')
	{
		G_KILL++;
		_x = _xmax;
		_y = rand() % _ymax;
	}
	this->left();
	shoot();
	this->sprite();
}

void	Enemy::setMaxs( int xmax, int ymax ) { _xmax = xmax; _ymax = ymax; }

void	Enemy::shoot( void ) { //Begins action chain:

	switch (rand() % 256) {
	case 0 : fire(_x, _y, 0, -1, _c); break;
	case 1 : fire(_x, _y, 0, 1, _c); break;
	case 2 : fire(_x, _y, -2, 0, _c); break;
	default : break;
	}
}
