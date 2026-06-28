#include <SFML/Graphics.hpp>
#include "parser/parser_rules.hpp"

int main(int argc, char *argv[])
{
	// Чтение файла и его парсинг
	std::string rules = argv[1];
	// std::cout << rules << "\n\n";
	Parser parser;
	parser.init(rules);
	parser.Read_all_rules();

	
	sf::RenderWindow window( sf::VideoMode( { 640, 640 } ), "Life" );
	sf::CircleShape shape( 100.f );
	shape.setFillColor( sf::Color::Green );

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		window.draw( shape );
		window.display();
	}
	
}
