
#include "Mesh.h"
#include "Advanced2D.h"

namespace Advanced2D
{

Mesh::Mesh(const _TCHAR* aFilePath) :
	Entity(RENDER3D),
	mMesh(0),
	mMaterials(NULL),
	mD3dxMaterials(0),
	mMaterialCount(0),
	mTextures(NULL),
	mPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	mVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	mRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	mScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f))
{
	if (aFilePath && aFilePath[0] != 0)
	{
		LPD3DXBUFFER materialBuffer = NULL;

		if (FAILED(D3DXLoadMeshFromX(aFilePath, D3DXMESH_SYSTEMMEM,
		                             g_engine->getDevice(), NULL, &materialBuffer, NULL, &mMaterialCount, &mMesh)))
		{
			throw new std::exception();
		}

		mD3dxMaterials = static_cast<LPD3DXMATERIAL>
		                 (materialBuffer->GetBufferPointer());
		mMaterials = new D3DMATERIAL9[static_cast<size_t>(mMaterialCount)];
		mTextures = new LPDIRECT3DTEXTURE9[static_cast<size_t>(mMaterialCount)];

		//create materials and textures
		for (size_t i = 0; i < static_cast<size_t>(mMaterialCount); ++i)
		{
			//grab the material
			mMaterials[i] = mD3dxMaterials[i].MatD3D;
			//set ambient color for material
			mMaterials[i].Ambient = mMaterials[i].Diffuse;
			//materials[i].Emissive = materials[i].Diffuse;
			mMaterials[i].Power = 0.5f;
			//materials[i].Specular = materials[i].Diffuse;
			mTextures[i] = NULL;

			if (mD3dxMaterials[i].pTextureFilename &&
			    mD3dxMaterials[i].pTextureFilename[0] != 0)
			{
#ifndef UNICODE

				if (FAILED(D3DXCreateTextureFromFile(g_engine->getDevice(),
				                                     mD3dxMaterials[i].pTextureFilename, &mTextures[i])))
				{
					throw new std::exception();
				}

#else
				size_t iPathLength = lstrlenA(mD3dxMaterials[i].pTextureFilename);
				wchar_t* szPathW = new wchar_t[iPathLength + 1];
				MultiByteToWideChar(CP_ACP, 0, mD3dxMaterials[i].pTextureFilename,
				                    static_cast<int>(iPathLength),
				                    szPathW, static_cast<int>(iPathLength));
				szPathW[iPathLength] = '\0';

				if (FAILED(D3DXCreateTextureFromFile(g_engine->getDevice(), szPathW,
				                                     &mTextures[i])))
				{
					delete[] szPathW;
					szPathW = NULL;
					throw new std::exception();
				}

				delete[] szPathW;
				szPathW = NULL;
#endif
			}
		}

		//done using material buffer
		materialBuffer->Release();
		materialBuffer = NULL;
	}
}

int Mesh::getFaceCount()
{
	return mMesh->GetNumFaces();
}

int Mesh::getVertexCount()
{
	return mMesh->GetNumVertices();
}

void Mesh::createSphere(float aRadius, int aSlices, int aStacks)
{
	if (FAILED(D3DXCreateSphere(g_engine->getDevice(), aRadius, aSlices, aStacks,
	                            &mMesh,
	                            NULL)))
	{
		throw new std::exception();
	}
}

void Mesh::createCube(float aWidth, float aHeight, float aDepth)
{
	if (FAILED(D3DXCreateBox(g_engine->getDevice(), aWidth, aHeight, aDepth, &mMesh,
	                         NULL)))
	{
		throw new std::exception();
	}
}

void Mesh::rotate(const D3DXVECTOR3& aRotate)
{
	rotate(aRotate.x, aRotate.y, aRotate.z);
}

void Mesh::rotate(float aRotateX, float aRotateY, float aRotateZ)
{
	mRotation.x += aRotateX;
	mRotation.y += aRotateY;
	mRotation.z += aRotateZ;
}

