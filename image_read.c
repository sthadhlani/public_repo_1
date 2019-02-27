#include <stdio.h>
#include <stdlib.h>
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
	printf("importantColors %d\n", img->info.importantColors);	
	
}
char** allocate_memory(char **img, int width, int height){
	int i = 0;
	img = (char **)malloc(height*sizeof(char *));
	for(i =0; i<height;i++){
		img[i] = (char *)malloc(width*sizeof(char));
	}
	return img;
}
void printmenu(){
	printf("Please select one of the following options\n");
	printf("R : To rotate clockwise 90 degrees\n");
	printf("L : To rotate clockwise 90 degrees\n");
	printf("F : flip across X axis\n");
	printf("V : flip across Y axis\n");
	
}
int main(int argc, char *argv[]){
	if(argc > 1){
		char *image = argv[1];
		FILE *fptr;
		fptr = fopen(image,"r");
		if(fptr){
			int i =0,j=0;
			char buf[1024];
			char **rbg_red;
			char **rbg_blue;
			char **rbg_green;
			image_header *img;
			for(i=0; i < 54;i++){
				buf[i] = fgetc(fptr);
			}
			signature[0] = buf[0];
			signature[1] = buf[1];
			img =(image_header *)&(buf[2]);
			printheader(img);
			while(i<img->info.dataOffset){
				char temp = fgetc(fptr);
				i++;
			}
			rbg_red = allocate_memory(rbg_red, (*img).info.width, (*img).info.height);
			rbg_green = allocate_memory(rbg_green, (*img).info.width, (*img).info.height);
			rbg_blue = allocate_memory(rbg_blue, (*img).info.width, (*img).info.height);
			
			for(i=0; i < (img->info.height); i++){
				for(j=0;j < (img->info.width); j++){
					rbg_red[i][j] = fgetc(fptr);
					rbg_green[i][j] = fgetc(fptr);
					rbg_blue[i][j] = fgetc(fptr);
				}
			}
			printmenu();
			{
				char option=getc(stdin);
				char output[255];
				FILE *out;
				int temp;
				while(option!='Q' && option!='q'){
					switch(option){
						case 'R':
						case 'r':
							temp = img->info.width;
							img->info.width = img->info.height;
							img->info.height = temp;
							sprintf(output,"right_%s",image);
							printf("output file %s\n",output);
							out = fopen(output,"w");
							{
								int i = 0,j=0;
								for(i=0;i<img->info.dataOffset;i++){
									fputc(buf[i],out);
								}
								for(i=0;i<img->info.height;i++){
									for(j=0;j<img->info.width;j++){
										fputc(rbg_red[j][i],out);
										fputc(rbg_green[j][i],out);
										fputc(rbg_blue[j][i],out);
									}
								}
							}
							fclose(out);
							img->info.height = img->info.width;
							img->info.width = temp;
							break;
							
						case 'L':
						case 'l':
							temp = img->info.width;
							img->info.width = img->info.height;
							img->info.height = temp;
							sprintf(output,"left_%s",image);
							printf("output file %s\n",output);
							out = fopen(output,"w");
							{
								int i = 0,j=0;
								for(i=0;i<img->info.dataOffset;i++){
									fputc(buf[i],out);
								}
								for(i=0;i<img->info.height;i++){
									for(j=0;j<img->info.width;j++){
										fputc(rbg_red[img->info.width-j-1][i],out);
										fputc(rbg_green[img->info.width-j-1][i],out);
										fputc(rbg_blue[img->info.width-j-1][i],out);
									}
								}
							}
							fclose(out);
							img->info.height = img->info.width;
							img->info.width = temp;
							break;		
						case 'F':
						case 'f':
							sprintf(output,"flip_horz_%s",image);
							printf("output file %s\n",output);
							out = fopen(output,"w");
							{
								int i = 0,j=0;
								for(i=0;i<img->info.dataOffset;i++){
									fputc(buf[i],out);
								}
								for(i=0;i<img->info.height;i++){
									for(j=0;j<img->info.width;j++){
										fputc(rbg_red[i][img->info.width-j-1],out);
										fputc(rbg_green[i][img->info.width-j-1],out);
										fputc(rbg_blue[i][img->info.width-j-1],out);
									}
								}
							}
							fclose(out);
							break;
						case 'V':
						case 'v':
							sprintf(output,"flip_ver_%s",image);
							printf("output file %s\n",output);
							out = fopen(output,"w");
							{
								int i = 0,j=0;
								for(i=0;i<img->info.dataOffset;i++){
									fputc(buf[i],out);
								}
								for(i=0;i<img->info.height;i++){
									for(j=0;j<img->info.width;j++){
										fputc(rbg_red[img->info.height-i-1][j],out);
										fputc(rbg_green[img->info.height-i-1][j],out);
										fputc(rbg_blue[img->info.height-i-1][j],out);
									}
								}
							}
							fclose(out);
							break;
							break;
						default:
							printf("Invalid Options\n");
					}
					printmenu();
					getc(stdin);
					option=getc(stdin);
				}
			}
			
		}
		printf("------\n%s\n-----\n",argv[1]);
	}else{
		printf("Missing Arguments\n");
	}
	return 0;
}
