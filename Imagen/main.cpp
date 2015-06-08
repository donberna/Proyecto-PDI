/*
    Luis Ovidio GOnzalez Codigo: 201154010
    Miguel Angel Bernal Codigo: 201153852
    Aslhey Ramirez Codigo:1153765
*/
#include <iostream>
#include "Imagen.h"

using namespace std;


int main()
{
    Imagen I(50,50);
    I.lee("RG1.pgm");

    vector<int> h;
    h.push_back(0); h.push_back(1); h.push_back(0);
    h.push_back(1); h.push_back(1); h.push_back(1);
    h.push_back(0); h.push_back(1); h.push_back(0);
    int tamano = 3;

    I.lee("imagenes/In/RG1.pgm");
    I.filtradoEspacial(tamano,h,0.5);
     I.escribe("imagenes/Out/RG/SalidaRG1.pgm");

    I.lee("imagenes/Out/RG/SalidaRG1.pgm");
    I.operadorUmbral(150);
    I.escribe("imagenes/Out/RG/SalidaUmbralRG1.pgm");

    //I.mejorarImagen();

    //resta
    /*I.lee("SalidaInvertir.pgm");
    Imagen I2(50,50);
    I2.lee("RG4.pgm");
    I.resta(I2, "salidaResta.pgm");*/

    //Invertir
    /*I.lee("invertirRLA4.pgm");
    I.invertir_imagen();
    I.escribe("dosInvertidaRLA4.pgm");*/

    //operador Umbral --este es
    /*I.lee("salidaSuavizadoRLA4.pgm");
    I.operadorUmbral(100);
    I.escribe("umbralRL4.pgm");*/





    // se lee la imagen :)

    vector<int> h;
    h.push_back(1); h.push_back(1); h.push_back(1);
    h.push_back(1); h.push_back(9); h.push_back(1);
    h.push_back(1); h.push_back(1); h.push_back(1);
    int tamano = 3;

    //para aplicar el filtro paso alto
    I.filtradoEspacial(tamano,h,0.5);
    I.escribe("filtradoEspacial.pgm");

    return 0;
}
