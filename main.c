//
// Created by Vinanddrinks,Riccardis and Djay on 07/10/2021.
//
// Vincent Labouret, Giuliano Riccardi, Joseph Beaumont - L2 INT2

#include "stdlib.h"
#include "stdio.h"
#include "bakery.h"

int main(){
    // We used a global variable "allocs" to keep a track of our memory allocations and to make sure we do not have any
    // memory leaks
    allocs = 0;
    // We define permanent variables
    Element_str* l_tastes;
    Order_Queue* q_orders = (Order_Queue*)malloc(sizeof(Order_Queue));
    ++allocs;
    q_orders->all_orders_head = NULL;
    Tasting_Queue* q_tasting = (Tasting_Queue*)malloc(sizeof(Tasting_Queue));
    ++allocs;
    q_tasting->all_cakes_head = NULL;
    l_tastes = initialize_tastes(7,"Chocolate", "Vanilla","Apple", "Fudge", "Strawberry", "Banana","Orange");
    // We begin to test our coded functions
    printf("Here's the list of available tastes:\n");
    display_list_Element_str(l_tastes);
    printf("The number of available tastes is : %d.\n",size_of_element_str(l_tastes));
    pass_order("CBSSSBAAV", q_orders);
    Cake* cake = create_cake(process_order(q_orders));
    // We display the order processed to make sure it is working
    display_list_Element_str(cake->order);
    build_cake(cake, l_tastes);
    // We display the tastes in the cake making sure that the first taste added is now the base of the cake so the last
    // one inside the cake
    display_list_Element_str(cake->s_tastes->real_tastes);
    deliver(cake, q_tasting);
    // We check to see if our cake is in the tasting queue after we deliver it
    display_list_Element_str(q_tasting->all_cakes_head->cake->s_tastes->real_tastes);
    // Make sure you are eating the same amount of parts in your cake and all the cakes you created to avoid
    // wasting food and memory leaks ( don't worry we covered memory leaks but not the wasted food :P )!
    tasting(q_tasting, 3);


    // We free all the permanent variables used during the cake confection
    free_list_Element_str(&l_tastes);
    free_list_Element_str(&q_orders->all_orders_head);
    free(q_orders);
    --allocs;
    free_list_Element_cake(&q_tasting->all_cakes_head);
    free(q_tasting);
    --allocs;

    // We print our allocs global variable to make sure we didn't miss any memory leaks
    printf("current dynamic memory allocated : %d \n",allocs);
    return 0;
    // Everything seems to work fine ! Yay !
}