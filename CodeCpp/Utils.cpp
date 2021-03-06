/**
 * \file Utils.h
 * \brief Notre utilitaire
 * \author CHARDAN Anaël
 * \author DAMEY Jérémy
 * \date 09/03/2014
 */

#include "Utils.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "Constantes.h"
#include <cmath>

using namespace std;

string intToString( int i ) {
    ostringstream oss;
    oss << i;
    return oss.str();
}

std::string
colorMessage( const char* out , int color ) {
    ostringstream o;
#ifdef __linux__
    o << "\E[" << color << ";1m"<< out << "\E[m";
    return o.str();
#else
    o << out;
    return o.str();
#endif
}

int convertIndiceXToPixel( int i ) {
    return CASEWITDH * i + MARGINLEFT + PADDINGRIGHT * i ;
}

int convertIndiceYToPixel ( int j ) {
    return CASEHEIGHT * j + MARGINTOP + PADDINGBOTTOM * j ;
}

int convertXPixel( int xpixel ) {
    if ( xpixel >= MARGINLEFT  && xpixel <= ( MARGINLEFT + ( COLONNE * CASEWITDH ) + ( ( COLONNE - 1 ) * PADDINGRIGHT ) ) ) {
        return ceil( ( xpixel - MARGINLEFT ) / ( CASEWITDH  + PADDINGRIGHT ) );
    }
    return -1;
}

int convertYPixel( int ypixel ) {
    if ( ypixel >= MARGINTOP && ypixel <= ( MARGINTOP + ( LIGNE * CASEHEIGHT ) + ( ( LIGNE - 1 ) * PADDINGBOTTOM ) ) ) {
        return ceil( ( ypixel - MARGINTOP ) / ( CASEHEIGHT  + PADDINGBOTTOM ) );
    }

        return -1;
}

int randomNumber( int min , int max ) {
    return min + ( rand() % ( max + 1 - min ) );
}


