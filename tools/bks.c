#include <stdio.h>
#include <stdlib.h>

/*
colmap
tilemap
output
*/

unsigned int fileSize(FILE* fp)
{
	if(fp) {
		unsigned int pos = ftell(fp);
		fseek(fp, 0, SEEK_END);
		unsigned int sz = ftell(fp);
		fseek(fp, pos, SEEK_SET);
		return sz;
	}
	return 0;
}

int main(int argc, char** argv)
{

	if(argc < 4) {
		printf("Not enough arguments provided!\n");
		return 0;
	}

	FILE* in;
	if((in=(fopen(argv[1], "rb")))==NULL) {
		printf("Collision map %s couldn't be opened\n", argv[1]);
		return 0;
	}
	FILE* out;
	if((out=fopen(argv[3], "wb"))==NULL) {
		printf("Output %s couldn't be created\n", argv[3]);
		fclose(in);
		return 0;
	}
	unsigned int sz = fileSize(in);
	void* tmp = malloc(sz);
	if(tmp==NULL) {
		fclose(in);
		fclose(out);
	}
	fread(tmp, 1, sz, in);
	fwrite(tmp, 1, sz, out);
	free(tmp);
	fclose(in);

	in = fopen(argv[2], "rb");
	sz = fileSize(in);
	tmp = malloc(sz);
	if(tmp==NULL) {
		fclose(in);
		fclose(out);
	}
	fread(tmp, 1, sz, in);
	fwrite(tmp, 1, sz, out);
	free(tmp);
	fclose(in);
	fclose(out);
	return 0;

}
