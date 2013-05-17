//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Vektor.hpp"

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
				(*this)[DIMX] = x;
				(*this)[DIMY] = y;
			}
			virtual ~Punkt2D( ) {}
		public:

			NUMERISCH x( ) const { return (*this)[DIMX]; }
			void x( NUMERISCH wert ) { (*this)[DIMX] = wert; }

			NUMERISCH y( ) const { return (*this)[DIMY]; }
			void y( NUMERISCH wert ) { (*this)[DIMY] = wert; }

		public:
			static void Test( ) {

				std::cout << std::endl << AW_FUNKTIONS_NAME  << std::endl << std::endl;
				Punkt2D<NUMERISCH> p1(1,2);
				Punkt2D<NUMERISCH> p2(3,4);
				Punkt2D<NUMERISCH> pc(p1);

				Objekt::testAusgabe( ) << "p1: " << p1 << std::endl;
				Objekt::testAusgabe( ) << "p2: " << p2 << std::endl;
				Objekt::testAusgabe( ) << "pc: " << pc << std::endl;

				assert( p1 == pc );
				assert( p1 != p2 );

				p1 = p2;
				assert( p1.id() != p2.id() );
				assert( p1 == p2 );

				p1.x( 42 );
				assert( p1.x() == 42 );

				std::cout << AW_FUNKTIONS_NAME  << " all test done. " << std::endl << std::endl;

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
