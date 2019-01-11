#include <stdio.h>
#include <stdlib.h>

#include "pixmap_io.c"

int main(int argc, char **argv){
	unsigned char *data;
	int width, height;

	if( (argc > 1) && ((data = load_pixmap(argv[1], &width, &height)) != NULL) ){
		// Lire taille,
		// Lire nom
		// Creer fichier
		// Mettre flux dans jpg

		unsigned char flow[height*width/4];
		printf("width : %d height : %d\n", width, height);
		for (int i = 0; i < 10; i+=4){
			flow[i/4]=(data[i]&0x3<<6)+(data[i+1]&0x3<<4)+(data[i+2]&0x3<<2)+(data[i]&0x3);
			printf("%X\n", flow[i/4]);
			printf("\n");
		}
	} else {
		printf("Erreur chargement pgm\n");
		return 0;	
	}
}