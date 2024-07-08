#include <SFML/Graphics.hpp>
#include "Personaje.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <iostream>
#include "Enemigo.h"
#include "Map.h"
using namespace std;
using namespace sf;

int main(int argc, char *argv[]){
	VideoMode vm(1920,1080);
	RenderWindow win(vm,"Ejemplo ProyectoFinal");
	win.setFramerateLimit(60);
	
	Map map;
	
	Personaje p1;
	vector<Disparo> vect_disparos;
	Texture flecha_tex;
	
	Enemigo e1;

	while(win.isOpen()) {
		Event e;
		while(win.pollEvent(e)) {
			if(e.type == Event::Closed)
				win.close();	
		}
		// Cargamos las texturas del Disparo	
		if (! flecha_tex.loadFromFile("flecha.png")) {
			cerr << "Error al cargar la imagen" << endl;
		}
		
		
		p1.actualizar();
		e1.actualizar(p1);
		
		//el personaje me dice si tengo que disparar o no y si hay que disparar el tanque genra el disparo pero el disparo lo guardamos en el vector del main
		if (p1.debeDisparar()) vect_disparos.push_back(p1.GenerarDisparo(flecha_tex));
		for(Disparo &disparo : vect_disparos)disparo.actualizar();
		
		win.clear(Color(255,255,255,255));
		//win.draw(map.ver_spr_Mapa());
		map.dibujar(win);
		
		p1.dibujar(win);
		
		// Verificar colisiones con el mapa
		if (!map.colisionConPersonaje(p1.rectColision)) {
			// Si no hay colisión, permitir el movimiento del personaje
			p1.dibujar(win);
		}

		//Enemigo
		e1.dibujar(win);
		e1.establecerTiempoEspera(3.0f);
		
		
		for(Disparo &disparo : vect_disparos)disparo.dibujar(win);
		win.display();
		
	}
	return 0;
}

