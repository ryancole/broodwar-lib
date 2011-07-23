#include "GlobalClass.h"

void GlobalClass::debugprint(char *output) {
	FILE * outfile;
	outfile = fopen("logger.txt", "at");
	fprintf(outfile, "%s", output);
	fclose(outfile);
}

GlobalClass *global = new GlobalClass;