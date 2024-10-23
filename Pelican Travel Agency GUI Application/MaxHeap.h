#ifndef MAXHEAP_H
#define MAXHEAP_H

struct clientInfo
{
    int clientID;
    string firstName;
    string surname;
    string destination;
    string payment;
    string booking;
};

class MaxHeap
    {
        private:
                vector <clientInfo> elements;

        public:
                MaxHeap(){elements.resize(1);}

                void addHeap(int);               // Add to Heap
                void heapify(unsigned int);      // Heapify Heap
                void deleteHeapVal(int);         // Delete element from Heap
                void removeRoot();
                string displayHeap();
                string sortHeap();
    };

//===================================================================================
// Add new element to Heap
//===================================================================================
void MaxHeap::addHeap(int, string, string, string, string, string)
    {
        struct clientInfo client;

        client.clientID = id;
        client.firstName = first;
        client.surname = last;
        client.destination = dst;
        client.payment = pay;
        client.booking = book;

        elements.push_back(client);
        heapify(elements.size() - 1);
    }

//===================================================================================
// Recursive heapify function for a Heap
//===================================================================================
void MaxHeap::heapify(unsigned int index)
    {
        unsigned int left, right, maxx;
        left = 2*index;
        right = 2*index + 1;

        // Base case
        if (index == 0)
            return;

        // Check the children, if they exist and pick the larger for swapping
        if (left < elements.size() && elements[left] > elements[index])
            maxx = left;
        else
            maxx = index;

        if (right < elements.size() && elements[right] > elements[maxx])
            maxx = right;

        if (maxx != index)
            {
                int temp = elements[maxx];
                elements[maxx] = elements[index];
                elements[index] = temp;
                heapify(maxx);
            }

        // Now check the parent, if it exists
        heapify(index/2);
    }

void MaxHeap::deleteHeapVal(int id)
    {

        int x = 0;

        while ( x <= elements.size() )
            {
                if ( id == elements[x].clientID )
                    {
                        elements[x] = elements[(elements.size() - 1)];

                        elements.pop_back();

                        heapify(x);              // parent
                        heapify((2 * x) +1);     // left child
                        heapify((2 * x) +2 );    // right child
                        break;      //No need to search further
                    }
                x++;
            }
    }


void MaxHeap::removeRoot()
    {
        if (elements.size() < 2)
            return;
        else
            {
                elements[1] = elements[elements.size() - 1];
                elements.resize(elements.size() - 1);
                heapify(1);
            }
    }

string MaxHeap::sortHeap()
    {
        string str ="";

        while (elements.size() > 1)
            {
                str.append(to_string(elements[1]));
                str.append("\t");
                removeRoot();
            }
        str.append("\n");
        return str;
    }


string MaxHeap::displayHeap()
{
    string str = "";
    for (int x = 1; x < elements.size(); x++)
        {
            str.append(to_string(elements[x].clientID));
            str.append("\t");
            str.append(elements[x].firstName);
            str.append("\t");
            str.append(elements[x].surname);
            str.append("\t");
            str.append(elements[x].destination);
            str.append("\t");
            str.append(elements[x].payment);
            str.append("\t");
            str.append(elements[x].booking);
            str.append("\n");
        }
    return str;
}

#endif
