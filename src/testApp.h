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
    
        void btnGuiCoru(bool & pressed);
        void btnGuiCadiz(bool & pressed);
        void btnGuiAciertos(bool & pressed);
        void btnGuiMascara(bool & pressed);
        void btnGuiTiempo(bool & pressed);
		
	controlImagenes * partida;
    
    ofxPanel gui;
    ofxToggle vImagenOn, vAciertosOn, vMascaraOn, vCoruOn, vCadizOn, vTiempoOn;
    bool verGui;
    
};
