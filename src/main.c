// C Source File
// Created 6/3/2005; 11:28:21 PM

#define USE_TI89              // Compile for TI-89
#define USE_TI92PLUS          // Compile for TI-92 Plus
#define USE_V200              // Compile for V200

#define OPTIMIZE_ROM_CALLS    // Use ROM Call Optimization

#define MIN_AMS 100           // Compile for AMS 1.00 or higher

#define SAVE_SCREEN           // Save/Restore LCD Contents

#include <tigcclib.h>         // Include All Header Files

/* Used IDs:
 * 0:  _NULL
 * 1:  void
 * 2:  string
 * 3:  pair
 * 4:  int
 * 5:  float
 * 6:  symbol
 * 7:  unspecified
 * 8:  true
 * 9:  false
 */

#include "meval.h"
#include "environment.h"

#include "parse.h"
#include "wrappers.h"
#include "util.h"
#include "memgc.h"

OBJECT g_symbolList = NULL;

// Main Function
void _main(void)
{
	OBJECT lst;
	OBJECT toklst;
	OBJECT exp;
	OBJECT env;
	
	g_symbolList = newList();

	clrscr();

	FILE* file = fopen( "scmprog", "r" );
	if(file == NULL){
		printf( "scmprog.TEXT not found." );
		ngetchx();
		return;
	}

	printf("Building env...\n");
	env = setupEnvironment();
	
	printf("parsing...\n");

	lst = file2strings( file );
	fclose( file );
	
	printf("pass 1 complete.\n");

//	printCStrList( lst );
//	newline();

	toklst = strings2tokens( lst, &g_symbolList );
//	printPair( toklst );
//	newline(); newline();

	printf("pass 2 complete.\n\n");
	

	while( !isNull( toklst ) ){
		exp = meval( car(toklst), env );
//		printf( ">" );
//		if(exp) exp->print(exp);
//		else printf("error");
//		newline();
		toklst = cdr(toklst);
	}
	printf( "\n\ndone." );
	
/*	char* str;
	OBJECT exp = _NULL,
		   quit = newSymbol( "quit" );

	while( !symbolEq( exp, quit ) ){
		gets( str );
		lst = stream2strings( str, sgetc, isNull );
		toklst = strings2tokens( lst, &g_symbolList );
		exp = meval( toklst, env );
		exp->print(exp);
	}		
*/
	freeAllGC();
	ngetchx();
}
