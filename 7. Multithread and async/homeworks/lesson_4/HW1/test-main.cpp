#include <iostream>
#include <tuple>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_approx.hpp>

#include "shape.h"
#include "transform.h"


TEST_CASE("test  figures", "[test_st_f_s]")
{
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
		
		double R = 5;
		double H = 0;

	SECTION("section line")
	{
		
		Shape shape_line(sh_type, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8);
		
		CHECK(shape_line.volume == 0);
		CHECK(shape_line.square == 0);

		transform trfrm_shape_line(shape_line);

		Shape shape_line1 = trfrm_shape_line.shift(shift_m, shift_n, shift_k);
		CHECK(shape_line1.volume == 0);
		CHECK(shape_line1.square == 0);

		
		Shape shape_line2 = trfrm_shape_line.scaleX(scale_a);
		CHECK(shape_line2.volume == 0);
		CHECK(shape_line2.square == 0);

		Shape shape_line3 = trfrm_shape_line.scaleY(scale_d);
		CHECK(shape_line3.volume == 0);
		CHECK(shape_line3.square == 0);

		Shape shape_line4 = trfrm_shape_line.scaleZ(scale_e);
		CHECK(shape_line4.volume == 0);
		CHECK(shape_line4.square == 0);

		Shape shape_line5 = trfrm_shape_line.scale(scale_s);
		CHECK(shape_line5.volume == 0);
		CHECK(shape_line5.square == 0);

	}

	SECTION("section sqr")
	{
		sh_type = 1;
		Shape shape_sqr(sh_type, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8);
		CHECK(shape_sqr.volume == 0);
		CHECK(shape_sqr.square == 25);

		transform trfrm_shape_sqr(shape_sqr);

		Shape shape_sqr1 = trfrm_shape_sqr.shift(shift_m, shift_n, shift_k);
		CHECK(shape_sqr1.volume == 0);
		CHECK(shape_sqr1.square == 25);
		
		Shape shape_sqr2 = trfrm_shape_sqr.scaleX(scale_a);
		CHECK(shape_sqr2.volume == 0);
		CHECK(shape_sqr2.square == 50);

		Shape shape_sqr3 = trfrm_shape_sqr.scaleY(scale_d);
		CHECK(shape_sqr3.volume == 0);
		CHECK(shape_sqr3.square == 150);
		
		Shape shape_sqr4 = trfrm_shape_sqr.scaleZ(scale_e);
		CHECK(shape_sqr4.volume == 0);
		CHECK(shape_sqr4.square == 150);

		Shape shape_sqr5 = trfrm_shape_sqr.scale(scale_s);
		CHECK(shape_sqr5.volume == 0);
		CHECK(shape_sqr5.square == 6);
	}

	SECTION("section cube")
	{
		sh_type = 2;
		z2 = 5;
		Shape shape_cube(sh_type, x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4, x5, y5, z5, x6, y6, z6, x7, y7, z7, x8, y8, z8);
		CHECK(shape_cube.volume == 125);
		CHECK(shape_cube.square == 150);

		transform trfrm_shape_cube(shape_cube);

		Shape shape_cube1 = trfrm_shape_cube.shift(shift_m, shift_n, shift_k);
		CHECK(shape_cube1.volume == 125);
		CHECK(shape_cube1.square == 150);

		Shape shape_cube2 = trfrm_shape_cube.scaleX(scale_a);
		CHECK(shape_cube2.volume == 250);
		CHECK(shape_cube2.square == 250);

		Shape shape_cube3 = trfrm_shape_cube.scaleY(scale_d);
		CHECK(shape_cube3.volume == 750);
		CHECK(shape_cube3.square == 550);

		Shape shape_cube4 = trfrm_shape_cube.scaleZ(scale_e);
		CHECK(shape_cube4.volume == 3000);
		CHECK(shape_cube4.square == 1300);

		Shape shape_cube5 = trfrm_shape_cube.scale(scale_s);
		CHECK(shape_cube5.volume == 24);
		CHECK(shape_cube5.square == 52);

	}

	SECTION("circle")
	{
		sh_type = 3;
		x1 = 0; y1 = 0;
		
		Shape shape_circle(sh_type, x1, y1, R, H);

		Catch::Approx target = Catch::Approx(78).epsilon(0.01);
		CHECK(shape_circle.volume == 0);
		//CHECK(shape_circle.square == 78.5398);
		CHECK(shape_circle.square == target);

		transform trfrm_shape_circle(shape_circle);

		Shape shape_circle1 = trfrm_shape_circle.shift(shift_m, shift_n, shift_k);
		CHECK(shape_circle1.volume == 0);
		CHECK(shape_circle1.square == target);

		Shape shape_circle2 = trfrm_shape_circle.scaleX(scale_a);
		CHECK(shape_circle2.volume == 0);
		CHECK(shape_circle2.square == target);

		Shape shape_circle3 = trfrm_shape_circle.scaleY(scale_d);
		CHECK(shape_circle3.volume == 0);
		CHECK(shape_circle3.square == target);

		Shape shape_circle4 = trfrm_shape_circle.scaleZ(scale_e);
		CHECK(shape_circle4.volume == 0);
		CHECK(shape_circle4.square == target);

		Shape shape_circle5 = trfrm_shape_circle.scale(scale_s);
		CHECK(shape_circle5.volume == 0);
		CHECK(shape_circle5.square == target);

	}

	SECTION("cylinder")
	{
		sh_type = 4;
		x1 = 0; y1 = 0;
		
		R = 5;
		H = 5;
		Shape shape_cylinder(sh_type, x1, y1, R, H);
		Catch::Approx target_Volume = Catch::Approx(392).epsilon(0.01);
		Catch::Approx target_Square = Catch::Approx(128).epsilon(0.01);
		CHECK(shape_cylinder.volume == target_Volume);
		CHECK(shape_cylinder.square == target_Square);

		transform trfrm_shape_cylinder(shape_cylinder);

		Shape shape_cylinder1 = trfrm_shape_cylinder.shift(shift_m, shift_n, shift_k);
		CHECK(shape_cylinder1.volume == target_Volume);
		CHECK(shape_cylinder1.square == target_Square);

		Shape shape_cylinder2 = trfrm_shape_cylinder.scaleX(scale_a);
		CHECK(shape_cylinder2.volume == target_Volume);
		CHECK(shape_cylinder2.square == target_Square);

		Shape shape_cylinder3 = trfrm_shape_cylinder.scaleY(scale_d);
		CHECK(shape_cylinder3.volume == target_Volume);
		CHECK(shape_cylinder3.square == target_Square);

		Shape shape_cylinder4 = trfrm_shape_cylinder.scaleZ(scale_e);
		CHECK(shape_cylinder4.volume == target_Volume);
		CHECK(shape_cylinder4.square == target_Square);

		Shape shape_cylinder5 = trfrm_shape_cylinder.scale(scale_s);
		CHECK(shape_cylinder5.volume == target_Volume);
		CHECK(shape_cylinder5.square == target_Square);

	}

	
	
}



int main()
{
	//создается объект Session и у него вызывается метод run
	return Catch::Session().run();
}
