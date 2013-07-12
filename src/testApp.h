#pragma once

#include "ofMain.h"

//  Addons
//
#include "ofxGui.h"
#include "ofxTuio.h"

//  Non core addons (just to know for every time you make a new project)
//
//  #include "ofxTextInputField.h"
//  #include "ofxBlobTracker.h"
//  #include "ofxFX.h"
//  #include "ofxInteractiveSurface.h"
//  #include "ofxKinect.h"
//  #include "ofxOpenCV.h"
//  #include "ofxTimer.h"
//  #include "ofxTweenzor.h"
//  #include "ofxXmlSettings.h"

//  Classes
//
#include "juegoFichas.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    ofxTuioClient   clienteTuio;

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    void cursorDentro(ofxTuioCursor & tr);
    void cursorMueve(ofxTuioCursor & tr);
    void cursorBorra(ofxTuioCursor & tr);
    
    void pulsacion(int _ptx, int pty);

    void setupGui();
    
    void btnGuiBg(bool & pressed);
    void btnGuiCoru(bool & pressed);
    void btnGuiCadiz(bool & pressed);
    void btnGuiAciertos(bool & pressed);
    void btnGuiMascara(bool & pressed);
    void btnGuiTiempo(bool & pressed);
    void btnGuiLogo(bool & pressed);
    
    void btnGuiBgMask(bool & pressed);
    void btnGuiCoruMask(bool & pressed);
    void btnGuiCadizMask(bool & pressed);
    void btnGuiAciertosMask(bool & pressed);
    void btnGuiMascaraMask(bool & pressed);
    void btnGuiTiempoMask(bool & pressed);
    void btnGuiLogoMask(bool & pressed);
		
	juegoFichas * partida;
    
    ofxPanel gui;
    ofxToggle vImagenOn, vAciertosOn, vMascaraOn, vCoruOn, vCadizOn, vTiempoOn, vBgOn, vLogoOn;
    ofxToggle maskImagenOn, maskAciertosOn, maskMascaraOn, maskCoruOn, maskCadizOn, maskTiempoOn, maskBgOn, maskLogoOn;
    ofxIntSlider ancho, alto,px,py;
    
    int _ptx, _pty,_ancho,_alto;
    
    bool verGui;
    
    int ptx, pty;
};
