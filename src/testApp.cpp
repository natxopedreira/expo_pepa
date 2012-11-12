#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);
    
    partida = NULL;
	
}

//--------------------------------------------------------------
void testApp::update(){
   if(partida) partida->update();
}

//--------------------------------------------------------------
void testApp::draw(){
    if(partida){
      partida->draw();   
    }else{
      // esta en reposo sin ningun user
        
      ofDrawBitmapStringHighlight("PULSA LA TECLA n PARA EMPEZAR A JUGAR", 500, 350);
    }
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 10);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'n'){
        partida = new controlImagenes();
        partida->setup();
    }
    
    if(key == 'd' && partida){
        delete partida;
        partida = new controlImagenes();
        partida->setup();
    }

    if(partida) partida->lanzaFicha();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){}