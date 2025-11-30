//
// Created by 刘凯源 on 24-10-13.
//
#include "Algorithm.h"
#include <stack>
#include <queue>
#include <unordered_set>
#include <vector>

namespace Graph {
    namespace Algorithm {
        std::list<Vertex> GetCircuit(LGraph& graph, Vertex start) {
            //todo:从给定点出发获得一条回路
            std::list<Vertex> circuit;
            std::stack<Vertex> stack;
            stack.push(start);
           // 创建一个映射来跟踪访问过的边
            std::unordered_map<Vertex, std::unordered_set<Vertex>> visitedEdges;

            while (!stack.empty()) {
            Vertex current = stack.top();
            bool hasEdge = false;

            for (auto& edge : graph.List()[current].adj) {
              if (edge.weight >= 0 && visitedEdges[current].find(edge.dest) == visitedEdges[current].end()) {
                hasEdge = true;
                Vertex next = edge.dest;
                // 标记这条边为已访问
                visitedEdges[current].insert(next);
                visitedEdges[next].insert(current);
                stack.push(next);
                break;
              }
            }

            if (!hasEdge) {
            circuit.push_front(stack.top());
            stack.pop();
            }
            }

        return circuit;
        }

        std::list<Vertex> EulerCircle(const LGraph& graph) {
          //todo:获取欧拉回路,你可以使用GetCircuit函数
          if (!HaveEulerCircle(graph)) return {};
          LGraph tempGraph = const_cast<LGraph&>(graph); // 创建临时图进行修改
          std::list<Vertex> eulerCircle;
          // 找到一个非孤立的顶点作为起点
          Vertex ver_count=tempGraph.VertexCount();
          for (Vertex v = 0; v < ver_count; ++v) {
             if (!tempGraph.List()[v].adj.empty()) {
             eulerCircle = GetCircuit(tempGraph, v);
             break;
             }
          }
          return eulerCircle;
          //std::cerr << "EulerCircle 还没实现" << std::endl;
          //return {};
        }

        bool HaveEulerCircle(const LGraph& graph) {
            //todo:判断是否有欧拉回路
            // 检查图是否连通
            if (!IsConnected(graph)) return false;

            // 创建一个映射来存储每个顶点的度数
            std::unordered_map<Vertex, int> degrees;

            // 遍历所有顶点及其邻接表，计算每个顶点的度数
            for (const auto& head : graph.List()) {
                for (const auto& edge : head.adj) {
                  ++degrees[edge.dest];
                  ++degrees[edge.from];
                }
            }

           // 检查每个顶点的度数是否为偶数
           for (const auto& degree : degrees) {
              if (degree.second % 2 != 0) {
                return false;
              }
           }

           return true;
            //std::cerr << "HaveEulerCircle 还没实现" << std::endl;
            //return false;
        }

        void BFSv(LGraph& graph, Vertex v, std::vector<bool>& visited) {
            //todo:广度优先搜索整个图
            std::queue<Vertex> queue;
            visited[v] = true;
            queue.push(v);
            while (!queue.empty()) {
              Vertex current = queue.front();
              queue.pop();
              for (const auto& edge : graph.List()[current].adj) {
                Vertex next = edge.dest;
                  if (!visited[next]) {
                    visited[next] = true;
                    queue.push(next);
                  }
              }
            }
            //std::cerr << "BFSv 还没实现" << std::endl;
        }

        bool IsConnected(const LGraph& graph) {//自己加了一个const
        //todo:判断图是否联通
          if (graph.VertexCount() == 0) return true; // 空图认为是连通的

          std::vector<bool> visited(graph.VertexCount(), false);
          int start = 0;
          BFSv(const_cast<LGraph&>(graph), start, visited);

          // 如果所有节点都被访问，则图是连通的
          return std::all_of(visited.begin(), visited.end(), [](bool v) { return v; });
          //std::cerr << "IsConnected 还没实现" << std::endl;
          //return false;
        }

