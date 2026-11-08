
#include <iostream>
using namespace std;

template<typename T>
class List
{
    struct Node
    {
        Node* prev;
        T value;
        Node* next;

        Node() : prev(nullptr), value(T()), next(nullptr) {}

        Node(Node* p, T v, Node* n)
            : prev(p), value(v), next(n) {
        }
    };

private:
    Node* head;
    Node* tail;

public:
    List()
    {
        head = tail = nullptr;
    }

    bool IsEmpty()
    {
        return head == nullptr;
    }

    void Print()
    {
        for (Node* i = head; i != nullptr; i = i->next)
        {
            cout << i->value << " ";
        }
        cout << endl;
    }

    void AddtoHead(T value)
    {
        Node* newNode = new Node(nullptr, value, head);

        if (IsEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            head->prev = newNode;
            head = newNode;
        }
    }

    void AddToTail(T value)
    {
        Node* newNode = new Node(tail, value, nullptr);

        if (IsEmpty())
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void DeleteToTile()
    {
        if (IsEmpty()) return;

        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
    }

    void DeleteToHEad()
    {
        if (IsEmpty()) return;

        Node* temp = head;

        if (head == tail)
        {
            head = tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
    }


    bool AddByPosition(int position, T value)
    {
        if (position < 0) return false;

        if (position == 0)
        {
            AddtoHead(value);
            return true;
        }

        Node* current = head;
        int index = 0;

        while (current != nullptr && index < position)
        {
            current = current->next;
            index++;
        }

        if (current == nullptr)
        {
            if (index == position)
            {
                AddToTail(value);
                return true;
            }

            return false;
        }

        Node* newNode = new Node(current->prev, value, current);

        current->prev->next = newNode;
        current->prev = newNode;

        return true;
    }

 
    bool DeleteByPosition(int position)
    {
        if (position < 0 || IsEmpty()) return false;

        if (position == 0)
        {
            DeleteToHEad();
            return true;
        }

        Node* current = head;
        int index = 0;

        while (current != nullptr && index < position)
        {
            current = current->next;
            index++;
        }

        if (current == nullptr) return false;

        if (current == tail)
        {
            DeleteToTile();
            return true;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;

        delete current;

        return true;
    }

    ~List()
    {
        while (head != nullptr)
        {
            Node* current = head;
            head = head->next;
            delete current;
        }
    }
};

struct Vagon
{
    int number;
    int countPlaces;
    int countPeople;

    Vagon()
    {
        number = 0;
        countPlaces = 0;
        countPeople = 0;
    }

    Vagon(int number, int countPlaces, int countPeople)
    {
        this->number = number;
        this->countPlaces = countPlaces;
        this->countPeople = countPeople;
    }
};

ostream& operator<<(ostream& out, const Vagon& v)
{
    out << "Number [" << v.number << "] "
        << "Places [" << v.countPlaces << "] "
        << "People [" << v.countPeople << "]";
    return out;
}

class Train
{
private:
    string model;
    List<Vagon> vagons;
    int countVagons;

public:
    Train()
    {
        model = "no model";
        countVagons = 0;
    }

    Train(string model)
    {
        this->model = model;
        countVagons = 0;
    }

    void AddToHead(Vagon vagon)
    {
        vagons.AddtoHead(vagon);
        countVagons++;
    }

    void AddToTile(Vagon vagon)
    {
        vagons.AddToTail(vagon);
        countVagons++;
    }

    void DeleteToHead()
    {
        if (countVagons == 0) return;
        vagons.DeleteToHEad();
        countVagons--;
    }

    void DeleteToTile()
    {
        if (countVagons == 0) return;
        vagons.DeleteToTile();
        countVagons--;
    }

    void AddByPosition(int position, Vagon vagon)
    {
        if (vagons.AddByPosition(position, vagon))
            countVagons++;
    }

    void DeleteByPosition(int position)
    {
        if (vagons.DeleteByPosition(position))
            countVagons--;
    }

    void Show()
    {
        vagons.Print();
    }
};

int main()
{
    List<int> l;

    l.AddToTail(10);
    l.AddToTail(20);
    l.AddToTail(30);
    l.AddToTail(40);

    cout << "Original list: ";
    l.Print();

    l.AddByPosition(2, 99);

    cout << "After adding: ";
    l.Print();

    l.DeleteByPosition(1);

    cout << "After deleting: ";
    l.Print();

    Train t;

    for (int i = 0; i < 5; i++)
    {
        t.AddToHead(Vagon(i, rand() % 20, rand() % 20));
    }

    cout << "\nTrain:\n";
    t.Show();

    return 0;
}
