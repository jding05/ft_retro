#ifndef ENTITY_H
# define ENTITY_H
# include "Include.hpp"
# include <ncurses.h>

class Entity {

public:
	Entity( int x, int y );
	Entity( void );
	Entity( Entity const & cp );
	virtual ~Entity( void );
	Entity & operator=( Entity const & e );

	int	getX( void ) const;
	int getY( void ) const;

protected:
	virtual void	sprite( void ) = 0;
	int	_x;
	int	_y;
	int	_xmax;
	int	_ymax;
};

#endif