        int GetShortestPath(const LGraph& graph, const std::string& vertex_name_x, const std::string& vertex_name_y) {
            //todo:获取两点之间的最短路径
            // 检查起始点和终点是否存在于图中
            if (!graph.exist_vertex(vertex_name_x) || !graph.exist_vertex(vertex_name_y)) return -1;

            // 通过地点名获取顶点ID
            Vertex x = graph.Map().at(vertex_name_x);
            Vertex y = graph.Map().at(vertex_name_y);

            // 初始化距离矩阵，所有不可达顶点对之间的距离设为INT_MAX
            std::vector<std::vector<int>> dist(graph.VertexCount(), std::vector<int>(graph.VertexCount(), INT_MAX));

            size_t vertex_count = graph.VertexCount();

            // 将每个顶点到自身的距离设置为0
            for (Vertex i = 0; i < vertex_count; ++i) {
                dist[i][i] = 0;
            }

            // 填充直接相连的边的距离
            for (Vertex u = 0; u < vertex_count; ++u) {
                for (const auto& edge : graph.List()[u].adj) {
                    dist[u][edge.dest] = edge.weight;
                }
            }

            // Floyd-Warshall算法核心逻辑：遍历每一个中间顶点k
            for (Vertex k = 0; k < vertex_count; ++k) {
                // 对于每一对顶点(i, j)，检查是否存在通过顶点k的更短路径
                for (Vertex i = 0; i < vertex_count; ++i) {
                    for (Vertex j = 0; j < vertex_count; ++j) {
                        // 如果存在从i到k且从k到j的路径，并且这条路径比当前记录的i到j的路径更短，则更新dist[i][j]
                        if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }

            // 返回起点x到终点y之间的最短路径长度，如果不存在路径则返回-1
            return dist[x][y] == INT_MAX ? -1 : dist[x][y];
        }

        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path) {
            //todo:获取拓扑受限的最短路径，拓扑序由path给出
           // 获取顶点数量
           int n = graph.VertexCount();

          // 初始化距离数组，所有不可达顶点的距离设为INT_MAX
          std::vector<int> dist(n, INT_MAX);

          // 起点到自身的距离为0
          if (path.empty() || !graph.exist_vertex(path.front())) {
            return -1; // 如果路径为空或起始点不存在，则返回-1表示无效
          }
          dist[graph.Map().at(path.front())] = 0;

          // 按照拓扑顺序处理每个顶点
          for (const auto& vertex_name : path) {
            // 获取当前顶点的索引
            Vertex u = graph.Map().at(vertex_name);

           // 如果当前顶点的最短路径是无穷大，跳过
           if (dist[u] == INT_MAX) continue;

           // 遍历当前顶点的邻接边
           for (const auto& edge : graph.List()[u].adj) {
             Vertex v = edge.dest;      // 邻接顶点的索引
             int weight = edge.weight; // 边的权重

             // 计算通过当前顶点 u 到达邻接顶点 v 的路径
             if (dist[u] + weight < dist[v]) {
                 dist[v] = dist[u] + weight;
             }
           }
          }

          // 返回从源点到目标点的最短路径
          Vertex end = graph.Map().at(path.back());
          return dist[end]; // 返回目标点的最短路径长度
          }

        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph) {
            //todo:计算最小生成树，并返回树上的边
            DSU dsu(graph.VertexCount());
            std::vector<EdgeNode> mst;
            //从小到大排序
            auto edges = graph.SortedEdges(std::less<>());


            for (const auto& edge : edges) {
              //如果不在同一个连通分量中
              if (dsu.find(edge.from) != dsu.find(edge.dest)) {
                mst.push_back(edge);
                dsu.unite(edge.from, edge.dest);

              }
            }

            return mst;
            //std::cerr << "MinimumSpanningTree 还没实现" << std::endl;
            //return {};
        }
    }
}
