
#include "Vector3.h"
#include <gtest/gtest.h>

class TestVector3Bool : public testing::Test
{
public:
	Advanced2D::Vector3<bool>* mVector1;
	Advanced2D::Vector3<bool>* mVector2;
protected:
	TestVector3Bool() : mVector1(NULL), mVector2(NULL)
	{
	}
	virtual void SetUp()
	{
		mVector1 = new Advanced2D::Vector3<bool>();
		mVector2 = new Advanced2D::Vector3<bool>();
	}
	virtual void TearDown()
	{
		delete mVector1;
		delete mVector2;
	}
	virtual ~TestVector3Bool()
	{
		mVector1 = NULL;
		mVector2 = NULL;
	}
};

TEST_F(TestVector3Bool, equal)
{
	ASSERT_TRUE((*mVector1) == (*mVector2));
	mVector1->mX = true;
	mVector1->mY = false;
	mVector1->mZ = true;
	//
	mVector2->mX = false;
	mVector2->mY = true;
	mVector2->mZ = false;
	ASSERT_FALSE((*mVector1) == (*mVector2));
}

TEST_F(TestVector3Bool, notEqual)
{
	ASSERT_FALSE((*mVector1) != (*mVector2));
	mVector1->mX = true;
	mVector1->mY = false;
	mVector1->mZ = true;
	//
	mVector2->mX = false;
	mVector2->mY = true;
	mVector2->mZ = false;
	ASSERT_TRUE((*mVector1) != (*mVector2));
}

class TestVector3Char : public testing::Test
{
public:
	Advanced2D::Vector3<char>* mVector1;
	Advanced2D::Vector3<char>* mVector2;
protected:
	TestVector3Char() : mVector1(NULL), mVector2(NULL)
	{
	}
	virtual void SetUp()
	{
		mVector1 = new Advanced2D::Vector3<char>();
		mVector2 = new Advanced2D::Vector3<char>();
	}
	virtual void TearDown()
	{
		delete mVector1;
		delete mVector2;
	}
	virtual ~TestVector3Char()
	{
		mVector1 = NULL;
		mVector2 = NULL;
	}
};

TEST_F(TestVector3Char, move)
{
}

TEST_F(TestVector3Char, plus)
{
}

TEST_F(TestVector3Char, minus)
{
}

TEST_F(TestVector3Char, multiplication)
{
}

TEST_F(TestVector3Char, divide)
{
}

TEST_F(TestVector3Char, equal)
{
	ASSERT_TRUE((*mVector1) == (*mVector2));
	mVector1->mX = 4;
	mVector1->mY = 9;
	mVector1->mZ = 16;
	//
	mVector2->mX = 2;
	mVector2->mY = 3;
	mVector2->mZ = 4;
	ASSERT_FALSE((*mVector1) == (*mVector2));
}

TEST_F(TestVector3Char, notEqual)
{
	ASSERT_FALSE((*mVector1) != (*mVector2));
	mVector1->mX = 4;
	mVector1->mY = 9;
	mVector1->mZ = 16;
	//
	mVector2->mX = 2;
	mVector2->mY = 3;
	mVector2->mZ = 4;
	ASSERT_TRUE((*mVector1) != (*mVector2));
}

TEST_F(TestVector3Char, appropriation)
{
}

TEST_F(TestVector3Char, distance2d)
{
}

TEST_F(TestVector3Char, length)
{
}

TEST_F(TestVector3Char, dotProduct)
{
}

TEST_F(TestVector3Char, crossProduct)
{
}

TEST_F(TestVector3Char, normal)
{
}

class TestVector3Int : public testing::Test
{
public:
	Advanced2D::Vector3<int>* mVector1;
	Advanced2D::Vector3<int>* mVector2;
protected:
	TestVector3Int() : mVector1(NULL), mVector2(NULL)
	{
	}
	virtual void SetUp()
	{
		mVector1 = new Advanced2D::Vector3<int>();
		mVector2 = new Advanced2D::Vector3<int>();
	}
	virtual void TearDown()
	{
		delete mVector1;
		delete mVector2;
	}
	virtual ~TestVector3Int()
	{
		mVector1 = NULL;
		mVector2 = NULL;
	}
};

