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
"  usage: Imagen [option] <.pgm file>\n"
"\n"
"  Options:\n"
"\n"
"      -a <amode> : force attack mode (1/WEP, 2/WPA-PSK)\n"
"      -e <essid> : target selection: network identifier\n"
"      -b <bssid> : target selection: access point's MAC\n"
"      -p <nbcpu> : # of CPU to use  (default: all CPUs)\n"
"      -q         : enable quiet mode (no status output)\n"
"\n"
"      --help     : Displays this usage screen\n"
"\n";



int main( int argc, char *argv[])
{
    int option;
    Imagen input(0,0);
    //while( 1 )
	//{

        int option_index = 0;

        static struct option long_options[] = {
            {"normal",             1, 0, 'n'},
            {"ruido",             1, 0, 'r'},
            {"RLA",           0, 0, 'l'},
            {"RG",           0, 0, 'g'},
            {"help",              0, 0, 'H'},
            {0,                   0, 0,  0 }
        };

		option = getopt_long( argc, argv, "r:a:e:b:p:qcthd:l:m:n:i:f:k:x::Xysw:0HKC:M:DP:zV1",
                        long_options, &option_index );

		switch( option )
		{

			case ':' :

				printf("\"%s --help\" for help.\n", argv[0]);
				return( 1 );

			case '?' :

				printf("\"%s --help\" for help.\n", argv[0]);
				return( 1 );

            case 'H' :
                printf("%s", usage);
                return( 1 );

            case 'r' :
                cout<<"Imagen con ruido: "<<argv[2]<<endl;

                if (1 == input.lee(argv[2]))
                {
                    Imagen output;
                    output = Mejoramiento::rg4(input);
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
                    //umbral //RG 150 //RLA 210
                    output = Mejoramiento::rg(input, 150);
                    char salida[] = "output.pgm";

                    output.escribe(salida);
                    Medida::test(&output);

                }
                return ( 1 );
            case 'l' :
                cout<<"RL";

                return( 1 );
        }

    //}



    //Entradas
    //input.lee("imagenes/In/RG/RG0.pgm");
    //input.lee("imagenes/In/RG1.pgm");

    //input.lee("imagenes/In/RG3.pgm");
    //input.lee("imagenes/In/RG4.pgm");


    //Imagen output = Mejoramiento::rg4(input);


    //Salidas

    //output.escribe("imagenes/Out/RG/RG2.pgm");
    //output.escribe("imagenes/Out/RG/RG3.pgm");
    //output.escribe("imagenes/Out/RG/RG4.pgm");



    return 0;
}
