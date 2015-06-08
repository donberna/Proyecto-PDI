/*
    Luis Ovidio Gonzalez Codigo: 201154010
    Miguel Angel Bernal Codigo: 201153852
    Aslhey Ramirez Codigo:1153765
*/


#include "Imagen.h"

using namespace std;

//constructor por defecto
Imagen::Imagen()
{
    _alto = 0;
    _ancho = 0;
}

// destructor
Imagen::~Imagen()
{
    //dtor
}

// sobre carga del constructor
Imagen::Imagen(const Imagen& other)
: _pixels(other._pixels)
{
    _alto = other._alto;
    _ancho = other._ancho;
}

//Sobre carga del constructor
Imagen::Imagen(int ancho, int alto)
: _pixels(ancho*alto,0)
{
    _alto = alto;
    _ancho = ancho;
}

// funcion que nos permite leer una imagen en formato pgm
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
    F >> max; //suponer max es 255
    _pixels.resize((_ancho*_alto));
    for(int i = 0; i < _pixels.size(); i++){
        F >> _pixels[i];
    }
}

// funcion para escribir un nuevo archivo (imagen resultante)
void Imagen::escribe(string nombrefichero)const{
    ofstream F(nombrefichero.c_str());
    F <<"P2" << endl;
    F <<"# escrito por la clase Imagen" << endl;
    F << _ancho << ' ' << _alto << endl;
    F << 255 << endl;
    for(int i=0; i < _pixels.size();i++){
        F << _pixels[i] << ' ';
        if(i% _ancho == (_ancho-1)){
            F<<endl;
        }
    }
}

// funcion que aplica el metodo de umbral
void Imagen::operadorUmbral(int p1){
    // se recorre la imagen comparando los valores de la imagen con el minimo y el maximo para aplicar el umbral
    for(int i = 0; i < _pixels.size(); i++){
            if(_pixels[i] <= p1)_pixels[i] = 0;
            if(_pixels[i] > p1) _pixels[i] = max;

    }
}

// funcion que aplica el metodo de umbral invertido entre cierto rango
void Imagen::intervaloUmbralInvertido(int p1, int p2){

    // se recorre la imagen comparando si los valores estan dentro del rango para aplicar el umbral
    for(int i = 0; i < _pixels.size(); i++){
            if( (_pixels[i] <= p1) || (_pixels[i] >= p2) )_pixels[i] = 0;
            if( (p1 < _pixels[i]) && (p2 > _pixels[i])  ) _pixels[i] = max;

    }
}

// funcion que realiza la resta entre dos imagenes
void Imagen::resta(Imagen i1, string nombrearchivo){
    // se crea una imagen temporal para guardar los valores
    Imagen temp(_ancho, _alto);
 	int s = _pixels.size();

 	// se recorren las dos imagenes aplicando la resta
	for(int i=0; i < s;i++)
      {
        if((_pixels[i] - i1.getpixel(i))*2 < 0) temp.setpixel(i, 0);
        else temp.setpixel(i,(_pixels[i] - i1.getpixel(i))*2 );
      }

    temp.escribe(nombrearchivo);

}

// funcion que invierte los valores de la imagen
void Imagen::invertir_imagen(){

    // se recorre la imagen invirtiendo sus valores
    for(int i = 0; i < _pixels.size(); i++){
        _pixels[i]=255-_pixels[i];
        if(_pixels[i]<0){
            _pixels[i]=0;
        }
    }
}

void Imagen::colocar_ceros(){

    //variables de la nueva matriz con los ceros
    ancho1 = _ancho + cerosPorFila;
    alto1 = _alto + cerosPorFila;
    int longitud = ancho1 * alto1;

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
    _pixels.clear();

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
                indice_mini_matriz++;

                // se verifica el recorrido en ancho
                if( (indice_mini_matriz % (tamano)) == 0 ){
                    indice_imagen +=  ancho1;
                    indice_mini_matriz = 0;
                }

            }

                suma = coeficiente * suma;
                if( suma <= 0){
                    suma=0;
                }else if(suma >= 255){
                    suma=255;
                }
                //guarda en la matrix y resetea
                _pixels.push_back(round(suma));
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

// Funcion que aplica el filtro laplaciano para detectat borde mas finos
void Imagen::filtroSegundoOrden(){

    //Se crea la mascara del laplaciano
    vector<int> h;
    h.push_back(-1); h.push_back(-1); h.push_back(-1);
    h.push_back(-1); h.push_back(8);  h.push_back(-1);
    h.push_back(-1); h.push_back(-1); h.push_back(-1);

    // se recorre la imagen aplicando el filtro de la mascara
    filtradoEspacial(3,h,1);

    // si el pixel es negativo se pone como cero dentro de la nueva imagen
    for(int i=0; i<_pixels.size(); i++){
         if(_pixels[i]<=0){
                _pixels[i]=0;
         }
    }
}

