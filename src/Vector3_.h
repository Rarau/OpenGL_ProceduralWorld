namespace engine {
	class Vector3_ {
		float v[3];

	public:
		Vector3_() {
			v[0] = v[1] = v[2] = 0.0f;
		}

		Vector3_(float num) {
			v[0] = v[1] = v[2] = num;
		}

		Vector3_(float x, float y, float z) {
			v[0] = x;
			v[1] = y;
			v[2] = z;
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

		const float& operator[](int index) const {
			return v[index];
		}
		float& operator[](int index) {
			return v[index];
		}

		Vector3_ operator+(const Vector3_ &r) const {
			return Vector3_(v[0] + r.v[0], v[1] + r.v[1], v[2] + r.v[2]);
		}

		Vector3_ operator-(const Vector3_ &r) const {
			return Vector3_(v[0] - r.v[0], v[1] - r.v[1], v[2] - r.v[2]);
		}

		Vector3_ operator*(const Vector3_ &r) const {
			return Vector3_(v[0] * r.v[0], v[1] * r.v[1], v[2] * r.v[2]);
		}

		float dot(const Vector3_ &r)
		{
			return v[0] * r.x() + v[1] * r.y() + v[2] * r.z();
		}
	};
}