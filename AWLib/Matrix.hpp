//////////////////////////////////////////////////////////////////////////////
//
// Author: Andreas Wittich
// Copyright: 2013
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Objekt.hpp"
#include "Vektor.hpp"
#include <string.h>

namespace AW {

	using namespace Grundlagen;

	namespace Mathematik {


		template< DIMENSION DimX, DIMENSION DimY, class NUMERISCH >
		class Matrix;

		template< DIMENSION DimX, DIMENSION DimY, class NUMERISCH >
		Matrix<DimY,DimY,NUMERISCH> operator*( const Matrix<DimX,DimY,NUMERISCH>&, const Matrix<DimY,DimX,NUMERISCH>& );

		template< DIMENSION DimY, DIMENSION DimX, class NUMERISCH >
		Matrix<DimX,DimX,NUMERISCH> operator*( const Matrix<DimY,DimX,NUMERISCH>&, const Matrix<DimX,DimY,NUMERISCH>& );

		template< DIMENSION DimX, DIMENSION DimY, class NUMERISCH >
		class Matrix : public Objekt
		{

			typedef Matrix< DimX, DimY , NUMERISCH > MatrixType;

			friend std::ostream& operator<<(std::ostream& out, const MatrixType&  matrix) {
				out << "{" << std::endl;
				for( uint8_t y = 0; y < matrix.dimensionY(); y++ ) {
					if( sizeof( NUMERISCH ) == 1 ) {
						for( uint8_t x = 0; x < matrix.dimensionX(); x++ ) 
							out << (int) matrix._data[y][x] << ( ( (x+1) < matrix.dimensionX() ) ? "\t" : "" );
					} else {
						for( uint8_t x = 0; x < matrix.dimensionX(); x++ ) 
							out << matrix._data[y][x] << ( ( (x+1) < matrix.dimensionX() ) ? "\t" : "" );
					}
					out << std::endl;
				}
				out << "}";
				return out;
			}
			friend MatrixType operator*( const NUMERISCH& sklar, const MatrixType& matrix ) {
				MatrixType res(matrix);
				for( uint8_t y = 0; y < res._dimensionY; y++ ) {
					for( uint8_t x = 0; x < res._dimensionX; x++ ) {
						res._data[y][x] *= sklar;
					}
				}
				return res;
			}
		private:
			const DIMENSION _dimensionX;
			const DIMENSION _dimensionY;
			NUMERISCH _data[DimY][DimX];
		private:
			void init() {
				for( uint8_t y = 0; y < _dimensionY; y++ ) {
					for( uint8_t x = 0; x < _dimensionX; x++ ) {
						_data[y][x] = (x==y) ? 1 : 0;
					}
				}
			}

		public:

			Matrix(void) : 
				Objekt(),
				_dimensionX(DimX),
				_dimensionY(DimY),
				_data()
			{
				init();
			}

			Matrix( NUMERISCH data[DimY][DimX] ) : 
				Objekt(),
				_dimensionX(DimX),
				_dimensionY(DimY)
			{
				for( uint8_t y = 0; y < DimY; y++ ) {
					for( uint8_t x = 0; x < DimX; x++ ) {
						_data[y][x] = data[y][x];
					}
				}
			}

			virtual ~Matrix(void)
			{
			}

			MatrixType& operator=( const MatrixType&  matrix ) {
				if( this == &matrix ) return *this;
				::memcpy( &_data[0][0], &matrix._data[0][0], sizeof( _data ) );
				return *this;
			}

			int operator==( const MatrixType&  matrix ) {
				return ( ::memcmp( &_data[0][0], &matrix._data[0][0], sizeof( _data ) ) == 0);
			}

			int operator!=( const MatrixType&  matrix ) {
				return !(*this == matrix);
			}

			MatrixType& operator+=( const MatrixType&  matrix ) {
				for( uint8_t y = 0; y < DimY; y++ ) {
					for( uint8_t x = 0; x < DimX; x++ ) {
						_data[y][x] += matrix._data[y][x];
					}
				}
				return *this;
			}

			MatrixType operator+( const MatrixType&  matrix ) const {
				MatrixType res(*this);
				return res += matrix;
			}

			MatrixType& operator-=( const MatrixType&  matrix ) {
				for( uint8_t y = 0; y < DimY; y++ ) {
					for( uint8_t x = 0; x < DimX; x++ ) {
						_data[y][x] -= matrix._data[y][x];
					}
				}
				return *this;
			}

			MatrixType operator-( const MatrixType&  matrix ) {
				MatrixType res(*this);
				return res -= matrix;
			}

			Matrix<DimY,DimY,NUMERISCH> operator*( const Matrix<DimY,DimX,NUMERISCH>&  matrix ) const;

			MatrixType& operator*=( const NUMERISCH&  skalar ) {
				for( uint8_t y = 0; y < DimY; y++ ) {
					for( uint8_t x = 0; x < DimX; x++ ) {
						_data[y][x] *= skalar;
					}
				}
				return *this;
			}

