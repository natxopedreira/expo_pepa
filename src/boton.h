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
#include "ofxTweenzor.h"

class boton : public ofRectangle {
public:
    
	boton();
	
	void setup(int _posx,int _posy,int _ancho,int _alto, string _valor, string _label, ofTrueTypeFont & _fuente);
	void update();
	void render();
    
    void reset();
    void animaOk();
    void animaError();
    
    //    bool isUnder(int px, int py);     // REPLACED with ofRectangle.inside();
    //    int     screenPosx, screenPosy;   // REPLACED with ofRectangle.x and ofRectangle.y;
    //    int     ancho, alto;              // REPLACED with ofRectangle.width and ofRectangle.height;
    
private:

    ofTrueTypeFont * fuente;
    
    string  valor;
    string  label;
    float   cr,cg,cb;
    float   tr,tg,tb;
    
    int     posx, posy;
    bool    touchOver;
};

#endif