TEST_F(TestVector3Int, move)
{
}

TEST_F(TestVector3Int, plus)
{
}

TEST_F(TestVector3Int, minus)
{
}

TEST_F(TestVector3Int, multiplication)
{
}

TEST_F(TestVector3Int, divide)
{
}

TEST_F(TestVector3Int, equal)
{
	ASSERT_TRUE((*mVector1) == (*mVector2));
	mVector1->mX = 4;
	mVector1->mY = 9;
	mVector1->mZ = 16;
	//
	mVector2->mX = 2;
	mVector2->mY = 3;
	mVector2->mZ = 4;
	ASSERT_FALSE((*mVector1) == (*mVector2));
}

TEST_F(TestVector3Int, notEqual)
{
	ASSERT_FALSE((*mVector1) != (*mVector2));
	mVector1->mX = 4;
	mVector1->mY = 9;
	mVector1->mZ = 16;
	//
	mVector2->mX = 2;
	mVector2->mY = 3;
	mVector2->mZ = 4;
	ASSERT_TRUE((*mVector1) != (*mVector2));
}

TEST_F(TestVector3Int, appropriation)
{
}

TEST_F(TestVector3Int, distance2d)
{
}

TEST_F(TestVector3Int, length)
{
}

TEST_F(TestVector3Int, dotProduct)
{
}

TEST_F(TestVector3Int, crossProduct)
{
}

TEST_F(TestVector3Int, normal)
{
}

class TestVector3Long : public testing::Test
{
public:
	Advanced2D::Vector3<long>* mVector1;
	Advanced2D::Vector3<long>* mVector2;
protected:
	TestVector3Long() : mVector1(NULL), mVector2(NULL)
	{
	}
	virtual void SetUp()
	{
		mVector1 = new Advanced2D::Vector3<long>();
		mVector2 = new Advanced2D::Vector3<long>();
	}
	virtual void TearDown()
	{
		delete mVector1;
		delete mVector2;
	}
	virtual ~TestVector3Long()
	{
		mVector1 = NULL;
		mVector2 = NULL;
	}
};

TEST_F(TestVector3Long, move)
{
}

TEST_F(TestVector3Long, plus)
{
}

TEST_F(TestVector3Long, minus)
{
}

TEST_F(TestVector3Long, multiplication)
{
}

TEST_F(TestVector3Long, divide)
{
}

TEST_F(TestVector3Long, equal)
{
	ASSERT_TRUE((*mVector1) == (*mVector2));
	mVector1->mX = 4;
	mVector1->mY = 9;
	mVector1->mZ = 16;
	//
	mVector2->mX = 2;
	mVector2->mY = 3;
	mVector2->mZ = 4;
	ASSERT_FALSE((*mVector1) == (*mVector2));
}

TEST_F(TestVector3Long, notEqual)
{
	ASSERT_FALSE((*mVector1) != (*mVector2));
	mVector1->mX = 4;
	mVector1->mY = 9;
	mVector1->mZ = 16;
	//
	mVector2->mX = 2;
	mVector2->mY = 3;
	mVector2->mZ = 4;
	ASSERT_TRUE((*mVector1) != (*mVector2));
}

TEST_F(TestVector3Long, appropriation)
{
}

TEST_F(TestVector3Long, distance2d)
{
}

TEST_F(TestVector3Long, length)
{
}

TEST_F(TestVector3Long, dotProduct)
{
}

TEST_F(TestVector3Long, crossProduct)
{
}

TEST_F(TestVector3Long, normal)
{
}

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

