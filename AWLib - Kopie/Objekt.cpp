//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Objekt.hpp"

using namespace AW::Grundlagen;

ID_TYPE Objekt::_naechsteId = 42;

#ifdef DEBUG_OBJEKTE
ObjektIdSet Objekt::_lebendeObjekte = ObjektIdSet();
ObjektIdSet Objekt::_vergangeneObjekte = ObjektIdSet();
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
	std::cout << std::endl << __FUNCTION__  << std::endl << std::endl;

#ifdef DEBUG_OBJEKTE
	Objekt * errObj;
	{

		Objekt a;
		Objekt b;
		Objekt c;

		std::cout << "a: " << a << " - " << a.status() << std::endl;
		assert( a.status() == Objekt::statusLebendig );

		std::cout << "b: " << c << " - " << b.status() << std::endl;
		assert( c.status() == Objekt::statusLebendig );

		std::cout << "c: " << c << " - " << c.status() << std::endl;
		assert( b.status() == Objekt::statusLebendig );

		errObj = &a;
	}
	std::cout << "stack error: " << *errObj << " - " << errObj->status() << std::endl;
	assert( errObj->status() != Objekt::statusLebendig );

	errObj = (Objekt*) 0x0000FFFF;
	std::cout << "adress error: " << *errObj << " - " << errObj->status() << std::endl;
	assert( errObj->status() != Objekt::statusLebendig );

	errObj = new Objekt();
	std::cout << "new : " << *errObj << " - " << errObj->status() << std::endl;
	assert( errObj->status() == Objekt::statusLebendig );

	delete errObj;
	std::cout << "deleted error : " << *errObj << " - " << errObj->status() << std::endl;
	assert( errObj->status() != Objekt::statusLebendig );
#endif
	std::cout << __FUNCTION__  << " all test done. " << std::endl << std::endl;
}

