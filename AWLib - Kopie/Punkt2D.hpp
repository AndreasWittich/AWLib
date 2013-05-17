//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "vektor.hpp"

namespace AW {

	using namespace Grundlagen;

	namespace Mathematik {

		template< class NUMERISCH >
		class Punkt2D : public Vektor< DIM2, NUMERISCH > {
			friend std::ostream& operator<<(std::ostream& out, const Punkt2D&  p) {
				out << "{\t";
				if( sizeof( NUMERISCH ) == 1 ) {
					out << "X: " <<(int) p.x() << "\t Y: " << (int) p.y();
				} else {
					out << "X: " << p.x() << "\t Y: " << p.y();
				}
				out << " }";
				return out;
			}
		public:
			static const DIMENSION DIMX;
			static const DIMENSION DIMY;
		public:
			Punkt2D( ) : Vektor< DIM2, NUMERISCH >() {}
			Punkt2D( NUMERISCH x, NUMERISCH y ) : Vektor< DIM2, NUMERISCH >() {				
				_koordinaten[DIMX] = x;
				_koordinaten[DIMY] = y;
			}
			virtual ~Punkt2D( ) {}
		public:

			NUMERISCH x( ) const { return _koordinaten[DIMX]; }
			void x( NUMERISCH wert ) { _koordinaten[DIMX] = wert; }

			NUMERISCH y( ) const { return _koordinaten[DIMY]; }
			void y( NUMERISCH wert ) { _koordinaten[DIMY] = wert; }

		public:
			static void Test( ) {

				std::cout << std::endl << __FUNCTION__  << std::endl << std::endl;
				Punkt2D<NUMERISCH> p1(1,2);
				Punkt2D<NUMERISCH> p2(3,4);
				Punkt2D<NUMERISCH> pc(p1);

				std::cout << "p1: " << p1 << std::endl;
				std::cout << "p2: " << p2 << std::endl;
				std::cout << "pc: " << pc << std::endl;

				assert( p1 == pc );
				assert( p1 != p2 );

				p1 = p2;
				assert( p1.id() != p2.id() );
				assert( p1 == p2 );

				p1.x( 42 );
				assert( p1.x() == 42 );

				std::cout << __FUNCTION__  << " all test done. " << std::endl << std::endl;

			}

		};
		template< class NUMERISCH >
		const DIMENSION Punkt2D<NUMERISCH>::DIMX = 0;
		template< class NUMERISCH >
		const DIMENSION Punkt2D<NUMERISCH>::DIMY = 1;

		typedef Punkt2D<unsigned int> Punkt2DU;
		typedef Punkt2D<double> Punkt2DD;
	}
}