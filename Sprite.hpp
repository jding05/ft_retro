#ifndef SPRITE_H
# define SPRITE_H
# include "Entity.hpp"
# include "Include.hpp"
# include <string>

class Sprite : virtual public Entity {

public:
	Sprite( int x, int y );
	Sprite( void );
	Sprite( Sprite const & cp );
	virtual ~Sprite( void );
	Sprite & operator=( Sprite const & e );

	void	fly( void );
	void	move( void );
	bool	drop( void );
	bool	reachEnd( void );
	void	sprite( void );
};

#endif
