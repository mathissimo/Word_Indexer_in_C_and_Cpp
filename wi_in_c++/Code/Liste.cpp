
/** File:		  Liste.cpp
 *  @author   Mathias Münscher (s0531968)
 *  @version  1.0
 *  @date     13.07.2011
 *  Copyright 2011: Keine Veröffentlichung oder Vervielfältigung.
 *
 *  CBF = Callback-Funktion
 */ 

//#include <stdlib.h>
//#include <stdio.h>

#include <cstdlib>

#include "Liste.hpp"

using namespace std ;

/** Der Konstruktor Liste initialisiert die Eigenschaften und speichert die übergebenen CBF

   @param *copy - CBF zum Kopieren der angehängten Datensätze
   @param *print - CBF zur Ausgabe der angehängten Datensätze auf der Konsole
   @param *remove - CBF zum Entfernen der angehängten Datensätze aus dem Heap
   @param *saveString - CBF zur String-Ausgabe der angehängten Datensätze (beim Speichern)
	
	
 */
 
Liste::Liste (void* (*copy) (void*), void (*print) (void*), void (*remove) (void*), string* (*saveString) (void*)):
	_first(NULL),
	_last(NULL), 
	_count(0),
	_copy(copy),
	_print(print),
	_remove(remove),
	_saveString (saveString)
	{}


 
 /** Die Methode setFirst legt _first fest

   @param neu - neuer Wert
	
 */
 
void Liste::setFirst (ListenElement* neu)
{
	this->_first=neu;
}

 /** Die Methode getFirst gibt _first zurück
	
 */

ListenElement* Liste::getFirst ()
{
	return this->_first;
}

 /** Die Methode setLast legt _last fest

   @param neu - neuer Wert
	
 */

void Liste::setLast (ListenElement* neu)
{
	this->_last=neu;
}

 /** Die Methode getLast gibt _last zurück.

   @param neu - neuer Wert
	
 */


ListenElement* Liste::getLast ()
{
	return this->_last;
}
/** Die Methode incrCount erhöht den Counter um 1

	
 */
void Liste::incrCount ()
{
	_count++;
}

/** Die Methode getCount gibt den Counter zurück

	
 */
int Liste::getCount ()
{
	return this->_count;
}

/** Die Methode zeileSchreiben schreibt einen String als Zeile in einen Filestream und gibt bei Erfolg ein true zurück.

   @param datei - Filestream
   @param zeile - zu speichernder String
	
 */

bool Liste::zeileSchreiben (ofstream & datei, string* zeile)
{
   if (datei.is_open())
   {
      if ( datei.good() )
      {
         datei<<*zeile<<endl;
         return true;
      }
   }
   return false;
}

/** Die Methode saveList speicher die Liste als Datei und gibt sie ggf. auf der Konsole aus

   @param dateiName - Name der neuen Datei
   @param ausgabeKonsole - Flag für Ausgabe Konsole
	
 */
 
void Liste::saveList (string dateiName, bool ausgabeKonsole)
{
	// Ausgabe der Liste als Datei und ggf. auf die Konsole
	ListenElement* readZeiger = NULL;
   ofstream fOut (dateiName.c_str(), ios::out);
   if (ausgabeKonsole) cout << "\n*** Indexliste *** \n";
	do
   {
		readZeiger=this->getNextNode (readZeiger);
		if (readZeiger !=NULL)
			{
         string bufferStr=*(this->readNode(readZeiger,this->_saveString));
         if (ausgabeKonsole) cout <<endl << *(this->readNode(readZeiger,this->_saveString)); 
			this->zeileSchreiben (fOut,&bufferStr);
			};
   } while (readZeiger!=NULL);
		if (ausgabeKonsole) cout << "\n **************** \n";
	fOut.close();
}

/** Die Methode insertNode fügt ein neues Listenenlement in die Liste ein und gibt einen Zeiger auf den Angehängten Datensatz zurück

   @param vorgaenger - Knoten der vor dem neuen Element kommt
   @param pvalue - Datensatz des neuen Elementes
	
	
 */
