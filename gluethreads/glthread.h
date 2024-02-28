#ifndef __GLUETHREAD__
#define __GLUETHREAD__

#define uint unsigned int
typedef struct glthread_node {
  glthread_node *left;
  glthread_node *right;
} glthread_t;


void glthread_add_next(glthread_t* base_thread, glthread_t* next_thread); //add next_thread after base_thread
void glthread_add_before(glthread_t* base_thread, glthread_t* next_thread); //add next_thread before base_thread;
void remove_glthread(glthread_t* glthread); //remove glthread
void glthread_add_last(glthread_t* base_thread, glthread_t* next_thread); //add glthread to end of list
void init_glthread(glthread_t* head);

#define IS_GLTHREADLIST_EMPTY(head) ((head->right == 0 && head->left == 0));

#define GLTHREAD_TO_STRUCT(fn_name, struct_name, field_name) \
  static inline (struct_name)* fn_name(glthread_t* gptr) {
    return (struct_name*)((char*)gptr (char*)&(((struct_name*)0)->field_name));
  }

#define BASE(glthread) ((glthread)->right);

#define ITERATE_GLTHREAD_BEGIN(head, gltarget) {
  glthread_t* tmp = NULL;
  glthread_t* headfirst = BASE(head);

  for (; gltarget != NULL; gltarget=tmp) {
    tmp = gltarget->right;

#define ITERATE_GLTHREAD_END(head, gltarget)
  }
}

#define GLTHREAD_GET_USER_DATA_FROM_OFFSET(head, offset) \
  (void*)((char*)head - offset)

void delete_glthread_list(glthread_t* head);
uint get_glthread_list_count(glthread_t* head);
void glthread_priority_insert(glthread_t* head, glthread_t* target, int*(comp)(void*, void*), int offset);

if #0
void* gl_thread_search(glthread_t* head, void*(*thread_to_struct_fn)(glthread_t*), void* key, int (*comp)(void*, void*));

#endif


