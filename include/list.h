#ifndef LIST_H
#define LIST_H 1

#define N 65535 // 整型数据的最大值

typedef int ver_code;
typedef int dist_t;

/**
 * @brief 该结构体表示无向加权图中邻接表的元素节点，即与图中顶点相邻的其他顶点
 *
 */
typedef struct node {
  char *name;             // 景点名称
  ver_code code;          // 景点代码
  char *desc;             // 景点简介
  unsigned long distance; // 相邻顶点间距离
  int deleted; // 懒惰删除标志，为1表示删除，为0表示未删除
  struct node *next;
} node_t, list_t;

/**
 * @brief 链表分配内存空间，初始化后返回指向其的指针
 *
 * @return adj_list* 指向邻接表的指针
 */
list_t *init_list();

/**
 * @brief 邻接表中添加边，并赋权值，表示两相邻顶点间的距离
 *
 * @param list      待添加边的顶点的邻接表
 * @param ver       待与顶点相连的顶点
 * @param distance  两顶点间的距离
 * @return int      状态码
 */
int add_node(list_t *list, char *name, const ver_code ver, char *desc,
             const dist_t distance);

/**
 * @brief 移除邻接表中的相邻顶点
 *
 * @param list 邻接表
 * @param ver 邻接表中待移除的景点
 * FIXME: @return int 状态码
 */
int remove_node(list_t *list, const ver_code ver);

/**
 * @brief 更新邻接表中相邻景点的路径信息
 *
 * @param list 邻接表
 * @param ver  邻接表中待更新路径信息的相邻景点
 * FIXME: @return int
 */
int update_node(list_t *list, const ver_code ver, dist_t distance);

/**
 * @brief 懒惰删除邻接表中顶点
 *
 * @param list 邻接表
 * @param ver  待删除顶点
 * FIXME: @return int
 */
int lazzy_remove_node(list_t *list, const ver_code ver);

/**
 * @brief 恢复邻接表中懒惰删除的节点
 *
 * @param list 邻接表
 * @param ver  待恢复景点
 * FIXME: @return int
 */
int restore_lazzy_remove_node(list_t *list, const ver_code ver);

int traverse(list_t *list);

#endif