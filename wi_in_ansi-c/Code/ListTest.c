/** @author   Mathias Münscher (s0531968)
 *  @version  1.0
 *  @date     01.12.2010
 *  Copyright 2010: Keine Veröffentlichung oder Vervielfältigung.
 
 Diese Programm generiert eine Indexliste über alle Worte mit einer Zeilenanagabe. Es können auch mehrere Dateien in eine Indexliste aufgenommen werden
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Liste.h"
#include "Wortindex.h"
#include "Dateien.h"
#include <stdbool.h>

const int  MAX_FILENAME2 = 256 ;       // Maximale Länge für die Dateinamen
const int  MAX_ZEILE2 = 256 ;       // Maximale Zeilenlänge Input-Datein


// Schwellenwert max. 4 Stellig

/** Die Funktion fMeld meldet einen Fehler und bricht (falls gewünscht) das Programm ab.

    @param meldung - Auszugebene Meldung
	@param leaveProg - Flag für Failure-Exit
 */
void fMeld (char meldung [], bool leaveProg)
{
	printf("\n\n  FEHLER: %s\n\n",meldung) ;
	if (leaveProg) exit(EXIT_FAILURE) ;
};

/** Die Funktion wWertLesen liest den Schwellenwert aus den Programm-Aufrufparametern aus.
	Der Schwellenwert wird zurückgegeben.

   	@param args - Programm-Aufrufparameter
	@param com - Index des zu prüfender String 
	@param pos - Fokus im Strin
	
 */

int wWertLesen (char* args [],int com, int pos)
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


/** Die Funktion kommandoValide liest den Schwellenwert aus den Programm-Aufrufparametern aus.
	Rückgabe true bei korrektem Aufruf

    @param args - Programm-Aufrufparameter
	@param argc - Anzahl Programm-Aufrufparameter
	@param ausgabeKonsole - Rückgabe Flag
	@param wortSchwelle - Rückgabe WErt
	@param inputDateien - Liste mit Quelldateien-Dateinamen
	@param anzInputDat - Anz. Quelldateien
	@param ouputDatei - Dateiname
	
	
 */

bool kommandoValide (int argc, char* args[],bool* ausgabeKonsole, int* wortSchwelle, char inputDateien[][MAX_FILENAME2], int* anzInputDat, char outputDatei [])
{
	*wortSchwelle=0; // Initialisierung der *wortSchwelle
	*anzInputDat=0; // Initialisierung des Zähler für Input-Dateien
	int com=1; // Zähler für die einzelnen Befehle in args (args[0] ist Programmname selber)
	// Überprüfung der Kommandozeilenparameter
	if (argc < 2) fMeld ("Programmaufruf mit:\n lt <options> <outputfile> <inputfile>", true);
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
			strncpy (outputDatei,args[com],MAX_FILENAME2-1);
			outputDatei[strlen(outputDatei)+1]='\0';
			com++;
			};
	// Existierten die Input-Files? Dann in Array speichern
	for (int i=com; i< argc; i++)
		if (existDatei (args[i]))
			{
			strncpy (inputDateien [i-com],args[i],MAX_FILENAME2-1);
			inputDateien [i-com][strlen(inputDateien [i-com])+1]='\0';
			(*anzInputDat)++;
			}
			else 
				{
				char fehlermeldung [100]="";
				snprintf (fehlermeldung, sizeof(fehlermeldung), "Quelldatei %s nicht gefunden.",args[i]);
				fMeld (fehlermeldung,true);
				};
	if (*anzInputDat>0) return true;
		else fMeld ("Es muss mind. eine Quelldatei angegeben werden.", true);
	return false;
};
	
bool isWort (char brocken[])
{
	if	( 
			((brocken[0]>=65) && (brocken[0]<=90))		// A-Z
		||	((brocken[0]>=97) && (brocken[0]<=122))		// a-z
		||	(brocken[0]==95)							// "_"
		)
		{
		int i=1;
		while (							   
					((brocken[i]>=65) && (brocken[i]<=90))		// A-Z
				||	((brocken[i]>=97) && (brocken[i]<=122))		// a-z
				||	((brocken[i]>=48) && (brocken[i]<=57))		// 0-9
				||	(brocken[i]==45)							// "-"
				||	(brocken[i]==95)							// "_"
				) i++;
		if (brocken[i]=='\0') return true;	
		}
	return false;
};

