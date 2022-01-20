#include "../include/graph.h"
#include "../include/custom_err_msg.h"
#include "../include/list.h"
#include "../include/queue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

graph_t *init_graph(int ver_num) {
  if (ver_num > MAX_VER || ver_num < 1)
    return NULL;
  graph_t *graph;
  graph = (graph_t *)malloc(sizeof(graph_t));
  assert(graph);
  graph->marked = (int *)malloc(sizeof(int) * ver_num);
  assert(graph->marked);

  graph->ver_num = ver_num;

  for (int i = 0; i < ver_num; i++) {
    graph->adj[i] = init_list();
    graph->adj[i]->distance = 0; // 表示顶点到自身的距离为0
    graph->marked[i] = 0;
  }

  return graph;
}

int init_vertex(graph_t *graph, const ver_code ver, char *name, char *desc) {
  if (!graph)
    return GRAPH_NULL;
  if (ver < 1 || ver > MAX_VER || ver > graph->ver_num)
    return VER_CODE_ERR;
  if (graph->adj[ver - 1] && graph->adj[ver - 1]->name)
    return VER_EXIST;

  list_t *list;
  list = graph->adj[ver - 1];
  if (!list) {
    list = init_list();
    assert(list);
  }
  list->name = (char *)malloc(sizeof(char) * 1000);
  list->desc = (char *)malloc(sizeof(char) * 1000);

  strcpy(list->name, name);
  strcpy(list->desc, desc);
  list->code = ver;
  list->next = 0;

  graph->adj[ver - 1] = list;

  traverse(list);

  return OK;
}

int add_edge(graph_t *graph, const ver_code ver1, const ver_code ver2,
             const dist_t distance) {
  if (!graph)
    return GRAPH_NULL;
  if (ver1 < 1 || ver1 > MAX_VER || ver1 > graph->ver_num)
    return VER_CODE_ERR;
  if (ver2 < 1 || ver2 > MAX_VER || ver2 > graph->ver_num)
    return VER_CODE_ERR;
  if (!(graph->adj[ver1 - 1]) || !(graph->adj[ver1 - 1]))
    return VER_NOT_EXIST;
  if (graph->adj[ver1 - 1]->code == 0)
    return VER_NOT_EXIST;
  if (graph->adj[ver2 - 1]->code == 0)
    return VER_NOT_EXIST;
  if (graph->adj[ver1 - 1]->deleted == 1 || graph->adj[ver2 - 1]->deleted == 1)
    return VER_ALREADY_CLOSE;

  list_t *adj_1 = graph->adj[ver1 - 1];
  list_t *adj_2 = graph->adj[ver2 - 1];

  int stat_code;

  stat_code = add_node(adj_1, adj_2->name, adj_2->code, adj_2->desc, distance);
  if (stat_code < 0)
    return stat_code;
  stat_code = add_node(adj_2, adj_1->name, adj_1->code, adj_1->desc, distance);
  if (stat_code < 0)
    return stat_code;

  return OK;
}

int remove_edge(graph_t *graph, const ver_code ver1, const ver_code ver2) {
  if (!graph)
    return GRAPH_NULL;
  if (ver1 < 1 || ver1 > MAX_VER || ver1 > graph->ver_num)
    return VER_CODE_ERR;
  if (ver2 < 1 || ver2 > MAX_VER || ver2 > graph->ver_num)
    return VER_CODE_ERR;
  if (!(graph->adj[ver1 - 1]))
    return VER_NOT_EXIST;
  if (!(graph->adj[ver2 - 1]))
    return VER_NOT_EXIST;
  if (graph->adj[ver1 - 1]->code == 0)
    return VER_NOT_EXIST;
  if (graph->adj[ver2 - 1]->code == 0)
    return VER_NOT_EXIST;

  list_t *adj_1 = graph->adj[ver1 - 1];
  list_t *adj_2 = graph->adj[ver2 - 1];

  int stat_code;
  stat_code = remove_node(adj_1, ver2);
  if (stat_code < 0)
    return stat_code;
  stat_code = remove_node(adj_2, ver1);
  if (stat_code < 0)
    return stat_code;

  return OK;
}

