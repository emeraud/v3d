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

Node::Node(const Tessellation3D* tessellation, const std::vector<const Triangle*>& triangles, const BoundingBox& bbox, const int depth) :
_lNode(0x0), _rNode(0x0), _bbox(bbox) {
  build(tessellation, triangles, depth);
}

Node::~Node() {
  delete _lNode;
  delete _rNode;
}

void Node::build(const Tessellation3D* tessellation, const std::vector<const Triangle*>& triangles, const int depth) {
  if (triangles.size() <= 4 || depth > 15) { // TODO find a smarter stop condition and expose params
    for (std::vector<const Triangle*>::const_iterator it = triangles.begin(); it != triangles.end(); ++it) {
     _triangles.push_back((*it));
    }
    return;
  }

  // get the split dimension
  int splitDimension = getSplitDimension(triangles, depth);

  // median computation
  std::vector<float> v;
  for (std::vector<const Triangle*>::const_iterator tIt = triangles.begin(); tIt != triangles.end(); ++tIt) {
    v.push_back(tessellation->getVertex((*tIt)->getVertex(0))->pos[splitDimension]);
    v.push_back(tessellation->getVertex((*tIt)->getVertex(1))->pos[splitDimension]);
    v.push_back(tessellation->getVertex((*tIt)->getVertex(2))->pos[splitDimension]);
  }
  std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
  float median = v[v.size()/2];
  if (median >= _bbox.getMax()[splitDimension] || median <= _bbox.getMin()[splitDimension]) {
    median = 0.5f * (_bbox.getMin()[splitDimension] + _bbox.getMax()[splitDimension]);
  }

  // vertices repartition
  std::vector<const Triangle*> lTriangles;
  std::vector<const Triangle*> rTriangles;
  bool addToLeft, addToRight;
  for (std::vector<const Triangle*>::const_iterator tIt = triangles.begin(); tIt != triangles.end(); ++tIt) {
    addToLeft = false;
    addToRight = false;
    for (unsigned int i=0; i<3; i++) {
      if (tessellation->getVertex((*tIt)->getVertex(i))->pos[splitDimension] < median) {
        addToLeft = true;
      } else {
        addToRight = true;
      }
    }

    if (addToLeft) {
      lTriangles.push_back(*tIt);
    }
    if (addToRight) {
      rTriangles.push_back(*tIt);
    }
  }

  // if no selection has been performed, just register vertices and stop (TODO FIXME: switch direction instead)
  if (lTriangles.size() <= 2 || rTriangles.size() <= 2 ||
        lTriangles.size() == triangles.size() || rTriangles.size() == triangles.size()) {
    for (std::vector<const Triangle*>::const_iterator it = triangles.begin(); it != triangles.end(); ++it) {
      _triangles.push_back(*it);
    }
    return;
  }

  BoundingBox lBox = _bbox;
  lBox.subdivide<true>(splitDimension, median);
  //std::cout << "Lvl" << depth << " BBOX=" << lbox[0] << " " << lbox[1] << " " << lbox[2] << std::endl;
  _lNode = new Node(tessellation, lTriangles, lBox, depth+1);

  lTriangles.resize(0);
  BoundingBox rBox = _bbox;
  rBox.subdivide<false>(splitDimension, median);
  //std::cout << "Lvl" << depth << " BBOX=" << rbox[0] << " " << rbox[1] << " " << rbox[2] << std::endl;
  _rNode = new Node(tessellation, rTriangles, rBox, depth+1);
}

int Node::getSplitDimension(const std::vector<const Triangle*>& points, const int depth) {
  return depth % 3; // FIXME largest bounding box dimension would be better
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

std::vector<const Triangle*> Node::getTriangles() const {
  return _triangles;
}

