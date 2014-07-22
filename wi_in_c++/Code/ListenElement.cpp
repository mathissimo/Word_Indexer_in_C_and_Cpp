/** File:		  ListenElement.cpp
 *  @author   Mathias Münscher (s0531968)
 *  @version  1.0
 *  @date     13.07.2011
 *  Copyright 2011: Keine Veröffentlichung oder Vervielfältigung.
 * 
 *  CBF: Callback-Funktion(en)
 */

#include <cstdlib>
#include <iostream>
#include "ListenElement.hpp"

using namespace std ;


// Das struct ListenElement bildet die Glieder einer mehrfach verketten Liste und verweist auf einen zugehörigen Datensatz

/** Der Konstruktor ListenElement initialisiert die Eigenschaften und hängt den übergebnen Datensatz an.

   @param daten - Zeiger auf Datensatz
  
	
 */

ListenElement::ListenElement (void* daten):
   _next (NULL),
   _before (NULL),
	_pvalue (daten)
{}

/** Die Funktion getNext gibt den Wert von _next zurück

	
 */
ListenElement* ListenElement::getNext ()
{
	return _next;
}

/** Die Funktion setNext setzt _next 

   @param neu - neuer Wert
	
 */
void ListenElement::setNext (ListenElement* neu)
{
	_next=neu;
}

/** Die Funktion geBefore gibt den Wert von _before zurück

	
 */
ListenElement* ListenElement::getBefore ()
{
	return _before;
}

/** Die Funktion setBefore setzt _before

   @param neu - neuer Wert
	
 */

void ListenElement::setBefore (ListenElement* neu)
{
	_before=neu;
}

/** Die Funktion getDaten gibt den Wert von _daten zurück
 
	
	
 */
void* ListenElement::getDaten ()
{
	return _pvalue;
}

/** Die Funktion setNext setzt _daten 

   @param neu - neuer Wert
	
 */


void ListenElement::setDaten (void* neu)
{
	_pvalue=neu;
}


