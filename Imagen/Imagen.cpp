/*
    Luis Ovidio GOnzalez Codigo: 201154010
    Miguel Angel Bernal Codigo: 201153852
    Aslhey Ramirez Codigo:1153765
*/

#include "Imagen.h"

using namespace std;

Imagen::Imagen() //aqui se llama al constructor de _pixel (por defecto)
{
    _alto = 0;
    _ancho = 0;
}

Imagen::~Imagen()
{
    //dtor
}

Imagen::Imagen(const Imagen& other)
: _pixels(other._pixels)
{
    _alto = other._alto;
    _ancho = other._ancho;
}

Imagen::Imagen(int ancho, int alto)
: _pixels(ancho*alto,0)
{
    _alto = alto;
    _ancho = ancho;
}

void Imagen::lee(string nombrefichero){
    ifstream F(nombrefichero.c_str());
    if (!F.is_open()){
        cout <<"No se ha podido abrir '" << nombrefichero << "'" << endl;
        return;
    }
    string linea;
    getline(F, linea);
    if (linea != "P2"){
        cout <<"formato incorrecto" << endl;
        return;
    }
    getline(F, linea); //suponemos que son comentarios
    while (linea[0] == '#'){
        getline(F,linea);
    }
    istringstream S(linea);
    S >> _ancho >> _alto;
    //int max;
    F >> max; //suponer max es 255
    _pixels.resize((_ancho*_alto));
    for(int i = 0; i < _pixels.size(); i++){
        F >> _pixels[i];
    }
}
void Imagen::escribe(string nombrefichero)const{
    ofstream F(nombrefichero.c_str());
    F <<"P2" << endl;
    F <<"# escrito por la clase Imagen" << endl;
    F << _ancho << ' ' << _alto << endl;
    F << 255 << endl;
    for(int i=0; i < _pixels.size();i++){
        F << _pixels[i] << ' ';
        if(i%_ancho == (_ancho-1)){
            F<<endl;
        }
    }
}


/* operadores punto 2.2 */
void Imagen::invertir_imagen(){

    for(int i = 0; i < _pixels.size(); i++){
        _pixels[i]=255-_pixels[i];
        if(_pixels[i]<0){
            _pixels[i]=0;
        }
    }
}

void Imagen::operadorUmbral(int p1){
    for(int i = 0; i < _pixels.size(); i++){
            if(_pixels[i] <= p1)_pixels[i] = 0;
            if(_pixels[i] > p1) _pixels[i] = max;

    }
}

void Imagen::resta(Imagen i1, string nombrearchivo){
    Imagen temp(_ancho, _alto);
 	int s = _pixels.size();
	for(int i=0; i < s;i++)
      {
        if((_pixels[i] - i1.getpixel(i))*2 < 0) temp.setpixel(i, 0);
        else temp.setpixel(i,(_pixels[i] - i1.getpixel(i))*2 );
      }

    temp.escribe(nombrearchivo);

}



void Imagen::colocar_ceros(){

    //variables de la nueva matriz con los ceros
    ancho1 = _ancho + cerosPorFila;
    //cout<<"ancho1: "<<ancho1<<endl;
    alto1 = _alto + cerosPorFila;
    //cout<<"alto1: "<<alto1<<endl;
    int longitud = ancho1 * alto1;
    //cout<<"longitud: "<<longitud<<endl;
    //vector donde se guarda la nueva imagen con ceros en los bordes
    _pixels2.resize(longitud);

    // se recorre la imagen y se agregan los ceros en las nuevas posiciones
    for(int i = 0; i < ancho1 ; i++){
        for(int j = 0; j < alto1 ; j++){

            if( ((i>=bordeCeros) && (i<ancho1-bordeCeros))&&((j>=bordeCeros) && (j<alto1-bordeCeros)) ){
                setpixel(i,j,getpixel(i-bordeCeros,j-bordeCeros));
            }
        }
    }
}

void Imagen::filtradoEspacial(int tamano, std::vector<int> mascara, double coeficiente){

    /* se acomoda la imagen con un borde de ceros*/

    /* cerosPorFila = numero de ceros que se necitan agregar a la matriz en la fila*/
    cerosPorFila = tamano-1;

    // bordeCeros = numero columnas y filas que agrego de ceros
    bordeCeros = tamano/2;

    colocar_ceros();

    // se crean las variables para recorrer la imagen
    int indice_mini_matriz = 0;
    int indice_imagen = 0;
    int salto=0; // variable para conocer cuando debe cambiar de fila dentro del vector
    double suma = 0;

    // se recorre el vector de la imagen con ceros
    for(int i = (ancho1*bordeCeros); i <= ( _pixels2.size() - ((ancho1*bordeCeros) + cerosPorFila) ); i++){

            //saca la minimatriz dentro de la imagen y realiza los calculos con la mascara
            for(int j = 0; j < mascara.size(); j++){

                suma += _pixels2[indice_imagen + indice_mini_matriz] * mascara[j];
                //cout<<"indice: "<<_pixels2[indice_imagen+ indice_mini_matriz]<<" mascara: "<<mascara[j]<<endl;
                //cout<<"indice: "<<indice_imagen+ indice_mini_matriz<<" mascara: "<< mascara[j]<<endl;
                indice_mini_matriz++;

                if( (indice_mini_matriz % (tamano)) == 0 ){
                    indice_imagen +=  ancho1;
                    indice_mini_matriz = 0;
                }

            }
                //cout<<"suma"<<suma<<endl;
                suma = coeficiente * suma;
                if( suma <= 0){
                    suma=0;
                }else if(suma >= 255){
                    suma=255;
                }
                _pixels3.push_back(round(suma));
                suma = 0;

                indice_imagen = ((i+1)-(ancho1*bordeCeros));
                salto++;

                // se verifica el indice para cambiar de fila dentro del vector
                if( (salto % _ancho) == 0){
                    indice_imagen+=cerosPorFila;
                    i+=cerosPorFila;
                }
        }
}
