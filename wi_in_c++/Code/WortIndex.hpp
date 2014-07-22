/** File:		  Wortindex.hpp
 *  @author   Mathias Münscher, Magnus Gomes-Fonfara
 *  @version  1.0
 *  @date     01.12.2010
 *  @contact  Mathias.Muenscher@gmx.de
 *  Copyright 2010: Keine Veröffentlichung oder Vervielfältigung.
 */

#ifndef WORTINDEX_HPP
#define WORTINDEX_HPP


#include <cstdlib>
#include <string>
#include "Liste.hpp"
using namespace std ;

/* Der struct WortIndex ist der Datensatz, der in die generische Liste eingehängt werden soll. Er besteht aus:
	_wort: Dem Indexwort
	_letzteDatei: Indexnummer der Datei in der zuletzt das Wort gefunden wurde.
	_letzteZeile: Zeilenenummer in der zuletzt das Wort gefunden wurde.
	_inxZeile: Vollständige Indexzeile
*/
class WortIndex
{
	public:
	WortIndex (string wort);
	string* getWort ();
	void setWort (string neu);
	void setInxZeile (string* neu);
	string* getInxZeile ();
	unsigned int getLastLine ();
	unsigned int getLastFile ();
	void setLastLine (unsigned int neu);
	void setLastFile (unsigned int neu);
   void appendZeile (unsigned int zeilenNr);
   void appendDatei (string* dateiName,unsigned int dateiNr, bool first);
   void clearWI ();
   void printme();
   
	
	//	 CBFs
	static void* copyWortIndex (void*) ;
	static void removeWortIndex (void*);
	static void printWortIndex (void*) ;
	static bool eqWort (void*, void*);
	static bool biggerWort (void*, void*);
	static string* readIndexLine (void*);

	private:
	string*  _wort ;    	
	int* _letzteDatei ;
	int* _letzteZeile ;	
	string* _inxZeile ;   
};
#endif

