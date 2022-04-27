#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include"todolist.h"
#pragma warning(disable:4996)

TodoListRef TodoListCreate() {
	TodoListRef list = (TodoListRef)malloc(sizeof(struct _TDTodoList));
	list->size = 0;
	list->capacity = 100;
	list->list = (TodoItemRef *)malloc(sizeof(TodoItemRef) * list->capacity);
	return list;
}

void TodoListRelase(TodoListRef list) {
	unsigned int i = 0;
	while (i < list->size) {
		TodoItemRef currentItem = (list->list)[i];
		TodoItemRelease(currentItem);
		i++;
	}
	free(list);
}

unsigned int TodoListGetSize(TodoListRef list) {
	return list->size;
}

TodoItemRef TodoListGetItemAtIndex(TodoListRef list, unsigned int index) {
	return (list->list)[index];
}

TodoItemRef TodoListAddNewItem(TodoListRef list, const char *name) {
	if (TodoListGetSize(list) == list->capacity) {
		return NULL;
	}
	TodoItemRef newItem = TodoItemCreate(name);
	(list->list)[TodoListGetSize(list)] = newItem;
	list->size += 1;
	return newItem;
}

void TodoListAppendItem(TodoListRef list, TodoItemRef item) {
	if (list->size == list->capacity) return;
	(list->list)[list->size] = item;
	list->size += 1;
}

void TodoListRemoveItemAtIndex(TodoListRef list, unsigned int index) {
	if (index >= list->size || list->size == 0) return;
	TodoItemRef toDel = (list->list)[index];
	unsigned int i = index;
	while (i < (list->size) - 1) {
		(list->list)[i] = (list->list)[i + 1];
		i++;
	}
	TodoItemRelease(toDel);
	list->size -= 1;
}

TodoItemRef TodoItemCreate(const char* name) {
	TodoItemRef newItem = (TodoItemRef)malloc(sizeof(struct _TDTodoItem));
	newItem->name = (char*)calloc(sizeof(char), strlen(name) + 1);
	strcpy(newItem->name, name);
	newItem->completed = false;
	return newItem;
}


void TodoItemComplete(TodoItemRef item) {
	item->completed = true;
}


void TodoItemRename(TodoItemRef item, const char *name) {
	if (strlen(item->name) < strlen(name)) {
		item->name = (char*)realloc(item->name, sizeof(char)*(strlen(name) + 1));
	}
	memset(item->name, 0, strlen(item->name) + 1);
	strcpy(item->name, name);
}

void TodoItemRelease(TodoItemRef item) {
	free(item->name);
	free(item);
}


void TodoListSaveIntoFile(TodoListRef list, FILE* file) {
	unsigned int numberOfItems = TodoListGetSize(list);
	unsigned int lengthOfTitle;
	unsigned int capacityOfList = list->capacity;
	TodoItemRef currentItem;
	fwrite(&capacityOfList, sizeof(unsigned int), 1, file);
	fwrite(&numberOfItems, sizeof(unsigned int), 1, file);
	unsigned int i = 0;
	while (i < numberOfItems) {
		currentItem = TodoListGetItemAtIndex(list, i);
		lengthOfTitle = strlen(currentItem->name);
		fwrite(&lengthOfTitle, sizeof(unsigned int), 1, file);
		fwrite(currentItem->name, sizeof(char), lengthOfTitle, file);
		fwrite(&(currentItem->completed), sizeof(bool), 1, file);
		i++;
	}
}

void TodoListLoadFromFile(TodoListRef list, FILE* file) {
	list->size = 0;
	unsigned int numberOfItems;
	unsigned int i = 0;
	TodoItemRef newItem;
	unsigned int lengthOfTitle;
	unsigned int completed;
	char* title;
	fread(&(list->capacity), sizeof(unsigned int), 1, file);
	fread(&numberOfItems, sizeof(unsigned int), 1, file);
	while (i < numberOfItems) {
		fread(&lengthOfTitle, sizeof(unsigned int), 1, file);
		title = (char*)calloc(sizeof(char), lengthOfTitle + 1);
		fread(title, sizeof(char), lengthOfTitle, file);
		fread(&completed, sizeof(bool), 1, file);
		newItem = TodoItemCreate(title);
		newItem->completed = completed;
		free(title);
		TodoListAppendItem(list, newItem);
		i++;
	}
}

TodoListRef TodoListCreateWithFile(FILE* file) {
	TodoListRef list = TodoListCreate();
	TodoListLoadFromFile(list, file);
	return list;
}


//  Implementtaion Loop Functions
void DisplayTodoList(TodoListRef list) {
	unsigned int i = 0;
	TodoItemRef currentItem;
	printf("\n\n======TODOLIST======\n");
	while (i < list->size) {
		currentItem = TodoListGetItemAtIndex(list, i);
		char done = (currentItem->completed) ? 'X' : ' ';
		printf("%02d: %s %c\n", i, currentItem->name, done);
		i++;
	}
}

void actionAdd(TodoListRef list) {
	char name[1024];
	memset(name, 0, 1024);
	printf("\n\nEnter new Todo's name: ");
	scanf(" %[^\n]s", name);
	TodoListAddNewItem(list, name);
}

void actionDone(TodoListRef list) {
	TodoItemRef selected;
	unsigned int i;
	bool well_selected = false;
	while (!well_selected) {
		printf("\n\nSelect Todo number");
		scanf("%u", &i);
		if (i < list->size) well_selected = true;
		selected = TodoListGetItemAtIndex(list, i);
		selected->completed = true;
		printf("Completed.\n\n");
	}
}


void actionDelete(TodoListRef list) {
	unsigned int i;
	bool well_selected = false;
	while (!well_selected) {
		printf("\n\nEnter the number: ");
		scanf("%u", &i);
		if (i < list->size) well_selected = true;
		TodoListRemoveItemAtIndex(list, i);
		printf("Deleted.\n\n");
	}
}

void actionRename(TodoListRef list) {

	unsigned int i;
	TodoItemRef selected;
	bool well_selected = false;
	char name[1024];
	memset(name, 0, 1024);
	while (!well_selected) {
		printf("\n\nEnter the number: ");
		scanf("%u", &i);
		if (i < list->size) well_selected = true;
		selected = TodoListGetItemAtIndex(list, i);
		printf("\nEnter new name:");
		scanf(" %[^\n]s", name);
		TodoItemRename(selected, name);
	}

}

#define FILENAME ("todo.dat")
void todolistmode() {
	TodoListRef list = TodoListCreate();
	FILE *file;
	file = fopen(FILENAME, "rb");
	if (file) {
		TodoListLoadFromFile(list, file);
		fclose(file);
	}
	bool keepLoop = true;
	while (keepLoop) {
		DisplayTodoList(list);
		printf("\n\nSelect Action: (a)dd, (r)ename, (d)one, (t)rash, (q)uit >");
		char s;
		scanf("%c", &s);
		switch (s) {
		case 'a':
			actionAdd(list);
			break;
		case 'r':
			actionRename(list);
			break;
		case 'd':
			actionDone(list);
			break;
		case 't':
			actionDelete(list);
			break;
		case 'q':
			keepLoop = false;
			break;
		}
	}
	file = fopen(FILENAME, "wb");
	TodoListSaveIntoFile(list, file);
	TodoListRelase(list);
}