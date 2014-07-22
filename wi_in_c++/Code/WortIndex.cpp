/** File:   start.cpp
 *  @author   Mathias Münscher (s0531968)
 *  @version  1.0
 *  @date     13.07.2011
 *  Copyright 2011: Keine Veröffentlichung oder Vervielfältigung.
 */


#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>


#include "WortIndex.hpp"


using namespace std ;

/** Der Konstruktor WortIndex legte einen Datensatz im Speicher an und intitalisiert ihn

   @param wort - Das zu speichernde Wort
	
 */

WortIndex::WortIndex (string wort)
{
    // Daten auf dem Heap erstellen
    _letzteDatei= new int;
    _letzteZeile= new int;
    _wort= new string;
    _inxZeile= new string;
    
    // Daten kopieren
    *_letzteDatei=0;
    *_letzteZeile=0;
    *_wort=wort;
    *_inxZeile="";
    
}
/** Die Funktion clearWI initialisiert einen Datensatz
  
	
 */
void WortIndex::clearWI ()
{
    *_letzteDatei=0;
    *_letzteZeile=0;
    *_wort="";
    *_inxZeile="";
}
/** Die Funktion getWort liefert den Wert zurück von _wort
	
 */
string* WortIndex::getWort ()
{
	return _wort;
}
/** Die Funktion getInxZeile liefert den Wert zurück von _inxZeile
	
 */
string* WortIndex::getInxZeile ()
{
	return _inxZeile;
}
/** Die Funktion getLastLine  liefert den Wert zurück von _letzteZeile
  
	
 */
unsigned int WortIndex::getLastLine () 
{
	return *_letzteZeile;
}
/** Die Funktion getLastFile liefert den Wert zurück von _letzteDatei

     	
 */
unsigned int WortIndex::getLastFile ()
{
	return *_letzteDatei;
}
/** Die Funktion setLastLine legt einen neuen Werf fest für -letzteZeile

   @param neu- neuer Wert

 */
void WortIndex::setLastLine (unsigned int neu)
{
	*_letzteZeile=neu;
}
/** Die Funktion setInxZeile legt einen neuen Werf fest für _inxZeile

   @param neu - neuer Wert
  
 */
void WortIndex::setInxZeile (string* neu)
{
	*_inxZeile=*neu;
}
/** Die Funktion setWort legt einen neuen Werf fest für _wort

   @param neu - neuer Wert

 */
void WortIndex::setWort (string neu)
{
	*_wort=neu;
}
/** Die Funktion setLastFile legt einen neuen Werf fest für _letzteDatei

   @param neu - neuer Wert

	
 */
void WortIndex::setLastFile (unsigned int neu) 
{
	*_letzteDatei=neu;
}
/** Die Funktion appendZeile ergänzt eine Zeilennummer im Datensatz und erneuert den Puffer der letzten Zeile

   @param zeilenNr - anzuhängende Nr.

	
 */  
void WortIndex::appendZeile (unsigned int zeilenNr)
{
  stringstream neu;
  neu << " " << zeilenNr;
  this->_inxZeile->append(neu.str());
  *(this->_letzteZeile) = zeilenNr;
}
/** Die Funktion appendDatei ergänzt eine Datei im Datensatz und erneuert den Puffer für die letzte Datei. Soll vorher ein Zeilenumbruch erfolgen darf das first-Flag nicht gesetzt sein.

   @param dateiName - zu ergänzender Dateiname
   @param dateiNr - Datei-Indexnummer
   @param first -  Flag auf true, falls Einfügen ohne Umbruch
	
 */
void WortIndex::appendDatei (string* dateiName,unsigned int dateiNr, bool first)
{
   if (first) *(this->_inxZeile) = *(this->_inxZeile) + " " + *dateiName;  // Erste Zeile Index-Eintrag ohne Umbruch  
      else *(this->_inxZeile) = *(this->_inxZeile) + "\n  " + *dateiName; // Umbruch f√ºr jede weitere Datei
   *(this->_letzteDatei) = dateiNr;
}

/** Die Funktion copyWortIndex dient als CBF für die List und legt eine Kopie des Datensatzes im Speicher ab und gibt einen Zeiger darauf zurück.

   @param pv- Zu kopierender Datensatz
 
 */

