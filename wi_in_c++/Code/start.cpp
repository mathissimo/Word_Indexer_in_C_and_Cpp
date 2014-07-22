/* 
 *  File:   start.cpp
 *  @author   Mathias Münscher (s0531968)
 *  @version  1.0
 *  @date     13.07.2011
 *  Copyright 2011: Keine Veröffentlichung oder Vervielfältigung.
 */

#include <cstdlib>
#include "IndexerApp.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    IndexerApp* app = new IndexerApp ();
    app->runCommand (argc,argv);
    delete (app);
    return EXIT_SUCCESS ;

}

