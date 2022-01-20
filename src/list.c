#include "../include/list.h"
#include "../include/custom_err_msg.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

list_t *init_list() {
  list_t *list;
  list = (list_t *)malloc(sizeof(list_t));
  assert(list);

  list->name = 0;
  list->code = 0;
  list->desc = 0;
  list->distance = N;
  list->deleted = 0;
  list->next = 0;

  return list;
}

int add_node(list_t *list, char *name, const ver_code ver, char *desc,
             const dist_t distance) {
  if (!list)
    return LIST_NULL;

  node_t *back, *cur;
  back = list;
  cur = list->next;
  while (cur) {
    if (cur->code == ver)
      return EDGE_EXIST;
    else if (cur->deleted == 1) {
      return VER_ALREADY_CLOSE;
    }
    back = cur;
    cur = cur->next;
  }

  node_t *node = (node_t *)malloc(sizeof(node_t));
  assert(node);
  node->name = name;
  node->code = ver;
  node->desc = desc;
  node->distance = distance;
  node->next = 0;

  back->next = node;

  return OK;
}

int remove_node(list_t *list, const ver_code ver) {
  if (!list)
    return LIST_NULL;

  node_t *pre, *cur;

  pre = list;
  cur = pre->next;
  while (cur) {
    if (cur->code == ver) {
      pre->next = cur->next;
      free(cur);
      return OK;
    }
    pre = cur;
    cur = cur->next;
  }

  return ADJ_VER_NOT_EXIST;
}

int update_node(list_t *list, const ver_code ver, dist_t distance) {
  if (!list)
    return LIST_NULL;

  node_t *cur;
  cur = list->next;

  while (cur) {
    if (cur->deleted == 1)
      return VER_ALREADY_CLOSE;
    else if (cur->code == ver) {
      cur->distance = distance;
      return OK;
    }
    cur = cur->next;
  }

  return EDGE_NOT_EXIST;
}

int lazzy_remove_node(list_t *list, const ver_code ver) {
  if (!list)
    return LIST_NULL;

  node_t *cur;
  cur = list->next;
  while (cur) {
    if (cur->code == ver) {
      cur->deleted = 1;
      return OK;
    }
    cur = cur->next;
  }

  return EDGE_NOT_EXIST;
}

int restore_lazzy_remove_node(list_t *list, const ver_code ver) {
  if (!list)
    return LIST_NULL;

  node_t *cur;
  cur = list->next;
  while (cur) {
    if (cur->code == ver) {
      cur->deleted = 0;
      return OK;
    }
    cur = cur->next;
  }

  return EDGE_NOT_EXIST;
}

int traverse(list_t *list) {
  if (!list)
    return LIST_NULL;
  if (list->deleted == 1) {
    fprintf(stdout, "景点%s已关闭\n", list->name);
    return VER_ALREADY_CLOSE;
  }

  list_t *cur;
  cur = list->next;

  fprintf(stdout, "顶点名称: %s\t顶点代码:%d\t顶点简介%s\n", list->name,
          list->code, list->desc);
  if (!cur)
    fprintf(stdout, "%s无相邻顶点\n", list->name);
  else {
    fprintf(stdout, "%s相邻顶点信息:\n", list->name);
    while (cur) {
      if (cur->deleted != 1)
        fprintf(stdout,
                "\t\t顶点名称: %s\t顶点代码:%d\t顶点简介%s\t与%s距离%ld\n",
                cur->name, cur->code, cur->desc, list->name, cur->distance);
      else
        fprintf(stdout, "\t\t景点%s已关闭\n", cur->name);
      cur = cur->next;
    }
  }

  return OK;
}