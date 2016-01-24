

namespace engine {

	class Matrix4x4 {		

	public:		
		Vector4 m[4];

		Matrix4x4()
		{
			m[0] = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
			m[1] = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
			m[2] = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
			m[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		}

		Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
		{
			m[0] = v0;
			m[1] = v1;
			m[2] = v2;
			m[3] = v3;
		}

		Matrix4x4(const Vector3& pos, float scale)
		{
			m[0] = Vector4(scale, 0.0f, 0.0f, 0.0f);
			m[1] = Vector4(0.0f, scale, 0.0f, 0.0f);
			m[2] = Vector4(0.0f, 0.0f, scale, 0.0f);
			m[3] = Vector4(pos.x(), pos.y(), pos.z(), 1.0f);
		}

		Vector3 getPosition() const
		{
			return Vector3(m[3].x(), m[3].y(), m[3].z());
		}	

		void LoadIdentity()
		{
			m[0] = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
			m[1] = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
			m[2] = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
			m[3] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
		}

		// Read a row
		const Vector4 &operator[](int i) const { return m[i]; }

		// Access (set) a row
		Vector4 &operator[](int i) { return m[i]; }

		// Multiply by another 4x4 matrix
		Matrix4x4 operator*(const Matrix4x4 &r)
		{
			Matrix4x4 res;
			for (int i = 0; i != 4; ++i) 
			{
				res[i] = 
					r[0].componentMultiplication(m[i].xxxx()) + 
					r[1].componentMultiplication(m[i].yyyy()) + 
					r[2].componentMultiplication(m[i].zzzz()) + 
					r[3].componentMultiplication(m[i].wwww());
			}
			return res;
		}

		void Rotate(float angle, float x, float y, float z) 
		{
			float c = cosf(angle * (3.14159265f / 180.0f));
			float s = sinf(angle * (3.14159265f / 180.0f));

			Matrix4x4 r(
				Vector4(x*x*(1 - c) + c, x*y*(1 - c) + z*s, x*z*(1 - c) - y*s, 0.0f),
				Vector4(x*y*(1 - c) - z*s, y*y*(1 - c) + c, y*z*(1 - c) + x*s, 0.0f),
				Vector4(x*z*(1 - c) + y*s, y*z*(1 - c) - x*s, z*z*(1 - c) + c, 0.0f),
				Vector4(0.0f, 0.0f, 0.0f, 1.0f)
				);
			*this = r * *this;
		}

		void Rotate(Vector3 eulerAngles)
		{
			//TO-DO: convert to angle-axis

			Rotate(eulerAngles.x(), 1.0f, 0.0f, 0.0f);
			Rotate(eulerAngles.y(), 0.0f, 1.0f, 0.0f);
			Rotate(eulerAngles.z(), 0.0f, 0.0f, 1.0f);
		}


		void Translate(float x, float y, float z) 
		{
			m[3][0] += x;
			m[3][1] += y;
			m[3][2] += z;
		}

		void Translate(Vector3 dir)
		{
			m[3][0] += dir.x();
			m[3][1] += dir.y();
			m[3][2] += dir.z();
		}

		void Scale(float x, float y, float z)
		{
			m[0].x() *= x;
			m[1].y() *= y;
			m[2].z() *= z;
		}

		void LookAt(Vector3 point, Vector3 up)
		{
			Vector3 pos = getPosition();
			Vector3 z = (pos - point).normalized();
			Vector3 x = z.Cross(up).normalized();
			Vector3 y = z.Cross(x);

			Matrix4x4 res;
			//res.LoadIdentity();
			res[0] = Vector4(x, 0.0f);
			res[1] = Vector4(y, 0.0f);
			res[2] = Vector4(z, 0.0f);
			res[3] = Vector4(pos, 1.0f);

			LoadIdentity();
			*this = *this * res;
		}

		/// Like glPerspective
		void Perspective(float fov, float aspect, float zNear, float zFar) {
			float fW, fH;
			fH = tan(fov / 360.0f * 3.14159f) * zNear;
			fW = fH * aspect;
			Frustum(-fW, fW, -fH, fH, zNear, zFar);
		}

		/// Like glFrustum 
		void Frustum(float left, float right, float bottom, float top, float zNear, float zFar) {
			Matrix4x4 mul (
				Vector4(2 * zNear / (right - left), 0.0f, 0.0f, 0.0f),
				Vector4(0.0f, 2 * zNear / (top - bottom), 0.0f, 0.0f),
				Vector4((right + left) / (right - left), (top + bottom) / (top - bottom), -(zFar + zNear) / (zFar - zNear), -1.0f),
				Vector4(0.0f, 0.0f, -2 * zFar*zNear / (zFar - zNear), 0.0f)
			);

			*this = mul * *this;
		}

		// Return the matrix values as a 16 element float array
		const float *data() const
		{
			/*
			float res[16];

			for (int j = 0; j != 4; ++j)
				for (int i = 0; i != 4; ++i)
					res[(j << 2) + i] = m[j][i];

			return res;
			*/
			return &m[0][0];
		}

		// Don't define them here to avoid cross references
		Vector3 forward();
		Vector3 right();
		Vector3 up();
		

		Vector4 col(int i) const
		{
			return Vector4(m[0][i], m[1][i], m[2][i], m[3][i]);
		}	
		
	};
}