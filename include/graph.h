#ifndef __GRAPH__
#define __GRAPH__

#include "gluethreads/glthread.h"
#include <assert.h>
#include <string.h>

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
GLTHREAD_TO_STRUCT(graph_glue_to_node, node_t, glue_node);

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
  for (int i = 0; i < MAX_INTFS_PE
         R_NODE; i++) {
    if (node->intfs[i] == NULL) return i;
  }
  return NULL;
}

static inline interface_t* get_node_if_by_name(node_t* node, char* if_name) {
  interface_t* ints[MAX_INTFS_PER_NODE] = node->intfs;
  for (int i = 0; i < MAX_INTFS_PER_NODE; i++) {
    if (!ints[i]) return NULL;
    if (!strncmp(ints[i]->if_name, if_name, IF_NAME)) return ints[i];
  }
  return NULL;
}

static inline node_t* get_node_by_node_name(graph_t* topo, char* node_name) {
  glthread_t* head = &topo->node_list;
  glthread_t* temp = NULL;
  node_t* ans = NULL;
  ITERATE_GLTHREAD_BEGIN(head, temp) {
    ans = graph_glue_to_node(temp);
    if (!strncmp(ans->node_name, node_name, NODE_NAME)) return ans; 
  }
  ITERATE_GLTHREAD_END(head, temp);
  return NULL;
}
