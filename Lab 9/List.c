/*
 * List.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Ashton
 *
 *      This file sets up the linked list
 */

void list_init(void){
  // write this
};



void list_add(struct list* host_list,struct list_node* added_node){
    host_list->tail->next = added_node;
    added_node->previous = host_list->tail;
    added_node->next = NULL;
    host_list->tail = added_node;
    length++;
}

void list_remove(struct list* host_list,struct list_node* removed_node){
    removed_node->previous->next = removed_node->next;
    if(host_list->tail == removed_node){
        host_list->tail = removed_node->previous;
    }
    if(host_list->head == removed_node){
        host_list->head = removed_node->next;
    }
    // Nothing References this node, therefore it is fine that the next and previous point to initial nodes
    // We will overwrite this when we add to next list
}
