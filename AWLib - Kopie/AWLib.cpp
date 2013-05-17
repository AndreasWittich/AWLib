//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////
//
// AWLib.cpp : Definiert den Einstiegspunkt f�r die Konsolenanwendung.
//

#include "stdafx.h"
#include "Objekt.hpp"
//#include "Vektor.hpp"
//#include "Punkt2D.hpp"
//#include "Groesse2D.hpp"
#include "Rechteck.hpp"
#include "Matrix.hpp"
#include "Winkel.hpp"
#include <iostream>
#include <assert.h>

using namespace AW;

using namespace AW::Grundlagen;
using namespace AW::Mathematik;

void WarteAufEingabe( char const * meldung = "Weiter mit belibiger Taste - (E zum abbrechen)") { 
	std::cout << meldung;
	int c = getchar(); 
	if( toupper( c ) == 'E' ) std::exit( 0 );
}

int _tmain(int argc, char* argv[])
{

	Winkel::Test();
	WarteAufEingabe();


	{
		Objekt::Test();
		WarteAufEingabe();
	}
	{
		Vektor<3,int>::Test();
		Vektor<3,uint8_t>::Test();
		Vektor<3,float>::Test();
		Vektor<3,double>::Test();
		WarteAufEingabe();

		Punkt2D<int>::Test();
		Punkt2D<uint8_t>::Test();
		Punkt2D<float>::Test();
		Punkt2D<double>::Test();
		WarteAufEingabe();

		Groesse2D<int>::Test();
		Groesse2D<uint8_t>::Test();
		Groesse2D<float>::Test();
		Groesse2D<double>::Test();
		WarteAufEingabe();

		Rechteck<int>::Test();
		WarteAufEingabe();

		Matrix<3,3,double>::Test();



		WarteAufEingabe();
	}

#ifdef DEBUG_OBJEKTE
	std::cout << std::endl;
	std::cout << "Gestorben: " <<  Objekt::vergangeneObjekte().size() << " objekte - "  <<  Objekt::vergangeneObjekte() << std::endl;
	std::cout << "Lebendig: " <<  Objekt::lebendeObjekte().size() << " objekte - "  <<  Objekt::lebendeObjekte() << std::endl;
#endif

	WarteAufEingabe( "Belibiger Taste zum Beenden..." );

	return 0;
}

