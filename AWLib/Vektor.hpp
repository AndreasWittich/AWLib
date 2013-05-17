//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

#pragma once 


#include "Objekt.hpp"
#include <assert.h>
#include <typeinfo>
#include <cstring>
#include <sstream>

namespace AW {

using namespace Grundlagen;

namespace Mathematik {

typedef uint8_t DIMENSION;

static const DIMENSION DIM1 = 1;
static const DIMENSION DIM2 = 2;
static const DIMENSION DIM3 = 3;

template< DIMENSION Dim, class NUMERISCH >
class Vektor;
template< class NUMERISCH >
class Punkt2D;
template< class NUMERISCH >
class Groesse2D;

template< DIMENSION Dim, class NUMERISCH >
class Vektor : public Objekt
{
	friend class Punkt2D<NUMERISCH>;
	friend class Groesse2D<NUMERISCH>;
private:
	const DIMENSION _dimension;
	NUMERISCH _koordinaten[Dim];
public:
	typedef Vektor< Dim , NUMERISCH > VektorType;
	friend std::ostream& operator<<(std::ostream& out, const VektorType&  vektor) {
		out << "{\t";
		if( sizeof( NUMERISCH ) == 1 ) {
			for( uint8_t d = 0; d < vektor.dimension(); d++ ) out << (int) vektor[d] << ( ( (d+1) < vektor.dimension() ) ? "\t" : "" );
		} else {
			for( uint8_t d = 0; d < vektor.dimension(); d++ ) out << vektor[d] << ( ( (d+1) < vektor.dimension() ) ? "\t" : "" );
		}
		out << " }";
		return out;
	}
public:
	class Fehler : public std::exception {
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
		Fehler( ) : exception() { }
		Fehler( const char * const nachricht ) : exception(  ) {
			_details = nachricht;
		}
		Fehler( const char * const nachricht, DIMENSION dim ) : exception( ) {
			_details = nachricht;
			std::stringstream ss;
			ss << " (Dimenson: ";
			ss << (int) dim;
			ss << ") ";
			_details += ss.str();
		}
		virtual ~Fehler() throw() {}
	};

	public:
	Vektor(void) :
		Objekt(),
		_dimension(Dim),
		_koordinaten()
	{
	}

	Vektor( NUMERISCH koordinaten[Dim] ) :
		Objekt(),
		_dimension(Dim)
	{
		for( DIMENSION n = 0; n < Dim; n++ ) {
			(*this)[n] = koordinaten[n];
		};
	}



	virtual ~Vektor(void) {
	}

	VektorType& operator=( const VektorType&  vektor ) {
		if( this == &vektor ) return *this;
		for( DIMENSION n = 0; n < Dim; n++ ) {
			(*this)[n]  = vektor[n];
		}
		return *this;
	}

	NUMERISCH operator[](DIMENSION d) const {
		if( d >= Dim ) throw Fehler( "ungueltige Dimenson.", d );
		return _koordinaten[d];
	}

	NUMERISCH& operator[](DIMENSION d) {
		if( d >= Dim ) throw Fehler( "ungueltige Dimenson.", d );
		return _koordinaten[d];
	}

	int operator==( const VektorType&  vektor ) const {
		for( DIMENSION n = 0; n < Dim; n++ ) {
			if( ! (_koordinaten[n] == vektor[n]) ) return false;
		}
		return true;
	}

	int operator!=( const VektorType&  vektor ) const {
		return !( *this == vektor );
	}

	VektorType& operator+=( const VektorType&  vektor ) {
		for( DIMENSION n = 0; n < Dim; n++ ) {
			_koordinaten[n] += vektor[n];
		}
		return *this;
	}

	VektorType operator+( const VektorType&  vektor ) const {
		VektorType res(*this);
		return res += vektor;
	}

	VektorType& operator-=( const VektorType&  vektor ) {
		for( DIMENSION n = 0; n < Dim; n++ ) {
			_koordinaten[n] += vektor[n];
		}
		return *this;
	}

	VektorType operator-( const VektorType&  vektor ) const {
		VektorType res(*this);
		return res -= vektor;
	}

	NUMERISCH operator*( const VektorType&  vektor ) const {
		NUMERISCH res(0);
		for( DIMENSION n = 0; n < Dim; n++ ) {
			res += (_koordinaten[n] * vektor[n]);
		}
		return res;
	}

	VektorType& operator*=( const NUMERISCH&  skalar ) {
		for( DIMENSION n = 0; n < Dim; n++ ) {
			_koordinaten[n] *= skalar;
		}
		return *this;
	}

