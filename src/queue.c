#include "../include/queue.h"
#include "../include/custom_err_msg.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

vqueue_t *init_queue() {
  vqueue_t *queue;
  queue = (vqueue_t *)malloc(sizeof(vqueue_t));
  assert(queue);

  queue->size = 0;
  queue->front = (qnode_t *)malloc(sizeof(qnode_t));
  assert(queue->front);

  queue->front->next = 0;
  queue->front->vnode = 0;
  queue->rear = queue->front;

  return queue;
}

int put_queue(vqueue_t *queue, node_t *vnode) {
  if (!queue)
    return QUEUE_NULL;

  qnode_t *node;
  node = (qnode_t *)malloc(sizeof(qnode_t));
  assert(node);

  node->vnode = vnode;
  node->next = 0;

  queue->rear->next = node;
  queue->rear = queue->rear->next;
  queue->size += 1;

  return OK;
}

int pop_queue(vqueue_t *queue, node_t **vnode) {
  if (!queue)
    return QUEUE_NULL;

  if (queue->front == queue->rear)
    return ELEM_IS_NULL;

  qnode_t *qnode;
  qnode = queue->front->next;
  *vnode = qnode->vnode;

  queue->front = qnode;
  queue->size -= 1;

  return OK;
}

int output_queue(vqueue_t *queue) {
  if (!queue)
    return QUEUE_NULL;

  if (queue->front == queue->rear)
    return ELEM_IS_NULL;

  qnode_t *qnode;
  node_t *vnode;
  qnode = queue->front->next;
  while (qnode != queue->rear) {
    vnode = qnode->vnode;
    if (vnode->deleted == 1)
      fprintf(stdout, "景点%s已关闭\n", vnode->name);
    else
      fprintf(stdout, "景点:%s\t景点代码:%d\t景点简介:%s\n", vnode->name,
              vnode->code, vnode->desc);
    qnode = qnode->next;
  }

  return OK;
}

int is_empty(vqueue_t *queue) {
  if (!queue)
    return QUEUE_NULL;

  return queue->rear != queue->front ? ELEM_NOT_NULL : ELEM_IS_NULL;
}

int clean_queue(vqueue_t *queue) {
  if (!queue)
    return QUEUE_NULL;

  queue->rear = queue->rear->next;
  queue->front = queue->rear;

  return OK;
}