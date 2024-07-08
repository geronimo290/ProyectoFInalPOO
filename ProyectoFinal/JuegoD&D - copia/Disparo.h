#ifndef DISPARO_H
#define DISPARO_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

using namespace std;
using namespace sf;

class Disparo {
public:
	// cuando llamamops a la textura nos aseguramos que no sea copia con un &
	Disparo(Texture &flecha_tex, Vector2f pos, Vector2f dir);
	void actualizar();
	void dibujar(RenderWindow &win);
	
	Vector2f getPosition() const {
		return posicion;
	}
	
	void setPosition(const Vector2f& newPos) {
		posicion = newPos;
	}
private:
	Sprite flecha_spr;
	Vector2f vel;
	Vector2f posicion;

};

#endif