void Imagen::mejorarImagen()
{

    //string donde se guarda el nombre del archivo
    std::string nombreImagenEntrada;
    //El usuario digita el nombre del archivo
    cout << "Digite el nombre de la imagen a cargar" <<endl;
    cin >> nombreImagenEntrada;

    //se acomoda el nombre del archivo para buscarlo en el directorio
    std::string nombreImagen = "imagenes/In/" + nombreImagenEntrada;

    //Mascaras que se usaran para el tratamiento de las imagenes
    vector<int> mascara1;
    mascara1.push_back(0);  mascara1.push_back(1);  mascara1.push_back(0);
    mascara1.push_back(1);  mascara1.push_back(1);  mascara1.push_back(1);
    mascara1.push_back(0);  mascara1.push_back(1);  mascara1.push_back(0);

    vector<int> mascara2;
    mascara2.push_back(1); mascara2.push_back(1); mascara2.push_back(1);
    mascara2.push_back(1); mascara2.push_back(1); mascara2.push_back(1);
    mascara2.push_back(1); mascara2.push_back(1); mascara2.push_back(1);

    //indica el tamaño de las mascaras
    int tamano = 3;

    /* los siguientes condicionales describen, cada uno, el flujo para hacer
    el mejoramiento de cada una de las imagenes, existen una imagenes para
    las que solo es necesario aplicar los metodos para detectar bordes*/


        /*
        Si el nombre de la imagen digitada por el usuario es igual a "imagenes/In/RG1.pgm"
        entra a este if
        */
        if(nombreImagen == "imagenes/In/RG1.pgm")
        {
            //1- se realiza un filtrado ESpacial a la imagen de entrada, para lograr un suavizado de la misma
            lee(nombreImagen);
            filtradoEspacial(tamano,mascara1,0.5);
            escribe("imagenes/Out/RG/SalidaRG1.pgm");

            //2- se aumenta el contrarse de la salida del paso 1, utilizando el operador umbral
            lee("imagenes/Out/RG/SalidaRG1.pgm");
            operadorUmbral(150);
            escribe("imagenes/Out/RG/SalidaUmbralRG1.pgm");

            //3-se detectan los bordes de la imagen mediante el operador laplaciano
            lee("imagenes/Out/RG/SalidaUmbralRG1.pgm");
            filtroSegundoOrden();
            escribe("imagenes/Out/RG/salidaLaplacianoRG1.pgm");

            cout<<"Operaciones realizadas con éxito"<<endl;

        }


        /*
        Si el nombre de la imagen digitada por el usuario es igual a "imagenes/In/RG2.pgm"
        entra a este if
        */
        if(nombreImagen == "imagenes/In/RG2.pgm")
        {
            //se detectan los bordes de la imagen mediante el operador laplaciano
            lee(nombreImagen);
            filtroSegundoOrden();
            escribe("imagenes/Out/RG/salidaLaplacianoRG2.pgm");

            cout<<"Operaciones realizadas con éxito"<<endl;
        }
        /*
        Si el nombre de la imagen digitada por el usuario es igual a "imagenes/In/RG3.pgm"
        entra a este if
        */
        if(nombreImagen == "imagenes/In/RG3.pgm")
        {
            //se detectan los bordes de la imagen mediante el operador laplaciano
            lee(nombreImagen);
            filtroSegundoOrden();
            escribe("imagenes/Out/RG/salidaLaplacianoRG3.pgm");

            cout<<"Operaciones realizadas con éxito"<<endl;
        }
        /*
        Si el nombre de la imagen digitada por el usuario es igual a "imagenes/In/RG4.pgm"
        entra a este if
        */
        if(nombreImagen == "imagenes/In/RG4.pgm")
        {
            //1-humbral invertido (25,255)
            lee(nombreImagen);
            intervaloUmbralInvertido(25,255);//
            escribe("imagenes/Out/RG/SalidaRG4.pgm");

            //2-invertir imagen salida paso 1
            lee("imagenes/Out/RG/SalidaRG4.pgm");
            invertir_imagen();
            escribe("imagenes/Out/RG/SalidaInvertirRG4.pgm");

            //3-restar salida paso 2 con la imagen original
            lee("imagenes/Out/RG/SalidaInvertirRG4.pgm");
            Imagen restica(_ancho, _alto);
            restica.lee(nombreImagen);
            resta(restica,"imagenes/Out/RG/SalidaRestaRG4.pgm");

            //4-invertir salida paso 3
            lee("imagenes/Out/RG/SalidaRestaRG4.pgm");
            invertir_imagen();
            escribe("imagenes/Out/RG/SalidaRestaInvertidaRG4.pgm");

            //5-filtrado espacial salida paso 4
            lee("imagenes/Out/RG/SalidaRestaInvertidaRG4.pgm");
            filtradoEspacial(tamano,mascara1,0.5);
            escribe("imagenes/Out/RG/SalidaFiltradoEspacialRG4.pgm");

            //6-se detectan los bordes de la imagen mediante el operador laplaciano
            lee("imagenes/Out/RG/SalidaFiltradoEspacialRG4.pgm");
            filtroSegundoOrden();
            escribe("imagenes/Out/RG/laplacianoRG4.pgm");

            cout<<"Operaciones realizadas con éxito"<<endl;
        }

        /*
        Si el nombre de la imagen digitada por el usuario es igual a "imagenes/In/RLA1.pgm"
        entra a este if
        */
        if(nombreImagen == "imagenes/In/RLA1.pgm")
        {
            //1- se realiza un filtrado ESpacial a la imagen de entrada, para lograr un suavizado de la misma
            lee(nombreImagen);
            filtradoEspacial(tamano,mascara1,0.5);
            escribe("imagenes/Out/RLA/SalidaFiltadoEspacialRLA1.pgm");

            //2- se aumenta el contrarse de la salida del paso 1, utilizando el operador umbral
            lee("imagenes/Out/RLA/SalidaFiltadoEspacialRLA1.pgm");
            operadorUmbral(210);
            escribe("imagenes/Out/RLA/SalidaUmbralRLA1.pgm");

            //3-se detectan los bordes de la imagen mediante el operador laplaciano
            lee("imagenes/Out/RLA/SalidaUmbralRLA1.pgm");
            filtroSegundoOrden();
            escribe("imagenes/Out/RLA/laplacianoRLA1.pgm");

            cout<<"Operaciones realizadas con éxito"<<endl;

        }

        /*
        Si el nombre de la imagen digitada por el usuario es igual a "imagenes/In/RLA2.pgm"
        entra a este if
        */
        if(nombreImagen == "imagenes/In/RLA2.pgm")
        {
            //6-se detectan los bordes de la imagen mediante el operador laplaciano
            lee(nombreImagen);
            filtroSegundoOrden();
            escribe("imagenes/Out/RLA/laplacianoRLA2.pgm");

            cout<<"Operaciones realizadas con éxito"<<endl;
        }

        /*
        Si el nombre de la imagen digitada por el usuario es igual a "imagenes/In/RLA3.pgm"
        entra a este if
        */
         if(nombreImagen == "imagenes/In/RLA3.pgm")
        {
            //se detectan los bordes de la imagen mediante el operador laplaciano
            lee(nombreImagen);
            filtroSegundoOrden();
            escribe("imagenes/Out/RLA/laplacianoRLA3.pgm");

            cout<<"Operaciones realizadas con éxito"<<endl;
        }

        /*
        Si el nombre de la imagen digitada por el usuario es igual a "imagenes/In/RLA4.pgm"
        entra a este if
        */
         if(nombreImagen == "imagenes/In/RLA4.pgm")
        {
            //1- se realiza un filtrado ESpacial a la imagen de entrada, para lograr un suavizado de la misma
            lee(nombreImagen);
            filtradoEspacial(tamano,mascara2,0.11);
            escribe("imagenes/Out/RLA/SalidaFiltradoEspacialRLA4.pgm");

            //2- se aumenta el contrarse de la salida del paso 1, utilizando el operador umbral
            lee("imagenes/Out/RLA/SalidaFiltradoEspacialRLA4.pgm");
            operadorUmbral(100);
            escribe("imagenes/Out/RLA/SalidaUmbralRLA4.pgm");

            //3-se detectan los bordes de la imagen mediante el operador laplaciano
            lee("imagenes/Out/RLA/SalidaUmbralRLA4.pgm");
            filtroSegundoOrden();
            escribe("imagenes/Out/RLA/laplacianoRLA4.pgm");

            cout<<"Operaciones realizadas con éxito"<<endl;

        }
        /*
            Si no encuentra ninguna coincidencia en los nombres
        */
        else
            {
                cout<<"No se han podido ralizar las acciones, archivo no encontrado"<<endl;
            }
}
