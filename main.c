#include "PA 2.h"

int main(int argc, char argv[])
{
	int option = 0;
	FILE *infile = NULL;
	FILE *outfile = NULL;
	Node *pHead = NULL;

	infile = fopen("musicPlayList.csv", "r");

	while (option != 11)
	{
		option = chooseOption();
		command(infile, outfile, &pHead, option);
	}

	fclose(infile);

	return 0;
}