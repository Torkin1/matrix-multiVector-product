/*
    A linked list implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll.h"
#include "logger/logger.h"

Node *newNode (void *value){

	Node *head = calloc(1, sizeof(Node));
	head -> value = value;
	head -> next = NULL;

	return head;

}

/*
void printLL(Node *current, char *format){

    char *buffer = calloc(strlen(format) + 3, sizeof(char));
	while (current != NULL){
		strcpy(buffer, format);
		strcat(buffer, ", ");
		printf(buffer, *(current -> value));
		current = current -> next;
	}
	printf("\n");
	free(buffer);
}
*/
void destroyLL (Node *current){

	if (current == NULL) return;
	else {

		destroyLL (current -> next);
		free (current);

	}

}

void appendLL(Node **currentAddr, void *value){

	if (*currentAddr == NULL){

		*currentAddr = newNode(value);
	}

	else {
		Node *current = *currentAddr;
		if (current -> next == NULL) {

			Node *newNode = calloc(1, sizeof(Node));
			current -> next = newNode;
			newNode -> next = NULL;
			newNode -> value = value;
		}

		else appendLL (&(current -> next), value);
	}
}

int getLL(Node *head, int index, Node **node){

	Node *current = head;
	if (index < 0 || index >= lenLL(current))
	{
		logMsg(E, "getLL: index %d out of range\n", index);
		return 1;
	}
	
	// travels list until it encounters node with given index
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}
	*node = current;

	return 0;
}

int popLL(Node **headAddr, int index, void **destination){

	Node *previous = NULL;
	if (*headAddr != NULL){
        Node *current = *headAddr;
        if (index >= 0 && index < lenLL(current)){

            // travels list until it encounters node with given index
            for (int i = 0; i < index; i ++){
            previous = current;
            current = current -> next;
            }

            // Pops node
            if (destination != NULL){
                *destination = current -> value;
            }
			if (previous != NULL){
                previous -> next = current -> next;
			} else {
                *headAddr = current -> next;
			}
			free(current);

        } else {
            logMsg(E, "pop: index %d out of range\n", index);
            return 1;
        }
	} else {
        logMsg(E, "pop: list is empty\n");
        return 1;
	}
	return 0;
}

int lenLL(Node *current){
	int count = 0;

	while (current != NULL){

		count ++;
		current = current -> next;
	}

	return count;
}
