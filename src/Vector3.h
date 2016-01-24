

namespace engine 
{

	class Vector3 
	{
		float v[3];

	public:
		Vector3() 
		{
			v[0] = v[1] = v[2] = 0.0f;
		}

		Vector3(float num) 
		{
			v[0] = v[1] = v[2] = num;
		}

		Vector3(float x, float y, float z) 
		{
			v[0] = x;
			v[1] = y;
			v[2] = z;
		}

		Vector3(double x, double y, double z)
		{
			v[0] = (float)x;
			v[1] = (float)y;
			v[2] = (float)z;
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

		const float& operator[](int index) const 
		{
			return v[index];
		}
		float& operator[](int index) 
		{
			return v[index];
		}

		Vector3 operator+(const Vector3 &r) const 
		{
			return Vector3(v[0] + r.v[0], v[1] + r.v[1], v[2] + r.v[2]);
		}

		Vector3 operator-(const Vector3 &r) const 
		{
			return Vector3(v[0] - r.v[0], v[1] - r.v[1], v[2] - r.v[2]);
		}	

		float operator*(const Vector3 &r) const
		{
			return v[0] * r.x() + v[1] * r.y() + v[2] * r.z();
		}

		Vector3 operator*(const float number) const
		{
			return Vector3(v[0] * number, v[1] * number, v[2] * number);
		}

		Vector3 componentMultiplication(const Vector3 &r) const
		{
			return Vector3(v[0] * r.v[0], v[1] * r.v[1], v[2] * r.v[2]);
		}

		Vector3 operator/(const float number) const
		{
			return operator*(1/number);
		}
		
		Vector3 operator-() const
		{
			return *this * -1.0f;
		}

		Vector3 Cross(const Vector3 &r) const {
			return Vector3(v[1] * r[2] - v[2] * r[1], v[2] * r[0] - v[0] * r[2], v[0] * r[1] - v[1] * r[0]);
		}

		float lengthSquared() const
		{
			return (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
		}

		float length() const
		{
			return sqrt(lengthSquared());
		}

		Vector3 normalized() const
		{
			return operator*(1/length());
		}

		void normalize() 
		{
			*this = operator*(1 / length());
		}

		// We dont want to have an implicit operator because we wouldn't
		// know if put a 0 or 1 (free vector or point)
		/*operator engine::Vector4() const
		{
			return Vector4(v[0], v[1], v[2]);
		}*/

	};
}