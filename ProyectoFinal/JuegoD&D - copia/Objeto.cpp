#include "Objeto.h"

Objeto::Objeto(std::string nombreImagen) {
	textura.loadFromFile(nombreImagen);
	sprite.setTexture(textura);
	
}

void Objeto::dibujar(RenderWindow &window) {
	window.draw(sprite);
}

bool Objeto::CollideWith (const Objeto & o) const {
	auto r1 = this->sprite.getGlobalBounds();
	auto r2 = o.sprite.getGlobalBounds();
	return r1.intersects(r2);
}
 /*variable local llamada r1 de tipo sf::FloatRect, que es una clase que 
representa un rect�ngulo con coordenadas de punto flotante. La variable se 
inicializa con el valor que devuelve el m�todo getGlobalBounds del atributo 
m_sprite, que es de tipo sf::Sprite. El m�todo getGlobalBounds devuelve un 
rect�ngulo que engloba al sprite, es decir, el �rea m�nima que ocupa el sprite 
en la pantalla.
La tercera l�nea hace lo mismo que la segunda, pero con el objeto que se pasa 
como par�metro (o). Crea una variable local llamada r2 de tipo sf::FloatRect que 
se inicializa con el rect�ngulo que engloba al sprite del objeto o.
La cuarta l�nea devuelve el resultado de llamar al m�todo intersects de la 
clase sf::FloatRect, que recibe como par�metro otro rect�ngulo (r2) y 
devuelve un valor booleano que indica si los dos rect�ngulos se solapan o no. 
Es decir, si los sprites de los dos objetos se tocan o no en la pantalla.*/
