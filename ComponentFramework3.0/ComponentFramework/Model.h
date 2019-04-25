#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "MMath.h"
#include "Mesh.h"
#include "ObjLoader.h"

using namespace MATH;

class Scene;

namespace GAME {

	class Model {
	protected:

		Vec3 orientation;
		Vec3 gravity;
		Sphere bounding;
		Matrix4 modelMatrix;
		Scene* parentScene;
		std::vector<Mesh*> meshes;

		//arifa did this
		std::string object;
	public:

		virtual ~Model() {};

		Model(const Model&) = delete;
		Model(Model&&) = delete;
		Model& operator = (const Model&) = delete;
		Model& operator = (Model&&) = delete;

		Model() : gravity(0.0f, -9.8f, 0.0f) { };


		virtual bool OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void Render(const Matrix4& projectionMatrix, const Matrix4& modelViewMatrix, const Matrix3& normalMatrix)const = 0;


		//gets model name  (arifa)
		inline std::string GetMOdelName()
		{
			return object;
		}

	};

} /// end of namespace

#endif