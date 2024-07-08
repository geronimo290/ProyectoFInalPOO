#include "Map.h"
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
using namespace std;
using namespace sf;

Map::Map(){
	
	if (!texmap.loadFromFile("exterior.png")) {
		cerr << "Error al cargar la imagen" << endl;
	}
	
	sprmap.setTexture(texmap);
	
	/// Configurar los l�mites del mapa
	//Define el tama�o del rect�ngulo con dimensiones calculadas espec�ficas
	rectLimites.setSize(sf::Vector2f(1920 - 310 - 380, 1080 - 220 - 220));
	//Establece la posici�n (esquina superior izquierda) del rect�ngulo rectLimites en las coordenadas (310, 260)
	rectLimites.setPosition(270, 220);
	//Configura el color de relleno del rect�ngulo rectLimites como transparente
	rectLimites.setFillColor(Color::Transparent);
	//Establece el color del contorno del rect�ngulo rectLimites como blanco
	rectLimites.setOutlineColor(sf::Color::White);
	//Define el grosor del contorno del rect�ngulo rectLimites como 2 p�xeles
	rectLimites.setOutlineThickness(2.f);
	
}

string Map::ver_nom_Mapa(){
	return nom_map;
}

Sprite Map::ver_spr_Mapa(){
	return sprmap;
}

void Map::dibujar(RenderWindow &window) {
	window.draw(sprmap);
	//dibujar los limites del mapa 
	window.draw(rectLimites);
}

// Funci�n para verificar colisiones con el personaje
bool Map::colisionConPersonaje(const FloatRect& rectPersonaje) const {
	return rectLimites.getGlobalBounds().intersects(rectPersonaje);
}

