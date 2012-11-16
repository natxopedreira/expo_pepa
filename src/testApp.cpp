#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);
    
    partida = NULL;
    gui.setup();
    gui.add(vCoruOn.setup("viewport Cor Editable", false));
	gui.add(vCadizOn.setup("viewport Cadiz Editable", false));
    gui.add(vAciertosOn.setup("viewport Aciertos Editable", false));
    gui.add(vMascaraOn.setup("viewport Mascara Editable", false));
    gui.add(vTiempoOn.setup("viewport Tiempo Editable", false));
    
    vCoruOn.addListener(this, &testApp::btnGuiCoru);
    vCadizOn.addListener(this, &testApp::btnGuiCadiz);
    vAciertosOn.addListener(this, &testApp::btnGuiAciertos);
    vMascaraOn.addListener(this, &testApp::btnGuiMascara);
    vTiempoOn.addListener(this, &testApp::btnGuiTiempo);
    
    verGui = false;
}

//--------------------------------------------------------------
void testApp::update(){
   if(partida) partida->update();
}
//--------------------------------------------------------------
void testApp::btnGuiCoru(bool & pressed){
    if(!partida) return;
    partida->viewportCoru.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiCadiz(bool & pressed){
    if(!partida) return;
    partida->viewportCadiz.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiAciertos(bool & pressed){
    if(!partida) return;
    partida->viewportAciertos.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiMascara(bool & pressed){
    if(!partida) return;
    partida->viewportMascara.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiTiempo(bool & pressed){
    if(!partida) return;
    partida->viewportTiempo.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::draw(){
    
    if(partida && !partida->partidaTerminada){
      partida->draw();   
    }else if(partida && partida->partidaTerminada){
      // esta en reposo sin ningun user
      ofDrawBitmapStringHighlight("PARTIDA TERMINADA "+ofToString(partida->puntos), 500, 350);
    }else{
    
    ofDrawBitmapStringHighlight("PULSA LA TECLA n PARA EMPEZAR A JUGAR", 500, 350);
    }
    
    if(verGui) gui.draw();
    
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
    
    if(key == 's' && partida){
        partida->guardaPosiciones();
    }
    if(key == OF_KEY_F5){
        verGui = !verGui;
    }
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