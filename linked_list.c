// Gillian Evers
// Lab Partner: Daniel Scholem
#include<stdio.h>
#include<stdlib.h>

// Node is a struct with 
// data as an int and next as a pointer to a Node
typedef struct Node
{
    int data;
    struct Node* next;
}NODE;

int   get_data    ();
int   get_index   ();
int   char_to_int (char c);
NODE* create_node (int data);
NODE* search_for  (NODE *first, int data);
void  add_at_end  (NODE *first, int data);
void  insert_node (NODE *first, int data, int index);
void  delete_node (NODE *first, NODE *to_delete);
void  print_node  (NODE *first, int index);
void  delete_list (NODE **first);
void  print_list  (NODE *first);

int main(int argc, char** argv)
{
    NODE *first = NULL;
    char keep_going = 'y';
    while(keep_going == 'y')
    {
        printf("Please choose an action for your linked list:\n");
        printf("s = search for node\na = add node at the end\ni = insert node\nd = delete node\np = print node\nD = delete list\nP = print list\nq = quit\n");
        char answer = getchar(); getchar();
        switch (answer)
        {
            case 's':
            {
                int data = get_data();
                search_for(first, data);
                break;
            }
            case 'a':
            {
                int data = get_data();
                if(first == NULL)
                {
                    first = create_node(data);
                }
                else
                {
                    add_at_end(first, data);
                }
                break;
            }
            case 'i':
            {
                int data  = get_data();
                int index = get_index();
                if(first == NULL)
                {
                    first = create_node(data);
                }
                else
                {
                    insert_node(first, data, index);
                }
                break;
            }  
            case 'd':
            {
                int   data   = get_data();
                NODE *delete = search_for(first, data);
                delete_node(first, delete);
                break;
            }
            case 'p':
            {
                int index = get_index();
                print_node(first, index);
                break;
            }
            case 'D':
                delete_list(&first);
                break;
            case 'P':
                print_list(first);
                break;
            case 'q':
                keep_going = 'n';
                break;
            default: 
                printf("Not a valid answer\n");
                break;
        }
    }

}

// Gets data from user and converts it into an int
// Returns data converted to int
int get_data()
{
    printf("Enter data (1-digit integer): ");
    char chardata = getchar(); getchar();   // second getchar() is for when the user presses ENTER
    int  data     = char_to_int(chardata);
    return data;
}

// Gets index from user and converts it into an int
// Returns index converted to int
int get_index()
{
    printf("Enter index: ");
    char charindex = getchar(); getchar();  // second getchar() is for when the user presses ENTER
    int  index     = char_to_int(charindex);
    return index;
}

// Converts a char to an int
int char_to_int(char c)
{
    return c - 48;
}

// Creates new node
// Takes in the data for the node
// Returns the newly created node
NODE* create_node(int data)
{
    NODE *new = (NODE *)malloc(sizeof(NODE));   // Allocates memory on the heap for new
    new->data = data;
    new->next = NULL;
    return new;
}

// Searches for node with specific data
// Uses first to access the list
// Returns the first node with the data being searched for
// Returns null if data not found
NODE* search_for(NODE *first, int data)
{
    NODE *temp = first; // uses a temp pointer to traverse through list
    int found  = 0;     // indicates whether the data was found or not
    if(first != NULL)   // makes sure the list in not empty
    {
        int index = 0;  // keeps track of the index where the node is found
        while (temp != NULL)
        {
            // once the data is found, exit loop
            if (temp->data == data)
            {
                found = 1;
                break;
            }
            // if not found, keep traversing
            temp = temp->next;
            index++;
        }
        // if the node was never found, set temp to null so it returns null
        if ((temp->next == NULL) && (found == 0))
        {
            printf("Could not find %d\n", data);
            temp = NULL;
        }
        else
        {
            printf("Found %d at index %d\n", temp->data, index);
        }
        return temp;
    }
    else
    {
        printf("List is empty!\n");
    }
}

// Adds a node with specified data to the end of the list
// Uses first to access the list
void add_at_end(NODE * first, int data)
{
    NODE *new, *temp;
    new  = create_node(data);   // creates new node from the data given
    temp = first;               // uses temp pointer to traverse through list
    // traverses until it reaches end of list
    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = new;   // the next node after the last node is new
    new ->next = NULL;  // now new is the last node
}

// Inserts node at specified index
// Uses first to access list
void insert_node(NODE *first, int data, int index)
{
    NODE *temp, *previous, *new;
    temp     = first;
    previous = first;
    new      = create_node(data);   // creates node to be inserted from specified data

    int current_index = 0;  // keeps track of the current index
    while(current_index != index)   // checks if it found the specified index
    {
        // if it's at the first node, then only move temp
        // there is no previous node before first
        if(temp == first)
        {
            temp = temp->next;
        }
        else{
            temp     = temp->next;
            previous = previous->next;
        }
        current_index++;
    }
    // once the index is found, insert new in between previous and temp
    // so it will be in this order: previous->new->temp
    new->next      = temp;
    previous->next = new;
}

// Deletes specified node
// Uses first to access the list
void delete_node(NODE *first, NODE *to_delete)
{
    NODE *previous = first; // keeps track of the previous node before to_delete
    while(previous->next != to_delete)  // checks if it found the node to be deleted
    {
        previous = previous->next;
    }

    // diconnect to_delete from list and make sure not to lose connection between previous and the rest of the list
    previous ->next = to_delete->next;
    to_delete->next = NULL;             

    printf("%d deleted from list\n", to_delete->data);

    free(to_delete);
}

// Prints the data of a node at a specific index
// Uses first to access the list
void print_node(NODE *first, int index)
{
    NODE *temp = first;     // uses a temp pointer to traverse through list
    int current_index = 0;  // keeps track of the current index
    // traverses list until it finds the specified index
    while(current_index != index)
    {
            temp = temp->next;
            current_index++;
    }
    printf("Data at index %d is: %d\n", index, temp->data);
}

// Deletes an entire list
// Uses a pointer to first to access the list
void delete_list(NODE **first)
{
    NODE *temp = *first;    // uses a temp pointer to travserse list
    NODE *next;             // keeps track of next node before temp gets deleted
    if(*first == NULL)
    {
        printf("List is already empty.\n");
    }
    else
    {
        // traverses through list and deletes nodes as it goes through
        while(temp != NULL)
        {
            next = temp->next;
            free(temp);
            temp = next;
        }
        *first = NULL;  // first points to null - list is now empty
    }
}

// Prints the entire list
// Uses first to access list
void print_list(NODE * first)
{
    NODE *temp = first; // uses a temp pointer to traverse through list
    if(temp == NULL)    // checks if list is empty 
    {
        printf("List is empty!\n");
    }
    else
    {
        // print the first node, then traverse through list and print the rest of the nodes
        printf("%d\n", first->data);
        while(temp->next != NULL)
        {
            temp = temp->next;
            printf("%d\n", temp->data);
        }
    }
}