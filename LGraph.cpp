//
// Created by 刘凯源 on 24-5-16.
//

#include "LGraph.h"

namespace Graph {
    LGraph::LGraph(bool directed)
        : n_verts(0), m_edges(0), directed(directed), ver_list(std::vector<HeadNode>()) {}

    bool LGraph::exist_vertex(const std::string& name) const {
        //todo:判断是否存在name名称的节点
        return vertex_map.find(name) != vertex_map.end();
        //std::cerr << "LGraph::exist_vertex(const std::string &name) 还没实现" << std::endl;
        //return false;
    }

    bool LGraph::exist_edge(const std::string& vertex_x_name, const std::string& vertex_y_name) const {
        //todo:判断是否存在x-y的边
        auto itx = vertex_map.find(vertex_x_name);
        auto ity = vertex_map.find(vertex_y_name);
        if (itx == vertex_map.end() || ity == vertex_map.end()) return false;
        for (const auto& edge : ver_list[itx->second].adj) {
            if (edge.dest == ity->second) return true;
        }
        for (const auto& edge : ver_list[ity->second].adj) {
            if (edge.dest == itx->second) return true;
        }
        return false;
       // std::cerr << "LGraph::exist_edge(const std::string &vertex_x_name, const std::string &vertex_y_name) 还没实现" << std::endl;
       //return false;
    }

    void LGraph::InsertVertex(const LocationInfo& vertex_info) {
        //todo:插入节点，节点信息由LocationInfo类给出
        if (!exist_vertex(vertex_info.name)) {
          vertex_map[vertex_info.name] = n_verts;
          ver_list.emplace_back(HeadNode(vertex_info));
          ++n_verts;
        }
        //std::cerr << "LGraph::InsertVertex(const LocationInfo &vertex_info) 还没实现" << std::endl;
    }

    void LGraph::DeleteVertex(const LocationInfo& vertex_info) {
        //todo:删除节点，节点信息由LocationInfo类给出
        if (exist_vertex(vertex_info.name)) {
          Vertex id = vertex_map[vertex_info.name];
          deleted.insert(vertex_info.name);
          vertex_map.erase(vertex_info.name);

          // 删除边
          for (auto& head_node : ver_list) {
            head_node.adj.remove_if([id](const EdgeNode& edge) { return edge.from == id || edge.dest == id; });
          }

          --n_verts;
        }
        //std::cerr << "LGraph::DeleteVertex(const LocationInfo &vertex_info) 还没实现" << std::endl;
    }

    void LGraph::UpdateVertex(const LocationInfo& old_info, LocationInfo& new_info) {
        //todo:更新节点，新/旧节点的信息由LocationInfo类给出
        if (exist_vertex(old_info.name)) {
          Vertex id = vertex_map[old_info.name];
          ver_list[id].data = new_info;
          // 更新vertex_map.
          if (old_info.name != new_info.name) {
              vertex_map.erase(old_info.name);
              vertex_map[new_info.name] = id;
          }
        }
        //std::cerr << "LGraph::UpdateVertex(const LocationInfo &old_info, LocationInfo &new_info) 还没实现" << std::endl;
    }

    VertInfo LGraph::GetVertex(const std::string& name) const {
        //todo:获取节点，由节点名查询节点信息
        auto it = vertex_map.find(name);
        if (it != vertex_map.end()) {
            return ver_list[it->second].data;
        }
        return VertInfo();
        //std::cerr << "LGraph::GetVertex(const std::string &name) 还没实现" << std::endl;
        //return VertInfo();
    }

    VertInfo LGraph::GetVertex(const Vertex vertex) const {
        //todo:获取节点，由节点的ID查询
        Vertex n=n_verts;
        if (vertex < n) {
        return ver_list[vertex].data;
        }
        return VertInfo(); // Return empty info if invalid vertex ID.
       // std::cerr << "LGraph::GetVertex(const Vertex vertex) 还没实现" << std::endl;
       //return VertInfo();
    }







