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
representa un rectángulo con coordenadas de punto flotante. La variable se 
inicializa con el valor que devuelve el método getGlobalBounds del atributo 
m_sprite, que es de tipo sf::Sprite. El método getGlobalBounds devuelve un 
rectángulo que engloba al sprite, es decir, el área mínima que ocupa el sprite 
en la pantalla.
La tercera línea hace lo mismo que la segunda, pero con el objeto que se pasa 
como parámetro (o). Crea una variable local llamada r2 de tipo sf::FloatRect que 
se inicializa con el rectángulo que engloba al sprite del objeto o.
La cuarta línea devuelve el resultado de llamar al método intersects de la 
clase sf::FloatRect, que recibe como parámetro otro rectángulo (r2) y 
devuelve un valor booleano que indica si los dos rectángulos se solapan o no. 
Es decir, si los sprites de los dos objetos se tocan o no en la pantalla.*/
