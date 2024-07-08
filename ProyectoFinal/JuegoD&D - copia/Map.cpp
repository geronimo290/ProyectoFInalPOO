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
	
	/// Configurar los límites del mapa
	//Define el tamaño del rectángulo con dimensiones calculadas específicas
	rectLimites.setSize(sf::Vector2f(1920 - 310 - 380, 1080 - 220 - 220));
	//Establece la posición (esquina superior izquierda) del rectángulo rectLimites en las coordenadas (310, 260)
	rectLimites.setPosition(270, 220);
	//Configura el color de relleno del rectángulo rectLimites como transparente
	rectLimites.setFillColor(Color::Transparent);
	//Establece el color del contorno del rectángulo rectLimites como blanco
	rectLimites.setOutlineColor(sf::Color::White);
	//Define el grosor del contorno del rectángulo rectLimites como 2 píxeles
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

// Función para verificar colisiones con el personaje
bool Map::colisionConPersonaje(const FloatRect& rectPersonaje) const {
	return rectLimites.getGlobalBounds().intersects(rectPersonaje);
}

