#ifndef GCAMERA_H
#define	GCAMERA_H

#include "MMath.h"
//Both Camera and Scene need their own perspective matrixes to work i.e: MMath::perspective(90.0f, aspect, 1.0f, 150.0f);

namespace GAME {
	using namespace MATH;


	class GCamera {
	private:
		Matrix4 projectionMatrix; // Type of camera Lens (Wide View or Focus View)
		Matrix4 viewMatrix; //Orientation (Physical movement)
		Vec3 pos, Opos;
		Vec3 orientation;
		Vec3 UpDir;



	public:
		GCamera(const int viewportWidth, const int viewportHeight, const Vec3 pos_);
		~GCamera();

		float aspect;
		GCamera* currentCamera;
		//Movement of Camera
		void OnUpArrowKeyDown();
		void OnDownArrowKeyDown();
		void OnLeftArrowKeyDown();
		void OnRightArrowKeyDown();
		void OnSpaceKeyDown();
		void OnShiftKeyDown();
		///Orientation
		void OnSKeyDown();
		void OnAKeyDown();
		void OnWKeyDown();
		void OnDKeyDown();
		void OnRKeyDown();

		//Matrixes 
		void UpdateViewMatrix();
		Matrix4&  getProjectionMatrix();
		Matrix4&  getViewMatrix();


		void setPos(const Vec3& pos_);
		void setOrientation(const Vec3& orientation_);
		void setUpDir(const Vec3& dir_);
		/// Return the 4x4 rotational matrix
		Matrix4 GetMatrix4() const { return viewMatrix; }

		/// Return the 3x3 rotational matrix, after all a rotational matrix is a 3x3!
		Matrix3 GetMatrix3() const { return Matrix3(viewMatrix); }
	};

}

#endif