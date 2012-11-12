//
//  controlImagenes.h
//  pepa
//
//  Created by ignacio pedreira gonzalez on 09/11/12.
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


class controlImagenes{
public:

    ofxMask mascara;
    vector<imagenJuego*> fichas;
    ofQTKitPlayer mascaraVideo;
    int indexFicha;
    int puntos;
    float alphaBotones;
    
    ofxTimer tiempoPartida;
    
    boton botonCoruna;
    boton botonCadiz;
    
    ofTrueTypeFont fuenteMarcador;
    
    ofSoundPlayer  sndAcierto, sndFallo;
    
    void setup();
    void update();
    void draw();
    
    void cargaFichas();
    void lanzaFicha();
    void botonCiudad(string & s);
};

#endif
