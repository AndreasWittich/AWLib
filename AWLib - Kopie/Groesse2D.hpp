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
		class Groesse2D : public Vektor< DIM2, NUMERISCH > {
			friend std::ostream& operator<<(std::ostream& out, const Groesse2D&  g) {
				out << "{\t";
				if( sizeof( NUMERISCH ) == 1 ) {
					out << "W: " <<(int) g.w() << "\t H: " << (int) g.h();
				} else {
					out << "W: " << g.w() << "\t H: " << g.h();
				}
				out << " }";
				return out;
			}

		public:
			virtual class Fehler : public std::invalid_argument {
			private:
				std::string _details;
			public:
				virtual const char* what() const throw()
				{
					static std::string m( __FUNCTION__ );
					m += " - ";
					m += _details;
					m +=  std::exception::what();
					return  m.c_str();
				}
				Fehler( ) : invalid() { }
				Fehler( const char * const nachricht ) : invalid_argument( nachricht ) { }
				Fehler( const char * const nachricht, NUMERISCH wert ) : invalid_argument( nachricht ) { 
					std::stringstream ss;
					ss << " (wert: ";
					ss << wert;
					ss << ") ";
					_details = ss.str();
				}
			};
		public:
			static const DIMENSION DIMX;
			static const DIMENSION DIMY;
		public:
			Groesse2D( ) : Vektor< DIM2, NUMERISCH >() {}
			Groesse2D( NUMERISCH w, NUMERISCH h ) : Vektor< DIM2, NUMERISCH >() {
				if( w < 0 ) throw Fehler( "Weite muss groesser 0 sein.", w );
				if( h < 0 ) throw Fehler( "Hoehe muss groesser 0 sein.", h );
				_koordinaten[DIMX] = w;
				_koordinaten[DIMY] = h;
			}
			virtual ~Groesse2D( ) {}
		public:

			NUMERISCH w( ) const { return _koordinaten[DIMX]; }
			void w( NUMERISCH wert ) { _koordinaten[DIMX] = wert; }

			NUMERISCH h( ) const { return _koordinaten[DIMY]; }
			void h( NUMERISCH wert ) { _koordinaten[DIMY] = wert; }

		public:
			static void Test( ) {

				std::cout << std::endl << __FUNCTION__  << std::endl << std::endl;
				Groesse2D<NUMERISCH> g1(1,2);
				Groesse2D<NUMERISCH> g2(3,4);
				Groesse2D<NUMERISCH> gc(g1);

				std::cout << "g1: " << g1 << std::endl;
				std::cout << "g2: " << g2 << std::endl;
				std::cout << "gc: " << gc << std::endl;

				assert( g1 == gc );
				assert( g1 != g2 );

				g1 = g2;
				assert( g1.id() != g2.id() );
				assert( g1 == g2 );

				NUMERISCH kleinerNull = -1;
				if( kleinerNull < 0 ) { // test nicht unsigned
					try {
						Groesse2D<NUMERISCH> ex( -1, 0 );
						assert( ! "Fehler erwartet!" );
					}
					catch( const Fehler& e ) {
						std::cout << "Erwarteter Fehler: " << e.what() << std::endl;
					}
					try {
						Groesse2D<NUMERISCH> ex( 0, -1 );
						assert( ! "Fehler erwartet!" );
					}
					catch( const Fehler& e ) {
						std::cout << "Erwarteter Fehler: " << e.what() << std::endl;
					}
				}
				std::cout << __FUNCTION__  << " all test done. " << std::endl << std::endl;
			}

		};
		template< class NUMERISCH >
		const DIMENSION Groesse2D<NUMERISCH>::DIMX = 0;
		template< class NUMERISCH >
		const DIMENSION Groesse2D<NUMERISCH>::DIMY = 1;

	}
}
