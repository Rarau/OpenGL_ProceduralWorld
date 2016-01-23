namespace engine {
	class Vector4_ {
		float v[4];

	public:
		Vector4_() {
			v[0] = v[1] = v[2] = v[3] = 0.0f;
		}

		Vector4_(float num) {
			v[0] = v[1] = v[2] = v[3] = num;
		}

		Vector4_(float x, float y, float z, float w) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
			v[3] = w;
		}

		// set x
		float &x() {
			return v[0];
		}

		// get x
		float x() const {
			return v[0];
		}

		// set y
		float &y() {
			return v[1];
		}

		// get y
		float y() const {
			return v[1];
		}

		// set z
		float &z() {
			return v[2];
		}

		// get z
		float z() const {
			return v[2];
		}

		// set w
		float &w() {
			return v[3];
		}

		// get w
		float w() const {
			return v[3];
		}

		Vector4_ xxxx() {
			return Vector4_(v[0], v[0], v[0], v[0]);
		}

		Vector4_ yyyy() {
			return Vector4_(v[1], v[1], v[1], v[1]);
		}

		Vector4_ zzzz() {
			return Vector4_(v[2], v[2], v[2], v[2]);
		}

		Vector4_ wwww() {
			return Vector4_(v[3], v[3], v[3], v[3]);
		}
		
		const float& operator[](int index) const {
			return v[index];
		}
		float& operator[](int index) {
			return v[index];
		}

		Vector4_ operator+(const Vector4_ &r) const {
			return Vector4_(v[0] + r.v[0], v[1] + r.v[1], v[2] + r.v[2], v[3] + r.v[3]);
		}

		Vector4_ operator-(const Vector4_ &r) const {
			return Vector4_(v[0] - r.v[0], v[1] - r.v[1], v[2] - r.v[2], v[3] - r.v[3]);
		}

		Vector4_ operator*(const Vector4_ &r) const {
			return Vector4_(v[0] * r.v[0], v[1] * r.v[1], v[2] * r.v[2], v[3] * r.v[3]);
		}

		float dot(const Vector4_ &r)
		{
			return v[0] * r.x() + v[1] * r.y() + v[2] * r.z() + v[3] * r.w();
		}
	};
}