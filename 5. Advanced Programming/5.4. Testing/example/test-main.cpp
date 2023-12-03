#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>

#include "Factorial.h"

TEST_CASE("test factorial", "[test_f_1]") {  //[test_f_1] - ��� ����, ������� � ���������� ��������� ������ ������� ���� ����
	SECTION("number < 3")
	{
		CHECK(Factorial(0) == 1);
		CHECK(Factorial(1) == 1);
		CHECK(Factorial(2) == 2);
		CHECK(Factorial(3) == 6);
	}

	SECTION("number > 3")
	{
		CHECK(Factorial(4) == 24);
		CHECK(Factorial(5) == 120);
		CHECK(Factorial(6) == 720);
	}

	SECTION("number > 3 - ver.2")
	{
		//��� ������ ��� ������� - ��� ������ �����, �� �� �����

		int results[] = { 24,520,720 }; //{ 24,120,720 }
		for (int x = 4; x < 7; ++x)
		{
			CHECK(Factorial(x) == results[x-4]);
		}		
	}	
}

TEST_CASE("test factorial2", "[test_f_2]") {
	SECTION("number < 3")
	{
		INFO("Factorial(0) is 1");  //INFO ��������� ������ ��� ������� CHECK
		REQUIRE(Factorial(0) == 2); //Factorial(0) == 1
		//REQUIRE - ���� ��� �����, ���������� CHECK �� �����������
		CHECK(Factorial(1) == 1);
		CHECK(Factorial(2) == 2);
		CHECK(Factorial(3) == 6);
	}

	SECTION("number > 3")
	{
		CHECK(Factorial(4) == 24);
		CHECK(Factorial(5) == 120);
		CHECK(Factorial(6) == 720);
	}

	SECTION("number > 3 - ver.2")
	{
		int results[] = { 24,120,720 }; //{ 24,120,720 }
		for (int x = 4; x < 7; ++x)
		{
			CHECK(Factorial(x) == results[x - 4]);
		}
	}

}

int main()
{
	//��������� ������ Session � � ���� ���������� ����� run
	return Catch::Session().run();
}
