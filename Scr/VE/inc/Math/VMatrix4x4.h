#pragma once
#include <memory>
#include "Requirements.hpp"
#include "VVector3D.h"
/// <summary>
/// A 4 by 4 Matrix. All values in the indies are set to float by defualt
/// </summary>
///
struct VMatrix4x4
{
public:
	//initalize of the values in the matrix to an identity
	//so if you were to multply this matrix by another 
	// you would get the same thing back
	//Matrix Equivalent to number 1
	VMatrix4x4()
	{
		setIdentity();
	}
	//initalize of the values in the matrix to the values passed in the parameters 
	VMatrix4x4
	(
		float i00, float i01, float i02, float i03,
		float i10, float i11, float i12, float i13,
		float i20, float i21, float i22, float i23,
		float i30, float i31, float i32, float i33
	) 
	{
		this->mat[0][0] = i00;
		this->mat[0][1] = i01;
		this->mat[0][2] = i02;
		this->mat[0][3] = i03;

		this->mat[1][0] = i10;
		this->mat[1][1] = i11;
		this->mat[1][2] = i12;
		this->mat[1][3] = i13;

		this->mat[2][0] = i20;
		this->mat[2][1] = i21;
		this->mat[2][2] = i22;
		this->mat[2][3] = i23;

		this->mat[3][0] = i30;
		this->mat[3][1] = i31;
		this->mat[3][2] = i32;
		this->mat[3][3] = i33;
	}
//initalize of the values in the matrix to an identity
//m4x4 = |1		0		0		0| 
//____       |0		1		0		0|
//____       |0		0		1		0|
//____       |0		0		 0		1|
//so if you were to multply this matrix by another 
//you would get the same thing back
//Matrix Equivalent to number 1
	void setIdentity()
	{
		::memset(mat, 0, sizeof(float) * 16);
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}
	//changes the X, Y, Z coordinates of the object the matrix represents 
	void setTranslation(const VVector3D& translation)
	{
		setIdentity();
		mat[3][0] = translation.X;
		mat[3][1] = translation.Y;
		mat[3][2] = translation.Z;
	}
	//changes the scale of the object the matrix represents 
	void setScale(const VVector3D& scale)
	{
		setIdentity();
		mat[0][0] = scale.X;
		mat[1][1] = scale.Y;
		mat[2][2] = scale.Z;
	}
	//multipies values in the matrix by another matrix 
	void operator *=(const VMatrix4x4& matrix)
	{
		VMatrix4x4 out;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				out.mat[row][col] =
					mat[row][0] * matrix.mat[0][col] + mat[row][1] * matrix.mat[1][col] +
					mat[row][2] * matrix.mat[2][col] + mat[row][3] * matrix.mat[3][col];
			}
		}
		*this = out;
	}
	//set all the values in the matrix to all the value of the matrix that was passed in the parameter
	const VMatrix4x4 operator=(const VMatrix4x4& matrix)
	{
		::memcpy(mat, matrix.mat, sizeof(float) * 16);
		return *this;
	}
	//an algorithime that allows us to present a 3D Scene/World on a 2D surface, where the scene
	//doesn't accully look 3d, when the scene is presented the line are parallel 
	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		mat[0][0] = (1.0f / width);
		mat[1][1] =(1.0f / height);
		mat[2][2] = (1.0f / (far_plane - near_plane));
		mat[3][2] = ( - (near_plane / (far_plane - near_plane)));
	}
	//rotates an object on the X using degress
	void setRotationX(float theta_degrees)
	{
		//degrees to radians
		float theta_radians = ((theta_degrees) * 3.14159265358979323846F / 180.0F);
		setIdentity();
		this->mat[1][1] = cosf(theta_radians);
		this->mat[1][2] = -sinf(theta_radians);
		this->mat[2][1] = sinf(theta_radians);
		this->mat[2][2] = cosf(theta_radians);
	}
	//rotates an object on the Y using degress
	void setRotationY(float theta_degrees)
	{
		//degrees to radians
		float theta_radians = ((theta_degrees) * 3.14159265358979323846F / 180.0F);
		setIdentity();
		this->mat[0][0] = cosf(theta_radians);
		this->mat[0][2] = sinf(theta_radians);
		this->mat[2][0] = -sinf(theta_radians);
		this->mat[2][2] = cosf(theta_radians);
	}
	//rotates an object on the Z using degress
	void setRotationZ(float theta_degrees)
	{
		//degrees to radians
		float theta_radians = ((theta_degrees) * 3.14159265358979323846F / 180.0F);
		setIdentity();
		this->mat[0][0] = cosf(theta_radians);
		this->mat[0][1] = -sinf(theta_radians);
		this->mat[1][0] = sinf(theta_radians);
		this->mat[1][1] = cosf(theta_radians);
	}
	
public:
	union
	{
		//4 by 4 matrix 
		struct
		{
			float mat[4][4];
		};
		//all the varaable in the matrix 
		struct
		{
			float i00, i01, i02, i03;
			float i10, i11, i12, i13;
			float i20, i21, i22, i23;
			float i30, i31, i32, i33;
		};
	};
	

};