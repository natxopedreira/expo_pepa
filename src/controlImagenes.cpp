//
//  controlImagenes.cpp
//  pepa
//
//  Created by natxo on 09/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "controlImagenes.h"

void controlImagenes::setup(){
    Tweenzor::init();
    
    /// video que usaremos para enmascarar
    mascaraVideo.loadMovie("Comp 1.mp4", OF_QTKIT_DECODE_PIXELS_AND_TEXTURE);
    mascaraVideo.setPosition(0.01);
    
    mascara.allocate(800, 600);
    
    cargaFichas();

    puntos = 0;
    indexFicha = 0;
    alphaBotones = 0;
    
    /// botones para seleccioar ciudad
    botonCoruna.setup(200, 550, "coru", "btn/coru.png");
    botonCadiz.setup(450, 550, "cadiz", "btn/cadiz.png");

    ofAddListener(botonCoruna.seleccionBoton, this,  &controlImagenes::botonCiudad);
    ofAddListener(botonCadiz.seleccionBoton, this,  &controlImagenes::botonCiudad);
    
    /// sonidos para indicar acierto/fallo
    sndAcierto.loadSound("Temple.aiff");
    sndFallo.loadSound("Wild Eep.aiff");
    
    fuenteMarcador.loadFont("GothamRounded-Book.otf", 108);
    fuenteLeyenda.loadFont("GothamRounded-Book.otf", 14);
    
    /// timer para la partida, 2 minutos
    tiempoPartida.setup(120000, false); // iniciamos el timer
    tiempoPartida.startTimer();
}
void controlImagenes::cargaFichas(){
    
    /// cargaremos desde un xml
    /// ahora mismo esta asi para ver
    imagenJuego * ficha0 = new imagenJuego();
    ficha0->setup("nature.jpg", "coru");
    
    imagenJuego * ficha1 = new imagenJuego();
    ficha1->setup("daisy_yellow_nature_flower.jpg", "cadiz");
    
    imagenJuego * ficha2 = new imagenJuego();
    ficha2->setup("nature-bani-flickr.jpg", "coru");
    
    imagenJuego * ficha3 = new imagenJuego();
    ficha3->setup("nature-paintings-free-screensaver-1.jpg", "cadiz");
    
    fichas.push_back(ficha0);
    fichas.push_back(ficha1);
    fichas.push_back(ficha2);
    fichas.push_back(ficha3);
}

void controlImagenes::update(){
    
    Tweenzor::update( ofGetElapsedTimeMillis() );
    
    ofSoundUpdate();
    
    mascaraVideo.update();
    fichas.at(indexFicha)->update();
    
    mascara.begin(0);
    mascaraVideo.draw(-20, -35, 800,700);
    mascara.end(0);
    
    mascara.begin(1);
    fichas.at(indexFicha)->imagen.draw(80, 60);
    mascara.end(1);
    
    mascara.update();
    
    botonCoruna.update();
    botonCadiz.update();
}

void controlImagenes::draw(){
    mascara.draw();
    
    /// debug para ver la zona de la foto
    ofPushStyle();
        ofNoFill();
        ofRect(80, 60, 640, 480);
    ofPopStyle();
    
    
    /// display del marcador de tiempo de la foto
    fichas.at(indexFicha)->draw();
    
    
    
    /// debug de mascara
    //mascaraVideo.draw(850, 0,320,240);
    
    
    /// botones de seleccion de ciudad
    ofPushStyle();
        ofSetColor(255,255,255,alphaBotones);
        botonCoruna.draw();
        botonCadiz.draw();
    ofPopStyle();
    
    
    /// estos son tus puntos
    /// mejor siempre dos digitos
    fuenteLeyenda.drawString("su puntuacion", 910, 385);
    if(puntos<10){
        fuenteMarcador.drawString("0"+ofToString(puntos), 890, 500);
    }else{
        fuenteMarcador.drawString(ofToString(puntos), 890, 500);
    }
    
    
    // marcador de tiempo restante
    fuenteLeyenda.drawString("tiempo restante", 890, 90);
    fuenteMarcador.drawString(ofToString((int)tiempoPartida.getTimeLeftInSeconds()), 890, 200);
    
}

void controlImagenes::lanzaFicha(){
    /// lanzas una imagen
    
    alphaBotones = 0;
    if(indexFicha<fichas.size()-1){
        indexFicha ++;
    }else{
        indexFicha = 0;
    }
    
    mascaraVideo.setPosition(0.01);
    mascaraVideo.play();
    
    fichas.at(indexFicha)->temporizador.reset();
    fichas.at(indexFicha)->temporizador.startTimer();
    
    Tweenzor::add(&alphaBotones, 0, 255, 0.5f, 3.f);
    
    botonCoruna.activo = true;
    botonCadiz.activo = true;
}

void controlImagenes::botonCiudad(string & s){
    /// has escojido una ciudad
    
    cout << "boton:: " << s << endl;
    
    botonCoruna.activo = false;
    botonCadiz.activo = false;

    if(mascaraVideo.isPlaying()) mascaraVideo.setPaused(true);
    fichas.at(indexFicha)->temporizador.pauseTimer();
    
    // comprobamos si es correcto o no TODO
    if(fichas.at(indexFicha)->ciudad == s){
        // sumamos los ptos si has acertado
        cout << "sumas " <<  fichas.at(indexFicha)->ptos << " ptos." << endl;
        puntos += fichas.at(indexFicha)->ptos;
        sndAcierto.play();
    }else{
        sndFallo.play();
    }
}
