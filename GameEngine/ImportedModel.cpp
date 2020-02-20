#include <assert.h>
#include <sb7.h>
#include "ImportedModel.h"
#include "Trace.h"
#include "ModelFileHeader.h"
#include "File.h"
#include "eat.h"
#include "TextureManager.h"
#include "BoundingSphere.h"


ImportedModel::ImportedModel(Model::ModelType type, const char * const pModelFileName, int textureNumber)
	: Model()
{
	assert(pModelFileName);

	this->createVAO(type, pModelFileName, textureNumber);
}

ImportedModel::~ImportedModel()
{
	// remove dynamic stuff here
}

void ImportedModel::createVAO(Model::ModelType type, const char * const pModelFileName, const char * const objectName)
{
	shutUp(type);
	shutUp(pModelFileName);
	shutUp(objectName);
}

void ImportedModel::createVAO(Model::ModelType type, const char * const pModelFileName, int textureNumber)
{
	shutUp(type);

	unsigned char *chunkBuff;
	unsigned int chunkSize;

	ModelFileHeader modelHdr;
	modelHdr.numChunks = 0;

	eatModelFileHeader(pModelFileName, modelHdr);

	// Using the hdr, allocate the space for the buffers
	this->numVerts = (int)modelHdr.totalNumVerts;
	this->numTris = (int)modelHdr.totalNumTriList;

	// allocate buffers
	vertexBuff = new Vertex[(unsigned int)modelHdr.totalNumVerts];
	triIndex = new Tri_index[(unsigned int)modelHdr.totalNumTriList];

	unsigned int thingsInside;

	eat(pModelFileName, ChunkType::VERTS_TYPE, modelHdr, thingsInside, chunkBuff, chunkSize);
	float *floatBuff = new float[chunkSize];
	memcpy((void *)floatBuff, chunkBuff, chunkSize);

	int k = 0;
	for (unsigned int i = 0; i < (int)thingsInside; i++)
	{
		vertexBuff[i].setVert(floatBuff[k + 0],   //x
			floatBuff[k + 1], //y
			floatBuff[k + 2], //z
			floatBuff[k + 3], //u
			floatBuff[k + 4], //v
			floatBuff[k + 5], //nx
			floatBuff[k + 6], //ny
			floatBuff[k + 7]);//nz

							  //Trace::out("Vert[%i]: %f, %f, %f, %f, %f, %f, %f, %f\n", i, 
							  //			vertexBuff[i].x, 
							  //			vertexBuff[i].y, 
							  //			vertexBuff[i].z, 
							  //			vertexBuff[i].u, 
							  //			vertexBuff[i].v, 
							  //			vertexBuff[i].nx, 
							  //			vertexBuff[i].ny, 
							  //			vertexBuff[i].nz);

		k += 8;
	}

	delete floatBuff;


	eat(pModelFileName, ChunkType::TRI_TYPE, modelHdr, thingsInside, chunkBuff, chunkSize);

	unsigned short *intBuff = new unsigned short[chunkSize];
	memcpy((void *)intBuff, chunkBuff, chunkSize);


	k = 0;
	for (unsigned int i = 0; i < (int)thingsInside; i++)
	{

		triIndex[i].set((unsigned short)intBuff[k + 0],
			(unsigned short)intBuff[k + 1],
			(unsigned short)intBuff[k + 2]);


		//Trace::out("Tri[%i]: %hu, %hu, %hu\n", i,
		//triIndex[i].v0, triIndex[i].v1, triIndex[i].v2);

		k += 3;
	}
	TextureManager::Name texture = TextureManager::Name::DEFAULT;
	int textNum = 0;

	const char* tgaFileExt = ".tga";

	const char* nameBuff = pModelFileName;
	
	char* textureBuff = new char[32];
	//get texture
	for (int i = 1; i <= modelHdr.numTextures; i++)
	{
		texture = (TextureManager::Name)(textureNumber + textNum);
		
		_itoa_s(textNum, textureBuff, sizeof(textureBuff),10);
		strcat_s(textureBuff, 32,nameBuff);
		strcat_s(textureBuff, 32,tgaFileExt);

		eat(pModelFileName, ChunkType::TEXTURE_TYPE, modelHdr, thingsInside, chunkBuff, chunkSize, i);

		if (chunkBuff == nullptr)
		{
			TextureManager::Add("default_text", (TextureManager::Name)(textureNumber + textNum), TextureManager::Status::Protected);

		}

		TextureManager::AddFromModel(pModelFileName, texture, chunkBuff);
		textNum++;
	}

	// Create a VAO
	glGenVertexArrays(1, &this->vao);
	assert(this->vao != 0);
	glBindVertexArray(this->vao);

	// Create a VBO
	glGenBuffers(2, &this->vbo[0]);
	assert(this->vbo[0] != 0);


	
	Sphere sphere;
	Vect *pVerts = new Vect[(unsigned int)this->numVerts];
	for (int i = 0; i < this->numVerts; i++)
	{
		pVerts[i].set(vertexBuff[i].x, vertexBuff[i].y, vertexBuff[i].z);
		//Trace::out("%d:  %f %f %f\n", i, pVerts[i][x], pVerts[i][y], pVerts[i][z]);
	}

	RitterSphere(sphere, pVerts, this->numVerts);
	//Trace::out("Ritter: cntr:%f %f %f  rad: %f ", sphere.center[x], sphere.center[y], sphere.center[z], sphere.radius);

	this->centerX = sphere.center.x();
	this->centerY = sphere.center.y();
	this->centerZ = sphere.center.z();
	this->radius = sphere.radius;

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

	/* Bind our 2nd VBO as being the active buffer and storing index ) */
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	/* Copy the index data to our buffer */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numTris), triIndex, GL_STATIC_DRAW);

	delete vertexBuff;
	delete triIndex;

	delete[] pVerts;
	delete[] floatBuff;
	delete[] intBuff;
	delete[] textureBuff;
	delete[] chunkBuff;
	//delete intBuff;
}