	VektorType operator*( const NUMERISCH&  skalar ) const {
		VektorType res(*this);
		return res *= skalar;
	}

	VektorType& operator/=( const NUMERISCH&  skalar ) {
		for( DIMENSION n = 0; n < Dim; n++ ) {
			_koordinaten[n] /= skalar;
		}
		return *this;
	}

	VektorType operator/( const NUMERISCH&  skalar ) const {
		VektorType res(*this);
		return res /= skalar;
	}

	operator std::string () {
		std::stringstream ss;
		ss << (*this);
		return ss.str();
	}


	DIMENSION dimension( ) const { return _dimension; }

	public:
	static void Test( ) {

		std::cout << std::endl << AW_FUNKTIONS_NAME  << std::endl << std::endl;

		//VektorType v1((NUMERISCH)1,(NUMERISCH)2,(NUMERISCH)3);
		//VektorType v2((NUMERISCH)5,(NUMERISCH)7,(NUMERISCH)13);
		NUMERISCH ke[Dim] =  { 1, 2 };
		VektorType ve( ke );
		Objekt::testAusgabe( ) << "\t" << ve << std::endl;

		NUMERISCH k1[3] =  { 1, 2, 3 };
		NUMERISCH k2[3] =  { 5, 7, 13 };
		NUMERISCH k3[3] =  {-7, 8, 9 };
		NUMERISCH k4[3] =  { 6, 9, 16 };


		VektorType v1( k1 );
		VektorType v2( k2 );

		Objekt::testAusgabe( ) << "\t" << (std::string) v1 << std::endl;
		Objekt::testAusgabe( ) << "\t" << v1 << std::endl;
		Objekt::testAusgabe( ) << "+\t" << v2 << std::endl;

		VektorType x = v1+v2;
		VektorType e( k4 );
		Objekt::testAusgabe( ) << "=\t" << x << std::endl<< std::endl;
		assert( x == e );

		v1 = VektorType( k1 );
		v2 = VektorType( k3 );

		Objekt::testAusgabe( ) << "\t" << v1 << std::endl;
		Objekt::testAusgabe( ) << "*\t" << v2 << std::endl;
		Objekt::testAusgabe( ) << "=\t" << v1*v2 << std::endl << std::endl;
		if( Dim == 3 ) {
			assert( v1*v2 == 36 );
		}

		VektorType c( v1 );

		assert( c.id() != v1.id() );
		assert( c == v1 );

		try {
			Objekt::testAusgabe( ) << typeid( NUMERISCH ).name() << " x = vektor[-1]" << std::endl;
			NUMERISCH x = v1[-1];
			Objekt::testAusgabe( ) << typeid( NUMERISCH ).name() << x << std::endl;

			assert( ! "Fehler erwartet!" );
		}
		catch( const Fehler& e ) {
			Objekt::testAusgabe( ) << "Erwarteter Fehler: " << e.what() << std::endl;
		}

		try {
			Objekt::testAusgabe( ) << typeid( NUMERISCH ).name() << "vektor[-1] = 0" << std::endl;
			v1[-1] = 0;
			assert( ! "Fehler erwartet!" );
		}
		catch( const Fehler& e ) {
			Objekt::testAusgabe( ) << "Erwarteter Fehler: " << e.what() << std::endl;
		}
		if( Dim == 3 ) {
			NUMERISCH f(2);
			VektorType vMul = v1 * f;
			NUMERISCH kMul[3] =  { v1[0] * f, v1[1] * f, v1[2] * f };
			Objekt::testAusgabe( ) << "\t" << v1 << std::endl;
			Objekt::testAusgabe( ) << "*\t" << f << std::endl;
			Objekt::testAusgabe( ) << "=\t" << v1*f << std::endl << std::endl;
			assert( v1*f == VektorType( kMul ) );

			VektorType vDiv = v1 * f;
			NUMERISCH kDiv[3] =  { v1[0] / f, v1[1] / f, v1[2] / f  };
			Objekt::testAusgabe( ) << "\t" << v1 << std::endl;
			Objekt::testAusgabe( ) << "/\t" << f << std::endl;
			Objekt::testAusgabe( ) << "=\t" << v1/f << std::endl << std::endl;
			assert( v1/f == VektorType( kDiv ) );
		}
		std::cout << AW_FUNKTIONS_NAME  << " all test done. " << std::endl << std::endl;
	}
};


}
}
