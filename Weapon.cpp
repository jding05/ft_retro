#include "Weapon.hpp"

Weapon::Weapon( char c ) : _head(NULL), _c(c), _count(0) { }
Weapon::Weapon( void ) : _head(NULL), _c('!'), _count(0) { }
Weapon::Weapon( Weapon const & cp ) { *this = cp; }
Weapon::~Weapon( void ) { }
Weapon&	Weapon::operator=( Weapon const & e ) {
	t_proj	*temp;
	t_proj	*free;
	temp = _head;
	while (temp)
	{
		free = temp;
		temp = temp->next;
		free->next = NULL;
		free->prev = NULL;
		delete free->ammo;
		free->ammo = NULL;
		delete free;
	}

	t_proj *another;
	temp = e.getHead();
	_head = temp;
	another = _head;
	while (temp)
	{
		if (temp == NULL)
			break;
		another->ammo = new Bullet(temp->ammo->getX(),
		temp->ammo->getY(), temp->ammo->getDx(), temp->ammo->getDy(), temp->ammo->getC());
		temp = temp->next;
		if (temp->next == NULL)
			another->next = NULL;
		else
			another->next = new t_proj;
		another = another->next;
	}
	return *this;
}

struct Weapon::s_proj*	Weapon::getHead( void ) const { return _head; }
char	Weapon::getC( void ) const { return _c; }

//Called by Player::update to iterate linked list of bullets, calls Bullet::move
void	Weapon::update( void ) {
	t_proj *temp;
	t_proj	*free;

	temp = _head;
	while (temp)
	{
		if (temp->ammo)
			temp->ammo->move();
		if (temp->ammo->getHit())
		{
			_count--;
			free = temp;
			if (free->prev)
				free->prev->next = free->next;
			else
				_head = _head->next;
			if (free->next)
				free->next->prev = free->prev;
			temp = temp->next;
			delete free->ammo;
			delete free;
		}
		else
			temp = temp->next;
	}
}

//Called by Player::shoot to append new bullet to list
void	Weapon::fire( int x, int y, int dx, int dy, char c) {
	if (_count < G_BULLS)
	{
		Bullet *fresh = new Bullet( x, y, dx, dy, c );
		t_proj	*app = new t_proj;

		_count++;
		app->prev = NULL;
		app->next = NULL;
		app->ammo = fresh;
		if (_head != NULL)
		{
			t_proj	*temp;

			temp = _head;
			while (temp->next)
				temp = temp->next;
			app->prev = temp;
			app->next = NULL;
			temp->next = app;
			app->ammo = fresh;
		}
		else
			_head = app;
	}
}
