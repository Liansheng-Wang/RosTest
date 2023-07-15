
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <execution>

struct Point3D {
  double x;
  double y;
  double z;

  Point3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
};

struct KDNode {
  Point3D point;
  KDNode* left;
  KDNode* right;

  KDNode(const Point3D& _point) : point(_point), left(nullptr), right(nullptr) {}
};

class KDTree {
public:
  void build(const std::vector<Point3D>& points) {
    if (points.empty())
      return;
    
    std::vector<Point3D> sortedPoints(points.begin(), points.end());
    root = buildRecursive(sortedPoints, 0, sortedPoints.size() - 1, 0);
  }

  Point3D findNearestNeighbor(const Point3D& query) const {
    return findNearestNeighborRecursive(root, query, root->point, 0);
  }

private:
  KDNode* root;

  KDNode* buildRecursive(std::vector<Point3D>& points, int start, int end, int depth) {
    if (start > end)
      return nullptr;

    int medianIndex = start + (end - start) / 2;
    int axis = depth % 3;

    std::nth_element(points.begin() + start, points.begin() + medianIndex, points.begin() + end + 1,
    [axis](const Point3D& p1, const Point3D& p2) {
      if (axis == 0)
        return p1.x < p2.x;
      else if (axis == 1)
        return p1.y < p2.y;
      else
        return p1.z < p2.z;
    });

    KDNode* node = new KDNode(points[medianIndex]);
    node->left = buildRecursive(points, start, medianIndex - 1, depth + 1);
    node->right = buildRecursive(points, medianIndex + 1, end, depth + 1);

    return node;
  }

  double distance(const Point3D& p1, const Point3D& p2) const {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }

  Point3D findNearestNeighborRecursive(const KDNode* node, const Point3D& query, const Point3D& best, int depth) const {
    if (node == nullptr)
      return best;

    Point3D closest = best;
    double bestDist = distance(query, best);
    double nodeDist = distance(query, node->point);

    if (nodeDist < bestDist) {
      closest = node->point;
      bestDist = nodeDist;
    }

    int axis = depth % 3;

    if ((axis == 0 && query.x < node->point.x) || (axis == 1 && query.y < node->point.y) || (axis == 2 && query.z < node->point.z)) {
      closest = findNearestNeighborRecursive(node->left, query, closest, depth + 1);
      if (axis == 0 && query.x + bestDist >= node->point.x)
          closest = findNearestNeighborRecursive(node->right, query, closest, depth + 1);
    }
    else {
      closest = findNearestNeighborRecursive(node->right, query, closest, depth + 1);
      if (axis == 0 && query.x - bestDist <= node->point.x)
          closest = findNearestNeighborRecursive(node->left, query, closest, depth + 1);
    }

    return closest;
  }
};


int main() {
  std::vector<Point3D> points = {
      {1.0, 2.0, 3.0},
      {4.0, 5.0, 6.0},
      {7.0, 8.0, 9.0},
      // Add more points as needed
  };

  KDTree tree;
  tree.build(points);

  Point3D query(2.5, 4.5, 6.5);
  Point3D nearestNeighbor = tree.findNearestNeighbor(query);

  std::cout << "Nearest Neighbor: (" << nearestNeighbor.x << ", " << nearestNeighbor.y << ", " << nearestNeighbor.z << ")" << std::endl;

  return 0;
}
