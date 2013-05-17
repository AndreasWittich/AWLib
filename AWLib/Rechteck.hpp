//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Vektor.hpp"
#include "Punkt2D.hpp"
#include "Groesse2D.hpp"

namespace AW {

	using namespace Grundlagen;

	namespace Mathematik {

		template< class NUMERISCH >
		class Rechteck : Objekt {
			friend std::ostream& operator<<(std::ostream& out, const Rechteck&  r) {
				out << "{" << std::endl;
				out << "punkt: " << r._punkt << std::endl;
				out << "groesse: " << r._groesse << std::endl;
				out << "}";
				return out;
			}

		private:
			Punkt2D<NUMERISCH>		_punkt;
			Groesse2D<NUMERISCH>	_groesse;
		public:
			Rechteck() : Objekt() {};
			Rechteck( const Punkt2D<NUMERISCH>& punkt, const Groesse2D<NUMERISCH>& groesse ) : 
				Objekt(),
				_punkt( punkt ),
				_groesse( groesse )
			{
			}
			Rechteck( const NUMERISCH& x, const NUMERISCH& y, const NUMERISCH& w, const NUMERISCH& h ) : 
				Objekt(),
				_punkt( x, y ),
				_groesse( w, h )
			{
			}
		public:
			int operator==( const Rechteck&  rechteck ) {
				if( ! (_punkt == rechteck._punkt) ) return false;
				if( ! (_groesse == rechteck._groesse) ) return false;
				return true;
			}

			int operator!=( const Rechteck&  rechteck ) {
				return !( *this == rechteck );
			}

			Rechteck& operator+=( const Rechteck&  rechteck ) {
				NUMERISCH xMin = std::min( x(), rechteck.x() );
				NUMERISCH yMin = std::min( y(), rechteck.y() );
				NUMERISCH xMax = std::max( x() + w(), rechteck.x() + rechteck.w());
				NUMERISCH yMax = std::max( y() + h(), rechteck.y() + rechteck.h() );
				_punkt = Punkt2D<NUMERISCH>( xMin, yMin );
				_groesse = Groesse2D<NUMERISCH>( xMax - xMin, yMax - yMin );
				return *this;
			}

			Rechteck operator+( const Rechteck&  rechteck ) {
				Rechteck res(*this);
				return res += rechteck;
			}
		public:
			NUMERISCH x() const { return _punkt.x(); }
			void x(const NUMERISCH& wert ) { _punkt.x(wert); }
			NUMERISCH y() const { return _punkt.y(); }
			void y(const NUMERISCH& wert ) { _punkt.y(wert); }
			NUMERISCH w() const { return _groesse.w(); }
			void w( NUMERISCH& wert ) { _groesse.w(wert); }
			NUMERISCH h() const { return _groesse.h(); }
			void h(const NUMERISCH& wert ) { _groesse.h(wert); }

		public:
			static void Test( ) {

				std::cout << std::endl << AW_FUNKTIONS_NAME  << std::endl << std::endl;


				Rechteck<NUMERISCH> r1( 0, 0, 10, 20 );
				Rechteck<NUMERISCH> r2( 100, 200, 30, 40 );
				Rechteck<NUMERISCH> rk( r1 );

				Objekt::testAusgabe( ) << "r1: " << r1 << std::endl;
				Objekt::testAusgabe( ) << "r2: " << r2 << std::endl;
				Objekt::testAusgabe( ) << "rk: " << rk << std::endl;

				assert( r1 != r2 );
				assert( r1 == rk );

				Objekt::testAusgabe( ) << "r1+r2: " << r1+r2 << std::endl;
				Rechteck<NUMERISCH> e( 0, 0, r2.x() + r2.w(), r2.y() + r2.h() );

				assert( (r1+r2) == e );
				assert( Rechteck<NUMERISCH>( 0, 0, r2.x() + r2.w(), r2.y() + r2.h() ) == e );

				r2 = rk;
				assert( r1 == r2 );



				std::cout << AW_FUNKTIONS_NAME  << " all test done. " << std::endl << std::endl;
			}

		};
	}
}
