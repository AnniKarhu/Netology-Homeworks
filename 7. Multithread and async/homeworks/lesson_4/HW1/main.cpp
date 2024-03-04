#include <iostream>
#include <tuple>

#include "shape.h"
#include "transform.h"


std::tuple<double, double> get_shape_info(const Shape& shp)
{
	auto result_tuple = std::make_tuple(shp.square, shp.volume);
	return result_tuple;
}

void print_shape_info(const Shape& shp)
{	
	std::cout << "volume: " << shp.volume << "\n"; //0
	std::cout << "square: " << shp.square << "\n"; //0
}

int main()
{
	std::cout << "Hello\n";
		
	int sh_type = 0;
	int x1 = 0, y1 = 0, z1 = 0,
		x2 = 5, y2 = 5, z2 = 0,
		x3 = 0, y3 = 0, z3 = 0,
		x4 = 0, y4 = 0, z4 = 0,
		x5 = 0, y5 = 0, z5 = 0,
		x6 = 0, y6 = 0, z6 = 0,
		x7 = 0, y7 = 0, z7 = 0,
		x8 = 0, y8 = 0, z8 = 0;
	
	int shift_m = 1, shift_n = 1, shift_k = 1;
	int scale_a = 2, scale_d = 3, scale_e = 4, scale_s = 5;

	std::cout << "Line:\n";
	Shape shape_line(sh_type, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8);
	print_shape_info(shape_line);
	
	transform trfrm_shape_line(shape_line);
	
	std::cout << "transform shift: m=" << shift_m << ", n=" << shift_n << ", k=" << shift_k << "\n";
    Shape shape_line1 = trfrm_shape_line.shift(shift_m, shift_n, shift_k);
	print_shape_info(shape_line1);
	
	std::cout << "transform ScaleX: " << scale_a << "\n";
	Shape shape_line2 = trfrm_shape_line.scaleX(scale_a);
	print_shape_info(shape_line2);

	std::cout << "transform ScaleY: " << scale_d << "\n";
	Shape shape_line3 = trfrm_shape_line.scaleY(scale_d);
	print_shape_info(shape_line3);

	std::cout << "transform ScaleZ: " << scale_e << "\n";
	Shape shape_line4 = trfrm_shape_line.scaleZ(scale_e);
	print_shape_info(shape_line4);

	std::cout << "transform scale: " << scale_s << "\n";
	Shape shape_line5 =  trfrm_shape_line.scale(scale_s);
	print_shape_info(shape_line5);
	std::cout << "\n\n";

	std::cout << "sqr:\n";
	sh_type = 1;
	
	Shape shape_sqr(sh_type, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8);
	print_shape_info(shape_sqr);

	transform trfrm_shape_sqr(shape_sqr);

	std::cout << "transform shift: m=" << shift_m << ", n=" << shift_n << ", k=" << shift_k << "\n";
	Shape shape_sqr1 = trfrm_shape_sqr.shift(shift_m, shift_n, shift_k);
	print_shape_info(shape_sqr1);

	std::cout << "transform ScaleX: " << scale_a << "\n";
	Shape shape_sqr2 = trfrm_shape_sqr.scaleX(scale_a);
	print_shape_info(shape_sqr2);

	std::cout << "transform ScaleY: " << scale_d << "\n";
	Shape shape_sqr3 = trfrm_shape_sqr.scaleY(scale_d);
	print_shape_info(shape_sqr3);

	std::cout << "transform ScaleZ: " << scale_e << "\n";
	Shape shape_sqr4 = trfrm_shape_sqr.scaleZ(scale_e);
	print_shape_info(shape_sqr4);

	std::cout << "transform scale: " << scale_s << "\n";
	Shape shape_sqr5 = trfrm_shape_sqr.scale(scale_s);
	print_shape_info(shape_sqr5);
	std::cout << "\n\n";
	

	std::cout << "cube:\n";	
	sh_type = 2;
	z2 = 5;
	Shape shape_cube(sh_type, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8);
	print_shape_info(shape_cube);

	transform trfrm_shape_cube(shape_cube);

	std::cout << "transform shift: m=" << shift_m << ", n=" << shift_n << ", k=" << shift_k << "\n";
	Shape shape_cube1 = trfrm_shape_cube.shift(shift_m, shift_n, shift_k);
	print_shape_info(shape_cube1);

	std::cout << "transform ScaleX: " << scale_a << "\n";
	Shape shape_cube2 = trfrm_shape_cube.scaleX(scale_a);
	print_shape_info(shape_cube2);

	std::cout << "transform ScaleY: " << scale_d << "\n";
	Shape shape_cube3 = trfrm_shape_cube.scaleY(scale_d);
	print_shape_info(shape_cube3);

	std::cout << "transform ScaleZ: " << scale_e << "\n";
	Shape shape_cube4 = trfrm_shape_cube.scaleZ(scale_e);
	print_shape_info(shape_cube4);

	std::cout << "transform scale: " << scale_s << "\n";
	Shape shape_cube5 = trfrm_shape_cube.scale(scale_s);
	print_shape_info(shape_cube5);
	std::cout << "\n\n";	
	
	
	std::cout << "circle:\n";
	sh_type = 3;
	x1 = 0; y1 = 0;
	double R = 5;
	double H = 0;
	Shape shape_circle(sh_type, x1, y1, R, H);
	print_shape_info(shape_circle);

	transform trfrm_shape_circle(shape_circle);

	std::cout << "transform shift: m=" << shift_m << ", n=" << shift_n << ", k=" << shift_k << "\n";
	Shape shape_circle1 = trfrm_shape_circle.shift(shift_m, shift_n, shift_k);
	print_shape_info(shape_circle1);

	std::cout << "transform ScaleX: " << scale_a << "\n";
	Shape shape_circle2 = trfrm_shape_circle.scaleX(scale_a);
	print_shape_info(shape_circle2);

	std::cout << "transform ScaleY: " << scale_d << "\n";
	Shape shape_circle3 = trfrm_shape_circle.scaleY(scale_d);
	print_shape_info(shape_circle3);

	std::cout << "transform ScaleZ: " << scale_e << "\n";
	Shape shape_circle4 = trfrm_shape_circle.scaleZ(scale_e);
	print_shape_info(shape_circle4);

	std::cout << "transform scale: " << scale_s << "\n";
	Shape shape_circle5 = trfrm_shape_circle.scale(scale_s);
	print_shape_info(shape_circle5);
	std::cout << "\n\n";


	std::cout << "cylinder:\n";
	sh_type = 4;
	x1 = 0; y1 = 0;
	R = 5;
	H = 5;
	Shape shape_cylinder(sh_type, x1, y1, R, H);
	print_shape_info(shape_cylinder);

	transform trfrm_shape_cylinder(shape_cylinder);

	std::cout << "transform shift: m=" << shift_m << ", n=" << shift_n << ", k=" << shift_k << "\n";
	Shape shape_cylinder1 = trfrm_shape_cylinder.shift(shift_m, shift_n, shift_k);
	print_shape_info(shape_cylinder1);

	std::cout << "transform ScaleX: " << scale_a << "\n";
	Shape shape_cylinder2 = trfrm_shape_cylinder.scaleX(scale_a);
	print_shape_info(shape_cylinder2);

	std::cout << "transform ScaleY: " << scale_d << "\n";
	Shape shape_cylinder3 = trfrm_shape_cylinder.scaleY(scale_d);
	print_shape_info(shape_cylinder3);

	std::cout << "transform ScaleZ: " << scale_e << "\n";
	Shape shape_cylinder4 = trfrm_shape_cylinder.scaleZ(scale_e);
	print_shape_info(shape_cylinder4);

	std::cout << "transform scale: " << scale_s << "\n";
	Shape shape_cylinder5 = trfrm_shape_cylinder.scale(scale_s);
	print_shape_info(shape_cylinder5);
	std::cout << "\n\n";
	

	return 0;
}