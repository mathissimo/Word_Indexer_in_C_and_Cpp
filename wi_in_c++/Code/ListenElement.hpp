#ifndef LISTENELEMENT_HPP
#define LISTENELEMENT_HPP

/** File:		  Liste.h
 *  @author   Mathias Münscher (s0531968)
 *  @version  1.0
 *  @date     13.07.2011
 *  Copyright 2011: Keine Veröffentlichung oder Vervielfältigung.
 *
 *  CBF: Callback-Funktion(en)
 */

#include <string>
#include <cstdlib>
#include <iostream>

///#include "Liste.hpp"

using namespace std ;

// Das struct ListenElement bildet die Glieder eine einfach verketten Liste und verweist auf einen zugehörigen Datensatz

class ListenElement
{
	public:
	ListenElement (void* daten);
	ListenElement* getNext ();
	void setNext (ListenElement* neu);
   void setBefore (ListenElement* neu);
   ListenElement* getBefore ();
	void* getDaten ();
	void setDaten (void* neu);
        
	private:
	ListenElement* _next ;
	ListenElement* _before ;
   	void* _pvalue ;
};

#endif
