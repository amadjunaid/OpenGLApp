//ENABLES SYNTAX AND INTELLISENSE FOR GLSL IN VS (include this file)

/*
* ----------------------------------------------------------------------------
* Author: Daniel Opitz
* 
* THIS SOFTWARE IS BEER LICENCED
* As long as you retain this notice you can do whatever you want with this stuff. 
* If we meet some day, and you think this stuff is worth it, 
* you can buy me a beer in return.
* ----------------------------------------------------------------------------
*/


#ifdef WIN32

#define GENFUN2_VEC(name) vec2 name(vec2,vec2); vec3 name(vec3,vec3); vec4 name(vec4,vec4);
#define GENFUN2D_VEC(name) dvec2 name(dvec2,dvec2); dvec3 name(dvec3,dvec3); dvec4 name(dvec4,dvec4);
#define GENFUN2I_VEC(name) ivec2 name(ivec2,ivec2); ivec3 name(ivec3,ivec3); ivec4 name(ivec4,ivec4);
#define GENFUN2U_VEC(name) uvec2 name(uvec2,uvec2); uvec3 name(uvec3,uvec3); uvec4 name(uvec4,uvec4);

#define GENFUN(name) float name(float); vec2 name(vec2); vec3 name(vec3); vec4 name(vec4);
#define GENFUND(name) double name(double); dvec2 name(dvec2,dvec2); dvec3 name(dvec3,dvec3); dvec4 name(dvec4,dvec4);
#define GENFUNI(name) int name(int); ivec2 name(ivec2,ivec2); ivec3 name(ivec3,ivec3); ivec4 name(ivec4,ivec4);
#define GENFUNU(name) unsigned name(unsigned); uvec2 name(uvec2,uvec2); uvec3 name(uvec3,uvec3); uvec4 name(uvec4,uvec4);

#define GENFUN2(name) float name(float,float); vec2 name(vec2,vec2); vec3 name(vec3,vec3); vec4 name(vec4,vec4);
#define GENFUN2D(name) double name(double,double); dvec2 name(dvec2,dvec2); dvec3 name(dvec3,dvec3); dvec4 name(dvec4,dvec4);
#define GENFUN2I(name) int name(int,int); ivec2 name(ivec2,ivec2); ivec3 name(ivec3,ivec3); ivec4 name(ivec4,ivec4);
#define GENFUN2U(name) unsigned name(unsigned,unsigned); uvec2 name(uvec2,uvec2); uvec3 name(uvec3,uvec3); uvec4 name(uvec4,uvec4);

#define GENFUN3(name) float name(float,float,float); vec2 name(vec2,vec2,vec2); vec3 name(vec3,vec3,vec3); vec4 name(vec4,vec4,vec4);
#define GENFUN3D(name) double name(double,double,double); dvec2 name(dvec2,dvec2,dvec2); dvec3 name(dvec3,dvec3,dvec3); dvec4 name(dvec4,dvec4,dvec4);
#define GENFUN3I(name) int name(int,int,int); ivec2 name(ivec2,ivec2,ivec2); ivec3 name(ivec3,ivec3,ivec3); ivec4 name(ivec4,ivec4,ivec4);
#define GENFUN3U(name) unsigned name(unsigned,unsigned,unsigned); uvec2 name(uvec2,uvec2,uvec2); uvec3 name(uvec3,uvec3,uvec3); uvec4 name(uvec4,uvec4,uvec4);

#define GENFUN_ALL(name) GENFUN(name) GENFUND(name) GENFUNI(name) GENFUNU(name) 
#define GENFUN2_ALL(name) GENFUN2(name) GENFUN2D(name) GENFUN2I(name) GENFUN2U(name) 
#define GENFUN3_ALL(name) GENFUN3(name) GENFUN3D(name) GENFUN3I(name) GENFUN3U(name) 

#define std140
#define flat
#define smooth
#define in
#define out
#define inout
#define varying
#define uniform
#define layout(x)
#define buffer 
#define shared
#define coherent 
#define volatile 
#define restricted 
#define readonly 
#define writeonly 
#define centroid 
#define sample
#define patch 
#define discard


#define triangles
#define quads
#define isolines
#define equal_spacing
#define fractional_even_spacing
#define fractional_odd_spacing
#define cw
#define ccw
#define point_mode
#define vertices

#define points
#define lines
#define lines_adjacency
#define triangles_adjacency
#define invocations
#define line_strip
#define triangle_strip
#define max_vertices
#define stream

#define origin_upper_left
#define pixel_center_integer
#define early_fragment_tests
#define depth_any
#define depth_greater
#define depth_less
#define depth_unchanged

#define local_size_x
#define local_size_y
#define local_size_z



// ******************************************************* //
// *********************** Types ************************* //

typedef unsigned int uint;
typedef unsigned int atomic_uint;

template <typename gytpe>
struct __vec2
{
	__vec2 ();
	__vec2 (gytpe);
	__vec2 (gytpe, gytpe);
	gytpe x, y;
	__vec2& xx, &yy, &xy, &yx;

	gytpe r, g;
	__vec2& rr, &gg, &rg, &gr;

	gtype operator [] (int i);

	__vec2<gtype>& operator*= (__vec2<gtype>);
	__vec2<gtype>& operator/= (__vec2<gtype>);
	__vec2<gtype>& operator+= (__vec2<gtype>);
	__vec2<gtype>& operator-= (__vec2<gtype>);

	__vec2<gtype>& operator*= (gtype);
	__vec2<gtype>& operator/= (gtype);
	__vec2<gtype>& operator+= (gtype);
	__vec2<gtype>& operator-= (gtype);
	__vec2<gtype>& operator= (gtype);
	__vec2<gtype>& operator- ();
};

template <typename gytpe>
struct __vec3
{
	__vec3 ();
	__vec3 (gytpe);
	__vec3 (uvec3);
	__vec3 (ivec3);
	__vec3 (gytpe, gytpe, gtype);
	__vec3 (__vec2<gtype>, gtype);
	gytpe x, y, z;
	__vec2 xx, xy, xz, yx, yy, yz, zx, zy, zz;
	__vec3 &xxx, &xxy, &xxz, &xyx, &xyy, &xyz, &yxx, &yxy, &yxz, &yyx, &yyy, &yyz, &yzx, &yzy, &yzz, &zxx, &zxy, &zxz, &zyx, &zyy, &zyz, &zzx, &zzy, &zzz;

	ggtpe r, g, b;
	__vec2 rr, rg, rb, gr, gg, gb, br, bg, bb;
	__vec3 &rrr, &rrg, &rrb, &rgr, &rgg, &rgb, &grr, &grg, &grb, &ggr, &ggg, &ggb, &gbr, &gbg, &gbb, &brr, &brg, &brb, &bgr, &bgg, &bgb, &bbr, &bbg, &bbb;

	gtype operator [] (int i);

	__vec3<gtype>& operator*= (__vec3<gtype>);
	__vec3<gtype>& operator/= (__vec3<gtype>);
	__vec3<gtype>& operator+= (__vec3<gtype>);
	__vec3<gtype>& operator-= (__vec3<gtype>);

	__vec3<gtype>& operator*= (gtype);
	__vec3<gtype>& operator/= (gtype);
	__vec3<gtype>& operator+= (gtype);
	__vec3<gtype>& operator-= (gtype);
	__vec3<gtype>& operator= (gtype);
	__vec3<gtype>& operator- ();
	__vec3<gtype>& operator/ (ivec3);
	__vec3<gtype>& operator* (ivec3);
	__vec3<gtype>& operator* (int);
};

template <typename gytpe>
struct __vec4
{
	__vec4 ();
	__vec4 (gytpe);
	__vec4 (gytpe, gytpe, gtype, gtype);
	__vec4 (__vec2<gtype>, gtype, gtype);
	__vec4 (__vec3<gtype>, gtype);
	gytpe x, y, z, w;
	__vec2 xx, xy, xz, xw, yx, yy, yz, yw, zx, zy, zz, zw, wx, wy, wz, ww;
	__vec3 xxx, xxy, xxz, xyx, xyy, xyz, yxx, yxy, yxz, yyx, yyy, yyz, yzx, yzy, yzz, zxx, zxy, zxz, zyx, zyy, zyz, zzx, zzy, zzz, www;
	__vec4 &xxxx, &xxxy, &xxxz, &xxxw, &xxyx, &xxyy, &xxyz, &xxyw, &xxzx, &xxzy, &xxzz, &xxzw, &xxwx, &xxwy, &xxwz, &xxww,
		&xyxx, &xyxy, &xyxz, &xyxw, &xyyx, &xyyy, &xyyz, &xyyw, &xyzx, &xyzy, &xyzz, &xyzw, &xywx, &xywy, &xywz, &xyww,
		&xzxx, &xzxy, &xzxz, &xzxw, &xzyx, &xzyy, &xzyz, &xzyw, &xzzx, &xzzy, &xzzz, &xzzw, &xzwx, &xzwy, &xzwz, &xzww,
		&xwxx, &xwxy, &xwxz, &xwxw, &xwyx, &xwyy, &xwyz, &xwyw, &xwzx, &xwzy, &xwzz, &xwzw, &xwwx, &xwwy, &xwwz, &xwww,
		&yxxx, &yxxy, &yxxz, &yxxw, &yxyx, &yxyy, &yxyz, &yxyw, &yxzx, &yxzy, &yxzz, &yxzw, &yxwx, &yxwy, &yxwz, &yxww,
		&yyxx, &yyxy, &yyxz, &yyxw, &yyyx, &yyyy, &yyyz, &yyyw, &yyzx, &yyzy, &yyzz, &yyzw, &yywx, &yywy, &yywz, &yyww,
		&yzxx, &yzxy, &yzxz, &yzxw, &yzyx, &yzyy, &yzyz, &yzyw, &yzzx, &yzzy, &yzzz, &yzzw, &yzwx, &yzwy, &yzwz, &yzww,
		&ywxx, &ywxy, &ywxz, &ywxw, &ywyx, &ywyy, &ywyz, &ywyw, &ywzx, &ywzy, &ywzz, &ywzw, &ywwx, &ywwy, &ywwz, &ywww,
		&zxxx, &zxxy, &zxxz, &zxxw, &zxyx, &zxyy, &zxyz, &zxyw, &zxzx, &zxzy, &zxzz, &zxzw, &zxwx, &zxwy, &zxwz, &zxww,
		&zyxx, &zyxy, &zyxz, &zyxw, &zyyx, &zyyy, &zyyz, &zyyw, &zyzx, &zyzy, &zyzz, &zyzw, &zywx, &zywy, &zywz, &zyww,
		&zzxx, &zzxy, &zzxz, &zzxw, &zzyx, &zzyy, &zzyz, &zzyw, &zzzx, &zzzy, &zzzz, &zzzw, &zzwx, &zzwy, &zzwz, &zzww,
		&zwxx, &zwxy, &zwxz, &zwxw, &zwyx, &zwyy, &zwyz, &zwyw, &zwzx, &zwzy, &zwzz, &zwzw, &zwwx, &zwwy, &zwwz, &zwww,
		&wxxx, &wxxy, &wxxz, &wxxw, &wxyx, &wxyy, &wxyz, &wxyw, &wxzx, &wxzy, &wxzz, &wxzw, &wxwx, &wxwy, &wxwz, &wxww,
		&wyxx, &wyxy, &wyxz, &wyxw, &wyyx, &wyyy, &wyyz, &wyyw, &wyzx, &wyzy, &wyzz, &wyzw, &wywx, &wywy, &wywz, &wyww,
		&wzxx, &wzxy, &wzxz, &wzxw, &wzyx, &wzyy, &wzyz, &wzyw, &wzzx, &wzzy, &wzzz, &wzzw, &wzwx, &wzwy, &wzwz, &wzww,
		&wwxx, &wwxy, &wwxz, &wwxw, &wwyx, &wwyy, &wwyz, &wwyw, &wwzx, &wwzy, &wwzz, &wwzw, &wwwx, &wwwy, &wwwz, &wwww;

	ggtpe r, g, b, a;
	__vec2 rr, rg, rb, ra, gr, gg, gb, ga, br, bg, bb, ba, ar, ag, ab, aa;
	__vec3 rrr, rrg, rrb, rgr, rgg, rgb, grr, grg, grb, ggr, ggg, ggb, gbr, gbg, gbb, brr, brg, brb, bgr, bgg, bgb, bbr, bbg, bbb;
	__vec4 &rrrr, &rrrg, &rrrb, &rrra, &rrgr, &rrgg, &rrgb, &rrga, &rrbr, &rrbg, &rrbb, &rrba, &rrar, &rrag, &rrab, &rraa,
		&rgrr, &rgrg, &rgrb, &rgra, &rggr, &rggg, &rggb, &rgga, &rgbr, &rgbg, &rgbb, &rgba, &rgar, &rgag, &rgab, &rgaa,
		&rbrr, &rbrg, &rbrb, &rbra, &rbgr, &rbgg, &rbgb, &rbga, &rbbr, &rbbg, &rbbb, &rbba, &rbar, &rbag, &rbab, &rbaa,
		&rarr, &rarg, &rarb, &rara, &ragr, &ragg, &ragb, &raga, &rabr, &rabg, &rabb, &raba, &raar, &raag, &raab, &raaa,
		&grrr, &grrg, &grrb, &grra, &grgr, &grgg, &grgb, &grga, &grbr, &grbg, &grbb, &grba, &grar, &grag, &grab, &graa,
		&ggrr, &ggrg, &ggrb, &ggra, &gggr, &gggg, &gggb, &ggga, &ggbr, &ggbg, &ggbb, &ggba, &ggar, &ggag, &ggab, &ggaa,
		&gbrr, &gbrg, &gbrb, &gbra, &gbgr, &gbgg, &gbgb, &gbga, &gbbr, &gbbg, &gbbb, &gbba, &gbar, &gbag, &gbab, &gbaa,
		&garr, &garg, &garb, &gara, &gagr, &gagg, &gagb, &gaga, &gabr, &gabg, &gabb, &gaba, &gaar, &gaag, &gaab, &gaaa,
		&brrr, &brrg, &brrb, &brra, &brgr, &brgg, &brgb, &brga, &brbr, &brbg, &brbb, &brba, &brar, &brag, &brab, &braa,
		&bgrr, &bgrg, &bgrb, &bgra, &bggr, &bggg, &bggb, &bgga, &bgbr, &bgbg, &bgbb, &bgba, &bgar, &bgag, &bgab, &bgaa,
		&bbrr, &bbrg, &bbrb, &bbra, &bbgr, &bbgg, &bbgb, &bbga, &bbbr, &bbbg, &bbbb, &bbba, &bbar, &bbag, &bbab, &bbaa,
		&barr, &barg, &barb, &bara, &bagr, &bagg, &bagb, &baga, &babr, &babg, &babb, &baba, &baar, &baag, &baab, &baaa,
		&arrr, &arrg, &arrb, &arra, &argr, &argg, &argb, &arga, &arbr, &arbg, &arbb, &arba, &arar, &arag, &arab, &araa,
		&agrr, &agrg, &agrb, &agra, &aggr, &aggg, &aggb, &agga, &agbr, &agbg, &agbb, &agba, &agar, &agag, &agab, &agaa,
		&abrr, &abrg, &abrb, &abra, &abgr, &abgg, &abgb, &abga, &abbr, &abbg, &abbb, &abba, &abar, &abag, &abab, &abaa,
		&aarr, &aarg, &aarb, &aara, &aagr, &aagg, &aagb, &aaga, &aabr, &aabg, &aabb, &aaba, &aaar, &aaag, &aaab, &aaaa;


