
#include "Vector3.h"
#include <gtest/gtest.h>

class TestVector3Float : public testing::Test
{
public:
	Advanced2D::Vector3<float>* mVector1;
	Advanced2D::Vector3<float>* mVector2;
protected:
	TestVector3Float() : mVector1(NULL), mVector2(NULL)
	{
	}
	virtual void SetUp()
	{
		mVector1 = new Advanced2D::Vector3<float>();
		mVector2 = new Advanced2D::Vector3<float>();
	}
	virtual void TearDown()
	{
		delete mVector1;
		delete mVector2;
	}
	virtual ~TestVector3Float()
	{
		mVector1 = NULL;
		mVector2 = NULL;
	}
};

TEST_F(TestVector3Float, move)
{
	ASSERT_EQ(0, mVector1->mX);
	ASSERT_EQ(0, mVector1->mY);
	ASSERT_EQ(0, mVector1->mZ);
	mVector1->move(1.0f, 2.0f, 3.0f);
	ASSERT_FLOAT_EQ(1.0f, mVector1->mX);
	ASSERT_FLOAT_EQ(2.0f, mVector1->mY);
	ASSERT_FLOAT_EQ(3.0f, mVector1->mZ);
}

TEST_F(TestVector3Float, plus)
{
	mVector1->mX = 1.0f;
	mVector1->mY = 2.0f;
	mVector1->mZ = 3.0f;
	//
	mVector2->mX = 4.0f;
	mVector2->mY = 5.0f;
	mVector2->mZ = 6.0f;
	//
	(*mVector1) += (*mVector2);
	//
	ASSERT_FLOAT_EQ(5.0f, mVector1->mX);
	ASSERT_FLOAT_EQ(7.0f, mVector1->mY);
	ASSERT_FLOAT_EQ(9.0f, mVector1->mZ);
}

TEST_F(TestVector3Float, minus)
{
	mVector1->mX = 1.0f;
	mVector1->mY = 2.0f;
	mVector1->mZ = 3.0f;
	//
	mVector2->mX = 4.0f;
	mVector2->mY = 5.0f;
	mVector2->mZ = 6.0f;
	//
	(*mVector1) -= (*mVector2);
	//
	ASSERT_FLOAT_EQ(-3.0f, mVector1->mX);
	ASSERT_FLOAT_EQ(-3.0f, mVector1->mY);
	ASSERT_FLOAT_EQ(-3.0f, mVector1->mZ);
}

TEST_F(TestVector3Float, multiplication)
{
	mVector1->mX = 1.0f;
	mVector1->mY = 2.0f;
	mVector1->mZ = 3.0f;
	//
	mVector2->mX = 4.0f;
	mVector2->mY = 5.0f;
	mVector2->mZ = 6.0f;
	//
	(*mVector1) *= (*mVector2);
	//
	ASSERT_FLOAT_EQ(4.0f, mVector1->mX);
	ASSERT_FLOAT_EQ(10.0f, mVector1->mY);
	ASSERT_FLOAT_EQ(18.0f, mVector1->mZ);
}

TEST_F(TestVector3Float, divide)
{
	mVector1->mX = 4.0f;
	mVector1->mY = 9.0f;
	mVector1->mZ = 16.0f;
	//
	mVector2->mX = 2.0f;
	mVector2->mY = 3.0f;
	mVector2->mZ = 4.0f;
	//
	(*mVector1) /= (*mVector2);
	//
	ASSERT_FLOAT_EQ(2.0f, mVector1->mX);
	ASSERT_FLOAT_EQ(3.0f, mVector1->mY);
	ASSERT_FLOAT_EQ(4.0f, mVector1->mZ);
}

TEST_F(TestVector3Float, equal)
{
	ASSERT_TRUE((*mVector1) == (*mVector2));
	mVector1->mX = 4.0f;
	mVector1->mY = 9.0f;
	mVector1->mZ = 16.0f;
	//
	mVector2->mX = 2.0f;
	mVector2->mY = 3.0f;
	mVector2->mZ = 4.0f;
	ASSERT_FALSE((*mVector1) == (*mVector2));
}

