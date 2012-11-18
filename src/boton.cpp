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
    fuente = NULL;
    label = "";
}

//--------------------------------------------------------------
void boton::setup(int _posx,int _posy, string _valor, string _url, string _label, ofTrueTypeFont & _fuente){
    posx = _posx;
    posy = _posy;
    valor = _valor;
    
    ofAddListener(ofEvents().mousePressed, this, &boton::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &boton::mouseReleased);
    
    fondo.loadImage(_url);
    /*ancho = fondo.getWidth();
    alto = fondo.getHeight();*/
    
    fbo.allocate(320,240);
    
    fbo.begin();
    ofClear(0);
    fbo.end();
    
    fuente = &_fuente;
    label = _label;
}

//--------------------------------------------------------------
void boton::update(){

}

//--------------------------------------------------------------
void boton::render(){
    fbo.begin();
    ofClear(0);
    fuente->drawString(label,posx, posy);
    //fondo.draw(posx, posy);
    fbo.end();
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
