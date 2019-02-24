#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
char signature[2];
typedef struct image{
	struct header {

		int fileSize;
		int reserved;
		int dataOffset;
		int size;
		int width;
		int height;
		short planes;
		short bitsPerPixel;
		int Compression;
		int ImageSize;
		int XpixelsPerM;
		int YpixelsPerM;
		int colorsUsed;
		int importantColors;
	} info;
} image_header;
void printheader(image_header *img){
	printf("Signature %c%c\n",signature[0],signature[1]);
	printf("fileSize %d\n",img->info.fileSize);
	printf("Reserved %d\n",img->info.reserved);
	printf("dataOffset %d\n",img->info.dataOffset);
	printf("size %d\n",img->info.size);
	printf("width %d\n",img->info.width);
	printf("height %d\n", img->info.height);
	printf("planes %d\n", img->info.planes);
	printf("bitsPerPixel %d\n", img->info.bitsPerPixel);
	printf("Compression %d\n", img->info.Compression);
	
}

int main(int argc, char *argv[]){
	
	if(argc > 1){
		char *image = argv[1];
		FILE *fptr;
		fptr = fopen(image,"r");
		if(fptr){
			int i =0;
			char buf[54];
			image_header *img;
			for(i=0; i < 54;i++){
				buf[i] = fgetc(fptr);
			}
			signature[0] = buf[0];
			signature[1] = buf[1];
			img =(image_header *)&(buf[2]);
			printheader(img);
		}
		printf("------\n%s\n-----\n",argv[1]);
	}else{
		printf("Missing Arguments\n");
	}
	return 0;
}
