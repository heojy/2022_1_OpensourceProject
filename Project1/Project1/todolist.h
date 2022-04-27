#ifndef TODOLIST_H_
#define TODOLIST_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Todo
 *
 * functions
 * – print list
 * – create new task
 * – edit task
 *   – make completed
 *   – rename
 *   – delete
 * – save
 * – load
 */

 /*  Defile Data Types   */

 //  I'd like to use 'false', 'true'.
 //  define my own boolean type.
typedef unsigned int bool;
#define true ((bool)(1))
#define false ((bool)(0))

//  types of data model
//  TodoItem
struct _TDTodoItem {
	char *name;
	bool completed;
};

typedef struct _TDTodoItem* TodoItemRef;

//  TodoList
struct _TDTodoList {
	unsigned int size;
	unsigned int capacity;
	TodoItemRef* list;
};

typedef struct _TDTodoList* TodoListRef;

/*  API Function  */

//  TodoList API Functions
TodoListRef TodoListCreate();
void TodoListRelease(TodoListRef list);
unsigned int TodoListGetSize(TodoListRef list);
TodoItemRef TodoListGetItemAtIndex(TodoListRef list, unsigned int index);
TodoItemRef TodoListAddNewItem(TodoListRef list, const char *name);
void TodoListAppendItem(TodoListRef list, TodoItemRef item);
void TodoListRemoveItemAtIndex(TodoListRef list, unsigned int index);
void TodoListSaveIntoFile(TodoListRef list, FILE* file);
void TodoListLoadFromFile(TodoListRef list, FILE* file);
TodoListRef TodoListCreateWithFile(FILE* file);


//  TodoItem API Functions
TodoItemRef TodoItemCreate(const char* name);
void TodoItemRelease(TodoItemRef item);
void TodoItemComplete(TodoItemRef item);
void TodoItemRename(TodoItemRef item, const char *name);

//  Action Loop Functions
void DisplayTodoList(TodoListRef list);
void actionAdd(TodoListRef list);
void actionDone(TodoListRef list);
void actionDelete(TodoListRef list);
void actionRename(TodoListRef list);
void todolistmode();

#endif