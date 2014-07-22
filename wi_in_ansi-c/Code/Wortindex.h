/** @author   Mathias Münscher
 *  @version  1.0
 *  @date     01.12.2010
 *  @contact  Mathias.Muenscher@gmx.de
 *  Copyright 2010: Keine Veröffentlichung oder Vervielfältigung.
 */
#include <stdbool.h>
#include "Liste.h"

/* Der struct WortIndex ist der Datensatz, der in die generische Liste eingehängt werden soll. Er besteht aus:
	_wort: Dem Indexwort
	_letzteDatei: Indexnummer der Datei in der zuletzt das Wort gefunden wurde.
	_letzteZeile: Zeilenenummer in der zuletzt das Wort gefunden wurde.
	_inxZeile: Vollständige Indexzeile
*/
typedef struct 
{
	char*  _wort ;    	
	int* _letzteDatei ;
	int* _letzteZeile ;	
	char* _inxZeile ;
} WortIndex ;

/** Die Funktion copyWortIndex legt einen neuen Datensatz vom Typ WortIndex im Heap an und kopiert die Daten des übergebenen Datensatzes in den neuen. Anschließend gibt es einen Zeiger auf den neuen Datensatz zurück.

Die Funktion ist als CBF gedacht.

	@param pv - Neuer Datensatz

 */
void* copyWortIndex(void* pv) ;

/** Die Funktion printWortIndex gibt den Speicher eines Datensatzes vom Typ WortIndex frei.

	@param pv - Ziel-Datensatz
 */

void removeWortIndex(void* pv);

/** Die Funktion printWortIndex druckt einen Datensatz vom Typ WortIndex auf der Konsole aus.

	@param pv - Quell-Datensatz
 */

void printWortIndex(void* pv) ;

/** Die Funktion eqWort vergleicht zwei Datensätze auf Ihre IndexWorter. Sind sie gleich, wird true zurückgegeben (sonst false).

	@param pv0 - Datensatz 1
	@param pv1 - Datensatz 2

 */

bool eqWort(void* pv0, void* pv1);

/** Die Funktion biggerWort vergleicht zwei Datensätze auf Ihre IndexWorter. Ist der erste Datensatz "größer" im Sinne der Lexigraphischen Sortierung, wird true zurückgegeben (sonst false). Groß und Kleinschreibung wird ignoriert.

	@param pv0 - Datensatz 1
	@param pv1 - Datensatz 2

 */

bool biggerWort (void* pv0, void* pv1);

/** Die Funktion appendZeile hängt einen neue Zeilennummer als Zeichenkette an das Ende der Indexzeile. Der übergebene String wird dynamisch erweitert und zurückgegeben.

	@param alt - Ursprünglicher String
	@param zeileNr - anzuhängende Zeilennummer
	

 */

char* appendZeile (char alt [],int zeileNr);

/** Die Funktion appendDatei hängt einen neuen Dateiname als Zeichenkette an das Ende der Indexzeile. Handelt es sich um die erste Datei im Eintrag (also ohne Zeilenumbruch und Vorschub) dann muss das Flag "first" gesetzt werden. Der übergebene String wird dynamisch erweitert und zurückgegeben.

	@param alt - Ursprünglicher String
	@param zeileNr - anzuhängende Dateiname
	@param first - Flag ob erster Dateiname im Eintrag

 */

char* appendDatei (char alt [],char dateiName [], bool first);

/** Die Funktion readIndexLine ließt die vollständige Indexzeile aus einem Datensatz vom Typ WortIndex aus und liefert sie als String zurück.

Die Funktion ist als CBF gedacht.

	@param wiElement - Zeiger auf Quell-Datensatz
	

 */

char* readIndexLine (void* wiElement);
