#include <stdio.h>
#include <stdlib.h>

#include "pixmap_io.c"

int pow2(int n){
	int res = 1;
	for (int i = 0; i < n; ++i){
		res*=2;
	}
	return res;
}

int main(int argc, char **argv){
	unsigned char *data;
	int width, height;

	if( (argc > 1) && ((data = load_pixmap(argv[1], &width, &height)) != NULL) ){
		// Lire taille,
		// Lire nom
		// Sauter 3 octets NUL
		// Récup flux
		
		printf("width : %d height : %d\n", width, height);
		
		unsigned char tailleBinary[4];
		char nameBinary[30];
		int taille = 0;
		int base = 31;
		for(int i=0 ; i<16 ; i+=4){
			tailleBinary[i/4] = ((data[i]&0x3)<<6)+((data[i+1]&0x3)<<4)+((data[i+2]&0x3)<<2)+(data[i+3]&0x3);
			taille += ((tailleBinary[i/4]&0x80)>>7)*pow2(base) + ((tailleBinary[i/4]&0x40)>>6)*pow2(base-1) + ((tailleBinary[i/4]&0x20)>>5)*pow2(base-2) + ((tailleBinary[i/4]&0x10)>>4)*pow2(base-3) +((tailleBinary[i/4]&0x8)>>3)*pow2(base-4) +((tailleBinary[i/4]&0x4)>>2)*pow2(base-5) + ((tailleBinary[i/4]&0x2)>>1)*pow2(base-6)+ (tailleBinary[i/4]&0x1)*pow2(base-7); 
			base -=8;
		}

		printf("%d\n", taille);

		int indice = 16;
		int indiceTabName = 0;
		unsigned char charData;
		while(indice<136){

			
			charData = ((data[indice]&0x3)<<6)+((data[indice+1]&0x3)<<4)+((data[indice+2]&0x3)<<2)+(data[indice+3]&0x3);			
			//recup nom
			
			printf("%c\n", charData);

			if(charData==NULL){
				printf("null trouvé à l'indice : %d\n", indice);
				indice += 12;
				break;
			}
			nameBinary[indiceTabName] = charData;
			indice += 4;
			indiceTabName++;
		}
		printf("%s\n", nameBinary);

		unsigned char flow[height*width/4];
		for (int i = indice; i < indice+taille*4; i+=4){
			flow[i/4]=((data[i]&0x3)<<6)+((data[i+1]&0x3)<<4)+((data[i+2]&0x3)<<2)+(data[i+3]&0x3);
		}

		store_pixmap(nameBinary, flow, 350, 233);

		return 1;

	} else {
		printf("Erreur chargement pgm\n");
		return 0;	
	}
}