#ifndef OBJETO_H
#define OBJETO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace sf;

class Objeto {
public:
	Objeto(std::string nombreImagen);
	virtual void dibujar(RenderWindow &window);
	
	/**Un m�todo CollideWith que recibe un par�metro o de tipo 
	const Object &, que es otro objeto con el que se quiere comprobar 
	si hay colisi�n. El m�todo devuelve un valor booleano que indica 
	si los sprites de los dos objetos se solapan o no. Para ello, 
	usa el m�todo getGlobalBounds de los sprites, que devuelve un rect�ngulo 
	que engloba al sprite, y el m�todo intersects de los rect�ngulos, 
	que devuelve si se intersectan o no.**/
	bool CollideWith(const Objeto &o) const;
protected:
	Texture textura;
	Sprite sprite;
};

#endif

