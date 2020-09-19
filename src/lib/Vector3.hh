#pragma once
namespace RGF
{

	class Vector3
	{
	public:
		double x;
		double y;
		double z;

		Vector3() = default;
		Vector3(double p_x, double p_y, double p_z) : x(p_x), y(p_y), z(p_z){};
		Vector3(double p) : x(p), y(p), z(p){};
		Vector3(Vector3 &&) = default;
		Vector3(const Vector3 &) = default;
		Vector3 &operator=(Vector3 &&) = default;
		Vector3 &operator=(const Vector3 &) = default;
		~Vector3();

		void setXYZ(double p_x, double p_y, double p_z)
		{
			x = p_x;
			y = p_y;
			z = p_z;
		}

		[[nodiscard]] static Vector3 add(const Vector3 &v1, const Vector3 &v2)
		{
			Vector3 target;
			return add(v1, v2, target);
		}
		static Vector3 &add(const Vector3 &v1, const Vector3 &v2, Vector3 &target)
		{
			target.setXYZ(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
			return target;
		}

		static Vector3 sub(const Vector3 &v1, const Vector3 &v2)
		{
			Vector3 target;
			return sub(v1, v2, target);
		}
		static Vector3 &sub(const Vector3 &v1, const Vector3 &v2, Vector3 &target)
		{
			target.setXYZ(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
			return target;
		}

		static Vector3 mul(const Vector3 &v1, const Vector3 &v2)
		{
			Vector3 target;
			return mul(v1, v2, target);
		}
		static Vector3 &mul(const Vector3 &v1, const Vector3 &v2, Vector3 &target)
		{
			target.setXYZ(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
			return target;
		}

		static Vector3 div(const Vector3 &v1, const Vector3 &v2)
		{
			Vector3 target;
			return div(v1, v2, target);
		}
		static Vector3 &div(const Vector3 &v1, const Vector3 &v2, Vector3 &target)
		{
			target.setXYZ(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
			return target;
		}

		static double dot(const Vector3 &v1, const Vector3 &v2)
		{
			return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
		}

		static Vector3 cross(const Vector3 &v1, const Vector3 &v2)
		{
			Vector3 target;
			return cross(v1, v2, target);
		}
		static Vector3 &cross(const Vector3 &a, const Vector3 &b, Vector3 &target)
		{
			target.setXYZ(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
			return target;
		}

		Vector3 operator+(Vector3 rhs) const
		{
			Vector3 out;
			add(*this, rhs, out);
			return out;
		}

		Vector3 &operator+=(Vector3 rhs)
		{
			add(*this, rhs, *this);
			return *this;
		}

		Vector3 operator-(Vector3 rhs) const
		{
			Vector3 out;
			sub(*this, rhs, out);
			return out;
		}

		Vector3 &operator-=(Vector3 rhs)
		{
			sub(*this, rhs, *this);
			return *this;
		}

		Vector3 operator*(Vector3 rhs) const
		{
			Vector3 out;
			mul(*this, rhs, out);
			return out;
		}

		Vector3 &operator*=(Vector3 rhs)
		{
			mul(*this, rhs, *this);
			return *this;
		}

		Vector3 operator/(Vector3 rhs) const
		{
			Vector3 out;
			div(*this, rhs, out);
			return out;
		}

		Vector3 &operator/=(Vector3 rhs)
		{
			div(*this, rhs, *this);
			return *this;
		}
	};
} // namespace RGF
