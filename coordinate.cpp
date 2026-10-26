#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "coordinate.h"


// Create a coordinate x,y
void add_coordinate(Coordinate *list_end, float x, float y)
{
    Coordinate *begin = list_end;
    while(begin->previous != nullptr) // loop to get the end pointer
    {
        begin = begin->previous;
    }

    Coordinate *c = (Coordinate *) malloc(sizeof(Coordinate));  // ask for memory for new node

    // store the value
    c->x = x;
    c->y = y;
    c->coord_id = list_length(begin);
    c->next = nullptr;
    c->previous = list_end;
    list_end->next = c;
}


// Display ID number, x and y coordinate number (coordinate will generate random)
void forward_display(Coordinate *list_beginning)
{
    Coordinate *c = list_beginning;
    while(c != nullptr)  // loop go until hit the last node
    {
	// print value of id, x, y
        std::cout << "\nid " << c->coord_id << std::endl;
	std::cout << "x: " << c->x << std::endl;
	std::cout << "y: " << c->y << std::endl;
	c= c->next; // move to the next node
    }
}


// Flip the order (ID: x,y) backwards (highest id number to lowest id number
void backward_display(Coordinate *list_end)
{
     Coordinate *c = list_end;
     while(c != nullptr) // loop go until hit the last node
     {
         // print id, x, y value
         std::cout << "\nid " << c->coord_id << std::endl;
         std::cout << "x: " << c->x << std::endl;
         std::cout << "y: " << c->y << std::endl;
         c = c->previous; // move back to the previous node
     }
}


// Free memory
void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{
     Coordinate *c = list_beginning;
     while(c != nullptr && c->coord_id != coord_id_to_delete)   // delete the first node, and let second node become the first
     {
          c = c->next;
     }

     if(c == nullptr)  // no matching id, tell the user and stop
     {
         std::cout << "id " << coord_id_to_delete << " not found" << std::endl;
         return;
     }

     if(c == list_beginning)  // free second node, node data into first node
     {
         Coordinate *second = c->next;
         if(second == nullptr) // only 1 node in the list
         {
              std::cout << "cannot delete the only coordinate in the list" << std::endl;
              return;
         }
     // copy all second node data into first
     c->x = second->x;
     c->y = second->y;
     c->coord_id = second->coord_id;
     c->next = second->next;
     if(second->next != nullptr)  // if there is a third node
     {
         second->next->previous = c;
     }
     free(second);  // give the second node memory back
     }
     else
     {
         c->previous->next = c->next;  // deleting the middle or last node
         if(c->next != nullptr)
         {
	     c->next->previous = c->previous;
	 }
         free(c);
     }
}


// counts how many nodes are in the list 
int list_length(Coordinate *list_beginning)
{
    int length = 0;
    Coordinate *c = list_beginning;
    while(c != nullptr)  // loop past to the end of the list
    {
        length++;
        c = c->next;
    }
    return length;
}


// finds the nearest to the point
void closest_to(Coordinate *list_beginning, float x, float y)
{
    if(list_beginning == nullptr)  // if there is no first node
    {
        std::cout << "the list is empty" << std::endl;
        return;
    }

    // let first node is the closest
    Coordinate *closest = list_beginning;
    float dx = list_beginning->x - x;
    float dy = list_beginning->y - y;
    float closest_distance = sqrt(dx * dx + dy * dy);

    Coordinate *c = list_beginning->next;
    while(c != nullptr) // start checking from second node
    {
        dx = c->x - x;
        dy = c->y - y;
        float distance = sqrt(dx * dx + dy * dy);

        if(distance < closest_distance)   // if this node is closer, keep it
        {
            closest_distance = distance;
            closest = c;
        }
        c = c->next;
    }

    // print out the node it keeps
    std::cout << "closest to id: " << closest->coord_id << std::endl;
    std::cout << "x: " << closest->x << std::endl;
    std::cout << "y: " << closest->y << std::endl;
    std::cout << "distance: " << closest_distance << std::endl;
}
