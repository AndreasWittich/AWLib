//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "Winkel.hpp"

using namespace AW::Mathematik;

const double Winkel::PI=3.14159265358979323846;

void Winkel::Test() {
	std::cout << std::endl << AW_FUNKTIONS_NAME  << std::endl << std::endl;

	for( double grad = 0; grad <= 360*2.0; grad += (45.0 / 2.0)  ) {
		Winkel a( grad );
		Winkel b( a.kosinus(), a.sinus() );

		Objekt::testAusgabe( ) << "grad:" << grad << " == " << a << std::endl;

		Objekt::testAusgabe( ) << "sin:" << a.sinus() << " cos:" << a.kosinus() << std::endl;

		Objekt::testAusgabe( ) << "asin:" << Winkel::BogenmassInGrand( asin( a.sinus() ) ) << " acos:" << Winkel::BogenmassInGrand( acos( a.kosinus() ) ) << std::endl;
		Objekt::testAusgabe( ) << "Test: " << b.grad() << std::endl;

		double test = grad;

		while( test >= 360 ) test -= 360;
		assert( fabs( test - b.grad() ) < 0.0000000000001L );
		Objekt::testAusgabe( ) << std::endl;
	}

	double winkelGrand[] = {
		0,
		30,
		45,
		60,
		90,
		180,
		270,
		360
	};
	double bogenmass[] = {
		0,
		PI / 6,
		PI / 4,
		PI / 3,
		PI / 2,
		PI,
		3.0 * PI / 2,
		0
	};
	double sinus[] = {
		0,
		1.0 / 2,
		1.0 / sqrt( 2.0 ),
		sqrt(3.0) / 2.0,
		1,
		0,
		-1,
		0
	};
	double kosinus[] = {
		1,
		sqrt(3.0) / 2.0,
		1.0 / sqrt( 2.0 ),
		1.0 / 2,
		0,
		-1,
		0,
		1
	};
	double tangens[] = {
		0,
		sqrt(3.0) / 3.0,
		1,
		sqrt(3.0),
		std::numeric_limits<double>::infinity(),
		0,
		std::numeric_limits<double>::infinity(),
		0
	};

	for( uint32_t winkelIndex = 0; winkelIndex < (sizeof(winkelGrand) / sizeof( double )); winkelIndex++ ) {
		double grad = winkelGrand[ winkelIndex ];
		Winkel a( grad );
		Objekt::testAusgabe( ) << "Winkel: " << winkelIndex << " - " << a << " " << a.bogenmass() << " PI / " << PI / a.bogenmass() << std::endl;
		Objekt::testAusgabe( ) << "\tsinus " << a.sinus() << std::endl;
		Objekt::testAusgabe( ) << "\tkosinus " << a.kosinus() << std::endl;
		Objekt::testAusgabe( ) << "\ttangens " << a.tangens() << std::endl;
		Objekt::testAusgabe( ) << "\tankathete " << a.ankathete() << std::endl;
		Objekt::testAusgabe( ) << "\tgegenkathete " << a.gegenkathete() << std::endl;
		Objekt::testAusgabe( ) << "\thypotenuse " << a.hypotenuse() << std::endl;		
		Objekt::testAusgabe( ) << std::endl;

		assert( a.bogenmass() == bogenmass[winkelIndex] );
		assert( fabs( a.sinus() - sinus[winkelIndex] ) < 0.00000000001L );
		assert( fabs( a.kosinus() - kosinus[winkelIndex] ) < 0.00000000001L );
		//		Objekt::testAusgabe( ) << "tangens:" << winkelIndex << " " << a.tangens() << " == " << tangens[winkelIndex] << std::endl;
		assert( 
			a.tangens() == std::numeric_limits<double>::infinity() ||
			fabs( a.tangens() - tangens[winkelIndex] ) < 0.00000000001L 
			);

	}

	for( int16_t grad = -1000; grad < 1000; grad += 25 ) {
		Winkel a( (double) grad );
		Winkel b( a.kosinus(), a.sinus() );

		Objekt::testAusgabe( ) << "grad:" << grad << " == " << a << std::endl;

		assert( a == b );
		assert( fabs( a.hypotenuse() - b.hypotenuse() ) < 0.00000000001L );
		assert( fabs( a.sinus() - b.sinus() ) < 0.00000000001L );
		assert( fabs( a.kosinus() - b.kosinus() ) < 0.00000000001L );
		assert( 
			(a.tangens() == std::numeric_limits<double>::infinity() && b.tangens() == std::numeric_limits<double>::infinity() ) ||
			fabs( a.tangens() - b.tangens() ) < 0.00000000001L 
			);

		assert( fabs( a.grad() - b.grad() ) < 0.00000000001L );
		assert( fabs( a.bogenmass() - b.bogenmass() ) < 0.00000000001L );
	}

	std::cout << AW_FUNKTIONS_NAME  << " all test done. " << std::endl << std::endl;

}
