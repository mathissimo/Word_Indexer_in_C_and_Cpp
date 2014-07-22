
/** File:		  Liste.hpp
 *  @author   Mathias Münscher (s0531968)
 *  @version  1.0
 *  @date     13.07.2011
 *  Copyright 2011: Keine Veröffentlichung oder Vervielfältigung.
 *  
 *  CBF: Callback-Funktion(en)
 */

#ifndef LISTE_HPP
#define LISTE_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "ListenElement.hpp"


using namespace std ;


// Das struct Liste ist der Listenkopf einer Liste aus (struct) Listenelementen. Es kennt das erste und letzte Element, die Anzahl der Elemente und speichert die CBF Kopieren und Drucken um die Liste unabhängig vom Datensatz zu halten.

class Liste
{
	public:
	Liste (void* (*copy) (void*), void (*print) (void*), void (*remove) (void*),string* (*saveString) (void*));
	void* append(void* pvalue) ;
	void* insertLex (void* pvalue,bool (*bigger) (void*, void*));
	string* readNode (ListenElement* sucher,string* (*readDataLine) (void* pvalue));
	ListenElement* getNextNode (ListenElement* oldNode);
	void removeList() ;
	void* find(void* pv, bool (*compare) (void*, void*));
   	void printListe();
	void setFirst (ListenElement* neu);
	ListenElement* getFirst ();
	void setLast (ListenElement* neu);
	ListenElement* getLast ();
	void incrCount ();
	int getCount ();
   	void printListNodes();
   	void saveList (string dateiName, bool ausgabeKonsole);
   	bool zeileSchreiben (ofstream & datei, string* zeile);
	
	private:
	ListenElement* _first ;
	ListenElement* _last ;
	int _count ;
	void removeFirst() ;
   void* insertNode (ListenElement* vorgaenger, void* pvalue);
	void* (*_copy) (void*) ;	
	void (*_print) (void*) ;
	void (*_remove) (void*) ;
   string* (*_saveString) (void*);
};
#endif
