#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0, 0, 0);
    
    partida = new juegoFichas();
    
    setupGui();
    
    clienteTuio.start(3333);
    
    ofAddListener(clienteTuio.cursorAdded, this, &testApp::cursorDentro);
    ofAddListener(clienteTuio.cursorUpdated, this, &testApp::cursorMueve);
    ofAddListener(clienteTuio.cursorRemoved, this, &testApp::cursorBorra);
}

//--------------------------------------------------------------
void testApp::update(){
    partida->update();
    
    clienteTuio.getMessage();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    partida->draw();
    
    
    if(verGui) gui.draw();
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 10);
    
    
   // ofPushStyle();
   // ofSetColor(255, 0, 0);
   // ofCircle(ptx, pty, 20);
   // ofPopStyle();
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
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
void testApp::pulsacion(int _ptx, int pty){
    if(partida->viewportMascara.isOver(ofPoint(ptx, pty))){
        // TOUCH EN LA PANTALLA PPAL
        //
        
        if(partida->estadoPartida == ESTADO_REPOSO || partida->estadoPartida == ESTADO_PARTIDA_ACABADA){    
            partida->nuevoUsuario();
            //empieza
            //partida->comienza();
            
        }else if (partida->estadoPartida == ESTADO_NUEVO_USUARIO_NOMBRE && partida->campoNombre.text !=""){
            // ya tienes nombre, lo insertas
            //
            partida->gestorUsuarios.ponNombre(partida->campoNombre.text);
            
            
            partida->resetAlphas();
            partida->estadoPartida = ESTADO_NUEVO_USUARIO_MOVIL;
            partida->campoNombre.endEditing();
            partida->campoMovil.beginEditing();
            
            partida->ponMovil();
            
        }else if (partida->estadoPartida == ESTADO_NUEVO_USUARIO_MOVIL && partida->campoMovil.text !="") {
            // ya tienes nombre, lo insertas
            //
            partida->gestorUsuarios.ponMovil(partida->campoMovil.text);
            partida->campoMovil.endEditing();
            
            // AQUI SE COMPRUEBA SI YA HA JUGADO
            // si ya jugo se va al carajo
            if(!partida->gestorUsuarios.compruebaUser()){
                
                partida->resetAlphas();
                
                
                partida->comienza();
                //partida->iniciaPartida();
            }else{
                // TODO
                // ya has jugado, te muestro un mensaje y vuelves a reposo
                // cout << "REPETIDO" << endl;
                partida->usuarioRepe();
            }
        }
        
    }else if (partida->viewportCoru.isOver(ofPoint(ptx, pty))) {
        // TOUCH EN EL BTN DE CORU„A
        //
        if(partida->estadoPartida == ESTADO_JUGANDO){
            string cual = "coru";
            partida->_botonCiudad(cual);
            
        }
        
    }else if (partida->viewportCadiz.isOver(ofPoint(ptx, pty))) {
        // TOUCH EN EL BTN DE CADIZ
        //
        if(partida->estadoPartida == ESTADO_JUGANDO){
            string cual = "cadiz";
            partida->_botonCiudad(cual);
            
        }
    }

}

void testApp::cursorDentro(ofxTuioCursor & tr){
    ptx = tr.getX()*1600 + 509;
    pty = tr.getY()*900 + 150 ;
    
    pulsacion(ptx, pty);
    
        
    
}
//--------------------------------------------------------------
void testApp::cursorMueve(ofxTuioCursor & tr){
    ptx = tr.getX()*1600+ 509;
    pty = tr.getY()*900 + 150 ;
    
    pulsacion(ptx, pty);
}
//--------------------------------------------------------------
void testApp::cursorBorra(ofxTuioCursor & tr){
}

