#include "precompiled.hpp"
#include "mesh/Generators.hpp"

#include "mesh/MeshGenerator.hpp"

namespace balls {
namespace mesh {
namespace generators {

MeshGenerator quad(MeshGenerator::tr("Quad"),  functions::quad,
{
  {LENGTH, {2.0f, 0, 10}},
  {WIDTH, {2.0f, 0, 10}}
});

MeshGenerator box(MeshGenerator::tr("Box"), functions::box,
{
  {LENGTH, {1.0f, 0, 10}},
  {WIDTH, {1.0f, 0, 10}},
  {HEIGHT, {1.0f, 0, 10}}
});

MeshGenerator icosahedron(MeshGenerator::tr("Icosahedron"), functions::icosahedron,
{
  {RADIUS, {1.0f, 0, 10}},
  {SUBDIVISIONS, {0, 0, 10}}
});

MeshGenerator sphere80(MeshGenerator::tr("Sphere (80-triangle)"), functions::icosahedron,
{
  {RADIUS, {1.0f, 0, 10}},
  {SUBDIVISIONS, {1, 0, 10}}
});

MeshGenerator sphere320(MeshGenerator::tr("Sphere (320-triangle)"), functions::icosahedron,
{
  {RADIUS, {1.0f, 0, 10}},
  {SUBDIVISIONS, {2, 0, 10}}
});

MeshGenerator icosphere(MeshGenerator::tr("Icosphere"), functions::icosahedron,
{
  {RADIUS, {1.0f, 0, 10}},
  {SUBDIVISIONS, {5, 0, 10}}
});

MeshGenerator tetrahedron(MeshGenerator::tr("Tetrahedron"), functions::tetrahedron,
{
  {LENGTH, {1.0f, 0, 10}}
});

MeshGenerator cylinder(MeshGenerator::tr("Cylinder"), functions::cylinder,
{
  {RADIUS, {0.5f, 0, 10}},
  {HEIGHT, {2.0f, 0, 10}},
  {RESOLUTION, {64, 3, 512}}
});

MeshGenerator cone(MeshGenerator::tr("Cone"), functions::cone,
{
  {RADIUS, {1.0f, 0, 10}},
  {HEIGHT, {3.0f, 0, 10}},
  {RESOLUTION, {64, 3, 512}}
});

MeshGenerator uvsphere(MeshGenerator::tr("UV Sphere"), functions::uvsphere,
{
  {X_SCALE, {1.0f, 0, 10}},
  {Y_SCALE, {1.0f, 0, 10}},
  {Z_SCALE, {1.0f, 0, 10}},
  {U_SAMPLES, {128, 3, 512}},
  {V_SAMPLES, {128, 3, 512}}
});

MeshGenerator ellipsoid(MeshGenerator::tr("Ellipsoid"), functions::uvsphere,
{
  {X_SCALE, {1.5f, 0, 10}},
  {Y_SCALE, {2.0f, 0, 10}},
  {Z_SCALE, {0.5f, 0, 10}},
  {U_SAMPLES, {128, 3, 512}},
  {V_SAMPLES, {128, 3, 512}}
});

MeshGenerator torus(MeshGenerator::tr("Torus"), functions::torus,
{
  {OUTER_RADIUS, {1.0f, 0, 10}},
  {INNER_RADIUS, {.5f, 0, 10}},
  {U_SAMPLES, {128, 3, 512}},
  {V_SAMPLES, {128, 3, 512}}
});

}
}
}
