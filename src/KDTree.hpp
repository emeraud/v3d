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
    Node(const std::vector<const Vertex*>& points, const BoundingBox& fatherBox, const int depth);
    ~Node();

  public:
    std::vector<const Vertex*> getVertices() const;

  private:
    void getIntersectedChildren(const Ray& ray, std::vector<IntersectedNode>& nodes, const int depth) const;

  private:
    void build(const std::vector<const Vertex*>& points, const int depth);
    int getSplitDimension(const std::vector<const Vertex*>& points, const int depth);

  private:
    Node*                        _lNode;
    Node*                        _rNode;
    std::vector<const Vertex*>   _points;
    BoundingBox                  _bbox;
};

#endif