	gtype operator [] (int i);

	__vec4<gtype>& operator*= (__vec4<gtype>);
	__vec4<gtype>& operator/= (__vec4<gtype>);
	__vec4<gtype>& operator+= (__vec4<gtype>);
	__vec4<gtype>& operator-= (__vec4<gtype>);

	__vec4<gtype>& operator*= (gtype);
	__vec4<gtype>& operator/= (gtype);
	__vec4<gtype>& operator+= (gtype);
	__vec4<gtype>& operator-= (gtype);
	__vec4<gtype>& operator= (gtype);
	__vec4<gtype>& operator- (gtype);
	__vec4<gtype>& operator- ();

};

typedef __vec2<float> vec2;
typedef __vec3<float> vec3;
typedef __vec4<float> vec4;

typedef __vec2<int> ivec2;
typedef __vec3<int> ivec3;
typedef __vec4<int> ivec4;

typedef __vec2<unsigned int> uvec2;
typedef __vec3<unsigned int> uvec3;
typedef __vec4<unsigned int> uvec4;

typedef __vec2<double> dvec2;
typedef __vec3<double> dvec3;
typedef __vec4<double> dvec4;

typedef __vec2<bool> bvec2;
typedef __vec3<bool> bvec3;
typedef __vec4<bool> bvec4;


template <typename gtype>
struct __mat2
{
	__mat2<gtype> ();
	__mat2<gtype> (gtype);
	__mat2<gtype> (__mat2<gtype>);
	__mat2<gtype> (__vec2<gtype>, __vec2<gtype>);
	__mat2<gtype> (gtype, gtype, gtype, gtype);

	__vec2<gtype> operator [] (int i);
};

template <typename gtype>
struct __mat3x2
{
	__mat3x2<gtype> ();
	__mat3x2<gtype> (gtype);
	__mat3x2<gtype> (__mat2<gtype>);
	__mat3x2<gtype> (__vec2<gtype>, __vec2<gtype>, __vec2<gtype>);
	__mat3x2<gtype> (gtype, gtype, gtype, gtype, gtype, gtype);

	__vec2<gtype> operator [] (int i);
};

template <typename gtype>
struct __mat4x2
{
	__mat4x2<gtype> ();
	__mat4x2<gtype> (gtype);
	__mat4x2<gtype> (__mat2<gtype>);
	__mat4x2<gtype> (__vec2<gtype>, __vec2<gtype>, __vec2<gtype>, __vec2<gtype>);
	__mat4x2<gtype> (gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype);

	__vec2<gtype> operator [] (int i);
};

template <typename gtype>
struct __mat2x3
{
	__mat2x3<gtype> ();
	__mat2x3<gtype> (gtype);
	__mat2x3<gtype> (__mat2<gtype>);
	__mat2x3<gtype> (__mat3<gtype>);
	__mat2x3<gtype> (__vec3<gtype>, __vec3<gtype>);
	__mat2x3<gtype> (__vec2<gtype>, gtype, __vec2<gtype>, gtype);
	__mat2x3<gtype> (gtype, gtype, gtype, gtype, gtype, gtype);

	__vec3<gtype> operator [] (int i);
};

template <typename gtype>
struct __mat3
{
	__mat3<gtype> ();
	__mat3<gtype> (__mat2<gtype>);
	__mat3<gtype> (__mat3<gtype>);
	__mat3<gtype> (__vec3<gtype>, __vec3<gtype>, __vec3<gtype>);
	__mat3<gtype> (__vec2<gtype>, gtype, __vec2<gtype>, gtype, __vec2<gtype>, gtype);
	__mat3<gtype> (gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype);

	__vec3<gtype> operator [] (int i);
	__vec3<gtype> operator * (__vec3<gtype> );
};

template <typename gtype>
struct __mat4x3
{
	__mat4x3<gtype> ();
	__mat4x3<gtype> (gtype);
	__mat4x3<gtype> (__mat2<gtype>);
	__mat4x3<gtype> (__mat3<gtype>);
	__mat4x3<gtype> (__vec3<gtype>, __vec3<gtype>, __vec3<gtype>, __vec3<gtype>);
	__mat4x3<gtype> (__vec2<gtype>, gtype, __vec2<gtype>, gtype, __vec2<gtype>, gtype, __vec2<gtype>, gtype);
	__mat4x3<gtype> (gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype);

	__vec3<gtype> operator [] (int i);
};

template <typename gtype>
struct __mat2x4
{
	__mat2x4<gtype> ();
	__mat2x4<gtype> (gtype);
	__mat2x4<gtype> (__mat2<gtype>);
	__mat2x4<gtype> (__mat3<gtype>);
	__mat2x4<gtype> (__mat4<gtype>);
	__mat2x4<gtype> (__vec4<gtype>, __vec4<gtype>);
	__mat2x4<gtype> (__vec3<gtype>, gtype, __vec3<gtype>, gtype);
	__mat2x4<gtype> (__vec2<gtype>, gtype, gtype, __vec2<gtype>, gtype, gtype);
	__mat2x4<gtype> (gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype);

	__vec4<gtype> operator [] (int i);
};

template <typename gtype>
struct __mat3x4
{
	__mat3x4<gtype> ();
	__mat3x4<gtype> (gtype);
	__mat3x4<gtype> (__mat2<gtype>);
	__mat3x4<gtype> (__mat3<gtype>);
	__mat3x4<gtype> (__mat4<gtype>);
	__mat3x4<gtype> (__vec4<gtype>, __vec4<gtype>, __vec4<gtype>, __vec4<gtype>);
	__mat3x4<gtype> (__vec3<gtype>, gtype, __vec3<gtype>, gtype, __vec3<gtype>, gtype);
	__mat3x4<gtype> (__vec2<gtype>, gtype, gtype, __vec2gtype>, gtype, gtype, __vec2<gtype>, gtype, gtype, __vec2<gtype>, gtype, gtype);
	__mat3x4<gtype> (gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype);

	__vec4<gtype> operator [] (int i);
};

template <typename gtype>
struct __mat4
{
	__mat4<gtype> ();
	__mat4<gtype> (gtype);
	__mat4<gtype> (__mat2<gtype>);
	__mat4<gtype> (__mat3<gtype>);
	__mat4<gtype> (__mat4<gtype>);
	__mat4<gtype> (__vec4<gtype>, __vec4<gtype>, __vec4<gtype>, __vec4<gtype>);
	__mat4<gtype> (__vec3<gtype>, gtype, __vec3<gtype>, gtype, __vec3<gtype>, gtype);
	__mat4<gtype> (__vec2<gtype>, gtype, gtype, __vec2gtype>, gtype, gtype, __vec2<gtype>, gtype, gtype, __vec2<gtype>, gtype, gtype);
	__mat4<gtype> (gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype, gtype);

	__vec4<gtype> operator [] (int i);
	__mat4<gtype> operator * (__mat4<gtype> );
	__vec4<gtype> operator * (__vec4<gtype> );
};


typedef __mat2<float> mat2;
typedef __mat2<float> mat2x2;
typedef __mat2<double> dmat2;
typedef __mat2<double> dmat2x2;
typedef __mat3x2<float> mat3x2;
typedef __mat3x2<double> dmat3x2;
typedef __mat4x2<float> mat4x2;
typedef __mat4x2<double> dmat4x2;

typedef __mat2x3<float> mat2x3;
typedef __mat2x3<double> dmat2x3;
typedef __mat3<float> mat3;
typedef __mat3<float> mat3x3;
typedef __mat3<double> dmat3;
typedef __mat3<double> dmat3x3;
typedef __mat4x3<float> mat4x3;
typedef __mat4x3<double> dmat4x3;

typedef __mat2x4<float> mat2x4;
typedef __mat2x4<double> dmat2x4;
typedef __mat3x4<float> mat3x4;
typedef __mat3x4<double> dmat3x4;
typedef __mat4<float> mat4;
typedef __mat4<float> mat4x4;
typedef __mat4<double> dmat4;
typedef __mat4<double> dmat4x4;




struct sampler1D {};
struct isampler1D {};
struct usampler1D {};

struct sampler2D {};
struct isampler2D {};
struct usampler2D {};

struct sampler3D {};
struct isampler3D {};
struct usampler3D {};

struct sampler2DRect {};
struct isampler2DRect {};
struct usampler2DRect {};

struct samplerCube {};
struct isamplerCube {};
struct usamplerCube {};

struct sampler1DShadow {};
struct isampler1DShadow {};
struct usampler1DShadow {};

struct sampler2DShadow {};
struct isampler2DShadow {};
struct usampler2DShadow {};

struct sampler2DRectShadow {};
struct isampler2DRectShadow {};
struct usampler2DRectShadow {};

struct samplerCubeShadow {};
struct isamplerCubeShadow {};
struct usamplerCubeShadow {};

struct sampler1DArray {};
struct isampler1DArray {};
struct usampler1DArray {};

struct sampler2DArray {};
struct isampler2DArray {};
struct usampler2DArray {};

struct samplerCubeArray {};
struct isamplerCubeArray {};
struct usamplerCubeArray {};

struct sampler1DArrayShadow {};
struct isampler1DArrayShadow {};
struct usampler1DArrayShadow {};

struct sampler2DArrayShadow {};
struct isampler2DArrayShadow {};
struct usampler2DArrayShadow {};

struct samplerCubeArrayShadow {};
struct isamplerCubeArrayShadow {};
struct usamplerCubeArrayShadow {};

struct samplerRect {};
struct isamplerRect {};
struct usamplerRect {};

struct samplerRectShadow {};
struct isamplerRectShadow {};
struct usamplerRectShadow {};

struct samplerBuffer {};
struct isamplerBuffer {};
struct usamplerBuffer {};

struct sampler2DMS {};
struct isampler2DMS {};
struct usampler2DMS {};

struct sampler2DMSArray {};
struct isampler2DMSArray {};
struct usampler2DMSArray {};




struct image1D {};
struct iimage1D {};
struct uimage1D {};

struct image2D {};
struct iimage2D {};
struct uimage2D {};

struct image3D {};
struct iimage3D {};
struct uimage3D {};

struct image2DRect {};
struct iimage2DRect {};
struct uimage2DRect {};

struct imageCube {};
struct iimageCube {};
struct uimageCube {};

struct image1DArray {};
struct iimage1DArray {};
struct uimage1DArray {};

struct image2DArray {};
struct iimage2DArray {};
struct uimage2DArray {};

struct imageBuffer {};
struct iimageBuffer {};
struct uimageBuffer {};

struct imageCubeArray {};
struct iimageCubeArray {};
struct uimageCubeArray {};

struct image2DMS {};
struct iimage2DMS {};
struct uimage2DMS {};

struct image2DMSArray {};
struct iimage2DMSArray {};
struct uimage2DMSArray {};




typedef int rgba32f;
typedef int rgba16f;
typedef int rg32f;
typedef int rg16f;
typedef int r11f_g11f_b10f;
typedef int r32f;
typedef int r16f;
typedef int rgba16;
typedef int rgb10_a2;
typedef int rgba8;
typedef int rg16;
typedef int rg8;
typedef int r16;
typedef int r8;
typedef int rgba16_snorm;
typedef int rgba8_snorm;
typedef int rg16_snorm;
typedef int rg8_snorm;
typedef int r16_snorm;
typedef int r8_snorm;

typedef int rgba32i;
typedef int rgba16i;
typedef int rgba8i;
typedef int rg32i;
typedef int rg16i;
typedef int rg8i;
typedef int r32i;
typedef int r16i;
typedef int r8i;

typedef int rgba32ui;
typedef int rgba16ui;
typedef int rgb10_a2ui;
typedef int rgba8ui;
typedef int rg32ui;
typedef int rg16ui;
typedef int rg8ui;
typedef int r32ui;
typedef int r16ui;
typedef int r8ui;


// ******************************************************* //
// ********************* Operators *********************** //
const vec4 operator* (const mat4&, const vec4&);

GENFUN2_VEC (operator*);
GENFUN2_VEC (operator/);
GENFUN2_VEC (operator+);
GENFUN2_VEC (operator-);

GENFUN2D_VEC (operator*);
GENFUN2D_VEC (operator/);
GENFUN2D_VEC (operator+);
GENFUN2D_VEC (operator-);

GENFUN2I_VEC (operator*);
GENFUN2I_VEC (operator/);
GENFUN2I_VEC (operator+);
GENFUN2I_VEC (operator-);

GENFUN2U_VEC (operator*);
GENFUN2U_VEC (operator/);
GENFUN2U_VEC (operator+);
GENFUN2U_VEC (operator-);





// ******************************************************* //
// ********************* Functions *********************** //
GENFUN_ALL (abs);
GENFUN (acos);
GENFUN (acosh);

bool all (bvec2); bool all (bvec3); bool all (bvec4);
bool any (bvec2); bool any (bvec3); bool any (bvec4);

GENFUN (asin);
GENFUN (asinh);
GENFUN (atan);
GENFUN (atanh);

