#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "coordinate.h"


int main(int argc, char *argv[])
{
    if(argc != 2)  // user must type at least 1 number

    {
        std::cout << "usage: ./main <number of coordinates>" << std::endl;
        return 1;
    }

    int number = atoi(argv[1]);  // let number = 10 ( argv[1] is text "10" )
    
    if(number < 1)  // need at least 1 coordinate
    {
        std::cout << "number of coordinates must be at least 1" << std::endl;
        return 1;
    }

    srand(time(NULL)); // random number generator with current time

    Coordinate *list_beginning = (Coordinate *) malloc(sizeof(Coordinate));  // need memory for existing node

    // rand() gives a whole number from 0 to rand_max
    list_beginning->x = (float) rand() / RAND_MAX * 100; // divide rand_max to gives 0.0 to 1.0, mutiply 100 gives 0.0 to 100.0
    list_beginning->y = (float) rand() / RAND_MAX * 100;
    list_beginning->coord_id = 0;
    list_beginning->next = nullptr;
    list_beginning->previous = nullptr;
    Coordinate *list_end = list_beginning;

    for(int i = 1; i < number; i++)  // add rest of the nodes
    {
        add_coordinate(list_end, (float) rand() / RAND_MAX * 100, (float) rand() / RAND_MAX * 100);
        list_end = list_end->next;
    }

    // print List_length
    std::cout << "length = " << list_length(list_beginning) << std::endl;

    // print foward_display
    std::cout << "forward display" << std::endl;
    forward_display(list_beginning);

    // print backward_display
    std::cout << "backward display" << std::endl;
    backward_display(list_end);

    // print closest_to
    std::cout << "closest to (x: 50, y: 50)" << std::endl;
    closest_to(list_beginning, 50, 50);

    // remove the node with id 2 and free its memory
    std::cout << "deleting id 2" << std::endl;
    delete_coordinate(list_beginning, 2);

    // print length_list and forward_display without id 2
    std::cout << "length = " << list_length(list_beginning) << std::endl;
    std::cout << "forward display after delete" << std::endl;
    forward_display(list_beginning);


    // free all remaining nodes
    Coordinate *c = list_beginning;
    while(c != nullptr)
    {
        Coordinate *next = c->next;
        free(c);
        c = next;
    }

    return 0;
}
