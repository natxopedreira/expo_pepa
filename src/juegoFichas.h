//
//  controlImagenes.h
//  pepa
//
//  Created by natxo on 09/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef CONTROL_IMAGEN
#define CONTROL_IMAGEN

#include "ofMain.h"
#include "imagenJuego.h"
#include "boton.h"

//non core addons
#include "ofxTweenzor.h"
#include "ofxFX.h"
#include "ofxInteractiveViewPort.h"
#include "ofxTimer.h"

enum EstadoPartida{
    ESTADO_REPOSO,
    ESTADO_NUEVO_USUARIO,
    ESTADO_JUGANDO,
    ESTADO_PARTIDA_ACABADA
};
class juegoFichas{
public:

    ofxMask mascara;
    ofQTKitPlayer mascaraVideo;
    ofxTimer tiempoPartida;
    ofxTimer tiempoEntreFoto;
    ofTrueTypeFont fuenteMarcador;
    ofTrueTypeFont fuenteLeyenda;
    ofTrueTypeFont fuenteAlerta;
    ofSoundPlayer  sndAcierto, sndFallo;
    
    EstadoPartida estadoPartida;
    
    vector<imagenJuego*> fichas;
    
    int indexFicha;
    int puntos;
    float alphaBotones;
    bool mensaje;
    string mensajeStr;
    float alphaMsjStr;
    float scaleMsjStr;
    
    boton botonCoruna;
    boton botonCadiz;
    
    void setup();
    void configViewPorts();
    void update();
    void draw();
    void iniciaPartida();
    void renderViewports();
    
    void cargaFichas();
    void lanzaFicha();
    void botonCiudad(string & s);
    
    void mensajeRespuesta(string s);
    void onCompleteMsg(float* arg);
    void cambiaFoto(ofEventArgs & args);
    void finTiempoPartida(ofEventArgs & args);
    
    void guardaPosiciones();
    
    ofxInteractiveViewPort viewportImagen, viewportAciertos, viewportMascara, viewportCoru, viewportCadiz, viewportTiempo;
    ofFbo fboImagen, fboAciertos, fboTiempo, fboMensajes;
    

};

#endif
