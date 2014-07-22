
/** File:		  IndexerApp.cpp
 *  @author   Mathias Münscher (s0531968)
 *  @version  1.0
 *  @date     13.07.2011
 *  Copyright 2011: Keine Veröffentlichung oder Vervielfältigung.
 
 * 
 Diese Programm generiert eine Indexliste über alle Worte mit einer Zeilenanagabe. Es können auch mehrere Dateien in eine Indexliste aufgenommen werden
 */
 
#include <string>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <ostream>



#include "IndexerApp.hpp"
using namespace std ;

/** Der Konstruktor initialisiert ausschließlich die Objekt-Eigenschaften

 */


IndexerApp::IndexerApp ():
		ausgabeKonsole (false),
		wortSchwelle(0),
		anzInputDat(0),
      indexList(NULL)
		{}

/** Die Methode charToString liefert einen Char-Array als String zurück

   @param c - der umzuwandelnde Char
	
	
 */
string IndexerApp::charToString (char* c)
{
   stringstream ss;
   string s;
   ss << c;
   ss >> s;
   ss >> s;
   return s;
}

/** Die Methode fMeld gibt eine Fehlermeldung aus und beendet ggf. das Programm.

   @param meldung - Auszugebende Fehlemeldung
   @param leaveProg - Programmexit-Flag


 */

void IndexerApp::fMeld (string meldung, bool leaveProg)
{
	cout << "FEHLER: " <<meldung << endl << endl ;
	if (leaveProg) exit(EXIT_FAILURE) ;
};

 
 /** Die Methode existDatei prüft die Existenz einer Datei durch kurzes öffnen.
  * Im Erfolgsfall gibt sie True zurück

   @param dateiName - Name der zu prüfenden Datei
	
 */
 

bool IndexerApp::existDatei (string dateiName)
{
	ifstream testDatei (dateiName.c_str());
	if (testDatei.is_open())
			{
				testDatei.close();
				return true;
			}
   else return false;
}

/** Die Methode zeileLesen ließt eine einzelne Zeile aus einem Filestream 
 *  und legt sie in den String-Pointer. Bei Datei-Ende oder Fehler gibt sie false zurück.

   @param datei - Filestream
   @param zeile -  Zurückgeliferte Zeile
	
	
 */
 
bool IndexerApp::zeileLesen (ifstream& datei, string* zeile)
{
   if (datei.is_open())
   {
      if ( datei.good() )
      {
         getline (datei,*zeile);
         return true;
      }
   }
   return false;
}

/** Die Methode wWertLesen liest den Schwellenwert aus den Programm-Aufrufparametern aus.
	Der Schwellenwert wird zurückgegeben.

   @param args - Programm-Aufrufparameter
	@param com - Index des zu prüfender String 
	@param pos - Fokus im String
	
 */	
 
unsigned int IndexerApp::wWertLesen (char** args,int com, int pos)
{
	int leseWert=0; // Initialisierung Ausgabewert
	if (args[com][pos]=='=') 
		{
		char bufferStr [5]=""; // Initialisierung Bufferstring
		int i=1;
		while ((args[com][pos+i]>=48) && (args[com][pos+i]<=57) && (i<=5)) // Übertragung aller Ziffern
			{
			bufferStr[i-1]= args[com][pos+i];
			i++;
			}
		bufferStr[i-1]='\0';
		if (i>1) leseWert=atoi(bufferStr);
			else fMeld ("Ganzzahl (max. 4 stellig) nach '-w=' erwartet",true);
		pos=pos+2+i;
		}
		else fMeld ("Nach Option '-w' wird '='<Anzahl Buchstaben> erwartet.",true);
	return leseWert;
};


