#ifndef STACK_H
#define STACK_H 1

#include "list.h"

/**
 * @brief
 * 链栈。用于图的深度优先遍历，链栈中每个节点的数据域为图中包含景点信息的景点节点。压栈和出栈操作算法实现时间复杂度为O(1)。即以单链表实现的栈，压栈时，链表头节点指向新压栈元素，而新压栈元素指向其未入栈时链表头节点指向的元素，以实现链表指向的元素节点充当栈的栈顶。
 *
 */
typedef struct vstack {
  node_t *vnode;
  struct vstack *next;
} vstack_t, snode_t;

/**
 * @brief 初始化链栈
 *
 * @return vstack_t*
 */
vstack_t *init_stack();

/**
 * @brief 将图中包含景点信息的节点放入栈中。
 *
 * @param stack
 * @param vnode
 * @return int
 */
int push_stack(vstack_t *stack, node_t *vnode);

/**
 * @brief 元素出栈
 *
 * @param stack
 * @param vnode 二级指针，存储待出栈的包含景点信息的元素节点
 * @return int
 */
int pop_stack(vstack_t *stack, node_t **vnode);

/**
 * @brief 判断链栈是否为空
 * 
 * @param stack 
 * @return int 
 */
int stack_is_empty(vstack_t *stack);

#endif