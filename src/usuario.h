//
//  usuario.h
//  pepa
//
//  Created by ignacio pedreira gonzalez on 23/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

// control de user para el juego
// graba los datos en una bd de mysql

#ifndef PEPA_USUARIO
#define PEPA_USUARIO

#include "ofxMySQL.h"

class usuario{
    
public:
    
    void    conectar();
    void    ponNombre(string _nombre);
    void    ponMovil(string _movil);
    void    ponPuntuacion(int _puntos);
    void    clearDatos();
    void    cerrar();
    
    void    guardaJugador();
    string     damePuntuacionMaxima();
    bool    compruebaUser();

private:
    
    ofxMySQL    db;
    string      nombre, movil;
    int         puntos;
};


#endif
