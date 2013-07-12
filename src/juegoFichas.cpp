//
//  juegoFichas.cpp
//  pepa
//
//  Created by natxo on 09/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "juegoFichas.h"

//--------------------------------------------------------------

juegoFichas::juegoFichas(){
    Tweenzor::init();
    
    /// video que usaremos para enmascarar
    //
    mascaraVideo.setPixelFormat(OF_PIXELS_RGB);
    mascaraVideo.loadMovie("mascara.mov", OF_QTKIT_DECODE_PIXELS_AND_TEXTURE);
    mascaraVideo.setLoopState(OF_LOOP_NONE);
    mascaraVideo.play();
    
    //  ofxMask
    //
    mascara.allocate(880, 660);

    
    //  Fuentes
    //
    fuenteMarcador.loadFont("BauerBodRom", 130, true, true);
    fuenteLeyenda.loadFont("BauerBodRom", 45, true, true);
    
    fuenteBonecaPeque.loadFont("BauerBodRom", 57, true, true); // para los textos de la mu√±eca
    fuenteBonecaPeque.setLetterSpacing(1);
    fuenteBonecaPeque.setSpaceSize(0.6);
    
    //
    fuenteBonecaGrande.loadFont("BauerBodRom", 100, true, true); // para los textos de la mu√±eca
    fuenteBonecaGrande.setLetterSpacing(0.95);
    fuenteBonecaGrande.setSpaceSize(0.6);
    
    //
    fuenteCampos.loadFont("BauerBodRom", 40, true, true);
    fuenteCampos.setLetterSpacing(1);
    fuenteCampos.setSpaceSize(0.6);
    
    //
    fuenteAviso.loadFont("BauerBodRom", 20, true, true);
    fuenteAviso.setSpaceSize(0.6);
    fuenteTiempo.loadFont("BauerBodRom", 70);
    
    //
    fuenteBotones.loadFont("BauerBodRom", 32, true, true);
    fuenteBotones.setLetterSpacing(1);
    fuenteBotones.setSpaceSize(0.45);
    
    //
    fuenteMini.loadFont("BauerBodRom", 18, true, true);
    fuenteMini.setLetterSpacing(1);
    fuenteMini.setSpaceSize(0.45);   
    // campo para mostrar el mensaje de donde son las fotos
    //
    direccion.loadFont("BauerBodBol", 45);
    direccion.setText(" ");
    direccion.setAlignment(OF_TEXT_ALIGN_CENTER, OF_TEXT_ALIGN_TOP);
    
    nombreCiudad.loadFont("BauerBodBol", 70);
    nombreCiudad.setText(" ");
    nombreCiudad.setAlignment(OF_TEXT_ALIGN_CENTER, OF_TEXT_ALIGN_TOP);
    
    //  Botones para seleccionar ciudad
    //
    botonCoruna.setup(40, 110, 305, 180, "coru", "A CoruÒa", fuenteBotones);
    botonCadiz.setup(25, 210, 180, 305, "cadiz", "C·diz", fuenteBotones);
    
    
    // timer para la partida, 2 minutos
    //
    tiempoPartida.setup(90000, false); // iniciamos el timer
    tiempoPartida.stopTimer();
    
    // timer para el paso entre fotos
    //
    tiempoEntreFoto.setup(1500, false); // iniciamos el timer
    tiempoEntreFoto.stopTimer();
    
    // timer para el texto de la procedencia de la foto
    //
    tiempoTexto.setup(1500, false); // iniciamos el timer
    tiempoTexto.stopTimer();

    // timer para marcar el tiempo que leemos la ficha
    //
    tiempoLeerTexto.setup(2500, false); // iniciamos el timer
    tiempoLeerTexto.stopTimer();
    
    // timer comenzar, hay que leer el texto que dice lo que hay que hacer
    //
    tiempoComienzo.setup(3500, false); // iniciamos el timer
    tiempoComienzo.stopTimer();
    
    // timer reposo, desde que pone cuantos ptos tienes a cuando vuelve a reposo
    //
    vuelveReposo.setup(6000, false); // iniciamos el timer
    vuelveReposo.stopTimer();
    
    
    //
    ofAddListener(tiempoLeerTexto.TIMER_REACHED, this, &juegoFichas::_onCompleteTiempoFicha);
    ofAddListener(tiempoTexto.TIMER_REACHED, this, &juegoFichas::_finTiempoTexto);
    ofAddListener(tiempoEntreFoto.TIMER_REACHED, this, &juegoFichas::_cambiaFoto);
    ofAddListener(tiempoPartida.TIMER_REACHED, this, &juegoFichas::_finTiempoPartida);
    ofAddListener(tiempoComienzo.TIMER_REACHED, this, &juegoFichas::_finTiempoComienzo);
    ofAddListener(vuelveReposo.TIMER_REACHED, this, &juegoFichas::_finTiempoReposo);
    
    
    _cargaFichas(); // creamos el vector con las imagenes
    _configViewPorts(); // cargamos los fbos para los viewports
    // iniciaPartida(); // setea vars y lanza fichas
    
    estadoPartida = ESTADO_REPOSO;
    
    campoNombre.setup();
    campoNombre.setFont(fuenteTiempo);
    campoNombre.bounds.x = 1;
    campoNombre.bounds.y = 160;
    campoNombre.bounds.width = 700;
    campoNombre.bounds.height = 80;
    campoNombre.text = "";
    campoNombre.drawCursor = false;
    
    campoMovil.setup();
    campoMovil.setFont(fuenteTiempo);
    campoMovil.bounds.x = 1;
    campoMovil.bounds.y = 160;
    campoMovil.bounds.width = 700;
    campoMovil.bounds.height = 80;
    campoMovil.text = "";
    campoMovil.drawCursor = false;
    
    // cargamos la imagenes para el bg de los viewports
    //
    imagenBg.loadImage("skin/capa_bg_color.png");
    mancha.loadImage("skin/mancha_color.png");
    boneca.loadImage("skin/boneca_colores.png"); // mu√±eca de la pepa
    imgPepa.loadImage("skin/pepa.png"); // mu√±eca de la pepa
    
    //
    mensajeInicio = false;
    botonEnabled = false;
    
    //
    puntos  =   0;
    tcr  =   0;
    tcg  =   0;
    tcb  =   0;
    
    //
    gestorUsuarios.conectar(); //te conectas a la db
    
    //
    record = gestorUsuarios.damePuntuacionMaxima();
    
    //
    bgr  =   210;
    bgg  =   209;
    bgb  =   187;
    
    
    //
    logo.loadImage("skin/logo.png");

    
    
}

