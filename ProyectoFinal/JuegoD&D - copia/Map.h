#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
using namespace std;
using namespace sf;

class Map {
public:
	Map();
	string ver_nom_Mapa();
	Sprite ver_spr_Mapa();
	void dibujar(RenderWindow &window);
	bool colisionConPersonaje(const FloatRect& rectPersonaje) const;
private:
	//int mapa; //para administrar los mapas 
	Texture texmap;
	Sprite sprmap;
	string nom_map;
	// limites del mapa(paredes)
	RectangleShape rectLimites;
};
#endif

