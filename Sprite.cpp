#include "Sprite.hpp"

Sprite::Sprite( int x, int y ) : Entity( x, y ) { }
Sprite::Sprite( void ) { }
Sprite::Sprite( Sprite const & cp ) { *this = cp; }
Sprite::~Sprite( void ) { _x = 0, _y = 0; _ymax = 0; _xmax = 0;}
Sprite& Sprite::operator=( Sprite const & e ) {
	_x = e.getX();
	_y = e.getY();
	return *this;
}

void	Sprite::fly( void ) {
	attron(COLOR_MAGENTA);
	mvprintw(_y + 0, _x,  "              ##### | #####");
	mvprintw(_y + 1, _x,  "             # _ _ #|# _ _ #");
	mvprintw(_y + 2, _x,  "             #      |      #");
	mvprintw(_y + 3, _x,  "       |       ############");
	mvprintw(_y + 4, _x,  "                   # #");
	mvprintw(_y + 5, _x,  "|                  # #");
	mvprintw(_y + 6, _x,  "                  #   #");
	mvprintw(_y + 7, _x,  "       |     |    #   #      |        |");
	mvprintw(_y + 8, _x,  "|  |             #     #               |");
	mvprintw(_y + 9, _x,  "       | |   |   # .-. #         |");
	mvprintw(_y + 10, _x,  "                 #( O )#    |    |     |");
	mvprintw(_y + 11, _x,  "|  ################. .###############  |");
	mvprintw(_y + 12, _x,  " ##  _ _|____|     ###     |_ __| _  ##");
	mvprintw(_y + 13, _x,  "#  |                                |  #");
	mvprintw(_y + 14, _x,  "#  |    |    |    |   |    |    |   |  #");
	mvprintw(_y + 15, _x,  " ######################################");
	mvprintw(_y + 16, _x,  "                 #     #");
	mvprintw(_y + 17,_x , "                  #####");
	mvprintw(_y + 18, _x, "             OOOOOOO|OOOOOOO");
	mvprintw(_y + 19, _x, "                    U");
	attroff(COLOR_MAGENTA);
}

void	Sprite::sprite( void ) {
	attron(COLOR_PAIR(0));
	mvprintw(_y, _x + 0,"               _  _");
	mvprintw(_y + 1, _x,"              ( `   )_");
	mvprintw(_y + 2, _x,"             (    )    `)");
	mvprintw(_y + 3, _x,"           (_   (_ .  _) _)");
	mvprintw(_y + 4, _x,"                                         _");
	mvprintw(_y + 5, _x,"                                        (  )");
	mvprintw(_y + 6, _x,"             _ .                     ( `  ) . )");
	mvprintw(_y + 7, _x,"           (  _ )_                  (_, _(  ,_)_)");
	mvprintw(_y + 8, _x,"         (_  _(_ ,)");
	attroff(COLOR_PAIR(0));
}

void	Sprite::move( void ) {
	_x--;
	if (_x < -250)
	{
		_x = _xmax + (rand() % 100);
	}
}

bool	Sprite::drop( void ) {
	if (_y > 100)
		return true;
	_y += 1;
	return false;
}

bool	Sprite::reachEnd( void ) { return _y == _ymax; }