juegoFichas::~juegoFichas(){
    
    //  Cada vez que haces un vector de punteros y queres destruirlo
    //  es necesario ir uno por uno borrando el objeto en memoria hacia
    //  donde mira el puntero y luego borrar el vector.
    //  Esto previene memory leaks
    //
    for(int i = 0; i < fichas.size(); i++){
        delete fichas[i];
    }
    
    fichas.clear();
    
    gestorUsuarios.cerrar();
}
//--------------------------------------------------------------
void juegoFichas::ponMovil(){
    
    Tweenzor::add(&alphaForms, 0, 255, 0.3f, 0.7f,EASE_OUT_SINE);
    Tweenzor::add(&alphaForms2, 0, 255, 0.5f, 0.7f,EASE_OUT_SINE);
}
//--------------------------------------------------------------
void juegoFichas::resetAlphas(){
    alphaForms = 0;
    alphaForms2 = 0;
}
//--------------------------------------------------------------
void juegoFichas::nuevoUsuario(){
    alphaForms = 0;
    gestorUsuarios.clearDatos();
    usuarioRepetido = false;
    
    Tweenzor::add(&bonecaX, bonecaX, -160, 0.1f, 0.7f,EASE_OUT_SINE);
    Tweenzor::add(&bonecaY, bonecaY, 40, 0.1f, 0.7f,EASE_OUT_SINE);
    Tweenzor::add(&bonecaAncho, bonecaAncho, boneca.getWidth(), 0.1f, 0.7f,EASE_OUT_SINE);
    Tweenzor::add(&bonecaAlto, bonecaAlto, boneca.getHeight(), 0.1f, 0.7f,EASE_OUT_SINE);
    
    Tweenzor::add(&alphaForms, 0, 255, 0.3f, 0.7f,EASE_OUT_SINE);
    Tweenzor::add(&alphaForms2, 0, 255, 0.5f, 0.7f,EASE_OUT_SINE);
    
    estadoPartida = ESTADO_NUEVO_USUARIO_NOMBRE;
    campoMovil.text = "";
    campoNombre.text = "";
    campoNombre.beginEditing();
}
//--------------------------------------------------------------
void juegoFichas::_cargaFichas(){
    
    /// cargaremos desde un xml
    /// ahora mismo esta asi para ver
    
    xmlFichas.loadFile("fichas_completas.xml");
    
    // movemos el xml a dentro de fichas
    xmlFichas.pushTag("fichas",0);
    
    // cuantas imagenes hay
    int cuantasFichas = xmlFichas.getNumTags("imagen");
    
    for(int i = 0; i < cuantasFichas; i++){
        xmlFichas.pushTag("imagen", i);
        
        string url = xmlFichas.getValue("imgurl", "");
        string msg = xmlFichas.getValue("msg", "");
        string lugar = xmlFichas.getValue("lugar", "");
        
        imagenJuego * ficha = new imagenJuego();
        ficha->setup(url, lugar, msg);
        
        fichas.push_back(ficha);
        
        xmlFichas.popTag();
        
    }
    
    
    
    
}