TEST_F(TestVector3Float, distance2d)
{
	mVector1->mX = 1.0f;
	mVector1->mY = 1.0f;
	mVector1->mZ = 0.0f;
	//
	mVector2->mX = 2.0f;
	mVector2->mY = 2.0f;
	mVector2->mZ = 0.0f;
	//
	ASSERT_FLOAT_EQ(sqrt(2.0f), mVector1->distance2d(*mVector2));
	ASSERT_FLOAT_EQ(sqrt(2.0f), mVector2->distance2d(*mVector1));
	ASSERT_FLOAT_EQ(0, mVector1->distance2d(*mVector1));
	ASSERT_FLOAT_EQ(0, mVector2->distance2d(*mVector2));
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
	ASSERT_EQ(Advanced2D::Vector3<float>(sqrt(0.5f), sqrt(0.5f), 0),
	          mVector1->normal());
	ASSERT_EQ(Advanced2D::Vector3<float>(sqrt(0.5f), sqrt(0.5f), 0),
	          mVector2->normal());
}

class TestVector3Double : public testing::Test
{
public:
	Advanced2D::Vector3<double>* mVector1;
	Advanced2D::Vector3<double>* mVector2;
protected:
	TestVector3Double() : mVector1(NULL), mVector2(NULL)
	{
	}
	virtual void SetUp()
	{
		mVector1 = new Advanced2D::Vector3<double>();
		mVector2 = new Advanced2D::Vector3<double>();
	}
	virtual void TearDown()
	{
		delete mVector1;
		delete mVector2;
	}
	virtual ~TestVector3Double()
	{
		mVector1 = NULL;
		mVector2 = NULL;
	}
};

TEST_F(TestVector3Double, move)
{
	ASSERT_EQ(0, mVector1->mX);
	ASSERT_EQ(0, mVector1->mY);
	ASSERT_EQ(0, mVector1->mZ);
	mVector1->move(1.0, 2.0, 3.0);
	ASSERT_DOUBLE_EQ(1.0, mVector1->mX);
	ASSERT_DOUBLE_EQ(2.0, mVector1->mY);
	ASSERT_DOUBLE_EQ(3.0, mVector1->mZ);
}

TEST_F(TestVector3Double, plus)
{
	mVector1->mX = 1.0;
	mVector1->mY = 2.0;
	mVector1->mZ = 3.0;
	//
	mVector2->mX = 4.0;
	mVector2->mY = 5.0;
	mVector2->mZ = 6.0;
	//
	(*mVector1) += (*mVector2);
	//
	ASSERT_DOUBLE_EQ(5.0, mVector1->mX);
	ASSERT_DOUBLE_EQ(7.0, mVector1->mY);
	ASSERT_DOUBLE_EQ(9.0, mVector1->mZ);
}

TEST_F(TestVector3Double, minus)
{
	mVector1->mX = 1.0;
	mVector1->mY = 2.0;
	mVector1->mZ = 3.0;
	//
	mVector2->mX = 4.0;
	mVector2->mY = 5.0;
	mVector2->mZ = 6.0;
	//
	(*mVector1) -= (*mVector2);
	//
	ASSERT_DOUBLE_EQ(-3.0, mVector1->mX);
	ASSERT_DOUBLE_EQ(-3.0, mVector1->mY);
	ASSERT_DOUBLE_EQ(-3.0, mVector1->mZ);
}

TEST_F(TestVector3Double, multiplication)
{
	mVector1->mX = 1.0;
	mVector1->mY = 2.0;
	mVector1->mZ = 3.0;
	//
	mVector2->mX = 4.0;
	mVector2->mY = 5.0;
	mVector2->mZ = 6.0;
	//
	(*mVector1) *= (*mVector2);
	//
	ASSERT_DOUBLE_EQ(4.0, mVector1->mX);
	ASSERT_DOUBLE_EQ(10.0, mVector1->mY);
	ASSERT_DOUBLE_EQ(18.0, mVector1->mZ);
}

TEST_F(TestVector3Double, divide)
{
	mVector1->mX = 4.0;
	mVector1->mY = 9.0;
	mVector1->mZ = 16.0;
	//
	mVector2->mX = 2.0;
	mVector2->mY = 3.0;
	mVector2->mZ = 4.0;
	//
	(*mVector1) /= (*mVector2);
	//
	ASSERT_DOUBLE_EQ(2.0, mVector1->mX);
	ASSERT_DOUBLE_EQ(3.0, mVector1->mY);
	ASSERT_DOUBLE_EQ(4.0, mVector1->mZ);
}