/** Die Methode kommandoValide liest den Schwellenwert aus den Programm-Aufrufparametern aus.
	Rückgabe true bei korrektem Aufruf

   @param args - Programm-Aufrufparameter
	@param argc - Anzahl Programm-Aufrufparameter
	@param ausgabeKonsole - Rückgabe Flag
	@param wortSchwelle - Rückgabe WErt
	@param inputDateien - Liste mit Quelldateien-Dateinamen
	@param anzInputDat - Anz. Quelldateien
	@param ouputDatei - Dateiname
	
	
 */

bool IndexerApp::kommandoValide (int argc, char** args, bool* ausgabeKonsole,unsigned int* wortSchwelle, string inputDateien[],unsigned int* anzInputDat, string* outputDatei)
{
	*wortSchwelle=0; // Initialisierung der *wortSchwelle
	*anzInputDat=0; // Initialisierung des Zähler für Input-Dateien
	int com=1; // Zähler für die einzelnen Befehle in args (args[0] ist Programmname selber)
	// Überprüfung der Kommandozeilenparameter
	if (argc < 2) fMeld ("Programmaufruf mit:\n iapp <options> <outputfile> <inputfile>", true);
	// <options> da?
	if (args[com][0]=='-')
		{
		// Erstes Kommando = <options>?
		if (args[com][1]=='w') *wortSchwelle=wWertLesen (args, 1,2);
			else
				if (args[com][1]=='p') *ausgabeKonsole=true;
					else fMeld ("'w' oder 'p' nach '-' erwartet",true);
		// Zweites Kommando = <options>?
		com++;
		if (args[com][0]=='-')
			{
			if (args[com][1]=='w') *wortSchwelle=wWertLesen (args, 2,2);
				else
					if (args[com][1]=='p') *ausgabeKonsole=true;	
						else fMeld ("'w' oder 'p' nach '-' erwartet",true);
			com++;
			};
		}

	// Existiert das Output-File schon? Dann abbrechen um Überschreiben zu verhindern
	if (existDatei (args[com])) fMeld ("Zieldatei existiert schon.",true);
		else 
			{
         *outputDatei=charToString(args[com]);
			com++;
			};
	// Existierten die Input-Files? Dann in Array speichern
	for (int i=com; i< argc; i++)
		if (existDatei (args[i]))
			{
			inputDateien [i-com]=charToString(args[i]);
			(this->anzInputDat)++;
			}
			else 
				{
				stringstream fehlermeldung;
            fehlermeldung << "Quelldatei nicht gefunden:" << args[i];
				fMeld (fehlermeldung.str(),true);
				};
	if (*anzInputDat>0) return true;
		else fMeld ("Es muss mind. eine Quelldatei angegeben werden.", true);
	return false;
};

/** Die Methode removeUmlaute gibt einen String ohne Umlaute (umgewandelt in ae,
 * ue,oe) und oh ß (umgewandelt in ss) zurück.

   @param input - String (ggf.) mit Umlauten
	
 */
string IndexerApp::removeUmlaute (string input)
{   
   string neu = "";
   string::iterator i=input.begin();
   while (i!=input.end())
   {
      switch ((int)(*i))   {
         case -33: neu.append("ss"); break; // "sz"
         case -60:
         case -28: neu.append("ae"); break; 	// "a-umlaut"
         case -36:
         case -4 : neu.append("ue"); break;	// "u-umlaut"
         case -42:
         case -10: neu.append("oe"); break;   // "o-umlaut"
         default: neu+=(*i);
         }
      i++;      
   };
   return neu;
}

/** Die Methode getBrocken sucht in eine Zeile nach dem Nächsten "Wort" das nicht aus A-Z,a-z,0-9,-,_ besteht und überträgt es in den Output. Danach werden die übertragenen und die vorlaufenen Zeichen aus dem Input-String entfernt und der String gekürzt. Es macht keine weitere inhaltliche Prüfung (kein RegEx!) Bei Stringende wird ein false zurückgegeben.

    @param input - Quellzeile
	@param pos - Suchstart-Position
	@param output - Nächstes gefundene "Wort"

 */ 
