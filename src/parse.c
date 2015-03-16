#include <tigcclib.h>         // Include All Header Files

#include "wrappers.h"
#include "parse.h"
#include "pair.h"
#include "util.h"

int isextended( char c ){
	switch( c ){
		case '!': case '$': case '%': case '&': case '*': case '+':
		case '-': case '.': case '/': case ':': case '<': case '=':
		case '>': case '?': case '@': case '^': case '_': case '~':
					return 1;
		default: 	return 0;
	}
}

int isIdentifierChar( char c ){
	return isalnum(c) || isextended(c);
}

OBJECT file2strings( FILE* file ){
	OBJECT strlist = newList();
	char *str = NULL;
	char cur, buffer[16];
	int i=0;
	
	cur = fgetc(file);
	while( cur != EOF ){
		cur = tolower(cur);
//		printf("%c",cur);

		if( isIdentifierChar(cur) ){
			buffer[i] = cur;
			++i;
		}
		else {
			if( i != 0 ){
				str = copyString(buffer);
				append( &strlist, (OBJECT)str );
				buffer[0] = '\0';
				i = 0;
			}
			if( !isspace( cur ) ){
				if( cur == ';' )
					while(cur != '\n' && cur!=EOF) cur = fgetc(file);
				else{
					if(cur == '\"'){
						do{
							buffer[i] = cur;
							cur = fgetc(file);
							++i;
						}while(cur != '\"');
						buffer[i] = '\0';
					}
					else{
						buffer[0] = cur;
						buffer[1] = '\0';
					}
					str = copyString(buffer);
					append( &strlist, (OBJECT)str );
					i = 0;
				}
			}
		}
		buffer[i] = '\0';
		cur = fgetc(file);
	}
	if( i != 0 ){
		str = copyString(buffer);
		append( &strlist, (OBJECT)str);
		buffer[0] = '\0';
		i = 0;
	}

	return strlist;
}

OBJECT stream2strings( void* stream, char (*extract)(void*), int (*isFinished)(char) ){
	OBJECT strlist = newList();
	char *str = NULL;
	char cur, buffer[16];
	int i=0;
	
	cur = extract(stream);
	printf( "%c", cur );
	while( !isFinished(cur)){
		printf("1");
		cur = tolower(cur);
		printf("[%c]", cur);
		
		if( isIdentifierChar(cur) ){
			buffer[i] = cur;
			++i;
		}
		else {
			if( i != 0 ){
				str = copyString(buffer);
				append( &strlist, (OBJECT)str );
				buffer[0] = '\0';
				i = 0;
			}
			if( !isspace( cur ) ){
				if( cur == ';' )
					while(cur != '\n' && !isFinished(cur)) cur = extract(stream);
				else{
					if(cur == '\"'){
						do{
							buffer[i] = cur;
							cur = extract(stream);
							++i;
						}while(cur != '\"');
						buffer[i] = '\0';
					}
					else{
						buffer[0] = cur;
						buffer[1] = '\0';
					}
					str = copyString(buffer);
					append( &strlist, (OBJECT)str );
					i = 0;
				}
			}
		}
		buffer[i] = '\0';
		cur = extract(stream);
	}
	if( i != 0 ){
		str = copyString(buffer);
		append( &strlist, (OBJECT)str);
		buffer[0] = '\0';
		i = 0;
	}

	return strlist;
}

OBJECT helper(OBJECT* pStrList, OBJECT* pSymList);

OBJECT strings2tokens(OBJECT strList, OBJECT* pSymList ){
	OBJECT copy = strList;
	return helper( &copy, pSymList );
}

OBJECT helper( OBJECT* pStrList, OBJECT* pSymList ){
	OBJECT exp;
	OBJECT pair;
	char* str;
	int i, inum, isfloat, isneg;
	double dnum, power;
	
	str = (char*)car( *pStrList );
	
	if( strEqual(str, "(") )
		exp = helper( next(pStrList), pSymList );
	else if( strEqual( str, ")" ) )
		return _NULL;	
	else if( (isdigit( str[0] ) || (str[0] == '.')) || 
			 (str[0] == '-' && (isdigit( str[1] ) || (str[1] == '.'))) ){
		isfloat = 0;
		power = 0.;
		
		isneg = str[0]=='-'? 1: 0;
		for( i=isneg; str[i] != '\0'; ++i ) 
			if( str[i] == '.' )	isfloat = 1;
			else if( isfloat )	power -= 1.;
				
		if( isfloat ){
			dnum = 0;
			power = -1;
			for( i=isneg; str[i] != '\0'; ++i ){
				if( str[i] != '.' ){
					dnum *= 10.;
					dnum += (double)(str[i]-'0');
				}
			}
			dnum *= isneg? -1: 1;
			dnum *= pow( 10., power);
			exp = newFloat( dnum );
		}				
		else{
			inum = 0;
			for( i=isneg; str[i] != '\0'; ++i ){
				inum *= 10;
				inum += str[i]-'0';
			}
			inum *= isneg? -1: 1;
			exp = newInt( inum );
		}
	}
	else if( strEqual(str, "#" ) ){
		str = (char*)car( *next( pStrList ) );
		if( strEqual( str, "t" ) ) exp = newTrue();
		else if( strEqual( str, "f" ) ) exp = newFalse();
		else exp = error( "bad syntax: #", 1, newString(str) );
	}
	else if( strEqual(str, "\'") )
		exp = cons( newSymbol("quote"), 
					helper( next(pStrList), pSymList ));
	else if( str[0] == '\"' )
		exp = newString( str+1 );
	else	exp = newSymbol( str );

	if( !isNull(*pStrList) && !isNull( *next( pStrList ) ) )
		pair = cons(exp, helper( pStrList, pSymList ));
	else
		pair = cons(exp, _NULL);
	
	return pair;
}
