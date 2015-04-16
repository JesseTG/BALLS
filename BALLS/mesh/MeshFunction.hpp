#ifndef MESHFUNCTION_HPP
#define MESHFUNCTION_HPP

#include <functional>

#include "mesh/MeshParameter.hpp"

namespace balls {
namespace mesh {


const QString HEIGHT = "height";
const QString INNER_RADIUS = "inner-radius";
const QString LENGTH = "length";
const QString OUTER_RADIUS = "outer-radius";
const QString RADIUS = "radius";
const QString RESOLUTION = "resolution";
const QString SUBDIVISIONS = "subdivisions";
const QString U_SAMPLES = "u-samples";
const QString V_SAMPLES = "v-samples";
const QString WIDTH = "width";
const QString X_SCALE = "x-scale";
const QString Y_SCALE = "y-scale";
const QString Z_SCALE = "z-scale";

class Mesh;
class MeshParameter;
class MeshGenerator;

using std::function;

typedef function<Mesh(const MeshParameters&)> MeshFunction;

namespace functions {
/**
 * @brief Returns an empty mesh (i.e. no vertices).
 */
extern MeshFunction empty;

/**
 * @brief Returns a quad
 * @param length The length of the quad
 * @param width The width of the quad
 * @param resolution The number of squares (i.e. pairs of triangles) to split
 * this plane into (must be at least 1)
 */
extern MeshFunction quad;

/**
 * @brief Returns a box
 * @param 0, 1, 2 The length, width, and height of the box
 * @param 3 The number of squares (i.e. pairs of triangles) to split each face
 * into (must be at least 1)
 * @param 4 Unused
 */
extern MeshFunction box;

/**
 * @brief Returns a pyramid
 * @param 0 The number of sides in the base (must be at least 3)
 * @param 1 The radius of the base
 * @param 2 The height of the pyramid
 * @param 3, 4 Unused
 */
extern MeshFunction pyramid;

/**
 * @brief Returns a tetrahedron
 */
extern MeshFunction tetrahedron;

extern MeshFunction octahedron;

extern MeshFunction icosahedron;

/**
 * @brief Returns an ellipsoid
 * @param x-scale x-axis scale factor
 * @param y-scale y-axis scale factor
 * @param z-scale z-axis scale factor
 * @param u-samples
 * @param v-samples
 */
extern MeshFunction ellipsoid;

/**
 * @brief Returns a cylinder
 * @param radius The radius of the cylinder
 * @param height The height of the cylinder
 * @param resolution The resolution of the cylinder's base (must be at least 3)
 */
extern MeshFunction cylinder;

/**
 * @brief Returns a cone mesh
 * @param radius The radius of the cone
 * @param height The height of the cone
 * @param resolution The resolution of the cone's base (must be at least 3)
 */
extern MeshFunction cone;

/**
 * @brief sphere Returns a sphere mesh.
 * @brief radius radius
 */
extern MeshFunction uvsphere;

/**
 * @brief Returns a torus
 * @param inner-radius Minor radius
 * @param outer-radius Major radius
 * @param u-samples
 * @param v-samples
 */
extern MeshFunction torus;
}
}
}

#endif // MESHFUNCTION_HPP
