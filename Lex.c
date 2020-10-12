/**********************************
//
//	Lex.c
//	Arranges input text in alphabetical order
//
***********************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#define MAX_LEN 160

int main(int argc, char * argv[]){
	FILE *in, *out;
	int nlines = 0;
	int count = 0;

	char line[MAX_LEN];

	if (argc != 3){
		printf("Usage: %s <input file> <outfile> \n", argv[0]);
		exit(1);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if (in == NULL){
		printf(" Unable to open file %s for reading \n", argv[1]);
		exit(1);
	}
	if (out == NULL){
		printf(" Unable to open file %s for reading \n", argv[2]);
		exit(1);
	}

	while(fgets(line, MAX_LEN, in) != NULL){
		nlines++;
	}

	char* array[nlines];
	rewind(in);

	for (int i = 0; i < nlines; i++){
		array[i] = malloc ((MAX_LEN)* sizeof(char));
	}

	while(fgets(line, sizeof(line), in) != NULL){
		strcpy(array[count], line);
		count++;
	}

	List L = newList();

	if (count > 0){
		append(L, 0);
	}

	for (int i = 1; i < nlines; i++){
		moveFront(L);

		while(index(L) >= 0){
			if (strcmp(array[get(L)], array[i]) > 0){
				insertBefore(L, i);
				break;
			}
			moveNext(L);
		}
		if(index(L) < 0){
			append(L, i);
		}
	}

	moveFront(L);

	while(index(L) >= 0){
		fprintf(out, "%s", array[get(L)]);
		moveNext(L);
	}

	fclose(in);
	fclose(out);

	for (int i = 0; i < count; i++){
		free(array[i]);
	}
	freeList(&L);
	return (0);
}
