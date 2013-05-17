//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Objekt.hpp"
#include <fstream>

using namespace AW::Grundlagen;

ID_TYPE Objekt::_naechsteId = 42;

#ifdef DEBUG_OBJEKTE
ObjektIdSet Objekt::_lebendeObjekte = ObjektIdSet();
ObjektIdSet Objekt::_vergangeneObjekte = ObjektIdSet();
#endif

#ifdef AWDEBUG
 std::ostream& Objekt::testAusgabe( ) { return std::cout; }
#else 
 std::ostream& Objekt::testAusgabe( ) {
	 static std::ofstream nullStream( "/dev/null");
	 return nullStream;
 }
#endif

Objekt::Objekt(void) : _id( _naechsteId+=77 ) {
#ifdef DEBUG_OBJEKTE
	_lebendeObjekte.insert( this->_id );
#endif
}
Objekt::Objekt( const Objekt& objekt )  : _id( _naechsteId+=55 ) {
#ifdef DEBUG_OBJEKTE
	_lebendeObjekte.insert( this->_id );
#endif
} // id nicht kopieren
Objekt::~Objekt(void) {
#ifdef DEBUG_OBJEKTE
	_vergangeneObjekte.insert( this->_id );
	_lebendeObjekte.erase( this->_id );
#endif
}
Objekt& Objekt::operator = ( const Objekt& objekt )  { return * this; }  // id nicht kopieren
ID_TYPE Objekt::id( ) const { return _id; }
#ifdef DEBUG_OBJEKTE
const std::string Objekt::statusLebendig = "Lebendig";
const std::string Objekt::statusVergangen = "Vergangen";
const std::string Objekt::statusUngueltig = "Ungueltig";

const std::string& Objekt::status( ) const  { return Objekt::status( id() ); };
const std::string& Objekt::status( const Objekt& objekt )  { return Objekt::status( objekt.id() ); }
const std::string& Objekt::status( const ID_TYPE& id )  {
	if( _lebendeObjekte.find( id ) != _lebendeObjekte.end() ) return Objekt::statusLebendig;
	if( _vergangeneObjekte.find( id ) != _vergangeneObjekte.end() ) return Objekt::statusVergangen;
	return statusUngueltig;
}
const ObjektIdSet& Objekt::lebendeObjekte() { return _lebendeObjekte; } 
const ObjektIdSet& Objekt::vergangeneObjekte() { return _vergangeneObjekte; }
#endif

void Objekt::Test(void) {
	std::cout << std::endl << AW_FUNKTIONS_NAME  << std::endl << std::endl;

#ifdef DEBUG_OBJEKTE
	Objekt * errObj;
	{

		Objekt a;
		Objekt b;
		Objekt c;

		Objekt::testAusgabe( ) << "a: " << a << " - " << a.status() << std::endl;
		assert( a.status() == Objekt::statusLebendig );

		Objekt::testAusgabe( ) << "b: " << c << " - " << b.status() << std::endl;
		assert( c.status() == Objekt::statusLebendig );

		Objekt::testAusgabe( ) << "c: " << c << " - " << c.status() << std::endl;
		assert( b.status() == Objekt::statusLebendig );

		errObj = &a;
	}
	Objekt::testAusgabe( ) << "stack error: " << *errObj << " - " << errObj->status() << std::endl;
	assert( errObj->status() != Objekt::statusLebendig );

#ifndef _WIN32
	errObj = (Objekt*) 0x7fffffff0000;
#else
	errObj = (Objekt*) 0x0000FFFF;
#endif
	Objekt::testAusgabe( ) << "adress error: " << *errObj << " - " << errObj->status() << std::endl;
	assert( errObj->status() != Objekt::statusLebendig );

	errObj = new Objekt();
	Objekt::testAusgabe( ) << "new : " << *errObj << " - " << errObj->status() << std::endl;
	assert( errObj->status() == Objekt::statusLebendig );

	delete errObj;
	Objekt::testAusgabe( ) << "deleted error : " << *errObj << " - " << errObj->status() << std::endl;
	assert( errObj->status() != Objekt::statusLebendig );
#endif
	std::cout << AW_FUNKTIONS_NAME  << " all test done. " << std::endl << std::endl;
}

