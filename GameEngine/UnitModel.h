#ifndef CUBE_MODEL_H
#define CUBE_MODEL_H

#include "Model.h"

class UnitModel : public Model
{
public:
	UnitModel(Model::ModelType type, const char * const pModelFileName, int textureNumber = 0);

	static void CreateCube(Vertex *&pVerts, int& nverts, Tri_index *&pTriList, int& ntri);
	static void CreatePyramid(Vertex *&pVerts, int& nverts, Tri_index *&pTriList, int& ntri);
	static void CreateDiamond(Vertex *&pVerts, int& nverts, Tri_index *&pTriList, int& ntri);
	static void CreateSphere(int vslice, int hslice, Vertex *&pVerts, int& nverts, Tri_index *&pTriList, int& ntri);

	static void GetNorms(Vertex *&pVerts, int& nverts, Tri_index *&pTriList, int& ntri);

	static void GetNorms(Vertex &point1, Vertex &point2, Vertex &point3);

	UnitModel() = delete;
	UnitModel(const UnitModel &) = delete;
	UnitModel & operator = (UnitModel &) = delete;
	virtual ~UnitModel();

private:
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, int textureNumber) override;
	virtual void createVAO(Model::ModelType type, const char * const pModelFileName, const char * const objectName) override;

};

#endif