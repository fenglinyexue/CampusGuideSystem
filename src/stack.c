#include "../include/stack.h"
#include "../include/custom_err_msg.h"
#include <assert.h>
#include <stdlib.h>

vstack_t *init_stack() {
  vstack_t *stack;
  stack = (vstack_t *)malloc(sizeof(vstack_t));
  assert(stack);

  stack->vnode = 0;
  stack->next = 0;

  return stack;
}

int push_stack(vstack_t *stack, node_t *vnode) {
  if (!stack)
    return STACK_NULL;

  snode_t *snode;
  snode = (snode_t *)malloc(sizeof(snode_t));
  assert(snode);

  snode->vnode = vnode;
  snode->next = stack->next;

  stack->next = snode;

  return OK;
}

int pop_stack(vstack_t *stack, node_t **vnode) {
  if (!stack)
    return STACK_NULL;

  int stat;
  stat = stack_is_empty(stack);
  if (stat < 0)
    return stat;

  snode_t *snode;
  snode = stack->next;

  *vnode = snode->vnode;
  stack->next = snode->next;

  return OK;
}

int stack_is_empty(vstack_t *stack) {
  if (!stack)
    return STACK_NULL;

  return stack->next ? ELEM_NOT_NULL : ELEM_IS_NULL;
}