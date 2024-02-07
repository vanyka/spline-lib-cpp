template <class BASETYPE>
class VEC2
{

public:
	typedef BASETYPE	REALTYPE;
	
	static VEC2	RndUniform( BASETYPE a, BASETYPE b)			{ return VEC2( ::RndUniform(a,b), ::RndUniform(a,b) ); }
	static VEC2	RndUniform( const VEC2& a, const VEC2& b)	{ return VEC2( ::RndUniform(a.x,a.y), ::RndUniform(b.x,b.y) ); }
	
	BASETYPE x;
	BASETYPE y;

	inline VEC2();
	inline VEC2(const BASETYPE &xval, const BASETYPE &yval);

	inline BASETYPE Length()    const; ///< Vector hossza.

		  BASETYPE& operator[](int c)				{ return ((BASETYPE*)this)[c]; }
	const BASETYPE& operator[](int c) const			{ return ((BASETYPE*)this)[c]; }


	inline VEC2 operator + (const VEC2 &v) const;
	inline VEC2 operator - (const VEC2 &v) const;
	inline BASETYPE operator * (const VEC2 &v) const; ///< skal�ris szorzat

	VEC2 operator - () const;	///< neg�l�s

	template <class BASETYPE_OTHER>
	inline VEC2& operator += (const BASETYPE_OTHER &v);
	template <class BASETYPE_OTHER>
	inline VEC2& operator -= (const BASETYPE_OTHER &v);
	
	template <class BASETYPE_OTHER>
	inline VEC2 operator * (const BASETYPE_OTHER &e) const; 
	template <class BASETYPE_OTHER>
	inline VEC2 operator / (const BASETYPE_OTHER &e) const; 
	
	template <class BASETYPE_OTHER>
	inline VEC2& operator *= (const BASETYPE_OTHER &e); 
	template <class BASETYPE_OTHER>
	inline VEC2& operator /= (const BASETYPE_OTHER &e);

	inline bool operator == (const VEC2 &e)const;
	inline bool operator != (const VEC2 &e)const;
	inline bool operator < (const VEC2 &_other)const;

	inline VEC2 operator << (const int i)const;
	inline VEC2 operator >> (const int i)const;
	inline VEC2& operator <<= (const int e);
	inline VEC2& operator >>= (const int e);
};
template <class BASETYPE> VEC2<BASETYPE> abs_(const VEC2<BASETYPE> &v);	///< abszolut �rt�kek




template <class BASETYPE>
inline VEC2<BASETYPE>::VEC2()
:	x()
,	y()
{

}


template <class BASETYPE>
inline VEC2<BASETYPE>::VEC2( const BASETYPE &xval, const BASETYPE &yval)
:	x(xval)
,	y(yval)
{
}

template <class BASETYPE>
inline BASETYPE VEC2<BASETYPE>::Length() const
{
	return std::sqrt(x*x + y*y);
}

template <class BASETYPE>
inline VEC2<BASETYPE> VEC2<BASETYPE>::operator + (const VEC2 &v) const
{
	return VEC2<BASETYPE>(x + v.x, y + v.y);
}


template <class BASETYPE>
inline VEC2<BASETYPE> VEC2<BASETYPE>::operator - (const VEC2 &v) const
{
	return VEC2<BASETYPE>(x - v.x, y - v.y);
}


template <class BASETYPE>
inline BASETYPE VEC2<BASETYPE>::operator * (const VEC2 &v) const
{
	return BASETYPE(x * v.x + y * v.y);
}


template <class BASETYPE>
inline VEC2<BASETYPE> VEC2<BASETYPE>::operator - () const
{
	return 	VEC2<BASETYPE>(- x, - y);
}


template <class BASETYPE>
template <class BASETYPE_OTHER>
inline VEC2<BASETYPE>& VEC2<BASETYPE>::operator += (const BASETYPE_OTHER &v)
{
	x += v.x;
	y += v.y;
	
	return *this;
}


template <class BASETYPE>
template <class BASETYPE_OTHER>
inline VEC2<BASETYPE>& VEC2<BASETYPE>::operator -= (const BASETYPE_OTHER &v)
{
	x -= v.x;
	y -= v.y;
	
	return *this;
}


template <class BASETYPE>
template <class BASETYPE_OTHER>
inline VEC2<BASETYPE> VEC2<BASETYPE>::operator * (const BASETYPE_OTHER &e) const
{
	return VEC2<BASETYPE>(x * e, y * e);
}


template <class BASETYPE>
template <class BASETYPE_OTHER>
inline VEC2<BASETYPE> VEC2<BASETYPE>::operator / (const BASETYPE_OTHER &e) const
{
	return VEC2<BASETYPE>(x / e, y / e);
}


template <class BASETYPE>
template <class BASETYPE_OTHER>
inline VEC2<BASETYPE>& VEC2<BASETYPE>::operator *= (const BASETYPE_OTHER &e)
{
	x *= e;
	y *= e;
	
	return *this;
}


template <class BASETYPE>
template <class BASETYPE_OTHER>
inline VEC2<BASETYPE>& VEC2<BASETYPE>::operator /= (const BASETYPE_OTHER &e)
{
	x /= e;
	y /= e;
	
	return *this;
}

template <class BASETYPE>
bool VEC2<BASETYPE>::operator == (const VEC2<BASETYPE> &e)const
{
	return ((e.x == x) && (e.y == y));
}

template <class BASETYPE>
bool VEC2<BASETYPE>::operator != (const VEC2<BASETYPE> &e)const
{
	return (e.x != x || e.y != y);
}

template <class BASETYPE>
inline VEC2<BASETYPE> VEC2<BASETYPE>::operator << (const int i)const
{
	return VEC2<BASETYPE>(x << i, y << i);
}

template <class BASETYPE>
inline VEC2<BASETYPE> VEC2<BASETYPE>::operator >> (const int i)const
{
	return VEC2<BASETYPE>(x >> i, y >> i);
}

template <class BASETYPE>
inline VEC2<BASETYPE>& VEC2<BASETYPE>::operator <<= (const int e)
{
	x <<= e;
	y <<= e;
	return *this;
}

template <class BASETYPE>
inline VEC2<BASETYPE>& VEC2<BASETYPE>::operator >>= (const int e)
{
	x >>= e;
	y >>= e;
	return *this;
}

template <class BASETYPE>
bool VEC2<BASETYPE>::operator < (const VEC2<BASETYPE> &_other)const
{
	if (x < _other.x)
		return TRUE;
	if (x > _other.x)
		return FALSE;
	if (y < _other.y)
		return TRUE;

	return FALSE;
}

template <class BASETYPE> VEC2<BASETYPE> abs_(const VEC2<BASETYPE> &v)	///< abszolut �rt�kek
{
	return VEC2<BASETYPE>( abs_(v.x), abs_(v.y) );
}


template <class BASETYPE> bool IsInUnitBox(const VEC2<BASETYPE> &v)	///< abszolut �rt�kek
{
	return v.x >= BASETYPE(0) && v.x < BASETYPE(1) &&
		v.y >= BASETYPE(0) && v.y < BASETYPE(1);
}

template <class BASETYPE>
inline const VEC2<int> floor_(const VEC2<BASETYPE> &_v)
{
	return VEC2<int>(floor_(_v.x), floor_(_v.y));
}
