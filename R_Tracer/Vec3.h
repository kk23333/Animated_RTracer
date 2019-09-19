//
// Created by KK on 16/9/15.
//

#ifndef RTRACER_Vec3_H
#define RTRACER_Vec3_H

typedef double Vec2d[2];
typedef double Vec3d[3];
typedef double Vec4d[4];
#include <math.h>
#include <stdlib.h>
#include <iostream>
#define  EPSILON1 1e-8

#define ALMOST_ZERO(x) ((x)>-EPSILON1 && (x)<EPSILON1)


class Vec3 {
public:
    Vec3(){}
    Vec3(double e0, double e1, double e2){ e[0] = e0; e[1] = e1; e[2] = e2;}
    Vec3(const Vec3& A){ this->e[0] = A.e[0];  this->e[1] = A.e[1];  this->e[2] = A.e[2];}


   inline bool isAlmostSame(const Vec3 & a, const Vec3 & b);
    inline double x() const{ return e[0];}
    inline double y() const{ return e[1];}
    inline double z() const{ return e[2];}
    inline double r() const{ return e[0];}
    inline double g() const{ return e[1];}
    inline double b() const{ return e[2];}

    inline const Vec3& operator+() const { return *this;}
    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    inline double operator[](int i) const { return e[i];};
    inline double& operator[](int i) { return e[i];};

    inline Vec3& operator+=(const Vec3 &v2);
    inline Vec3& operator-=(const Vec3 &v2);
    inline Vec3& operator*=(const Vec3 &v2);
    inline Vec3& operator/=(const Vec3 &v2);
    inline Vec3& operator*=(const double t);
    inline Vec3& operator/=(const double t);
    inline bool operator==(const Vec3 &v);
    inline bool operator < (const Vec3 &v);
    inline bool operator!=(const Vec3 &v);

    inline double length() const{
        return sqrt(e[0]*e[0] +e[1]*e[1] + e[2]*e[2]);
    }
    inline double squared_length() const{
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
    inline void make_unit_Vector();

    double e[3];
};

inline std::istream& operator>>(std::istream &is, Vec3 &t){
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Vec3 &t){
    os << t.e[0] << " " << t.e[1] << " " << t.e[2];
    return os;
}

inline void Vec3::make_unit_Vector() {
    double k =1.0 / sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2){
    return Vec3(v1.e[0] + v2.e[0],v1.e[1] + v2.e[1],v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2){
    return Vec3(v1.e[0] - v2.e[0],v1.e[1] - v2.e[1],v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2){
    return Vec3(v1.e[0] * v2.e[0],v1.e[1] * v2.e[1],v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2){
    return Vec3(v1.e[0] / v2.e[0],v1.e[1] / v2.e[1],v1.e[2] / v2.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v){
    return Vec3(t*v.e[0],t*v.e[1],t*v.e[2]);
}

inline Vec3 operator*( const Vec3 &v,double t){
    return Vec3(t*v.e[0],t*v.e[1],t*v.e[2]);
}

inline Vec3 operator/( Vec3 v, double t){
    return Vec3(v.e[0]/t,v.e[1]/t,v.e[2]/t);
}



inline double dot(const Vec3 &v1, const Vec3 &v2){
    return v1.e[0]*v2.e[0]+v1.e[1]*v2.e[1]+v1.e[2]*v2.e[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2){
    return Vec3((v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),(-(v1.e[0]*v2.e[2]-v1.e[2]*v2.e[0])),(v1.e[0]*v2.e[1]-v1.e[1]*v2.e[0]));
}

inline Vec3& Vec3::operator+=(const Vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3 &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3 &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline  Vec3& Vec3::operator-=(const Vec3 &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline bool Vec3::operator == (const Vec3 &v) {
    return (this->e[0]==v[0]&&this->e[1]==v[1]&&this->e[2]==v[2]);
}

inline bool Vec3::operator < (const Vec3 &v) {
    return (this->e[0]<v[0]&&this->e[1]<v[1]&&this->e[2]<v[2]);
}

inline bool Vec3::operator != (const Vec3 &v) {
    return (this->e[0]!=v[0]||this->e[1]!=v[1]||this->e[2]!=v[2]);
}

inline Vec3& Vec3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline Vec3& Vec3::operator/=(const double t) {
    double k = 1.0/t;

    e[0] *=k;
    e[1] *=k;
    e[2] *=k;
    return *this;
}

inline Vec3 unit_Vector(Vec3 v){
    if(v.length()!=0){
        return v/v.length();
    } else
        return v;
}


inline bool isAlmostSame(const Vec3 & a, const Vec3 & b){
    if(ALMOST_ZERO(a.x()-b.x()) && ALMOST_ZERO(a.y()-b.y()) && ALMOST_ZERO(a.z()-b.z()))
        return true;
    return false;
}

inline bool isAlmostSamed(const double & a, const double & b){
    if(ALMOST_ZERO(a-b) && ALMOST_ZERO(a-b) && ALMOST_ZERO(a-b))
        return true;
    return false;
}

#endif //RTRACER_Vec3_H
