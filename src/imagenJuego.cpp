/*
 *  imagenJuego.cpp
 *  pepa
 *
 *  Created by natxo on 09/11/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "imagenJuego.h"

imagenJuego::imagenJuego(){
	ptos = 0;
}

void imagenJuego::setup(string rutaImagen, string _ciudad){
	
	imagen.loadImage(rutaImagen); // cargamos la imagen
    
    ciudad = _ciudad;
    
	temporizador.setup(15000, false); // iniciamos el timer
    temporizador.stopTimer();
    
	ofAddListener(temporizador.TIMER_REACHED, this, &imagenJuego::timeOut); // listener tiempo finalizado

}

void imagenJuego::update(){
  
	if(!temporizador.isTimerFinished()){
		ptos = temporizador.getTimeLeftInSeconds();
		ptos = ptos + 1; /// para que por lo menos si se acaba el tiempo y aciertas te lleves 1 pto
	}
}

void imagenJuego::timeOut(ofEventArgs & args){
	
}

void imagenJuego::draw(){
	ofDrawBitmapString("tiempo:: " + ofToString(ptos), ofPoint(50,50));
}