int atomicAdd (int mem, int data); uint atomicAdd (uint mem, uint data);
int atomicAnd (int mem, int data); uint atomicAnd (uint mem, uint data);
int atomicCompSwap (int mem, uint compare, uint data); uint atomicCompSwap (uint mem, uint compare, uint data);
uint atomicCounter (atomic_uint c);
uint atomicCounterDecrement (atomic_uint c);
uint atomicCounterIncrement (atomic_uint c);
int atomicExchange (int mem, int data); uint atomicExchange (uint mem, uint data);
int atomicMax (int mem, int data); uint atomicMax (uint mem, uint data);
int atomicMin (int mem, int data); uint atomicMin (uint mem, uint data);
int atomicOr (int mem, int data); uint atomicOr (uint mem, uint data);
int atomicXor (int mem, int data); uint atomicXor (uint mem, uint data);

void barrier ();

int bitCount (int value); uint bitCount (uint value);
int bitfieldExtract (int value, int offset, int bits); uint bitfieldExtract (uint value, int offset, int bits);
int bitfieldInsert (int base, int insert, int offset, int bits); uint bitfieldInsert (uint base, uint insert, int offset, int bits);
int bitfieldReverse (int value); uint bitfieldReverse (uint value);

GENFUN (ceil);
GENFUND (ceil);

float clamp (float, float, float); float clamp (float, double, double); vec2 clamp (vec2, float, float); vec3 clamp (vec3, float, float);vec3 clamp (vec3, vec3, vec3); vec4 clamp (vec4, float, float);
double clamp (double, double, double); dvec2 clamp (dvec2, double, double); dvec3 clamp (dvec3, double, double); dvec4 clamp (dvec4, double, double);
int clamp (int, int, int); ivec2 clamp (ivec2, int, int); ivec3 clamp (ivec3, int, int); ivec4 clamp (ivec4, int, int);
uint clamp (uint, uint, uint); uvec2 clamp (uvec2, uint, uint); uvec3 clamp (uvec3, uint, uint); uvec4 clamp (uvec4, uint, uint);

GENFUN (cos);
GENFUN (cosh);

vec3 cross (vec3, vec3); dvec3 cross (dvec3, dvec3);

GENFUN_ALL (degrees);

float determinant (mat2 m); float determinant (mat3 m); float determinant (mat4 m); double determinant (dmat2 m); double determinant (dmat3 m); double determinant (dmat4 m);

float distance (float p0, float p1); float distance (vec2 p0, vec2 p1); float distance (vec3 p0, vec3 p1); float distance (vec4 p0, vec4 p1);
double distance (double p0, double p1); double distance (dvec2 p0, dvec2 p1); double distance (dvec3 p0, dvec3 p1); double distance (dvec4 p0, dvec4 p1);

float dot (vec2, vec2); float dot (vec3, vec3); float dot (vec4, vec4);
double dot (dvec2, dvec2); float dot (dvec3, dvec3); float dot (dvec4, dvec4);


void EmitStreamVertex (int stream);
void EmitVertex ();
void EndPrimitive ();
void EndPrimitive ();


bvec2 equal (vec2 x, vec2 y); bvec3 equal (ivec3 x, ivec3 y); bvec4 equal (uvec4 x, uvec4 y);
GENFUN_ALL (exp);
GENFUN_ALL (exp2);

GENFUN3 (faceforward);
GENFUN3D (faceforward);
GENFUN_ALL (dFdx);
GENFUN_ALL (dFdy);
GENFUNI (findLSB);
GENFUNU (findLSB);
GENFUNI (findMSB);
GENFUNU (findMSB);

int floatBitsToInt (float x); ivec2 floatBitsToInt (vec2 x); ivec3 floatBitsToInt (vec3 x); ivec4 floatBitsToInt (vec4 x);
uint floatBitsToUInt (float x); uvec2 floatBitsToUInt (vec2 x); uvec3 floatBitsToUInt (vec3 x); uvec4 floatBitsToUInt (vec4 x);

GENFUN (floor);
GENFUND (floor);
GENFUN3 (fma);
GENFUN3D (fma);
GENFUN_ALL (fract);

float frexp (float x, out int exp); vec2 frexp (vec2 x, out int exp); vec3 frexp (vec3 x, out int exp); vec4 frexp (vec4 x, out int exp);
double frexp (double x, out int exp); dvec2 frexp (dvec2 x, out int exp); dvec3 frexp (dvec3 x, out int exp); dvec4 frexp (dvec4 x, out int exp);

GENFUN_ALL (fwidth);

bvec2 greaterThan (vec2 x, vec2 y); bvec3 greaterThan (vec3 x, vec3 y); bvec4 greaterThan (vec4 x, vec4 y);
bvec2 greaterThan (ivec2 x, ivec2 y); bvec3 greaterThan (ivec3 x, ivec3 y); bvec4 greaterThan (ivec4 x, ivec4 y);
bvec2 greaterThan (uvec2 x, uvec2 y); bvec3 greaterThan (uvec3 x, uvec3 y); bvec4 greaterThan (uvec4 x, uvec4 y);

bvec2 greaterThanEqual (vec2 x, vec2 y); bvec3 greaterThanEqual (vec3 x, vec3 y); bvec4 greaterThanEqual (vec4 x, vec4 y);
bvec2 greaterThanEqual (ivec2 x, ivec2 y); bvec3 greaterThanEqual (ivec3 x, ivec3 y); bvec4 greaterThanEqual (ivec4 x, ivec4 y);
bvec2 greaterThanEqual (uvec2 x, uvec2 y); bvec3 greaterThanEqual (uvec3 x, uvec3 y); bvec4 greaterThanEqual (uvec4 x, uvec4 y);

void groupMemoryBarrier ();



uint imageAtomicAdd (uimage1D image, int P, uint data);
uint imageAtomicAdd (uimage2D image, ivec2 P, uint data);
uint imageAtomicAdd (uimage3D image, ivec3 P, uint data);
uint imageAtomicAdd (uimage2DRect image, ivec2 P, uint data);
uint imageAtomicAdd (uimageCube image, ivec3 P, uint data);
uint imageAtomicAdd (uimageBuffer image, int P, uint data);
uint imageAtomicAdd (uimage1DArray image, ivec2 P, uint data);
uint imageAtomicAdd (uimage2DArray image, ivec3 P, uint data);
uint imageAtomicAdd (uimageCubeArray image, ivec3 P, uint data);
uint imageAtomicAdd (uimage2DMS image, ivec2 P, int sample, uint data);
uint imageAtomicAdd (uimage2DMSArray image, ivec3 P, int sample, uint data);

int imageAtomicAdd (iimage1D image, int P, int data);
int imageAtomicAdd (iimage2D image, ivec2 P, int data);
int imageAtomicAdd (iimage3D image, ivec3 P, int data);
int imageAtomicAdd (iimage2DRect image, ivec2 P, int data);
int imageAtomicAdd (iimageCube image, ivec3 P, int data);
int imageAtomicAdd (iimageBuffer image, int P, uint data);
int imageAtomicAdd (iimage1DArray image, ivec2 P, int data);
int imageAtomicAdd (iimage2DArray image, ivec3 P, int data);
int imageAtomicAdd (iimageCubeArray image, ivec3 P, int data);
int imageAtomicAdd (iimage2DMS image, ivec2 P, int sample, int data);
int imageAtomicAdd (iimage2DMSArray image, ivec3 P, int sample, int data);

uint imageAtomicAnd (uimage1D image, int P, uint data);
uint imageAtomicAnd (uimage2D image, ivec2 P, uint data);
uint imageAtomicAnd (uimage3D image, ivec3 P, uint data);
uint imageAtomicAnd (uimage2DRect image, ivec2 P, uint data);
uint imageAtomicAnd (uimageCube image, ivec3 P, uint data);
uint imageAtomicAnd (uimageBuffer image, int P, uint data);
uint imageAtomicAnd (uimage1DArray image, ivec2 P, uint data);
uint imageAtomicAnd (uimage2DArray image, ivec3 P, uint data);
uint imageAtomicAnd (uimageCubeArray image, ivec3 P, uint data);
uint imageAtomicAnd (uimage2DMS image, ivec2 P, int sample, uint data);
uint imageAtomicAnd (uimage2DMSArray image, ivec3 P, int sample, uint data);

int imageAtomicAnd (iimage1D image, int P, int data);
int imageAtomicAnd (iimage2D image, ivec2 P, int data);
int imageAtomicAnd (iimage3D image, ivec3 P, int data);
int imageAtomicAnd (iimage2DRect image, ivec2 P, int data);
int imageAtomicAnd (iimageCube image, ivec3 P, int data);
int imageAtomicAnd (iimageBuffer image, int P, uint data);
int imageAtomicAnd (iimage1DArray image, ivec2 P, int data);
int imageAtomicAnd (iimage2DArray image, ivec3 P, int data);
int imageAtomicAnd (iimageCubeArray image, ivec3 P, int data);
int imageAtomicAnd (iimage2DMS image, ivec2 P, int sample, int data);
int imageAtomicAnd (iimage2DMSArray image, ivec3 P, int sample, int data);


uint imageAtomicCompSwap (uimage1D image, int P, uint compare, uint data);
uint imageAtomicCompSwap (uimage2D image, ivec2 P, uint compare, uint data);
uint imageAtomicCompSwap (uimage3D image, ivec3 P, uint compare, uint data);
uint imageAtomicCompSwap (uimage2DRect image, ivec2 P, uint compare, uint data);
uint imageAtomicCompSwap (uimageCube image, ivec3 P, uint compare, uint data);
uint imageAtomicCompSwap (uimageBuffer image, int P, uint compare, uint data);
uint imageAtomicCompSwap (uimage1DArray image, ivec2 P, uint compare, uint data);
uint imageAtomicCompSwap (uimage2DArray image, ivec3 P, uint compare, uint data);
uint imageAtomicCompSwap (uimageCubeArray image, ivec3 P, uint compare, uint data);
uint imageAtomicCompSwap (uimage2DMS image, ivec2 P, int sample, uint compare, uint data);
uint imageAtomicCompSwap (uimage2DMSArray image, ivec3 P, int sample, uint compare, uint data);

int imageAtomicCompSwap (iimage1D image, int P, int compare, int data);
int imageAtomicCompSwap (iimage2D image, ivec2 P, int compare, int data);
int imageAtomicCompSwap (iimage3D image, ivec3 P, int compare, int data);
int imageAtomicCompSwap (iimage2DRect image, ivec2 P, int compare, int data);
int imageAtomicCompSwap (iimageCube image, ivec3 P, int compare, int data);
int imageAtomicCompSwap (iimageBuffer image, int P, int compare, int data);
int imageAtomicCompSwap (iimage1DArray image, ivec2 P, int compare, int data);
int imageAtomicCompSwap (iimage2DArray image, ivec3 P, int compare, int data);
int imageAtomicCompSwap (iimageCubeArray image, ivec3 P, int compare, int data);
int imageAtomicCompSwap (iimage2DMS image, ivec2 P, int sample, int compare, int data);
int imageAtomicCompSwap (iimage2DMSArray image, ivec3 P, int sample, int compare, int data);


uint imageAtomicExchange (uimage1D image, int P, uint data);
uint imageAtomicExchange (uimage2D image, ivec2 P, uint data);
uint imageAtomicExchange (uimage3D image, ivec3 P, uint data);
uint imageAtomicExchange (uimage2DRect image, ivec2 P, uint data);
uint imageAtomicExchange (uimageCube image, ivec3 P, uint data);
uint imageAtomicExchange (uimageBuffer image, int P, uint data);
uint imageAtomicExchange (uimage1DArray image, ivec2 P, uint data);
uint imageAtomicExchange (uimage2DArray image, ivec3 P, uint data);
uint imageAtomicExchange (uimageCubeArray image, ivec3 P, uint data);
uint imageAtomicExchange (uimage2DMS image, ivec2 P, int sample, uint data);
uint imageAtomicExchange (uimage2DMSArray image, ivec3 P, int sample, uint data);

int imageAtomicExchange (iimage1D image, int P, int data);
int imageAtomicExchange (iimage2D image, ivec2 P, int data);
int imageAtomicExchange (iimage3D image, ivec3 P, int data);
int imageAtomicExchange (iimage2DRect image, ivec2 P, int data);
int imageAtomicExchange (iimageCube image, ivec3 P, int data);
int imageAtomicExchange (iimageBuffer image, int P, int data);
int imageAtomicExchange (iimage1DArray image, ivec2 P, int data);
int imageAtomicExchange (iimage2DArray image, ivec3 P, int data);
int imageAtomicExchange (iimageCubeArray image, ivec3 P, int data);
int imageAtomicExchange (iimage2DMS image, ivec2 P, int sample, int data);
int imageAtomicExchange (iimage2DMSArray image, ivec3 P, int sample, int data);


uint imageAtomicMax (uimage1D image, int P, uint data);
uint imageAtomicMax (uimage2D image, ivec2 P, uint data);
uint imageAtomicMax (uimage3D image, ivec3 P, uint data);
uint imageAtomicMax (uimage2DRect image, ivec2 P, uint data);
uint imageAtomicMax (uimageCube image, ivec3 P, uint data);
uint imageAtomicMax (uimageBuffer, int P, uint data);
uint imageAtomicMax (uimage1DArray image, ivec2 P, uint data);
uint imageAtomicMax (uimage2DArray image, ivec3 P, uint data);
uint imageAtomicMax (uimageCubeArray image, ivec3 P, uint data);
uint imageAtomicMax (uimage2DMS image, ivec2 P, int sample, uint data);
uint imageAtomicMax (uimage2DMSArray image, ivec3 P, int sample, uint data);

int imageAtomicMax (iimage1D image, int P, int data);
int imageAtomicMax (iimage2D image, ivec2 P, int data);
int imageAtomicMax (iimage3D image, ivec3 P, int data);
int imageAtomicMax (iimage2DRect image, ivec2 P, int data);
int imageAtomicMax (iimageCube image, ivec3 P, int data);
int imageAtomicMax (iimageBuffer image, int P, int data);
int imageAtomicMax (iimage1DArray image, ivec2 P, int data);
int imageAtomicMax (iimage2DArray image, ivec3 P, int data);
int imageAtomicMax (iimageCubeArray image, ivec3 P, int data);
int imageAtomicMax (iimage2DMS image, ivec2 P, int sample, int data);
int imageAtomicMax (iimage2DMSArray image, ivec3 P, int sample, int data);



