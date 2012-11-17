//
//  controlImagenes.cpp
//  pepa
//
//  Created by natxo on 09/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "controlImagenes.h"

//--------------------------------------------------------------
void controlImagenes::setup(){
    Tweenzor::init();
    
    /// video que usaremos para enmascarar
    mascaraVideo.setPixelFormat(OF_PIXELS_RGB);
   
    mascaraVideo.loadMovie("mascara.mov", OF_QTKIT_DECODE_PIXELS_AND_TEXTURE);
    mascaraVideo.setLoopState(OF_LOOP_NONE);
    mascaraVideo.play();
    
    mascara.allocate(800, 600);

    /// botones para seleccioar ciudad
    botonCoruna.setup(10, 20, "coru", "btn/coru.png");
    botonCadiz.setup(10, 20, "cadiz", "btn/cadiz.png");

    ofAddListener(botonCoruna.seleccionBoton, this,  &controlImagenes::botonCiudad);
    ofAddListener(botonCadiz.seleccionBoton, this,  &controlImagenes::botonCiudad);
    
    /// sonidos para indicar acierto/fallo
    sndAcierto.loadSound("Temple.aiff");
    sndFallo.loadSound("Wild Eep.aiff");
    
    fuenteMarcador.loadFont("BodoniXT.ttf", 130);
    fuenteLeyenda.loadFont("BodoniXT.ttf", 30);
    fuenteAlerta.loadFont("BodoniXT.ttf", 70);
    
    /// timer para la partida, 2 minutos
    tiempoPartida.setup(480000, false); // iniciamos el timer
    
    
    /// timer para el paso entre fotos
    tiempoEntreFoto.setup(1500, false); // iniciamos el timer
    tiempoEntreFoto.stopTimer();
    
    ofAddListener(tiempoEntreFoto.TIMER_REACHED, this, &controlImagenes::cambiaFoto);
    ofAddListener(tiempoPartida.TIMER_REACHED, this, &controlImagenes::finTiempoPartida);
    
    cargaFichas(); // creamos el vector con las imagenes
    
    configViewPorts(); // cargamos los fbos para los viewports
    
    iniciaPartida(); // setea vars y lanza fichas

}

//--------------------------------------------------------------
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

//--------------------------------------------------------------
void controlImagenes::update(){
    mascaraVideo.update();
    Tweenzor::update( ofGetElapsedTimeMillis() );
    ofSoundUpdate();
    
    fichas.at(indexFicha)->update();
    
    
    if(mascaraVideo.isFrameNew()){
        //si el frame del video es nuevo update la mascara
        
        mascara.begin(0);
            mascaraVideo.draw(-20, -35, 800,700);
        mascara.end(0);
        
        mascara.begin(1);
            ofSetColor(255,255,255);
            fichas.at(indexFicha)->imagen.draw(80, 60);
        mascara.end(1);
    
        mascara.update();
    }

    ///// renderizas los fbos para dar de comer a los viewports
    renderViewports();
    
    
    botonCoruna.screenPosx = viewportCoru.getPos().x-(viewportCoru.getWidth()/2);
    botonCoruna.screenPosy = viewportCoru.getPos().y-(viewportCoru.getHeight()/2);
    
    botonCadiz.screenPosx = viewportCadiz.getPos().x-(viewportCadiz.getWidth()/2);
    botonCadiz.screenPosy = viewportCadiz.getPos().y-(viewportCadiz.getHeight()/2);
    
    
    botonCoruna.update();
    botonCadiz.update();
}

//--------------------------------------------------------------
void controlImagenes::draw(){
    /// cada cosa sale en un viewport con mapping y mascara
    viewportMascara.draw(mascara.getTextureReference());
    viewportAciertos.draw(fboAciertos.getTextureReference());
    viewportTiempo.draw(fboTiempo.getTextureReference());
    viewportCoru.draw(fboCou.getTextureReference());
    viewportCadiz.draw(fboCadiz.getTextureReference());
    
    if(mensaje){
        ofPushStyle();
        // acabas de pulsar una opcion y esto dice ok o fallo
        ofSetColor(255, 255, 255, alphaMsjStr);
        fuenteAlerta.drawString(ofToString(mensajeStr), 200, 280);
        
        ofPopStyle();
    }
}
//--------------------------------------------------------------
void controlImagenes::renderViewports(){
    
    
    fboAciertos.begin();
    ofClear(0);
    ofSetColor(255,255,255);
    /// estos son tus puntos
    /// mejor siempre dos digitos
    fuenteLeyenda.drawString("aciertos", 20, 190);
    if(puntos<10){
        fuenteMarcador.drawString("0"+ofToString(puntos), 0, 150);
    }else{
        fuenteMarcador.drawString(ofToString(puntos), 0, 150);
    }
    
    fboAciertos.end(); 
    
    
    fboTiempo.begin();
    ofClear(0);
    ofSetColor(255,255,255);
    // marcador de tiempo restante
    if(!partidaTerminada){
        int minutos = (int)tiempoPartida.getTimeLeftInSeconds()/60;
        int segundos = (int)tiempoPartida.getTimeLeftInSeconds() % 60;
        
        if(segundos<10){
            fuenteMarcador.drawString(ofToString(minutos)+":0"+ofToString(segundos), 0, 150);
        }else{
            fuenteMarcador.drawString(ofToString(minutos)+":"+ofToString(segundos), 0, 150);
        }
    }
    fboTiempo.end();
    
    
    fboCou.begin();
        ofClear(0);
        /// botones de seleccion de ciudad
        ofPushStyle();
        ofSetColor(255,255,255,alphaBotones);
        botonCoruna.draw();
        ofPopStyle();
    fboCou.end();  
    
    fboCadiz.begin();
        ofClear(0);
        /// botones de seleccion de ciudad
        ofPushStyle();
        ofSetColor(255,255,255,alphaBotones);
        botonCadiz.draw();
        ofPopStyle();
    fboCadiz.end(); 

}

