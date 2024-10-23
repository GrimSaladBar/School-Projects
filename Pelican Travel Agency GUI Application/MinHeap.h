#ifndef MINHEAP_H
#define MINHEAP_H

struct clientInfo
{
    int clientID;
    string firstName;
    string surname;
    string destination;
    string payment;
    string booking;
};

class MinHeap
{
        private:
                vector <clientInfo> elements;

        public:
                MinHeap(){elements.resize(1);}

                void addHeap(int, string, string, string, string, string);               // Add to MinHeap
                void heapify(unsigned int);      // Heapify MinHeap
                void deleteHeapVal(int);         // Delete element from MinHeap
                void removeRoot();
                string sortHeap();
    };

//===================================================================================
// Add new element to MinHeap
//===================================================================================
void MinHeap::addHeap(int, string, string, string, string, string)
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
// Recursive heapify function for a MinHeap
//===================================================================================
void MinHeap::heapify(unsigned int index)
    {
        unsigned int left, right, minn;
        left = 2*index;
        right = 2*index + 1;

        // Base case
        if (index == 0)
            return;

        // Check the children, if they exist and pick the larger for swapping
        if (left < elements.size() && elements[left] < elements[index])
            minn = left;
        else
            minn = index;

        if (right < elements.size() && elements[right] < elements[minn])
            minn = right;

        if (minn != index)
            {
                int temp = elements[minn];
                elements[minn] = elements[index];
                elements[index] = temp;
                heapify(minn);
            }

        // Now check the parent, if it exists
        heapify(index/2);
    }

void MinHeap::deleteHeapVal(int id)
    {

        int x = 0;

        while ( x <= elements.size() )
            {
                if ( id == elements[x].clientID )
                    {
                        elements[x] = elements[ (elements.size() - 1) ];

                        elements.pop_back();

                        heapify(x);              // parent
                        heapify((2 * x) +1);     // left child
                        heapify((2 * x) +2 );    // right child
                        break;      //No need to search further
                    }
                x++;
            }
    }

void MinHeap::removeRoot()
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

string MinHeap::sortMinHeap()
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


string MinHeap::displayHeap()
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
