//
//  controlImagenes.h
//  pepa
//
//  Created by natxo on 09/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef JUEGO_FICHAS
#define JUEGO_FICHAS

#include "ofMain.h"
#include "imagenJuego.h"
#include "boton.h"
#include "usuario.h"

//non core addons
#include "ofxTweenzor.h"
#include "ofxFX.h"
#include "ofxInteractiveViewPort.h"
#include "ofxTimer.h"
#include "ofxTextInputField.h"
#include "ofxTextSuite.h"


enum EstadoPartida{
    ESTADO_REPOSO,
    ESTADO_NUEVO_USUARIO_NOMBRE,
    ESTADO_NUEVO_USUARIO_MOVIL,
    ESTADO_COMIENZA,
    ESTADO_JUGANDO,
    ESTADO_PARTIDA_ACABADA
};

class juegoFichas {
public:
    
    juegoFichas();
    ~juegoFichas();
    
    void    iniciaPartida();
    void    nuevoUsuario();
    void    guardaPosiciones();
    void    comienza();
    void    ponMovil();
    void    resetAlphas();
    
    void    update();
    void    draw();
    void    usuarioRepe();

    ofxTextInputField       campoNombre, campoMovil;
    ofxInteractiveViewPort  viewportImagen, viewportAciertos, viewportMascara, viewportCoru, viewportCadiz, viewportTiempo, viewportBg, viewportLogo;
    EstadoPartida           estadoPartida;
    
    void    _botonCiudad(string & s);
    
    usuario         gestorUsuarios;
    
    ofxXmlSettings  xmlFichas; // xml con la lista de imagenes
    

    
private:
    
    void    _configViewPorts();
    void    _renderViewports();
    
    void    _cargaFichas();
    void    _lanzaFicha();

    
    void    _mensajeRespuesta(string s);
    void    _onCompleteMsg(float* arg);
    void    _onCompleteTiempoTexto(float* arg);
    void    _onCompleteTiempoFicha(ofEventArgs & args);
    void    _cambiaFoto(ofEventArgs & args);
    void    _finTiempoPartida(ofEventArgs & args);
    void    _finTiempoTexto(ofEventArgs & args);
    void    _finTiempoComienzo(ofEventArgs & args);
    void    _finTiempoReposo(ofEventArgs & args);
    
    ofxMask         mascara;
    ofQTKitPlayer   mascaraVideo;
    ofxTimer        tiempoPartida;
    ofxTimer        tiempoEntreFoto;
    ofxTimer        tiempoTexto;
    ofxTimer        tiempoLeerTexto;
    ofxTimer        tiempoComienzo;
    ofxTimer        vuelveReposo;
    
    ofTrueTypeFont  fuenteMarcador;
    ofTrueTypeFont  fuenteLeyenda;
    ofTrueTypeFont  fuenteCampos;
    ofTrueTypeFont  fuenteTiempo;
    ofTrueTypeFont  fuenteAviso;
    ofTrueTypeFont  fuenteBonecaPeque;
    ofTrueTypeFont  fuenteBonecaGrande;
    ofTrueTypeFont  fuenteBotones;  
    ofTrueTypeFont  fuenteMini;
    
    ofxTextBlock    direccion;
    ofxTextBlock    nombreCiudad;
    
    // vars skin
    ofImage         boneca;
    ofImage         mancha;
    ofImage         logo;

    
    ofImage         imagenBg, imgPepa;
    ofFbo           fboImagen, fboAciertos, fboTiempo, fboMensajes, fboCoru, fboCadiz, fboLogo;
    vector<imagenJuego*> fichas;    // ImagenJuego parece s—lo contener informaci—n para eso son mejores los struct  
    
    boton           botonCoruna;
    boton           botonCadiz;
    
    ofRectangle     r;
    
    string          mensajeStr;
    float           alphaBotones;
    float           alphaMsjStr;
    float           alphaTextoFoto;
    float           alphaRevela;
    float           alphaForms;
    float           alphaForms2;
    float           scaleMsjStr;
    float           alphaComienza;
    float           tcr, tcg, tcb;
    float           bgr, bgg, bgb;
    
    float           bonecaX, bonecaY; // posiciones de la mu–eca de la pepa
    float           bonecaAncho, bonecaAlto; // posiciones de la mu–eca de la pepa
    
    int             indexFicha;
    int             puntos;
    string             record;
    
    bool            mensaje;
    bool            mensajeInicio;
    bool            textoFoto;
    bool            botonEnabled;
    bool            usuarioRepetido;
    
};

#endif
