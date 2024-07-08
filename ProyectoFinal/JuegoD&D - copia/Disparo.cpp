#include "Disparo.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

Disparo::Disparo(Texture &flecha_tex,Vector2f pos, Vector2f dir) {

	// Establecemos la textura en el sprite
	flecha_spr.setTexture(flecha_tex);
	flecha_spr.setScale(.75,.75);
	flecha_spr.setPosition(pos);
	flecha_spr.setOrigin(100,100);
	flecha_spr.rotate(atan2(dir.y,dir.x)*180/M_PI);
	vel = dir*2.f;
}

void Disparo::actualizar(){
	flecha_spr.move(vel);
}

void Disparo::dibujar(RenderWindow &win){
	win.draw(flecha_spr);
}
