#include "transform.h"

transform::transform(const Shape& sh)
{
	shape = sh;
}

Shape transform::shift(int m, int n, int k)
{
	shape.shift(m, n, k);
	return shape;
}

Shape transform::scaleX(int a)
{
	shape.scaleX(a);
	return shape;
}

Shape transform::scaleY(int d)
{
	shape.scaleY(d);
	return shape;
}

Shape transform::scaleZ (int e)
{
	shape.scaleZ(e);
	return shape;
}

Shape transform::scale(int s)
{
	shape.scale(s);
	return shape;
}