//--------------------------------------------------------------
void juegoFichas::update(){
    Tweenzor::update( ofGetElapsedTimeMillis() );

    ///// renderizas los fbos para dar de comer a los viewports
    
    _renderViewports(); // puntos y tiempo
    
    switch (estadoPartida) {
            
        case ESTADO_REPOSO:
            // EL JUEGO ESTA EN REPOSO = SIN USER
            // tienes a la boneca en medio con el texto
            // toca y comienza el juego
            // el fondo es un rect blanco
            
            fboMensajes.begin();
                ofPushStyle();
                ofClear(238, 236, 188);
                ofSetColor(238, 236, 188);
                ofRect(0,0,(float)fboMensajes.getWidth(),(float)fboMensajes.getHeight()); // rect blanco
            
                ofSetColor(255, 255, 255);
                bonecaAncho = 520;
                bonecaAlto = 660;
            
                bonecaX = 370-(bonecaAncho/2);
                bonecaY = fboMensajes.getHeight()-bonecaAlto + 40;
            
                boneca.draw(bonecaX, bonecaY, bonecaAncho, bonecaAlto); // mu√±eca centrada
            
                ofSetColor(47, 58, 49, 255);
                fuenteBonecaPeque.drawString("y        comienza", bonecaX + 125,bonecaY+329);
                fuenteBonecaPeque.drawString("el juego", bonecaX + 412,bonecaAlto-226);
                fuenteBonecaGrande.drawString("toca", bonecaX + 435,290);
                ofPopStyle();
            
            
               
            
            fboMensajes.end();
            
            /// viewport de coruña, en este estado tiene una leyenda "Puedes ganar un viaje a cadiz"
            fboCoru.begin();
                ofClear(0);
                ofSetColor(238, 236, 188);
                ofRect(0,0,(float)fboCoru.getWidth(),(float)fboCoru.getHeight()); // rect blanco
            fboCoru.end();
            
            fboCadiz.begin();
                ofClear(0);
                ofSetColor(238, 236, 188);
                ofRect(0,0,(float)fboCadiz.getWidth(),(float)fboCadiz.getHeight()); // rect blanco
            
                ofSetColor(47, 58, 49);
                fuenteAviso.drawString("A CoruÒa\ny C·diz\ntienen mucho\nen com˙n,\nøpuedes\ndistinguirlas?", 15, 45);
            fboCadiz.end();
            
            
            fboLogo.begin();
                //zona del teclado
                ofClear(0);
                ofSetColor(255, 255, 255);
                logo.draw(0, 0);
            fboLogo.end();
            
            
            break;    
            
        case ESTADO_NUEVO_USUARIO_NOMBRE:
            // EL JUEGO ESTA EN REPOSO = SIN USER
            
            fboMensajes.begin();
            
                ofPushStyle();
                ofClear(238, 236, 188);
                ofSetColor(238, 236, 188);
                
                ofRect(0,0,(float)fboMensajes.getWidth(),(float)fboMensajes.getHeight()); // rect blanco
                ofSetColor(255, 255, 255);
                
                boneca.draw(bonecaX, bonecaY, bonecaAncho, bonecaAlto); // mu√±eca centrada
            
                ofSetColor(47, 58, 49, alphaForms);
                fuenteBonecaPeque.drawString("tu nombre:", 400, 305);
                fuenteMini.drawString("usa el teclado para escribir\ntoca en la pantalla para continuar", 405, 335);
            
                ofSetColor(47, 58, 49, alphaForms2);
            
                campoNombre.bounds.x = 370;
                campoNombre.bounds.y = 420;
            
                //fuenteAviso.drawString("toca en la pantalla para continuar", 400, 480);
            
                campoNombre.draw();
                ofPopStyle();
            
            fboMensajes.end(); 
            
            
            /// viewport de coruña, en este estado tiene una leyenda "empieza"
           
            fboCoru.begin();
                ofClear(0);
                ofSetColor(238, 236, 188);
                ofRect(0,0,(float)fboCoru.getWidth(),(float)fboCoru.getHeight()); // rect blanco
            fboCoru.end();
            
            fboCadiz.begin();
                ofClear(0);
                ofSetColor(238, 236, 188);
                ofRect(0,0,(float)fboCadiz.getWidth(),(float)fboCadiz.getHeight()); // rect blanco
                ofSetColor(47, 58, 49, alphaForms);
                fuenteAviso.drawString("DÈjanos\ntus datos\npara poder\nentrar en\nel sorteo", 15, 95);
            fboCadiz.end();
            
            
            fboLogo.begin();
                //zona del teclado
                ofClear(0);
                ofSetColor(255, 255, 255);
                logo.draw(0, 0);
            fboLogo.end();
            
            break;
            
            
        case ESTADO_COMIENZA:
            // YA TIENES LOS DATOS
            fboMensajes.begin();
            
                ofPushStyle();
                ofClear(238, 236, 188);
                ofSetColor(238, 236, 188);
    
                ofRect(0,0,(float)fboMensajes.getWidth(),(float)fboMensajes.getHeight()); // rect blanco
                ofSetColor(255, 255, 255);
            
                ofSetColor(255, 255, 255, alphaForms2);
                mancha.draw(0, 0);
            
            
                ofSetColor(47, 58, 49, alphaComienza);
                direccion.draw(36, 251, 880-(45*2), 1400);
            
                ofSetColor(150, 41, 41, alphaComienza);
                direccion.draw(35, 250, 880-(45*2), 1400);
 
                ofPopStyle();
            
            fboMensajes.end(); 
            
            
            
            
            /// viewport de coruña, en este estado tiene una leyenda "empieza"
            fboCoru.begin();
                ofClear(0);
                ofSetColor(238, 236, 188);
                ofRect(0,0,(float)fboCoru.getWidth(),(float)fboCoru.getHeight()); // rect blanco
            fboCoru.end();
            
            
            fboLogo.begin();
                //zona del teclado
                ofClear(0);
                ofSetColor(255, 255, 255);
                logo.draw(0, 0);
            fboLogo.end();            
            
            break;
            
            
        case ESTADO_NUEVO_USUARIO_MOVIL:
            // EL JUEGO ESTA EN REPOSO = SIN USER
            
            fboMensajes.begin();
                ofPushStyle();
                ofClear(238, 236, 188);
                ofSetColor(238, 236, 188);
                ofRect(0,0,(float)fboMensajes.getWidth(),(float)fboMensajes.getHeight()); // rect blanco
                ofSetColor(255, 255, 255);
                
                boneca.draw(bonecaX, bonecaY, bonecaAncho, bonecaAlto); // mu√±eca centrada
            
            if(!usuarioRepetido){
                ofSetColor(47, 58, 49, alphaForms);
                fuenteBonecaPeque.drawString("tu movil:", 400, 305);
                fuenteMini.drawString("usa el teclado para escribir\ntoca en la pantalla para continuar", 405, 335);
            
                ofSetColor(47, 58, 49, alphaForms2);
            
                campoMovil.bounds.x = 370;
                campoMovil.bounds.y = 420;
            
                campoMovil.draw(); 
                
            }else{
                ofSetColor(150, 47, 47, alphaForms);
                fuenteCampos.drawString("ya has\nparticipado\ncon esos datos", 440, 310);
            
            }
                ofPopStyle();
            fboMensajes.end(); 
            
            /// viewport de coruña, en este estado tiene una leyenda "empieza"
            fboCoru.begin();
                ofClear(0);
                ofSetColor(238, 236, 188);
                ofRect(0,0,(float)fboCoru.getWidth(),(float)fboCoru.getHeight()); // rect blanco
            fboCoru.end();
            
            fboLogo.begin();
                //zona del teclado
                ofClear(0);
                ofSetColor(255, 255, 255);
                logo.draw(0, 0);
            fboLogo.end();  
            
            break;
          
        case ESTADO_PARTIDA_ACABADA:
            // SE ACABO LA PARTIDA
            
            fboMensajes.begin();
                ofPushStyle();
                ofClear(238, 236, 188);
                ofSetColor(238, 236, 188);
                ofRect(0,0,(float)fboMensajes.getWidth(),(float)fboMensajes.getHeight()); // rect blanco
                ofSetColor(255, 255, 255, alphaForms2);
                mancha.draw(0, 0);
            
                ofSetColor(47, 58, 49, alphaForms);
                fuenteCampos.drawString("has conseguido",450, 340);
                fuenteBonecaGrande.drawString(ofToString(puntos)+" aciertos", 270, 460);
                fuenteBotones.drawString("Gracias por participar",390, 550);
                ofPopStyle();
            fboMensajes.end(); 
            
            fboCadiz.begin();
                ofClear(0);
                ofSetColor(238, 236, 188);
                ofRect(0,0,(float)fboCadiz.getWidth(),(float)fboCadiz.getHeight()); // rect blanco
            
                ofSetColor(47, 58, 49, alphaForms);
            
                fuenteAviso.drawString("Entrar·s\nen nuestro\nsorteo.\n\n!Suerte!", 15, 95);
            fboCadiz.end();
            
            
            fboCoru.begin();
                ofClear(0);
                ofSetColor(238, 236, 188);
                
                ofRect(0,0,(float)fboCoru.getWidth(),(float)fboCoru.getHeight()); // rect blanco
                ofSetColor(255, 255, 255);
                imgPepa.draw(130, 30); // mu√±eca centrada
            fboCoru.end();
            
            
            fboLogo.begin();
                //zona del teclado
                ofClear(0);
                ofSetColor(255, 255, 255);
                logo.draw(0, 0);
            fboLogo.end();  
            
            break;
            
        case ESTADO_JUGANDO:
            // LA PARTIDA ESTA EN CURSO
            mascaraVideo.update();
            
            // update de los botones
            botonCadiz.update();
            botonCoruna.update();
 
            ofSoundUpdate();
            
            fichas.at(indexFicha)->update();
            
            
            if(mascaraVideo.isFrameNew()){
                //si el frame del video es nuevo update la mascara
                //
                ofPushStyle();
                mascara.begin(0);
                    ofSetColor(255,255,255,255);
                    mascaraVideo.draw(0, 0);
                mascara.end(0);
                
                mascara.begin(1);
                    ofSetColor(255,255,255,255);
                    fichas.at(indexFicha)->imagen.draw(0, 0, 880, 660);
                mascara.end(1);
                
                mascara.update();

                ofPopStyle();
            }
            
            
            ofPushStyle();
            fboMensajes.begin();
                //ofClear(238, 236, 188);
                ofSetColor(238, 236, 188,255);
                ofRect(0,0,(float)fboMensajes.getWidth(),(float)fboMensajes.getHeight()); // rect blanco
                ofSetColor(255, 255, 255);
                
                ofSetColor(255, 255, 255, alphaRevela); // imagen para revelar
                fichas.at(indexFicha)->imagen.draw(0, 0, 880, 660);
                ofSetColor(255, 255, 255, 255);
                mascara.draw();
            fboMensajes.end();
            ofPopStyle();
            
            fboCoru.begin();
                ofClear(0);
                ofSetColor(255, 255, 255);
            
                botonCoruna.render();
            fboCoru.end();
            
            fboCadiz.begin();
                ofClear(0);
                ofSetColor(255, 255, 255);
                botonCadiz.render();
            fboCadiz.end();
            
            fboLogo.begin();
                //zona del teclado
                ofClear(0);
                ofSetColor(255, 255, 255);
                logo.draw(0, 0);
            fboLogo.end();  
            
            break;            
            
        default:
            break;
    }
    
    
}

