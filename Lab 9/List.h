/*
 * List
 *
 *  Created on: Apr 13, 2024
 *      Author: Ashton
 */

#ifndef LIST_H_
#define LIST_H_


struct list_node{
    struct list_node* next;
    struct list_node* previous;
    struct card* card_pointer;
};
#define list_node list_node_t


struct list{
    struct list_node* head;
    struct list_node* tail;
    uint32_t length;
};
#define list


struct card{
    uint8_t value; // Card Number - 0-9 - Numbers, 10 - Skip, 11 - Reverse, 12 - Draw Two, 13 - Wild (any)
    uint8_t color; // 0 - Red, 1 - Yellow, 2 - Blue, 3 - Green
    uint8_t power; // 0 - Nothing, 1 - Skip Turn, 2 - Draw Two, 3 - Wild, 4 - Wild +4
    uint8_t in_deck; // 0 - discard, 1 - in deck, 2 - User Hand, 3 - Opponent Hand
    uint16_t* image_pointer // Pointer to Spirit Image
    int32_t x_position // Sprite x position
    int32_t y_position // Sprite y position
    int32_t x_velocity // Sprite x velocity
    int32_t y_velocity // Sprite y velocity
};
#define card card_t














// Function Declarations
void list_init(void);
void list_add(list* host_list, card* added_card);
void list_remove(list* host_list, list_node* removed_node);













#endif /* LIST_H_ */
