#include <stdio.h>
#include <stdlib.h>

typedef struct {
	float lat;
	float lon;
	short alt;
	char name[5];
	char misc;
} Field;

int main()
{
	FILE *ifile = fopen("tracks.dat", "rb");
	Field f_struct;

	while (fread(&f_struct, sizeof(Field), 1, ifile) != 0) {
		printf("Lat: %.1f", f_struct.lat);
		printf(" lon: %.1f", f_struct.lon);
		printf(" alt: %d", f_struct.alt);
		printf(" name: ");
		for (int i = 0; i < 5; i++) {
			printf("%c", f_struct.name[i]);
		}
		switch(f_struct.misc & 3){
			case 0:
				printf(" ID: unknown");
				break;
			case 1:
				printf(" ID: friend");
				break;
			case 2:
				printf(" ID: foe");
				break;
			case 3:
				printf(" ID: neutral");
				break;
		}
		switch((f_struct.misc & 12) >> 2){
			case 0:
				printf(" Cat: ship");
				break;
			case 1:
				printf(" Cat: ground");
				break;
			case 2:
				printf(" Cat: airplane");
				break;
		}
		if(((f_struct.misc & 48) >> 4) == 1){
			printf(" Engaged");
		}
		printf("\n");
	}
	
	fclose(ifile);
	return 0;
}