//--------------------------------------------------------------
void juegoFichas::draw(){
    // el fondo se dibuja siempre
        viewportBg.draw(fboImagen.getTextureReference());
    
    // los que siempre salen
    viewportMascara.draw(fboMensajes.getTextureReference());
    viewportTiempo.draw(fboTiempo.getTextureReference());
    viewportCoru.draw(fboCoru.getTextureReference());
    viewportCadiz.draw(fboCadiz.getTextureReference());
    viewportAciertos.draw(fboAciertos.getTextureReference());
    viewportLogo.draw(fboLogo.getTextureReference());
    
    // excepciones que atienden al estado
    if(estadoPartida == ESTADO_JUGANDO){
        // LA PARTIDA ESTA EN CURSO
        
        ofPushStyle();
            ofSetColor(238, 236, 188, alphaBotones);
            ofRect(viewportCadiz.getPos().x - viewportCadiz.getWidth()/2, viewportCadiz.getPos().y - viewportCadiz.getHeight()/2, viewportCadiz.getWidth(), viewportCadiz.getHeight());
            ofRect(viewportCoru.getPos().x - viewportCoru.getWidth()/2, viewportCoru.getPos().y - viewportCoru.getHeight()/2, 500, 500);
        ofPopStyle();
        
        if(mensaje){
            ofPushStyle();
            // acabas de pulsar una opcion y esto dice ok o fallo
                //area para centrar el texto
                ofRectangle areaPhoto = fuenteMarcador.getStringBoundingBox(ofToString(mensajeStr), 0, 0);
                int ptx = viewportMascara.getPos().x-areaPhoto.getWidth()/2;
                int pty = viewportMascara.getPos().y+areaPhoto.getHeight()/2;
            
            
                ofSetColor(10, 10, 10, alphaMsjStr);
                fuenteMarcador.drawString(ofToString(mensajeStr), ptx+1,  pty+1);
            
                ofSetColor(255, 255, 255, alphaMsjStr);
                fuenteMarcador.drawString(ofToString(mensajeStr), ptx,  pty);
            
            ofPopStyle();
        }
        if(textoFoto){
            ofPushStyle();
            // acabas de pulsar una opcion y esto dice ok o fallo
                //area para centrar el texto
                string mensajePantalla = fichas.at(indexFicha)->msg;
            
                ofRectangle areaPhoto = fuenteLeyenda.getStringBoundingBox(mensajePantalla, 0, 0);
            
                int ptx = viewportMascara.getPos().x-viewportMascara.getWidth()/2;
                int pty = viewportMascara.getPos().y-viewportMascara.getHeight()/2;
            
                
                float anchoTxt = direccion.getTextWidth();
            
                float altoTxt = direccion.getTextHeight();
                
                int margen = 100;
            
                if(anchoTxt<(viewportMascara.getWidth())){
                    // es mas pequeño que el espacio por lo que lo centras
                    //
                    
                    
                    ofSetColor(10, 10, 10, alphaTextoFoto);
                    direccion.draw(ptx + margen + 1,pty + 351,viewportMascara.getWidth()-(margen*2),1400);
                    
                    ofSetColor(255, 255, 255, alphaTextoFoto);
                    direccion.draw(ptx + margen ,pty + 350,viewportMascara.getWidth()-(margen*2),1400);
                    
                    
                    ofSetColor(10, 10, 10, alphaTextoFoto);
                    nombreCiudad.draw(ptx + margen + 1,pty + 241,viewportMascara.getWidth()-(margen*2),1400);
                    
                    ofSetColor(255, 255, 255, alphaTextoFoto);
                    nombreCiudad.draw(ptx + margen ,pty + 240,viewportMascara.getWidth()-(margen*2),1400);                    
                    
                   // ofNoFill();
                   // ofRect(ptx + margen ,pty + 240,viewportMascara.getWidth()-(margen*2),1400);
                   // ofFill();
                }

                
            
            ofPopStyle();
        }
    
    }
    
}
//--------------------------------------------------------------
void juegoFichas::_renderViewports(){
    fboImagen.begin();
        ofPushStyle();
        ofClear(0);
        ofSetColor(bgr, bgg, bgb);
        imagenBg.draw(0, 0);
        ofPopStyle();
    fboImagen.end(); 
    
    
    fboAciertos.begin();
    ofPushStyle();
        ofClear(241, 203, 158);
        ofSetColor(241, 203, 158);
        ofRect(0,0,(float)fboAciertos.getWidth(),(float)fboAciertos.getHeight()); // rect blanco
        
        ofSetColor(47, 58, 49);
        if(estadoPartida == ESTADO_JUGANDO || estadoPartida == ESTADO_COMIENZA){    
            // estos son tus puntos - mejor siempre dos digitos
            //
            fuenteAviso.drawString("tu marca", 100, 50);
            fuenteMarcador.drawString(ofToString(puntos), 100, 190);
            fuenteLeyenda.drawString("aciertos", 50, 255);
        }else{
            // este es el record de puntos - mejor siempre dos digitos
            //
            fuenteAviso.drawString("el rÈcord son", 70, 50);
            fuenteMarcador.drawString(ofToString(record), 100, 190);
            fuenteLeyenda.drawString("aciertos", 50, 255);
        }
    ofPopStyle();
    fboAciertos.end();
    
    fboTiempo.begin();
        ofPushStyle();
        ofClear(0);
        ofSetColor(205, 167, 144);
        ofRect(0,0,(float)fboTiempo.getWidth(),(float)fboTiempo.getHeight()); // rect blanco
        // marcador de tiempo restante
        //
        ofSetColor(tcr, tcg, tcb);
        int medioX = 20;
        int medioY = 110;
    
    if(estadoPartida == ESTADO_JUGANDO){
            //ofSetColor(150, 41, 41);
            int minutos = (int)tiempoPartida.getTimeLeftInSeconds()/60;
            int segundos = (int)tiempoPartida.getTimeLeftInSeconds() % 60;
        
        if(segundos<10){
            fuenteTiempo.drawString(ofToString(minutos)+":0"+ofToString(segundos), medioX, medioY);
        }else{
            fuenteTiempo.drawString(ofToString(minutos)+":"+ofToString(segundos), medioX, medioY);
        }
    }else if(estadoPartida == ESTADO_PARTIDA_ACABADA){
        //ofSetColor(150, 41, 41);
        fuenteTiempo.drawString("0:00", medioX, medioY);
    }else{
        fuenteTiempo.drawString("1:30", medioX, medioY);
    }
        ofPopStyle();
    fboTiempo.end();
    
}