int update_edge(graph_t *graph, const ver_code ver1, const ver_code ver2,
                const dist_t distance) {
  if (!graph)
    return GRAPH_NULL;
  if (ver1 < 1 || ver1 > MAX_VER || ver1 > graph->ver_num)
    return VER_CODE_ERR;
  if (ver2 < 1 || ver2 > MAX_VER || ver2 > graph->ver_num)
    return VER_CODE_ERR;
  if (!(graph->adj[ver1 - 1]))
    return VER_NOT_EXIST;
  if (!(graph->adj[ver2 - 1]))
    return VER_NOT_EXIST;
  if (graph->adj[ver1 - 1]->code == 0)
    return VER_NOT_EXIST;
  if (graph->adj[ver2 - 1]->code == 0)
    return VER_NOT_EXIST;

  list_t *adj_1;
  list_t *adj_2;
  int stat_code;

  adj_1 = graph->adj[ver1 - 1];
  adj_2 = graph->adj[ver2 - 1];

  stat_code = update_node(adj_1, ver2, distance);
  if (stat_code < 0)
    return stat_code;
  stat_code = update_node(adj_2, ver1, distance);
  if (stat_code < 0)
    return stat_code;

  return OK;
}

int remove_vertex(graph_t *graph, const ver_code ver) {
  if (!graph)
    return GRAPH_NULL;
  if (ver < 1 || ver > MAX_VER || ver > graph->ver_num)
    return VER_CODE_ERR;
  if (!graph->adj[ver - 1] || graph->adj[ver - 1]->code == 0)
    return VER_NOT_EXIST;

  list_t *adj;
  ver_code tmp_ver;
  int stat_code;

  adj = graph->adj[ver - 1];

  // 若顶点被标记为懒惰删除，需恢复其未懒惰删除前的状态
  if (adj->deleted == 1)
    restore_vertex(graph, ver);

  while ((tmp_ver = next_adj_vertex(adj)) != ADJ_VER_NOT_EXIST) {
    stat_code = remove_edge(graph, ver, tmp_ver);
    if (stat_code < 0)
      return stat_code;
  }

  free(adj);
  graph->adj[ver - 1] = NULL;

  return OK;
}

int vertex_info(graph_t *graph, ver_code ver) {
  if (!graph)
    return GRAPH_NULL;
  if (ver < 1 || ver > MAX_VER || ver > graph->ver_num)
    return VER_CODE_ERR;
  if (!(graph->adj[ver - 1]))
    return VER_NOT_EXIST;
  if (graph->adj[ver - 1]->code == 0)
    return VER_NOT_EXIST;

  list_t *adj;
  adj = graph->adj[ver - 1];

  return traverse(adj);
}

static node_t *pos; // 辅助变量，用以定位到邻接表的下一个节点
ver_code next_adj_vertex(list_t *list) {
  if (!list)
    return LIST_NULL;

  if (!pos)
    pos = list->next;
  else
    pos = pos->next;

  return pos ? pos->code : ADJ_VER_NOT_EXIST;
}

static node_t *subsequent; // 辅助变量，用以懒惰删除
int lazzy_remove_vertex(graph_t *graph, const ver_code ver) {
  if (!graph)
    return GRAPH_NULL;
  if (ver < 1 || ver > MAX_VER || ver > graph->ver_num)
    return VER_CODE_ERR;
  if (!(graph->adj[ver - 1]))
    return VER_NOT_EXIST;
  if (graph->adj[ver - 1]->code == 0)
    return VER_NOT_EXIST;
  if (graph->adj[ver - 1]->deleted == 1)
    return VER_ALREADY_CLOSE;

  list_t *adj, *adj_tmp;
  node_t *cur;
  int stat_code;

  adj = graph->adj[ver - 1];
  adj->deleted = 1;
  subsequent = adj->next;
  adj->next = NULL;

  cur = subsequent;
  while (cur) {
    adj_tmp = graph->adj[cur->code - 1];
    stat_code = lazzy_remove_node(adj_tmp, ver);
    if (stat_code < 0)
      return stat_code;
    cur = cur->next;
  }

  return OK;
}

int restore_vertex(graph_t *graph, const ver_code ver) {
  if (!graph)
    return GRAPH_NULL;
  if (ver < 1 || ver > MAX_VER || ver > graph->ver_num)
    return VER_CODE_ERR;
  if (!(graph->adj[ver - 1]))
    return VER_NOT_EXIST;
  if (graph->adj[ver - 1]->code == 0)
    return VER_NOT_EXIST;
  if (graph->adj[ver - 1]->deleted != 1)
    return VER_NOT_CLOSE;

  list_t *adj, *adj_tmp;
  node_t *cur;
  int stat_code;

  adj = graph->adj[ver - 1];
  adj->deleted = 0;
  adj->next = subsequent;
  cur = subsequent;

  while (cur) {
    adj_tmp = graph->adj[cur->code - 1];
    stat_code = restore_lazzy_remove_node(adj_tmp, ver);
    if (stat_code < 0)
      return stat_code;
    cur = cur->next;
  }

  subsequent = NULL;

  return OK;
}