uint imageAtomicMin (uimage1D image, int P, uint data);
uint imageAtomicMin (uimage2D image, ivec2 P, uint data);
uint imageAtomicMin (uimage3D image, ivec3 P, uint data);
uint imageAtomicMin (uimage2DRect image, ivec2 P, uint data);
uint imageAtomicMin (uimageCube image, ivec3 P, uint data);
uint imageAtomicMin (uimageBuffer image, int P, uint data);
uint imageAtomicMin (uimage1DArray image, ivec2 P, uint data);
uint imageAtomicMin (uimage2DArray image, ivec3 P, uint data);
uint imageAtomicMin (uimageCubeArray image, ivec3 P, uint data);
uint imageAtomicMin (uimage2DMS image, ivec2 P, int sample, uint data);
uint imageAtomicMin (uimage2DMSArray image, ivec3 P, int sample, uint data);

int imageAtomicMin (iimage1D image, int P, int data);
int imageAtomicMin (iimage2D image, ivec2 P, int data);
int imageAtomicMin (iimage3D image, ivec3 P, int data);
int imageAtomicMin (iimage2DRect image, ivec2 P, int data);
int imageAtomicMin (iimageCube image, ivec3 P, int data);
int imageAtomicMin (iimageBuffer image, int P, int data);
int imageAtomicMin (iimage1DArray image, ivec2 P, int data);
int imageAtomicMin (iimage2DArray image, ivec3 P, int data);
int imageAtomicMin (iimageCubeArray image, ivec3 P, int data);
int imageAtomicMin (iimage2DMS image, ivec2 P, int sample, int data);
int imageAtomicMin (iimage2DMSArray image, ivec3 P, int sample, int data);




uint imageAtomicOr (uimage1D image, int P, uint data);
uint imageAtomicOr (uimage2D image, ivec2 P, uint data);
uint imageAtomicOr (uimage3D image, ivec3 P, uint data);
uint imageAtomicOr (uimage2DRect image, ivec2 P, uint data);
uint imageAtomicOr (uimageCube image, ivec3 P, uint data);
uint imageAtomicOr (uimageBuffer image, int P, uint data);
uint imageAtomicOr (uimage1DArray image, ivec2 P, uint data);
uint imageAtomicOr (uimage2DArray image, ivec3 P, uint data);
uint imageAtomicOr (uimageCubeArray image, ivec3 P, uint data);
uint imageAtomicOr (uimage2DMS image, ivec2 P, int sample, uint data);
uint imageAtomicOr (uimage2DMSArray image, ivec3 P, int sample, uint data);

int imageAtomicOr (iimage1D image, int P, int data);
int imageAtomicOr (iimage2D image, ivec2 P, int data);
int imageAtomicOr (iimage3D image, ivec3 P, int data);
int imageAtomicOr (iimage2DRect image, ivec2 P, int data);
int imageAtomicOr (iimageCube image, ivec3 P, int data);
int imageAtomicOr (iimageBuffer image, int P, int data);
int imageAtomicOr (iimage1DArray image, ivec2 P, int data);
int imageAtomicOr (iimage2DArray image, ivec3 P, int data);
int imageAtomicOr (iimageCubeArray image, ivec3 P, int data);
int imageAtomicOr (iimage2DMS image, ivec2 P, int sample, int data);
int imageAtomicOr (iimage2DMSArray image, ivec3 P, int sample, int data);


uint imageAtomicXor (uimage1D image, int P, uint data);
uint imageAtomicXor (uimage2D image, ivec2 P, uint data);
uint imageAtomicXor (uimage3D image, ivec3 P, uint data);
uint imageAtomicXor (uimage2DRect image, ivec2 P, uint data);
uint imageAtomicXor (uimageCube image, ivec3 P, uint data);
uint imageAtomicXor (uimageBuffer image, int P, uint data);
uint imageAtomicXor (uimage1DArray image, ivec2 P, uint data);
uint imageAtomicXor (uimage2DArray image, ivec3 P, uint data);
uint imageAtomicXor (uimageCubeArray image, ivec3 P, uint data);
uint imageAtomicXor (uimage2DMS image, ivec2 P, int sample, uint data);
uint imageAtomicXor (uimage2DMSArray image, ivec3 P, int sample, uint data);

int imageAtomicXor (iimage1D image, int P, int data);
int imageAtomicXor (iimage2D image, ivec2 P, int data);
int imageAtomicXor (iimage3D image, ivec3 P, int data);
int imageAtomicXor (iimage2DRect image, ivec2 P, int data);
int imageAtomicXor (iimageCube image, ivec3 P, int data);
int imageAtomicXor (iimageBuffer image, int P, int data);
int imageAtomicXor (iimage1DArray image, ivec2 P, int data);
int imageAtomicXor (iimage2DArray image, ivec3 P, int data);
int imageAtomicXor (iimageCubeArray image, ivec3 P, int data);
int imageAtomicXor (iimage2DMS image, ivec2 P, int sample, int data);
int imageAtomicXor (iimage2DMSArray image, ivec3 P, int sample, int data);


vec4 imageLoad (image1D image, int P);
vec4 imageLoad (image2D image, ivec2 P);
vec4 imageLoad (image3D image, ivec3 P);
vec4 imageLoad (image2DRect image, ivec2 P);
vec4 imageLoad (imageCube image, ivec3 P);
vec4 imageLoad (imageBuffer image, int P);
vec4 imageLoad (image1DArray image, ivec2 P);
vec4 imageLoad (image2DArray image, ivec3 P);
vec4 imageLoad (imageCubeArray image, ivec3 P);
vec4 imageLoad (image2DMS image, ivec2 P, int sample);
vec4 imageLoad (image2DMSArray image, ivec3 P, int sample);

ivec4 imageLoad (iimage1D image, int P);
ivec4 imageLoad (iimage2D image, ivec2 P);
ivec4 imageLoad (iimage3D image, ivec3 P);
ivec4 imageLoad (iimage2DRect image, ivec2 P);
ivec4 imageLoad (iimageCube image, ivec3 P);
ivec4 imageLoad (iimageBuffer image, int P);
ivec4 imageLoad (iimage1DArray image, ivec2 P);
ivec4 imageLoad (iimage2DArray image, ivec3 P);
ivec4 imageLoad (iimageCubeArray image, ivec3 P);
ivec4 imageLoad (iimage2DMS image, ivec2 P, int sample);
ivec4 imageLoad (iimage2DMSArray image, ivec3 P, int sample);

uvec4 imageLoad (uimage1D image, int P);
uvec4 imageLoad (uimage2D image, ivec2 P);
uvec4 imageLoad (uimage3D image, ivec3 P);
uvec4 imageLoad (uimage2DRect image, ivec2 P);
uvec4 imageLoad (uimageCube image, ivec3 P);
uvec4 imageLoad (uimageBuffer image, int P);
uvec4 imageLoad (uimage1DArray image, ivec2 P);
uvec4 imageLoad (uimage2DArray image, ivec3 P);
uvec4 imageLoad (uimageCubeArray image, ivec3 P);
uvec4 imageLoad (uimage2DMS image, ivec2 P, int sample);
uvec4 imageLoad (uimage2DMSArray image, ivec3 P, int sample);


int imageSize (image1D image);
ivec2 imageSize (image2D image);
ivec3 imageSize (image3D image);
ivec2 imageSize (imageCube image);
ivec3 imageSize (imageCubeArray image);
ivec2 imageSize (image1DArray image);
ivec3 imageSize (image2DArray image);
int imageSize (imageBuffer image);
ivec2 imageSize (image2DMS image);
ivec3 imageSize (image2DMSArray image);

int imageSize (iimage1D image);
ivec2 imageSize (iimage2D image);
ivec3 imageSize (iimage3D image);
ivec2 imageSize (iimageCube image);
ivec3 imageSize (iimageCubeArray image);
ivec2 imageSize (iimage1DArray image);
ivec3 imageSize (iimage2DArray image);
int imageSize (iimageBuffer image);
ivec2 imageSize (iimage2DMS image);
ivec3 imageSize (iimage2DMSArray image);

int imageSize (uimage1D image);
ivec2 imageSize (uimage2D image);
ivec3 imageSize (uimage3D image);
ivec2 imageSize (uimageCube image);
ivec3 imageSize (uimageCubeArray image);
ivec2 imageSize (uimage1DArray image);
ivec3 imageSize (uimage2DArray image);
int imageSize (uimageBuffer image);
ivec2 imageSize (uimage2DMS image);
ivec3 imageSize (uimage2DMSArray image);


void imageStore (image1D image, int P, vec4 data);
void imageStore (image2D image, ivec2 P, vec4 data);
void imageStore (image3D image, ivec3 P, vec4 data);
void imageStore (image2DRect image, ivec2 P, vec4 data);
void imageStore (imageCube image, ivec3 P, vec4 data);
void imageStore (imageBuffer image, int P, vec4 data);
void imageStore (image1DArray image, ivec2 P, vec4 data);
void imageStore (image2DArray image, ivec3 P, vec4 data);
void imageStore (imageCubeArray image, ivec3 P, vec4 data);
void imageStore (image2DMS image, ivec2 P, int sample, vec4 data);
void imageStore (image2DMSArray image, ivec3 P, int sample, vec4 data);

void imageStore (iimage1D image, int P, ivec4 data);
void imageStore (iimage2D image, ivec2 P, ivec4 data);
void imageStore (iimage3D image, ivec3 P, ivec4 data);
void imageStore (iimage2DRect image, ivec2 P, ivec4 data);
void imageStore (iimageCube image, ivec3 P, ivec4 data);
void imageStore (iimageBuffer image, int P, ivec4 data);
void imageStore (iimage1DArray image, ivec2 P, ivec4 data);
void imageStore (iimage2DArray image, ivec3 P, ivec4 data);
void imageStore (iimageCubeArray image, ivec3 P, ivec4 data);
void imageStore (iimage2DMS image, ivec2 P, int sample, ivec4 data);
void imageStore (iimage2DMSArray image, ivec3 P, int sample, ivec4 data);

void imageStore (uimage1D image, int P, uvec4 data);
void imageStore (uimage2D image, ivec2 P, uvec4 data);
void imageStore (uimage3D image, ivec3 P, uvec4 data);
void imageStore (uimage2DRect image, ivec2 P, uvec4 data);
void imageStore (uimageCube image, ivec3 P, uvec4 data);
void imageStore (uimageBuffer image, int P, uvec4 data);
void imageStore (uimage1DArray image, ivec2 P, uvec4 data);
void imageStore (uimage2DArray image, ivec3 P, uvec4 data);
void imageStore (uimageCubeArray image, ivec3 P, uvec4 data);
void imageStore (uimage2DMS image, ivec2 P, int sample, uvec4 data);
void imageStore (uimage2DMSArray image, ivec3 P, int sample, uvec4 data);


void umulExtended (uint x, uint y, uint msb, uint lsb); void umulExtended (uvec2 x, uvec2 y, uvec2 msb, uvec2 lsb); void umulExtended (uvec3 x, uvec3 y, uvec3 msb, uvec3 lsb); void umulExtended (uvec4 x, uvec4 y, uvec4 msb, uvec4 lsb);
void umulExtended (int x, int y, int msb, int lsb); void umulExtended (ivec2 x, ivec2 y, ivec2 msb, ivec2 lsb); void umulExtended (ivec3 x, ivec3 y, ivec3 msb, ivec3 lsb); void umulExtended (ivec4 x, ivec4 y, ivec4 msb, ivec4 lsb);


float intBitsToFloat (int x); vec2 intBitsToFloat (ivec2 x); vec3 intBitsToFloat (ivec3 x); vec4 intBitsToFloat (ivec4 x);
float intBitsToFloat (uint x); vec2 intBitsToFloat (uvec2 x); vec3 intBitsToFloat (uvec3 x); vec4 intBitsToFloat (uvec4 x);

float interpolateAtCentroid (float interpolant);
vec2 interpolateAtCentroid (vec2 interpolant);
vec3 interpolateAtCentroid (vec3 interpolant);
vec4 interpolateAtCentroid (vec4 interpolant);

float interpolateAtOffset (float interpolant, vec2 offset);
vec2 interpolateAtOffset (vec2 interpolant, vec2 offset);
vec3 interpolateAtOffset (vec3 interpolant, vec2 offset);
vec4 interpolateAtOffset (vec4 interpolant, vec2 offset);

float interpolateAtSample (float interpolant, int sample);
vec2 interpolateAtSample (vec2 interpolant, int sample);
vec3 interpolateAtSample (vec3 interpolant, int sample);
vec4 interpolateAtSample (vec4 interpolant, int sample);

mat2 inverse (mat2 m);
mat3 inverse (mat3 m);
mat4 inverse (mat4 m);
dmat2 inverse (dmat2 m);
dmat3 inverse (dmat3 m);
dmat4 inverse (dmat4 m);

GENFUN (inversesqrt);

bool isinf (float x); bvec2 isinf (vec2 x); bvec3 isinf (vec3 x); bvec4 isinf (vec4 x);
bool isinf (double x); bvec2 isinf (dvec2 x); bvec3 isinf (dvec3 x); bvec4 isinf (dvec4 x);

bool isnan (float x); bvec2 isnan (vec2 x); bvec3 isnan (vec3 x); bvec4 isnan (vec4 x);
bool isnan (double x); bvec2 isnan (dvec2 x); bvec3 isnan (dvec3 x); bvec4 isnan (dvec4 x);


float ldexp (float x, int exp); vec2 ldexp (vec2 x, ivec2 exp); vec3 ldexp (vec3 x, ivec3 exp); vec4 ldexp (vec4 x, ivec4 exp);
double ldexp (double x, int exp); dvec2 ldexp (dvec2 x, ivec2 exp); dvec3 ldexp (dvec3 x, ivec3 exp); dvec4 ldexp (dvec4 x, ivec4 exp);

float length (vec2); float length (vec3); float length (vec4);
double length (dvec2); double length (dvec3); double length (dvec4);

bvec2 lessThan (vec2 x, vec2 y); bvec3 lessThan (vec3 x, vec3 y); bvec4 lessThan (vec4 x, vec4 y);
bvec2 lessThan (ivec2 x, ivec2 y); bvec3 lessThan (ivec3 x, ivec3 y); bvec4 lessThan (ivec4 x, ivec4 y);
bvec2 lessThan (uvec2 x, uvec2 y); bvec3 lessThan (uvec3 x, uvec3 y); bvec4 lessThan (uvec4 x, uvec4 y);

