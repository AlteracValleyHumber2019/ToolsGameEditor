#include "VMath.h"
#include "MMath.h"
#include "Collider.h"
#include <iostream>
#include <algorithm>    // std::reverse
#include <vector> 
#include <functional>   // std::negate
#include "Body.h"

using namespace MATH;
namespace GAME {
	bool Collider::Collided(const  Body& b1, const Body& b2) {

		Vec3 orgin = (0, 0, 0);

		Vec3 Centre;
		Vec3 Centre2;

		Vec3 Direaction;
		Vec3 Direaction2;
		Vec3 Direaction3;

		// finds the Centre of triangle by getting position of triangle and dividing by 3
	
			Vec3 total;
			Vec3 total2;
			for (int i = 0; i < b1.GetShape().size(); i++)
			{
				total += b1.GetShape()[i];
				total2 += b2.GetShape()[i];
			}
		
			Centre = total / b1.GetShape().size();
			Centre2 = total2 / b2.GetShape().size();


		/*Centre = ((b1.GetShape()[0] + b1.GetShape()[1] + b1.GetShape()[2]) / 3.0f) + b1.getPos();
			Centre2 = ((b2.GetShape()[0] + b2.GetShape()[1] + b2.GetShape()[2]) / 3.0f) + b2.getPos();*/

		//THE First INITIAL DIRECTION
		Direaction = Centre2 - Centre;//1.0 ,1.3

		// Normalizes the direction
		Vec3 DirecNormal = VMath::normalize(Direaction);//0.6, 0.8

		//Creates the first main point calling the Support functin to the dot product of both triangles positons using  Normalizes the first normalized direction
		Vec3 pMain1 = Support(b1, b2, DirecNormal);//1.5 2

		//SECOND INITIAL DIRECTION
		Direaction2 = Centre - Centre2;//1.0,1.3
		// Normalizes the secound direction
		Vec3 DirecNormal2 = VMath::normalize(Direaction2);//{x=-0.600000024 y=-0.800000012 z=0.000000000 }

		//Creates the secound main point calling the Support function to the dot product of both triangles positons using  Normalizes the secound normalized direction
		Vec3 pMain2 = Support(b1, b2, DirecNormal2); //{x = -1.50000000 y = -4.00000000 z = 0.000000000 }


		//THIRD DIRECTION VECTOR
		Vec3 Line = pMain2 - pMain1;

		//equals the  negated values of the line
		Vec3 Lineneg = -Line; // 𝐿𝑖𝑛𝑒 = (9, 7)
		Vec3 Lineneg2 = -Lineneg;//𝐿𝑖𝑛𝑒 = (-9, -7)

		//swaps the values
		std::swap(Lineneg.x, Lineneg.y);//𝐿𝑖𝑛𝑒 =
		std::swap(Lineneg2.x, Lineneg2.y);//𝐿𝑖𝑛𝑒 = (-7, -9)

		//makes vaule x of Lineneg postive
		Lineneg.x *= -1;
		//makes vaule x of Lineneg2 negative
		Lineneg2.x *= -1;


		// finding  the centre of the line lerp form
		Vec3 tri = ((1 - 0.5) * pMain1) + (0.5 * pMain2);

		// Normalizes the third direction using Lineneg2
		Vec3 DirecNormal3 = VMath::normalize(Lineneg2);

		// Normalizes the third direction using Lineneg
		Vec3 DirecNormal3B = VMath::normalize(Lineneg);

		//find the value between origin and Vec3 tri
		Vec3 COtri = orgin - tri; // (3.5, 1.5)

		//finds the dot product between the both third normalized third direction and COtri
		float COtriN = VMath::dot(DirecNormal3, COtri);//
		float COtriNB = VMath::dot(DirecNormal3B, COtri);//

		Vec3 pMain3;

		// this will determine which normalized third direction I use for the dot product to get the third main point
		if (COtriN > COtriNB)
		{
			pMain3 = Support(b1, b2, DirecNormal3);

		}
		else if (COtriNB > COtriN)
		{
			pMain3 = Support(b1, b2, DirecNormal3B);

		}

		//Perpendicular value
		Vec3 ABper = pMain2 - pMain1;
		Vec3 ACper = pMain3 - pMain1;
		Vec3 BCper = pMain3 - pMain2;
		Vec3 BAper = pMain1 - pMain2;


		//distance between Main points and origin
		Vec3 AO = orgin - pMain1;
		Vec3 BO = orgin - pMain2;
		Vec3 CO = orgin - pMain3;

		// GETTING THE PERPENDICULAR VECTOR by cross multplying perpendicular value
		Vec3 CrossofABAC = VMath::cross(VMath::cross(ABper, ACper), ABper);
		Vec3 CrossofAC = VMath::cross(VMath::cross(ACper, ABper), ACper);
		Vec3 CrossofBC = VMath::cross(VMath::cross(BCper, BAper), BCper);

		//gets the inside origin value
		float DOTAO = VMath::dot(CrossofABAC, AO);//
		float DOTBO = VMath::dot(CrossofAC, AO);//
		float DOTCO = VMath::dot(CrossofBC, BO);//

		//Checks to see if all values are postive if one value is negative then values are not inside the origin
		if (DOTAO >= 0 && DOTBO >= 0 && DOTCO >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}

	}



