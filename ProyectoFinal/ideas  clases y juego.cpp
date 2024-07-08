#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

//tipo de arma = mostrar sprite de ataque en pantalla 


class Ataque {
protected:
	float danio;
	float alcance;
	// velociudad del ataque
public:
	Ataque(float d, float a) : danio(d), alcance(a) {}
	
	virtual void ejecutar_ataque() = 0;
	
	void set_danio(float nuevo_danio) { danio = nuevo_danio; }
	float get_danio() const { return danio; }
	
	void set_alcance(float nuevo_alcance) { alcance = nuevo_alcance; }
	float get_alcance() const { return alcance; }
};

class Arma {
protected:
	Ataque& ataque;
	
public:
	Arma(Ataque& a) : ataque(a) {}
	
	void atacar() {
		ataque.ejecutar_ataque();
	}
};

class AtaqueCortaDistancia : public Ataque {
	
	//aca tendria que tener el atributo del tipo de arma para segun que tipo de arma asignarle el sprite y cambiar asi tmabien las variables de daño?
	// porque tenemeos 3 ataque de distancia corta que hacen distinto daño
	// y es algo que se tiene que cambiar segun el personaje (el oso con el palo, el mercenario con las dagas y el zorro con los puños)
	// el oso > marcenario > zorro
	// en velocidad de los ataques 
	// el oso es mas lento, el mercenario normal y el zorro mas rapido
	
public:
	AtaqueCortaDistancia(float d, float a) : Ataque(d, a) {}
	
	void ejecutar_ataque() override {
		cout << "Ataque de corta distancia. Danio: " << get_danio() << ", Alcance: " << get_alcance() << endl;
	}
};

class AtaqueMediaDistancia : public Ataque {
public:
	AtaqueMediaDistancia(float d, float a) : Ataque(d, a) {}
	
	void ejecutar_ataque() override {
		cout << "Ataque de media distancia. Danio: " << get_danio() << ", Alcance: " << get_alcance() << endl;
	}
};

class AtaqueLargaDistancia : public Ataque {
public:
	AtaqueLargaDistancia(float d, float a) : Ataque(d, a) {}
	
	void ejecutar_ataque() override {
		cout << "Ataque de larga distancia. Danio: " << get_danio() << ", Alcance: " << get_alcance() << endl;
	}
};

class Personaje {
private:
	//velocidad de movimiento
	//vida
	//
	Arma& arma;
	
public:
	Personaje(Arma& a) : arma(a) {}
	
	void atacar() {
		arma.atacar();
	}
};

int main() {
	AtaqueCortaDistancia ataque_corta(15.0f, 5.0f);
	Arma arma_corta(ataque_corta);
	
	AtaqueMediaDistancia ataque_media(10.0f, 20.0f);
	Arma arma_media(ataque_media);
	
	AtaqueLargaDistancia ataque_larga(5.0f, 50.0f);
	Arma arma_larga(ataque_larga);
	
	Personaje personaje_corta(arma_corta);
	Personaje personaje_media(arma_media);
	Personaje personaje_larga(arma_larga);
	
	personaje_corta.atacar();
	personaje_media.atacar();
	personaje_larga.atacar();
	
	return 0;
}
