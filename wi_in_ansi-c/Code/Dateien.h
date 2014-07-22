/** @author   Mathias Münscher
 *  @version  1.0
 *  @date     01.12.2010
 *  @contact  Mathias.Muenscher@gmx.de
 *  Copyright 2010: Keine Veröffentlichung oder Vervielfältigung.
 */

#include <stdbool.h>
#include <stdio.h>


/** Die Funktion getBrocken sucht in eine Zeile ab einer gewünschten Position nach dem Nächsten "Wort" das nicht aus A-Z,a-z,0-9,-,_ besteht. Es macht keine weitere inhaltliche Prüfung (kein RegEx!) Bei Zeilenende oder Stringende wird ein false zurückgegeben.

    @param input - Quellzeile
	@param pos - Suchstart-Position
	@param output - Nächstes gefundene "Wort"

 */
 
bool getBrocken (char input[], int* pos, char output[]);

/** Die Funktion leseSchreibFehlerMelden gibt eine Fehlermeldung zu
fehlgeschlagenen Dateien-Operationen (mit Dateinamen) aus.
 */
void leseSchreibFehlerMelden(char dateiName[]);

/** Die Funktion existDatei prüft die Existenz einer Datei durch "fopen".
	Bei Erfolg liefert sie ein 1 zurück. Dann wird solange nach einem neuen
	Dateinamen gefragt bis dieser (a.) gefunden wird oder (b.) ein Abbruch über "q"
	erfolgt. Bei Abbruch wird eine 0 zurückgeliefert.

    @param dateiName: Hier wird der zu prüfende Dateiname an die Funktion übergeben 
    		und am Ende der Funktion der ermittelte Dateiname zurückgegeben.

 */
 
bool existDatei (char dateiName[]) ;

/** Die Funktion zeileLesen liest eine Zeile aus einer Datei. Der Stream wird nicht zurückgesetzt. Ist das Dateiende erreicht liefert sie false zurück (sonst true).

    @param datei - Quelldatei
	@param zeile - Gefunden Zeile

 */

bool zeileLesen (FILE* datei, char zeile []);

/** Die Funktion zeileSchreiben schreibt eine Zeile in eine Datei. Der Stream wird nicht zurückgesetzt. Bei Schreibfehler oder Platzmangel liefert sie false zurück (sonst true).

    @param datei - Zieldatei
	@param zeile - Zu speichernde Zeile

 */

bool zeileSchreiben (FILE* datei, char zeile []);

/** Die Funktion initString intitialisiert einen String mit dem \0-Zeichen.

    @param opfer - Ziel-String
 */

void initString (char opfer []);
