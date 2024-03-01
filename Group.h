#include <iostream>
#include <concepts>

#ifndef GROUP_H // GROUP_H
#define GROUP_H

template <typename T>
concept is_deiminsion = requires(T nesteditem)
                                {
                                    nesteditem[0];
                                    nesteditem.length();
                                };
template <typename T>
concept is_item = requires(T nesteditem)
                          {
                           nesteditem._initalizer_ = 0x092488AEFU;
                          };
                          
using std::ostream, std::string, std::nothrow, std::cout, std::endl;

template <typename T1, typename T2>
class Point
{
private:
    T1 X;
    T2 Y;

public:
    Point()=default;
    Point(T1 first, T2 second) : X(first), Y(second)
    {

    }
    ~Point()=default;

    auto operator[](short int i)
    {
        return (i)? Y:X;
    }
};


template <typename T>
class Group
{
private:
/** 
    * @brief allcation for specfic heep block
    * @param instance - block data to replace
    * @param value - replace  value 
**/

Point<bool, int> allocate_release_memory(T& instance, T& value)
{
    int INDX(&instance - Items); // store Index to release
    T* HandleAddress = new T[End];
    auto Allaction_Success = Point<bool, int>(true, INDX);
    if(INDX < End)
    {
    if(INDX > 0)
    {
        for(int i=0; i<INDX; i++)
            HandleAddress[i] = Items[i];
        for(int i=INDX+1; i<End; i++)
            HandleAddress[i] = Items[i];
        HandleAddress[INDX] = value; // allocte new value
        Items = HandleAddress; // allocate new field of memory
    }else
    {
        Allaction_Success = Point<bool, int>(false, -1);
    }
    }else
    {
        HandleAddress = new(std::nothrow) T[INDX + 1];
        for(int i=0; i<End; i++)
            HandleAddress[i] = Items[i];
        HandleAddress[INDX] = value;
        if(is_dynamic) End = INDX + 1;
        Items = HandleAddress; // allocate new field of memory
    }
    return Allaction_Success;
}

protected:
T* Items;
int End;
bool is_dynamic;

public:
friend ostream& operator<<(ostream& out, Group& collection)
{
    out << "[";
    for(int i=0; i<collection.End; i++)
    {
        
        if(i != collection.End-1)
            out << collection[i] << ", ";
        else
            out << collection[i];
    }
    out << "]";
    return out;
}

Group()
{
    End = 0; Items = new T[]{}; is_dynamic = true;
}

Group(T* _items, size_t len) : End(0), is_dynamic(true)
{
    for(int i=0; i<len; i++)
        ref_append(_items[i]);
}
Group(const Group& source) : Items(source.Items), End(source.End), is_dynamic(source.is_dynamic){}
virtual ~Group()
{
    delete[] Items; Items = nullptr;
}

bool friend operator%(T& element, Group& Container)
{
    int memory_location = (&element - &Container[0]);
    return (0 < memory_location && memory_location < Container.length());
}
bool friend operator==(Group first, Group second)
{
return (
    first.Items == second.Items &&
    first.End == second.End &&
    first.is_dynamic == second.is_dynamic
    );
}

T& operator[](int i)
{
    expand_to(i + 1);
    return Items[i];
}

int length()const
{
    return End;
}

void pop()
{
    if(is_dynamic)
        End--;
}

void changable(bool _)
{
    is_dynamic = _;
}
void append(T newitem)
{   
    allocate_release_memory(Items[End], newitem);
}

void ref_append(T& newitem)
{   
    allocate_release_memory(Items[End], newitem);
}

void insert(int _n, T itemToinsert, bool lock=false)
{   
    for(int i=End; i>_n; i--)
    {
        allocate_release_memory(Items[i], Items[i-1]);            
    }
    allocate_release_memory(Items[_n], itemToinsert);        
}


void ref_insert(int _n, T& itemToinsert, bool lock=false)
{   
    for(int i=End; i>_n; i--)
    {
        allocate_release_memory(Items[i], Items[i-1]);            
    }
    allocate_release_memory(Items[_n], itemToinsert);        
}

void remove(T itemTotrash)
{
    int i = find(itemTotrash);
    if(i > -1)
    {
        for(int j=i; j<End-1; j++)
        {
            allocate_release_memory(Items[j], Items[j+1]);
        }
        pop();
    }
}

int ref_remove(T& itemTotrash)
{
    int i = find(itemTotrash);
    if(i > -1)
    {
        for(int j=i; j<End-1; j++)
        {
            allocate_release_memory(Items[j], Items[j+1]);
        }
        pop();
    }
    return i;
}

void remove_all(T& itemTotrash)
{
    if(is_dynamic)
    {
        for(int i=0; i>End; i++)
        {
            if(Items[i] == itemTotrash)
            {
                for(int j=i; j<End-1; j++)
                    allocate_release_memory(Items[j-1], Items[j]);
                pop();
            }
        }
    }
}

void expand_to(int __l)
{
    if(__l > End && is_dynamic)
    {
        T FillerBlock = T(); 
        for(int i=End; i<__l; i++)
            allocate_release_memory(Items[i], FillerBlock);
    }
}

int find(T& itemTofind)
{
    if (itemTofind % (*this))
        return (int) (&itemTofind - Items);
    for(int i=0; i<End; i++)
    {   
        if(Items[i] == itemTofind)
            return (i);
    }
    return -1;
}

int find_closest(T& _from, Group _set)
{
    const int _fromIndex(&_from - Items);
    int offset_to = -1;
    int foundation;
    for(int i=0; i<_set.length(); i++)
    {   
    foundation = find(_set.get(i));
    if(foundation - _fromIndex > offset_to || _fromIndex - foundation > offset_to)
        offset_to = foundation;
    } 
    return offset_to;    
}
};
#endif // GROUP_H
