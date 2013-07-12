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
    posx = 0;
    posy = 0;

//    ancho = 0;
//    alto = 0;
//    screenPosx = 0;
//    screenPosy = 0;
    
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    
    touchOver = false;
    fuente = NULL;
    label = "";
    
    cr = 238;
    cg = 236;
    cb = 188;
    
    tr = 47;
    tg = 58;
    tb = 49;   
}
//--------------------------------------------------------------
void boton::animaOk(){
    Tweenzor::add(&cr, cr, 19, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE);
    Tweenzor::add(&cg, cg, 132, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE);
    Tweenzor::add(&cb, cb, 0, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE); 
    
    Tweenzor::add(&tr, cr, 238, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE);
    Tweenzor::add(&tg, cg, 236, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE);
    Tweenzor::add(&tb, cb, 188, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE); 
}
//--------------------------------------------------------------
void boton::animaError(){
    Tweenzor::add(&cr, cr, 150, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE);
    Tweenzor::add(&cg, cg, 41, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE);
    Tweenzor::add(&cb, cb, 41, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE); 
    
    Tweenzor::add(&tr, cr, 238, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE);
    Tweenzor::add(&tg, cg, 236, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE);
    Tweenzor::add(&tb, cb, 188, 0.0f, 0.3f, EASE_OUT_IN_BOUNCE); 
}
//--------------------------------------------------------------
void boton::setup(int _posx,int _posy,int _ancho,int _alto, string _valor, string _label, ofTrueTypeFont & _fuente){
    posx = _posx;
    posy = _posy;
    valor = _valor;
    
    //ofAddListener(ofEvents().mousePressed, this, &boton::mousePressed);
    //ofAddListener(ofEvents().mouseReleased, this, &boton::mouseReleased);
    

    width = _ancho;
    height = _alto;
    
    fuente = &_fuente;
    label = _label;
}

//--------------------------------------------------------------
void boton::update(){

}
void boton::reset(){
    cr = 238;
    cg = 236;
    cb = 188;
    
    tr = 47;
    tg = 58;
    tb = 49;  
}
//--------------------------------------------------------------
void boton::render(){
    ofSetColor(cr, cg, cb);
    ofRect(0,0,width,height); // rect blanco
    
    ofSetColor(tr, tg, tb);
    fuente->drawString(label,posx, posy);
}

//--------------------------------------------------------------
//bool boton::isUnder(int px, int py){  
//    if (px < screenPosx || px > screenPosx + ancho) return false;  
//    if (py < screenPosy || py > screenPosy + alto) return false;  
//    return true;  
//}