			MatrixType operator*( const NUMERISCH&  skalar ) {
				MatrixType res(*this);
				return res *= skalar;
			}

		public:
			NUMERISCH operator[]( const Punkt2DU pos ) const { 
				if( pos.x() >= DimX ) throw typename Vektor< DimX,NUMERISCH >::Fehler( "ungueltige X Dimenson.", pos.x() );
				if( pos.y() >= DimY ) throw typename Vektor< DimY,NUMERISCH >::Fehler( "ungueltige Y Dimenson.", pos.y() );
				return _data[pos.y()][pos.x()]; 
			}

			NUMERISCH& operator[]( const Punkt2DU pos ) { 
				if( pos.x() >= DimX ) throw typename Vektor< DimX,NUMERISCH >::Fehler( "ungueltige X Dimenson.", pos.x() );
				if( pos.y() >= DimY ) throw typename Vektor< DimY,NUMERISCH >::Fehler( "ungueltige Y Dimenson.", pos.y() );
				return _data[pos.y()][pos.x()]; 
			}

		public:
			DIMENSION dimensionX( ) const { return _dimensionX; }
			DIMENSION dimensionY( ) const { return _dimensionY; }

		public:
			static void Test( ) {

				std::cout << std::endl << AW_FUNKTIONS_NAME  << std::endl << std::endl;
				MatrixType mat0;
				NUMERISCH k1[DimY][DimX] =  {
					{ 1, 2, 3 },
					{ 4, 5, 6 },
					{ 7, 8, 9 }
				};
				MatrixType mat1( k1 );

				NUMERISCH k2[DimY][DimX] =  {
					{ 11, 12, 13 },
					{ 21, 22, 23 },
					{ 31, 32, 33 }
				};
				MatrixType mat2( k2 );


				MatrixType matK( mat1 );

				Objekt::testAusgabe( ) << "mat0: = " << mat0 << std::endl;

				Objekt::testAusgabe( ) << "mat1: = " << mat1 << std::endl;

				Objekt::testAusgabe( ) << "mat2: = " << mat2 << std::endl;

				Objekt::testAusgabe( ) << "matK: = " << matK << std::endl;

				matK = mat2;

				Objekt::testAusgabe( ) << "matK: = " << matK << std::endl;

				Matrix matSum( mat1 + mat2 );

				for( uint16_t y = 0; y < DimY; y++ ) {
					for( uint16_t x = 0; x < DimX; x++ ) {
						assert( matSum[Punkt2DU(x,y)] == ( mat1[Punkt2DU(x,y)] + mat2[Punkt2DU(x,y)] ) );
					}
				}

				Objekt::testAusgabe( ) << "mat1 + mat2: = " << mat1 + mat2 << std::endl;


				{
					double d1[2][3] =  {
						{ 1, 2, 3 },
						{ 4, 5, 6 }
					};
					Matrix<3,2,double> mat1( d1 );

					double d2[3][2] =  {
						{ 6, -1 },
						{ 3, 2 },
						{ 0, -3 }
					};
					Matrix<2,3,double> mat2( d2 );

					double dE[2][2] =  {
						{ 12, -6 },
						{ 39, -12 }
					};
					Matrix<2,2,double> matE( dE );


					Matrix<2,2,double> mulMat;

					mulMat = mat1*mat2;

					Objekt::testAusgabe( ) << "mat1: = " << mat1 << std::endl;
					Objekt::testAusgabe( ) << "mat2: = " << mat2 << std::endl;
					Objekt::testAusgabe( ) << "*     = " << mulMat << std::endl;

					assert( matE == mulMat );


					Objekt::testAusgabe( ) << "2*mat1: = " << 2*mat1 << std::endl;
					Objekt::testAusgabe( ) << "mat1*2: = " << mat1*2 << std::endl;

					assert( 2*mat1 == mat1*2 );

					mat1 *= 2;
					Objekt::testAusgabe( ) << "mat1: *= 2" << mat1 << std::endl;
				}

				std::cout << AW_FUNKTIONS_NAME  << " all test done. " << std::endl << std::endl;
			}

		};

		template< DIMENSION DimX, DIMENSION DimY, class NUMERISCH > 
		Matrix<DimY,DimY,NUMERISCH> Matrix<DimX,DimY,NUMERISCH>::operator*( const Matrix<DimY,DimX,NUMERISCH>&  matrix ) const {
			Matrix<DimY,DimY,NUMERISCH> res;
			for( uint8_t y = 0; y < DimY; y++ ) {
				for( uint8_t x = 0; x < DimY; x++ ) {
					double wert = 0;
					for( uint8_t n = 0; n < DimX; n++ ) {
						//Objekt::testAusgabe( ) << " "<< _data[y][n] << " * " << matrix._data[n][x] << " ";
						wert += (*this)[Punkt2DU(n,y)] * matrix[Punkt2DU(x,n)];
					}
					res[Punkt2DU(x,y)] = wert;
				}
				//Objekt::testAusgabe( ) << std::endl;
			}
			return res;
		}
	}
}