	void Collider::HandleCollision(Body & b1, Body & b2, Vec3 CN,Vec3 CP2, Vec3 CP)
	{
		float	Coe = 1.0f;
		float	Mass1 = b1.getMass();
		float	Mass2 = b2.getMass();
		Vec3 Vel1 = b1.getVel();
		Vec3 Vel2 = b2.getVel();
		
		//gets the Rotational Inertia of the triangle
		float RoationaL1 =b1.getRotationalInertia();
		float RoationaL2 = b2.getRotationalInertia();
	 
		// relative velocity along the normal
		float Vr = VMath::dot(CN, Vel1 - Vel2);

		// finds the Centre of triangle by getting position of triangle and dividing by 3 then adding trianglage position 
		Vec3 Centre = ((b1.GetShape()[0] + b1.GetShape()[1] + b1.GetShape()[2]) / 3.0f) + b1.getPos();
		Vec3 Centre2 = ((b2.GetShape()[0] + b2.GetShape()[1] + b2.GetShape()[2]) / 3.0f) + b2.getPos();
		
		//the vector from the body’s centre of mass to the collision point
		Vec3 r1 = CP - Centre;
		Vec3 r2 = CP2 - Centre2;
		
		//impulse 
		float impulse =  (-Vr * (Coe + 1) )  /  (1.0f / Mass1 + 1.0f / Mass2) + VMath::dot (   CN, VMath::cross (RoationaL1 * VMath::cross(r1, CN)/ RoationaL1, r1)) + VMath::dot(CN, VMath::cross(RoationaL2 * VMath::cross(r2, CN)/ RoationaL2, r2 ) );;

	//	final linearvelocity
		Vec3 V1f = Vel1 + (impulse * CN) / Mass1;
		Vec3 V2f = Vel2 + (-impulse * CN) / Mass2;

		//	final angular velocity
		float angularvelF1 = b1.getAngularVel() + (VMath::cross(r1, impulse * CN) / RoationaL1).y;
	    float angularvelF2 = b2.getAngularVel() + (VMath::cross(r2, -impulse * CN) / RoationaL2).y;
		
		//set the final velocity of the triangles
		b1.SetVelocity(V1f);
		b2.SetVelocity(V2f);

		//set the final Angular velocity of the triangles
		b1.SetAngularVel(angularvelF1);
		b2.SetAngularVel(angularvelF2);

	}



