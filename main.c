//
// Created by Vinanddrinks,Riccardis and Djay on 07/10/2021.
//
#include "stdlib.h"
#include "stdio.h"
#include "bakery.h"
int main(){
    allocs = 0;
    Element_str* l_tastes;
    Order_Queue* q_orders = (Order_Queue*)malloc(sizeof(Order_Queue));
    ++allocs;
    q_orders->all_orders_head = NULL;
    Tasting_Queue* q_tasting = (Tasting_Queue*)malloc(sizeof(Tasting_Queue));
    ++allocs;
    q_tasting->all_cakes_head = NULL;
    l_tastes = initialize_tastes(7,"Chocolate", "Vanilla", "Apple", "Fudge", "Strawberry", "Banana","Orange");
    //display_list_Element_str(l_tastes);
    printf("%d\n",size_of_element_str(l_tastes));
    pass_order("CSV", q_orders);
//    display_list_Element_str(q_orders->all_orders_head);
//    display_list_Element_str(q_orders->all_orders_head);
    Element_str* hello = process_order(q_orders);
//    display_list_Element_str(hello);
    Cake* cake = create_cake(hello);
    display_list_Element_str(cake->order);
//    display_list_Element_str(cake->s_tastes->real_tastes);
    build_cake(cake, l_tastes);
    display_list_Element_str(cake->s_tastes->real_tastes);
    q_tasting->all_cakes_head=NULL;
    deliver(cake, q_tasting);
    display_list_Element_str(q_tasting->all_cakes_head->cake->s_tastes->real_tastes);
//    display_list_Element_str(hello);
    q_tasting = NULL;
    tasting(q_tasting, 3);


    free_list_Element_str(l_tastes);
//    free_list_Element_str(hello);
    free_list_Element_str(q_orders->all_orders_head);
    free(q_orders);
    --allocs;
    free(q_tasting);
    --allocs;
//    free_list_Element_str(cake->s_tastes->real_tastes);
//    free(cake->s_tastes);
//    --allocs;
//    free(cake);
//    --allocs;
//    free(l_tastes);
//    -- allocs;



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