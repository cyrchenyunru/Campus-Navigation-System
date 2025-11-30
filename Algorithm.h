//
// Created by 刘凯源 on 24-10-13.
//

#ifndef CAMPUSNAVIGATION_ALGORITHM_H
#define CAMPUSNAVIGATION_ALGORITHM_H

#include "LGraph.h"

namespace Graph {
    namespace Algorithm {
        class DSU {
        private:
            std::vector<int> parent, rank;
        public:
            // 并查集构造函数
            explicit DSU(int n) : parent(n), rank(n, 0) {//更改了原有代码，新增了parent(n), rank(n, 0)
                // todo: 请完成并查集的构造函数
              for (int i = 0; i < n; i++) {
                parent[i] = i; // 每个元素都是自己的父节点
              }

            }

            // 查找根节点并路径压缩
            int find(int x) {
                // todo: 查找元素的根节点，并完成路径压缩
                if (parent[x] != x) {
                parent[x] = find(parent[x]); // 路径压缩：将x直接连接到根节点
                }
                return parent[x];
            }

            // 合并两个集合
            void unite(int x, int y) {
                // todo: 合并集合
                int rootX = find(x);
                int rootY = find(y);

                if (rootX != rootY) {
                // 按秩合并：较低秩的树成为较高秩树的子树
                  if (rank[rootX] > rank[rootY]) {
                     parent[rootY] = rootX;
                  }
                  else if (rank[rootX] < rank[rootY]) {
                    parent[rootX] = rootY;
                  }
                  else {
                    parent[rootY] = rootX;
                    rank[rootX]++; // 如果秩相等，则任意选择一个作为新的根，并增加其秩
                  }
                }
            }

            // 检查两个节点是否属于同一集合
            bool same(int x, int y) const {
                // todo: 检查两个节点是否属于同一个集合
                while (x != parent[x]) {
                    x = parent[x];
                }
                while (y != parent[y]) {
                    y = parent[y];
                }
                return x == y;
            }
        };

        std::list<Vertex> EulerCircle(const LGraph& graph); //计算欧拉回路
        bool HaveEulerCircle(const LGraph& graph); //判断是否存在欧拉回路
        bool IsConnected(const LGraph& graph); //判断图是否联通
        int GetShortestPath(const LGraph& graph, const std::string& vertex_name_x,
            const std::string& vertex_name_y); //计算单源最短路径
        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path); //计算拓扑受限的最短路径
        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph); //计算最小生成树
    }
}
#endif //CAMPUSNAVIGATION_ALGORITHM_H
