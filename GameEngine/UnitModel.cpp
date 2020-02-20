#include <assert.h>
#include <sb7.h>
#include "UnitModel.h"
#include "Trace.h"
#include "UnitModelFileHeader.h"
#include "File.h"

#define WRITE_DATA_TO_FILE 1


UnitModel::UnitModel(Model::ModelType type, const char * const pModelFileName, int textureNumber)
	: Model()
{
	assert(pModelFileName);

	this->createVAO(type, pModelFileName, textureNumber);
}

UnitModel::~UnitModel()
{
	// remove dynamic stuff here
}
void UnitModel::createVAO(Model::ModelType type, const char * const pModelFileName, const char * const objectName)
{
	shutUp(type);
	shutUp(pModelFileName);
	shutUp(objectName);
}

void UnitModel::createVAO(Model::ModelType type, const char * const pModelFileName, int textureNumber)
{
	shutUp(type);
	shutUp(pModelFileName);
	shutUp(textureNumber);
	
#if WRITE_DATA_TO_FILE
	

	vertexBuff = nullptr;
	triIndex = nullptr;

	// create a header
	UnitModelFileHeader modelHdr;

	if (type == Model::ModelType::UnitCube)
	{
		CreateCube(vertexBuff, this->numVerts, triIndex, this->numTris);
		// object name
		strncpy_s(modelHdr.objName, OBJECT_NAME_SIZE, "Cube", _TRUNCATE);

	}
	else if (type == Model::ModelType::UnitPyramid)
	{
		CreatePyramid(vertexBuff, this->numVerts, triIndex, this->numTris);
		// object name
		strncpy_s(modelHdr.objName, OBJECT_NAME_SIZE, "Pyramid", _TRUNCATE);
	}
	else if (type == Model::ModelType::UnitSphere)
	{
		CreateSphere(8, 8, vertexBuff, this->numVerts, triIndex, this->numTris);
		// object name
		strncpy_s(modelHdr.objName, OBJECT_NAME_SIZE, "Sphere", _TRUNCATE);
	}
	else if (type == Model::ModelType::Diamond)
	{
		CreateDiamond(vertexBuff, this->numVerts, triIndex, this->numTris);
		// object name
		strncpy_s(modelHdr.objName, OBJECT_NAME_SIZE, "Diamond", _TRUNCATE);
	}

	// vertex buffer
	modelHdr.numVerts = this->numVerts;
	modelHdr.vertBufferOffset = 0;

	// trilist index 
	modelHdr.numTriList = this->numTris;
	modelHdr.triListBufferOffset = 0;

	strncpy_s(modelHdr.textName, OBJECT_NAME_SIZE, "null", _TRUNCATE);

	modelHdr.numMeshes = 1;
	modelHdr.numTextures = 0;

	// Write to a file

	// Write the data to a file ---------------------------------------------

	File::Handle fh;
	File::Error  ferror;

	//----------- WRITE ------------------------------------------
	ferror = File::Open(fh, pModelFileName, File::Mode::READ_WRITE);
	assert(ferror == File::Error::SUCCESS);

	// write the Header
	ferror = File::Write(fh, &modelHdr, sizeof(UnitModelFileHeader));
	assert(ferror == File::Error::SUCCESS);

	// write the vert buffer data
	ferror = File::Tell(fh, modelHdr.vertBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, vertexBuff, sizeof(Vertex) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// write the index buffer
	ferror = File::Tell(fh, modelHdr.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, triIndex, sizeof(Tri_index) * this->numTris);
	assert(ferror == File::Error::SUCCESS);

	// Finish the write
	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	// Rewind and overwrite model hdr
	ferror = File::Seek(fh, File::Location::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Write(fh, &modelHdr, sizeof(UnitModelFileHeader));
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Flush(fh);
	assert(ferror == File::Error::SUCCESS);

	// VERIFY
	UnitModelFileHeader modelHdr2;

	ferror = File::Seek(fh, File::Location::BEGIN, 0);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh, &modelHdr2, sizeof(UnitModelFileHeader));
	assert(ferror == File::Error::SUCCESS);

	// CLOSE
	ferror = File::Close(fh);
	assert(ferror == File::Error::SUCCESS);


#else

	File::Handle fh2;
	File::Error  ferror;

	ferror = File::Open(fh2, pModelFileName, File::Mode::READ);
	assert(ferror == File::Error::SUCCESS);

	// Read the Hdr
	ModelFileHeader modelHdr;
	ferror = File::Read(fh2, &modelHdr, sizeof(ModelFileHeader));
	assert(ferror == File::Error::SUCCESS);

	// Using the hdr, allocate the space for the buffers
	this->numVerts = modelHdr.numVerts;
	this->numTris = modelHdr.numTriList;

	// allocate buffers
	vertexBuff = new Vertex[(unsigned int)modelHdr.numVerts];
	triIndex = new Tri_index[(unsigned int)modelHdr.numTriList];



	// Read verts
	ferror = File::Seek(fh2, File::Location::BEGIN, (int)modelHdr.vertBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh2, vertexBuff, sizeof(Vertex) * this->numVerts);
	assert(ferror == File::Error::SUCCESS);

	// Read trilist
	ferror = File::Seek(fh2, File::Location::BEGIN, (int)modelHdr.triListBufferOffset);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Read(fh2, triIndex, sizeof(Tri_index) * this->numTris);
	assert(ferror == File::Error::SUCCESS);

	ferror = File::Close(fh2);
	assert(ferror == File::Error::SUCCESS);



#endif


	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);

	// Create a VBO
	glGenBuffers(2, &this->vbo[0]);
	assert(this->vbo[0] != 0);

	// Load the combined data: ---------------------------------------------------------

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);

	// load the data to the GPU
	glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vertex) * this->numVerts), vertexBuff, GL_STATIC_DRAW);

	// Define an array of generic vertexBuff attribute data

	// Vert data is location: 0  (used in vertexBuff shader)
	// todo make a table or enum
	void *offsetVert = (void *)((unsigned int)&vertexBuff[0].x - (unsigned int)vertexBuff);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetVert);
	glEnableVertexAttribArray(0);

	// Texture data is location: 1  (used in vertexBuff shader)
	void *offsetTex = (void *)((unsigned int)&vertexBuff[0].u - (unsigned int)vertexBuff);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetTex);
	glEnableVertexAttribArray(1);

	// normals data in location 2 (used in vertexBuff shader
	void *offsetNorm = (void *)((unsigned int)&vertexBuff[0].nx - (unsigned int)vertexBuff);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetNorm);
	glEnableVertexAttribArray(2);

	// Load the index data: ---------------------------------------------------------

	//Bind our 2nd VBO as being the active buffer and storing index )
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	// Copy the index data to our buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numTris), triIndex, GL_STATIC_DRAW);
	
}

