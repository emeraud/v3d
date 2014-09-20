#include "KDTree.hpp"

#include <algorithm>

// KDTree

KDTree::KDTree(Tessellation3D* tessellation) : _tessellation(tessellation), _root(0x0) {

}

KDTree::~KDTree() {
  delete _root;
}

void KDTree::build() {
  _root = new Node(_tessellation->getVerticesView(), 0);
}


// Node

Node::Node(const std::vector<const Vertex*>& points, const int depth) : _lNode(0x0), _rNode(0x0) {
  build(points, depth);
}

Node::~Node() {
  delete _lNode;
  delete _rNode;
}

// FIXME: check number of points...
void Node::build(const std::vector<const Vertex*>& points, const int depth) {
  if (points.size() <= 10) {
    _points.push_back(points[0]); // FIXME find a smarter stop condition
    return;
  }


  // get the split dimension
  int splitDimension = getSplitDimension(points, depth);

  // median computation
  std::vector<float> v;
  for (std::vector<const Vertex*>::const_iterator it=points.begin(); it != points.end(); ++it) {
    v.push_back((*it)->pos[splitDimension]);
  }
  std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
  float median = v[v.size()/2];

  // vertices repartition
  std::vector<const Vertex*> lVertices;
  std::vector<const Vertex*> rVertices;
  for (std::vector<const Vertex*>::const_iterator it=points.begin(); it != points.end(); ++it) {
    if ((*it)->pos[splitDimension] > median) {
      lVertices.push_back(*it);
    } else {
      rVertices.push_back(*it);
    }
  }

  // if no selection has been perform, just register vertices and stop (TODO FIXME: switch direction instead)
  if (lVertices.size() == 0 || rVertices.size() == 0) {
    for (std::vector<const Vertex*>::const_iterator it=points.begin(); it != points.end(); ++it) {
      _points.push_back(*it);
    }
    return;
  }

  _lNode = new Node(lVertices, depth+1);
  lVertices.resize(0);
  _rNode = new Node(rVertices, depth+1);
}

int Node::getSplitDimension(const std::vector<const Vertex*>& points, const int depth) {
  return depth % 3; // FIXME largest bounding box dimension would be better
}
