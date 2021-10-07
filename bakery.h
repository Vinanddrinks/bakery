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
    //Todo
}Taste_Stack;
typedef struct Cake{
    Element_str* order;
    Taste_Stack* s_tastes;
}Cake;
typedef struct Element_cake{
    Cake* cake;
    struct Element_str* next;
}Element_cake;
typedef struct Order_Queue{
    //Todo
}Order_Queue;
typedef struct Tasting_Queue{
    //Todo
}Tasting_Queue;

//str def end
//start debug var
int allocs;
//end debug var

// Start Prototype déclaration

// End Prototype déclaration
#endif //BAKERY_BAKERY_H