void testApp::setupGui(){
    gui.setup();
    
    //
    gui.add(vBgOn.setup("area Fondo Edit", false));
    gui.add(vCoruOn.setup("area Coruna Edit", false));
	gui.add(vCadizOn.setup("area Cadiz Edit", false));
    gui.add(vAciertosOn.setup("area Aciertos Edit", false));
    gui.add(vMascaraOn.setup("area Imagen Edit", false));
    gui.add(vTiempoOn.setup("area Tiempo Edit", false));
    gui.add(vLogoOn.setup("area Logo Edit", false));
    
    //
    gui.add(maskBgOn.setup("mask Fondo Edit", false));
    gui.add(maskCoruOn.setup("mask Coru Edit", false));
    gui.add(maskCadizOn.setup("mask Cadiz Edit", false));
    gui.add(maskAciertosOn.setup("mask Aciertos Edit", false));
    gui.add(maskMascaraOn.setup("mask Imagen Edit", false));
    gui.add(maskTiempoOn.setup("mask Tiempo Edit", false));
    gui.add(maskLogoOn.setup("mask Logo Edit", false));
    
    gui.add(px.setup("pos x", _ptx, 0, 1920));
    gui.add(py.setup("pos y", _pty, 0, 1080));
    gui.add(ancho.setup("ancho", _ancho, 0, 1920));
    gui.add(alto.setup("alto", _alto, 0, 1080));
    
    
    //
    vBgOn.addListener(this, &testApp::btnGuiBg);
    vCoruOn.addListener(this, &testApp::btnGuiCoru);
    vCadizOn.addListener(this, &testApp::btnGuiCadiz);
    vAciertosOn.addListener(this, &testApp::btnGuiAciertos);
    vMascaraOn.addListener(this, &testApp::btnGuiMascara);
    vTiempoOn.addListener(this, &testApp::btnGuiTiempo);
    vLogoOn.addListener(this, &testApp::btnGuiLogo);
    
    //
    maskBgOn.addListener(this, &testApp::btnGuiBgMask);
    maskCoruOn.addListener(this, &testApp::btnGuiCoruMask);
    maskCadizOn.addListener(this, &testApp::btnGuiCadizMask);
    maskAciertosOn.addListener(this, &testApp::btnGuiAciertosMask);
    maskMascaraOn.addListener(this, &testApp::btnGuiMascaraMask);
    maskTiempoOn.addListener(this, &testApp::btnGuiTiempoMask);
    maskLogoOn.addListener(this, &testApp::btnGuiLogoMask);
    
    //
    verGui = false;
}
//--------------------------------------------------------------
void testApp::btnGuiLogoMask(bool & pressed){
    if(partida == NULL) return;
    partida->viewportLogo.bEditMask = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiBg(bool & pressed){
    if(partida == NULL) return;
    partida->viewportBg.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiLogo(bool & pressed){
    if(partida == NULL) return;
    partida->viewportLogo.bEditMode = pressed;
}
//--------------------------------------------------------------
void testApp::btnGuiBgMask(bool & pressed){
    if(partida == NULL) return;
    partida->viewportBg.bEditMask = pressed;
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
        // TOUCH EN LA PANTALLA PPAL
        //
        if(partida->estadoPartida == ESTADO_REPOSO || partida->estadoPartida == ESTADO_PARTIDA_ACABADA){    
                partida->nuevoUsuario();
                //empieza
                //partida->comienza();
            
        }else if (partida->estadoPartida == ESTADO_NUEVO_USUARIO_NOMBRE && partida->campoNombre.text !=""){
            // ya tienes nombre, lo insertas
            //
            partida->gestorUsuarios.ponNombre(partida->campoNombre.text);
            
            
            partida->resetAlphas();
            partida->estadoPartida = ESTADO_NUEVO_USUARIO_MOVIL;
            partida->campoNombre.endEditing();
            partida->campoMovil.beginEditing();
            
            partida->ponMovil();
            
        }else if (partida->estadoPartida == ESTADO_NUEVO_USUARIO_MOVIL && partida->campoMovil.text !="") {
            // ya tienes nombre, lo insertas
            //
            partida->gestorUsuarios.ponMovil(partida->campoMovil.text);
            partida->campoMovil.endEditing();
            
            // AQUI SE COMPRUEBA SI YA HA JUGADO
            // si ya jugo se va al carajo
            if(!partida->gestorUsuarios.compruebaUser()){
            
                partida->resetAlphas();
                
            
                partida->comienza();
                //partida->iniciaPartida();
            }else{
                // TODO
                // ya has jugado, te muestro un mensaje y vuelves a reposo
                // cout << "REPETIDO" << endl;
                partida->usuarioRepe();
            }
        }
        
    }else if (partida->viewportCoru.isOver(ofPoint(x, y))) {
        // TOUCH EN EL BTN DE CORU„A
        //
        if(partida->estadoPartida == ESTADO_JUGANDO){
            string cual = "coru";
            partida->_botonCiudad(cual);
        
        }
        
    }else if (partida->viewportCadiz.isOver(ofPoint(x, y))) {
        // TOUCH EN EL BTN DE CADIZ
        //
        if(partida->estadoPartida == ESTADO_JUGANDO){
            string cual = "cadiz";
            partida->_botonCiudad(cual);
            
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){}

