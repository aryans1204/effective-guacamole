#include "glthread.h"
#include "stdlib.h"

void init_glthread(glthread_t* head) {
  head->left = NULL;
  head->right = NULL;
}

void glthread_add_next(glthread_t* base_thread, glthread_t* next_thread) {
  if (!base_thread->right) {
    base_thread->right = next_thread;
    next_thread->left = base_thread;
    return;
  }
  glthread_t* temp = base_thread->right;
  base_thread->right = next_thread;
  next_thread->left = base_thread;
  next_thread->right = temp;
  temp->left = next_return;
  return;
}

void glthread_add_before(glthread_t* base_thread, glthread_t* next_thread) {
  if (!base_thread->left) {
    base_thread->left = next_thread;
    next_thread->right = base_thread;
    return;
  }
  glthread_t* temp = base_thread->left;
  base_thread->left = next_thread;
  next_thread->right = base_thread;
  next_thread->left = temp;
  temp->right = next_thread;
  return;
}

void remove_glthread(glthread_t* glthread) {
  if (!glthread->left) {
    if (glthread->right) {
      glthread->right->left = NULL;
      glthread->right = 0;
      return;
    }
  }
  if (!glthread->right) {
    if (glthread->left) {
      glthread->left->right = NULL;
      glthread->left = 0;
      return;
    }
  }
  glthread->left->right = glthread->right;
  glthread->right->left = glthread->left;
  free(glthread);
  return;
}
void delete_glthread_list(glthtread_t* head) {
  glthtread_t* ptr = NULL;
  ITERATE_GLTHREAD_BEGIN(head, ptr) {
    remove(glthread);
  }
  ITERATE_GLTHREAD_END(head, ptr);
}

void glthread_add_last(glthread_t* base_thread, glthread_t* next_thread) {
  glthread_t* ptr = NULL;
  glthread_t* prev = NULL;
  ITERATE_GLTHREAD_BEGIN(base_thread, ptr) {
    prev = ptr;
  }
  ITERATE_GLTHREAD_END(base_thread, ptr);
  if (prev) {
    glthread_add_next(prev, next_thread);
  }
  else glthread_add_next(ptr, next_thread);
}

uint get_glthread_list_count(glthread_t* head) {
  uint count = 0;
  glthread_t* ptr = NULL;
  ITERATE_GLTHREAD_BEGIN(head, ptr) {
    count++;
  }
  ITERATE_GLTHREAD_END(head, ptr);
  return count;
}