bvec2 lessThanEqual (vec2 x, vec2 y); bvec3 lessThanEqual (vec3 x, vec3 y); bvec4 lessThanEqual (vec4 x, vec4 y);
bvec2 lessThanEqual (ivec2 x, ivec2 y); bvec3 lessThanEqual (ivec3 x, ivec3 y); bvec4 lessThanEqual (ivec4 x, ivec4 y);
bvec2 lessThanEqual (uvec2 x, uvec2 y); bvec3 lessThanEqual (uvec3 x, uvec3 y); bvec4 lessThanEqual (uvec4 x, uvec4 y);

GENFUN_ALL (log);
GENFUN_ALL (log2);


GENFUN2_ALL (max);
void memoryBarrier ();
void memoryBarrierAtomicCounter ();
void memoryBarrierBuffer ();
void memoryBarrierImage ();
void memoryBarrierShared ();
GENFUN2_ALL (min);
GENFUN3_ALL (mix);

GENFUN2 (mod);
GENFUN2D (mod);
float mod (float x, float y); vec2 mod (vec2 x, float y); vec3 mod (vec3 x, float y); vec4 mod (vec4 x, float y);
double mod (double x, double y); dvec2 mod (dvec2 x, double y); dvec3 mod (dvec3 x, double y); dvec4 mod (dvec4 x, double y);
GENFUN2 (modf);
GENFUN2D (modf);


float noise1 (float x); float noise1 (vec2 x); float noise1 (vec3 x); float noise1 (vec4 x);
vec2 noise2 (float x); vec2 noise2 (vec2 x); vec2 noise2 (vec3 x); vec2 noise2 (vec4 x);
vec3 noise3 (float x); vec3 noise3 (vec2 x); vec3 noise3 (vec3 x); vec3 noise3 (vec4 x);
vec4 noise4 (float x); vec4 noise4 (vec2 x); vec4 noise4 (vec3 x); vec4 noise4 (vec4 x);

GENFUN_ALL (normalize);

bvec2 not (bvec2); bvec3 not (bvec3); bvec4 not (bvec4);
bvec2 notEqual (vec2 x, vec2 y); bvec3 notEqual (vec3 x, vec3 y); bvec4 notEqual (vec4 x, vec4 y);
bvec2 notEqual (ivec2 x, ivec2 y); bvec3 notEqual (ivec3 x, ivec3 y); bvec4 notEqual (ivec4 x, ivec4 y);
bvec2 notEqual (uvec2 x, uvec2 y); bvec3 notEqual (uvec3 x, uvec3 y); bvec4 notEqual (uvec4 x, uvec4 y);

mat2 outerProduct (vec2 c, vec2 r);
mat3 outerProduct (vec3 c, vec3 r);
mat4 outerProduct (vec4 c, vec4 r);
mat2x3 outerProduct (vec3 c, vec2 r);
mat3x2 outerProduct (vec2 c, vec3 r);
mat2x4 outerProduct (vec4 c, vec2 r);
mat4x2 outerProduct (vec2 c, vec4 r);
mat3x4 outerProduct (vec4 c, vec3 r);
mat4x3 outerProduct (vec3 c, vec4 r);
dmat2 outerProduct (dvec2 c, dvec2 r);
dmat3 outerProduct (dvec3 c, dvec3 r);
dmat4 outerProduct (dvec4 c, dvec4 r);
dmat2x3 outerProduct (dvec3 c, dvec2 r);
dmat3x2 outerProduct (dvec2 c, dvec3 r);
dmat2x4 outerProduct (dvec4 c, dvec2 r);
dmat4x2 outerProduct (dvec2 c, dvec4 r);
dmat3x4 outerProduct (dvec4 c, dvec3 r);
dmat4x3 outerProduct (dvec3 c, dvec4 r);


double packDouble2x32 (uvec2 v);
uint packHalf2x16 (vec2 v);
uint packUnorm2x16 (vec2 v);
uint packSnorm2x16 (vec2 v);
uint packUnorm4x8 (vec4 v);
uint packSnorm4x8 (vec4 v);

GENFUN2_ALL (pow);

GENFUN (radians);
GENFUND (radians);
GENFUN2 (reflect);
GENFUN2D (reflect);
vec2 refract (vec2 I, vec2 N, float eta); vec3 refract (vec3 I, vec3 N, float eta); vec4 refract (vec4 I, vec4 N, float eta);
dvec2 refract (dvec2 I, dvec2 N, float eta); dvec3 refract (dvec3 I, dvec3 N, float eta); dvec4 refract (dvec4 I, dvec4 N, float eta);

GENFUN (round);
GENFUND (round);
GENFUN (roundEven);
GENFUND (roundEven);

GENFUN_ALL (sign);
GENFUN (sin);
GENFUN (sinh);
GENFUN2 (smoothstep);
GENFUN (sqrt);
GENFUND (sqrt);

GENFUN2 (step);

GENFUN (tan);
GENFUN (tanh);

vec4 texelFetch (sampler1D sampler, int P, int lod);
vec4 texelFetch (sampler2D sampler, ivec2 P, int lod);
vec4 texelFetch (sampler3D sampler, ivec3 P, int lod);
vec4 texelFetch (sampler2DRect sampler, ivec2 P);
vec4 texelFetch (sampler1DArray sampler, ivec2 P, int lod);
vec4 texelFetch (sampler2DArray sampler, ivec3 P, int lod);
vec4 texelFetch (samplerBuffer sampler, int P);
vec4 texelFetch (samplerBuffer sampler, int P);

ivec4 texelFetch (isampler1D sampler, int P, int lod);
ivec4 texelFetch (isampler2D sampler, ivec2 P, int lod);
ivec4 texelFetch (isampler3D sampler, ivec3 P, int lod);
ivec4 texelFetch (isampler2DRect sampler, ivec2 P);
ivec4 texelFetch (isampler1DArray sampler, ivec2 P, int lod);
ivec4 texelFetch (isampler2DArray sampler, ivec3 P, int lod);
ivec4 texelFetch (isamplerBuffer sampler, int P);
ivec4 texelFetch (isamplerBuffer sampler, int P);

uvec4 texelFetch (usampler1D sampler, int P, int lod);
uvec4 texelFetch (usampler2D sampler, ivec2 P, int lod);
uvec4 texelFetch (usampler3D sampler, ivec3 P, int lod);
uvec4 texelFetch (usampler2DRect sampler, ivec2 P);
uvec4 texelFetch (usampler1DArray sampler, ivec2 P, int lod);
uvec4 texelFetch (usampler2DArray sampler, ivec3 P, int lod);
uvec4 texelFetch (usamplerBuffer sampler, int P);
uvec4 texelFetch (usamplerBuffer sampler, int P);


vec4 texelFetchOffset (sampler1D sampler, int P, int lod, int offset);
vec4 texelFetchOffset (sampler2D sampler, ivec2 P, int lod, int offset);
vec4 texelFetchOffset (sampler3D sampler, ivec3 P, int lod, int offset);
vec4 texelFetchOffset (sampler2DRect sampler, ivec2 P, int offset);
vec4 texelFetchOffset (sampler1DArray sampler, ivec2 P, int lod, int offset);
vec4 texelFetchOffset (sampler2DArray sampler, ivec3 P, int lod, int offset);

ivec4 texelFetchOffset (isampler1D sampler, int P, int lod, int offset);
ivec4 texelFetchOffset (isampler2D sampler, ivec2 P, int lod, int offset);
ivec4 texelFetchOffset (isampler3D sampler, ivec3 P, int lod, int offset);
ivec4 texelFetchOffset (isampler2DRect sampler, ivec2 P, int offset);
ivec4 texelFetchOffset (isampler1DArray sampler, ivec2 P, int lod, int offset);
ivec4 texelFetchOffset (isampler2DArray sampler, ivec3 P, int lod, int offset);

uvec4 texelFetchOffset (usampler1D sampler, int P, int lod, int offset);
uvec4 texelFetchOffset (usampler2D sampler, ivec2 P, int lod, int offset);
uvec4 texelFetchOffset (usampler3D sampler, ivec3 P, int lod, int offset);
uvec4 texelFetchOffset (usampler2DRect sampler, ivec2 P, int offset);
uvec4 texelFetchOffset (usampler1DArray sampler, ivec2 P, int lod, int offset);
uvec4 texelFetchOffset (usampler2DArray sampler, ivec3 P, int lod, int offset);




vec4 texture (sampler1D sampler, float P, float bias = 0);
vec4 texture (sampler2D sampler, vec2 P, float bias = 0);
vec4 texture (sampler3D sampler, vec3 P, float bias = 0);
vec4 texture (samplerCube sampler, vec3 P, float bias = 0);
float texture (sampler1DShadow sampler, vec3 P, float bias = 0);
float texture (sampler2DShadow sampler, vec3 P, float bias = 0);
float texture (samplerCubeShadow sampler, vec3 P, float bias = 0);
vec4 texture (sampler1DArray sampler, vec2 P, float bias = 0);
vec4 texture (sampler2DArray sampler, vec3 P, float bias = 0);
vec4 texture (samplerCubeArray sampler, vec4 P, float bias = 0);
float texture (sampler1DArrayShadow sampler, vec3 P, float bias = 0);
float texture (sampler2DArrayShadow sampler, vec4 P, float bias = 0);
vec4 texture (sampler2DRect sampler, vec2 P);
float texture (sampler2DRectShadow sampler, vec3 P);
float texture (samplerCubeArrayShadow sampler, vec4 P, float compare);

ivec4 texture (isampler1D sampler, float P, float bias = 0);
ivec4 texture (isampler2D sampler, vec2 P, float bias = 0);
ivec4 texture (isampler3D sampler, vec3 P, float bias = 0);
ivec4 texture (isamplerCube sampler, vec3 P, float bias = 0);
float texture (isampler1DShadow sampler, vec3 P, float bias = 0);
float texture (isampler2DShadow sampler, vec3 P, float bias = 0);
float texture (isamplerCubeShadow sampler, vec3 P, float bias = 0);
ivec4 texture (isampler1DArray sampler, vec2 P, float bias = 0);
ivec4 texture (isampler2DArray sampler, vec3 P, float bias = 0);
ivec4 texture (isamplerCubeArray sampler, vec4 P, float bias = 0);
float texture (isampler1DArrayShadow sampler, vec3 P, float bias = 0);
float texture (isampler2DArrayShadow sampler, vec4 P, float bias = 0);
ivec4 texture (isampler2DRect sampler, vec2 P);
float texture (isampler2DRectShadow sampler, vec3 P);
float texture (isamplerCubeArrayShadow sampler, vec4 P, float compare);

uvec4 texture (usampler1D sampler, float P, float bias = 0);
uvec4 texture (usampler2D sampler, vec2 P, float bias = 0);
uvec4 texture (usampler3D sampler, vec3 P, float bias = 0);
uvec4 texture (usamplerCube sampler, vec3 P, float bias = 0);
float texture (usampler1DShadow sampler, vec3 P, float bias = 0);
float texture (usampler2DShadow sampler, vec3 P, float bias = 0);
float texture (usamplerCubeShadow sampler, vec3 P, float bias = 0);
uvec4 texture (usampler1DArray sampler, vec2 P, float bias = 0);
uvec4 texture (usampler2DArray sampler, vec3 P, float bias = 0);
uvec4 texture (usamplerCubeArray sampler, vec4 P, float bias = 0);
float texture (usampler1DArrayShadow sampler, vec3 P, float bias = 0);
float texture (usampler2DArrayShadow sampler, vec4 P, float bias = 0);
uvec4 texture (usampler2DRect sampler, vec2 P);
float texture (usampler2DRectShadow sampler, vec3 P);
float texture (usamplerCubeArrayShadow sampler, vec4 P, float compare);


vec4 textureGather (sampler2D sampler, vec2 P, int comp = 0);
vec4 textureGather (sampler2DArray sampler, vec3 P, int comp = 0);
vec4 textureGather (samplerCube sampler, vec3 P, int comp = 0);
vec4 textureGather (samplerCubeArray sampler, vec4 P, int comp = 0);
vec4 textureGather (sampler2DRect sampler, vec3 P, int comp = 0);
vec4 textureGather (sampler2DShadow sampler, vec2 P, float refZ);
vec4 textureGather (sampler2DArrayShadow sampler, vec3 P, float refZ);
vec4 textureGather (samplerCubeShadow sampler, vec3 P, float refZ);
vec4 textureGather (samplerCubeArrayShadow sampler, vec4 P, float refZ);
vec4 textureGather (sampler2DRectShadow sampler, vec3 P, float refZ);

ivec4 textureGather (isampler2D sampler, vec2 P, int comp = 0);
ivec4 textureGather (isampler2DArray sampler, vec3 P, int comp = 0);
ivec4 textureGather (isamplerCube sampler, vec3 P, int comp = 0);
ivec4 textureGather (isamplerCubeArray sampler, vec4 P, int comp = 0);
ivec4 textureGather (isampler2DRect sampler, vec3 P, int comp = 0);
vec4 textureGather (isampler2DShadow sampler, vec2 P, float refZ);
vec4 textureGather (isampler2DArrayShadow sampler, vec3 P, float refZ);
vec4 textureGather (isamplerCubeShadow sampler, vec3 P, float refZ);
vec4 textureGather (isamplerCubeArrayShadow sampler, vec4 P, float refZ);
vec4 textureGather (isampler2DRectShadow sampler, vec3 P, float refZ);

uvec4 textureGather (usampler2D sampler, vec2 P, int comp = 0);
uvec4 textureGather (usampler2DArray sampler, vec3 P, int comp = 0);
uvec4 textureGather (usamplerCube sampler, vec3 P, int comp = 0);
uvec4 textureGather (usamplerCubeArray sampler, vec4 P, int comp = 0);
uvec4 textureGather (usampler2DRect sampler, vec3 P, int comp = 0);
vec4 textureGather (usampler2DShadow sampler, vec2 P, float refZ);
vec4 textureGather (usampler2DArrayShadow sampler, vec3 P, float refZ);
vec4 textureGather (usamplerCubeShadow sampler, vec3 P, float refZ);
vec4 textureGather (usamplerCubeArrayShadow sampler, vec4 P, float refZ);
vec4 textureGather (usampler2DRectShadow sampler, vec3 P, float refZ);