//--------------------------------------------------------------
void juegoFichas::_configViewPorts(){

    fboImagen.allocate(1920, 1080);
    fboAciertos.allocate(310, 310);
    fboTiempo.allocate(305, 305);
    fboMensajes.allocate(880, 660);
    fboCoru.allocate(305, 180);
    fboCadiz.allocate(180, 305);
    
    fboLogo.allocate(480, 135);
    
    fboLogo.begin();
    ofClear(0);
    fboLogo.end();
    
    fboCadiz.begin();
    ofClear(0);
    fboCadiz.end(); 
    
    fboCoru.begin();
    ofClear(0);
    fboCoru.end();  
    
    fboMensajes.begin();
    ofSetColor(238, 236, 188);
    fboMensajes.end();  
    
    fboImagen.begin();
    ofClear(0);
    fboImagen.end(); 
    
    fboAciertos.begin();
    ofClear(241, 203, 158);
    fboAciertos.end(); 
    
    fboTiempo.begin();
    ofClear(0);
    fboTiempo.end();
    
    viewportImagen.loadSettings(0,"config0.xml");
    viewportAciertos.loadSettings(0,"config1.xml");
    viewportMascara.loadSettings(0,"config2.xml");
    viewportCoru.loadSettings(0,"config3.xml");
    viewportCadiz.loadSettings(0,"config4.xml");
    viewportTiempo.loadSettings(0,"config5.xml");
    viewportBg.loadSettings(0,"config8.xml");
    viewportLogo.loadSettings(0,"config7.xml");
}
//--------------------------------------------------------------
void juegoFichas::comienza(){
    mensajeInicio = true;
    estadoPartida = ESTADO_COMIENZA;
    Tweenzor::add(&alphaForms2, 0, 255, 0.1f, 0.7f,EASE_IN_SINE);
    Tweenzor::add(&alphaComienza, 0, 255, 0.5f, 0.7f,EASE_IN_SINE);
    tiempoComienzo.startTimer();
    
    direccion.setText("pulsa A CoruÒa o C·diz\nen cuanto lo sepas");
}
//--------------------------------------------------------------
void juegoFichas::iniciaPartida(){
    
    std::random_shuffle(fichas.begin(), fichas.end());

    puntos = 0;
    indexFicha = 0;
    
    estadoPartida = ESTADO_JUGANDO;

    mensaje = false;
    textoFoto = false;
    
    
    alphaComienza = 0;
    alphaMsjStr = 0;
    scaleMsjStr = 0;
    alphaTextoFoto = 0;
    alphaBotones = 0;
    alphaForms = 0;
    alphaForms2 = 0;
    alphaBotones = 0;
    alphaRevela = 0;
    
    tiempoPartida.reset();
    tiempoEntreFoto.reset();
    
    tiempoLeerTexto.reset();
    tiempoTexto.reset();
    
    Tweenzor::add(&tcr, tcr, 255, 0.2f, 1.5f,EASE_IN_SINE);
    Tweenzor::add(&tcg, tcg, 255, 0.2f, 1.5f,EASE_IN_SINE);
    Tweenzor::add(&tcb, tcb, 255, 0.2f, 1.5f,EASE_IN_SINE);
    
    _lanzaFicha();
    
    tiempoPartida.startTimer();
    
    //mensajeInicio = false;
}

