#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>

#include "Tessellation3D.hpp"

class Node;

class KDTree {
  public:
    KDTree(Tessellation3D* tessellation);
    ~KDTree();

  public:
    void build();

  private:
    Tessellation3D*         _tessellation;
    Node*                   _root;
    
};

class Node {
  public:
    Node(const std::vector<const Vertex*>& points, const int depth);
    ~Node();

  private:
    void build(const std::vector<const Vertex*>& points, const int depth);
    int getSplitDimension(const std::vector<const Vertex*>& points, const int depth);

  private:
    Node*                        _lNode;
    Node*                        _rNode;
    std::vector<const Vertex*>   _points;
};

#endif
