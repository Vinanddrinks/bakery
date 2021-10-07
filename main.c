//
// Created by Vinanddrinks,Riccardis and Djay on 07/10/2021.
//
#include "stdlib.h"
#include "stdio.h"
#include "bakery.h"
int main(){
    char * Tastes[7] = {"Chocolate", "Vanilla", "Apple", "Fudge", "Strawberry", "Banana","Orange"};
    allocs = 0;
    Element_str* l_tastes;
    Order_Queue* q_orders = (Order_Queue*)malloc(sizeof(Order_Queue));
    ++allocs;
    q_orders->all_orders_head = NULL;
    Tasting_Queue* q_tasting = (Tasting_Queue*)malloc(sizeof(Tasting_Queue));
    ++allocs;
    q_tasting->all_cakes_head = NULL;
    l_tastes = initialize_tastes(7,"Chocolate", "Vanilla", "Apple", "Fudge", "Strawberry", "Banana","Orange");
    display_list_Element_str(l_tastes);
    printf("%d\n",size_of_element_str(l_tastes));
    pass_order("CCAC", q_orders);
    display_list_Element_str(q_orders->all_orders_head);
//    free_list_Element_str(l_tastes);

//    printf("%s->", l_tastes->text);
//    l_tastes=l_tastes->next;
//    printf("%s->", l_tastes->text);
//    l_tastes=l_tastes->next;
//    printf("%s->", l_tastes->text);
//    l_tastes=l_tastes->next;
//    printf("%s->", l_tastes->text);
//    l_tastes=l_tastes->next;
//    printf("%s->", l_tastes->text);
//    l_tastes=l_tastes->next;
    printf("current dynamic memory allocated : %d \n",allocs);
    return 0;
}