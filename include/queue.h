#ifndef QUEUE_H
#define QUEUE_H 1

#include "list.h"

typedef struct queue_node {
  node_t *vnode;
  struct queue_node *next;
} qnode_t;

typedef struct queue {
  int size;
  qnode_t *front;
  qnode_t *rear;
} vqueue_t;

/**
 * @brief 初始化队列
 *
 * @return queue_t*
 */
vqueue_t *init_queue();

/**
 * @brief 将景点节点入队
 *
 * @param queue 指向分配内存后的队列的指针
 * @param vnode 指向景点节点的指针
 * @return int
 */
int put_queue(vqueue_t *queue, node_t *vnode);

/**
 * @brief 将非空队列内的元素即含景点节点的节点出队
 *
 * @param queue 指向分配内存后的队列的指针
 * @param vnode 存储景点信息的元素节点
 * @return int
 */
int pop_queue(vqueue_t *queue, node_t **vnode);

/**
 * @brief 判断队列是否为空，若是返回OK，否则返回QUEUE_ELEM_NOT_NULL。
 *
 * @param queue 指向分配内存后的队列的指针
 * @return int
 */
int is_empty(vqueue_t *queue);

/**
 * @brief 清空队列
 *
 * @param queue 指向分配内存后的队列的指针
 * @return int
 */
int clean_queue(vqueue_t *queue);

#endif