#pragma once

#include "ofMain.h"

//non core addons
#include "controlImagenes.h"
#include "ofxGui.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void setupGui();
    
        void btnGuiCoru(bool & pressed);
        void btnGuiCadiz(bool & pressed);
        void btnGuiAciertos(bool & pressed);
        void btnGuiMascara(bool & pressed);
        void btnGuiTiempo(bool & pressed);
    
        void btnGuiCoruMask(bool & pressed);
        void btnGuiCadizMask(bool & pressed);
        void btnGuiAciertosMask(bool & pressed);
        void btnGuiMascaraMask(bool & pressed);
        void btnGuiTiempoMask(bool & pressed);
    
        bool juegoEmpezado;
		
	controlImagenes * partida;
    
    ofxPanel gui;
    ofxToggle vImagenOn, vAciertosOn, vMascaraOn, vCoruOn, vCadizOn, vTiempoOn;
    ofxToggle maskImagenOn, maskAciertosOn, maskMascaraOn, maskCoruOn, maskCadizOn, maskTiempoOn;
    bool verGui;
    
};
