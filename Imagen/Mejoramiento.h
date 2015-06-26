#ifndef MEJORAMIENTO_H
#define MEJORAMIENTO_H
#include "Imagen.h"

using namespace std;

class Mejoramiento
{
    public:
        Mejoramiento();

        static vector<int> obtenerMascara1()
        {
            vector<int> mascara1;
            mascara1.push_back(0);  mascara1.push_back(1);  mascara1.push_back(0);
            mascara1.push_back(1);  mascara1.push_back(1);  mascara1.push_back(1);
            mascara1.push_back(0);  mascara1.push_back(1);  mascara1.push_back(0);
            return mascara1;
        }


        static Imagen normal(Imagen input, int umbral=150)
        {
            vector<int> mascara1 = obtenerMascara1();

            input.filtradoEspacial(3,mascara1,0.5);

            input.ecualizarHistograma();
            input.operadorUmbral(umbral);//150 //210

            return input;
        }

        static Imagen ruido(Imagen input, int umbral=160)
        {
            Imagen original = input;
            vector<int> mascara1 = obtenerMascara1();


            input.intervaloUmbralInvertido(25,255);//

            //2-invertir imagen salida paso 1
            input.invertir_imagen();


            //3-restar salida paso 2 con la imagen original
            input = input.resta(original);

            //4-invertir salida paso 3
            input.invertir_imagen();

            //5-filtrado espacial salida paso 4
            input.filtradoEspacial(3,mascara1,0.5);
            input.operadorUmbral(umbral);


            return input;
        }

        virtual ~Mejoramiento();
    protected:
    private:
};

#endif // MEJORAMIENTO_H
