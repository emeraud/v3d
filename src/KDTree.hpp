#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>

#include "BoundingBox.hpp"
#include "Tessellation3D.hpp"
#include "Ray.hpp"

class Node;

struct IntersectedNode {
  const Node* node;
  float sqDist;

  IntersectedNode(const Node* iNode, float iSqDist) : node(iNode), sqDist(iSqDist) { }
};

struct IntersectedNodeSorter {
  inline bool operator() (const IntersectedNode& node1, const IntersectedNode& node2) {
    return (node1.sqDist < node2.sqDist);
  }
};

class KDTree {
  public:
    KDTree(Tessellation3D* tessellation);
    ~KDTree();

  public:
    std::vector<IntersectedNode> getSortedIntersectedLeaves(const Ray& ray) const;

  private:
    void build();

  private:
    Tessellation3D*         _tessellation;
    Node*                   _root;
    
};

class Node {
  friend class KDTree;

  public:
    Node(const Tessellation3D* tessellation, const std::vector<const Triangle*>& triangles, const BoundingBox& fatherBox, const int depth);
    ~Node();

  public:
    std::vector<const Triangle*> getTriangles() const;

  private:
    void getIntersectedChildren(const Ray& ray, std::vector<IntersectedNode>& nodes, const int depth) const;

  private:
    void build(const Tessellation3D* tessellation, const std::vector<const Triangle*>& triangles, const int depth);
    int getSplitDimension(const std::vector<const Triangle*>& triangles, const int depth);

  private:
    Node*                            _lNode;
    Node*                            _rNode;
    std::vector<const Triangle*>     _triangles;
    BoundingBox                      _bbox;
};

#endif

