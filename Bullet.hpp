#ifndef BULLET_H
# define BULLET_H
# include <ncurses.h>
# include "Include.hpp"
# include "Entity.hpp"
class Bullet : public Entity {

public:
	Bullet( int x, int y , int dx, int dy, char c);
	Bullet( void );
	Bullet( Bullet const & cp );
	~Bullet( void );
	Bullet & operator=( Bullet const & e );

	void	move( void );
	bool	getHit( void ) const;
	bool	collide( void );

	int		getDx( void ) const;
	int		getDy( void ) const;
	char	getC( void ) const;
	void	sprite( void );

private:
	int		_x;
	int		_y;
	int		_dx;
	int		_dy;
	char	_c;
	bool	_hit;
};

#endif
