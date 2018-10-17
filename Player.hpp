#ifndef PLAYER_H
# define PLAYER_H
# include "Entity.hpp"
# include "Weapon.hpp"
# include <ncurses.h>

class Player : public Entity, public Weapon {

public:
	Player( int x, int y );
	Player( void );
	Player( Player const & cp );
	virtual ~Player( void );
	Player & operator=( Player const & e );

	void	respawn( int x, int y );
	void	sprite( void );
	void	left( void );
	void	right( void );
	void	up( void );
	void	down( void );
	void	update( void );
	void	shoot( char dir );
};

#endif
