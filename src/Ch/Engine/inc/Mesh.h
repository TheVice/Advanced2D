#ifndef __MESH_H_
#define __MESH_H_

#include "Entity.h"
#include <d3dx9.h>

namespace Advanced2D
{
class Mesh : public Entity
{
private:
	LPD3DXMESH mMesh;

	D3DMATERIAL9* mMaterials;
	LPD3DXMATERIAL mD3dxMaterials;
	DWORD mMaterialCount;

	LPDIRECT3DTEXTURE9* mTextures;

	D3DXVECTOR3 mPosition;
	D3DXVECTOR3 mVelocity;
	D3DXVECTOR3 mRotation;
	D3DXVECTOR3 mScale;

	D3DXMATRIX mMaterialWorld;
	D3DXMATRIX mMaterialTranslate;
	D3DXMATRIX mMaterialRotate;
	D3DXMATRIX mMaterialScale;

	Mesh();
	Mesh(const Mesh& aRhs);
	Mesh& operator=(const Mesh& aRhs);
public:
	Mesh(const _TCHAR* aFilePath);

	int getFaceCount();
	int getVertexCount();

	void createSphere(float aRadius = 0.1f, int aSlices = 10, int aStacks = 10);
	void createCube(float aWidth = 1.0f, float aHeight = 1.0f, float aDepth = 1.0f);

	void rotate(const D3DXVECTOR3& aRotate);
	void rotate(float aRotateX, float aRotateY, float aRotateZ);

	void limitBoundary(float aLeft, float aRight, float aTop, float aBottom,
	                   float aBack,
	                   float aFront);

	void setPosition(const D3DXVECTOR3& aPosition);
	void setPosition(float aPositionX, float aPositionY, float aPositionZ);
	D3DXVECTOR3 getPosition();

	void setVelocity(const D3DXVECTOR3& aVelocity);
	void setVelocity(float aVelocityX, float aVelocityY, float aVelocityZ);
	D3DXVECTOR3 getVelocity();

	void setRotation(const D3DXVECTOR3& aRotation);
	void setRotation(float aRotationX, float aRotationY, float aRotationZ);
	D3DXVECTOR3 getRotation();

	void setScale(const D3DXVECTOR3& aScale);
	void setScale(float aScaleX, float aScaleY, float aScaleZ);
	D3DXVECTOR3 getScale();

	void draw();
	void transform();
	void move();
	void animate();

	virtual ~Mesh();
};
}

#endif
