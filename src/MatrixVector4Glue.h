
namespace engine
{
	Vector4 Vector4::operator*(const Matrix4x4 mat) const
	{
		return Vector4(*this * mat.col(0), *this * mat.col(1), *this * mat.col(2), *this * mat.col(3));
	}

	Vector3 Matrix4x4::forward()
	{
		return (Vector4(0.0f, 0.0f, 1.0f, 0.0f) * (*this));
	}
	Vector3 Matrix4x4::right()
	{
		return (Vector4(1.0f, 0.0f, 0.0f, 0.0f) * (*this));
	}
	Vector3 Matrix4x4::up()
	{
		return (Vector4(0.0f, 1.0f, 0.0f, 0.0f) * (*this));
	}
}