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
    unsigned char *dataImg;
    int imgWidth, imgHeight;

    if( (argc > 2) && ((dataImg = load_pixmap(argv[1], &imgWidth, &imgHeight)) != NULL) && argv[2] != NULL){
        printf("IMG Width : %d\n",imgWidth);
        printf("IMG Height : %d\n",imgHeight);

        FILE *file;
        unsigned char *buffer;
        unsigned long imgLen;

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

        printf("FileToHide size : %ld\n", imgLen);



        return 1;
    }
    else{
        printf("Something went wrong with the arguments\n");
    }
    return 1;
}
