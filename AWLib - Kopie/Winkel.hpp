//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Objekt.hpp"
#include <limits>
#include <math.h>

namespace AW {
	namespace Mathematik {

		using namespace Grundlagen;

		typedef double Bogenmass;
		typedef double Grad;

		class Winkel : public Objekt 
		{
			friend std::ostream& operator<<(std::ostream& out, const Winkel&  winkel) {
				out << winkel.grad() << " Grad";
				return out;
			}

		public:
			static const double PI;
		public:
			static double GrandInBogenmass( double grad ) {
				return grad * PI / 180.0;
			}
			static double BogenmassInGrand( double bogenmass ) {
				return bogenmass * 180.0 / PI;
			}
		private:
			double _ankathete;
			double _gegenkathete;
			double _hypotenuse;
			double _sinus;
			double _kosinus;
			double _tangens;
			double _bogenmass;
			double _grad;

		public:
			Winkel(void) : 
				Objekt(),
				_ankathete(0.0),
				_gegenkathete(1.0),
				_hypotenuse(1.0),
				_sinus(1.0),
				_kosinus(0.0),
				_tangens(0.0),
				_bogenmass(0.0),
				_grad(0.0)
			{
			}

			Winkel(Grad grad) : 
				Objekt(),
				_ankathete(std::numeric_limits<double>::infinity()),
				_gegenkathete(std::numeric_limits<double>::infinity()),
				_hypotenuse(std::numeric_limits<double>::infinity()),
				_sinus(std::numeric_limits<double>::infinity()),
				_kosinus(std::numeric_limits<double>::infinity()),
				_tangens(std::numeric_limits<double>::infinity()),
				_bogenmass(std::numeric_limits<double>::infinity()),
				_grad(std::numeric_limits<double>::infinity())
			{
				if( grad < 0 ) {
					while( grad <= -360 ) grad += 360;
					if( grad < 0 ) grad += 360;
				} else {
					while( grad >= 360 ) grad -= 360;
				}
				_grad = grad;
				_bogenmass = GrandInBogenmass( _grad );
				_sinus = sin( _bogenmass );
				if( fabs( _sinus ) < 0.00000000001L ) _sinus = 0.0;
				_kosinus = cos( _bogenmass );
				if( fabs( _kosinus ) < 0.00000000001L ) _kosinus = 0.0;
				if( _kosinus )
					_tangens = _sinus / _kosinus;
				else 
					_tangens = std::numeric_limits<double>::infinity();
				if( _tangens > 1.e10 ) _tangens = std::numeric_limits<double>::infinity();

				_ankathete = _kosinus;
				_gegenkathete = _sinus;
				_hypotenuse = 1.0;
			}

			Winkel(double ankathete, double gegenkathete) : 
				Objekt(),
				_ankathete(ankathete),
				_gegenkathete(gegenkathete),
				_hypotenuse(std::numeric_limits<double>::infinity()),
				_sinus(std::numeric_limits<double>::infinity()),
				_kosinus(std::numeric_limits<double>::infinity()),
				_tangens(std::numeric_limits<double>::infinity()),
				_bogenmass(std::numeric_limits<double>::infinity()),
				_grad(std::numeric_limits<double>::infinity())
			{
				_hypotenuse = sqrt( _ankathete * _ankathete + _gegenkathete * _gegenkathete );
				_sinus = _gegenkathete / _hypotenuse;
				_kosinus = _ankathete / _hypotenuse;

				if( _ankathete ) 
					_tangens = _gegenkathete / _ankathete;
				else
					_tangens = std::numeric_limits<double>::infinity();

				//std::cout << "sin: " << _sinus << " cos: " << _kosinus << std::endl;
				//std::cout << "asin: " << asin( _sinus ) << " acos: " << acos( _kosinus ) << std::endl;


				if( _sinus >= 0 ) { 
					if( _kosinus >= 0 ) {	// Quadrant 1
						_bogenmass = asin( _sinus );
						//std::cout << "Q1" << std::endl;
					} else {				// Quadrant 2
						_bogenmass = acos( _kosinus );
						//std::cout << "Q2" << std::endl;
					}
				} else {
					if( _kosinus < 0 ) {	// Quadrant 3
						_bogenmass = PI - asin( _sinus );
						//std::cout << "Q3" << std::endl;
					} else {				// Quadrant 4
						_bogenmass = 2.0*PI + asin( _sinus );
						//std::cout << "Q4" << std::endl;
					}
				}
				_grad = BogenmassInGrand( _bogenmass );
			}

			virtual ~Winkel(void) {}
		public:
			int operator==(const Winkel& winkel) const {
				return _ankathete == winkel._ankathete && _gegenkathete == winkel._gegenkathete;
			}
			int operator!=(const Winkel& winkel) const {
				return ! ((*this) == winkel);
			}
		public:
			double ankathete() const { return _ankathete; }
			double gegenkathete() const { return _gegenkathete; }
			double hypotenuse() const { return _hypotenuse; }
			double sinus() const { return _sinus; }
			double kosinus() const { return _kosinus; }
			double tangens() const { return _tangens; }
			double bogenmass() const { return _bogenmass; }
			double grad() const { return _grad; }

		public:
			static void Test(void);

		};

	}
}