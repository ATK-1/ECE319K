/*
 * List
 *
 *  Created on: Apr 13, 2024
 *      Author: Ashton
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>

typedef enum {deck,user,opp,dis} status_t;
typedef enum {red,yellow,blue,green,wild_color} color_t;
typedef enum {zero,one,two,three,four,five,six,seven,eight,nine,skip,reverse,draw_two,wild} value_t;
typedef enum {nothing,skip_turn,plus_two,change_color,plus_four} power_t;

struct list_node{
    struct list_node* next;
    struct list_node* previous;
    struct card* card_pointer;
};
typedef struct list_node list_node_t;


struct list{
    struct list_node* head;
    struct list_node* tail;
    uint32_t length;
    status_t id;
};
typedef struct list list_t;


struct card{ // Potentially add page variable
    value_t value; // Card Number - 0-9 - Numbers, 10 - Skip, 11 - Reverse, 12 - Draw Two, 13 - Wild (any)
    color_t color; // 0 - Red, 1 - Yellow, 2 - Blue, 3 - Green
    power_t power; // 0 - Nothing, 1 - Skip Turn, 2 - Draw Two, 3 - Wild, 4 - Wild +4
    status_t in_deck; // 0 - discard, 1 - in deck, 2 - User Hand, 3 - Opponent Hand
    uint8_t global_index; // Index sent between devices
    uint8_t page; // Only for when in user's hand
    uint8_t position; // determining where on page
};
typedef struct card card_t;














// Function Declarations
void list_init(list_t* host_list);
void list_add(list_t* host_list,list_node_t* added_node);
void list_remove(list_t* host_list,list_node_t* removed_node);
list_node_t* get_first_node(list_t* host_list);
list_node_t* list_traverse(list_node_t* initial_node);












#endif /* LIST_H_ */
