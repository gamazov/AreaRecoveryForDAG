#include <iostream>
#include <vector>

struct Edge {
  size_t id = 0;

  size_t head = 0;
  size_t tail = 0;

  float af = 0;
};

struct Node {
  size_t id = 0;

  std::vector<size_t> succ = {};
  std::vector<size_t> pred = {};

  std::vector<size_t> oedge = {};
  std::vector<size_t> iedge = {};

  float af = 0;
  bool afFixed = false;
};

void initPred(std::vector<Node> &nodes);
void initEdges(std::vector<Node> &nodes, std::vector<Edge> &edges);
void inputNodes(std::vector<Node> &nodes, std::vector<Edge> &edges);
void initNodesAndEdges(std::vector<Node> &nodes, std::vector<Edge> &edges);

void printNodes(std::vector<Node> &nodes, std::vector<Edge> &edges);

void initAreaFlow(std::vector<Node> &nodes, std::vector<Edge> &edges);
void initAFOnlySucc(std::vector<Node> &nodes, std::vector<Edge> &edges);

float initAreaFlowNoEdges(std::vector<Node> &nodes, size_t id);
