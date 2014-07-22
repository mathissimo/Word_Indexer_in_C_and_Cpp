/** Liste.c
 *
 *  @author  Horst Hansen, Mathias Münscher
 *  @version 1.0
 *  @date    7.4.2011
 */

#include <stdlib.h>
#include <stdio.h>

#include "Liste.h"

Liste* initListe(void* (*copy) (void*), void (*print) (void*), void (*remove) (void*))
{
	Liste* l = (Liste*) malloc(sizeof(Liste)) ;
	if (l == NULL)
	{
		printf("Kein Arbeitsspeicher mehr vorhanden!\n") ;
		printf("Das Programm wird beendet!\n") ;
		exit(EXIT_FAILURE) ;
	} ;
	l->_first = NULL ;
	l->_last  = NULL ;
	l->_count = malloc (sizeof(int));
	*(l->_count) = 0;
	l->_copy  = copy ;
	l->_print = print ;
	l->_remove = remove ;
	return l ;
}

/** Eine Liste ist genau dann leer, wenn die Komponente
    _first den Wert NULL hat!
 */
void* insertLex (Liste* l, void* pvalue, bool (*bigger) (void*, void*))
{
	Listenelement* neu = (Listenelement*) malloc(sizeof(Listenelement)) ;
	if (neu == NULL)
	{
		printf("\n\nKein Arbeitsspeicher mehr vorhanden!\n") ;
		printf("Das Programm wird beendet!\n") ;
		exit(EXIT_FAILURE) ;
	} ;
	// Neues Listenelement initialisieren
	neu->_pvalue = l->_copy(pvalue) ;
	
	// Vorgehendes Listenelement finden
	Listenelement* k = l->_first ;			// Bufferlement zum Suchen
	Listenelement* bufferOne=NULL;	// Buffer für Buffer, weil einfach verkette Liste
	while (k != NULL)
	{
		if (bigger(k->_pvalue, pvalue))
		{
			if (k == l->_first) l->_first= neu;
				else bufferOne->_next = neu;
			neu->_next = k;
			*(l->_count)=1+*(l->_count);
			return neu->_pvalue ; // Rückgabe Zeiger auf neues Datenfeld
		}
		bufferOne=k;
		k = k->_next ;
	} ;
   l->_remove (neu->_pvalue);
   free (neu);
   return append (l,pvalue); // Falls neues Element = letztes Element
}

void* append(Liste* l, void* pvalue)
{
	Listenelement* neu = (Listenelement*) malloc(sizeof(Listenelement)) ;
	if (neu == NULL)
	{
		printf("\n\nKein Arbeitsspeicher mehr vorhanden!\n") ;
		printf("Das Programm wird beendet!\n") ;
		exit(EXIT_FAILURE) ;
	} ;
	// Neues Listenelement initialisieren
	(*neu)._pvalue = l->_copy(pvalue) ;
	neu->_next  = NULL ;
	// _next vom letzten Listenelement aktualisieren
	if (l->_first == NULL)
	{	// Die Liste ist noch leer!!!

		l->_first = neu ;
		l->_last  = neu ;
		*(l->_count)=1+*(l->_count);
	}
	else
	{
		l->_last->_next = neu ;
		l->_last = neu ;
		*(l->_count)=1+*(l->_count);
	} ;
    return neu->_pvalue ; // Rückgabe Zeiger auf neues Datenfeld
}

void printListe(Liste* l)
{
	Listenelement* k = l->_first ;
	while (k != NULL)
	{
		l->_print(k->_pvalue) ;
		k = k->_next ;
	} ;
}

char* readNode (Listenelement* sucher,char* (*readDataLine) (void* pvalue))
{
	return readDataLine (sucher->_pvalue);
}

Listenelement* getNextNode (Liste* l,Listenelement* oldNode)
{
	if (oldNode==NULL) return l->_first;
	return oldNode->_next;
}


void removeFirst(Liste* l)
{
	if (l->_first == NULL) return ;
	// Speicher des Inhalts freigeben
	l->_remove(l->_first->_pvalue);
	// Speicher des Listenelements freigeben
	Listenelement* next = l->_first->_next;
	free(l->_first) ;
	// Verzeigerung der Liste aktualisieren
	l->_first = next ;
	if (l->_first == NULL) l->_last = NULL ; // kommt kein Knoten mehr
}

void removeList(Liste* l)
{
	while (l->_first != NULL) removeFirst(l) ;
	free (l->_count);
	free(l) ;
}

void* find(Liste* l, void* pv, bool (*compare) (void*, void*))
{
	Listenelement* k = l->_first ;
	while (k != NULL)
	{
		if (compare(k->_pvalue, pv)) return k->_pvalue ;
		k = k->_next ;
	} ;
	return NULL ;
}