void* Liste::insertNode (ListenElement* vorgaenger, void* pvalue)
{
   ListenElement* neu = new ListenElement (this->_copy(pvalue)); // Kopiert Datensatz zuerst
   if (vorgaenger!=NULL) 
   {  // regulärer Fall zweites Listenelement bis Listen-Ende
         neu->setNext (vorgaenger->getNext());
         neu->setBefore(vorgaenger);
         if ((vorgaenger->getNext())!=NULL) (vorgaenger->getNext())->setBefore(neu);
         vorgaenger->setNext(neu); 
   }
   else 
   {  // Spezialfall: Einfügen am Anfang
      neu->setNext(this->_first);
      neu->setBefore(NULL);
      this->_first=neu;
   }
	if (neu->getNext()==NULL) this->_last=neu;  // Einfügen am Ende der Liste
   (this->_count)++;
   return neu->getDaten();
}

/** Die Methode insertLex fügt einen Datensatz (ggf. lexigraphisch) sortiert in die Liste ein und gibt einen Zeiger auf den Angehängten Datensatz zurück

   @param pvalue - zu speichernder Datensatz
   @param (*bigger) - CBF für Sortierung
	
	
 */
void* Liste::insertLex (void* pvalue, bool (*bigger) (void*, void*))
{
	// Vorgehendes ListenElement finden
	ListenElement* k = this->_first ;			// Bufferlement zum Suchen
	ListenElement* bufferOne=NULL;	
	while ((k != NULL)&&(bigger(k->getDaten(), pvalue)))
	{
		bufferOne=k;
		k = k->getNext() ;
	}
   return insertNode (bufferOne,pvalue);
}

/** Die Methode printListe gibt die Liste auf der Konsole aus

 * 	
 */
void Liste::printListe()
{
	ListenElement* k = this->_first ;
	while (k != NULL)
	{
		this->_print(k->getDaten()) ;
		k = k->getNext() ;
	} ;
}

/** Die Methode readNode gibt mittels CBF einen String aus einem Datensatz zurück
 * 
   @param sucher - Relevantes Listen-Element
   @param (*readDataLine) - CBF zur String-Generierung aus dem Datensatz


	
 */


string* Liste::readNode (ListenElement* sucher,string* (*readDataLine) (void* pvalue))
{
	return readDataLine (sucher->getDaten());
}

ListenElement* Liste::getNextNode (ListenElement* oldNode)
{
	if (oldNode==NULL) return this->getFirst();
	return oldNode->getNext();
}


/** Die Methode removeFirst entfernt das erste Listenelement aus dem Speicher

		
 */
void Liste::removeFirst()
{
	if (this->_first == NULL) return ;
	// Speicher des Inhalts freigeben
	this->_remove(this->_first->getDaten());
	// Speicher des Listenelements freigeben
	ListenElement* nextNext = this->_first->getNext();
	delete(this->_first) ;
	// Verzeigerung der Liste aktualisieren
	this->_first = nextNext ;
   if (nextNext!=NULL) nextNext->setBefore(NULL);
	if (this->_first == NULL) this->_last = NULL ; // kommt kein Knoten mehr
}

/** Die Methode removeList entfernt die ganze Liste aus dem Speicher

	
	
 */
void Liste::removeList()
{
	while (this->_first != NULL) removeFirst() ;
	delete (this) ;
}

/** Die Methode find durchsucht die Liste nach einem Datensatz mittels CBF und liefert im Erfolgsfall den Zeiger zurück; sonst NULL.

   @param pv - Zeiger auf Such-Datensatz
   @param (*compare) - CBF zum Vergleich von zwei Datensätze	
	
 */
void* Liste::find(void* pv, bool (*compare) (void*, void*))
{
	ListenElement* k = this->_first ;
	while (k != NULL)
	{
		if (compare(k->getDaten(), pv)) return k->getDaten() ;
		k = k->getNext() ;
	} ;
	return NULL ;
}

