

namespace engine 
{

	class Vector4 
	{
		float v[4];

	public:
		Vector4() 
		{
			v[0] = v[1] = v[2] = v[3] = 0.0f;
		}

		Vector4(float num) {
			v[0] = v[1] = v[2] = v[3] = num;
		}

		Vector4(float x, float y, float z, float w) 
		{
			v[0] = x;
			v[1] = y;
			v[2] = z;
			v[3] = w;
		}

		// set x
		float &x() 
		{
			return v[0];
		}

		// get x
		float x() const 
		{
			return v[0];
		}

		// set y
		float &y() 
		{
			return v[1];
		}

		// get y
		float y() const 
		{
			return v[1];
		}

		// set z
		float &z() 
		{
			return v[2];
		}

		// get z
		float z() const 
		{
			return v[2];
		}

		// set w
		float &w() 
		{
			return v[3];
		}

		// get w
		float w() const 
		{
			return v[3];
		}

		Vector4 xxxx() 
		{
			return Vector4(v[0], v[0], v[0], v[0]);
		}

		Vector4 yyyy() 
		{
			return Vector4(v[1], v[1], v[1], v[1]);
		}

		Vector4 zzzz() 
		{
			return Vector4(v[2], v[2], v[2], v[2]);
		}

		Vector4 wwww() 
		{
			return Vector4(v[3], v[3], v[3], v[3]);
		}
		
		/*const float& operator[](int index) const 
		{
			return v[index];
		}*/
		float& operator[](int index) 
		{
			return v[index];
		}

		Vector4 operator+(const Vector4 &r) const 
		{
			return Vector4(v[0] + r.v[0], v[1] + r.v[1], v[2] + r.v[2], v[3] + r.v[3]);
		}

		Vector4 operator-(const Vector4 &r) const
		{
			return Vector4(v[0] - r.v[0], v[1] - r.v[1], v[2] - r.v[2], v[3] - r.v[3]);
		}

		float operator*(const Vector4 &r) const
		{
			return v[0] * r.x() + v[1] * r.y() + v[2] * r.z() + v[3] * r.w();
		}

		Vector4 operator*(const float number) const
		{
			return Vector4(v[0] * number, v[1] * number, v[2] * number, v[3] * number);
		}

		Vector4 componentMultiplication(const Vector4 &r) const
		{
			return Vector4(v[0] * r.v[0], v[1] * r.v[1], v[2] * r.v[2], v[3] * r.v[3]);
		}

		Vector4 operator/(const float number) const
		{
			return operator*(1 / number);
		}

		float lengthSquared() const
		{
			return (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]) + (v[3] * v[3]);
		}
		
		float length() const
		{
			return sqrt(lengthSquared());
		}

		Vector4 normalized() const
		{
			return operator*(1 / length());
		}

		Vector4 normalize()
		{
			*this = operator*(1 / length());
		}

		/*explicit operator engine::Vector3()
		{
			return Vector3(v[0], v[1], v[2]);
		}*/

	};
}