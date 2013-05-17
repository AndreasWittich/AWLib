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
	std::cout << std::endl << __FUNCTION__  << std::endl << std::endl;

	for( double grad = 0; grad <= 360*2.0; grad += (45.0 / 2.0)  ) {
		Winkel a( grad );
		Winkel b( a.kosinus(), a.sinus() );

		std::cout << "grad:" << grad << " == " << a << std::endl;

		std::cout << "sin:" << a.sinus() << " cos" << a.kosinus() << std::endl;

		std::cout << "asin:" << Winkel::BogenmassInGrand( asin( a.sinus() ) ) << " acos" << Winkel::BogenmassInGrand( acos( a.kosinus() ) ) << std::endl;
		std::cout << "Test: " << b.grad() << std::endl;

		double test = grad;

		while( test >= 360 ) test -= 360;
		assert( fabs( test - b.grad() ) < 0.0000000000001L );
		std::cout << std::endl;
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
		std::cout << "Winkel: " << winkelIndex << " - " << a << " " << a.bogenmass() << " PI / " << PI / a.bogenmass() << std::endl;
		std::cout << "\tsinus " << a.sinus() << std::endl;
		std::cout << "\tkosinus " << a.kosinus() << std::endl;
		std::cout << "\ttangens " << a.tangens() << std::endl;
		std::cout << "\tankathete " << a.ankathete() << std::endl;
		std::cout << "\tgegenkathete " << a.gegenkathete() << std::endl;
		std::cout << "\thypotenuse " << a.hypotenuse() << std::endl;		
		std::cout << std::endl;

		assert( a.bogenmass() == bogenmass[winkelIndex] );
		assert( fabs( a.sinus() - sinus[winkelIndex] ) < 0.00000000001L );
		assert( fabs( a.kosinus() - kosinus[winkelIndex] ) < 0.00000000001L );
		//		std::cout << "tangens:" << winkelIndex << " " << a.tangens() << " == " << tangens[winkelIndex] << std::endl;
		assert( 
			a.tangens() == std::numeric_limits<double>::infinity() ||
			fabs( a.tangens() - tangens[winkelIndex] ) < 0.00000000001L 
			);

	}

	for( int16_t grad = -1000; grad < 1000; grad += 10 ) {
		Winkel a( (double) grad );
		Winkel b( a.kosinus(), a.sinus() );

		std::cout << "grad:" << grad << " == " << a << std::endl;

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

	std::cout << __FUNCTION__  << " all test done. " << std::endl << std::endl;

}