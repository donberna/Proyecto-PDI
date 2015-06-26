#ifndef MEDIDA_H
#define MEDIDA_H

#include "Imagen.h"

using namespace std;


class Medida
{
    public:
        Medida() {}

        static void test(Imagen *img)
        {
            //1:  busca la columna donde inicia el area de interes
            int columna = encontrar_columna(img);
            //cout<<"pivote: "<<columna<<endl;


            //al tratarse de un aro entonces tendremos 4 fronteras
            int cambios[4] = {0};
            //cambios[0] = primer borde
            //cambios[1] = segundo borde

            //cambios[2] = primer borde
            //cambios[3] = segundo borde

            //se toma un color inicial como pivote, el cual se usa para determinar cuando haya un cambio de color
            int color_pivote = img->getpixel(0,columna);

            //se recorre la imagen de izquierda a derecha por la
            for(int j = 0, contador_cambios=0;j < img->ancho(); j++)
            {
                if (img->getpixel(j,columna) != color_pivote)
                {
                    cambios[contador_cambios] = j;
                    contador_cambios++;
                    color_pivote = img->getpixel(j,columna);
                }
            }

            if(cambios[3] == 0)
            {
                cout<<"No se pueden calcular las dimensiones"<<endl;
                return;
            }


            cout<<"Diametro externo: "<<cambios[3] - cambios[0]<<endl;
            cout<<"Diametro interno: "<<cambios[2] - cambios[1]<<endl;
            cout<<"Espesor: "<<cambios[1] - cambios[0]<<endl;

        }
        virtual ~Medida() {}
    protected:
    private:

    static int encontrar_columna(Imagen *img)
    {
        for(int i = 0;i < img->ancho(); i++)
            {
                for(int j = 0;j < img->alto(); j++)
                {
                    if(img->getpixel(i,j) == 0)
                    {
                        return j;
                    }
                }
            }
            return -1;
    }
};

#endif // MEDIDA_H

