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


class controlImagenes{
public:

    ofxMask mascara;
    ofQTKitPlayer mascaraVideo;
    ofxTimer tiempoPartida;
    ofTrueTypeFont fuenteMarcador;
    ofTrueTypeFont fuenteLeyenda;
    ofSoundPlayer  sndAcierto, sndFallo;
    
    vector<imagenJuego*> fichas;
    
    int indexFicha;
    int puntos;
    float alphaBotones;   
    
    boton botonCoruna;
    boton botonCadiz;
    
    void setup();
    void update();
    void draw();
    
    void cargaFichas();
    void lanzaFicha();
    void botonCiudad(string & s);
    void pacman(int resolution, float radius, float loaded, int px, int py);
};

#endif
