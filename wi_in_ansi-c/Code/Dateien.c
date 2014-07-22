/** @author   Mathias Münscher
 *  @version  1.0
 *  @date     01.12.2010
 *  @contact  Mathias.Muenscher@gmx.de
 *  Copyright 2010: Keine Veröffentlichung oder Vervielfältigung.
 
 */

#include "Dateien.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
const int  MAX_FILENAME = 256 ;       // Maximale Länge für die Dateinamen 
const int  MAX_ZEILE = 256 ;       // Maximale Zeilenlänge Input-Datein

 
bool getBrocken (char input[], int* pos, char output[]) 
{
	int i = *pos ;		 	// Inputindex 
    int k = 0 ; 			// Outputindex
    int iMax =(strlen (input)+1);

	if ((input [i]=='\n') || (input [i]=='\0')) return false;

	// Vorlauf bis nächster Brocken oder Zeilen-Ende
	while (	(i<=iMax) &&
			(!(							   
				((input[i]>=65) && (input[i]<=90))		// A-Z
			||	((input[i]>=97) && (input[i]<=122))		// a-z
			||	((input[i]>=48) && (input[i]<=57))		// 0-9
			||	(input[i]==45)							// "-"
			||	(input[i]==95)							// "_"
			||	(input [i]=='\n')						// .. oder Zeilenende
			||	(input [i]=='\0')						// .. oder Stringende
			))) i++;

	// Brocken in Output kopieren
	if ((input [i]!='\n') || (input [i]!='\0'))
		while (							   
					((input[i]>=65) && (input[i]<=90))		// A-Z
				||	((input[i]>=97) && (input[i]<=122))		// a-z
				||	((input[i]>=48) && (input[i]<=57))		// 0-9
				||	(input[i]==45)							// "-"
				||	(input[i]==95)							// "_"
				) 
					{
						output[k] = input [i];
						input[i] = " ";
						i++;
						k++; 				
					}
	// Rückgabe
	*pos=i;
	output[k]='\0';
	return true;
};
	


void leseSchreibFehlerMelden(char dateiName[])
{
	printf("\n\n\n  Fehler beim Arbeiten mit der Datei: %s\n\n",dateiName) ;
}


bool existDatei (char dateiName[])
{
	FILE* testDatei = fopen(dateiName, "r") ;
	if (testDatei == NULL) return false;
		else 
			{
				fclose(testDatei);
				return true;
			}
}


bool zeileLesen (FILE* datei, char zeile [])
{
	if (fgets(zeile, MAX_ZEILE-1, datei) != NULL) return true;
		else return false;
}

bool zeileSchreiben (FILE* datei, char zeile [])
{
	if (fputs(zeile,datei)==EOF) return false;
		else 
		{
			if (fputc('\n',datei)==EOF) return false;		
				else return true;
		};
}

/** Die Funktion initString dient dazu,

    @param opfer - mmmmm

 */
void initString (char opfer [])
{
	for (int i=0; i<=sizeof(opfer);i++) opfer[i]='\0';
}
