//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Vektor.hpp"
#include <stdexcept>

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
			class Fehler : public std::invalid_argument {
			private:
				std::string _details;
			public:
				virtual const char* what() const throw()
				{
					static std::string m( AW_FUNKTIONS_NAME );
					m += " - ";
					m += _details;
					m +=  std::exception::what();
					return  m.c_str();
				}
				Fehler( ) : std::invalid_argument("") { }
				Fehler( const char * const nachricht ) : invalid_argument( nachricht ) { }
				Fehler( const char * const nachricht, NUMERISCH wert ) : invalid_argument( nachricht ) { 
					std::stringstream ss;
					ss << " (wert: ";
					ss << wert;
					ss << ") ";
					_details = ss.str();
				}
				virtual ~Fehler() throw() {}
			};
		public:
			static const DIMENSION DIMX;
			static const DIMENSION DIMY;
		public:
			Groesse2D( ) : Vektor< DIM2, NUMERISCH >() {}
			Groesse2D( NUMERISCH w, NUMERISCH h ) : Vektor< DIM2, NUMERISCH >() {
				if( w < 0 ) throw Fehler( "Weite muss groesser 0 sein.", w );
				if( h < 0 ) throw Fehler( "Hoehe muss groesser 0 sein.", h );
				(*this)[DIMX] = w;
				(*this)[DIMY] = h;
			}
			virtual ~Groesse2D( ) {}
		public:

			NUMERISCH w( ) const { return (*this)[DIMX]; }
			void w( NUMERISCH wert ) { (*this)[DIMX] = wert; }

			NUMERISCH h( ) const { return (*this)[DIMY]; }
			void h( NUMERISCH wert ) { (*this)[DIMY] = wert; }

		public:
			static void Test( ) {

				std::cout << std::endl << AW_FUNKTIONS_NAME  << std::endl << std::endl;
				Groesse2D<NUMERISCH> g1(1,2);
				Groesse2D<NUMERISCH> g2(3,4);
				Groesse2D<NUMERISCH> gc(g1);

				Objekt::testAusgabe( ) << "g1: " << g1 << std::endl;
				Objekt::testAusgabe( ) << "g2: " << g2 << std::endl;
				Objekt::testAusgabe( ) << "gc: " << gc << std::endl;

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
						Objekt::testAusgabe( ) << "Erwarteter Fehler: " << e.what() << std::endl;
					}
					try {
						Groesse2D<NUMERISCH> ex( 0, -1 );
						assert( ! "Fehler erwartet!" );
					}
					catch( const Fehler& e ) {
						Objekt::testAusgabe( ) << "Erwarteter Fehler: " << e.what() << std::endl;
					}
				}
				Objekt::testAusgabe( ) << AW_FUNKTIONS_NAME  << " all test done. " << std::endl << std::endl;
			}

		};
		template< class NUMERISCH >
		const DIMENSION Groesse2D<NUMERISCH>::DIMX = 0;
		template< class NUMERISCH >
		const DIMENSION Groesse2D<NUMERISCH>::DIMY = 1;

	}
}
