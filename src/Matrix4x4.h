namespace engine {
	class Matrix4x4 {
		//float m[16];

	public:		
		Vector4_ m[4];

		Matrix4x4()
		{
			m[0] = Vector4_(1.0f, 0.0f, 0.0f, 0.0f);
			m[1] = Vector4_(0.0f, 1.0f, 0.0f, 0.0f);
			m[2] = Vector4_(0.0f, 0.0f, 1.0f, 0.0f);
			m[3] = Vector4_(0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4x4(const Vector4_& v0, const Vector4_& v1, const Vector4_& v2, const Vector4_& v3)
		{
			m[0] = v0;
			m[1] = v1;
			m[2] = v2;
			m[3] = v3;
		}


		Matrix4x4(const Vector3_& pos, float scale)
		{
			m[0] = Vector4_(scale, 0.0f, 0.0f, 0.0f);
			m[1] = Vector4_(0.0f, scale, 0.0f, 0.0f);
			m[2] = Vector4_(0.0f, 0.0f, scale, 0.0f);
			m[3] = Vector4_(pos.x(), pos.y(), pos.z(), 1.0f);
		}

		void LoadIdentity()
		{
			m[0] = Vector4_(1.0f, 0.0f, 0.0f, 0.0f);
			m[1] = Vector4_(0.0f, 1.0f, 0.0f, 0.0f);
			m[2] = Vector4_(0.0f, 0.0f, 1.0f, 0.0f);
			m[3] = Vector4_(0.0f, 0.0f, 0.0f, 1.0f);
		}

		// Read a row
		const Vector4_ &operator[](int i) const { return m[i]; }

		// Acces (set) a row
		Vector4_ &operator[](int i) { return m[i]; }

		// Multiply by another 4x4 matrix
		Matrix4x4 operator*(const Matrix4x4 &r)
		{
			Matrix4x4 res;
			for (int i = 0; i != 4; ++i) {
				res[i] = r[0] * m[i].xxxx() + r[1] * m[i].yyyy() + r[2] * m[i].zzzz() + r[3] * m[i].wwww();
			}
			return res;
		}

		void Rotate(float angle, float x, float y, float z) {
			float c = cosf(angle * (3.14159265f / 180.0f));
			float s = sinf(angle * (3.14159265f / 180.0f));

			Matrix4x4 r(
				Vector4_(x*x*(1 - c) + c, x*y*(1 - c) + z*s, x*z*(1 - c) - y*s, 0.0f),
				Vector4_(x*y*(1 - c) - z*s, y*y*(1 - c) + c, y*z*(1 - c) + x*s, 0.0f),
				Vector4_(x*z*(1 - c) + y*s, y*z*(1 - c) - x*s, z*z*(1 - c) + c, 0.0f),
				Vector4_(0.0f, 0.0f, 0.0f, 1.0f)
				);
			*this = r * *this;
		}


		void Translate(float x, float y, float z) {
			m[3][0] += x;
			m[3][1] += y;
			m[3][2] += z;
		}

		// Return the matrix values as a 16 element float array
		float *data()
		{
			float res[16];

			for (int j = 0; j != 4; ++j)
				for (int i = 0; i != 4; ++i)
					res[(j << 2) + i] = m[j][i];

			return res;
		}
	};
}