bool IndexerApp::getBrocken (string* input, string* output) 
{

   int inCount=0,outCount=0;
   *output="";
   if ((*input).length() == 0) return false;
   string::iterator inI = (*input).begin();

	// Vorlauf bis nächster Brocken oder Zeilen-Ende
	while (	(inI!=(*input).end()) &&
			(!(							   
				((((int)(*inI))>=65) && (((int)(*inI))<=90))		// A-Z
			||	((((int)(*inI))>=97) && (((int)(*inI))<=122))	// a-z
			||	((((int)(*inI))>=48) && (((int)(*inI))<=57))		// 0-9
         ||	((int)(*inI)==-60)   ||	((int)(*inI)==-28)		// "a-umlaut"
         ||	((int)(*inI)==-36)   ||	((int)(*inI)==-4)       // "u-umlaut"
         ||	((int)(*inI)==-42)   ||	((int)(*inI)==-10)		// "o-umlaut"
			||	(((int)(*inI))==-33)                          	// "sz"
			||	(((int)(*inI))==45)                          	// "-"
			||	(((int)(*inI))==95)                            	// "_"
			||	(((int)(*inI))=='\n')                           // .. oder Zeilenende
			||	(((int)(*inI))=='\0')                           // .. oder Stringende
			))) {
//               cout << ((int)(*inI))<<"|";
               inI++;
               inCount++;
             };

	// Brocken in Output kopieren
	if (inI!=(*input).end())
		while (							   
					((((int)(*inI))>=65) && (((int)(*inI))<=90))		// A-Z
				||	((((int)(*inI))>=97) && (((int)(*inI))<=122))	// a-z
				||	((((int)(*inI))>=48) && (((int)(*inI))<=57))		// 0-9
            ||	((int)(*inI)==-60)   ||	((int)(*inI)==-28)		// "a-umlaut"
            ||	((int)(*inI)==-36)   ||	((int)(*inI)==-4)       // "u-umlaut"
            ||	((int)(*inI)==-42)   ||	((int)(*inI)==-10)		// "o-umlaut"
            ||	(((int)(*inI))==-33)                          	// "sz"
				||	(((int)(*inI))==45)                          	// "-"
				||	(((int)(*inI))==95)                          	// "_"
				) 
					{
                  outCount++;
						inCount++;
                  inI++;
					}
   (*output)=input->substr((inCount-outCount),outCount); // Alten String löschen
   input->erase(0,inCount);
    return true;
};

/** Die Methode isWort prüft ob der übergebene String eine Zeichkette im Sinne der RegEx-Definition in der Belegarbeit ist und gibt entsprechend true/false zurück.

   @param brocken - zu prüfender String

	
 */

bool IndexerApp::isWort (string brocken)
{
   string::iterator i=brocken.begin();
   if	( 
					(((int)(*i)>=65)     && ((int)(*i)<=90))		// A-Z
				||	(((int)(*i)>=97)     && ((int)(*i)<=122))		// a-z
				||	((int)(*i)==95)									// "_"
				||	((int)(*i)==-33)           							// "sz"
            ||	((int)(*i)==-60)   ||	((int)(*i)==-28)		// "a-umlaut"
            ||	((int)(*i)==-36)   ||	((int)(*i)==-4)       // "u-umlaut"
            ||	((int)(*i)==-42)   ||	((int)(*i)==-10)		// "o-umlaut"
		)
		{
      i++;
      while (							   
					(((int)(*i)>=65) && ((int)(*i)<=90))		// A-Z
				||	(((int)(*i)>=97) && ((int)(*i)<=122))		// a-z
				||	(((int)(*i)>=48) && ((int)(*i)<=57))		// 0-9
				||	((int)(*i)==45)									// "-"
				||	((int)(*i)==95)									// "_"
				||	((int)(*i)==-33)									// "sz"
            ||	((int)(*i)==-60)   ||	((int)(*i)==-28)		// "a-umlaut"
            ||	((int)(*i)==-36)   ||	((int)(*i)==-4)       // "u-umlaut"
            ||	((int)(*i)==-42)   ||	((int)(*i)==-10)		// "o-umlaut"
				) i++;
		if (i==brocken.end()) return true;	
		}
	return false;
};

