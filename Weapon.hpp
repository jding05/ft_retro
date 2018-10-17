#ifndef WEAPON_H
# define WEAPON_H
# include "Bullet.hpp"
# include <ncurses.h>

class Weapon {

typedef struct s_proj
{
	Bullet *	ammo;
	struct s_proj *next;
	struct s_proj *prev;
}			t_proj;
public:
	Weapon( char c);
	Weapon( void );
	Weapon( Weapon const & cp );
	virtual ~Weapon( void );
	Weapon& operator=( Weapon const & e );

	void	update( void );

protected:
	struct s_proj*	getHead( void ) const;
	char	getC( void ) const;
	void	fire( int x, int y, int dx, int dy, char c );
	t_proj	*_head;
	char	_c;

private:
	int		_count;
};

#endif