int main(int argc, char* args[])
{
	// Kommando-Variablen initialisieren
	bool ausgabeKonsole=false;
	int wortSchwelle=0;
	int anzInputDat=0;
	char inputDateien [30][MAX_FILENAME2];
	char outputDatei [MAX_FILENAME2];
	// Aufrufkommandos lesen und prüfen
	if (!kommandoValide (argc,args,&ausgabeKonsole,&wortSchwelle,inputDateien,&anzInputDat,outputDatei)) fMeld ("Aufrufparameter nicht valide. Aufruf: \n lt <options> <outputfile> <inputfile>\n",true);

	// Datei-Variablen intitialisieren
	FILE* fOut = fopen(outputDatei, "w") ;
	FILE* fIn = NULL;
	
	// Text-Elemente initialisieren
	Liste* indexList = initListe(copyWortIndex, printWortIndex,removeWortIndex) ;	// Indexliste
	char zeile [MAX_ZEILE2];										// Pufferzeile
	char brocken [MAX_ZEILE2];										// Puffer für Brocken
	WortIndex* wiBuffer=malloc(sizeof(WortIndex));												// Puffer für WortIndex Struct
	wiBuffer->_wort=malloc(256*sizeof(char));
	wiBuffer->_letzteDatei=malloc(sizeof(int));
	wiBuffer->_letzteZeile=malloc(sizeof(int));
	wiBuffer->_inxZeile=malloc(256*sizeof(char));							
	WortIndex* wiGefunden=NULL;										// Puffer (Zeiger!) für Suche
	int cntDat=0;
	int cntZeile=0;
	int zPos=0;
	
	// Daten einlesen uns in  Liste übertragen	
	for (cntDat=0; (cntDat)<(anzInputDat);cntDat++) 						// Schleife für alle Input-Datein
		{
			fIn=fopen(inputDateien[cntDat], "r") ;
			cntZeile=0;
			while (zeileLesen (fIn,zeile)) 					// Schleife für jede Zeile in der Datei
			{
				zPos=0;
				cntZeile++;
				while (getBrocken (zeile, &zPos, brocken)) 	// Schleife für jeden Brocken in einer Zeile
				{
					if (strlen(brocken)>=wortSchwelle)
					{
						if (isWort (brocken))
						{   								
							char* lineBuffer = NULL;
							strcpy(wiBuffer->_wort,brocken);
							wiGefunden=find(indexList, wiBuffer, eqWort); // Wort im Index suchen
							if (wiGefunden==NULL)
							// neues Wort im Index anlegen
							{  		
								// Puffer-Datensatz vom Typ Wortindex ("wiBuffer") befüllen..
								*(wiBuffer->_letzteDatei)=cntDat;
								*(wiBuffer->_letzteZeile)=cntZeile;
								if (anzInputDat>1)
									{
										char* lineBuffer2 = appendDatei (brocken,inputDateien[cntDat],true);
										lineBuffer = appendZeile(lineBuffer2,cntZeile);
										free (lineBuffer2);
									}
									else lineBuffer = appendZeile(brocken,cntZeile);
								strcpy (wiBuffer->_inxZeile,lineBuffer);
								free (lineBuffer);
								//.. und in Index-Liste einfügen				
								insertLex (indexList, wiBuffer,biggerWort);
							}
								else
							// bestehenden Eintrag im Index ergänzen
								{  
									if (*(wiGefunden->_letzteDatei)==cntDat)
									{
										if (*(wiGefunden->_letzteZeile)!=cntZeile)
											{
												lineBuffer=appendZeile(wiGefunden->_inxZeile,cntZeile);
												free (wiGefunden->_inxZeile);
												wiGefunden->_inxZeile=lineBuffer;
											};
									}
										else 
											{
												char* lineBuffer2 = appendDatei (wiGefunden->_inxZeile,inputDateien[cntDat],false);
												lineBuffer=appendZeile(lineBuffer2,cntZeile);
												free (lineBuffer2);
												free (wiGefunden->_inxZeile);
												wiGefunden->_inxZeile=lineBuffer;
											}										
									*(wiGefunden->_letzteDatei)=cntDat;
									*(wiGefunden->_letzteZeile)=cntZeile; 
								};
						};
					};
					initString (brocken);
				};
			};
		if (fclose(fIn)==EOF) fMeld ("Fehler beim Schließen einer Quelldatei",true);
		};
	
	// Ausgabe der Liste als Datei und ggf. auf die Konsole
	Listenelement* readZeiger = NULL; 
	char* bufferZeile=NULL;
	if (ausgabeKonsole) printf("\n*** Indexliste *** \n");
	do
		{
		readZeiger=getNextNode (indexList,readZeiger);
		if (readZeiger !=NULL)
			{
			bufferZeile=readNode(readZeiger,readIndexLine);
			if (ausgabeKonsole) printf("\n%s",bufferZeile) ;
			if (!zeileSchreiben (fOut,bufferZeile)) fMeld ("Fehler beim Schreiben in Zieldatei.",true);
			};
		} while (readZeiger!=NULL);
		if (ausgabeKonsole) printf("\n **************** \n") ;
	
	// Speicher freigeben
	removeList(indexList);
	free (wiBuffer->_wort);
	free (wiBuffer->_letzteDatei);
	free (wiBuffer->_letzteZeile);
	free (wiBuffer->_inxZeile);							
	free (wiBuffer);			
	if (fclose(fOut)==EOF) fMeld ("Fehler beim Schließen der Zieldatei.",true);
    return EXIT_SUCCESS ;
   
   // Dateien schließen und Speicher freigeben
}