void UnitModel::CreateCube(Vertex *&pVerts, int& nverts, Tri_index *&pTriList, int& ntri)
{
	//this SHOULD make it easier to import values from an OBJ file
	//derived from my DirectX engine

	nverts = 24;
	pVerts = new Vertex[(unsigned int)nverts];
	ntri = 12;
	pTriList = new Tri_index[(unsigned int)ntri];

	// Setting up faces
	// Forward
	int vertIndex = 0;
	int triIndex = 0;
	pVerts[vertIndex].setPosUV(0.5f, 0.5f, 0.5f, 1, 0);
	pVerts[vertIndex + 1].setPosUV(-0.5f, 0.5f, 0.5f, 0, 0);
	pVerts[vertIndex + 2].setPosUV(-0.5f, -0.5f, 0.5f, 0, 1);
	pVerts[vertIndex + 3].setPosUV(0.5f, -0.5f, 0.5f, 1, 1);

	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);
	pTriList[triIndex + 1].set(vertIndex + 3, vertIndex + 2, vertIndex);

	// Back
	vertIndex += 4;
	triIndex += 2;
	pVerts[vertIndex].setPosUV(0.5f, 0.5f, -0.5f, 0, 0);
	pVerts[vertIndex + 1].setPosUV(-0.5f, 0.5f, -0.5f, 1, 0);
	pVerts[vertIndex + 2].setPosUV(-0.5f, -0.5f, -0.5f, 1, 1);
	pVerts[vertIndex + 3].setPosUV(0.5f, -0.5f, -0.5f, 0, 1);

	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);
	pTriList[triIndex + 1].set(vertIndex, vertIndex + 2, vertIndex + 3);

	// Left
	vertIndex += 4;
	triIndex += 2;
	pVerts[vertIndex].setPosUV(0.5f, 0.5f, -0.5f, 1, 0);
	pVerts[vertIndex + 1].setPosUV(0.5f, 0.5f, 0.5f, 0, 0);
	pVerts[vertIndex + 2].setPosUV(0.5f, -0.5f, 0.5f, 0, 1);
	pVerts[vertIndex + 3].setPosUV(0.5f, -0.5f, -0.5f, 1, 1);

	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);
	pTriList[triIndex + 1].set(vertIndex + 3, vertIndex + 2, vertIndex);

	// Right
	vertIndex += 4;
	triIndex += 2;
	pVerts[vertIndex].setPosUV(-0.5f, 0.5f, 0.5f, 1, 0);
	pVerts[vertIndex + 1].setPosUV(-0.5f, 0.5f, -0.5f, 0, 0);
	pVerts[vertIndex + 2].setPosUV(-0.5f, -0.5f, -0.5f, 0, 1);
	pVerts[vertIndex + 3].setPosUV(-0.5f, -0.5f, 0.5f, 1, 1);

	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);
	pTriList[triIndex + 1].set(vertIndex + 3, vertIndex + 2, vertIndex);

	// Top
	vertIndex += 4;
	triIndex += 2;
	pVerts[vertIndex].setPosUV(0.5f, 0.5f, -0.5f, 1, 0);
	pVerts[vertIndex + 1].setPosUV(-0.5f, 0.5f, -0.5f, 0, 0);
	pVerts[vertIndex + 2].setPosUV(-0.5f, 0.5f, 0.5f, 0, 1);
	pVerts[vertIndex + 3].setPosUV(0.5f, 0.5f, 0.5f, 1, 1);

	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);
	pTriList[triIndex + 1].set(vertIndex + 3, vertIndex + 2, vertIndex);

	// Bottom
	vertIndex += 4;
	triIndex += 2;
	pVerts[vertIndex].setPosUV(0.5f, -0.5f, 0.5f, 1, 0);
	pVerts[vertIndex + 1].setPosUV(-0.5f, -0.5f, 0.5f, 0, 0);
	pVerts[vertIndex + 2].setPosUV(-0.5f, -0.5f, -0.5f, 0, 1);
	pVerts[vertIndex + 3].setPosUV(0.5f, -0.5f, -0.5f, 1, 1);

	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);
	pTriList[triIndex + 1].set(vertIndex + 3, vertIndex + 2, vertIndex);


	GetNorms(pVerts, vertIndex, pTriList, ntri);
}

