#include "mathfunctions.h"

float mathfunc::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
        float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
        float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
        float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
        float l3 = 1.0f - l1 - l2;
        return l1 * p1.y + l2 * p2.y + l3 * p3.y;
    }

bool mathfunc::getLowestRoot(float a, float b, float c, float maxR, float* root)
{
    // Check if a solution exists
    float determinant = b*b - 4.0f*a*c;
    // If determinant is negative it means no solutions.
    if (determinant < 0.0f) return false;
    // calculate the two roots: (if determinant == 0 then
    // x1==x2 but let’s disregard that slight optimization)
    float sqrtD = sqrtf(determinant);
    float r1 = (-b - sqrtD) / (2*a);
    float r2 = (-b + sqrtD) / (2*a);
    // Sort so x1 <= x2
    if (r1 > r2) {
        float temp = r2;
        r2 = r1;
        r1 = temp;
    }
    // Get lowest root:
    if (r1 > 0 && r1 < maxR) {
        *root = r1;
        return true;
    }
    // It is possible that we want x2 - this can happen
    // if x1 < 0
    if (r2 > 0 && r2 < maxR) {
        *root = r2;
        return true;
    }
    // No (valid) solutions
    return false;
}

typedef unsigned int uint32;
#define in(a) ((uint32&) a)

bool mathfunc::checkPointInTriangle(const glm::vec3& point,
const glm::vec3& pa,const glm::vec3& pb, const glm::vec3& pc)
{
    glm::vec3 e10=pb-pa;
    glm::vec3 e20=pc-pa;
    float a = glm::dot(e10, e10);
    float b = glm::dot(e10, e20);
    float c = glm::dot(e20, e20);

    float ac_bb=(a*c)-(b*b);

    glm::vec3 vp(point.x-pa.x, point.y-pa.y, point.z-pa.z);

    float d = glm::dot(vp, e10);
    float e = glm::dot(vp, e20);

    float x = (d*c)-(e*b);
    float y = (e*a)-(d*b);
    float z = x+y-ac_bb;

    return (( in(z)& ~(in(x)|in(y)) ) & 0x80000000);
}

float mathfunc::Polynomial(float X, float a, float b, float c, float d)
{
    return a + b*X + c*X*X + d*(X*X*X);
}


float mathfunc::Polynomial(float X, float a, float b, float c, float d, float e, float f)
{
    return a + b*X + c*powf(X,2) + d*powf(X,3) + e * powf(X,4) + f * powf(X,5);
}

float mathfunc::expProp(float X, float y0, float v0, float k)
{
    return y0 - (v0/k)*(1 - expf( -k*X ));
}
