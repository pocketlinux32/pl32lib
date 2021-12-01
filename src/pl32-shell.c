// pl32-shell.c: Interpreter module
#include <pl32-shell.h>

// Struct defining a variable-sized array of char arrays and the size of the array of arrays
struct pltokenizedstr {
	char** array;
	size_t size;
}

// Struct defining a function pointer and the name of said function
struct plfunctionptr {
	int (*function)(int, char**);
	char* name;
}

// Wrapper for ISO C function strtok() that copies the output of strtok() into a memory-allocated buffer
char* plSafeMallocStrtok(char* input, char* delimiter){
	char* returnPtr = NULL;
	char* tempPtr;

	if((tempPtr = strtok(input, delimiter)) != NULL){
		returnPtr = plSafeMalloc((strlen(tempPtr) + 1) * sizeof(char));
		strcpy(tempPtr, returnPtr);
	}

	return returnPtr;
}

// Parses a string into an array
pltokenizedstr_t plParser(char* input){
	pltokenizedstr_t returnStruct;
	returnStruct.size = 1;
	returnStruct.array = malloc(2 * sizeof(char*));

	char* tempPtr = plSafeMallocStrtok(input, " \n");
	returnStruct.array[0] = tempPtr;

	while((tempPtr = plSafeMallocStrtok(NULL, " \n")) != NULL){
		returnStruct.size++;
		char** tempArrPtr = realloc(returnStruct.array, returnStruct.size * sizeof(char*));

		if(!tempArrPtr){
			for(int i = 0; i < returnStruct.size; i++){
				free(returnStruct.array[i]);
			}

			free(returnStruct.array);
			returnStruct.array = NULL;
			returnStruct.size = ENOMEM;

			return returnStruct;
		}

		returnStruct.array = tempArrPtr;
		returnStruct.array[returnStruct.size - 1] = tempPtr;
	}

	return returnStruct;
}

// Creates an object containing pl
plfunctionptr_t plCreateFunctionPointer(int (*function)(int, char**), char* name){
	plfunctionptr_t returnStruct;
	returnStruct.function = function;
	returnStruct.name = name;

	return returnStruct;
}

int plShellAddFunction(plfunctionptr_t functionPtr){
	
}