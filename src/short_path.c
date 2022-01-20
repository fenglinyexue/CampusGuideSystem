#include "../include/short_path.h"
#include "../include/custom_err_msg.h"
#include "../include/graph.h"
#include "../include/queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

spath_t *init_spath_data(const graph_t *graph) {
  if (!graph)
    return NULL;

  spath_t *spath;
  spath = (spath_t *)malloc(sizeof(spath_t));
  assert(spath);

  spath->ver_num = graph->ver_num;
  spath->dis = (int *)malloc(sizeof(int) * spath->ver_num);
  assert(spath->dis);
  spath->pre_visited = (int *)malloc(sizeof(int) * spath->ver_num);
  assert(spath->pre_visited);

  for (int i = 0; i < graph->ver_num; i++) {
    spath->dis[i] = N;
    spath->pre_visited[i] = -1;
  }

  return spath;
}

int dijkstra(graph_t *graph, spath_t *spath, ver_code startv) {
  if (!graph)
    return GRAPH_NULL;
  if (!spath)
    return SPATH_NULL;
  if (startv < 1 || graph->ver_num < startv || startv > MAX_VER)
    return VER_CODE_ERR;
  if (!(graph->adj[startv - 1]))
    return VER_NOT_EXIST;
  if (graph->adj[startv - 1]->code == 0)
    return VER_NOT_EXIST;

  init_marked(graph);

  list_t *adj, *cur;
  dist_t min, tmp;
  int stat_code;
  ver_code min_ver;
  vqueue_t *queue;
  node_t *vnode;
  queue = init_queue();

  adj = graph->adj[startv - 1];
  cur = adj;

  // 标记出发顶点，其前驱顶点为其自身，将其入队
  graph->marked[startv - 1] = 1;
  spath->pre_visited[startv - 1] = startv;
  spath->dis[startv - 1] = 0;
  put_queue(queue, cur);

  while (is_empty(queue) != ELEM_IS_NULL) {
    stat_code = pop_queue(queue, &vnode);
    if (stat_code < 0)
      return stat_code;

    adj = graph->adj[vnode->code - 1];
    cur = adj;
    min = N;
    while (cur) {
      if (graph->marked[cur->code - 1] != 1) {
        if (cur->distance < min) {
          min_ver = cur->code;
          min = cur->distance;
        }
        put_queue(queue, cur);
      }
      cur = cur->next;
    }

    // 标记当前顶点
    graph->marked[vnode->code - 1] = 1;

    // 更新最短距离
    cur = adj;
    while (cur) {
      tmp = spath->dis[vnode->code - 1] + cur->distance;
      if (graph->marked[cur->code - 1] != 1 &&
          tmp < spath->dis[cur->code - 1]) {
        spath->dis[cur->code - 1] = tmp;
        spath->pre_visited[cur->code - 1] = vnode->code;
      }
      cur = cur->next;
    }
  }

  return OK;
}

int show_short_path(const graph_t *graph, const spath_t *spath, ver_code startv,
                    ver_code endv) {
  if (!graph)
    return GRAPH_NULL;
  if (!spath)
    return SPATH_NULL;
  if (!(graph->adj[startv - 1]))
    return VER_NOT_EXIST;
  if (graph->adj[startv - 1]->code == 0)
    return VER_NOT_EXIST;

  fprintf(stdout, "最短路径为: ");
  fprintf(stdout, "%s<--", graph->adj[endv - 1]->name);
  ver_code cur, v;
  cur = endv;
  while (spath->pre_visited[cur - 1] != startv) {
    v = spath->pre_visited[cur - 1];
    fprintf(stdout, "%s<--", graph->adj[v - 1]->name);
    cur = v;
  }
  fprintf(stdout, "%s\n", graph->adj[startv - 1]->name);

  return OK;
}