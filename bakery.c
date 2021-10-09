//
// Created by Vinanddrinks on 07/10/2021.
//
#include "bakery.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"
Element_str* create_taste(char order[50]){
    Element_str* new_taste = (Element_str*)malloc(sizeof(Element_str));
    allocs++;
    strcpy(new_taste->text, order);
    new_taste->next = NULL;
    return new_taste;
}
void display_list_Element_str(Element_str* tastes){
    if (tastes != NULL){
        printf("%s->",tastes->text);
        display_list_Element_str(tastes->next);
    }else{
        printf("NULL\n");
    }
}
void free_list_Element_str(Element_str* tastes){
    if (tastes!=NULL) {
        free_list_Element_str(tastes->next);
        free(tastes);
        allocs--;
    }
}
Element_str* initialize_tastes(int size, ...){
    Element_str* tastes_list = NULL,*head = NULL;
    va_list valist;
    va_start(valist,size);
    head = create_taste(va_arg(valist,char*));
    tastes_list = head;
    for(int i = 1; i < size;++i){
        tastes_list->next = create_taste(va_arg(valist,char *));
        tastes_list = tastes_list->next;
    }
    va_end(valist);
    return head;
}
// gives us the real size of our elements_str list
int size_of_element_str(Element_str* tastes) {
    if (tastes != NULL) {
        return 1 + size_of_element_str(tastes->next);
    }else return 0;
}
void pass_order(char order[50], Order_Queue* f_orders) {
    if (size_of_element_str(f_orders->all_orders_head)<10) {
        Element_str *new = create_taste(order);
        new->next = f_orders->all_orders_head;
        f_orders->all_orders_head = new;
    }
}

char* taste_processor(char taste){
    // This function is used as a translator for our existing tastes
    switch (taste) {
        case 'C' :
            return "Chocolate";
        case 'V' :
            return "Vanilla";
        case 'S':
            return "Strawberry";
        case 'O' :
            return "Orange";
        case 'A' :
            return "Apple";
        case 'B':
            return "Banana";
        case 'F' :
            return "Fudge";
        default:
            return "Unknown Taste";
    }
}
Element_str* process_order(Order_Queue* q_orders){
    if (q_orders != NULL && q_orders->all_orders_head != NULL){
        Order_Queue* temp = q_orders;
        // If we do not have any problems we find the oldest order in our order queue
        while (temp->all_orders_head->next != NULL) {
            temp->all_orders_head = temp->all_orders_head->next;
        }
        Element_str* processed_order;
        int i = 1 ;
        // We create the first element of the order
        processed_order = create_taste(taste_processor(temp->all_orders_head->text[0]));
        Element_str* temp1 = processed_order;
        // We fill the order with all the other tastes the client asked
        while (temp->all_orders_head->text[i] != '\0'){
            temp1->next = create_taste(taste_processor(temp->all_orders_head->text[i]));
            temp1 = temp1->next;
            i++;
        }
        // We return the head of processed order
        return processed_order;
    }
}
Cake* create_cake(Element_str* processed_order){
    // This function creates an empty cake associated with the processed order sent as a parameters
    Cake* empty_cake = (Cake*)malloc(sizeof(Cake));
    allocs++;
    empty_cake->order = processed_order;
    empty_cake->s_tastes = (Taste_Stack*)malloc(sizeof (Taste_Stack));
    empty_cake->s_tastes->real_tastes = NULL;
    allocs++;
    return empty_cake;
}

int is_in_stock(Element_str* taste, Element_str* l_tastes){
    // function to check if a taste is within the taste list
    if(l_tastes != NULL){
        if(strcmp(taste->text, l_tastes->text) == 0){
            return 1;
        }else return is_in_stock(taste,l_tastes->next);
    }else return 0;
}
void add_to_cake(Cake* cake, Element_str* taste){
    //function that add a cake slice in the stack
    if (cake != NULL && taste != NULL) {
        Element_str *new = create_taste(taste->text);
        Element_str *temp = cake->s_tastes->real_tastes;
        cake->s_tastes->real_tastes = new;
        new->next = temp;
    }
}
void build_cake(Cake* cake, Element_str* l_tastes) {
    //the pastry function that build the cake from the comprehensive order
    if (cake != NULL && l_tastes != NULL){
        Element_str * temp = cake->order;
        while(temp != NULL){

            if (is_in_stock(temp, l_tastes) == 1){
                add_to_cake(cake, temp);
            }
                temp = temp->next;
        }
    }
}
Element_cake * create_element_cake(Cake* cake){
    if(cake!=NULL){
        Element_cake* new = (Element_cake*)malloc(sizeof(Element_cake));
        new->cake = cake;
        new->next = NULL;
        return new;
    }
}
void deliver(Cake* cake, Tasting_Queue* q_tasting){
    // We only deliver when we finished the cake
    if (cake != NULL && q_tasting != NULL){
        // We can throw away the cake order
        free_list_Element_str(cake->order);
        // If Tasting Queue is not NULL we create a temp to go through the list until the before last element
            if(q_tasting->all_cakes_head != NULL) {
                Element_cake * temp = q_tasting->all_cakes_head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                // We add the cake in the last position
                temp->next = create_element_cake(cake);
            }
            // If Tasting Queue is NULL we put the cake in the first position
            else {
                q_tasting->all_cakes_head = create_element_cake(cake);
            }
    }
}
void tasting(Tasting_Queue* q_tasting, int nb_parts){
    //Todo

}