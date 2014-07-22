#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Wortindex.h"

void* copyWortIndex(void* pv)
{
	// Übergebenen Void-Zeiger mittels Buffer auf WortIndex-Struct casten
	WortIndex* wiBuffer = (WortIndex*) pv ;
	char* pBufferW = (char*) wiBuffer->_wort ;
	int* pBufferLD = (int*) wiBuffer->_letzteDatei ;
	int* pBufferLZ = (int*) wiBuffer->_letzteZeile ;
	char* pBufferIZ = (char*) wiBuffer->_inxZeile ;
	
	// Speicher für neuen WortIndex und angehängte Variablen besorgen
	WortIndex* wiNeu = (WortIndex*) malloc(sizeof(WortIndex)) ;
	char* pNeuW = (char*) malloc(strlen(pBufferW)+1) ;
	int* pNeuLD = (int*) malloc(sizeof(int)) ;
	int* pNeuLZ = (int*) malloc(sizeof(int)) ;
	char* pNeuIZ = (char*) malloc(strlen(pBufferIZ)+1) ;

	// Speicher bekommen? Sonst Programmabbruch
	if ((wiNeu == NULL) ||(pNeuW == NULL) || (pNeuLD == NULL) || 
		(pNeuLZ == NULL) || (pNeuIZ == NULL))
	{
		printf("\n\nKein Arbeitsspeicher mehr vorhanden!\n") ;
		printf("Das Programm wird beendet!\n") ;
		exit(EXIT_FAILURE) ;
	} ;
	
	// Daten kopieren..
	strcpy(pNeuW, pBufferW) ;
	*pNeuLD=*pBufferLD;
	*pNeuLZ=*pBufferLZ;
	strcpy(pNeuIZ, pBufferIZ) ;
	
	// ..und im Struct einhängen
	wiNeu->_wort			= pNeuW ;
	wiNeu->_letzteDatei	= pNeuLD ;
	wiNeu->_letzteZeile 	= pNeuLZ ;
	wiNeu->_inxZeile  	= pNeuIZ ;

	return wiNeu ;
}

void removeWortIndex(void* pv)
{
	// Übergebenen Void-Zeiger auf WortIndex-Struct casten..

	WortIndex* pKill = (WortIndex*) pv;

	// .. und die verzeichneten Variablen löschen
	free (pKill->_wort) ;
	free (pKill->_letzteDatei) ;
	free (pKill->_letzteZeile) ;
	free (pKill->_inxZeile) ;
	free (pKill) ;

}

void printWortIndex(void* pv)
{
	WortIndex* pc = (WortIndex*) pv ;
	printf("\n%s  ", pc->_inxZeile) ;
}

bool eqWort(void* pv0, void* pv1)
{
	WortIndex* w0 = (WortIndex*) pv0 ;
	WortIndex* w1 = (WortIndex*) pv1 ;
	return (strcmp(w0->_wort, w1->_wort)==0)?true:false ;
}

bool biggerWort (void* pv0, void* pv1)
{
	WortIndex* w0 = (WortIndex*) pv0 ;
	WortIndex* w1 = (WortIndex*) pv1 ;
	
	// Großbuchstaben auf Kleinbuchstaben übersetzen
	char* stBuffer0= malloc(strlen(w0->_wort)+1);
	char* stBuffer1= malloc(strlen(w1->_wort)+1);
	int i=0;
	while (w0->_wort[i]!='\0')
		{
	   		if((w0->_wort[i] >= 'A') && (w0->_wort[i] <= 'Z')) stBuffer0[i] = w0->_wort[i] +32;
	   			else stBuffer0[i] = w0->_wort[i];
	   		i++;
	   	}
	stBuffer0[i]='\0';
	i=0;
	while (w1->_wort[i]!='\0')
		{
	   		if((w1->_wort[i] >= 'A') && (w1->_wort[i] <= 'Z')) stBuffer1[i] = w1->_wort[i] +32;
	   			else stBuffer1[i] = w1->_wort[i];
	   		i++;
	   	}
	stBuffer1[i]='\0';

	// Stringvergleich
	bool bBuffer=(strcmp(stBuffer0, stBuffer1)>0);
	free (stBuffer0);
	free (stBuffer1);
	if (bBuffer) return true;
		return false;
}

char* appendZeile (char* alt,int zeileNr)
{
	char sNr [10]="";
	snprintf (sNr, sizeof(sNr), "%d",zeileNr);
	char* stBuffer=malloc(strlen(alt)+strlen(sNr)+1+1);
	strcpy (stBuffer,alt);
	strcat (stBuffer," ");
	strcat (stBuffer,sNr);
	return stBuffer;
}

char* appendDatei (char* alt ,char dateiName [], bool first)
{
	char* pNeu=NULL;
	if (first)
		{      // Erste Zeile Index-Eintrag ohne Umbruch  
		pNeu = malloc(strlen(alt)+strlen(dateiName)+1+1);
		snprintf (pNeu, (strlen(alt)+strlen(dateiName)+1+1), "%s %s",alt,dateiName);
		}
		else 
			{	// Umbruch für jede weitere Datei
			pNeu = malloc(strlen(alt)+strlen(dateiName)+4+1);
			snprintf (pNeu,(strlen(alt)+strlen(dateiName)+4+1), "%s\n   %s",alt,dateiName); 
			}
	return pNeu;
}

char* readIndexLine (void* wiElement)
{
	WortIndex* wiBuffer = (WortIndex*) wiElement;
	return wiBuffer->_inxZeile;
}