	void Collider::HandleNormal(Body& b1, Body& b2) {

		Vec3 orgin = (0, 0, 0);

		Vec3 Centre;
		Vec3 Centre2;

		Vec3 Direaction;
		Vec3 Direaction2;
		Vec3 Direaction3;

		// finds the Centre of triangle by getting position of triangle and dividing by 3
		Centre = ((b1.GetShape()[0] + b1.GetShape()[1] + b1.GetShape()[2]) / 3.0f) + b1.getPos();
		Centre2 = ((b2.GetShape()[0] + b2.GetShape()[1] + b2.GetShape()[2]) / 3.0f) + b2.getPos();

		//orgin to center
		Vec3 CentreOrgin = orgin - Centre;
		Vec3 OrginCentre = Centre - orgin;

		Vec3 CentreO2 = orgin - Centre2;
		Vec3 O2Centre = Centre2 - orgin;



		// shrinking the triangle by tranlating the matrix then scaling and translate again
		
		Mat3 TranslateCentr1 = MMath::translate3(OrginCentre.x, OrginCentre.y, OrginCentre.z) * MMath::scale3(0.75f, 0.75f, 1.0f) *  MMath::translate3(CentreOrgin.x, CentreOrgin.y, CentreOrgin.z);

		//
		// gets the points of the triangle
		Vec3 Translatedpos1 = TranslateCentr1 * b1.GetShape()[0] + b1.getPos();
		Vec3 Translatedpos2 = TranslateCentr1 * b1.GetShape()[1] + b1.getPos();
		Vec3 Translatedpos3 = TranslateCentr1 * b1.GetShape()[2] + b1.getPos();


		// shrinking the triangle by tranlating the matrix then scaling and translate again 										 // come back later
		Mat3 TranslateCentr2 = MMath::translate3(O2Centre.x, O2Centre.y, O2Centre.z) * MMath::scale3(0.75f, 0.75f, 1.0f) *  MMath::translate3(CentreO2.x, CentreO2.y, CentreO2.z);
		
		// gets the points of the triangle
		Vec3 Translatedpos4 = TranslateCentr2 * b2.GetShape()[0] + b2.getPos();
		Vec3 Translatedpos5 = TranslateCentr2 * b2.GetShape()[1] + b2.getPos();
		Vec3 Translatedpos6 = TranslateCentr2 * b2.GetShape()[2] + b2.getPos();


		//THE First INITIAL DIRECTION
		Direaction = Centre2 - Centre;
		//SECOND INITIAL DIRECTION
		Direaction2 = Centre - Centre2;

		//Creates the first main point calling the Support function to  do the dot product of Translatedpos points and  direction
		Vec3 pMain1 = Support(Translatedpos1, Translatedpos2, Translatedpos3, Translatedpos4, Translatedpos5, Translatedpos6, Direaction, TranslateCentr1, TranslateCentr2, b1, b2);

		//Creates the second main point calling the Support functin to  do the dot product of Translatedpos points and  direction2
		Vec3 pMain2 = Support(Translatedpos1, Translatedpos2, Translatedpos3, Translatedpos4, Translatedpos5, Translatedpos6, Direaction2, TranslateCentr1, TranslateCentr2, b1,  b2);

		//distance between Main points and origin
		Vec3 AO = orgin - pMain1;
		//distance between Mainpoint2 and origin
		Vec3 BO = orgin - pMain2;

		//distance between Main point2 and  Main point1
		Vec3 AB = pMain2 - pMain1;

		// the line lerp form finding the point of origin
		float t = VMath::dot(AO, AB) / VMath::dot(AB, AB);

		//point of the line 1
		Vec3  PLine = pMain1 + AB * t;

		//calculate the distance to the origin by getting the magitude of  PLine
		float Dpline = VMath::mag(PLine);

		//Third INITIAL DIRECTION
		Direaction3 = orgin - PLine;

		//Creates the third main point calling the Support functin to  do the dot product of Translatedpos points and  direction
		Vec3 pMain3 = Support(Translatedpos1, Translatedpos2, Translatedpos3, Translatedpos4, Translatedpos5, Translatedpos6, Direaction3, TranslateCentr1, TranslateCentr2, b1,  b2);

		//distance between Mainpoint3 and origin
		Vec3 CO = orgin - pMain3;

		//distance between Mainpoint3 and pMain1
		Vec3 AC = pMain3 - pMain1;

		//distance between Main point3  and pMain2
		Vec3 BC = pMain3 - pMain2;


		// the line lerp form finding the point of origin
		t = VMath::dot(AO, AC) / VMath::dot(AC, AC);

		//point of the line 2
		Vec3  PLine2 = pMain1 + t * AC;

		//calculate the distance to the origin by taking the  mag Pline2
		float q2 = VMath::mag(PLine2);

		// the line lerp form finding the point of origin
		t = VMath::dot(BO, BC) / VMath::dot(BC, BC);

		//point of the line 3
		Vec3  PLine3 = pMain2 + t * BC;

		//calculate the distance to the origin by taking the  mag Pline3
		float q3 = VMath::mag(PLine3);

		Vec3 Pline2Neg = PLine2;
		//negates x and y value  of Pline2Neg
		Pline2Neg.x = Pline2Neg.x*-1;
		Pline2Neg.y = Pline2Neg.y*-1;
		//
		Vec3 SD = Support(Translatedpos1, Translatedpos2, Translatedpos3, Translatedpos4, Translatedpos5, Translatedpos6, Pline2Neg, TranslateCentr1, TranslateCentr2, b1,  b2);


	}


