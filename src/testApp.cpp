#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofBackground(0, 0, 0);
    
    partida = new juegoFichas();
    partida->setup();
    
    
    setupGui();
}

//--------------------------------------------------------------
void testApp::update(){
   partida->update();
}


void testApp::draw(){
      partida->draw();
      if(verGui) gui.draw();
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 10);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key) {
        case 'n':
            partida->nuevoUsuario();
            
            break;
             

        case 's':
            partida->guardaPosiciones();
            break; 

            
        case OF_KEY_F5:
            verGui = !verGui;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------



void testApp::setupGui(){
    gui.setup();
    gui.add(vCoruOn.setup("area Coruna Editable", false));
	gui.add(vCadizOn.setup("area Cadiz Editable", false));
    gui.add(vAciertosOn.setup("area Aciertos Editable", false));
    gui.add(vMascaraOn.setup("area Imagen Editable", false));
    gui.add(vTiempoOn.setup("area Tiempo Editable", false));
    
    gui.add(maskCoruOn.setup("mascara Coru Editable", false));
    gui.add(maskCadizOn.setup("mascara Cadiz Editable", false));
    gui.add(maskAciertosOn.setup("mascara Aciertos Editable", false));
    gui.add(maskMascaraOn.setup("mascara Imagen Editable", false));
    gui.add(maskTiempoOn.setup("mascara Tiempo Editable", false));
    
    vCoruOn.addListener(this, &testApp::btnGuiCoru);
    vCadizOn.addListener(this, &testApp::btnGuiCadiz);
    vAciertosOn.addListener(this, &testApp::btnGuiAciertos);
    vMascaraOn.addListener(this, &testApp::btnGuiMascara);
    vTiempoOn.addListener(this, &testApp::btnGuiTiempo);
    
    maskCoruOn.addListener(this, &testApp::btnGuiCoruMask);
    maskCadizOn.addListener(this, &testApp::btnGuiCadizMask);
    maskAciertosOn.addListener(this, &testApp::btnGuiAciertosMask);
    maskMascaraOn.addListener(this, &testApp::btnGuiMascaraMask);
    maskTiempoOn.addListener(this, &testApp::btnGuiTiempoMask);
    
    verGui = false;
}

//--------------------------------------------------------------
void testApp::btnGuiCoru(bool & pressed){
    if(partida == NULL) return;
    partida->viewportCoru.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiCadiz(bool & pressed){
    if(partida == NULL) return;
    partida->viewportCadiz.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiAciertos(bool & pressed){
    if(partida == NULL) return;
    partida->viewportAciertos.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiMascara(bool & pressed){
    if(partida == NULL) return;
    partida->viewportMascara.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiTiempo(bool & pressed){
    if(partida == NULL) return;
    partida->viewportTiempo.bEditMode = pressed;
}

//--------------------------------------------------------------
void testApp::btnGuiCoruMask(bool & pressed){
    if(partida == NULL) return;
    partida->viewportCoru.bEditMask = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiCadizMask(bool & pressed){
    if(partida == NULL) return;
    partida->viewportCadiz.bEditMask = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiAciertosMask(bool & pressed){
    if(partida == NULL) return;
    partida->viewportAciertos.bEditMask = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiMascaraMask(bool & pressed){
    if(partida == NULL) return;
    partida->viewportMascara.bEditMask = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiTiempoMask(bool & pressed){
    if(partida == NULL) return;
    partida->viewportTiempo.bEditMask = pressed;
}
//--------------------------------------------------------------
void testApp::keyReleased(int key){}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    if(partida->viewportMascara.isOver(ofPoint(x, y))){
        if(partida->estadoPartida == ESTADO_NUEVO_USUARIO_NOMBRE){
            partida->estadoPartida = ESTADO_NUEVO_USUARIO_MOVIL;
            partida->campoMovil.beginEditing();
        }else if (partida->estadoPartida == ESTADO_NUEVO_USUARIO_MOVIL) {
            partida->iniciaPartida();
        }
    }
     
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}