#ifndef __SEQLIST_H__
#define __SEQLIST_H__

typedef unsigned int SeqListNode;
typedef struct _seqlist {
	int capacity;
	int length;
	SeqListNode *node;
}SeqList;

SeqList *SeqList_Create(int capacity);
void SeqList_Destroy(SeqList *list);
void SeqList_Clear(SeqList *list);
int SeqList_Length(SeqList *list);
int SeqList_Capacity(SeqList *list);
int SeqList_Insert(SeqList *list, SeqListNode *node, int pos);
SeqListNode *SeqList_Delete(SeqList *list, int pos);
SeqListNode *SeqList_Get(SeqList *list, int pos);

#endif //__SEQLIST_H__

