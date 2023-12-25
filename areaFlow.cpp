#include "areaFlow.h"

int main() {
  std::vector<Node> nodes = {};
  std::vector<Edge> edges = {};

  initNodesAndEdges(nodes, edges);

  // initAreaFlow(nodes, edges);
  for (size_t id = 0; id < nodes.size(); id++) {
    if (nodes[id].succ.size() == 0) {
      initAreaFlowNoEdges(nodes, id);
    }
  }
  printNodes(nodes, edges);
  /*
  for (Node &node : nodes) {
    node.af = 0;
  }
  
  initAFOnlySucc(nodes, edges);
  printNodes(nodes, edges);
  */
  return 0;
}

void initPred(std::vector<Node> &nodes) {
  for (Node node : nodes) {
    for (size_t succId : node.succ) {
      nodes[succId].pred.push_back(node.id);
    }
  }
}

void initEdges(std::vector<Node> &nodes, std::vector<Edge> &edges) {
  size_t countEdge = 0;
  for (Node &node : nodes) {
    for (size_t succId : node.succ) {
      struct Edge newEdge = {};
      newEdge.id = countEdge;
      newEdge.head = node.id;
      newEdge.tail = succId;

      node.oedge.push_back(newEdge.id);
      nodes[succId].iedge.push_back(newEdge.id);

      edges.push_back(newEdge);
      countEdge++;
    }
  }
}

void inputNodes(std::vector<Node> &nodes, std::vector<Edge> &edges) {
  size_t lenNodes = -1;
  std::cin >> lenNodes;

  for (size_t id = 0; id < lenNodes; id++) {
    struct Node newNode = {};
    newNode.id = static_cast<size_t>(id);

    int inpSuccId = -1;
    while (1) {
      std::cin >> inpSuccId;
      if (inpSuccId == -1) {
        break;
      }
      newNode.succ.push_back(static_cast<size_t>(inpSuccId));
    }

    nodes.push_back(newNode);
  }
}

void initNodesAndEdges(std::vector<Node> &nodes, std::vector<Edge> &edges) {
  inputNodes(nodes, edges);

  initPred(nodes);

  initEdges(nodes, edges);
}

void printNodes(std::vector<Node> &nodes, std::vector<Edge> &edges) {
  std::cout << "NODES" << std::endl;
  for (Node &node : nodes) {
    std::cout << "id: " << node.id;

    std::cout << std::endl << "succ: ";
    for (size_t succId : node.succ) {
      std::cout << succId << " ";
    }

    std::cout << std::endl << "pred: ";
    for (size_t predId : node.pred) {
      std::cout << predId << " ";
    }

    std::cout << std::endl << "oedges: ";
    for (size_t oedgeId : node.oedge) {
      std::cout << "[" << edges[oedgeId].head << "," << edges[oedgeId].tail
                << "]"
                << "af=" << edges[oedgeId].af << " ";
    }

    std::cout << std::endl << "iedges: ";
    for (size_t iedgeId : node.iedge) {
      std::cout << "[" << edges[iedgeId].head << "," << edges[iedgeId].tail
                << "]"
                << "af=" << edges[iedgeId].af << " ";
    }

    std::cout << std::endl << "af: " << node.af;

    std::cout << std::endl << std::endl;
  }

  std::cout << "EDGES" << std::endl;
  for (Edge &edge : edges) {
    std::cout << "id: " << edge.id << std::endl;
    std::cout << "af: " << edge.af << std::endl;
  }
}

void initAreaFlow(std::vector<Node> &nodes, std::vector<Edge> &edges) {
  for (Node &node : nodes) {
    if (node.pred.size() == 0) {
      node.af = 0;
      for (size_t oedgeId : node.oedge) {
        edges[oedgeId].af = 0;
      }
    }
  }

  for (Node &node : nodes) {
    if (node.pred.size() == 0) {
      continue;
    }

    if (node.succ.size() == 0) {
      node.af = 0;
    } else {
      node.af = 1;
    }
    for (size_t iedgeId : node.iedge) {
      node.af += edges[iedgeId].af;
    }

    for (size_t oedgeId : node.oedge) {
      edges[oedgeId].af = node.af / node.oedge.size();
    }
  }
}

void initAFOnlySucc(std::vector<Node> &nodes, std::vector<Edge> &edges) {
  for (Node &node : nodes) {
    if (node.iedge.size() == 0) {
      node.af = 0;
    } else {
      if (node.oedge.size() != 0) {
        node.af += 1;
      }
    }
    
    for (size_t idEdge : node.oedge) {
      nodes[edges[idEdge].tail].af += node.af / node.oedge.size();
    }
  }
}

float initAreaFlowNoEdges(std::vector<Node> &nodes, size_t id) {
  if (nodes[id].afFixed) {
    return nodes[id].af;
  }
  if (nodes[id].pred.size() == 0) {
    nodes[id].af = 0;
    return nodes[id].af;
  }
  if (nodes[id].succ.size() == 0) {
    nodes[id].af = 0;
  } else {
    nodes[id].af = 1;
  }
  for (size_t predId : nodes[id].pred) {
    nodes[id].af += initAreaFlowNoEdges(nodes, predId) / nodes[predId].succ.size();
  }
  nodes[id].afFixed = true;
  return nodes[id].af;
}