//--------------------------------------------------------------
void juegoFichas::_lanzaFicha(){
    
    // lanzas una imagen
    //
    alphaBotones = 255;

    if(indexFicha<fichas.size()-1){
        indexFicha ++;
    }else{
        indexFicha = 0;
    }
    
    mascaraVideo.setPosition(0.01);
    mascaraVideo.play();
    
    Tweenzor::add(&alphaBotones, 255, 0, 0.5f, 3.f,EASE_IN_SINE);
    
    botonCoruna.reset();
    botonCadiz.reset();
    
    mensajeStr = "";
    alphaMsjStr = 0;
    alphaRevela = 0;
    
    botonEnabled = true;
    
    direccion.setText(fichas.at(indexFicha)->msg);
    
    if (fichas.at(indexFicha)->ciudad == "coru") {
        nombreCiudad.setText("A CoruÒa");
    }else {
        nombreCiudad.setText("C·diz");
    }
    
}

//--------------------------------------------------------------
void juegoFichas::_botonCiudad(string & s){
    /// has escojido una ciudad
    
    //primero comprobamos que esten habilidatos los botones
    if(botonEnabled){
    
        // comprobamos si es correcto o no TODO
        if(fichas.at(indexFicha)->ciudad == s){
            // sumamos los ptos si has acertado
            puntos ++;
            _mensajeRespuesta("SÌ");
            
            // pones el bg verde
            Tweenzor::add(&bgr, bgr, 199, 0.1f, 0.7f,EASE_IN_SINE);
            Tweenzor::add(&bgg, bgg, 214, 0.1f, 0.7f,EASE_IN_SINE);
            Tweenzor::add(&bgb, bgb, 193, 0.1f, 0.7f,EASE_IN_SINE);
            // acertaste
            // iluminamos el boton
            if(s=="cadiz"){
                //animamos boton cadiz
                botonCadiz.animaOk();
            }else if (s=="coru") {
                //animamos boton coruna
                botonCoruna.animaOk();
            }
        
        }else{
            _mensajeRespuesta("No");
            // fallaste
            // iluminamos el boton
            // pones el bg rojo
            Tweenzor::add(&bgr, bgr, 211, 0.1f, 0.7f,EASE_IN_SINE);
            Tweenzor::add(&bgg, bgg, 148, 0.1f, 0.7f,EASE_IN_SINE);
            Tweenzor::add(&bgb, bgb, 109, 0.1f, 0.7f,EASE_IN_SINE);
            
            if(s=="cadiz"){
                //animamos boton cadiz
                botonCadiz.animaError();
            }else if (s=="coru") {
                //animamos boton coruna
                botonCoruna.animaError();
            }
        }
    }
    botonEnabled = false;
}