TEST_F(TestVector3Double, equal)
{
	ASSERT_TRUE((*mVector1) == (*mVector2));
	mVector1->mX = 4.0;
	mVector1->mY = 9.0;
	mVector1->mZ = 16.0;
	//
	mVector2->mX = 2.0;
	mVector2->mY = 3.0;
	mVector2->mZ = 4.0;
	ASSERT_FALSE((*mVector1) == (*mVector2));
}

TEST_F(TestVector3Double, notEqual)
{
	ASSERT_FALSE((*mVector1) != (*mVector2));
	mVector1->mX = 4.0;
	mVector1->mY = 9.0;
	mVector1->mZ = 16.0;
	//
	mVector2->mX = 2.0;
	mVector2->mY = 3.0;
	mVector2->mZ = 4.0;
	ASSERT_TRUE((*mVector1) != (*mVector2));
}

TEST_F(TestVector3Double, appropriation)
{
	mVector1->mX = 4.0;
	mVector1->mY = 9.0;
	mVector1->mZ = 16.0;
	//
	mVector2->mX = 2.0;
	mVector2->mY = 3.0;
	mVector2->mZ = 4.0;
	ASSERT_FALSE((*mVector1) == (*mVector2));
	(*mVector1) = (*mVector2);
	ASSERT_TRUE((*mVector1) == (*mVector2));
}

TEST_F(TestVector3Double, distance2d)
{
	mVector1->mX = 1.0;
	mVector1->mY = 1.0;
	mVector1->mZ = 0.0;
	//
	mVector2->mX = 2.0;
	mVector2->mY = 2.0;
	mVector2->mZ = 0.0;
	//
	ASSERT_DOUBLE_EQ(sqrt(2.0), mVector1->distance2d(*mVector2));
	ASSERT_DOUBLE_EQ(sqrt(2.0), mVector2->distance2d(*mVector1));
	ASSERT_DOUBLE_EQ(0, mVector1->distance2d(*mVector1));
	ASSERT_DOUBLE_EQ(0, mVector2->distance2d(*mVector2));
}

TEST_F(TestVector3Double, length)
{
	ASSERT_DOUBLE_EQ(0, mVector1->length());
	mVector1->mX = 1.0;
	mVector1->mY = 1.0;
	mVector1->mZ = 0.0;
	ASSERT_DOUBLE_EQ(sqrt(2.0), mVector1->length());
}

TEST_F(TestVector3Double, dotProduct)
{
	ASSERT_DOUBLE_EQ(0, mVector1->dotProduct(*mVector2));
	//
	mVector1->mX = 1.0;
	mVector1->mY = 2.0;
	mVector1->mZ = 3.0;
	//
	mVector2->mX = 4.0;
	mVector2->mY = 5.0;
	mVector2->mZ = 6.0;
	//
	ASSERT_DOUBLE_EQ(32, mVector1->dotProduct(*mVector2));
}

TEST_F(TestVector3Double, crossProduct)
{
	Advanced2D::Vector3<double> v(*mVector1);
	ASSERT_EQ(v, mVector1->crossProduct(*mVector2));
	//
	mVector1->mX = 1.0;
	mVector1->mY = 2.0;
	mVector1->mZ = 3.0;
	//
	mVector2->mX = 4.0;
	mVector2->mY = 5.0;
	mVector2->mZ = 6.0;
	//
	v = Advanced2D::Vector3<double>(-3, 9, -3);
	ASSERT_EQ(v, mVector1->crossProduct(*mVector2));
}

TEST_F(TestVector3Double, normal)
{
	ASSERT_EQ(*mVector1, mVector2->normal());
	mVector1->mX = 1.0;
	mVector1->mY = 1.0;
	mVector1->mZ = 0.0;
	//
	mVector2->mX = 3.0;
	mVector2->mY = 3.0;
	mVector2->mZ = 0.0;
	//
	ASSERT_EQ(Advanced2D::Vector3<double>(sqrt(0.5), sqrt(0.5), 0),
	          mVector1->normal());
	ASSERT_EQ(Advanced2D::Vector3<double>(sqrt(0.5), sqrt(0.5), 0),
	          mVector2->normal());
}
