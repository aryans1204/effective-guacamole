#ifndef __GRAPH__
#define __GRAPH__

#include "gluethreads/glthread.h"
#include <assert.h>

#define uint unsigned int

#define IF_NAME 20
#define NODE_NAME 16
#define MAX_INTFS_PER_NODE 20
#define MAX_TOPO_NAME 32

typedef struct node_ node_t;
typedef struct link_ link_t;

typedef struct interface_ {
  char if_name[IF_NAME];
  struct node_* node;
  struct link_* link;
} interface_t;

struct link_ {
  interface_t intf1;
  interface_t intf2;
  uint cost;
};

struct node_ {
  char node_name[NODE_NAME];
  interface_t *intfs[MAX_INTFS_PER_NODE];
  glthread_t glue_node;
};

typedef struct graph_ {
  char topology_name[MAX_TOPO_NAME];
  glthread_t node_list;
} graph_t;

static inline node_t* get_nbr_node(interface_t* interface) {
  assert(interface->node);
  assert(interface->link);

  link_t* l = interface->link;
  if (&(l->intf1) == interface) return l->intf2.node;
  return l->intf1.node;
}

static inline int get_node_intf_available_slot(node_t* node) {
  for (int i = 0; i < MAX_INTFS_PER_NODE; i++) {
    if (node->intfs[i] == NULL) return i;
  }
  return -1;
}