void* WortIndex::copyWortIndex(void* pv)
{
	// √úbergebenen Void-Zeiger mittels Buffer auf WortIndex-Struct casten
   WortIndex* wiBuffer = (WortIndex*) pv ;
	WortIndex* neu = new WortIndex(*(wiBuffer->_wort)) ;
   neu->setInxZeile(wiBuffer->getInxZeile());
	neu->setLastFile(wiBuffer->getLastFile());
	neu->setLastLine(wiBuffer->getLastLine());
	return neu ;
}
/** Die Funktion removeWortIndex dient als CBF zum entfernen eines Datensatzes aus dem Speicher.

   @param pv - Zeiger auf zu löschenden Datensatz
 
	
 */
void WortIndex::removeWortIndex(void* pv)
{
	// √úbergebenen Void-Zeiger auf WortIndex-Struct casten..
  
   WortIndex* pKill = (WortIndex*) pv;
	// .. und die verzeichneten Variablen l√∂schen	
  delete (pKill->_letzteDatei);
  delete (pKill->_letzteZeile);
  delete (pKill->_wort);
  delete (pKill->_inxZeile);
  delete (pKill) ;

}
/** Die Funktion printWortIndex dient als CBF zur Ausgabe eines Datensatzes auf der Konsole

   @param pv - auszugebender Datensatz
	
 */
void WortIndex::printWortIndex(void* pv)
{
	WortIndex* wiBuffer = (WortIndex*) pv ;
	cout << endl << *(wiBuffer->_wort)  ;
	cout << endl << *(wiBuffer->_inxZeile)  ;
	cout << endl << *(wiBuffer->_letzteZeile)  ;
	cout << endl << *(wiBuffer->_letzteDatei)  ;
}
/** Die Funktion printme gibt den Datensatz auf der Konsole aus


 */
void WortIndex::printme()
{
   cout << endl << "== Wortindex =="  ;
   cout << endl << *(this->_wort)  ;
	cout << endl << *(this->_inxZeile)  ;
	cout << endl << *(this->_letzteZeile)  ;
	cout << endl << *(this->_letzteDatei)  ;
}
/** Die Funktion eqWort dient als CBF zum prüfen ob zwei Datensätze vom gleichen Wort sind. Gibt true/false zurück

   @param pv0 - Datensatz 1
   @param pv1 - Datensatz 2
   
	
 */

bool WortIndex::eqWort(void* pv0, void* pv1)
{
	WortIndex* w0 = (WortIndex*) pv0 ;
	WortIndex* w1 = (WortIndex*) pv1 ;
	// Pr√ºfung mit Iteratoren
	string::iterator p0 = (*(w0->_wort)).begin();
	string::iterator p1 = (*(w1->_wort)).begin(); 
	/// Umbau Umlaute + sz
	if ((*(w0->_wort)).length() != (*(w1->_wort)).length())return false;
	while (p0 != (*(w0->_wort)).end() && p1 != (*(w1->_wort)).end()) 
	{
		if (*p0 != *p1) return false;
		p0++;
		p1++;
	}
        
	return true ;
}
/** Die Funktion biggerWort dient als CBF um zum prüfen, ob der zweite Datesatz (lexikographis) größer als der erste ist. Es wird true/false zurückgegeben

   @param mark - Erster Datensatz (Schwelle)
   @param competitor - Zweiter Datensatz (Prüfwert)

	
 */
bool WortIndex::biggerWort (void* mark, void* competitor)
{
	WortIndex* w0 = (WortIndex*) mark ;
	WortIndex* w1 = (WortIndex*) competitor ;
	// Prüfung mit Iteratoren
   string::iterator p0 = (*(w0->_wort)).begin();
	string::iterator p1 = (*(w1->_wort)).begin(); 
	/// Umbau Umlaute + sz
	while (p0 != (*(w0->_wort)).end() && p1 != (*(w1->_wort)).end()) 
	{
		return (toupper(*p0)<toupper(*p1))? true : false;
		p0++;
		p1++;
	}
	if ((*(w0->_wort)).length() < (*(w1->_wort)).length()) return true;
   return false;
}
/** Die Funktion readIndexLine dient als CBF zur Ausgabe eins Datensatzes als String. Gibt einen String zurück.

   @param wiElement - auzugebender Datensatz
 
	
 */

string* WortIndex::readIndexLine (void* wiElement)
{
	WortIndex* wiBuffer = (WortIndex*) wiElement;
	return (wiBuffer->_inxZeile);
}
