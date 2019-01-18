#include "PA 2.h"

void printMenu(void)
{
	printf("Menu\n");
	printf("(1) Load\n");
	printf("(2) Store\n");
	printf("(3) Display\n");
	printf("(4) Insert\n");
	printf("(5) Delete\n");
	printf("(6) Edit\n");
	printf("(7) Sort\n");
	printf("(8) Rate\n");
	printf("(9) Play\n");
	printf("(10) Shuffle\n");
	printf("(11) Exit\n\n");
}

Node* makeNode(Record data)
{
	Node *pMem = NULL;

	pMem = (Node *)malloc(sizeof(Node));
	pMem->data = data;
	pMem->pNext = NULL;
	pMem->pPrev = NULL;

	return pMem;
}

bool insertAtFront(Node **pHead, Record data)
{
	bool success = false;
	Node *pCur = NULL;

	pCur = makeNode(data);

	if (*pHead == NULL)
	{
		*pHead = pCur;
		success = true;
	}
	else if (*pHead != NULL)
	{
		pCur->pNext = *pHead;
		(*pHead)->pPrev = pCur;
		*pHead = pCur;
		success = true;
	}
	return success;
}

int convertInt(char *str)
{
	int num = atoi(str);

	return num;
}

int chooseOption(void)
{
	int option;

	do
	{
		system("cls");
		printMenu();
		printf("Please choose a menu option: ");
		scanf("%d", &option);
	} while ((option < 1) || (option > 11));

	return option;
}

void command(FILE* infile, FILE* outfile, Node **pHead, int option)
{
	bool success = false;
	switch (option)
	{
		case 1: // (1) load
			success = load(infile, pHead);
			break;
		case 2: // (2) store
			success = store(outfile, pHead);
			break;
		case 3: // (3) display
			display(pHead);
			break; 
		case 4: // (4) insert

			break;
		case 5: // (5) delete

			break;
		case 6: // (6) edit
			success = edit(pHead);
			break; 
		case 7: // (7) sort

			break; 
		case 8: // (8) rate
			success = rate(pHead);
			break;
		case 9: // (9) play
			play(pHead);
			break;
		case 10: // (10) shuffle

			break;
		case 11: // (11) exit
			success = store(outfile, pHead);
			break;
		default:
			printf("Something went wrong. :( Please try again.\n");
			break;
	}
	if (success && option != 11)
	{
		printf("Operation completed successfully!\n");
		system("pause");
	}
	else
	{
		printf("Something went wrong. :( Please try again.\n");
	}
}

bool load(FILE *infile, Node **pHead)
{
	bool success = false;
	Record songData;
	char temp[100];	

	while (!feof(infile))
	{
		fgets(temp, 100, infile);
		if (temp[0] == '"')
		{
			strcpy(songData.artist, strtok(temp, "\""));
			strcpy(songData.album, strtok(NULL, ","));
			strcpy(songData.title, strtok(NULL, ","));
			strcpy(songData.genre, strtok(NULL, ","));
			songData.length.minutes = atoi(strtok(NULL, ":"));
			songData.length.seconds = atoi(strtok(NULL, ","));
			songData.plays = atoi(strtok(NULL, ","));
			songData.rating = atoi(strtok(NULL, ","));
		}
		else
		{
			strcpy(songData.artist, strtok(temp, ","));
			strcpy(songData.album, strtok(NULL, ","));
			strcpy(songData.title, strtok(NULL, ","));
			strcpy(songData.genre, strtok(NULL, ","));
			songData.length.minutes = atoi(strtok(NULL, ":"));
			songData.length.seconds = atoi(strtok(NULL, ","));
			songData.plays = atoi(strtok(NULL, ","));
			songData.rating = atoi(strtok(NULL, ","));
		}
		success = insertAtFront(pHead, songData);
	}

	return success;
}

bool store(FILE *outfile, Node **pHead)
{
	bool success = false;
	Node *pCur = NULL;

	pCur = *pHead;

	outfile = fopen("musicPlayList.csv", "w");
	// "Swift, Taylor",1989,Shake it Off,Pop,3:35,12,3
	while (pCur != NULL)
	{
		fprintf("\"%s\",%s,%s,%s,%d:%d,%d,%d\n", pCur->data.artist, pCur->data.album, pCur->data.title, pCur->data.genre,
			pCur->data.length.minutes, pCur->data.length.seconds, pCur->data.plays, pCur->data.rating);
		success = true;
	}
	fclose(outfile);

	return success;
}