vec4 textureGatherOffset (sampler2D sampler, vec2 P, ivec2 offset, int comp = 0);
vec4 textureGatherOffset (sampler2DArray sampler, vec3 P, ivec2 offset, int comp = 0);
vec4 textureGatherOffset (sampler2DRect sampler, vec3 P, ivec2 offset, int comp = 0);
vec4 textureGatherOffset (sampler2DShadow sampler, vec2 P, float refZ, ivec2 offset);
vec4 textureGatherOffset (sampler2DArrayShadow sampler, vec3 P, float refZ, ivec2 offset);
vec4 textureGatherOffset (sampler2DRectShadow sampler, vec3 P, float refZ, ivec2 offset);

ivec4 textureGatherOffset (isampler2D sampler, vec2 P, ivec2 offset, int comp = 0);
ivec4 textureGatherOffset (isampler2DArray sampler, vec3 P, ivec2 offset, int comp = 0);
ivec4 textureGatherOffset (isampler2DRect sampler, vec3 P, ivec2 offset, int comp = 0);
vec4 textureGatherOffset (isampler2DShadow sampler, vec2 P, float refZ, ivec2 offset);
vec4 textureGatherOffset (isampler2DArrayShadow sampler, vec3 P, float refZ, ivec2 offset);
vec4 textureGatherOffset (isampler2DRectShadow sampler, vec3 P, float refZ, ivec2 offset);

uvec4 textureGatherOffset (usampler2D sampler, vec2 P, ivec2 offset, int comp = 0);
uvec4 textureGatherOffset (usampler2DArray sampler, vec3 P, ivec2 offset, int comp = 0);
uvec4 textureGatherOffset (usampler2DRect sampler, vec3 P, ivec2 offset, int comp = 0);
vec4 textureGatherOffset (usampler2DShadow sampler, vec2 P, float refZ, ivec2 offset);
vec4 textureGatherOffset (usampler2DArrayShadow sampler, vec3 P, float refZ, ivec2 offset);
vec4 textureGatherOffset (usampler2DRectShadow sampler, vec3 P, float refZ, ivec2 offset);


vec4 textureGatherOffset (sampler2D sampler, vec2 P, ivec2 offsets[4], int comp = 0);
vec4 textureGatherOffset (sampler2DArray sampler, vec3 P, ivec2 offsets[4], int comp = 0);
vec4 textureGatherOffset (sampler2DRect sampler, vec3 P, ivec2 offsets[4], int comp = 0);
vec4 textureGatherOffset (sampler2DShadow sampler, vec2 P, float refZ, ivec2 offsets[4]);
vec4 textureGatherOffset (sampler2DArrayShadow sampler, vec3 P, float refZ, ivec2 offsets[4]);
vec4 textureGatherOffset (sampler2DRectShadow sampler, vec3 P, float refZ, ivec2 offsets[4]);

ivec4 textureGatherOffset (isampler2D sampler, vec2 P, ivec2 offsets[4], int comp = 0);
ivec4 textureGatherOffset (isampler2DArray sampler, vec3 P, ivec2 offsets[4], int comp = 0);
ivec4 textureGatherOffset (isampler2DRect sampler, vec3 P, ivec2 offsets[4], int comp = 0);
vec4 textureGatherOffset (isampler2DShadow sampler, vec2 P, float refZ, ivec2 offsets[4]);
vec4 textureGatherOffset (isampler2DArrayShadow sampler, vec3 P, float refZ, ivec2 offsets[4]);
vec4 textureGatherOffset (isampler2DRectShadow sampler, vec3 P, float refZ, ivec2 offsets[4]);

uvec4 textureGatherOffset (usampler2D sampler, vec2 P, ivec2 offsets[4], int comp = 0);
uvec4 textureGatherOffset (usampler2DArray sampler, vec3 P, ivec2 offsets[4], int comp = 0);
uvec4 textureGatherOffset (usampler2DRect sampler, vec3 P, ivec2 offsets[4], int comp = 0);
vec4 textureGatherOffset (usampler2DShadow sampler, vec2 P, float refZ, ivec2 offsets[4]);
vec4 textureGatherOffset (usampler2DArrayShadow sampler, vec3 P, float refZ, ivec2 offsets[4]);
vec4 textureGatherOffset (usampler2DRectShadow sampler, vec3 P, float refZ, ivec2 offsets[4]);


vec4 textureGrad (sampler1D sampler, float P, float dPdx, float dPdy);
vec4 textureGrad (sampler2D sampler, vec2 P, vec2 dPdx, vec2 dPdy);
vec4 textureGrad (sampler3D sampler, vec3 P, vec3 dPdx, vec3 dPdy);
vec4 textureGrad (samplerCube sampler, vec3 P, vec3 dPdx, vec3 dPdy);
vec4 textureGrad (sampler2DRect sampler, vec2 P, vec2 dPdx, vec2 dPdy);
float textureGrad (sampler2DRectShadow sampler, vec2 P, vec2 dPdx, vec2 dPdy);
float textureGrad (sampler1DShadow sampler, vec3 P, float dPdx, float dPdy);
float textureGrad (sampler2DShadow sampler, vec3 P, vec2 dPdx, vec2 dPdy);
vec4 textureGrad (sampler1DArray sampler, vec2 P, float dPdx, float dPdy);
vec4 textureGrad (sampler2DArray sampler, vec3 P, vec2 dPdx, vec2 dPdy);
float textureGrad (sampler1DArrayShadow sampler, vec3 P, float dPdx, float dPdy);
vec4 textureGrad (samplerCubeArray sampler, vec4 P, vec3 dPdx, vec3 dPdy);

ivec4 textureGrad (isampler1D sampler, float P, float dPdx, float dPdy);
ivec4 textureGrad (isampler2D sampler, vec2 P, vec2 dPdx, vec2 dPdy);
ivec4 textureGrad (isampler3D sampler, vec3 P, vec3 dPdx, vec3 dPdy);
ivec4 textureGrad (isamplerCube sampler, vec3 P, vec3 dPdx, vec3 dPdy);
ivec4 textureGrad (isampler2DRect sampler, vec2 P, vec2 dPdx, vec2 dPdy);
ivec4 textureGrad (isampler1DArray sampler, vec2 P, float dPdx, float dPdy);
ivec4 textureGrad (isampler2DArray sampler, vec3 P, vec2 dPdx, vec2 dPdy);
ivec4 textureGrad (isamplerCubeArray sampler, vec4 P, vec3 dPdx, vec3 dPdy);

uvec4 textureGrad (usampler1D sampler, float P, float dPdx, float dPdy);
uvec4 textureGrad (usampler2D sampler, vec2 P, vec2 dPdx, vec2 dPdy);
uvec4 textureGrad (usampler3D sampler, vec3 P, vec3 dPdx, vec3 dPdy);
uvec4 textureGrad (usamplerCube sampler, vec3 P, vec3 dPdx, vec3 dPdy);
uvec4 textureGrad (usampler2DRect sampler, vec2 P, vec2 dPdx, vec2 dPdy);
uvec4 textureGrad (usampler1DArray sampler, vec2 P, float dPdx, float dPdy);
uvec4 textureGrad (usampler2DArray sampler, vec3 P, vec2 dPdx, vec2 dPdy);
uvec4 textureGrad (usamplerCubeArray sampler, vec4 P, vec3 dPdx, vec3 dPdy);


