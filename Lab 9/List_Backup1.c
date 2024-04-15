/*
 * List.c
 *
 *  Created on: Apr 13, 2024
 *      Author: Ashton
 *
 *      This file sets up the linked list
 */


#include "List.h"
#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>

void list_init(list_t* host_list){
    host_list->head = NULL;
    host_list->tail = NULL;
    host_list->length = 0;
}



void list_add(list_t* host_list,list_node_t* added_node){
    if(host_list->head == NULL){
        host_list->head = added_node;
        host_list->tail = added_node;
        host_list->length++;
        return;
    }

    host_list->tail->next = added_node;
    added_node->previous = host_list->tail;
    added_node->next = NULL;
    host_list->tail = added_node;
    host_list->length++;
}

void list_remove(list_t* host_list,list_node_t* removed_node){
    removed_node->previous->next = removed_node->next;
    if(host_list->tail == removed_node){
        host_list->tail = removed_node->previous;
    }
    if(host_list->head == removed_node){
        host_list->head = removed_node->next;
    }
    host_list->length = host_list->length+1;
    // Nothing References this node, therefore it is fine that the next and previous point to initial nodes
    // We will overwrite this when we add to next list
}

list_node_t *get_first_node(list_t* host_list) {
    return NULL;
}



