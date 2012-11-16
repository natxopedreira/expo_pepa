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
#include "utilidadesDraw.h"

//non core addons
#include "ofxTweenzor.h"
#include "ofxFX.h"
#include "ofxInteractiveViewPort.h"



class controlImagenes{
public:

    ofxMask mascara;
    ofQTKitPlayer mascaraVideo;
    ofxTimer tiempoPartida;
    ofTrueTypeFont fuenteMarcador;
    ofTrueTypeFont fuenteLeyenda;
    ofTrueTypeFont fuenteAlerta;
    ofSoundPlayer  sndAcierto, sndFallo;
    ofxTimer tiempoEntreFoto;
    
    vector<imagenJuego*> fichas;
    
    int indexFicha;
    int puntos;
    float alphaBotones;
    bool mensaje;
    string mensajeStr;
    float alphaMsjStr;
    float scaleMsjStr;
    bool partidaTerminada;
    
    boton botonCoruna;
    boton botonCadiz;
    
    void setup();
    void update();
    void draw();
    
    void cargaFichas();
    void lanzaFicha();
    void botonCiudad(string & s);
    void pacman(int resolution, float radius, float loaded, int px, int py);
    
    void mensajeRespuesta(string s);
    void onCompleteMsg(float* arg);
    void cambiaFoto(ofEventArgs & args);
    void finTiempoPartida(ofEventArgs & args);
    
    void guardaPosiciones();
    
    ofxInteractiveViewPort viewportImagen, viewportAciertos, viewportMascara, viewportCoru, viewportCadiz, viewportTiempo;
    ofFbo fboImagen, fboAciertos, fboMascara, fboCou, fboCadiz, fboTiempo;
    

};

#endif