//--------------------------------------------------------------
void controlImagenes::configViewPorts(){
    fboMascara.allocate(800, 600);
    fboImagen.allocate(640, 480);
    fboAciertos.allocate(320, 240);
    fboCou.allocate(320, 240);
    fboCadiz.allocate(320, 240);
    fboTiempo.allocate(320, 240);
    
    
    fboImagen.begin();
    ofClear(0);
    fboImagen.end(); 
    
    fboAciertos.begin();
    ofClear(0);
    fboAciertos.end(); 
    
    fboCou.begin();
    ofClear(0);
    fboCou.end();  
    
    fboCadiz.begin();
    ofClear(0);
    fboCadiz.end(); 
    
    fboTiempo.begin();
    ofClear(0);
    fboTiempo.end();
    
    viewportImagen.loadSettings(0);
    viewportAciertos.loadSettings(1);
    viewportMascara.loadSettings(2);
    viewportCoru.loadSettings(3);
    viewportCadiz.loadSettings(4);
    viewportTiempo.loadSettings(5);
}

//--------------------------------------------------------------
void controlImagenes::iniciaPartida(){
    puntos = 0;
    indexFicha = 0;
    alphaBotones = 0;
    partidaTerminada = false;
    mensaje = false;
    alphaMsjStr = 0;
    scaleMsjStr = 0;
    
    tiempoPartida.reset();
    tiempoEntreFoto.reset();
    
    lanzaFicha();
    
    tiempoPartida.startTimer();
}

//--------------------------------------------------------------
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
    
    Tweenzor::add(&alphaBotones, 0, 255, 0.5f, 3.f,EASE_IN_OUT_SINE);
    
    botonCoruna.activo = true;
    botonCadiz.activo = true;
    
    mensajeStr = "";
    alphaMsjStr = 0;
    
}

//--------------------------------------------------------------
void controlImagenes::botonCiudad(string & s){
    /// has escojido una ciudad
    
    cout << "boton:: " << s << endl;
    
    botonCoruna.activo = false;
    botonCadiz.activo = false;

    if(mascaraVideo.isPlaying()) mascaraVideo.setPaused(true);
    
    // comprobamos si es correcto o no TODO
    if(fichas.at(indexFicha)->ciudad == s){
        // sumamos los ptos si has acertado
        puntos ++;
        mensajeRespuesta("correcto");
    }else{
        mensajeRespuesta("error");
    }
}

//--------------------------------------------------------------
void controlImagenes::mensajeRespuesta(string s){
    mensajeStr = s;
    mensaje = true;
    Tweenzor::add(&alphaMsjStr, 0, 255, 0.0f, 0.3f,EASE_IN_OUT_QUAD);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&alphaMsjStr), this, &controlImagenes::onCompleteMsg);
}

//--------------------------------------------------------------
void controlImagenes::onCompleteMsg(float* arg) {
    if(mensajeStr == "correcto"){
        sndAcierto.play();
    }else if (mensajeStr == "error") {
        sndFallo.play();
    }
    tiempoEntreFoto.startTimer();
}
//--------------------------------------------------------------
void controlImagenes::guardaPosiciones(){
    viewportImagen.saveSettings();
    viewportAciertos.saveSettings();
    viewportMascara.saveSettings();
    viewportCoru.saveSettings();
    viewportCadiz.saveSettings();
    viewportTiempo.saveSettings();

}
//--------------------------------------------------------------
void controlImagenes::cambiaFoto(ofEventArgs & args){
    lanzaFicha();
}

//--------------------------------------------------------------
void controlImagenes::finTiempoPartida(ofEventArgs & args){
    partidaTerminada = true;
}