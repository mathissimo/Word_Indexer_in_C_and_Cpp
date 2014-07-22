#ifndef LISTE_H
#define LISTE_H

/** Liste.h
 *  @author  Horst Hansen, Mathias Münscher, Magnus Gomes-Fonfara
 *  @version 1.0
 *  @date    7.4.2011
 
   CBF: Callback-Funktion(en)
 */

#include <stdbool.h>

// Das struct Listenelement bildet die Glieder eine einfach verketten Liste und verweist auf einen zugehörigen Datensatz

typedef struct Listenelement
{
	struct Listenelement* _next ;
    void* _pvalue ;
} Listenelement ;

// Das struct Liste ist der Listenkopf einer Liste aus (struct) Listenelementen. Es kennt das erste und letzte Element, die Anzahl der Elemente und speichert die CBF Kopieren und Drucken um die Liste unabhängig vom Datensatz zu halten.

typedef struct Liste
{
	Listenelement* _first ;
	Listenelement* _last ;
	int* _count ;
	void* (*_copy) (void*) ;
	void (*_print) (void*) ;
	void (*_remove) (void*) ;
} Liste ;

/** Die Funktion initListe initialisiert die generische Liste.

    @param (*copy) - CBF um angehängte Datensätze zu kopieren
	@param (*print) - CBF um angehängte Datensätze zu drucken
	@param (*remove) - CBF um angehängte Datensätze aus dem Speicher zu entfernen
	
 */

Liste* initListe(void* (*copy) (void*), void (*print) (void*), void (*remove) (void*));

/** Die Funktion append hängt einen neuen Datensatz an das Ende der Liste

    @param l - Liste
	@param pvalue - anzuhängender Datensatz

 */
void* append(Liste* l, void* pvalue) ;

/** Die Funktion insertLex fügt einen Datensatz in eine kardinale Struktur ein.

    @param Liste* l - Liste
	@param pvalue - Datensatz
	@param (*bigger) - CBF für kardinalen Vergleich

 */
 
void* insertLex (Liste* l, void* pvalue,bool (*bigger) (void*, void*));

/** Die Funktion readNode gibt einen einzelnen Datensatz eines gewünschten Kettengliedes als String zurück

    @param sucher - Quell-Listenglied
	@param (*readDataLine)  - CBF zur Ausgabe des Datensatzes

 */
char* readNode (Listenelement* sucher,char* (*readDataLine) (void* pvalue));

/** Die Funktion getNextNode "hangelt" sich durch die einfach-verkettete Liste. Es gibt den Nachfolger zu einem gegebenen Listenglied zurück. Falls es mit einem NULL-Pointer aufgerufen wird, springt es an den Anfang der Liste

    @param l - Liste
	@param oldNode - Zeiger zum Vorgänger

 */
Listenelement* getNextNode (Liste* l,Listenelement* oldNode);

/** Die Funktion removeFirst löscht das erste Listenelement der Liste.

    @param Liste* l - Liste

 */
 
void removeFirst(Liste* l) ;

/** Die Funktion removeList löscht die gesammte Liste

    @param Liste* l - Liste
	
 */
 
void removeList(Liste* l) ;

/** Die Funktion find sucht einen Datensatz in einer Liste. Die CBF ermöglicht einen Vergleich der Listen- mit dem Such-Datensatz. Als Ergebnis wird entweder ein Zeiger auf den gefundenen Datensatz (Erfolgsfall) oder NULL (nicht gefunden) zrückgegeben

    @param l - Zu prüfende Liste
	@param pv - Such-Datensatz
	@param output - CBF die true/false zurückgibt um zwei Datensätze zu vergleichen

 */
void* find(Liste* l, void* pv, bool (*compare) (void*, void*));

#endif
