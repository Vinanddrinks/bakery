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
        --allocs;
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
Element_str* process_order(Order_Queue* q_orders){
    //Todo
}
Cake* create_cake(Element_str* order){
    //Todo
}
void build_cake(Cake* cake, Element_str* l_tastes) {
    //Todo
}
void deliver(Cake* cake, Tasting_Queue* q_tasting){
    //Todo
}
void tasting(Tasting_Queue* q_tasting, int nb_parts){
    //Todo
}