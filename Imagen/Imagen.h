/*
    Luis Ovidio GOnzalez Codigo: 201154010
    Miguel Angel Bernal Codigo: 201153852
    Aslhey Ramirez Codigo:1153765
*/

#ifndef IMAGEN_H
#define IMAGEN_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>

class Imagen
{
    public:
        Imagen();
        virtual ~Imagen();
        Imagen(const Imagen& other);
        Imagen(int ancho, int alto);
        int ancho() const {return _ancho;}
        int alto() const {return _alto;}
        int getpixel(int i, int j) const {
            return _pixels[j*_ancho + i];
        }
        void setpixel(int i, int j, int valor){
            _pixels[j*_ancho+i] = valor;
        }
        void lee(std::string nombrefichero);
        void escribe(std::string nombrefichero)const;


        /* operadores para tratar el ruido de las imagenes */
        void invertir_imagen();
        void operadorUmbral(int p1);
        int getpixel(int i) const {return _pixels[i];}
        void setpixel(int i, int valor){_pixels[i] = valor;}
        void resta(Imagen,std::string);
        void colocar_ceros();
        void filtradoEspacial(int tamano, std::vector<int> mascara, double coeficiente);

    protected:
    private:
        std::vector<int> _pixels;
        std::vector<int> _pixels2;
        std::vector<int> _pixels3;

        int max;
        int _ancho, ancho1, _alto, alto1;
        int bordeCeros;
        int cerosPorFila;

};

#endif // IMAGEN_H