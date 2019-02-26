#include "Primitive.h"

using namespace GAME;


//takes in a drawmode  list of vertices, noramals and uvs
Primitive::Primitive(GLenum drawMode_, std::vector<Vec3> &vertices_,
	std::vector<Vec3> &normals, std::vector<Vec2>&uvs_)
{
	meshes.push_back(new Mesh(drawMode_, vertices_, normals, uvs_));
	OnCreate();
}
// makes it able to  make a path to an obj text file that contains vertices, uv(texture cor) , vn(normals) and faces
Primitive::Primitive(std::string filePath_) 
{
	ObjLoader obj(filePath_.c_str());

	//GL_LINE_LOOP  draws the out side line of the obj
	//GL_TRIANGLES  fill  triangle with texture or color 
	meshes.push_back(new Mesh(GL_LINE_LOOP, obj.vertices, obj.normals, obj.uvCoords));
	OnCreate();
}
//destory 
Primitive::~Primitive()
{
	OnDestroy();
}

 bool Primitive:: OnCreate() {
	 //creates shader
	 shader = new Shader("baseVert.glsl", "baseFrag.glsl", 3, 0, "vVertex", 1, "vNormal", 2, "texCoords");
	 //sets location of the  projectionMatrixID , modelViewMatrixID, normalMatrixID
	 projectionMatrixID = glGetUniformLocation(shader->getProgram(), "projectionMatrix");
	 modelViewMatrixID = glGetUniformLocation(shader->getProgram(), "modelViewMatrix");
	 normalMatrixID = glGetUniformLocation(shader->getProgram(), "normalMatrix");
	 body = new Body(1.0f, 0.0f);
	 for (int i = 0; i < meshes.size(); i++) 
	 {
		 for (int j = 0; j < meshes[i]->vertices.size(); j++) 
		 {
			 body->AddPoint(meshes[i]->vertices[j]);
		 }
	 
	 }
	 
	 return true;
 }


 void Primitive::OnDestroy() {
	 glDeleteVertexArrays(1, &vao);//vbo
	 glDeleteBuffers(1, &vbo);
	 //deletes shader
	 if (shader) {
		 delete shader;
	 }

	 shader = nullptr;
	 
	 for ( Mesh* m : meshes)
	 {
		 if (m)
		 {
			 delete m;
		 }
		 m = nullptr;
	 }
 }

 void Primitive::Update(const float deltaTime) {
	
	 Model::Update(deltaTime);
	 modelMatrix = MMath::translate(body->getPos().x, body->getPos().y, body->getPos().z);//pos.x ,pos.y, pos.z);
	 modelMatrix *= MMath::rotate(body->getAngle(),0,0,1);
 }

void Primitive::Render(const Matrix4& projectionMatrix,	const Matrix4& viewMatrix, const Matrix3& normalMatrix)const {
	//tells opengl to use this shader programm
	glUseProgram(shader->getProgram());

	//passses the projectionMatrix to where the shader is 
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, projectionMatrix);
	
	//passses the  viewMatrix *  modelMatrix to where the shader is 
	glUniformMatrix4fv(modelViewMatrixID, 1, GL_FALSE, viewMatrix *  modelMatrix);
	
	//passses the normalMatrix(direction) to where the shader is
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	
	//goes though all the meshes in the mesh vector then calls rrender fir each mesh
	for (Mesh* mesh : meshes) {
		mesh->Render();
	}
	glEnableVertexAttribArray(0); // Disable the VAO

}
