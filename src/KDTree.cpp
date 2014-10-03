#include "KDTree.hpp"

#include <algorithm>

// KDTree

KDTree::KDTree(Tessellation3D* tessellation) : _tessellation(tessellation), _root(0x0) {
  build();
}

KDTree::~KDTree() {
  delete _root;
}

void KDTree::build() {
  std::vector<const Vertex*> verticesView = _tessellation->getVerticesView();
  BoundingBox bbox;
  for (std::vector<const Vertex*>::const_iterator it = verticesView.begin(); it != verticesView.end(); ++it) {
    bbox.extendTo((*it)->pos);
  }

  _root = new Node(_tessellation, _tessellation->getTrianglesView(), bbox, 0);
  std::cout << "KDTree built" << std::endl;
}

std::vector<IntersectedNode> KDTree::getSortedIntersectedLeaves(const Ray& ray) const {
  std::vector<IntersectedNode> nodes;
  _root->getIntersectedChildren(ray, nodes, 0);
  std::sort(nodes.begin(), nodes.end(), IntersectedNodeSorter());
  return nodes;
}

// Node

Node::Node(const Tessellation3D* tessellation, const std::vector<UInt>& triangles, const BoundingBox& bbox, const int depth) :
_lNode(0x0), _rNode(0x0), _bbox(bbox) {
  build(tessellation, triangles, depth);
}

Node::~Node() {
  delete _lNode;
  delete _rNode;
}

void Node::build(const Tessellation3D* tessellation, const std::vector<UInt>& triangles, const int depth) {
  if (triangles.size() <= 4 || depth > 15) { // TODO find a smarter stop condition and expose params
    addAllTriangles(triangles);
    return;
  }

  // get the split dimension
  UInt splitDimension = getSplitDimension(triangles, depth);
  bool splitSuccess = false;
  float median;
  std::vector<UInt> lTriangles;
  std::vector<UInt> rTriangles;

  for (UInt k=0; k<3; k++) {
    splitDimension = (splitDimension + k) % 3;
    median = computeMedian(tessellation, triangles, splitDimension);

    if (splitTriangles(tessellation, triangles, splitDimension, median, lTriangles, rTriangles)) {
      splitSuccess = true;
      break;
    }
    lTriangles.clear();
    rTriangles.clear();
  }

  if (!splitSuccess) {
    addAllTriangles(triangles); 
    return;
  }

  // left child node
  BoundingBox lBox = _bbox;
  lBox.subdivide<true>(splitDimension, median);
  _lNode = new Node(tessellation, lTriangles, lBox, depth+1);
  lTriangles.resize(0);

  // right child node
  BoundingBox rBox = _bbox;
  rBox.subdivide<false>(splitDimension, median);
  _rNode = new Node(tessellation, rTriangles, rBox, depth+1);
}

UInt Node::getSplitDimension(const std::vector<UInt>& triangles, const int depth) const {
  float dim[3] = { _bbox.getWidth(), _bbox.getHeight(), _bbox.getLength() };

  if (dim[0] > dim[1]) {
    if (dim[0] > dim[2]) {
      return 0;
    } else {
      return 2;
    }
  } else {
    if (dim[1] > dim[2]) {
      return 1;
    } else {
      return 2;
    }
  }
}

bool Node::splitTriangles(const Tessellation3D* tessellation, const std::vector<UInt>& triangles,
                          UInt splitDimension, float median,
                          std::vector<UInt>& lTriangles, std::vector<UInt>& rTriangles) const {
  bool addToLeft, addToRight;
  const Triangle* triangle = 0x0;
  UInt nbIntersections = 0;
  for (UInt i=0; i<triangles.size(); i++) {
    addToLeft = false;
    addToRight = false;
    triangle = tessellation->getTriangle(triangles[i]);
    for (UInt j=0; j<3; j++) {
      if (tessellation->getVertex(triangle->getVertex(j))->pos[splitDimension] < median) {
        addToLeft = true;
      } else {
        addToRight = true;
      }
    }

    if (addToLeft && addToRight) {
      nbIntersections++;
    }

    if (addToLeft) {
      lTriangles.push_back(triangles[i]);
    }
    if (addToRight) {
      rTriangles.push_back(triangles[i]);
    }
  }

  // if no selection has been performed, just register vertices and stop (TODO FIXME: switch direction instead)
  if (lTriangles.size() <= 2 || rTriangles.size() <= 2 ||
        lTriangles.size() == triangles.size() || rTriangles.size() == triangles.size() ||
        nbIntersections*2 > triangles.size()) {
    return false;
  }
  return true;
}

void Node::getIntersectedChildren(const Ray& ray, std::vector<IntersectedNode>& nodes, const int depth) const {
  Vec3Df intersectionPoint;
  if (ray.intersect(_bbox, intersectionPoint)) {
    if (_triangles.size() > 0) {
      nodes.push_back(IntersectedNode(this, Vec3Df::squaredDistance(ray.getOrigin(), intersectionPoint)));
    } else {
      if (_lNode != 0x0) {
        _lNode->getIntersectedChildren(ray, nodes, depth+1);
      }
      if (_rNode != 0x0) {
        _rNode->getIntersectedChildren(ray, nodes, depth+1);
      }
    }
  }
}

float Node::computeMedian(const Tessellation3D* tessellation, const std::vector<UInt>& triangles, UInt splitDimension) const {
  // median computation
  std::vector<float> v;
  for (UInt i=0; i<triangles.size(); i++) {
    TriangleVertices triangleVertices = tessellation->getTriangleVertices(triangles[i]);
    v.push_back(triangleVertices.v0->pos[splitDimension]);
    v.push_back(triangleVertices.v1->pos[splitDimension]);
    v.push_back(triangleVertices.v2->pos[splitDimension]);
  }
  std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
  float median = v[v.size()/2];
  if (median >= _bbox.getMax()[splitDimension] || median <= _bbox.getMin()[splitDimension]) {
    median = 0.5f * (_bbox.getMin()[splitDimension] + _bbox.getMax()[splitDimension]);
  }
  return median;
}

const std::vector<UInt>& Node::getTriangles() const {
  return _triangles;
}

void Node::addAllTriangles(const std::vector<UInt>& triangles) {
  for (UInt i=0; i<triangles.size(); i++) {
   _triangles.push_back(triangles[i]);
  }
}