    void LGraph::InsertEdge(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet weight) {
        //todo:插入边
        if ((!exist_edge(vertex_x_name, vertex_y_name))&&exist_vertex(vertex_x_name)&&exist_vertex(vertex_y_name)) {
        Vertex from = vertex_map[vertex_x_name];
        Vertex dest = vertex_map[vertex_y_name];

        ver_list[from].adj.emplace_back(EdgeNode(from, dest, weight));
        ++m_edges;
       }
       else if(exist_edge(vertex_x_name, vertex_y_name)){}
       else{std::cout<<"输入数据有问题";}
        //std::cerr << "LGraph::InsertEdge(const std::string &vertex_x_name, const std::string &vertex_y_name, GElemSet weight) 还没实现" << std::endl;

    }

    void LGraph::DeleteEdge(const std::string& vertex_x_name, const std::string& vertex_y_name) {
        //todo:删除边，由两个节点名确定一条边
         DeleteEdge(vertex_map[vertex_x_name], vertex_map[vertex_y_name]);
        //std::cerr << "LGraph::DeleteEdge(const std::string &vertex_x_name, const std::string &vertex_y_name) 还没实现" << std::endl;

    }

    void LGraph::DeleteEdge(Vertex vertex_x, Vertex vertex_y) {
        //todo:删除边，由两个节点ID确定一条边
        if (exist_edge(GetVertex(vertex_x).name, GetVertex(vertex_y).name)) {
          ver_list[vertex_x].adj.remove_if([vertex_y](const EdgeNode& edge) { return edge.dest == vertex_y; });
          ver_list[vertex_y].adj.remove_if([vertex_x](const EdgeNode& edge) { return edge.dest == vertex_x; });
        --m_edges;
        }
        else{std::cout<<"边不存在";}
        //std::cerr << "LGraph::DeleteEdge(Vertex vertex_x, Vertex vertex_y) 还没实现" << std::endl;
    }


    void LGraph::UpdateEdge(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet new_weight) {
        //todo:更新边，由两个节点名确定一条边
        if (exist_edge(vertex_x_name, vertex_y_name)) {
          Vertex from = vertex_map[vertex_x_name];
          Vertex dest = vertex_map[vertex_y_name];

        for (auto& edge : ver_list[from].adj) {
            if (edge.dest == dest) {
                edge.weight = new_weight;
                break;
            }
        }
        if (!directed) {
            for (auto& edge : ver_list[dest].adj) {
                if (edge.dest == from) {
                    edge.weight = new_weight;
                    break;
                }
            }
        }
        }
        //std::cerr << "LGraph::UpdateEdge(const std::string &vertex_x_name, const std::string &vertex_y_name, GElemSet new_weight) 还没实现" << std::endl;
    }

    GElemSet LGraph::GetEdge(const std::string& vertex_x_name, const std::string& vertex_y_name) const {
        //todo:获取边的信息
        if (exist_edge(vertex_x_name, vertex_y_name)) {
          Vertex from = vertex_map.at(vertex_x_name);
          Vertex dest = vertex_map.at(vertex_y_name);

        for (const auto& edge : ver_list[from].adj) {
            if (edge.dest == dest) return edge.weight;
        }
        for (const auto& edge : ver_list[dest].adj) {
            if (edge.dest == from) return edge.weight;
        }
        }
        //std::cerr << "LGraph::GetEdge(const std::string &vertex_x_name, const std::string &vertex_y_name) 还没实现" << std::endl;
        return GElemSet();
    }

    std::vector<EdgeNode> LGraph::SortedEdges(std::function<bool(const GElemSet&, const GElemSet&)> cmp) const {
        //todo:获取按边权和给定规则排序的所有边
        std::vector<EdgeNode> all_edges;
        for (const auto& head : ver_list) {
            for (const auto& edge : head.adj) {
                all_edges.push_back(edge);
            }
        }
        std::sort(all_edges.begin(), all_edges.end(), [cmp](const EdgeNode& a, const EdgeNode& b) {
            return cmp(a.weight, b.weight);
        });
        return all_edges;
        //std::cerr << "LGraph::SortedEdges(std::function<bool(const GElemSet &, const GElemSet &)> cmp) 还没实现" << std::endl;
        //return std::vector<EdgeNode>();
    }


}
