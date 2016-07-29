#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


char *
basename(char *path)
{
    char *base = strrchr(path, '/');

    return base ? (1+base) : path;
}


int
main(argc, argv)
char **argv;
{
    float hta;
    float ehta;
    float a2c;
    float clearance;
    float rake;
    float deck2bolt;
    
    if ( argc < 4 || argc > 5 ) {
	fprintf(stderr, "usage: %s HTA A-C RAKE [MIN-CLEARANCE]\n",
			 basename(argv[0]));
	exit(1);
    }

    hta      = atof(argv[1]);
    a2c      = atof(argv[2]);
    rake     = atof(argv[3]);
    clearance= (argc == 5) ? atof(argv[4]) : hta;

    if ( a2c < 100 ) {
	fprintf(stderr, "%s: axle-to-crown is %.0f?\n",
			     basename(argv[0]), a2c);
	exit(1);
    }

    if ( clearance < 100 ) {
	fprintf(stderr, "%s: min rack clearance is %.0f?\n",
			    basename(argv[0]), clearance);
	exit(1);
    }

    hta = M_PI * ((90-hta) / 180);
    
    ehta = hta + asin(rake/a2c);

    deck2bolt = a2c * ( 1 - cos(ehta) ) + (clearance-a2c);

    printf("deck to brake bolt drop is %.0f\n", deck2bolt < 0 ? 0 : deck2bolt);
}
