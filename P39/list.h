#define TList struct List

struct List
{
	void *Data;
	struct List *Next;
};

TList *ListAppend( TList *List, void *Data );
TList *ListPrepend( TList *List, void *Data );

TList *ListRemove( TList *From, void *Data );
TList *ListRemoveAll( TList *From, void *Data );

TList *ListLast( TList *List );
TList *ListCopy( TList *List );
TList *ListReverse( TList *List );
TList *ListConcat( TList *List1, TList *List2 );

TList *ListNth( TList *List, int Num );
TList *ListFind( TList *List, void *Data );
TList *ListFindCustom( TList *List, void *Data, int (*compare)(void *, void*) );
TList *ListFindPosition( TList *List, TList *Template ); 

void *ListRemoveNext( TList *After );
void ListInsert( TList *After, void *Data );
void ListDestroy( TList *List );
void ListForeach( TList *List, void (*func)(void *, void *), void *UserData );
unsigned ListSize( TList *List );