void UnitModel::CreatePyramid(Vertex *&pVerts, int& nverts, Tri_index *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new Vertex[(unsigned int)nverts];
	ntri = 12;
	pTriList = new Tri_index[(unsigned int)ntri];


	// Forward
	int vertIndex = 0;
	int triIndex = 0;
	pVerts[vertIndex].setPosUV(0.0f, 0.5f, 0.0f, 1, 1);
	pVerts[vertIndex + 1].setPosUV(0.5f, -0.5f, 0.5f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(-0.5f, -0.5f, 0.5f, 0, 1);

	GetNorms(pVerts[vertIndex], pVerts[vertIndex + 1], pVerts[vertIndex + 2]);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// Back
	vertIndex += 3;
	triIndex += 1;
	pVerts[vertIndex].setPosUV(0.0f, 0.5f, 0.0f, 0, 1);
	pVerts[vertIndex + 1].setPosUV(0.5f, -0.5f, -0.5f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(-0.5f, -0.5f, -0.5f, 1, 1);

	GetNorms(pVerts[vertIndex + 2], pVerts[vertIndex + 1], pVerts[vertIndex]);
	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);

	// Left
	vertIndex += 3;
	triIndex += 1;
	pVerts[vertIndex].setPosUV(0.0f, 0.5f, 0.0f, 1, 1);
	pVerts[vertIndex + 1].setPosUV(0.5f, -0.5f, -0.5f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(0.5f, -0.5f, 0.5f, 0, 1);

	GetNorms(pVerts[vertIndex], pVerts[vertIndex + 1], pVerts[vertIndex + 2]);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// Right
	vertIndex += 3;
	triIndex += 1;
	pVerts[vertIndex].setPosUV(0.0f, 0.5f, 0.0f, 1, 1);
	pVerts[vertIndex + 1].setPosUV(-0.5f, -0.5f, 0.5f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(-0.5f, -0.5f, -0.5f, 0, 1);

	GetNorms(pVerts[vertIndex], pVerts[vertIndex + 1], pVerts[vertIndex + 2]);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// Bottom
	vertIndex += 4;
	triIndex += 2;
	pVerts[vertIndex].setPosUV(0.5f, -0.5f, 0.5f, 1, 0);
	pVerts[vertIndex + 1].setPosUV(-0.5f, -0.5f, 0.5f, 0, 0);
	pVerts[vertIndex + 2].setPosUV(-0.5f, -0.5f, -0.5f, 0, 1);
	pVerts[vertIndex + 3].setPosUV(0.5f, -0.5f, -0.5f, 1, 1);

	GetNorms(pVerts[vertIndex+2], pVerts[vertIndex + 1], pVerts[vertIndex]);
	pTriList[triIndex].set(vertIndex+2, vertIndex + 1, vertIndex);

	GetNorms(pVerts[vertIndex+3], pVerts[vertIndex + 1], pVerts[vertIndex]);
	pTriList[triIndex + 1].set(vertIndex + 3, vertIndex + 2, vertIndex);

}

void UnitModel::CreateDiamond(Vertex *&pVerts, int& nverts, Tri_index *&pTriList, int& ntri)
{
	nverts = 0x18;
	pVerts = new Vertex[(unsigned int)nverts];
	ntri = 0x8;
	pTriList = new Tri_index[(unsigned int)ntri];


	// Forward
	int vertIndex = 0;
	int triIndex = 0;
	pVerts[vertIndex].setPosUV(0.0f, 0.5f, 0.0f, 1, 1);
	pVerts[vertIndex + 1].setPosUV(0.25f, -0.0f, 0.25f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(-0.25f, -0.0f, 0.25f, 0, 1);

	GetNorms(pVerts[vertIndex], pVerts[vertIndex + 1], pVerts[vertIndex + 2]);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// Back
	vertIndex += 3;
	triIndex += 1;
	pVerts[vertIndex].setPosUV(0.0f, 0.5f, 0.0f, 0, 1);
	pVerts[vertIndex + 1].setPosUV(0.25f, -0.0f, -0.25f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(-0.25f, -0.0f, -0.25f, 1, 1);

	GetNorms(pVerts[vertIndex + 2], pVerts[vertIndex + 1], pVerts[vertIndex]);
	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);

	// Left
	vertIndex += 3;
	triIndex += 1;
	pVerts[vertIndex].setPosUV(0.0f, 0.5f, 0.0f, 1, 1);
	pVerts[vertIndex + 1].setPosUV(0.25f, -0.0f, -0.25f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(0.25f, -0.0f, 0.25f, 0, 1);

	GetNorms(pVerts[vertIndex], pVerts[vertIndex + 1], pVerts[vertIndex + 2]);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// Right
	vertIndex += 3;
	triIndex += 1;
	pVerts[vertIndex].setPosUV(0.0f, 0.5f, 0.0f, 1, 1);
	pVerts[vertIndex + 1].setPosUV(-0.25f, -0.0f, 0.25f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(-0.25f, -0.0f, -0.25f, 0, 1);

	GetNorms(pVerts[vertIndex], pVerts[vertIndex + 1], pVerts[vertIndex + 2]);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// Bottom front
	vertIndex += 3;
	triIndex += 1;
	pVerts[vertIndex].setPosUV(0.0f, -0.5f, 0.0f, 1, 1);
	pVerts[vertIndex + 1].setPosUV(0.25f, -0.0f, 0.25f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(-0.25f, -0.0f, 0.25f, 0, 1);

	GetNorms(pVerts[vertIndex + 2], pVerts[vertIndex + 1], pVerts[vertIndex]);
	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);

	//bottom back
	vertIndex += 3;
	triIndex += 1;
	pVerts[vertIndex].setPosUV(0.0f, -0.5f, 0.0f, 0, 1);
	pVerts[vertIndex + 1].setPosUV(0.25f, -0.0f, -0.25f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(-0.25f, -0.0f, -0.25f, 1, 1);

	GetNorms(pVerts[vertIndex], pVerts[vertIndex + 1], pVerts[vertIndex + 2]);
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	// bottom Left
	vertIndex += 3;
	triIndex += 1;
	pVerts[vertIndex].setPosUV(0.0f, -0.5f, 0.0f, 1, 1);
	pVerts[vertIndex + 1].setPosUV(0.25f, -0.0f, -0.25f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(0.25f, -0.0f, 0.25f, 0, 1);

	GetNorms(pVerts[vertIndex + 2], pVerts[vertIndex + 1], pVerts[vertIndex]);
	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);

	// bottom Right
	vertIndex += 3;
	triIndex += 1;
	pVerts[vertIndex].setPosUV(0.0f, -0.5f, 0.0f, 1, 1);
	pVerts[vertIndex + 1].setPosUV(-0.25f, -0.0f, 0.25f, 0.5f, 0);
	pVerts[vertIndex + 2].setPosUV(-0.25f, -0.0f, -0.25f, 0, 1);

	GetNorms(pVerts[vertIndex + 2], pVerts[vertIndex + 1], pVerts[vertIndex]);
	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);

	vertIndex += 3;
	triIndex += 1;

}

void UnitModel::CreateSphere(int vslice, int hslice, Vertex *&pVerts, int& nverts, Tri_index *&pTriList, int& ntri) {

	nverts = (vslice * hslice) + 2;
	pVerts = new Vertex[(unsigned int)nverts];
	ntri = (vslice * hslice) * 2;
	pTriList = new Tri_index[(unsigned int)ntri];

	int vertIndex = 0;
	int triIndex = 0;

	float phiStep = 3.1415926f / hslice;
	float thetaStep = 2.0f*3.1415926f / vslice;

	//set up top pole
	pVerts[vertIndex].setPos(0.0f, 0.5f, 0.0f); //top pole
	vertIndex += 1;

	//now do the middle ones
	for (int i = 1; i <= hslice - 1; ++i)
	{
		float phi = i*phiStep;

		for (int j = 0; j <= vslice; ++j)
		{
			float theta = j * thetaStep;

			pVerts[vertIndex].setPosUV(sinf(phi)*sinf(theta)/2, cosf(phi)/2, sinf(phi)*cosf(theta)/2, theta / (2.0f * 3.1415926f)/2, (phi / 3.1415926f)/2);
			vertIndex += 1;
		}
	}

	//and now the bottom ones
	pVerts[vertIndex].setPos(0.0f, -0.5f, 0.0f); //bottom pole
	vertIndex += 1;

	//top
	for (int i = 1; i <= vslice; ++i)
	{
		GetNorms(pVerts[0], pVerts[i + 1], pVerts[i]);


		pTriList[triIndex].set(0, i + 1, i);
		triIndex += 1;
	}

	//middle
	int baseIndex = 1;
	int ringVertexCount = vslice + 1;
	for (int i = 0; i < hslice - 2; ++i)
	{
		for (int j = 0; j < vslice; ++j)
		{
			GetNorms(pVerts[baseIndex + i*ringVertexCount + j], pVerts[baseIndex + i*ringVertexCount + j + 1], pVerts[baseIndex + (i + 1)*ringVertexCount + j]);
			GetNorms(pVerts[baseIndex + (i + 1)*ringVertexCount + j], pVerts[baseIndex + i*ringVertexCount + j + 1], pVerts[baseIndex + (i + 1)*ringVertexCount + j + 1]);

			pTriList[triIndex].set(baseIndex + i*ringVertexCount + j, baseIndex + i*ringVertexCount + j + 1, baseIndex + (i + 1)*ringVertexCount + j);
			pTriList[triIndex + 1].set(baseIndex + (i + 1)*ringVertexCount + j, baseIndex + i*ringVertexCount + j + 1, baseIndex + (i + 1)*ringVertexCount + j + 1);
			
			triIndex += 2;
		}
	}

	//bottom
	int southPoleIndex = vertIndex - 1;

	baseIndex = southPoleIndex - ringVertexCount;

	for (int i = 0; i < vslice; ++i)
	{
		GetNorms(pVerts[pTriList[southPoleIndex].v0], pVerts[pTriList[baseIndex + i].v1], pVerts[pTriList[baseIndex + i + 1].v2]);
		pTriList[triIndex].set(southPoleIndex, baseIndex + i, baseIndex + i + 1);
		triIndex += 1;
	}

	//GetNorms(pVerts, vertIndex, pTriList, triIndex);
}

void UnitModel::GetNorms(Vertex *&pVerts, int& nverts, Tri_index *&pTriList, int& ntri)
{
	shutUp(nverts);

	Vertex v0;
	Vertex v1;
	Vertex v2;

	for (int i = 0; i < ntri; i++) {
		GetNorms(pVerts[pTriList[i].v0], pVerts[pTriList[i].v1], pVerts[pTriList[i].v2]);
	}
}

void UnitModel::GetNorms(Vertex &point1, Vertex &point2, Vertex &point3)
{

	Vect v0Pos(0.0f,0.0f,0.0f);
	Vect v1Pos(0.0f,0.0f,0.0f);
	Vect v2Pos(0.0f,0.0f,0.0f);

	v0Pos.set(point1.x, point1.y, point1.z);
	v1Pos.set(point2.x, point2.y, point2.z);
	v2Pos.set(point3.x, point3.y, point3.z);

	v0Pos.norm();
	v1Pos.norm();
	v2Pos.norm();

	point1.setNorm(v0Pos.x(), v0Pos.y(), v0Pos.z());
	point2.setNorm(v1Pos.x(), v1Pos.y(), v1Pos.z());
	point3.setNorm(v2Pos.x(), v2Pos.y(), v2Pos.z());

}
