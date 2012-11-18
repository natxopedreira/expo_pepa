/*
 *  boton.h
 *  pepa
 *
 *  Created by natxo on 09/11/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef _BOTON
#define _BOTON

#include "ofMain.h"

class boton {
public:
    int ancho, alto, posx, posy, screenPosx, screenPosy;
    bool touchOver;
    bool activo;
    string valor;
    string label;
    
    ofImage fondo;
    ofEvent<string> seleccionBoton;
    ofFbo fbo;
    ofTrueTypeFont * fuente;
    
	boton();
	
	void setup(int _posx,int _posy, string _valor, string _url, string _label, ofTrueTypeFont & _fuente);
	void update();
	void render();
    
    
    bool isUnder(int px, int py);
    
    void mousePressed(ofMouseEventArgs& rArgs);
    void mouseReleased(ofMouseEventArgs& rArgs);
};




#endif