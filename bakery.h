//
// Created by Vinanddrinks on 07/10/2021.
//

#ifndef BAKERY_BAKERY_H
#define BAKERY_BAKERY_H
//structures def start
typedef struct Element_str{
    char text[50];
    struct Element_str* next;
}Element_str;
typedef struct Taste_Stack{
    Element_str* real_tastes;
}Taste_Stack;
typedef struct Cake{
    Element_str* order;
    Taste_Stack* s_tastes;
}Cake;
typedef struct Element_cake{
    Cake* cake;
    struct Element_cake* next;
}Element_cake;
typedef struct Order_Queue{
    Element_str* all_orders_head;
}Order_Queue;
typedef struct Tasting_Queue{
    Element_cake* all_cakes_head;
}Tasting_Queue;

//str def end
//start debug var
int allocs;
//end debug var


// Start Prototype declaration
Element_str* initialize_tastes(int size, ...) ;
void display_list_Element_str(Element_str* tastes) ;
Element_str* create_taste(char text[50]) ;
int size_of_element_str(Element_str* tastes) ;
void free_list_Element_str(Element_str** tastes) ;
void free_list_Element_cake(Element_cake ** tastes);
void pass_order(char order[50], Order_Queue* f_orders) ;
char* taste_processor(char taste);
Element_str* process_order(Order_Queue* q_orders) ;
int is_in_stock(Element_str* taste, Element_str* l_tastes);
Cake* create_cake(Element_str* order) ;
void build_cake(Cake* cake, Element_str* l_tastes) ;
Element_cake * create_element_cake(Cake* cake);
void deliver(Cake* cake, Tasting_Queue* q_tasting) ;
void tasting(Tasting_Queue* q_tasting, int nb_parts) ;


// End Prototype declaration
#endif //BAKERY_BAKERY_H
