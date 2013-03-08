#include "list.h"
#include <stdlib.h>
#include <string.h>

TList *CreateList( void *Data, TList *Next )
{
	TList *Result = (TList*)malloc(sizeof(TList*));
	
	Result->Data = Data;
	Result->Next = Next;
	
	return Result;
}

TList *ListAppend( TList *List, void *Data )
{
	if( List == NULL )
		return CreateList( Data, NULL );
	
	TList *T = List;
	
	while ( T->Next != NULL )
		T = T->Next;
		
	T->Next = CreateList( Data, NULL );
	
	return List;
}

TList *ListPrepend( TList *List, void *Data )
{
	TList *Head = CreateList( Data, List );
	return Head;
}

TList *ListRemove( TList *From, void *Data )
{
	if( From == NULL )
		return NULL;
	
	if( From->Data == Data )
	{
		TList *Temp = From;
		From = From->Next;
		free(Temp);
		return From;
	}
	
	TList *T = From;
	
	while( T->Next != NULL && T->Next->Data != Data )
		T = T->Next;
	
	if( T->Next != NULL && T->Next->Data == Data )
	{
		TList *Temp = T->Next;
		T->Next = Temp->Next;
		free(Temp);  
	}
	
	return From; 
}

TList *ListRemoveAll( TList *From, void *Data )
{
	if( From == NULL )
		return NULL;
	
	while( From != NULL && From->Data == Data )
	{
		TList *Temp = From;
		From = From->Next;
		free(Temp);
	}
	
	TList *T = From;
	
	while( T->Next != NULL )
	{
		if( T->Next->Data == Data )
		{
			TList *Temp = T->Next;
			T->Next = Temp->Next;
			free(Temp);
		}
		
		if( T->Next != NULL )
			T = T->Next;
	}

	return From;
}

TList *ListLast( TList *List )
{
	if( List == NULL )
		return NULL;
	
	while( List->Next != NULL )
		List = List->Next;
	return List;
}

TList *ListCopy( TList *List )
{
	if( List == NULL )
		return NULL;
			
	TList *T, *Result;
	
	T = Result = CreateList(List->Data, NULL);
	List = List->Next;
	
	while( List != NULL )
	{
		T->Next = CreateList(List->Data, NULL);
		T = T->Next; 
		List = List->Next;
	}
	
	return Result;
}


TList *ListReverse( TList *List )
{
	if( List == NULL )
		return NULL;
	
	TList *Result = NULL;
	
	while( List != NULL )
	{
		TList *Temp = List;
		List = List->Next;
		
		Result = ListPrepend(Result, Temp->Data);
		free(Temp);
	}
	
	return Result;
}

TList *ListConcat( TList *List1, TList *List2 )
{
	TList *T = List1;
	
	if( T != NULL )
		while( T->Next != NULL )
			T = T->Next;
			
	while( List2 != NULL )
	{
		T = ListAppend(T, List2->Data );
		List2 = List2->Next;
	}
	
	return List1;
}

TList *ListNth( TList *List, int Num )
{
	int Size = ListSize(List);
	Num = Num > 0 ? (Num - 1) : (Size - Num);	
	
	if( Num < 0 || Num >= Size )
		return NULL;
	
	for( int i = 0; i < Num; i++ )
		List = List->Next;
	
	return List;
}

TList *ListFind( TList *List, void *Data )
{	
	while( List != NULL && List->Data != Data )
		List = List->Next;

	if( List != NULL && List->Data == Data )
		return List;
	else
		return NULL;
}

TList *ListFindCustom( TList * List, void *Data, int (*compare)(void *, void*) )
{	
	while( List != NULL && compare(List->Data, Data) != 0 )
		List = List->Next;
	
	if( List != NULL && compare(List->Data, Data) == 0 )
		return List;
	else
		return NULL;
}

TList *ListFindPosition( TList *List, TList *Template )
{
	while( List != NULL && List != Template )
		List = List->Next;
	
	if( List != NULL && List == Template )
		return List;
	else
		return NULL;
}

void *ListRemoveNext( TList *After )
{
	if( After == NULL || After->Next == NULL )
		return NULL;
		
	TList *Temp = After->Next;
	After->Next = Temp->Next;
	
	void *Data = Temp->Data;
	free(Temp);
	
	return Data;
}

void ListInsert( TList *After, void *Data )
{
	if( After == NULL )
		return NULL;
		
	TList *Temp = After->Next;
	After->Next = CreateList(Data, Temp);
}

void ListDestroy( TList *List )
{
	while( List != NULL )
	{
		TList *Temp = List;
		List = List->Next;
		free(Temp);
	}
}
 
void ListForeach( TList *List, void (*func)(void *, void *), void *UserData )
{
	while( List != NULL )
	{
		func( List->Data, UserData);
		List = List->Next;
	}
} 
 
unsigned ListSize( TList *List )
{
	int size = 0;
	
	while( List != NULL )
	{
		size++;
		List = List->Next;
	}
	
	return size;
}