void display(Node **pHead)
{
	int option = 0;
	Node *pCur = NULL;
	char artist[50];

	pCur = *pHead;

	do
	{
		system("cls");
		printf("(1) Print all records.\n");
		printf("(2) Print all records that match an artist.\n\n");
		printf("Please pick an option: ");
		scanf("%d", &option);
	} while (option < 1 || option > 2);
	
	if (option == 1)
	{
		while (pCur != NULL)
		{
			printf("%s, %s, %s, %s, %d:%d, %d, %d\n", pCur->data.artist, pCur->data.album, pCur->data.title, pCur->data.genre, 
				pCur->data.length.minutes, pCur->data.length.seconds, pCur->data.plays, pCur->data.rating);
			
			pCur = pCur->pNext;
		}
	}
	else if (option == 2)
	{
		printf("\nPlease type in an artist \n(Note: artists with a first and last name will need to be inputted with 'LastName, FirstName' format): ");
		scanf(" %[^\n]s", &artist);

		while (pCur != NULL)
		{
			if (strcmp(pCur->data.artist, artist) == 0)
			{
				printf("%s, %s, %s, %s, %d:%d, %d, %d\n", pCur->data.artist, pCur->data.album, pCur->data.title, pCur->data.genre,
					pCur->data.length.minutes, pCur->data.length.seconds, pCur->data.plays, pCur->data.rating);
			}
			pCur = pCur->pNext;
		}
	}
	system("pause");
}

bool edit(Node **pHead)
{
	char song[50], edit[50];
	Node *pCur = NULL;
	int attribute, edit1, edit2;
	bool success = false;

	pCur = *pHead;
	
	system("cls");
	printf("Enter the name of the song you would like to edit: ");
	scanf(" %[^\n]s", &song);

	while (strcmp(pCur->data.title, song) != 0 && pCur != NULL)
	{
		pCur = pCur->pNext;
	}
	if (pCur != NULL)
	{
		do {
			system("cls");
			printf("Which attribute would you like to edit?\n");
			printf("(1) Artist\n");
			printf("(2) Album\n");
			printf("(3) Title\n");
			printf("(4) Genre\n");
			printf("(5) Length\n");
			printf("(6) Plays\n");
			printf("(7) Rating\n");
			scanf("%d", &attribute);
		} while (attribute < 1 || attribute > 8);

		switch (attribute)
		{
		case 1: // (1) artist
			printf("Enter the new artist name: ");
			scanf("%[^\n]s", &edit);
			strcpy(pCur->data.artist, edit);
			success = true;
			break;
		case 2: // (2) album
			printf("Enter the new album name: ");
			scanf("%[^\n]s", &edit);
			strcpy(pCur->data.album, edit);
			success = true;
			break;
		case 3: // (3) title
			printf("Enter the new title: ");
			scanf("%[^\n]s", &edit);
			strcpy(pCur->data.title, edit);
			success = true;
			break;
		case 4: // (4) genre
			printf("Enter the new genre name: ");
			scanf("%[^\n]s", &edit);
			strcpy(pCur->data.genre, edit);
			success = true;
			break;
		case 5: // (5) length
			printf("Enter the new minutes of song (will enter seconds next): ");
			scanf("%d", &edit1);
			printf("Enter the new seconds of song: ");
			scanf("%d", &edit2);
			pCur->data.length.minutes = edit;
			pCur->data.length.seconds = edit2;
			success = true;
			break;
		case 6: // (6) plays
			printf("Enter the new amount of plays: ");
			scanf("%d", &edit1);
			pCur->data.plays = edit;
			success = true;
			break;
		case 7: // (7) rating
			printf("Enter the new rating: ");
			scanf("%d", &edit1);
			pCur->data.rating = edit;
			success = true;
			break;
		}
	}
	return success;
}

bool rate(Node **pHead)
{
	bool success = false;
	char song[50];
	int edit;
	Node *pCur = NULL;

	pCur = *pHead;

	printf("Enter the name of the song you would like to rate: ");
	scanf(" %[^\n]s", &song);

	while (strcmp(pCur->data.title, song) != 0 && pCur != NULL)
	{
		pCur = pCur->pNext;
	}

	if (pCur != NULL)
	{
		do
		{
			system("cls");
			printf("Enter the new rating: ");
			scanf("%d", &edit);
		} while (edit < 1 || edit > 5);
		pCur->data.rating = edit;
		success = true;
	}

	return success;
}

void play(Node **pHead)
{
	Node *pCur = NULL;
	char song[50];

	pCur = *pHead;
	

	printf("Enter the name of the song you would like to play: ");
	scanf(" %[^\n]s", &song);

	while (strcmp(pCur->data.title, song) != 0 && pCur != NULL)
	{
		pCur = pCur->pNext;
	}

	while (pCur != NULL)
	{
		system("cls");
		printf("Now Playing\n");
		printf("%s - %s - %s", pCur->data.title, pCur->data.artist, pCur->data.album);
		Sleep(2000);

		pCur = pCur->pNext;
	}

}