	Vec3 Collider::Support(const Body & b1, const Body & b2, Vec3 Direction)
	{



		// Direction Value of triangle A
		float d1 = VMath::dot(Direction, b1.GetShape()[0]+ b1.getPos());
		float d2 = VMath::dot(Direction, b1.GetShape()[1] + b1.getPos());
		float d3 = VMath::dot(Direction, b1.GetShape()[2] + b1.getPos());

		// Direction Value of triangle B
		float d4 = VMath::dot(Direction, b2.GetShape()[0] + b2.getPos());
		float d5 = VMath::dot(Direction, b2.GetShape()[1] + b2.getPos());
		float d6 = VMath::dot(Direction, b2.GetShape()[2] + b2.getPos());



		Vec3 p1;
		Vec3 p2;



		// determines which direction points is the  greatest in triangle A
		if (d1 >= d2)
		{

			if (d1 >= d3)
			{
				//printf("d1 is the greatest among three \n");
				p1 = b1.GetShape()[0] + b1.getPos();

			}

			else
			{
				//printf("d3 is the greatest among three \n");
				p1 = b1.GetShape()[2] + b1.getPos();
			}
		}

		else if (d2 >= d3)
		{
			//printf("d2 is the greatest among three \n");
			p1 = b1.GetShape()[1] + b1.getPos();

		}
		else
		{
			//printf("d3 is the greatest among three \n");
			p1 = b1.GetShape()[2] + b1.getPos();
		}


		// determines which direction points is the smallest in triangle B
		if (d4 <= d5)
		{

			if (d4 <= d6)
			{
				//printf("d4 is the smallest among three \n");
				p2 = b2.GetShape()[0] + b2.getPos();

			}

			else
			{
				//printf("d6 is the smallest among three \n");
				p2 = b2.GetShape()[2] + b2.getPos();
			}
		}

		else if (d5 <= d6)
		{
			//printf("d5 is the smallest among three \n");
			p2 = b2.GetShape()[1] + b2.getPos();

		}
		else
		{
			//printf("d6 is the smallest among three \n");
			p2 = b2.GetShape()[2] + b2.getPos();
		}

		// RETURNS THE MAIN POINTS OF THE TRIANGLE
		return  p1 - p2;
	}




