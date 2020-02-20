#ifndef MODEL_H
#define MODEL_H
#include "sb7.h"
#include "MathEngine.h"

class Model
{

public:

	struct Vertex
	{
		float x;
		float y;
		float z;
		float u = 0.0f;
		float v = 0.0f;
		float nx = 0.0f;
		float ny = 0.0f;
		float nz = 0.0f;

		void setVert(float inX, float inY, float inZ, float inU, float inV, float inNX, float inNY, float inNZ)
		{
			this->x = inX;
			this->y = inY;
			this->z = inZ;

			this->u = inU;
			this->v = inV;

			this->nx = inNX;
			this->ny = inNY;
			this->nz = inNZ;
		}

		void setPosUV(float inX, float inY, float inZ, float inU, float inV)
		{
			this->x = inX;
			this->y = inY;
			this->z = inZ;

			this->u = inU;
			this->v = inV;

		}

		void setPos(float inX, float inY, float inZ)
		{
			this->x = inX;
			this->y = inY;
			this->z = inZ;
		}
		void setUV(float inU, float inV)
		{
			this->u = inU;
			this->v = inV;

		}
		void setNorm(float inNX, float inNY, float inNZ)
		{
			this->nx = inNX;
			this->ny = inNY;
			this->nz = inNZ;
		}
	};

	struct Tri_index
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;

		void set(unsigned int inV0, unsigned int inV1, unsigned int inV2)
		{
			v0 = inV0;
			v1 = inV1;
			v2 = inV2;
		}
		void set(unsigned short inV0, unsigned short inV1, unsigned short inV2)
		{
			v0 = (unsigned int)inV0;
			v1 = (unsigned int)inV1;
			v2 = (unsigned int)inV2;
		}
		void set(int inV0, int inV1, int inV2)
		{
			v0 = (unsigned int)inV0;
			v1 = (unsigned int)inV1;
			v2 = (unsigned int)inV2;
		}
	};


	enum ModelType
	{
		UnitCube,
		UnitPyramid,
		UnitSphere,
		Diamond,
		Imported,
		AnimPyramid,
		CameraModel
	};

	Model();
	Model(Model &copyModel) = delete;
	Model & operator = (Model &copyModel) = delete;
	virtual ~Model();

	

	int numVerts;
	int numTris;

	GLuint vao;
	GLuint vbo[2];

protected:
	Vertex *vertexBuff;
	Tri_index *triIndex;
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, int textureNumber) = 0;
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, const char * const objectName) = 0;
private:
	

};

#endif