//--------------------------------------------------------------
void juegoFichas::_mensajeRespuesta(string s){
    mensajeStr = s;
    mensaje = true;
    Tweenzor::add(&alphaMsjStr, 0, 255, 0.0f, 0.3f,EASE_IN_SINE);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&alphaMsjStr), this, &juegoFichas::_onCompleteMsg);
}

//--------------------------------------------------------------
void juegoFichas::_onCompleteMsg(float* arg) {
    /// ahora encendemos el timer que nos indica cuando poner el texto
    //  que dice de donde es la foto
    tiempoTexto.startTimer();
    //

}
//--------------------------------------------------------------
void juegoFichas::_onCompleteTiempoTexto(float* arg){
    /// iniciamos el alpa del texto de la foto y lo mostramos
    mensaje = false;
    textoFoto = true;
    Tweenzor::add(&alphaTextoFoto, 0, 255, 0.0f, 0.3f,EASE_IN_SINE);
    /// iniciamos otro timer para ver el texto
    tiempoLeerTexto.startTimer();
    Tweenzor::add(&alphaRevela, 0, 255, 0.1f, 1.6f,EASE_IN_SINE);
}
//--------------------------------------------------------------
void juegoFichas::_finTiempoComienzo(ofEventArgs & args){
    iniciaPartida();
}

