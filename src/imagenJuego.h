/*
 *  imagenJuego.h
 *  pepa
 *
 *  Created by Created by natxo on 09/11/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *	
	
	Clase que contiene las imagenes para el juego, cada instancia contiene:

	- una imagen
	- dos botones
	- una mascara para ir desvelandose
	- un evento que se dispara cuando se ha seleccionado uno de los botones
 
	- var donde: si es coruña o cadiz
	- var timer: es una cuenta atras, que indica los ptos que vas a obtener
	  cuanto mas rapido seas en decidir mas ptos te llevas
	- var ptos
 *	
 *	
 */

#ifndef IMAGEN_JUEGO
#define IMAGEN_JUEGO

#include "ofMain.h"

//#include "ofxTimer.h"

class imagenJuego {
public:
	imagenJuego();
    
    void    setup(string rutaImagen,string _ciudad,string _msg);
	void    update();
	void    draw();

    ofImage imagen;
    string  ciudad;
    string  msg;
private:
	void    timeOut(ofEventArgs & args);

//	ofxTimer    temporizador;
	
    float   tiempo;
    int     ptos;
};
#endif