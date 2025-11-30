# Campus-Navigation-System
A versatile campus navigation application built with C++ that leverages graph theory to enable efficient pathfinding, network analysis, and data management for campus locations.

## 项目介绍

本项目旨在通过图论算法解决校园导航的核心需求，支持从文件加载校园地点（顶点）和路径（边）数据，提供全面的图操作功能与算法分析工具。不仅可作为校园导航实用工具，也可作为数据结构与算法学习的实践案例，帮助理解图的存储、遍历、最短路径、最小生成树等核心知识点。

## 核心功能

| 功能模块 | 具体实现 |
|----------|----------|
| **图初始化** | 从 nodes.csv（顶点数据）和 edges.csv（边数据）读取信息，自动构建无向图 |
| **顶点管理** | 1. 查询特定顶点详情（名称、类型、建议游览时间）<br>2. 展示所有顶点信息<br>3. 添加/删除顶点<br>4. 导出顶点数据到 CSV 文件（test_nodes.csv） |
| **边管理** | 1. 查询特定两点间边信息（距离）<br>2. 展示所有边详情（起点、终点、距离）<br>3. 添加/删除边<br>4. 导出边数据到 CSV 文件（test_edges.csv） |
| **文件重新加载** | 重新读取原始 CSV 文件数据，覆盖当前修改，恢复初始图状态 |
| **欧拉通路检测** | 判断图中是否存在欧拉回路，支持图连通性与顶点度数分析 |
| **最短路径计算** | 基于 Floyd 算法，求解任意两点间的最短距离 |
| **最小生成树** | 基于 Kruskal 或 Prim 算法，生成图的最小生成树并计算总权重（仅连通图有效） |
| **拓扑受限最短路径** | 根据用户指定的拓扑序列，求解满足该序列约束的最短路径 |
| **菜单交互界面** | 多级菜单设计，操作指引清晰，支持错误捕获与友好提示 |

## 技术实现

### 开发环境
- **编程语言**：C++11 及以上标准
- **依赖库**：C++ 标准库（iostream、fstream、vector、sstream 等）
- **自定义头文件**：
  - LGraph.h（图结构定义）
  - Algorithm.h（算法实现）
  - LocationInfo.h（顶点信息结构体）
  - GraphException.h（异常处理）

### 数据结构与算法

| 模块 | 核心技术 |
|------|----------|
| **图存储** | 邻接表（LGraph 类实现），高效支持顶点/边的增删改查 |
| **最短路径** | Floyd 算法（时间复杂度 $O(n^3)$），适用于小规模校园地图（顶点数量较少场景） |
| **最小生成树** | Kruskal 或 Prim 算法（时间复杂度 $O(E \log E)$ 或 $O(n^2)$） |
| **欧拉回路检测** | 基于图连通性判断 + 顶点度数分析（无向图欧拉回路条件：连通且所有顶点度数为偶数） |
| **数据持久化** | CSV 文件读写，支持逗号分隔符解析与数据格式转换 |
| **异常处理** | 自定义 GraphException 类，捕获顶点/边不存在、重复添加等异常场景 |

## 快速开始

### 环境准备
1. 安装支持 C++11 及以上标准的编译器（如 GCC、Clang、MSVC）
2. 确保项目目录下包含以下文件：
   - 主程序文件：main.cpp
   - 自定义头文件：LGraph.h、Algorithm.h、LocationInfo.h、GraphException.h
   - 数据文件：nodes.csv（顶点数据）、edges.csv（边数据）

### 数据文件格式

#### 1. 顶点文件（nodes.csv）
格式：顶点名称,顶点类型,建议游览时间（逗号分隔，无空格）

示例：
```csv
stadium,体育场馆,60
swimming_pool,游泳馆,45
Jinshajiang_Road_Gate,金沙江路校门,10
Hedong_Basketball_Court,河东篮球场,30
Liberal_Arts_Building,文科楼,20
```

#### 2. 边文件（edges.csv）
格式：起点名称,终点名称,距离（逗号分隔，无空格）

示例：
```csv
Jinshajiang_Road_Gate,swimming_pool,300
swimming_pool,stadium,500
stadium,Hedong_Basketball_Court,200
Hedong_Basketball_Court,Liberal_Arts_Building,150
Liberal_Arts_Building,Jinshajiang_Road_Gate,400
```

### 编译与运行

直接运行main.cpp文件

## 性能分析

### 1. 读写效率
- CSV 文件解析采用字符串流（stringstream）与字符替换逻辑，高效处理逗号分隔数据
- 支持大规模数据加载（校园场景下顶点/边数量通常较少，读写耗时可忽略）

### 2. 算法效率
- Floyd 算法适用于顶点数 $n < 100$ 的场景，校园地图通常满足该条件，响应迅速
- 最小生成树算法（Kruskal/Prim）针对边数较少的无向图，效率表现良好
- 若需扩展至更大规模图，可替换为 Dijkstra 算法（单源最短路径）或优化存储结构

### 3. 内存使用
- 邻接表存储方式避免了矩阵存储的空间浪费，内存占用与顶点/边数量线性相关
- 校园导航场景下内存需求可控，无冗余开销

## 项目改进方向

### 算法优化
- 引入 Dijkstra 算法（单源最短路径）、A* 算法（启发式路径规划），提升大规模图的路径计算效率

### 功能扩展
- 添加路线可视化功能（结合 OpenGL 或 Qt 绘制校园地图与路径）
- 支持多路径对比、景点推荐（基于游览时间、距离等权重）
- 增加用户登录、历史查询记录功能

### 用户体验
- 优化控制台交互（输入校验、分页展示大量顶点/边）
- 开发图形化界面（GUI），替代命令行菜单
