#ifndef MATHFUNCTIONS_H
#define MATHFUNCTIONS_H

#include <glm.h>

namespace mathfunc {

    float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

    bool getLowestRoot(float a, float b, float c, float maxR, float* root);

    bool checkPointInTriangle(const glm::vec3& point,const glm::vec3& pa,const glm::vec3& pb, const glm::vec3& pc);

    float Polynomial(float X, float a, float b, float c, float d);
    float Polynomial(float X, float a, float b, float c, float d, float e, float f);
    float expProp(float X, float y0, float v0, float k);


}


#endif // MATHFUNCTIONS_H
