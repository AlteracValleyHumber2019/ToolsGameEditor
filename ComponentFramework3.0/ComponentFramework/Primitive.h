#ifndef PRIMITVE_H 
#define PRIMITVE_H 

#include "Shader.h"
#include "Model.h"
#include"ObjLoader.h"
#include "Body.h"

namespace GAME {

	class Primitive:public Model {

	public: 

		//delete the copy and move constucotr
		Primitive(const Primitive&) = delete;
		Primitive(Primitive&&) = delete;
		Primitive& operator = (const Primitive&) = delete;
		Primitive& operator = (Primitive&&) = delete;

		
		
		Primitive(GLenum drawMode_, std::vector<Vec3> &vertices_, std::vector<Vec3> &normals, std::vector<Vec2>&uvs_);
		
		Primitive(std::string filePath_);
		
		virtual	~Primitive();
		virtual bool OnCreate() ;
		virtual void OnDestroy() ;
		virtual void Update(const float deltaTime)override;
		virtual void Render(const Matrix4& projectionMatrix,const Matrix4& viewMatrix, 
		const Matrix3& normalMatrix)const ;

	private:

		Shader* shader;
		GLuint vbo;
		GLuint vao;
		GLint verticiesID;
		GLint normalsID;
		GLint uvCoordsID;
		GLint projectionMatrixID;
		GLint modelViewMatrixID;
		GLint normalMatrixID;
	
	};
}
#endif
