//
//  usuario.cpp
//  pepa
//
//  Created by ignacio pedreira gonzalez on 23/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "usuario.h"

void   usuario::conectar(){
    db.connect("127.0.0.1", "root", "root", "participantes");
}

void   usuario::ponNombre(string _nombre){
    nombre = _nombre;
}

void   usuario::ponMovil(string _movil){
    movil = _movil;
}

void   usuario::ponPuntuacion(int _puntos){
    puntos = _puntos;
}

bool   usuario::compruebaUser(){
    int cuantso = db.getNumRecords("usuarios ", "movil","movil="+movil+"");
    
    if(cuantso>0){
        return true;
    }else{
        return false;
    }
}
void   usuario::cerrar(){
    db.close();
}
void   usuario::clearDatos(){
    nombre = "";
    puntos = 0;
    movil = "";
}

void   usuario::guardaJugador(){
    
    vector<ofxMySQLField> valores;
    
    ofxMySQLField nome("nombre", "'"+nombre+"'");
    ofxMySQLField num("movil", "'"+movil+"'");
    ofxMySQLField pts("puntos", ofToString(puntos));
    
    valores.push_back(nome);
    valores.push_back(num);
    valores.push_back(pts);
    
    db.insert("usuarios", valores);
}

string   usuario::damePuntuacionMaxima(){
    vector<string> resultado;
    
    if(db.getStrings(resultado, "usuarios ", "puntos","")){
        //cout << resultado.size() << endl;
        return resultado[0];   
    }else{
        return "no db";
    }
    
}