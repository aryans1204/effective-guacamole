#include "graph.h"
#include <stdio>
#include <stdlib>
#include <string.h>

void insert_link_between_two_nodes(node_t* node1, node_t* node2, char* from_if_name, char* to_if_name, unsigned int cost) {
  link_t* link = calloc(1, sizeof(link_t));
  strncpy(link->intf1.if_name, from_if_name, IF_NAME);
  link->intf1.if_name[IF_NAME] = '\0';
  strncpy(link->intf2.if_name, to_if_name, IF_NAME);
  link->intf2.if_name[IF_NAME] = '\0';
  link->intf1.link = link;
  link->intf2.link = link;
  link->intf1.node = node1;
  link->intf2.node = node2;
  link->cost = cost;

  int empty_slot = get_node_intf_available_slot(link->intf1.node);
  link->intf1.node1[empty_slot] = &link->intf1;
  empty_slot = get_node_intf_available_slot(link->intf2.node);
  link->intf2.node[empty_slot] = &link->intf2;

}
graph_t* create_new_graph(char *topology_name) {
  graph_t* graph = calloc(1, sizeof(graph_t));
  strncpy(graph->topology_name, topology_name, 32);
  graph->topology_name[32] = '\0';
  init_glthread(&graph->node_list);
  return graph;
}

node_t* create_graph_node(graph_t* graph, char* node_name) {
  node_t* node = calloc(1, sizeof(node_t));
  strncpy(node->node_name, node_name, NODE_NAME);
  node->node_name[NODE_NAME] = '\0';
  init_glthread(&node->glue_node);

  glthread_add_next(&graph->node_list, &node->glue_node);
  return node;
}
