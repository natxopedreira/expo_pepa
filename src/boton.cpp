/*
 *  boton.cpp
 *  pepa
 *
 *  Created by natxo on 09/11/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "boton.h"

boton::boton(){
    ancho = 0;
    alto = 0;
    posx = 0;
    posy = 0;
    screenPosx = 0; 
    screenPosy = 0;
    touchOver = false;
    activo = false;
}

//--------------------------------------------------------------
void boton::setup(int _posx,int _posy, string _valor, string _url){
    posx = _posx;
    posy = _posy;
    valor = _valor;
    
    ofAddListener(ofEvents().mousePressed, this, &boton::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &boton::mouseReleased);
    
    fondo.loadImage(_url);
    ancho = fondo.getWidth();
    alto = fondo.getHeight();
    
    fbo.allocate(320,240);
    
    fbo.begin();
    ofClear(0);
    fbo.end();
}

//--------------------------------------------------------------
void boton::update(){
    fbo.begin();
    ofClear(0);
    fondo.draw(posx, posy);
    fbo.end();
}

//--------------------------------------------------------------
void boton::draw(){
   // ofPushStyle();
    //ofSetColor(255,255,255);
    //if(touchOver) ofSetColor(255,0,0);
    //fondo.draw(posx, posy);
    //ofRect(posx, posy, ancho, alto);
   // ofPopStyle();
}

//--------------------------------------------------------------
bool boton::isUnder(int px, int py){  
    if (px < screenPosx || px > screenPosx + ancho) return false;  
    if (py < screenPosy || py > screenPosy + alto) return false;  
    return true;  
}

//--------------------------------------------------------------
void boton::mousePressed(ofMouseEventArgs& rArgs){
    if(isUnder(rArgs.x, rArgs.y)){
        touchOver = true;
        if(activo) ofNotifyEvent(seleccionBoton,valor,this); //seleccionBoton
    }
    
}

//--------------------------------------------------------------
void boton::mouseReleased(ofMouseEventArgs& rArgs){
     if(touchOver) touchOver = false;
}
