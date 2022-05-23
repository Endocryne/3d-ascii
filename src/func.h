#pragma once

#include <cmath>
#include "vector2.h"
#include "vector3.h"

float clamp(float value, float min, float max) { return fmax(fmin(value, max), min); }
float dot(vector3 const& a, vector3 const& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
double sign(double a) { return (0 < a) - (a < 0); }
double step(double edge, double x) { return x > edge; }

float length(vector2 const& v) {return sqrt(v.x * v.x + v.y * v.y);}
float length(vector3 const& v) {return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);}

vector3 abs(vector3 const& v) { return vector3(fabs(v.x), fabs(v.y), fabs(v.z)); }
vector3 sign(vector3 const& v) { return vector3(sign(v.x), sign(v.y), sign(v.z)); }
vector3 step(vector3 const& edge, vector3 v) { return vector3(step(edge.x, v.x), step(edge.y, v.y), step(edge.z, v.z)); }
vector3 reflect(vector3 rd, vector3 n) { return rd - n * (2 * dot(n, rd)); }

vector3 norm(vector3 v) {return v / length(v);}
vector2 sphere(vector3 ro, vector3 rd, float r) {
    float b = dot(ro, rd);
    float c = dot(ro, ro) - r * r;
    float h = b * b - c;
    if (h < 0.0) return vector2(-1.0);
    h = sqrt(h);
    return vector2(-b - h, -b + h);
}
vector2 box(vector3 ro, vector3 rd, vector3 boxSize, vector3& outNormal) {
    vector3 m = vector3(1.0) / rd;
    vector3 n = m * ro;
    vector3 k = abs(m) * boxSize;
    vector3 t1 = -n - k;
    vector3 t2 = -n + k;
    float tN = fmax(fmax(t1.x, t1.y), t1.z);
    float tF = fmin(fmin(t2.x, t2.y), t2.z);
    if (tN > tF || tF < 0.0) return vector2(-1.0);
    vector3 yzx = vector3(t1.y, t1.z, t1.x);
    vector3 zxy = vector3(t1.z, t1.x, t1.y);
    outNormal = -sign(rd) * step(yzx, t1) * step(zxy, t1);
    return vector2(tN, tF);
}
float plane(vector3 ro, vector3 rd, vector3 p, float w) {
    return -(dot(ro, p) + w) / dot(rd, p);
}

vector3 rotateX(vector3 a, double angle)
{
    vector3 b = a;
    b.z = a.z * cos(angle) - a.y * sin(angle);
    b.y = a.z * sin(angle) + a.y * cos(angle);
    return b;
}

vector3 rotateY(vector3 a, double angle)
{
    vector3 b = a;
    b.x = a.x * cos(angle) - a.z * sin(angle);
    b.z = a.x * sin(angle) + a.z * cos(angle);
    return b;
}

vector3 rotateZ(vector3 a, double angle)
{
    vector3 b = a;
    b.x = a.x * cos(angle) - a.y * sin(angle);
    b.y = a.x * sin(angle) + a.y * cos(angle);
    return b;
}

float getDist(vector3 p, float t){
    vector2 q = vector2(length(vector2(p.x, p.y)) - 1.0, p.z);
    return length(q) - 0.5;
}