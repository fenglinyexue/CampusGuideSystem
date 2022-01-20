#ifndef GRAPH_H
#define GRAPH_H 1

#include "list.h"
#include "queue.h"
#include "stack.h"

#define MAX_VER 100

/**
 * @brief 无向加权图
 */
typedef struct graph {
  int ver_num;          // 顶点个数
  list_t *adj[MAX_VER]; // 邻接表
  int *marked; // 指针形式整型数组，为1表示顶点已访问，为0表示未访问
} graph_t;

/**
 * @brief 为图分配内存空间，初始化后返回指向图的指针
 *
 * @param   ver_num   顶点个数
 * @return  graph_t*
 * 指向初始化后的图的指针;若指定的顶点个数超出顶点上限MAX_VER，则为NULL。
 */
graph_t *init_graph(int ver_num);

/**
 * @brief 初始化顶点
 *
 * @param graph 指向图的指针
 * @param ver   顶点
 * @param name  景点名称
 * @param code  景点代码
 * @param desc  景点简介
 * @return int
 * 若指向图的指针为空，则为GRAPH_NULL；若待初始化的景点代码不符规范，则返回VER_CODE_ERR；若顶点已存在，则返回VER_EXIST；若成功初始化顶点则返回OK。
 */
int init_vertex(graph_t *graph, const ver_code ver, char *name, char *desc);

/**
 * @brief 在图中连接两个顶点，顶两顶点间距离
 *
 * @param graph     指向图的指针
 * @param ver1      待连接路径的首端点
 * @param ver2      待连接路径的尾端点
 * @param distance  两顶点间的距离
 * TODO: @return int
 */
int add_edge(graph_t *graph, const ver_code ver1, const ver_code ver2,
             const dist_t distance);

/**
 * @brief
 * 移除图中量相邻顶点的边，若两顶点相邻，成功执行相应操作，返回OK，反之则返回相应的错误码
 *
 * @param graph 指向图的指针
 * @param ver1  待移除路径的首端点
 * @param ver2  待移除路径的尾端点
 * @return int
 */
int remove_edge(graph_t *graph, const ver_code ver1, const ver_code ver2);

/**
 * @brief 更新路径信息
 *
 * @param graph 指向图的指针
 * @param ver1  待更新路径的首端点
 * @param ver2  待更新路径的尾端点
 * TODO: @return int
 */
int update_edge(graph_t *graph, const ver_code ver1, const ver_code ver2,
                const dist_t distance);

/**
 * @brief 移除图中顶点，若待移除顶点成功，返回OK；反之则返回相应的错误码
 *
 * @param graph 指向无向加权图的指针
 * @param ver   待移除的顶点
 * TODO: @return int
 */
int remove_vertex(graph_t *graph, const ver_code ver);

/**
 * @brief
 * 懒惰删除图中景点，即非物理意义上的删除，而是利用标志变量标志景点，标记后该景点不会被访问。
 *
 * @param graph 指向无向加权图的指针
 * @param ver   待移除的顶点
 * TODO: @return int
 */
int lazzy_remove_vertex(graph_t *graph, const ver_code ver);

/**
 * @brief
 * 恢复关闭的景点，即将图中懒惰删除的景点所在结点的deleted属性赋值为0(node_t.deleted
 * = 1)。
 *
 * @param graph 指向无向加权图的指针
 * @param ver   待移除的顶点
 * TODO: @return int
 */
int restore_vertex(graph_t *graph, const ver_code ver);

/**
 * @brief
 * 返回某个顶点邻接表中的下一个相邻顶点，若无相邻顶点或已查找到最后一个相邻顶点后再次查找下个相邻顶点，则返回ADJ_VER_NULL
 *
 * @param list      指定顶点的邻接表
 * @return ver_code
 * 若下个相邻顶点存在则返回对应的顶点代码，反之则返回ADJ_VER_NULL
 */
ver_code next_adj_vertex(list_t *list);

/**
 * @brief
 * 查询某顶点，若该顶点存在，输出其相关信息，其若存在相邻顶点，则一并输出其相邻顶点信息
 *
 * @param graph 指向无向加权图的指针
 * @param ver   待查找的顶点
 * TODO: @return int
 */
int vertex_info(graph_t *graph, ver_code ver);

/**
 * @brief 遍历图中所有顶点
 *
 * @param graph 指向无向加权图的指针
 * @return int
 */
int traverse_graph(graph_t *graph);

/**
 * @brief 深度优先遍历
 *
 * @param graph 指向无向加权图的指针
 * @param queue 作辅助的队列
 * @param startv  开始遍历的起点
 * @return int
 */
int BFS(graph_t *graph, vqueue_t *queue, ver_code startv);

/**
 * @brief 将图中的标记数组置为0，表示先前已访问过的所有景点置为为访问状态
 *
 * @param graph 指向无向加权图的指针
 */
int init_marked(graph_t *graph);

/**
 * @brief 图的深度优先遍历
 *
 * @param graph 指向无向加权图的指针
 * @param stack 作辅助的栈
 * @param startv  开始遍历的起点
 * @return int
 */
int DFS(graph_t *graph, vstack_t *stack, ver_code startv);

/**
 * @brief
 * 查看系统内有效的可初始化顶点个数，即待初始化的景点代码在图中未存在
 *
 * @param graph 指向无向加权图的指针
 * @return int
 */
int valid_init_vertex_count(graph_t *graph);

#endif