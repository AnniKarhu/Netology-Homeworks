#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>
#include <algorithm> 


Shape::Shape(int _type, int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8)
{
	set_shape_type(_type);
	
	v_X[0] = _x1; v_Y[0] = _y1; v_Z[0] = _z1;
	v_X[1] = _x2; v_Y[1] = _y2; v_Z[1] = _z2;
	v_X[2] = _x3; v_Y[2] = _y3; v_Z[2] = _z3;
	v_X[3] = _x4; v_Y[3] = _y4; v_Z[3] = _z4;
	v_X[4] = _x5; v_Y[4] = _y5; v_Z[4] = _z5;
	v_X[5] = _x6; v_Y[5] = _y6; v_Z[5] = _z6;
	v_X[6] = _x7; v_Y[6] = _y7; v_Z[6] = _z7;
	v_X[7] = _x8; v_Y[7] = _y8; v_Z[7] = _z8;
	
	renew_X_Y_Z();
	_calculate_VS->calculate_VS(*this);
}

Shape::Shape(int _type, int _x1, int _y1, double R, double H)
{
	set_shape_type(_type);

	x1 = _x1; y1 = _y1;
	radius = R;
	height = H;		

	_calculate_VS->calculate_VS(*this);
}

void Shape::set_shape_type(int _type)
{
	type = _type;
	switch (type) 
	{
	case line:
		_calculate_VS = std::make_shared<LineVolumeSquare>();
		break;
	case sqr:
		_calculate_VS = std::make_shared<SqrVolumeSquare>();
		break;
	case cube:
		_calculate_VS = std::make_shared<CubeVolumeSquare>();
		break;
	case circle:
		_calculate_VS = std::make_shared<CircleVolumeSquare>();
		break;
	case cylinder:
		_calculate_VS = std::make_shared<cylinderVolumeSquare>();
		break;
	default:
		throw std::runtime_error("Incorrect shape type");
	}
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

int Shape::side_a()
{
	return (abs(v_X[0] - v_X[1]));
}
int Shape::side_b()
{
	return (abs(v_Y[0] - v_Y[1]));
}

int Shape::side_c()
{
	return (abs(v_Z[0] - v_Z[1]));
}



void Shape::shift(int m, int n, int k)
{
	for (auto& elem : v_X) { elem += m; }
	for (auto& elem : v_Y) { elem += n; }
	for (auto& elem : v_Z) { elem += k; }
			
	renew_X_Y_Z();
	_calculate_VS->calculate_VS(*this);
}

void Shape::scaleX(int a)
{
	for (auto& elem : v_X) { elem *= a; }
		
	renew_X_Y_Z();
	_calculate_VS->calculate_VS(*this);
}

void Shape::scaleY(int d)
{
	for (auto& elem : v_Y) { elem *= d; }
	
	renew_X_Y_Z();
	_calculate_VS->calculate_VS(*this);
}

void Shape::scaleZ(int e)
{
	for (auto& elem : v_Z) { elem *= e; }
	
	renew_X_Y_Z();
	_calculate_VS->calculate_VS(*this);
}

void Shape::scale(int s)
{
	for (auto& elem : v_X) { elem /= s; }
	for (auto& elem : v_Y) { elem /= s; }
	for (auto& elem : v_Z) { elem /= s; }
		
	renew_X_Y_Z();
	_calculate_VS->calculate_VS(*this);	
}


void LineVolumeSquare::calculate_VS(Shape& shp) 
{
	shp.volume = 0;
	shp.square = 0;
}

void SqrVolumeSquare::calculate_VS(Shape& shp) 
{
	shp.volume = 0;
	shp.square = shp.side_a() * shp.side_b();
}

void CubeVolumeSquare::calculate_VS(Shape& shp)
{
	shp.square = 2 * shp.side_a() * shp.side_b() + 2 * shp.side_a() * shp.side_c() + 2 * shp.side_b() * shp.side_c();
	shp.volume = shp.side_a() * shp.side_b() * shp.side_c();
}


void CircleVolumeSquare::calculate_VS(Shape& shp) 
{
	shp.volume = 0;
	shp.square = M_PI * shp.radius * shp.radius;
}

void cylinderVolumeSquare::calculate_VS(Shape& shp) 
{
	shp.square = M_PI * shp.radius * shp.radius + 2 * shp.radius * shp.height;
	shp.volume = M_PI * shp.radius * shp.radius * shp.height;
}


