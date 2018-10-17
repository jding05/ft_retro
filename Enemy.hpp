#ifndef ENEMY_H
# define ENEMY_H
# include "Entity.hpp"
# include "Weapon.hpp"
# include <stdlib.h>
# include <ncurses.h>

class Enemy : public Entity , public Weapon {

public:
	Enemy( int x, int y );
	Enemy( void );
	Enemy( Enemy const & cp );
	virtual ~Enemy( void );
	Enemy & operator=( Enemy const & e );
	void	update( void );
	void	setMaxs( int xmax, int ymax );

protected:
	void	sprite( void );
	void	left( void );
	void	right( void );
	void	up( void );
	void	down( void );
	void	shoot( void );
};

#endif