vec4 textureGradOffset (sampler1D sampler, float P, float dPdx, float dPdy, int offset);
vec4 textureGradOffset (sampler2D sampler, vec2 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
vec4 textureGradOffset (sampler3D sampler, vec3 P, vec3 dPdx, vec3 dPdy, ivec3 offset);
vec4 textureGradOffset (sampler2DRect sampler, vec2 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
float textureGradOffset (sampler2DRectShadow sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
float textureGradOffset (sampler1DShadow sampler, vec3 P, float dPdx, float dPdy, int offset);
float textureGradOffset (sampler2DShadow sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
vec4 textureGradOffset (sampler1DArray sampler, vec2 P, float dPdx, float dPdy, int offset);
vec4 textureGradOffset (sampler2DArray sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
float textureGradOffset (sampler1DArrayShadow sampler, vec3 P, float dPdx, float dPdy, int offset);
float textureGradOffset (sampler2DArrayShadow sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset);

ivec4 textureGradOffset (isampler1D sampler, float P, float dPdx, float dPdy, int offset);
ivec4 textureGradOffset (isampler2D sampler, vec2 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
ivec4 textureGradOffset (isampler3D sampler, vec3 P, vec3 dPdx, vec3 dPdy, ivec3 offset);
ivec4 textureGradOffset (isampler2DRect sampler, vec2 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
ivec4 textureGradOffset (isampler1DArray sampler, vec2 P, float dPdx, float dPdy, int offset);
ivec4 textureGradOffset (isampler2DArray sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset);

uvec4 textureGradOffset (usampler1D sampler, float P, float dPdx, float dPdy, int offset);
uvec4 textureGradOffset (usampler2D sampler, vec2 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
uvec4 textureGradOffset (usampler3D sampler, vec3 P, vec3 dPdx, vec3 dPdy, ivec3 offset);
uvec4 textureGradOffset (usampler2DRect sampler, vec2 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
uvec4 textureGradOffset (usampler1DArray sampler, vec2 P, float dPdx, float dPdy, int offset);
uvec4 textureGradOffset (usampler2DArray sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset);


vec4 textureLod (sampler1D sampler, float P, float lod);
vec4 textureLod (sampler2D sampler, vec2 P, float lod);
vec4 textureLod (sampler3D sampler, vec3 P, float lod);
vec4 textureLod (samplerCube sampler, vec3 P, float lod);
float textureLod (sampler1DShadow sampler, vec3 P, float lod);
float textureLod (sampler2DShadow sampler, vec4 P, float lod);
vec4 textureLod (sampler1DArray sampler, vec2 P, float lod);
vec4 textureLod (sampler2DArray sampler, vec3 P, float lod);
float textureLod (sampler1DArrayShadow sampler, vec3 P, float lod);
vec4 textureLod (samplerCubeArray sampler, vec4 P, float lod);

ivec4 textureLod (isampler1D sampler, float P, float lod);
ivec4 textureLod (isampler2D sampler, vec2 P, float lod);
ivec4 textureLod (isampler3D sampler, vec3 P, float lod);
ivec4 textureLod (isamplerCube sampler, vec3 P, float lod);
ivec4 textureLod (isampler1DArray sampler, vec2 P, float lod);
ivec4 textureLod (isampler2DArray sampler, vec3 P, float lod);
ivec4 textureLod (isamplerCubeArray sampler, vec4 P, float lod);

uvec4 textureLod (usampler1D sampler, float P, float lod);
uvec4 textureLod (usampler2D sampler, vec2 P, float lod);
uvec4 textureLod (usampler3D sampler, vec3 P, float lod);
uvec4 textureLod (usamplerCube sampler, vec3 P, float lod);
uvec4 textureLod (usampler1DArray sampler, vec2 P, float lod);
uvec4 textureLod (usampler2DArray sampler, vec3 P, float lod);
uvec4 textureLod (usamplerCubeArray sampler, vec4 P, float lod);


vec4 textureLodOffset (sampler1D sampler, float P, float lod, int offset);
vec4 textureLodOffset (sampler2D sampler, vec2 P, float lod, ivec2 offset);
vec4 textureLodOffset (sampler3D sampler, vec3 P, float lod, ivec3 offset);
float textureLodOffset (sampler1DShadow sampler, vec3 P, float lod, int offset);
float textureLodOffset (sampler2DShadow sampler, vec4 P, float lod, ivec2 offset);
vec4 textureLodOffset (sampler1DArray sampler, vec2 P, float lod, int offset);
vec4 textureLodOffset (sampler2DArray sampler, vec3 P, float lod, ivec2 offset);
float textureLodOffset (sampler1DArrayShadow sampler, vec3 P, float lod, int offset);

ivec4 textureLodOffset (isampler1D sampler, float P, float lod, int offset);
ivec4 textureLodOffset (isampler2D sampler, vec2 P, float lod, ivec2 offset);
ivec4 textureLodOffset (isampler3D sampler, vec3 P, float lod, ivec3 offset);
ivec4 textureLodOffset (isampler1DArray sampler, vec2 P, float lod, int offset);
ivec4 textureLodOffset (isampler2DArray sampler, vec3 P, float lod, ivec2 offset);

uvec4 textureLodOffset (usampler1D sampler, float P, float lod, int offset);
uvec4 textureLodOffset (usampler2D sampler, vec2 P, float lod, ivec2 offset);
uvec4 textureLodOffset (usampler3D sampler, vec3 P, float lod, ivec3 offset);
uvec4 textureLodOffset (usampler1DArray sampler, vec2 P, float lod, int offset);
uvec4 textureLodOffset (usampler2DArray sampler, vec3 P, float lod, ivec2 offset);


vec4 textureOffset (sampler1D sampler, float P, int offset, float bias = 0.0f);
vec4 textureOffset (sampler2D sampler, vec2 P, ivec2 offset, float bias = 0.0f);
vec4 textureOffset (sampler3D sampler, vec3 P, ivec3 offset, float bias = 0.0f);
vec4 textureOffset (sampler2DRect sampler, vec2 P, ivec2 offset);
float textureOffset (sampler2DRectShadow sampler, vec3 P, ivec2 offset);
float textureOffset (sampler1DShadow sampler, vec3 P, int offset, float bias = 0.0f);
float textureOffset (sampler2DShadow sampler, vec4 P, ivec2 offset, float bias = 0.0f);
vec4 textureOffset (sampler1DArray sampler, vec2 P, int offset, float bias = 0.0f);
vec4 textureOffset (sampler2DArray sampler, vec3 P, ivec2 offset, float bias = 0.0f);
float textureOffset (sampler1DArrayShadow sampler, vec3 P, int offset);
float textureOffset (sampler2DArrayShadow sampler, vec4 P, vec2 offset);

ivec4 textureOffset (isampler1D sampler, float P, int offset, float bias = 0.0f);
ivec4 textureOffset (isampler2D sampler, vec2 P, ivec2 offset, float bias = 0.0f);
ivec4 textureOffset (isampler3D sampler, vec3 P, ivec3 offset, float bias = 0.0f);
ivec4 textureOffset (isampler2DRect sampler, vec2 P, ivec2 offset);
ivec4 textureOffset (isampler1DArray sampler, vec2 P, int offset, float bias = 0.0f);
ivec4 textureOffset (isampler2DArray sampler, vec3 P, ivec2 offset, float bias = 0.0f);

uvec4 textureOffset (usampler1D sampler, float P, int offset, float bias = 0.0f);
uvec4 textureOffset (usampler2D sampler, vec2 P, ivec2 offset, float bias = 0.0f);
uvec4 textureOffset (usampler3D sampler, vec3 P, ivec3 offset, float bias = 0.0f);
uvec4 textureOffset (usampler2DRect sampler, vec2 P, ivec2 offset);
uvec4 textureOffset (usampler1DArray sampler, vec2 P, int offset, float bias = 0.0f);
uvec4 textureOffset (usampler2DArray sampler, vec3 P, ivec2 offset, float bias = 0.0f);


vec4 textureProj (sampler1D sampler, vec2 P, float bias = 0.0f);
vec4 textureProj (sampler1D sampler, vec4 P, float bias = 0.0f);
vec4 textureProj (sampler2D sampler, vec3 P, float bias = 0.0f);
vec4 textureProj (sampler2D sampler, vec4 P, float bias = 0.0f);
vec4 textureProj (sampler3D sampler, vec4 P, float bias = 0.0f);
float textureProj (sampler1DShadow sampler, vec4 P, float bias = 0.0f);
float textureProj (sampler2DShadow sampler, vec4 P, float bias = 0.0f);
vec4 textureProj (sampler2DRect sampler, vec3 P);
vec4 textureProj (sampler2DRect sampler, vec4 P);
float textreProj (sampler2DRectShadow sampler, vec4 P);

ivec4 textureProj (isampler1D sampler, vec2 P, float bias = 0.0f);
ivec4 textureProj (isampler1D sampler, vec4 P, float bias = 0.0f);
ivec4 textureProj (isampler2D sampler, vec3 P, float bias = 0.0f);
ivec4 textureProj (isampler2D sampler, vec4 P, float bias = 0.0f);
ivec4 textureProj (isampler3D sampler, vec4 P, float bias = 0.0f);
ivec4 textureProj (isampler2DRect sampler, vec3 P);
ivec4 textureProj (isampler2DRect sampler, vec4 P);

uvec4 textureProj (usampler1D sampler, vec2 P, float bias = 0.0f);
uvec4 textureProj (usampler1D sampler, vec4 P, float bias = 0.0f);
uvec4 textureProj (usampler2D sampler, vec3 P, float bias = 0.0f);
uvec4 textureProj (usampler2D sampler, vec4 P, float bias = 0.0f);
uvec4 textureProj (usampler3D sampler, vec4 P, float bias = 0.0f);
uvec4 textureProj (usampler2DRect sampler, vec3 P);
uvec4 textureProj (usampler2DRect sampler, vec4 P);


vec4 textureProjGrad (sampler1D sampler,	vec2 P,	float pDx,	float pDy);
vec4 textureProjGrad (sampler1D sampler,	vec4 P,	float pDx,	float pDy);
vec4 textureProjGrad (sampler2D sampler,	vec3 P,	vec2 pDx,	vec2 pDy);
vec4 textureProjGrad (sampler2D sampler,	vec4 P,	vec2 pDx,	vec2 pDy);
vec4 textureProjGrad (sampler3D sampler,	vec4 P,	vec3 pDx,	vec3 pDy);
float textureProjGrad (sampler1DShadow sampler,	vec4 P,	float pDx,	float pDy);
float textureProjGrad (sampler2DShadow sampler,vec4 P,	vec2 pDx,	vec2 pDy);
vec4 textureProjGrad (sampler2DRect sampler,	vec3 P,	vec2 pDx,	vec2 pDy);
vec4 textureProjGrad (sampler2DRect sampler,	vec4 P,	vec2 pDx,	vec2 pDy);
float textureProjGrad (sampler2DRectShadow sampler,	vec4 P,	vec2 pDx,	vec2 pDy);

ivec4 textureProjGrad (isampler1D sampler, vec2 P, float pDx, float pDy);
ivec4 textureProjGrad (isampler1D sampler, vec4 P, float pDx, float pDy);
ivec4 textureProjGrad (isampler2D sampler, vec3 P, vec2 pDx, vec2 pDy);
ivec4 textureProjGrad (isampler2D sampler, vec4 P, vec2 pDx, vec2 pDy);
ivec4 textureProjGrad (isampler3D sampler, vec4 P, vec3 pDx, vec3 pDy);
ivec4 textureProjGrad (isampler2DRect sampler, vec3 P, vec2 pDx, vec2 pDy);
ivec4 textureProjGrad (isampler2DRect sampler, vec4 P, vec2 pDx, vec2 pDy);

uvec4 textureProjGrad (usampler1D sampler, vec2 P, float pDx, float pDy);
uvec4 textureProjGrad (usampler1D sampler, vec4 P, float pDx, float pDy);
uvec4 textureProjGrad (usampler2D sampler, vec3 P, vec2 pDx, vec2 pDy);
uvec4 textureProjGrad (usampler2D sampler, vec4 P, vec2 pDx, vec2 pDy);
uvec4 textureProjGrad (usampler3D sampler, vec4 P, vec3 pDx, vec3 pDy);
uvec4 textureProjGrad (usampler2DRect sampler, vec3 P, vec2 pDx, vec2 pDy);
uvec4 textureProjGrad (usampler2DRect sampler, vec4 P, vec2 pDx, vec2 pDy);


vec4 textureProjGradOffset (sampler1D sampler,	vec2 P,	float dPdx,	float dPdy,	int offset);
vec4 textureProjGradOffset (sampler1D sampler,	vec4 P,	float dPdx,	float dPdy,	int offset);
vec4 textureProjGradOffset (sampler2D sampler,	vec3 P,	vec2 dPdx,	vec2 dPdy,	ivec2 offset);
vec4 textureProjGradOffset (sampler2D sampler,	vec4 P,	vec2 dPdx,vec2 dPdy,	ivec2 offset);
vec4 textureProjGradOffset (sampler3D sampler,	vec4 P,	vec3 dPdx,	vec3 dPdy,	ivec3 offset);
float textureProjGradOffset (sampler1DShadow sampler,	vec4 P,	float dPdx,	float dPdy,	int offset);
float textureProjGradOffset (sampler2DShadow sampler,	vec4 P,	vec2 dPdx,	vec2 dPdy,	ivec2 offset);
vec4 textureProjGradOffset (sampler2DRect sampler,	vec3 P,	vec2 dPdx,	vec2 dPdy,	ivec2 offset);
vec4 textureProjGradOffset (sampler2DRect sampler,	vec4 P,	vec2 dPdx,	vec2 dPdy,	ivec2 offset);
float textureProjGradOffset (sampler2DRectShadow sampler,	vec4 P,	vec2 dPdx,	vec2 dPdy,	ivec2 offset);

ivec4 textureProjGradOffset (isampler1D sampler, vec2 P, float dPdx, float dPdy, int offset);
ivec4 textureProjGradOffset (isampler1D sampler, vec4 P, float dPdx, float dPdy, int offset);
ivec4 textureProjGradOffset (isampler2D sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
ivec4 textureProjGradOffset (isampler2D sampler, vec4 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
ivec4 textureProjGradOffset (isampler3D sampler, vec4 P, vec3 dPdx, vec3 dPdy, ivec3 offset);
ivec4 textureProjGradOffset (isampler2DRect sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
ivec4 textureProjGradOffset (isampler2DRect sampler, vec4 P, vec2 dPdx, vec2 dPdy, ivec2 offset);

uvec4 textureProjGradOffset (usampler1D sampler, vec2 P, float dPdx, float dPdy, int offset);
uvec4 textureProjGradOffset (usampler1D sampler, vec4 P, float dPdx, float dPdy, int offset);
uvec4 textureProjGradOffset (usampler2D sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
uvec4 textureProjGradOffset (usampler2D sampler, vec4 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
uvec4 textureProjGradOffset (usampler3D sampler, vec4 P, vec3 dPdx, vec3 dPdy, ivec3 offset);
uvec4 textureProjGradOffset (usampler2DRect sampler, vec3 P, vec2 dPdx, vec2 dPdy, ivec2 offset);
uvec4 textureProjGradOffset (usampler2DRect sampler, vec4 P, vec2 dPdx, vec2 dPdy, ivec2 offset);


vec4 textureProjLod (sampler1D sampler,	vec2 P,	float lod);
vec4 textureProjLod (sampler1D sampler,	vec4 P,	float lod);
vec4 textureProjLod (sampler2D sampler,	vec3 P,	float lod);
vec4 textureProjLod (sampler2D sampler,	vec4 P,	float lod);
vec4 textureProjLod (sampler3D sampler,	vec4 P,	float lod);
float textureProjLod (sampler1DShadow sampler,	vec4 P,	float lod);
float textureProjLod (sampler2DShadow sampler,	vec4 P,	float lod);

ivec4 textureProjLod (isampler1D sampler, vec2 P, float lod);
ivec4 textureProjLod (isampler1D sampler, vec4 P, float lod);
ivec4 textureProjLod (isampler2D sampler, vec3 P, float lod);
ivec4 textureProjLod (isampler2D sampler, vec4 P, float lod);
ivec4 textureProjLod (isampler3D sampler, vec4 P, float lod);

uvec4 textureProjLod (usampler1D sampler, vec2 P, float lod);
uvec4 textureProjLod (usampler1D sampler, vec4 P, float lod);
uvec4 textureProjLod (usampler2D sampler, vec3 P, float lod);
uvec4 textureProjLod (usampler2D sampler, vec4 P, float lod);
uvec4 textureProjLod (usampler3D sampler, vec4 P, float lod);


vec4 textureProjLodOffset (sampler1D sampler,	vec2 P,	float lod,	int offset);
vec4 textureProjLodOffset (sampler1D sampler,	vec4 P,	float lod,	int offset);
vec4 textureProjLodOffset (sampler2D sampler,	vec3 P,	float lod,	ivec2 offset);
vec4 textureProjLodOffset (sampler2D sampler,	vec4 P,	float lod,	ivec2 offset);
vec4 textureProjLodOffset (sampler3D sampler,	vec4 P,	float lod,	ivec3 offset);
float textureProjLodOffset (sampler1DShadow sampler,	vec4 P,	float lod,	int offset);
float textureProjLodOffset (sampler2DShadow sampler,	vec4 P,	float lod,	ivec2 offset);

ivec4 textureProjLodOffset (isampler1D sampler, vec2 P, float lod, int offset);
ivec4 textureProjLodOffset (isampler1D sampler, vec4 P, float lod, int offset);
ivec4 textureProjLodOffset (isampler2D sampler, vec3 P, float lod, ivec2 offset);
ivec4 textureProjLodOffset (isampler2D sampler, vec4 P, float lod, ivec2 offset);
ivec4 textureProjLodOffset (isampler3D sampler, vec4 P, float lod, ivec3 offset);

uvec4 textureProjLodOffset (usampler1D sampler, vec2 P, float lod, int offset);
uvec4 textureProjLodOffset (usampler1D sampler, vec4 P, float lod, int offset);
uvec4 textureProjLodOffset (usampler2D sampler, vec3 P, float lod, ivec2 offset);
uvec4 textureProjLodOffset (usampler2D sampler, vec4 P, float lod, ivec2 offset);
uvec4 textureProjLodOffset (usampler3D sampler, vec4 P, float lod, ivec3 offset);


vec4 textureProjOffset (sampler1D sampler,	vec2 P,	int offset,	float bias = 0.0f);
vec4 textureProjOffset (sampler1D sampler,	vec4 P,	int offset,	float bias = 0.0f);
vec4 textureProjOffset (sampler2D sampler,	vec3 P,	ivec2 offset,	float bias = 0.0f);
vec4 textureProjOffset (sampler2D sampler,	vec4 P,	ivec2 offset,	float bias = 0.0f);
vec4 textureProjOffset (sampler3D sampler,	vec4 P,	ivec3 offset,	float bias = 0.0f);
float textureProjOffset (sampler1DShadow sampler,	vec4 P,	int offset,	float bias = 0.0f);
float textureProjOffset (sampler2DShadow sampler,	vec4 P,	ivec2 offset,	float bias = 0.0f);
vec4 textureProjOffset (sampler2DRect sampler,	vec3 P,	ivec2 offset);
vec4 textureProjOffset (sampler2DRect sampler,	vec4 P,	ivec2 offset);
float textureProjOffset (sampler2DRectShadow sampler,	vec4 P,	ivec2 offset);

ivec4 textureProjOffset (isampler1D sampler, vec2 P, int offset, float bias = 0.0f);
ivec4 textureProjOffset (isampler1D sampler, vec4 P, int offset, float bias = 0.0f);
ivec4 textureProjOffset (isampler2D sampler, vec3 P, ivec2 offset, float bias = 0.0f);
ivec4 textureProjOffset (isampler2D sampler, vec4 P, ivec2 offset, float bias = 0.0f);
ivec4 textureProjOffset (isampler3D sampler, vec4 P, ivec3 offset, float bias = 0.0f);
ivec4 textureProjOffset (isampler2DRect sampler, vec3 P, ivec2 offset);
ivec4 textureProjOffset (isampler2DRect sampler, vec4 P, ivec2 offset);

uvec4 textureProjOffset (usampler1D sampler, vec2 P, int offset, float bias = 0.0f);
uvec4 textureProjOffset (usampler1D sampler, vec4 P, int offset, float bias = 0.0f);
uvec4 textureProjOffset (usampler2D sampler, vec3 P, ivec2 offset, float bias = 0.0f);
uvec4 textureProjOffset (usampler2D sampler, vec4 P, ivec2 offset, float bias = 0.0f);
uvec4 textureProjOffset (usampler3D sampler, vec4 P, ivec3 offset, float bias = 0.0f);
uvec4 textureProjOffset (usampler2DRect sampler, vec3 P, ivec2 offset);
uvec4 textureProjOffset (usampler2DRect sampler, vec4 P, ivec2 offset);


int textureQueryLevels (sampler1D sampler);
int textureQueryLevels (sampler2D sampler);
int textureQueryLevels (sampler3D sampler);
int textureQueryLevels (samplerCube sampler);
int textureQueryLevels (sampler1DArray sampler);
int textureQueryLevels (sampler2DArray sampler);
int textureQueryLevels (samplerCubeArray sampler);
int textureQueryLevels (sampler1DShadow sampler);
int textureQueryLevels (sampler2DShadow sampler);
int textureQueryLevels (samplerCubeShadow sampler);
int textureQueryLevels (sampler1DArrayShadow sampler);
int textureQueryLevels (sampler2DArrayShadow sampler);
int textureQueryLevels (samplerCubeArrayShadow sampler);

int textureQueryLevels (isampler1D sampler);
int textureQueryLevels (isampler2D sampler);
int textureQueryLevels (isampler3D sampler);
int textureQueryLevels (isamplerCube sampler);
int textureQueryLevels (isampler1DArray sampler);
int textureQueryLevels (isampler2DArray sampler);
int textureQueryLevels (isamplerCubeArray sampler);
int textureQueryLevels (isampler1DShadow sampler);
int textureQueryLevels (isampler2DShadow sampler);
int textureQueryLevels (isamplerCubeShadow sampler);
int textureQueryLevels (isampler1DArrayShadow sampler);
int textureQueryLevels (isampler2DArrayShadow sampler);
int textureQueryLevels (isamplerCubeArrayShadow sampler);

int textureQueryLevels (usampler1D sampler);
int textureQueryLevels (usampler2D sampler);
int textureQueryLevels (usampler3D sampler);
int textureQueryLevels (usamplerCube sampler);
int textureQueryLevels (usampler1DArray sampler);
int textureQueryLevels (usampler2DArray sampler);
int textureQueryLevels (usamplerCubeArray sampler);
int textureQueryLevels (usampler1DShadow sampler);
int textureQueryLevels (usampler2DShadow sampler);
int textureQueryLevels (usamplerCubeShadow sampler);
int textureQueryLevels (usampler1DArrayShadow sampler);
int textureQueryLevels (usampler2DArrayShadow sampler);
int textureQueryLevels (usamplerCubeArrayShadow sampler);


vec2 textureQueryLod (sampler1D sampler,	float P);
vec2 textureQueryLod (sampler2D sampler,	vec2 P);
vec2 textureQueryLod (sampler3D sampler,	vec3 P);
vec2 textureQueryLod (samplerCube sampler,	vec3 P);
vec2 textureQueryLod (sampler1DArray sampler,	float P);
vec2 textureQueryLod (sampler2DArray sampler,	vec2 P);
vec2 textureQueryLod (samplerCubeArray sampler,	vec3 P);
vec2 textureQueryLod (sampler1DShadow sampler,	float P);
vec2 textureQueryLod (sampler2DShadow sampler,	vec2 P);
vec2 textureQueryLod (samplerCubeShadow sampler,	vec3 P);
vec2 textureQueryLod (sampler1DArrayShadow sampler,	float P);
vec2 textureQueryLod (sampler2DArrayShadow sampler,	vec2 P);
vec2 textureQueryLod (samplerCubeArrayShadow sampler,	vec3 P);

vec2 textureQueryLod (isampler1D sampler, float P);
vec2 textureQueryLod (isampler2D sampler, vec2 P);
vec2 textureQueryLod (isampler3D sampler, vec3 P);
vec2 textureQueryLod (isamplerCube sampler, vec3 P);
vec2 textureQueryLod (isampler1DArray sampler, float P);
vec2 textureQueryLod (isampler2DArray sampler, vec2 P);
vec2 textureQueryLod (isamplerCubeArray sampler, vec3 P);
vec2 textureQueryLod (isampler1DShadow sampler, float P);
vec2 textureQueryLod (isampler2DShadow sampler, vec2 P);
vec2 textureQueryLod (isamplerCubeShadow sampler, vec3 P);
vec2 textureQueryLod (isampler1DArrayShadow sampler, float P);
vec2 textureQueryLod (isampler2DArrayShadow sampler, vec2 P);
vec2 textureQueryLod (isamplerCubeArrayShadow sampler, vec3 P);

vec2 textureQueryLod (usampler1D sampler, float P);
vec2 textureQueryLod (usampler2D sampler, vec2 P);
vec2 textureQueryLod (usampler3D sampler, vec3 P);
vec2 textureQueryLod (usamplerCube sampler, vec3 P);
vec2 textureQueryLod (usampler1DArray sampler, float P);
vec2 textureQueryLod (usampler2DArray sampler, vec2 P);
vec2 textureQueryLod (usamplerCubeArray sampler, vec3 P);
vec2 textureQueryLod (usampler1DShadow sampler, float P);
vec2 textureQueryLod (usampler2DShadow sampler, vec2 P);
vec2 textureQueryLod (usamplerCubeShadow sampler, vec3 P);
vec2 textureQueryLod (usampler1DArrayShadow sampler, float P);
vec2 textureQueryLod (usampler2DArrayShadow sampler, vec2 P);
vec2 textureQueryLod (usamplerCubeArrayShadow sampler, vec3 P);


int textureSize (sampler1D sampler,	int lod);
ivec2 textureSize (sampler2D sampler,	int lod);
ivec3 textureSize (sampler3D sampler,	int lod);
ivec2 textureSize (samplerCube sampler,	int lod);
int textureSize (sampler1DShadow sampler,	int lod);
ivec2 textureSize (sampler2DShadow sampler,	int lod);
ivec2 textureSize (samplerCubeShadow sampler,	int lod);
ivec3 textureSize (samplerCubeArray sampler,	int lod);
ivec3 textureSize (samplerCubeArrayShadow sampler,	int lod);
ivec2 textureSize (samplerRect sampler);
ivec2 textureSize (samplerRectShadow sampler);
ivec2 textureSize (sampler1DArray sampler,	int lod);
ivec3 textureSize (sampler2DArray sampler,	int lod);
ivec2 textureSize (sampler1DArrayShadow sampler,	int lod);
ivec3 textureSize (sampler2DArrayShadow sampler,	int lod);
int textureSize (samplerBuffer sampler);
ivec2 textureSize (sampler2DMS sampler);
ivec3 textureSize (sampler2DMSArray sampler);

int textureSize (isampler1D sampler, int lod);
ivec2 textureSize (isampler2D sampler, int lod);
ivec3 textureSize (isampler3D sampler, int lod);
ivec2 textureSize (isamplerCube sampler, int lod);
int textureSize (isampler1DShadow sampler, int lod);
ivec2 textureSize (isampler2DShadow sampler, int lod);
ivec2 textureSize (isamplerCubeShadow sampler, int lod);
ivec3 textureSize (isamplerCubeArray sampler, int lod);
ivec3 textureSize (isamplerCubeArrayShadow sampler, int lod);
ivec2 textureSize (isamplerRect sampler);
ivec2 textureSize (isamplerRectShadow sampler);
ivec2 textureSize (isampler1DArray sampler, int lod);
ivec3 textureSize (isampler2DArray sampler, int lod);
ivec2 textureSize (isampler1DArrayShadow sampler, int lod);
ivec3 textureSize (isampler2DArrayShadow sampler, int lod);
int textureSize (isamplerBuffer sampler);
ivec2 textureSize (isampler2DMS sampler);
ivec3 textureSize (isampler2DMSArray sampler);

int textureSize (usampler1D sampler, int lod);
ivec2 textureSize (usampler2D sampler, int lod);
ivec3 textureSize (usampler3D sampler, int lod);
ivec3 textureSize (usampler3D sampler, int lod = 0);
ivec3 textureSize (sampler3D sampler, int lod = 0);
ivec2 textureSize (usamplerCube sampler, int lod);
int textureSize (usampler1DShadow sampler, int lod);
ivec2 textureSize (usampler2DShadow sampler, int lod);
ivec2 textureSize (usamplerCubeShadow sampler, int lod);
ivec3 textureSize (usamplerCubeArray sampler, int lod);
ivec3 textureSize (usamplerCubeArrayShadow sampler, int lod);
ivec2 textureSize (usamplerRect sampler);
ivec2 textureSize (usamplerRectShadow sampler);
ivec2 textureSize (usampler1DArray sampler, int lod);
ivec3 textureSize (usampler2DArray sampler, int lod);
ivec2 textureSize (usampler1DArrayShadow sampler, int lod);
ivec3 textureSize (usampler2DArrayShadow sampler, int lod);
int textureSize (usamplerBuffer sampler);
ivec2 textureSize (usampler2DMS sampler);
ivec3 textureSize (usampler2DMSArray sampler);



mat2 transpose (mat2 m);
mat3 transpose (mat3 m);
mat4 transpose (mat4 m);
mat2x3 transpose (mat3x2 m);
mat2x4 transpose (mat4x2 m);
mat3x2 transpose (mat2x3 m);
mat3x4 transpose (mat4x3 m);
mat4x2 transpose (mat2x4 m);
mat4x3 transpose (mat3x4 m);
dmat2 transpose (dmat2 m);
dmat3 transpose (dmat3 m);
dmat4 transpose (dmat4 m);
dmat2x3 transpose (dmat3x2 m);
dmat2x4 transpose (dmat4x2 m);
dmat3x2 transpose (dmat2x3 m);
dmat3x4 transpose (dmat4x3 m);
dmat4x2 transpose (dmat2x4 m);
dmat4x3 transpose (dmat3x4 m);

GENFUN (trunc);
GENFUND (trunc);



// ******************************************************* //
// **************** Build in attributes ****************** //

uvec3 gl_NumWorkGroups;
uvec3 gl_WorkGroupSize;
uvec3 gl_WorkGroupID;
uvec3 gl_LocalInvocationID;
uvec3 gl_GlobalInvocationID;
uint  gl_LocalInvocationIndex;


in int gl_VertexID;
in int gl_InstanceID;

vec4 gl_Position;
float gl_PointSize;
float gl_ClipDistance[];


int gl_PrimitiveIDIn;
int gl_InvocationID;

struct glin{int length(){};};
glin gl_in;

int gl_Layer;
int gl_ViewportIndex;

float gl_TessLevelOuter[4];
float gl_TessLevelInner[2];

int gl_PatchVerticesIn;
vec3 gl_TessCoord;


vec4 gl_FragCoord;
bool gl_FrontFacing;
vec2 gl_PointCoord;
int gl_SampleID;
vec2 gl_SamplePosition;
int gl_SampleMaskIn[];
float gl_FragDepth;
int gl_SampleMask[];


const ivec3 gl_MaxComputeWorkGroupCount = { 65535, 65535, 65535 };
const ivec3 gl_MaxComputeWorkGroupSize = { 1024, 1024, 64 };
const int gl_MaxComputeUniformComponents = 1024;
const int gl_MaxComputeTextureImageUnits = 16;
const int gl_MaxComputeImageUniforms = 8;
const int gl_MaxComputeAtomicCounters = 8;
const int gl_MaxComputeAtomicCounterBuffers = 1;
const int gl_MaxVertexAttribs = 16;
const int gl_MaxVertexUniformComponents = 1024;
const int gl_MaxVaryingComponents = 60;
const int gl_MaxVertexOutputComponents = 64;
const int gl_MaxGeometryInputComponents = 64;
const int gl_MaxGeometryOutputComponents = 128;
const int gl_MaxFragmentInputComponents = 128;
const int gl_MaxVertexTextureImageUnits = 16;
const int gl_MaxCombinedTextureImageUnits = 80;
const int gl_MaxTextureImageUnits = 16;
const int gl_MaxImageUnits = 8;
const int gl_MaxCombinedImageUnitsAndFragmentOutputs = 8;
const int gl_MaxImageSamples = 0;
const int gl_MaxVertexImageUniforms = 0;
const int gl_MaxTessControlImageUniforms = 0;
const int gl_MaxTessEvaluationImageUniforms = 0;
const int gl_MaxGeometryImageUniforms = 0;
const int gl_MaxFragmentImageUniforms = 8;
const int gl_MaxCombinedImageUniforms = 8;
const int gl_MaxFragmentUniformComponents = 1024;
const int gl_MaxDrawBuffers = 8;
const int gl_MaxClipDistances = 8;
const int gl_MaxGeometryTextureImageUnits = 16;
const int gl_MaxGeometryOutputVertices = 256;
const int gl_MaxGeometryTotalOutputComponents = 1024;
const int gl_MaxGeometryUniformComponents = 1024;
const int gl_MaxGeometryVaryingComponents = 64;
const int gl_MaxTessControlInputComponents = 128;
const int gl_MaxTessControlOutputComponents = 128;
const int gl_MaxTessControlTextureImageUnits = 16;
const int gl_MaxTessControlUniformComponents = 1024;
const int gl_MaxTessControlTotalOutputComponents = 4096;
const int gl_MaxTessEvaluationInputComponents = 128;
const int gl_MaxTessEvaluationOutputComponents = 128;
const int gl_MaxTessEvaluationTextureImageUnits = 16;
const int gl_MaxTessEvaluationUniformComponents = 1024;
const int gl_MaxTessPatchComponents = 120;
const int gl_MaxPatchVertices = 32;
const int gl_MaxTessGenLevel = 64;
const int gl_MaxViewports = 16;
const int gl_MaxVertexUniformVectors = 256;
const int gl_MaxFragmentUniformVectors = 256;
const int gl_MaxVaryingVectors = 15;
const int gl_MaxVertexAtomicCounters = 0;
const int gl_MaxTessControlAtomicCounters = 0;
const int gl_MaxTessEvaluationAtomicCounters = 0;
const int gl_MaxGeometryAtomicCounters = 0;
const int gl_MaxFragmentAtomicCounters = 8;
const int gl_MaxCombinedAtomicCounters = 8;
const int gl_MaxAtomicCounterBindings = 1;
const int gl_MaxVertexAtomicCounterBuffers = 0;
const int gl_MaxTessControlAtomicCounterBuffers = 0;
const int gl_MaxTessEvaluationAtomicCounterBuffers = 0;
const int gl_MaxGeometryAtomicCounterBuffers = 0;
const int gl_MaxFragmentAtomicCounterBuffers = 1;
const int gl_MaxCombinedAtomicCounterBuffers = 1;
const int gl_MaxAtomicCounterBufferSize = 16384;
const int gl_MinProgramTexelOffset = -8;
const int gl_MaxProgramTexelOffset = 7;


#endif
