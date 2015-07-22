#ifndef GENERATORS_HPP
#define GENERATORS_HPP

namespace balls {
namespace mesh {

class MeshGenerator;

namespace generators {

extern MeshGenerator quad;
extern MeshGenerator box;
extern MeshGenerator tetrahedron;
extern MeshGenerator icosahedron;
extern MeshGenerator sphere80;
extern MeshGenerator sphere320;
extern MeshGenerator icosphere;
extern MeshGenerator cylinder;
extern MeshGenerator cone;
extern MeshGenerator uvsphere;
extern MeshGenerator ellipsoid;
extern MeshGenerator torus;
}
}
}
#endif // GENERATORS_HPP