int traverse_graph(graph_t *graph) {
  if (!graph)
    return GRAPH_NULL;

  list_t *adj;
  for (int i = 0; i < graph->ver_num; i++) {
    adj = graph->adj[i];
    if ((adj && adj->name) && adj->deleted != 1)
      traverse(adj);
  }

  return OK;
}

int BFS(graph_t *graph, vqueue_t *queue, ver_code startv) {
  if (!graph)
    return GRAPH_NULL;
  if (startv < 1 || startv > MAX_VER || startv > graph->ver_num)
    return VER_CODE_ERR;
  if (!(graph->adj[startv - 1]))
    return VER_NOT_EXIST;
  if (graph->adj[startv - 1] && graph->adj[startv - 1]->code == 0)
    return VER_NOT_EXIST;
  if (!queue)
    return QUEUE_NULL;

  init_marked(graph);

  list_t *adj;
  node_t *cur, *vnode;
  int stat_code;
  adj = graph->adj[startv - 1];
  if (!adj)
    return EDGE_NOT_EXIST;

  put_queue(queue, adj);
  while (is_empty(queue) != ELEM_IS_NULL) {
    stat_code = pop_queue(queue, &vnode);
    if (stat_code < 0)
      return stat_code;
    if (graph->marked[vnode->code - 1] == 1)
      continue;

    fprintf(stdout, "景点:%s\t景点代码:%d\t景点简介:%s\n", vnode->name,
            vnode->code, vnode->desc);
    graph->marked[vnode->code - 1] = 1;
    adj = graph->adj[vnode->code - 1];
    cur = adj->next;
    while (cur) {
      put_queue(queue, cur);
      cur = cur->next;
    }
  }

  return OK;
}

int DFS(graph_t *graph, vstack_t *stack, ver_code startv) {
  if (!graph)
    return GRAPH_NULL;
  if (!stack)
    return STACK_NULL;
  if (startv < 1 || startv > MAX_VER || startv > graph->ver_num)
    return VER_CODE_ERR;
  if (!(graph->adj[startv - 1]))
    return VER_NOT_EXIST;
  if (graph->adj[startv - 1]->code == 0)
    return VER_NOT_EXIST;

  init_marked(graph);

  list_t *adj, *cur, *tmp;
  node_t *vnode;
  int stat_code, *marked;

  adj = graph->adj[startv - 1];
  marked = graph->marked;

  push_stack(stack, adj);
  while (stack_is_empty(stack) != ELEM_IS_NULL) {
    stat_code = pop_stack(stack, &vnode);
    if (stat_code < 0)
      return stat_code;

    if (graph->marked[vnode->code - 1] != 0)
      continue;

    fprintf(stdout, "景点:%s\t景点代码:%d\t景点简介:%s\n", vnode->name,
            vnode->code, vnode->desc);

    marked[vnode->code - 1] = 1; // 标记出栈节点已访问

    // 当前包含景点信息的节点的邻接表
    adj = graph->adj[vnode->code - 1];
    cur = adj->next;

    // 如果当前包含景点信息的节点以访问过，则跳到当前邻接表的下一个邻接节点；反之，则跳到与当前节点相邻的节点
    while (cur && marked[cur->code - 1] == 1) {
      cur = cur->next;
    }
    if (!cur)
      continue;

    // FIXME
    // tmp = cur->next;
    tmp = cur;
    while (tmp) {
      if (marked[tmp->code - 1] != 1) {
        stat_code = push_stack(stack, tmp);
        if (stat_code < 0)
          return stat_code;
      }
      tmp = tmp->next;
    }
    // stat_code = push_stack(stack, cur);
    // if (stat_code < 0)
    //   return stat_code;
  }

  return OK;
}

int init_marked(graph_t *graph) {
  if (!graph)
    return GRAPH_NULL;

  int i;
  for (i = 0; i < graph->ver_num; i++)
    graph->marked[i] = 0;

  return OK;
}

int valid_init_vertex_count(graph_t *graph) {
  if (!graph)
    return GRAPH_NULL;

  int inited_count, ver;
  list_t *adj;
  for (inited_count = 0, ver = 0; ver < graph->ver_num; ver++) {
    adj = graph->adj[ver];
    if (adj && adj->name)
      inited_count += 1;
  }

  return graph->ver_num - inited_count;
}