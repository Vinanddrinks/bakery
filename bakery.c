//
// Created by Vinanddrinks, Riccardis and Djay on 07/10/2021.
//
// Vincent Labouret, Giuliano Riccardi, Joseph Beaumont - L2 INT2

#include "bakery.h" // we include the header for our structures
#include "stdlib.h" // we include it to manage memory
#include "stdio.h"  // here to manage input and output operation
#include "string.h" // here to manage strings
#include "stdarg.h" // to manage non predefined argument function call

Element_str* create_taste(char order[50]){
    //this function allocate and fill with the given parameter an Element_str
    // and return its pointer
    Element_str* new_taste = (Element_str*)malloc(sizeof(Element_str));
    allocs++;
    strcpy(new_taste->text, order);
    new_taste->next = NULL;
    return new_taste;
}
void display_list_Element_str(Element_str* tastes){
    // this function display a string simply linked list (Element_str)
    if (tastes != NULL){
        printf("%s->",tastes->text);
        display_list_Element_str(tastes->next);
    }else{
        printf("NULL\n");
    }
}
void free_list_Element_str(Element_str** tastes){
    //this function free a str SLL(Element_str) and put is head and next value to NULL so other function know when
    //an str SLL is unassigned
    if (*tastes!=NULL) {
        free_list_Element_str(&(*tastes)->next);
        free(*tastes);
        *tastes = NULL;
        allocs--;
    }
}
void free_cake(Cake** cake){
    //this function function is used to free a built cake (no order to free)
    // as the 3 structures allocated consecutively we need to free them
    // from the last (the SLL real_tastes) to the first (struct Cake)
    free_list_Element_str(&(*cake)->s_tastes->real_tastes);
    free((*cake)->s_tastes);
    allocs--;
    free(*cake);
    allocs--;
    *cake = NULL;
}
void free_list_Element_cake(Element_cake ** cake){
    //this function free a cake SLL(Element_cake)and put is head and next value to NULL so other function know when
    //an cake SLL is unassigned
    if (*cake!=NULL) {
        free_list_Element_cake(&(*cake)->next);
        free_cake(&(*cake)->cake);
        free(*cake);
        *cake = NULL;
        allocs--;
    }
}
void eat_slices(Cake* cake, int number_of_slice){
    // Everytime we eat a slice we free the taste we ate from the cake
    // so this function remove and free the first flavour of the cake as it is a stack
    for(int i = 0; i < number_of_slice;i++){
        Element_str * slice_to_free = cake->s_tastes->real_tastes;
        cake->s_tastes->real_tastes = cake->s_tastes->real_tastes->next;
        free(slice_to_free);
        allocs--;
    }
}
Element_str* initialize_tastes(int size, ...){
    //this function take an unlimited number of parameter and create from it an Element str list containing these argument
    // the first argument is always the number of argument to add in the list.
    Element_str* tastes_list = NULL,*head = NULL;
    //here we initialize a list from the exec pipe containing all the argument up to the size
    va_list valist;
    va_start(valist,size);
    //here we create the first element as the list do not have a type we need to provide it
    // in the va_arg function
    head = create_taste(va_arg(valist,char*));
    tastes_list = head;
    //here we add the following taste
    //knowing that va_arg goes automatically to the next argument when called
    for(int i = 1; i < size;++i){
        tastes_list->next = create_taste(va_arg(valist,char *));
        tastes_list = tastes_list->next;
    }
    //we free the list after using it with va_end
    va_end(valist);
    return head;
}

int size_of_element_str(Element_str* tastes) {
    // gives us the real size of our elements_str list
    if (tastes != NULL) {
        return 1 + size_of_element_str(tastes->next);
    }else return 0;
}
void pass_order(char order[50], Order_Queue* f_orders) {
    // We only add it to the order if we have less than 10 orders in our Order queue
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
    //Transform the oldest order string in a simply linked list (Element_str)
    //containing the tastes full names while keeping the order given in the string
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
    // This function creates a cake associated with the processed order sent as a parameter
    // and return its address
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
    //function that add a cake slice in the beginning of the stack
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
            // We check to see if the taste chosen is available and if so we add it to the cake otherwise we skip this
            // flavour
            if (is_in_stock(temp, l_tastes) == 1){
                add_to_cake(cake, temp);
            }
                temp = temp->next;
        }
    }
}
Element_cake * create_element_cake(Cake* cake){
    // if we send a cake we do something otherwise we do nothing
    if(cake!=NULL){
        // We allocate the memory for this Element_cake
        Element_cake* new = (Element_cake*)malloc(sizeof(Element_cake));
        allocs ++;
        // We put the cake inside
        new->cake = cake;
        // We set the next value to NULL
        new->next = NULL;
        return new;
    }
}

void deliver(Cake* cake, Tasting_Queue* q_tasting){
    // We only deliver when we finished building the cake
    if (cake != NULL && q_tasting != NULL){
        // We can throw away the cake order
        free_list_Element_str(&cake->order);
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
void taste_cake(Cake* cake, int nb_parts){
    // First we fetch the size of the cake, in other words, how many parts it has
    int size_cake = size_of_element_str(cake->s_tastes->real_tastes);
    // If the number of parts we are tasting is equal or superior to the number of parts we have in the cake we can
    // say that the cake was finished so we free this cake from the memory
    if (nb_parts >= size_cake){
        free_cake(&cake);
    }
    // otherwise if the number of parts is between 0 and the size of the cake we only eat some slices or parts using
    // our eat_slice function
    else if(nb_parts>0){
        eat_slices(cake, nb_parts);
    }
    // If the user tastes 0 or a negative number of parts we do nothing to the cake
}
void tasting(Tasting_Queue* q_tasting, int nb_parts){
    if (q_tasting!=NULL){
        // We only taste when there is something on the tasting queue, otherwise we cannot taste anything
        Element_cake * temp = q_tasting->all_cakes_head;
        // We go to the oldest cake in the queue because the oldest in should be the first out
        while (temp->next != NULL){
            temp = temp->next;
        }
        // We taste the cake using our tasting function that allows us to eat only some slices
        taste_cake(temp->cake, nb_parts);
        // If we eat the whole cake we can then free the Element_cake containing the empty cake
        if (temp->cake == NULL){
            Element_cake * old = temp;
            temp = NULL;
            free(old);
            allocs --;
        }
    }
}