#include "Primitive.h"
namespace GAME {
	class Collider
	{
	public:


		static bool Collided(const Body& b1, const Body& b2);
		static void HandleCollision(Body& b1, Body& b2, Vec3 CN, Vec3 CP, Vec3 CP2);
		static Vec3 Support(const Body& b1, const Body& b2, Vec3 Direction);
		static Vec3 Support(const Vec3 Translatedpos1, const Vec3 Translatedpos2, const Vec3 Translatedpos3, const Vec3 Translatedpos4, const Vec3 Translatedpos5, const Vec3 Translatedpos6, Vec3 Direction, Mat3 mat1, Mat3 mat2 ,  Body& b1,  Body& b2);
		static void HandleNormal(Body& b1, Body& b2);
		static void Convex(Vec3 M1, Vec3 M2, Vec3 pm1, Vec3 pm2, Vec3 pm3, Mat3 inverse, Mat3 inverse2,  Body& b1,  Body& b2);



		//static bool Collided(const Primitive& b1, const Primitive& b2);
		//static void HandleCollision(Primitive& b1, Primitive& b2);
		//static Vec3 Support(const Primitive& b1, const Primitive& b2, Vec3 Direction);
		//static Vec3 Support(const Vec3 Translatedpos1, const Vec3 Translatedpos2, const Vec3 Translatedpos3, const Vec3 Translatedpos4, const Vec3 Translatedpos5, const Vec3 Translatedpos6, Vec3 Direction, Mat3 mat1, Mat3 mat2);
		//static void HandleNormal(Primitive& b1, Primitive& b2);
		//static void Convex(Vec3 M1, Vec3 M2, Vec3 pm1, Vec3 pm2, Vec3 pm3, Mat3 inverse, Mat3 inverse2);
	};
};