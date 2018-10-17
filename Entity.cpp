#include "Entity.hpp"

Entity::Entity( int x, int y) : _x(x), _y(y), _xmax(0), _ymax(0) { getmaxyx(stdscr, _ymax, _xmax); }
Entity::Entity( void ) { }
Entity::Entity( Entity const & cp ) { *this = cp; }
Entity::~Entity( void ) { }
Entity& Entity::operator=( Entity const & e ) {
	_x = e.getX();
	_y = e.getY();
	return *this;
}

int	Entity::getX( void ) const { return _x; }
int	Entity::getY( void ) const { return _y; }