TEST_F(TestVector3Float, notEqual)
{
	ASSERT_FALSE((*mVector1) != (*mVector2));
	mVector1->mX = 4.0f;
	mVector1->mY = 9.0f;
	mVector1->mZ = 16.0f;
	//
	mVector2->mX = 2.0f;
	mVector2->mY = 3.0f;
	mVector2->mZ = 4.0f;
	ASSERT_TRUE((*mVector1) != (*mVector2));
}

TEST_F(TestVector3Float, appropriation)
{
	mVector1->mX = 4.0f;
	mVector1->mY = 9.0f;
	mVector1->mZ = 16.0f;
	//
	mVector2->mX = 2.0f;
	mVector2->mY = 3.0f;
	mVector2->mZ = 4.0f;
	ASSERT_FALSE((*mVector1) == (*mVector2));
	(*mVector1) = (*mVector2);
	ASSERT_TRUE((*mVector1) == (*mVector2));
}

TEST_F(TestVector3Float, distance2D)
{
	mVector1->mX = 1.0f;
	mVector1->mY = 1.0f;
	mVector1->mZ = 0.0f;
	//
	mVector2->mX = 2.0f;
	mVector2->mY = 2.0f;
	mVector2->mZ = 0.0f;
	//
	ASSERT_FLOAT_EQ(sqrt(2.0f), mVector1->distance2D(*mVector2));
	ASSERT_FLOAT_EQ(sqrt(2.0f), mVector2->distance2D(*mVector1));
	ASSERT_FLOAT_EQ(0, mVector1->distance2D(*mVector1));
	ASSERT_FLOAT_EQ(0, mVector2->distance2D(*mVector2));
}

TEST_F(TestVector3Float, length)
{
	ASSERT_FLOAT_EQ(0, mVector1->length());
	mVector1->mX = 1.0f;
	mVector1->mY = 1.0f;
	mVector1->mZ = 0.0f;
	ASSERT_FLOAT_EQ(sqrt(2.0f), mVector1->length());
}

TEST_F(TestVector3Float, dotProduct)
{
	ASSERT_FLOAT_EQ(0, mVector1->dotProduct(*mVector2));
	//
	mVector1->mX = 1.0f;
	mVector1->mY = 2.0f;
	mVector1->mZ = 3.0f;
	//
	mVector2->mX = 4.0f;
	mVector2->mY = 5.0f;
	mVector2->mZ = 6.0f;
	//
	ASSERT_FLOAT_EQ(32, mVector1->dotProduct(*mVector2));
}

TEST_F(TestVector3Float, crossProduct)
{
	Advanced2D::Vector3<float> v(*mVector1);
	ASSERT_EQ(v, mVector1->crossProduct(*mVector2));
	//
	mVector1->mX = 1.0f;
	mVector1->mY = 2.0f;
	mVector1->mZ = 3.0f;
	//
	mVector2->mX = 4.0f;
	mVector2->mY = 5.0f;
	mVector2->mZ = 6.0f;
	//
	v = Advanced2D::Vector3<float>(-3, 9, -3);
	ASSERT_EQ(v, mVector1->crossProduct(*mVector2));
}

TEST_F(TestVector3Float, normal)
{
	ASSERT_EQ(*mVector1, mVector2->normal());
	mVector1->mX = 1.0f;
	mVector1->mY = 1.0f;
	mVector1->mZ = 0.0f;
	//
	mVector2->mX = 3.0f;
	mVector2->mY = 3.0f;
	mVector2->mZ = 0.0f;
	//
	ASSERT_EQ(Advanced2D::Vector3<float>(sqrt(0.5), sqrt(0.5), 0),
	          mVector1->normal());
	ASSERT_EQ(Advanced2D::Vector3<float>(sqrt(0.5), sqrt(0.5), 0),
	          mVector2->normal());
}

