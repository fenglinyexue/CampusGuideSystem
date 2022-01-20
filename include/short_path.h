#ifndef SHORT_PATH_H
#define SHORT_PATH_H

#include "graph.h"
#include "list.h"

/**
 * @brief 辅助数据，用以找到图中任意起点到图中其他顶点的最短距离
 *
 */
typedef struct short_path {
  int ver_num;
  int *dis;         // 目标顶点到图中各顶点的最短距离
  int *pre_visited; // 前驱顶点，用以存储与某一顶点距离最短的顶点代码
  // int *final;
} spath_t;

/**
 * @brief 初始化辅助结构体
 *
 * @return spath_t*
 */
spath_t *init_spath_data(const graph_t *graph);

/**
 * @brief 迪杰斯特拉算法，用以实现找到图中任意起点到其他顶点的最短距离
 *
 * @param graph     指向无向加权图的指针
 * @param startv    开始顶点
 * @return OK
 */
int dijkstra(graph_t *graph, spath_t *spath, ver_code startv);

/**
 * @brief 打印任意出发点到图中任一顶点的最短距离
 * 
 * @param spath 
 * @return int 
 */
int show_short_path(const graph_t *graph, const spath_t *spath, ver_code startv, ver_code endv);

#endif