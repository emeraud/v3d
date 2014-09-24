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

  _root = new Node(_tessellation->getVerticesView(), bbox, 0);
  std::cout << "KDTree built" << std::endl;
}

std::vector<IntersectedNode> KDTree::getSortedIntersectedLeaves(const Ray& ray) const {
  std::vector<IntersectedNode> nodes;
  _root->getIntersectedChildren(ray, nodes, 0);
  std::sort(nodes.begin(), nodes.end(), IntersectedNodeSorter());
  return nodes;
}

// Node

Node::Node(const std::vector<const Vertex*>& points, const BoundingBox& bbox, const int depth) : _lNode(0x0), _rNode(0x0), _bbox(bbox) {
  build(points, depth);
}

Node::~Node() {
  delete _lNode;
  delete _rNode;
}

// FIXME: check number of points...
void Node::build(const std::vector<const Vertex*>& points, const int depth) {
  if (points.size() <= 10) { // find a smarter stop condition
    for (std::vector<const Vertex*>::const_iterator it = points.begin(); it != points.end(); ++it) {
     _points.push_back((*it));
    }
    return;
  }

  // get the split dimension
  int splitDimension = getSplitDimension(points, depth);

  // median computation
  std::vector<float> v;
  for (std::vector<const Vertex*>::const_iterator it = points.begin(); it != points.end(); ++it) {
    v.push_back((*it)->pos[splitDimension]);
  }
  std::nth_element(v.begin(), v.begin() + v.size()/2, v.end());
  float median = v[v.size()/2];

  // vertices repartition
  std::vector<const Vertex*> lVertices;
  std::vector<const Vertex*> rVertices;
  for (std::vector<const Vertex*>::const_iterator it = points.begin(); it != points.end(); ++it) {
    if ((*it)->pos[splitDimension] < median) {
      lVertices.push_back(*it);
    } else {
      rVertices.push_back(*it);
    }
  }

  // if no selection has been perform, just register vertices and stop (TODO FIXME: switch direction instead)
  if (lVertices.size() == 0 || rVertices.size() == 0) {
    for (std::vector<const Vertex*>::const_iterator it = points.begin(); it != points.end(); ++it) {
      _points.push_back(*it);
    }
    return;
  }

  BoundingBox lBox = _bbox;
  lBox.subdivide<true>(splitDimension, median);
  //std::cout << "Lvl" << depth << " BBOX=" << lbox[0] << " " << lbox[1] << " " << lbox[2] << std::endl;
  _lNode = new Node(lVertices, lBox, depth+1);

  lVertices.resize(0);
  BoundingBox rBox = _bbox;
  rBox.subdivide<false>(splitDimension, median);
  //std::cout << "Lvl" << depth << " BBOX=" << rbox[0] << " " << rbox[1] << " " << rbox[2] << std::endl;
  _rNode = new Node(rVertices, rBox, depth+1);
}

int Node::getSplitDimension(const std::vector<const Vertex*>& points, const int depth) {
  return depth % 3; // FIXME largest bounding box dimension would be better
}

void Node::getIntersectedChildren(const Ray& ray, std::vector<IntersectedNode>& nodes, const int depth) const {
  Vec3Df intersectionPoint;
  if (ray.intersect(_bbox, intersectionPoint)) {
    if (_points.size() > 0) {
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

std::vector<const Vertex*> Node::getVertices() const {
  return _points;
}

