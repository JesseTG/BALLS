#include "precompiled.hpp"
#include "mesh/Generators.hpp"

#include "mesh/MeshGenerator.hpp"

namespace balls {
namespace mesh {

namespace generators {
MeshGenerator quad("Quad",
                    functions::quad,
                    {{LENGTH, {2.0f, 0.0f, 10.0f}}, {WIDTH, {2.0f, 0.0f, 10.0f}}});

MeshGenerator box("Box",
                  functions::box,
                  {{LENGTH, {1.0f, 0.0f, 10.0f}},
                   {WIDTH, {1.0f, 0.0f, 10.0f}},
                   {HEIGHT, {1.0f, 0.0f, 10.0f}}});


MeshGenerator
 icosahedron("Icosahedron",
             functions::icosahedron,
             {{RADIUS, {1.0f, 0.0f, 10.0f}}, {SUBDIVISIONS, {0, 0, 10}}});

MeshGenerator sphere80("Sphere (80-triangle)",
                       functions::icosahedron,
                       {{RADIUS, {1.0f, 0.0f, 10.0f}}, {SUBDIVISIONS, {1, 0, 10}}});

MeshGenerator sphere320("Sphere (320-triangle)",
                        functions::icosahedron,
                        {{RADIUS, {1.0f, 0.0f, 10.0f}}, {SUBDIVISIONS, {2, 0, 10}}});

MeshGenerator icosphere("Icosphere",
                        functions::icosahedron,
                        {{RADIUS, {1.0f, 0.0f, 10.0f}}, {SUBDIVISIONS, {5, 0, 10}}});

MeshGenerator
 tetrahedron("Tetrahedron", functions::tetrahedron, {{LENGTH, {1.0f, 0.0f, 10.0f}}});

MeshGenerator cylinder("Cylinder",
                       functions::cylinder,
                       {{RADIUS, {0.5f, 0.0f, 10.0f}},
                        {HEIGHT, {2.0f, 0.0f, 10.0f}},
                        {RESOLUTION, {64, 3, 512}}});

MeshGenerator cone("Cone",
                   functions::cone,
                   {{RADIUS, {1.0f, 0.0f, 10.0f}},
                    {HEIGHT, {3.0f, 0.0f, 10.0f}},
                    {RESOLUTION, {64, 3, 512}}});

MeshGenerator uvsphere("UV Sphere",
                       functions::uvsphere,
                       {{X_SCALE, {1.0f, 0.0f, 10.0f}},
                        {Y_SCALE, {1.0f, 0.0f, 10.0f}},
                        {Z_SCALE, {1.0f, 0.0f, 10.0f}},
                        {U_SAMPLES, {128, 3, 512}},
                        {V_SAMPLES, {128, 3, 512}}});

MeshGenerator ellipsoid("Ellipsoid",
                        functions::uvsphere,
                        {{X_SCALE, {1.5f, 0.0f, 10.0f}},
                         {Y_SCALE, {2.0f, 0.0f, 10.0f}},
                         {Z_SCALE, {0.5f, 0.0f, 10.0f}},
                         {U_SAMPLES, {128, 3, 512}},
                         {V_SAMPLES, {128, 3, 512}}});

MeshGenerator torus("Torus",
                    functions::torus,
                    {{OUTER_RADIUS, {1.0f, 0.0f, 10.0f}},
                     {INNER_RADIUS, {.5f, 0.0f, 10.0f}},
                     {U_SAMPLES, {128, 3, 512}},
                     {V_SAMPLES, {128, 3, 512}}});
}
}
}