//--------------------------------------------------------------
void juegoFichas::_finTiempoTexto(ofEventArgs & args){
    // ahora le quitas el alpha y ponemos el texto
    Tweenzor::add(&alphaMsjStr, 255, 0, 0.0f, 0.3f,EASE_IN_SINE);
    Tweenzor::addCompleteListener( Tweenzor::getTween(&alphaMsjStr), this, &juegoFichas::_onCompleteTiempoTexto);
    
    // ponemos el bg negro
    Tweenzor::add(&bgr, bgr, 210, 0.1f, 0.4f,EASE_IN_SINE);
    Tweenzor::add(&bgg, bgg, 209, 0.1f, 0.4f,EASE_IN_SINE);
    Tweenzor::add(&bgb, bgb, 187, 0.1f, 0.4f,EASE_IN_SINE);
}
//--------------------------------------------------------------
void juegoFichas::_onCompleteTiempoFicha(ofEventArgs & args){
    /// se acabo esta imagen, lanzamos el timer para la siguiente
    tiempoEntreFoto.startTimer();
}
//--------------------------------------------------------------
void juegoFichas::guardaPosiciones(){
    //
    viewportImagen.saveSettings("config0.xml");
    viewportAciertos.saveSettings("config1.xml");
    viewportMascara.saveSettings("config2.xml");
    viewportCoru.saveSettings("config3.xml");
    viewportCadiz.saveSettings("config4.xml");
    viewportTiempo.saveSettings("config5.xml");
    
    viewportLogo.saveSettings("config7.xml");
    viewportBg.saveSettings("config8.xml");
    
    
    /*
     viewportImagen.loadSettings(0,"config0.xml");
     viewportAciertos.loadSettings(1,"config1.xml");
     viewportMascara.loadSettings(2,"config2.xml");
     viewportCoru.loadSettings(3,"config3.xml");
     viewportCadiz.loadSettings(4,"config4.xml");
     viewportTiempo.loadSettings(5,"config5.xml");
     viewportBg.loadSettings(8,"config8.xml");
     viewportLogo.loadSettings(7,"config7.xml");
     */
    
    
    
}
//--------------------------------------------------------------
void juegoFichas::_cambiaFoto(ofEventArgs & args){
    textoFoto = false;
    _lanzaFicha();
}

//--------------------------------------------------------------
void juegoFichas::_finTiempoPartida(ofEventArgs & args){
    estadoPartida = ESTADO_PARTIDA_ACABADA;
    
    // acabo la partida asi que guardas los datos
    gestorUsuarios.ponPuntuacion(puntos);
    gestorUsuarios.guardaJugador();
    
    
    resetAlphas();
    Tweenzor::add(&alphaForms, 0, 255, 0.8f, 0.7f,EASE_OUT_SINE);
    Tweenzor::add(&alphaForms2, 0, 255, 0.1f, 0.7f,EASE_OUT_SINE);
    vuelveReposo.startTimer();
    
    record = gestorUsuarios.damePuntuacionMaxima();
}

//--------------------------------------------------------------
void juegoFichas::_finTiempoReposo(ofEventArgs & args){
    // se acabo el tiempo para que veas tus points, volvemos al estado de reposo
    estadoPartida = ESTADO_REPOSO;
    
    alphaComienza = 0;
    alphaMsjStr = 0;
    scaleMsjStr = 0;
    alphaTextoFoto = 0;
    alphaBotones = 0;
    alphaForms = 0;
    alphaForms2 = 0;
    alphaBotones = 0;
    alphaRevela = 0;
    
    tcr  =   0;
    tcg  =   0;
    tcb  =   0;
}

//--------------------------------------------------------------
void    juegoFichas::usuarioRepe(){
    usuarioRepetido = true;
    
    vuelveReposo.startTimer();
}