	Vec3 Collider::Support(const Vec3 Translatedpos1, const Vec3 Translatedpos2, const Vec3 Translatedpos3, const Vec3 Translatedpos4, const Vec3 Translatedpos5, const Vec3 Translatedpos6, Vec3 Direction, Mat3 mat1, Mat3 mat2, Body& b1, Body& b2)
	{



		// Direction Value of triangle A
		float d1 = VMath::dot(Direction, Translatedpos1);
		float d2 = VMath::dot(Direction, Translatedpos2);
		float d3 = VMath::dot(Direction, Translatedpos3);

		// Direction Value of triangle B
		float d4 = VMath::dot(Direction, Translatedpos4);
		float d5 = VMath::dot(Direction, Translatedpos5);
		float d6 = VMath::dot(Direction, Translatedpos6);



		Vec3 p1;
		Vec3 p2;

	

		// determines which direction points is the  greatest in triangle A
		if (d1 >= d2)
		{

			if (d1 >= d3)
			{
				//printf("d1 is the greatest among three \n");
				p1 = Translatedpos1;

			}

			else
			{
				//printf("d3 is the greatest among three \n");
				p1 = Translatedpos3;
			}



		}

		else if (d2 >= d3)
		{
			//printf("d2 is the greatest among three \n");
			p1 = Translatedpos2;

		}
		else
		{
			//printf("d3 is the greatest among three \n");
			p1 = Translatedpos3;
		}


		// determines which direction points are equal to each and which one is smaller then other
		if (d4 == d5 && d4 < d6)
		{
			Vec3 M1 = p1 - Translatedpos5;
			Vec3 M2 = p1 - Translatedpos4;
			Convex(M1, M2, p1, Translatedpos5, Translatedpos4, mat1, mat2, b1, b2);
		}
		else if (d4 == d6 && d4 < d5)
		{
			Vec3 M1 = p1 - Translatedpos6;
			Vec3 M2 = p1 - Translatedpos4;
			Convex(M1, M2, p1, Translatedpos6, Translatedpos4, mat1, mat2, b1, b2);

		}
		else if (d5 == d6 && d5 < d4)
		{
			Vec3 M1 = p1 - Translatedpos6;
			Vec3 M2 = p1 - Translatedpos5;
			Convex(M1, M2, p1, Translatedpos6, Translatedpos5, mat1, mat2, b1, b2);
		}

		// determines which direction points is the smallest in triangle B
		if (d4 <= d5)
		{


			if (d4 <= d6)
			{
				//printf("d4 is the smallest among three \n");
				p2 = Translatedpos4;

			}

			else
			{
				//printf("d6 is the smallest among three \n");
				p2 = Translatedpos6;
			}
		}

		else if (d5 <= d6)
		{
			//printf("d5 is the smallest among three \n");
			p2 = Translatedpos5;

		}
		else
		{
			//printf("d6 is the smallest among three \n");
			p2 = Translatedpos6;
		}

		// RETURNS THE MAIN POINTS OF THE TRIANGLE
		return  p1 - p2;

	}



	void Collider::Convex(Vec3 M1, Vec3 M2, Vec3 pm1, Vec3 pm2, Vec3 pm3, Mat3 inverse, Mat3 inverse2,  Body& b1,  Body& b2)
	{

		Vec3 L = M2 - M1;
		// lambda values
		float Lambda = VMath::dot(M2, L) / VMath::dot(L, L);
		float Lambda2 = 1.0f - Lambda;
		//Closest point of triangle A
		Vec3 Aclosest = Lambda * (pm1)+Lambda2 * (pm1);
		//Closest point of triangle B
		Vec3 Bclosest = Lambda * (pm2)+Lambda2 * (pm3);

		//contact normal
		Vec3 CN = (Bclosest - Aclosest) / VMath::mag(Bclosest - Aclosest);
		
		//innverse Matrix of the points
		Mat3 inveresepoint = Mat3::inverse3(inverse);
		Mat3 inveresepoint2 = Mat3::inverse3(inverse2);
		//contact points
		Vec3 CP = inveresepoint * Aclosest;
		Vec3 CP2 = inveresepoint2 * Bclosest;

		CN.print();
		CP.print();
		CP2.print();

		HandleCollision(b1, b2, CN, CP, CP2);
	}
}

