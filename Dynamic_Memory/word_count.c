#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

//create a node for linked list 
struct node{
	char* word;
	int length;
	int frequency;
	struct node* next;
	struct node* down;
};

//free memory allocated for list
void Free_List(struct node** head){
	struct node* current = *head;
	struct node* current_next;
	struct node* temp_down;
	struct node* temp_down_next;
	while(current != NULL){
		current_next = current->next;
		temp_down = current;
		while(temp_down != NULL){
			temp_down_next = temp_down->down;
			free(temp_down->word);
			free(temp_down);
			temp_down = temp_down_next;
		}
		current = current_next;
	}
}

//insert a new node into the linked list
void Insert_Node(struct node** head, struct node* new){
	struct node* current = *head;
	if(current == NULL){//empty list
		*head = new;
		return;
	}
	if(new->length < current->length){//new word length is less than head
			new->next = *head;
			*head = new;
			return;
	}
	while(current != NULL){	
		if(new->length == current->length){//new word is same length as head
			current->frequency += 1;
			if(strcasecmp(new->word, current->word) != 0){
				while(current->down != NULL){
					current = current->down;
					if(strcasecmp(new->word, current->word) == 0){
						return;
					}
				}
				current->down = new;
			}
			return;
		}
		current = current->next;
	}
	current = *head;
	while(current->next != NULL){
		if(new->length < current->next->length){//new word length is less than current's next
			new->next = current->next;
			current->next = new;
			return;
		}
		current = current->next;
	}
	current->next = new;//new word length is greater than all lengths
}

//create a new node to be added to linked list
void Create_Node(struct node** head, char* word){
	struct node* new = malloc(sizeof(*new));
	int length = strlen(word) + 1;
	new->word = (char*)malloc(sizeof(*word));
	strncpy(new->word, word, length);
	new->length = length - 1;
	new->frequency = 1;
	new->next = NULL;
	new->down = NULL;
	Insert_Node(head, new);
}

//get all data from the file (the word, its length, and the frequency)
void Get_Words(struct node** head, char word_buffer[]){
	char* current = strtok(word_buffer, " .,;()\b\t\n"); 
	if(current){
		Create_Node(head, current);
	}
	while(current){
		current = strtok(NULL, " .,;()\b\t\n"); 		
		if(current){
			Create_Node(head, current);
		}
	}
}

//print length ascending (part A)
void Print_Length_Ascending(struct node* head){
	struct node* current = head;
	while(current != NULL){ 
		printf("Count[%02d]=%02d;\n", current->length, current->frequency);
		current = current->next;
	}
}

//print frequency descending (part B)
void Print_Frequency_Descending(struct node* head){
	struct node* current = head;
	struct node* temp = head;
	int frequency = current->frequency;
	while(temp != NULL){
		if(frequency < temp->frequency){
			frequency = temp->frequency;
		}
		temp = temp->next;
	}
	while(frequency > 0){
		current = head;
		while(current != NULL){
			if(frequency == current->frequency){
				printf("Count[%02d]=%02d;\n", current->length, current->frequency);
			}
			current = current->next;
		}
		frequency--;
	}
}

//print frequency descending with words (part C)
void Print_Frequency_Descending_Words(struct node* head){
	struct node* current = head;
	struct node* current_down = head;
	struct node* temp = head;
	int frequency = current->frequency;
	while(temp != NULL){
		if(frequency < temp->frequency){
			frequency = temp->frequency;
		}
		temp = temp->next;
	}
	while(frequency > 0){
		current = head;
		while(current != NULL){ 
			current_down = current;
			if(frequency == current->frequency){	
				printf("Count[%02d]=%02d; ", current->length, current->frequency);
				printf("(words: \"%s\"", current->word);
				while(current_down->down != NULL){
					current_down = current_down->down;
					if(current_down->down != NULL){
						printf(", ");
					}
					if(current_down->down == NULL){
						printf(" and ");
					}
					printf("\"%s\"", current_down->word);
				}
				printf(")\n");
			}
			current = current->next;
		}
		frequency--;
	}
}

//print length ascending with words (part C special case)
void Print_Length_Ascending_Words(struct node* head){
	struct node* current = head;
	struct node* current_down = current;
	while(current != NULL){ 
		current_down = current;
		printf("Count[%02d]=%02d; ", current->length, current->frequency);
		printf("(words: \"%s\"", current->word);
		while(current_down->down != NULL){
			current_down = current_down->down;
			if(current_down->down != NULL){
				printf(",");
			}
			if(current_down->down == NULL){
				printf(" and");
			}
			printf(" \"%s\"", current_down->word);
		}
		printf(")\n");
		current = current->next;
	}
}

int main(int argc, char *argv[]){
	struct node* head = NULL;
	FILE* file_name = NULL;
	int sort;
	int print_words;
	int sort_print_words;
	if(argc < 3){
		printf("Failure: not enough inputs\n");
		return -1; 
	}
	else{
		for(int a = 0; a < argc; a++){//find user inputs
			if(!strcmp(argv[a], "--infile")){
				file_name = fopen(argv[a+1], "r");
				if(file_name == NULL){//could not find file
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
		fseek(file_name, 0, SEEK_END);
		char word_buffer[ftell(file_name)+1];
		fseek(file_name, 0, SEEK_SET);	
		while(fgets(word_buffer, sizeof(word_buffer), file_name)){
			if(strlen(word_buffer) > 0){
				Get_Words(&head, word_buffer);
			}
		}
		if(sort_print_words == 0){//part A
			Print_Length_Ascending(head);
		}
		else if(sort == 1){//part B
			Print_Frequency_Descending(head);
		}
		else if(sort_print_words == 2){//part C
			Print_Frequency_Descending_Words(head);
		}
		else if(print_words == 1){//part C special case
			Print_Length_Ascending_Words(head);
		}
	}
	fclose(file_name);
	Free_List(&head);
	return 0;
}
//compile with gcc word_count.c
//run with ./a.out --infile <input_file> <--sort> <--print-words>