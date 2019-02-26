#ifndef MATRIX2_H
#define MATRIX2_H
#include <stdio.h>
#include "Vector.h"
#include <iostream>

namespace MATH {
	class Mat3 {
	private:
		float m[3][3];
	public:
		inline Mat3(float r1c1, float r1c2, float r1c3,
			float r2c1, float r2c2, float r2c3,
			float r3c1, float r3c2, float r3c3) {
			m[0][0] = r1c1; m[0][1] = r1c2; m[0][2] = r1c3;
			m[1][0] = r2c1; m[1][1] = r2c2; m[1][2] = r2c3;
			m[2][0] = r3c1; m[2][1] = r3c2; m[2][2] = r3c3;
		}

		inline void LoadIdentity() {
			m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
			m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
			m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
		}

		inline Mat3(float n = 1.0f) {
			if (n == 1.0f) {
				LoadIdentity();
			}
			else {
				m[0][0] = n; m[0][1] = n; m[0][2] = n;
				m[1][0] = n; m[1][1] = n; m[1][2] = n;
				m[2][0] = n; m[2][1] = n; m[2][2] = n;
			}
		}

		inline Mat3 operator *(const Mat3& n) {
			Mat3 result;
			float sum = 0.0f;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						sum += m[i][k] * n.m[k][j];
					}
					result.m[i][j] = sum;
					sum = 0.0f;
				}
			}
			return result;
		}

		inline Mat3 operator+(const Mat3& n) {
			Mat3 result;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					result.m[i][j] = m[i][j] + n.m[i][j];
				}
			}
			return result;
		}

		inline Mat3 operator-(const Mat3& n) {
			Mat3 result;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					result.m[i][j] = m[i][j] - n.m[i][j];
				}
			}
			return result;
		}

		inline Vec3 operator*(const Vec3& v) {
			return Vec3(
				m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
				m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
				m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
			);
		}




		//stuff A.T did 
		inline const Mat3 operator*(const Vec3& v) const
		{
			Mat3 result;

			//this should get matrix the col and times it to vector row 
			for (int i = 0; i < 3; i++) {//row 
				for (int j = 0; j < 3; j++) {//col

					float x = v[0] * m[i][j] + v[1] * m[i][j] + v[2] * m[i][j];
					float y = v[0] * m[i][j] + v[1] * m[i][j] + v[2] * m[i][j];
					float z = v[0] * m[i][j] + v[1] * m[i][j] + v[2] * m[i][j];
					result = x, y, z;
					return result;

				}
			}

		}




		//stuff A.T did 
		inline const Vec3 operator*(const Mat3& m_) const
		{
			Vec3 result;
			Vec3 v;

				float x = v[0] * m_.m[0][0] + v[1] * m_.m[1][0] + v[2] * m_.m[2][0];
				float y = v[0] * m_.m[0][1] + v[1] * m_.m[1][1] + v[2] * m_.m[2][1];
				float z = v[0] * m_.m[0][2] + v[1] * m_.m[1][2] + v[2] * m_.m[2][2];
				
				result = x, y, z;
				return result;

			
		}
	



		static Mat3 inverse3(const Mat3 & m)
		{
			float determinate = 0.0f;
			Mat3 inMatrix;


			for (int i = 0; i < 3; i++)
				determinate = determinate + (m.m[0][i] * (m.m[1][(i + 1) % 3] * m.m[2][(i + 2) % 3] - m.m[1][(i + 2) % 3] * m.m[2][(i + 1) % 3]));

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++)

					inMatrix.m[i][j] = ((m.m[(j + 1) % 3][(i + 1) % 3] * m.m[(j + 2) % 3][(i + 2) % 3]) - (m.m[(j + 1) % 3][(i + 2) % 3] * m.m[(j + 2) % 3][(i + 1) % 3])) / determinate;


			}

			return inMatrix;


		}










		inline Vec3 ToVec3() {
			return Vec3(m[0][0], m[1][0], m[2][0]);
		}

		inline void Print() {
			std::cout <<
				m[0][0] << "\t" << m[0][1] << "\t" << m[0][2] << "\n" <<
				m[1][0] << "\t" << m[1][1] << "\t" << m[1][2] << "\n" <<
				m[2][0] << "\t" << m[2][1] << "\t" << m[2][2] << "\n" <<
				std::endl;

		

		}
	};






}

#endif // !MATRIX2_H