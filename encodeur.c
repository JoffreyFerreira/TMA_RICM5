#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pixmap_io.c"

int main(int argc, char **argv){
    unsigned char *dataImg;
    char *fileName;
    int imgWidth, imgHeight;
    int fileNameLength;
    if( (argc > 3) && ((dataImg = load_pixmap(argv[1], &imgWidth, &imgHeight)) != NULL) && argv[2] != NULL && argv[3] != NULL){
        printf("IMG Width : %d\n",imgWidth);
        printf("IMG Height : %d\n",imgHeight);
        fileName = argv[3];
        fileNameLength = strlen(fileName);
        FILE *file;
        unsigned char *buffer;
        unsigned int imgLen;

        file = fopen(argv[2],"rb");
        if(!file){
            printf("Could not read file to hide\n");
            return 1;
        }
        fseek(file, 0, SEEK_END);
        imgLen=ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer=(unsigned char *)malloc(imgLen);
        if (!buffer)
        {
            fprintf(stderr, "Memory error!\n");
            fclose(file);
            return 1;
        }

        fread(buffer,imgLen,sizeof(unsigned char),file);
        fclose(file);

        printf("FileToHide size : %d\n", imgLen);
        printf("Longueur chaine : %ld\n", strlen(fileName));

        int i = 0;
        int tmp;
        //on met la taille de l'image
        int tailleImg = imgLen;
        for(;i<16;i++){
            tmp = (tailleImg & 0xC0000000) >> 30;
            dataImg[i] = (dataImg[i] & 0xFC) + tmp;
            tailleImg = tailleImg << 2;
        }

        //on met le nom du fichier
        int indiceParcoursNomFichier = 0;
        unsigned char tmp2;
        int indiceParcoursImgData = 16;
        for(;indiceParcoursNomFichier < fileNameLength; indiceParcoursNomFichier++){
            tmp2 = fileName[indiceParcoursNomFichier];
            for(int j=0; j<4;j++){
                dataImg[indiceParcoursImgData] = (dataImg[indiceParcoursImgData] & 0xFC) + (tmp2 >> 6);
                indiceParcoursImgData++;
                tmp2 = (tmp2 << 2);
            }
        }
        for(;indiceParcoursImgData<144;indiceParcoursImgData++){
            dataImg[indiceParcoursImgData] = (dataImg[indiceParcoursImgData] & 0xFC);
        }

        //on encode l'image
        indiceParcoursImgData = 144;
        int indiceParcoursImgAEncoder = 0;
        for(; indiceParcoursImgAEncoder < imgLen; indiceParcoursImgAEncoder++){
            tmp2 = buffer[indiceParcoursImgAEncoder];
            for(int i=0;i<4;i++){
                dataImg[indiceParcoursImgData] = (dataImg[indiceParcoursImgData] & 0xFC) + (tmp2 >> 6);
                indiceParcoursImgData++;
                tmp2 = (tmp2 << 2);
            }
        }


        store_pixmap("output.pgm",dataImg,imgWidth,imgHeight);

        return 1;
    }
    else{
        printf("Something went wrong with the arguments\n");
    }
    return 1;
}