void Mesh::limitBoundary(float aLeft, float aRight, float aTop, float aBottom,
                         float aBack, float aFront)
{
	if (mPosition.x < aLeft || mPosition.x > aRight)
	{
		mVelocity.x *= -1;
	}

	if (mPosition.y < aBottom || mPosition.y > aTop)
	{
		mVelocity.y *= -1;
	}

	if (mPosition.z < aFront || mPosition.z > aBack)
	{
		mVelocity.z *= -1;
	}
}

void Mesh::setPosition(const D3DXVECTOR3& aPosition)
{
	mPosition = aPosition;
}

void Mesh::setPosition(float aPositionX, float aPositionY, float aPositionZ)
{
	mPosition = D3DXVECTOR3(aPositionX, aPositionY, aPositionZ);
}

D3DXVECTOR3 Mesh::getPosition()
{
	return mPosition;
}

void Mesh::setVelocity(const D3DXVECTOR3& aVelocity)
{
	mVelocity = aVelocity;
}

void Mesh::setVelocity(float aVelocityX, float aVelocityY, float aVelocityZ)
{
	mVelocity = D3DXVECTOR3(aVelocityX, aVelocityY, aVelocityZ);
}

D3DXVECTOR3 Mesh::getVelocity()
{
	return mVelocity;
}

void Mesh::setRotation(const D3DXVECTOR3& aRotation)
{
	mRotation = aRotation;
}

void Mesh::setRotation(float aRotationX, float aRotationY, float aRotationZ)
{
	mRotation = D3DXVECTOR3(aRotationX, aRotationY, aRotationZ);
}

D3DXVECTOR3 Mesh::getRotation()
{
	return mRotation;
}

void Mesh::setScale(const D3DXVECTOR3& aScale)
{
	mScale = aScale;
}

void Mesh::setScale(float aScaleX, float aScaleY, float aScaleZ)
{
	mScale = D3DXVECTOR3(aScaleX, aScaleY, aScaleZ);
}

D3DXVECTOR3 Mesh::getScale()
{
	return mScale;
}

void Mesh::draw()
{
	transform();

	if (0 == mMaterialCount)
	{
		mMesh->DrawSubset(0);
		return;
	}

	for (size_t i = 0; i < static_cast<size_t>(mMaterialCount); ++i)
	{
		g_engine->getDevice()->SetMaterial(&mMaterials[i]);

		if (mTextures[i] && D3DRTYPE_TEXTURE == mTextures[i]->GetType())
		{
			D3DSURFACE_DESC desc;
			mTextures[i]->GetLevelDesc(0, &desc);

			if (desc.Width > 0)
			{
				g_engine->getDevice()->SetTexture(0, mTextures[i]);
			}
		}

		if (FAILED(mMesh->DrawSubset(static_cast<DWORD>(i))))
		{
			throw new std::exception();
		}
	}
}

void Mesh::transform()
{
	D3DXMatrixRotationYawPitchRoll(&mMaterialRotate, D3DXToRadian(mRotation.x),
	                               D3DXToRadian(mRotation.y), D3DXToRadian(mRotation.z));
	//set scaling matrix
	D3DXMatrixScaling(&mMaterialScale, mScale.x, mScale.y, mScale.z);
	//set transformation matrix
	D3DXMatrixTranslation(&mMaterialTranslate, mPosition.x, mPosition.y,
	                      mPosition.z);
	//transform the mesh
	mMaterialWorld = mMaterialRotate * mMaterialScale * mMaterialTranslate;

	if (FAILED(g_engine->getDevice()->SetTransform(D3DTS_WORLD, &mMaterialWorld)))
	{
		throw new std::exception();
	}
}

void Mesh::move()
{
	mPosition.x += mVelocity.x;
	mPosition.y += mVelocity.y;
	mPosition.z += mVelocity.z;
}

void Mesh::animate()
{
}

Mesh::~Mesh()
{
	delete [] mMaterials;

	if (mTextures)
	{
		for (size_t i = 0; i < static_cast<size_t>(mMaterialCount); ++i)
		{
			if (mTextures[i])
			{
				mTextures[i]->Release();
			}
		}

		delete [] mTextures;
	}

	if (mMesh)
	{
		mMesh->Release();
	}
}

}
