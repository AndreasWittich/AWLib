//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

#define DEBUG_OBJEKTE

#pragma once
#include <stdint.h>
#include <set>
namespace AW {
	namespace Grundlagen {

		typedef uint64_t ID_TYPE;


		class ObjektIdSet : public std::set< ID_TYPE >
		{

			friend std::ostream& operator<<(std::ostream& out, const ObjektIdSet&  objektSet) {
				std::string sep;

				for( std::set< ID_TYPE >::const_iterator idIterator = objektSet.begin(); idIterator != objektSet.end(); idIterator++ ) {
					out << sep << *idIterator;
					sep = ", ";
				}
				out << std::endl;
				return out;
			}
		public:
			ObjektIdSet() : std::set< ID_TYPE >() {};
			virtual ~ObjektIdSet() {};

		private:

		};

		class Objekt;

		//std::ostream& operator<<(std::ostream&, const ObjektIdSet&);



		class Objekt
		{
			friend std::ostream& operator<<(std::ostream& out, const Objekt&  objekt) {
				;
				std::cout << "Objekt " << (void*) &objekt << " Id: " << objekt.id();
				return out;
			}

		private:
			static ID_TYPE _naechsteId;
#ifdef DEBUG_OBJEKTE
			static ObjektIdSet _lebendeObjekte;
			static ObjektIdSet _vergangeneObjekte;
#endif
		private:
			const ID_TYPE _id;
		public:
			Objekt(void);
			Objekt( const Objekt& objekt );
			virtual ~Objekt(void);
		public:
			Objekt& operator = ( const Objekt& objekt );
		public:
			ID_TYPE id( ) const;
#ifdef DEBUG_OBJEKTE
			static const std::string statusLebendig;
			static const std::string statusVergangen;
			static const std::string statusUngueltig;

			const std::string& status( ) const;
			static const std::string& status( const Objekt& objekt );
			static const std::string& status( const ID_TYPE& id );
			static const ObjektIdSet& lebendeObjekte();
			static const ObjektIdSet& vergangeneObjekte();
#endif

		public:
			static void Test(void);
		};

	}

}
