#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[]) {
	char c;
	FILE *fi, *fo;

	if ( argc != 3 )
		printf("%s if of\n", argv[0]),exit(-1);
	
	if ( (fi=fopen(argv[1], "r")) == NULL) {
		printf("%s is not exist!\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	if ( (fo=fopen(argv[2], "w")) == NULL) {
		printf("open %s error!\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	
	while ( (c=fgetc(fi)) != EOF ) {
		fputc(c, fo);
		fseek(fi, 1, SEEK_CUR);
	}
	
	fclose(fi);
	fclose(fo);
	
	return 0;
}

