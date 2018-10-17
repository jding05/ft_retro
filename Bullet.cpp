#include "Bullet.hpp"

Bullet::Bullet( int x, int y , int dx, int dy, char c ) : Entity(x, y),
							_x(x), _y(y), _dx(dx), _dy(dy), _c(c), _hit(0) { }
Bullet::Bullet( void ) : Entity(), _x(0), _y(0), _dx(0), _dy(0), _c(0), _hit(0) { }
Bullet::Bullet( Bullet const & cp ) { *this = cp; }
Bullet::~Bullet( void ) {
	_x = 0;
	_y = 0;
	_dx = 0;
	_dy = 0;
	_c = 0;
	_hit = 0;
}

Bullet&	Bullet::operator=( Bullet const & e ) {
	_x = e.getX();
	_y = e.getY();
	_dx = e.getDx();
	_dy = e.getDy();
	_c = e.getC();
	_hit = e.getHit();
	return *this;
}

int		Bullet::getDx( void ) const { return _dx; }
int		Bullet::getDy( void ) const { return _dy; }
char	Bullet::getC( void ) const { return _c; }
void	Bullet::sprite( void ) {
	mvaddch(_y, _x, _c);
}

// Called by Weapon::update called by Player::update to either print or pop bullet in list
void	Bullet::move( void ) {
	_x += _dx;
	_y += _dy;
	if ((mvinch(_y, _x) & A_CHARTEXT) == '#' && _c == '*' && G_KILL >= NUM)
		G_BOSS++;
	if (_y < 0 || _x < 0 || _y > _ymax || _x > _xmax)
	{
		_hit = true;
	}
	else
	{
		_c == '*' ?	attron(GREEN) : attron(YELLOW);
		this->sprite();
		_c == '*' ?	attroff(GREEN) : attroff(YELLOW);
	}

}

bool	Bullet::getHit( void ) const { return _hit; }
