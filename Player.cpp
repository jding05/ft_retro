#include "Player.hpp"

Player::Player( int x, int y ) : Entity(x, y), Weapon('*') { this->sprite(); }
Player::Player( void ) : Entity(20, 20), Weapon('*') { }
Player::Player( Player const & cp ) { *this = cp; }
Player::~Player( void ) { }
Player& Player::operator=( Player const & e ) {
	_x = e.getX();
	_y = e.getY();
	return *this;
}

void	Player::respawn( int x, int y) {
	_x = x;
	_y = y;
}

void	Player::sprite( void ) {
	attron(CYAN);
	if (_y < 0)
		_y = 0;
	if (_x < 0)
		_x = 0;
	if (_y > _ymax - 1)
		_y = _ymax - 1;
	if (_x > _xmax - 2)
		_x = _xmax - 2;
	mvprintw(_y, _x, "**");
	attroff(CYAN);
	refresh();
}

void	Player::left( void ) { _x -= 2; }
void	Player::right( void ) { _x += 2; }
void	Player::up( void ) { _y--; }
void	Player::down( void ) { _y++; }
void	Player::update( void ) {

	if ((mvinch(_y, _x) & A_CHARTEXT) == '+' || (mvinch(_y, _x + 1) & A_CHARTEXT) == '+')
		G_GAMEOVER++;
	this->sprite();
}

void	Player::shoot( char dir ) { //Begins action chain:
	switch (dir) {
	case 'w' : fire(_x, _y, 0, -1, _c); break;
	case 's' : fire(_x, _y, 0, 1, _c); break;
	case 'a' : fire(_x, _y, -1, 0, _c); break;
	case 'd' : fire(_x + 1, _y, 1, 0, _c); break;
	default : break;
	}
}
