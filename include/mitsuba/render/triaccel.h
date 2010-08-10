#if !defined(__TRIACCEL_H)
#define __TRIACCEL_H

#include <mitsuba/render/trimesh.h>

MTS_NAMESPACE_BEGIN

// Used when a fake triangle is used to reference a non-triangle shape instance
static const uint32_t KNoTriangleFlag = 0xFFFFFFFF;

/**
 * Pre-computed triangle representation using Ingo Wald's TriAccel layout. 
 * Fits into three 16-byte cache lines if single precision floats are used.
 * The k parameter is also used for classification during kd-tree construction.
 */
struct TriAccel {
	uint32_t k;
	Float n_u;
	Float n_v;
	Float n_d;

	Float a_u;
	Float a_v;
	Float b_nu;
	Float b_nv;

	Float c_nu;
	Float c_nv;
	uint32_t index;
	uint32_t shapeIndex;

	/// Construct from vertex data. Returns '1' if there was a failure
	inline int load(const Point &A, const Point &B, const Point &C);

	/// Fast ray-triangle intersection test
	FINLINE bool rayIntersect(const Ray &ray, Float mint, Float maxt,
		Float &u, Float &v, Float &t) const;
		
#if defined(MTS_SSE)
	FINLINE __m128 rayIntersectPacket(const RayPacket4 &packet, const
		__m128 mint, __m128 maxt, __m128 inactive, Intersection4 &its) const;
#endif
};

inline int TriAccel::load(const Point &A, const Point &B, const Point &C) {
	static const int waldModulo[4] = { 1, 2, 0, 1 };

	Vector b = C-A, c = B-A, N = cross(c, b);

	k = 0;
	/* Determine the largest projection axis */
	for (int j=0; j<3; j++) {
		if (std::abs(N[j]) > std::abs(N[k]))
			k = j;
	}

	uint32_t u = waldModulo[k],
		v = waldModulo[k+1];
	const Float n_k = N[k],
		denom = b[u]*c[v] - b[v]*c[u];

	if (denom == 0)
		return 1;

	/* Pre-compute intersection calculation constants */
	n_u   =  N[u] / n_k;
	n_v   =  N[v] / n_k;
	n_d   =  dot(A, N) / n_k;
	b_nu  =  b[u] / denom;
	b_nv  = -b[v] / denom;
	a_u   =  A[u];
	a_v   =  A[v];
	c_nu  =  c[v] / denom;
	c_nv  = -c[u] / denom;
	return 0;
}

FINLINE bool TriAccel::rayIntersect(const Ray &ray, Float mint, Float maxt,
	Float &u, Float &v, Float &t) const {
	static const int waldModulo[4] = { 1, 2, 0, 1 };
	const int ku = waldModulo[k], kv = waldModulo[k+1];

	/* Get the u and v components */
	const Float o_u = ray.o[ku], o_v = ray.o[kv], o_k = ray.o[k],
				d_u = ray.d[ku], d_v = ray.d[kv], d_k = ray.d[k];

	/* Calculate the plane intersection (Typo in the thesis?) */
	t = (n_d - o_u*n_u - o_v*n_v - o_k) / (d_u * n_u + d_v * n_v + d_k);

	if (t < mint || t > maxt)
		return false;

	/* Calculate the projected plane intersection point */
	const Float hu = o_u + t * d_u - a_u;
	const Float hv = o_v + t * d_v - a_v;

	/* In barycentric coordinates */
	u = hv * b_nu + hu * b_nv;
	v = hu * c_nu + hv * c_nv;

	return (u >= 0 && v >= 0 &&  u+v <= 1.0f);
}

MTS_NAMESPACE_END

#ifdef MTS_SSE
#include <mitsuba/render/triaccel_sse.h>
#endif

#endif /* __TRIACCEL_H */