/** Die Methode runCommand führt die Index-Application aus

   @param argc - Anzahl Aufrufparameter Programm
   @param args - Aufrufparameter Programm selber.
	
	
 */
 
int IndexerApp::runCommand (int argc, char** args)
{
	// Aufrufkommandos lesen und prüfen
	if (!kommandoValide (argc,args,&ausgabeKonsole,&wortSchwelle,inputDateien,&anzInputDat,&outputDatei)) fMeld ("Aufrufparameter nicht valide. Aufruf: \n lt <options> <outputfile> <inputfile>\n",true);

   // Liste inititalisieren
   indexList = new Liste (WortIndex::copyWortIndex, WortIndex::printWortIndex, WortIndex::removeWortIndex, WortIndex::readIndexLine);
	
	// Text-Elemente initialisieren
   string zeile;											// Pufferzeile
	string brocken;										// Puffer für Brocken
	WortIndex* wiBuffer=new WortIndex ("");						// Puffer für WortIndex Struct
	WortIndex* wiGefunden=NULL;										// Puffer (Zeiger!) für Suche
   // WortIndex* kk=NULL;
	unsigned int cntDat=0;
	unsigned int cntZeile=0;
	int* zPos=new int(0);
	
	// Daten einlesen uns in  Liste übertragen	
	for (cntDat=0; (cntDat)<(anzInputDat);cntDat++) 						// Schleife für alle Input-Datein
		{
			this->fIn.open (inputDateien[cntDat].c_str()) ;
			cntZeile=0;
			while ((this->zeileLesen (fIn,&zeile))) //&&(cntZeile<1)) 					// Schleife für jede Zeile in der Datei
			{
            *zPos=0;
				cntZeile++;
				while (this->getBrocken (&zeile,&brocken)) 	// Schleife für jeden Brocken in einer Zeile
				{
               if (brocken.length()>=wortSchwelle)
					{
						if (isWort (brocken))
						{   								
                     wiBuffer->setWort(removeUmlaute(brocken));
							wiGefunden=(WortIndex*)indexList->find(wiBuffer, WortIndex::eqWort); // Wort im Index suchen
                     if (wiGefunden==NULL)
							// neues Wort im Index anlegen
							{  		
                        // Puffer-Datensatz vom Typ Wortindex ("wiBuffer") befüllen..
                        wiBuffer->setInxZeile (&brocken);
								if (anzInputDat>1)
									{
										wiBuffer->appendDatei(&inputDateien[cntDat],cntDat,true);
										wiBuffer->appendZeile(cntZeile);
									}
                        else wiBuffer->appendZeile(cntZeile);
                        indexList->insertLex (wiBuffer,WortIndex::biggerWort);
							}
                     else
                     // bestehenden Eintrag im Index ergänzen
                     {  
                        if (wiGefunden->getLastFile()==cntDat)
                        {  // in der selben Datei wie Eintrag davor
                           if (wiGefunden->getLastLine()!=cntZeile)
                              {
                                 wiGefunden->appendZeile(cntZeile);
                              };
                        }
                        else 
                           { // neue Datei
                              wiGefunden->appendDatei (&inputDateien[cntDat],cntDat,false);
                              wiGefunden->appendZeile (cntZeile);
                           }										
                     };
						};
                  wiBuffer->clearWI();
					};
					brocken="";
				};
			};
		fIn.close();
		};
	// Ausgabe
   indexList->saveList (outputDatei,ausgabeKonsole);
	   
	// Speicher freigeben
	indexList->removeList();
   WortIndex::removeWortIndex(wiBuffer);
   delete (zPos);
   return EXIT_SUCCESS ;
}
