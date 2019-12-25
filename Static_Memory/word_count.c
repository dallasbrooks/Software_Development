#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAX_LENGTH 34
#define MAX_WORDS 750

//print length ascending (part A)
void Print_Length_Ascending(int word_frequency[]){  
	for(int a = 0; a < MAX_LENGTH; a++){
		if(word_frequency[a] != 0){
			printf("Count[%02d]=%02d;\n", a+1, word_frequency[a]);
		}
	}
} 	

//print frequency descending (part B)
void Print_Frequency_Descending(int word_frequency[]){
	int maxindex;
	int max = 0;
	for(int a = 0; a < MAX_LENGTH; a++){
		for(int b = 0; b < MAX_LENGTH; b++){
			if(word_frequency[b] > max){
				max = word_frequency[b];
				maxindex = b;
			}
		}
		if(max > 0){
			printf("Count[%02d]=%02d;\n", maxindex+1, max);
		}
		word_frequency[maxindex] = 0;
		maxindex = 0; 
		max = 0;
	}
}

//print frequency descending with unique words (part C)
void Print_Frequency_Descending_Words(int word_frequency[], char master_words[][MAX_WORDS][MAX_LENGTH]){ 
	int maxindex;
	int max = 0;
	for(int a = 0; a < MAX_LENGTH; a++){
		for(int b = 0; b < MAX_LENGTH; b++){
			if(word_frequency[b] > max){
				max = word_frequency[b];
				maxindex = b;
			}
		}
		if(max > 0){
			int c = 0;
			printf("Count[%02d]=%02d; ", maxindex+1, max);
			printf("(words: ");
			while(strlen(master_words[maxindex][c]) != 0){
				printf("\"%s\"", master_words[maxindex][c]);
				if(strlen(master_words[maxindex][c+2]) != 0){
					printf(", ");
				}
				else if(strlen(master_words[maxindex][c+1]) != 0){
					printf(" and ");
				}
				c++; 
			}
			printf(")\n");	
		}
		word_frequency[maxindex] = 0;
		maxindex = 0; 
		max = 0;
	}
}	

//print length ascending with words (part C special case)
void Print_Length_Ascending_Words(int word_frequency[], char master_words[][MAX_WORDS][MAX_LENGTH]){ 
	for(int a = 0; a < MAX_LENGTH; a++){
		if(word_frequency[a] != 0){
			int b = 0;
			printf("Count[%02d]=%02d; ", a+1, word_frequency[a]);
			printf("(words: ");
			while(strlen(master_words[a][b]) != 0){
				printf("\"%s\"", master_words[a][b]);
				if(strlen(master_words[a][b+2]) != 0){
					printf(", ");
				}
				else if(strlen(master_words[a][b+1]) != 0){
					printf(" and ");
				}
				b++; 
			}
			printf(")\n");	
		}
	}
}

//sort master_words alphanumerically
void Alphanumeric_Sort(char master_words[][MAX_WORDS][MAX_LENGTH]){ 
	char temp[MAX_LENGTH];
	int length;
	int current = 0;
	for(int a = 0; a < MAX_LENGTH; a++){
		length = 0;
		while(strlen(master_words[a][length]) != 0){
			length++;
		}
		for(int b = 0; b < length-1 ; b++){
			current = b;
			for(int c = b+1; c < length; c++){
				if(strcasecmp(master_words[a][current], master_words[a][c]) > 0){
					current = c;
				}
			}
			if(current != b){
				strncpy(temp, master_words[a][b], a+1);
				strncpy(master_words[a][b], master_words[a][current], a+1);
				strncpy(master_words[a][current], temp, a+1);
			}		
		}
	}
}	

int main(int argc, char *argv[]){ 
	FILE *fp;
	const char *current;
	char words[MAX_LENGTH*MAX_WORDS];
	int word_frequency[MAX_LENGTH] = {0};
	char master_words[MAX_LENGTH][MAX_WORDS][MAX_LENGTH];
	int sort = 0;
	int print_words = 0;
	int sort_print_words = 0;
	if(argc < 3){
		printf("Failure: not enough inputs\n");
		return -1; 
	}
	for(int a = 0; a < argc; a++){
			if(!strcmp(argv[a], "--infile")){
				fp = fopen(argv[a+1], "r");
				if(fp == NULL){
					printf("Failure: could not access file\n");
					return -1;
				}
		}
		if(!strcmp(argv[a], "--sort")){
			sort = 1;
		}
		if(!strcmp(argv[a], "--print-words")){
			print_words = 1;
		}
		sort_print_words = sort + print_words;
		if(sort_print_words == 2){
			sort = 0;
			print_words = 0;
		}
	}
	while(fgets(words, sizeof(words), fp)){
		int duplicate;
		int word_length;
		int b;
		if(strcasecmp(words, "\n") != 0){
			current = strtok(words, " .,;()\b\t\n");
			word_length = strlen(current);
			word_frequency[word_length-1] = word_frequency[word_length-1]+1;
			duplicate = 0;
			for(int a = 0; a < word_frequency[word_length-1]; a++){
				if(!strcasecmp(master_words[word_length-1][a], current)){ 
					duplicate = 1;
					break;
				}
			}
			if(duplicate == 0){
				b = 0;
				while(strlen(master_words[word_length-1][b]) != 0){
					b++;
				}
				strncpy(master_words[word_length-1][b], current, word_length);
				master_words[word_length-1][b][word_length] = '\0'; 
			}
			while(current){
				current = strtok(NULL, " .,;()\b\t\n");
				duplicate = 0;
				if(current){
					word_length = strlen(current);
					word_frequency[word_length-1] = word_frequency[word_length-1]+1;
					for(int a = 0; a < word_frequency[word_length-1]; a++){
						if(strcasecmp(master_words[word_length-1][a], current) == 0){
							duplicate = 1;
							break;
						}
					}
					if(!duplicate){
						b = 0;
						while(strlen(master_words[word_length-1][b]) != 0){
							b++;
						}
						strncpy(master_words[word_length-1][b], current, word_length);
						master_words[word_length-1][b][word_length] = '\0'; 
					}
				}
			}
		}
	}
	Alphanumeric_Sort(master_words);
	if(sort_print_words == 0){//part A
		Print_Length_Ascending(word_frequency);
	}
	else if(sort == 1){//part B
		Print_Frequency_Descending(word_frequency);
	}
	else if(sort_print_words == 2){//part C
		Print_Frequency_Descending_Words(word_frequency, master_words);
	}
	else if(print_words == 1){//part C special case
		Print_Length_Ascending_Words(word_frequency, master_words);
	}
	return 0;
}
//compile with gcc word_count.c
//run with ./a.out --infile <input_file> <--sort> <--print-words>