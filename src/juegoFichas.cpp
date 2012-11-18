//
//  juegoFichas.cpp
//  pepa
//
//  Created by natxo on 09/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "juegoFichas.h"

//--------------------------------------------------------------
void juegoFichas::setup(){
    Tweenzor::init();
    
    /// video que usaremos para enmascarar
    mascaraVideo.setPixelFormat(OF_PIXELS_RGB);
   
    mascaraVideo.loadMovie("mascara.mov", OF_QTKIT_DECODE_PIXELS_AND_TEXTURE);
    mascaraVideo.setLoopState(OF_LOOP_NONE);
    mascaraVideo.play();
    
    mascara.allocate(800, 600);


    ofAddListener(botonCoruna.seleccionBoton, this,  &juegoFichas::botonCiudad);
    ofAddListener(botonCadiz.seleccionBoton, this,  &juegoFichas::botonCiudad);
    
    /// sonidos para indicar acierto/fallo
    sndAcierto.loadSound("Temple.aiff");
    sndFallo.loadSound("Wild Eep.aiff");
    
    fuenteMarcador.loadFont("BodoniXT.ttf", 130);
    fuenteLeyenda.loadFont("BodoniXT.ttf", 40, true, true);
    fuenteAlerta.loadFont("BodoniXT.ttf", 70);
    fuenteCampos.loadFont("BodoniXT.ttf", 30, true, true);
    
    /// botones para seleccioar ciudad
    botonCoruna.setup(40, 40, "coru", "btn/coru.png", "¿a coruña?", fuenteLeyenda);
    botonCadiz.setup(40, 40, "cadiz", "btn/cadiz.png", "¿cadiz?", fuenteLeyenda);    
    
    /// timer para la partida, 2 minutos
    tiempoPartida.setup(480000, false); // iniciamos el timer
    
    
    /// timer para el paso entre fotos
    tiempoEntreFoto.setup(1500, false); // iniciamos el timer
    tiempoEntreFoto.stopTimer();
    
    ofAddListener(tiempoEntreFoto.TIMER_REACHED, this, &juegoFichas::cambiaFoto);
    ofAddListener(tiempoPartida.TIMER_REACHED, this, &juegoFichas::finTiempoPartida);
    
    cargaFichas(); // creamos el vector con las imagenes
    
    configViewPorts(); // cargamos los fbos para los viewports
    
   // iniciaPartida(); // setea vars y lanza fichas

    estadoPartida = ESTADO_REPOSO;
    
    campoNombre.setup();
    campoNombre.setFont(fuenteCampos);
    campoNombre.bounds.x = 1;
    campoNombre.bounds.y = 160;
    campoNombre.bounds.width = 700;
    campoNombre.bounds.height = 80;
    campoNombre.text = "nombre...";
    
    campoMovil.setup();
    campoMovil.setFont(fuenteCampos);
    campoMovil.bounds.x = 1;
    campoMovil.bounds.y = 160;
    campoMovil.bounds.width = 700;
    campoMovil.bounds.height = 80;
    campoMovil.text = "movil...";
    
}
//--------------------------------------------------------------
void juegoFichas::nuevoUsuario(){
    estadoPartida = ESTADO_NUEVO_USUARIO_NOMBRE;
    campoNombre.beginEditing();
}
//--------------------------------------------------------------
void juegoFichas::cargaFichas(){
    
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
void juegoFichas::update(){
Tweenzor::update( ofGetElapsedTimeMillis() );
    
    switch (estadoPartida) {
        case ESTADO_NUEVO_USUARIO_NOMBRE:
            // EL JUEGO ESTA EN REPOSO = SIN USER
            
            fboMensajes.begin();
            
            ofPushStyle();
            ofClear(0);
            ofSetColor(255);
            fuenteCampos.drawString("Introduce tu nombre\ny pulsa la pantalla\npara continuar", 0, 30);
            ofNoFill();
            ofRect(campoNombre.bounds);
            ofFill();
            campoNombre.draw();
            ofPopStyle();
            
            fboMensajes.end(); 
            
            break;
        case ESTADO_NUEVO_USUARIO_MOVIL:
            // EL JUEGO ESTA EN REPOSO = SIN USER
            
            fboMensajes.begin();
            
            ofPushStyle();
            ofClear(0);
            ofSetColor(255);
            fuenteCampos.drawString("Introduce tu numero de movil\ny pulsa la pantalla\npara continuar", 0, 30);
            ofNoFill();
            ofRect(campoMovil.bounds);
            ofFill();
            campoMovil.draw(); 
            ofPopStyle();
            
            fboMensajes.end(); 
            
            break;
            
        case ESTADO_REPOSO:
            // EL JUEGO ESTA EN REPOSO = SIN USER
            
            fboMensajes.begin();
            ofClear(0);
            ofSetColor(255, 255, 255, 255);
            fuenteAlerta.drawString("PULSA n PARA\nEMPEZAR\nA JUGAR", 0, 80);
            fboMensajes.end(); 
            
            break;
          
        case ESTADO_PARTIDA_ACABADA:
            // SE ACABO LA PARTIDA
            
            fboMensajes.begin();
            ofClear(0);
            ofSetColor(255, 255, 255, 255);
            fuenteCampos.drawString(campoNombre.text+" PARTIDA TERMINADA "+ofToString(puntos), 0, 80);
            fboMensajes.end(); 
            
            break;
            
        case ESTADO_JUGANDO:
            // LA PARTIDA ESTA EN CURSO
            mascaraVideo.update();
 
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
            botonCoruna.ancho = viewportCadiz.getWidth();
            botonCoruna.alto = viewportCadiz.getHeight();
            
            botonCadiz.screenPosx = viewportCadiz.getPos().x-(viewportCadiz.getWidth()/2);
            botonCadiz.screenPosy = viewportCadiz.getPos().y-(viewportCadiz.getHeight()/2);
            botonCadiz.ancho = viewportCadiz.getWidth();
            botonCadiz.alto = viewportCadiz.getHeight();
            
            
            botonCoruna.render();
            botonCadiz.render();
            
            break;            
            
        default:
            break;
    }
    

}

//--------------------------------------------------------------
void juegoFichas::draw(){
    
    switch (estadoPartida) {
        case ESTADO_REPOSO:
            // EL JUEGO ESTA EN REPOSO = SIN USER
            viewportMascara.draw(fboMensajes.getTextureReference());
            break;
            
            
        case ESTADO_JUGANDO:
            // LA PARTIDA ESTA EN CURSO
           
            /// cada cosa sale en un viewport con mapping y mascara
            viewportMascara.draw(mascara.getTextureReference());
            viewportAciertos.draw(fboAciertos.getTextureReference());
            viewportTiempo.draw(fboTiempo.getTextureReference());
            
            ofPushStyle();
            
            viewportCoru.draw(botonCoruna.fbo.getTextureReference());
            viewportCadiz.draw(botonCadiz.fbo.getTextureReference());
            ofSetColor(0,0,0,alphaBotones);
            ofRect(viewportCadiz.getPos().x - viewportCadiz.getWidth()/2, viewportCadiz.getPos().y - viewportCadiz.getHeight()/2, viewportCadiz.getWidth(), viewportCadiz.getHeight());
            
            ofRect(viewportCoru.getPos().x - viewportCoru.getWidth()/2, viewportCoru.getPos().y - viewportCoru.getHeight()/2, viewportCoru.getWidth(), viewportCoru.getHeight());
            ofPopStyle();
            
            if(mensaje){
                ofPushStyle();
                // acabas de pulsar una opcion y esto dice ok o fallo
                ofSetColor(255, 255, 255, alphaMsjStr);
                fuenteAlerta.drawString(ofToString(mensajeStr), 200, 280);
                ofPopStyle();
            }
            
            break;            
        
        case ESTADO_PARTIDA_ACABADA:
            // SE ACABO LA PARTIDA
            fboMensajes.draw(400, 300);
            
            break;
            
        case ESTADO_NUEVO_USUARIO_NOMBRE:
            // NUEVO USER
            viewportMascara.draw(fboMensajes.getTextureReference());
            
            break;
        case ESTADO_NUEVO_USUARIO_MOVIL:
            // NUEVO USER
            viewportMascara.draw(fboMensajes.getTextureReference());
            
            break;  
        default:
            break;
    }
    
    

}
//--------------------------------------------------------------
void juegoFichas::renderViewports(){
    
    
    fboAciertos.begin();
    ofClear(0);
    ofSetColor(255,255,255);
    /// estos son tus puntos - mejor siempre dos digitos
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
    if(estadoPartida == ESTADO_JUGANDO){
        int minutos = (int)tiempoPartida.getTimeLeftInSeconds()/60;
        int segundos = (int)tiempoPartida.getTimeLeftInSeconds() % 60;
        
        if(segundos<10){
            fuenteMarcador.drawString(ofToString(minutos)+":0"+ofToString(segundos), 0, 150);
        }else{
            fuenteMarcador.drawString(ofToString(minutos)+":"+ofToString(segundos), 0, 150);
        }
    }
    fboTiempo.end();
    
}

//--------------------------------------------------------------
void juegoFichas::configViewPorts(){

    fboImagen.allocate(640, 480);
    fboAciertos.allocate(320, 240);
    fboTiempo.allocate(320, 240);
    
    fboMensajes.allocate(800, 600);
    
    fboMensajes.begin();
    ofClear(0);
    fboMensajes.end();  
    
    fboImagen.begin();
    ofClear(0);
    fboImagen.end(); 
    
    fboAciertos.begin();
    ofClear(0);
    fboAciertos.end(); 
    
    
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
void juegoFichas::iniciaPartida(){
    
    std::random_shuffle(fichas.begin(), fichas.end());
    
    campoMovil.text = "movil...";
    campoNombre.text = "nombre...";
    
    puntos = 0;
    indexFicha = 0;
    
    estadoPartida = ESTADO_JUGANDO;

    mensaje = false;
    alphaMsjStr = 0;
    scaleMsjStr = 0;
    
    tiempoPartida.reset();
    tiempoEntreFoto.reset();
    
    lanzaFicha();
    
    tiempoPartida.startTimer();
    
    
}

//--------------------------------------------------------------
void juegoFichas::lanzaFicha(){
    /// lanzas una imagen
    alphaBotones = 255;

    if(indexFicha<fichas.size()-1){
        indexFicha ++;
    }else{
        indexFicha = 0;
    }
    
    mascaraVideo.setPosition(0.01);
    mascaraVideo.play();
    
    Tweenzor::add(&alphaBotones, 255, 0, 0.5f, 3.f,EASE_IN_OUT_SINE);
    
    botonCoruna.activo = true;
    botonCadiz.activo = true;
    
    mensajeStr = "";
    alphaMsjStr = 0;
    
}

//--------------------------------------------------------------
void juegoFichas::botonCiudad(string & s){
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
void juegoFichas::mensajeRespuesta(string s){
    mensajeStr = s;
    mensaje = true;
    Tweenzor::add(&alphaMsjStr, 0, 255, 0.0f, 0.3f,EASE_IN_OUT_QUAD);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&alphaMsjStr), this, &juegoFichas::onCompleteMsg);
}

//--------------------------------------------------------------
void juegoFichas::onCompleteMsg(float* arg) {
    if(mensajeStr == "correcto"){
        sndAcierto.play();
    }else if (mensajeStr == "error") {
        sndFallo.play();
    }
    tiempoEntreFoto.startTimer();
}
//--------------------------------------------------------------
void juegoFichas::guardaPosiciones(){
    viewportImagen.saveSettings();
    viewportAciertos.saveSettings();
    viewportMascara.saveSettings();
    viewportCoru.saveSettings();
    viewportCadiz.saveSettings();
    viewportTiempo.saveSettings();

}
//--------------------------------------------------------------
void juegoFichas::cambiaFoto(ofEventArgs & args){
    lanzaFicha();
}

//--------------------------------------------------------------
void juegoFichas::finTiempoPartida(ofEventArgs & args){
    estadoPartida = ESTADO_PARTIDA_ACABADA;
}