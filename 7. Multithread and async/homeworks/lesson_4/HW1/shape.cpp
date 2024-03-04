#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>
#include <algorithm> 

Shape::Shape(int _type, int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8)
{
	type = _type;
	
	v_X[0] = _x1; v_Y[0] = _y1; v_Z[0] = _z1;
	v_X[1] = _x2; v_Y[1] = _y2; v_Z[1] = _z2;
	v_X[2] = _x3; v_Y[2] = _y3; v_Z[2] = _z3;
	v_X[3] = _x4; v_Y[3] = _y4; v_Z[3] = _z4;
	v_X[4] = _x5; v_Y[4] = _y5; v_Z[4] = _z5;
	v_X[5] = _x6; v_Y[5] = _y6; v_Z[5] = _z6;
	v_X[6] = _x7; v_Y[6] = _y7; v_Z[6] = _z7;
	v_X[7] = _x8; v_Y[7] = _y8; v_Z[7] = _z8;
	
	renew_X_Y_Z();
	calculate_square_and_volume();	

}

Shape::Shape(int _type, int _x1, int _y1, double R, double H)
{
	type = _type;
	
	x1 = _x1; y1 = _y1;
	radius = R;
	height = H;		

	calculate_square_and_volume();

}

void Shape::renew_X_Y_Z()
{
	x1 = v_X[0]; y1 = v_Y[0]; z1 = v_Z[0];
	x2 = v_X[1]; y2 = v_Y[1]; z2 = v_Z[1];
	x3 = v_X[2]; y3 = v_Y[2]; z3 = v_Z[2];
	x4 = v_X[3]; y4 = v_Y[3]; z4 = v_Z[3];
	x5 = v_X[4]; y5 = v_Y[4]; z5 = v_Z[4];
	x6 = v_X[5]; y6 = v_Y[5]; z6 = v_Z[5];
	x7 = v_X[6]; y7 = v_Y[6]; z7 = v_Z[6];
	x8 = v_X[7]; y8 = v_Y[7]; z8 = v_Z[7];
}

void Shape::calculate_square_and_volume()
{
	// стороны фигуры
	int a = abs(v_X[0] - v_X[1]);
	int b = abs(v_Y[0] - v_Y[1]);
	int c = abs(v_Z[0] - v_Z[1]);

		
	// считаем площадь и объем фигуры
	switch (type)
	{
	case line:
		square = 0;
		volume = 0;
		break;
	case sqr:
		square = a * b;
		volume = 0;
		break;
	case cube:
		square = 2 * a * b + 2 * a * c + 2 * b * c;
		volume = a * b * c;
		break;
	case circle:
		square = M_PI * radius * radius;
		volume = 0;
		break;
	case cylinder:
		square = M_PI * radius * radius + 2 * radius * height;
		volume = M_PI * radius * radius * height;
		break;
	default:
		break;
	}
}

void Shape::shift(int m, int n, int k)
{
	for (auto& elem : v_X) {	elem += m; }
	for (auto& elem : v_Y) { elem += n; }
	for (auto& elem : v_Z) { elem += k; }
			
	renew_X_Y_Z();

	calculate_square_and_volume();
}

void Shape::scaleX(int a)
{
	for (auto& elem : v_X) { elem *= a; }
		
	renew_X_Y_Z();
	calculate_square_and_volume();
}

void Shape::scaleY(int d)
{
	for (auto& elem : v_Y) { elem *= d; }
	
	renew_X_Y_Z();
	calculate_square_and_volume();
}

void Shape::scaleZ(int e)
{
	for (auto& elem : v_Z) { elem *= e; }
	
	renew_X_Y_Z();
	calculate_square_and_volume();
}

void Shape::scale(int s)
{
	for (auto& elem : v_X) { elem /= s; }
	for (auto& elem : v_Y) { elem /= s; }
	for (auto& elem : v_Z) { elem /= s; }
		
	renew_X_Y_Z();

	calculate_square_and_volume();
}

