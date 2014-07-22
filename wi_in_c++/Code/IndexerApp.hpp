
/** File:		  IndexerApp.hpp
 *  @author   Mathias Münscher (s0531968)
 *  @version  1.0
 *  @date     13.07.2011
 *  Copyright 2011: Keine Veröffentlichung oder Vervielfältigung.
 
 Diese Programm generiert eine Indexliste über alle Worte mit einer Zeilenanagabe. Es können auch mehrere Dateien in eine Indexliste aufgenommen werden
 */
 
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Liste.hpp"
#include "WortIndex.hpp"
#include "ListenElement.hpp"

using namespace std ;

class IndexerApp
{
	public:
		IndexerApp ();
		int runCommand (int argc, char** args);
		
	private:
		bool ausgabeKonsole;
		unsigned int wortSchwelle;
		unsigned int anzInputDat;
		string inputDateien [30];
		string outputDatei;
      ifstream fIn;
		Liste* indexList;

		void fMeld (string meldung, bool leaveProg);
		unsigned int wWertLesen (char** args,int com, int pos);
		bool kommandoValide (int argc, char** args,bool* ausgabeKonsole,unsigned int* wortSchwelle, string inputDateien[],unsigned int* anzInputDat, string* outputDatei);
		bool isWort (string brocken);
		string charToString (char* c);
      bool getBrocken (string* input, string* output);      
      
		bool existDatei (string) ;
      bool zeileLesen (ifstream& datei, string* zeile);
      string removeUmlaute (string input);
 
};
