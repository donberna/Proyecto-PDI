/*
    Luis Ovidio GOnzalez Codigo: 201154010
    Miguel Angel Bernal Codigo: 201153852
    Aslhey Ramirez Codigo:1153765
*/
#include <iostream>
#include <getopt.h>
#include "Imagen.h"
#include "Mejoramiento.h"
#include "Medida.h"

using namespace std;

char usage[] =
"\n"
"  uso: Imagen [opcion] <archivo .pgm>\n"
"\n"
"  Opciones:\n"
"\n"
"      -n <file.pgm> : Analiza una imagen sin ruido\n"
"      -r <file.pgm> : Analiza una imagen con ruido\n"
"\n"
"      --help     : Muestra esta pantalla\n"
"\n";



int main( int argc, char *argv[])
{
    int option;
    Imagen input(0,0);

    int option_index = 0;

    //para el menu de opciones
    static struct option long_options[] = {
            {"normal",             1, 0, 'n'},
            {"ruido",             1, 0, 'r'},
            {"help",              0, 0, 'H'},
            {0,                   0, 0,  0 }
    };

	option = getopt_long( argc, argv, "r:a:e:b:p:qcthd:l:m:n:i:f:k:x::Xysw:0HKC:M:DP:zV1",
                        long_options, &option_index );

		switch( option )
		{

			case ':' :

				printf("\"%s --help\" para ayuda.\n", argv[0]);
				return( 1 );

			case '?' :

				printf("\"%s --help\" para ayuda.\n", argv[0]);
				return( 1 );

            case 'H' :
                printf("%s", usage);
                return( 1 );

            case 'r' :
                cout<<"Imagen con ruido: "<<argv[2]<<endl;

                if (1 == input.lee(argv[2]))
                {
                    Imagen output;
                    output = Mejoramiento::ruido(input);
                    char salida[] = "output.pgm";

                    output.escribe(salida);
                    Medida::test(&output);
                }

                return( 1 );

            case 'n' :
                cout<<"Imagen sin ruido: "<<argv[2]<<endl;

                if (1 == input.lee(argv[2]))
                {
                    Imagen output;
                    //umbral // 150 // 210
                    output = Mejoramiento::normal(input);
                    char salida[] = "output.pgm";

                    output.escribe(salida);
                    Medida::test(&output);

                }
                return ( 1 );
        }
    return 0;
}
