#include <ctime>
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

/*
* Swaps elements of any kind
*/
template <class T>
void swap(T& x, T& y)
{
     T temp;
     temp = x;
     x = y;
     y = temp;
}

template <class T>
class min_priority{

  public:
   
    std::vector<T> heap;  

  private:
    /* Inserting new element
    *  @param index of node to start heapifying
    */ 
    int build_heap(int i)
    {

        for(int index=i; index>=0; index--){

          int parent = (index-1)/2;

          //If the element is less than the current parent
          if(heap[index].time < heap[parent].time)
              swap(heap[parent], heap[index]);  //Swap with the parent
        

        }
        return 1;
    }
 
    /* Removing top element from heap
    *  @param index of node to start heapifying
    */ 
    int heapify(int index)
    {
        // Left and right child
        int s = index;
        int left_child = 2*index + 1;
        int right_child = 2*index + 2;

        //Find the smallest out of node, left and right child
        if (left_child < heap.size() && heap[left_child].time < heap[s].time)
            s = left_child;
        else 
            s = index;

        if (right_child < heap.size() && heap[right_child].time < heap[s].time) 
            s = right_child;

        //If node is not already the smallest
        if (s != index)
        {
            swap(heap[index], heap[s]);  //Swap with the smallest
            heapify(s);   //Heapify the tree
        }

        return 1;
    }
  
    public:
    /*
    * Insert new element
    *   Adds to end of heap
    *   Calls heapify to recursively move upwards
    */
    void insert(T element)
    {
        heap.emplace_back(element);
        build_heap(heap.size()-1);
    }

    /*
    * Extract element from top (highest priority with min value)
    *   Removes the minimum value by swapping with 
    *   the last element and heapifies again.
    */
    T extract()
    {
      T temp{}; 

      if(heap.size() > 0)                  //If heap is not empty
      { 
        temp = heap[0];
        swap(heap[0], heap[heap.size()-1]); //Swap the element at begin and end
        heap.pop_back();                    //Remove from end 
        heapify(0);                            //Heapify from removed node to down
      }
      return temp;
    
    }

    /*
    * Decrease the priority of the given lucky index
    *   Lucky index has the lowest priority now 
    *   heapified again.
    */
    void decrease(int lucky)
    {
      T highest = heap[0];                    //Element with highest priority
      heap[lucky].time = highest.time - 1;    //Change the index
      build_heap(lucky);                              //Heapify from lucky to up

    }


    /*
    * Print elements of the heap in array form
    */
    void print()
    {
      for(int i=0; i< heap.size(); i++)
        heap[i].print();

    }
    
    
};

class vehicle
{
    public:

    int vehicle_ID{};
    std::string location_code;
    double distance{};
    double speed{};
    float time{};

    void print()
    {
        std::cout << vehicle_ID << " " 
        << location_code << " "
        << distance << " "
        << speed << " "
        << time << std::endl;


    }

    vehicle()
    {

    }
    vehicle(const vehicle& other)
    {
        if (this != &other) // not a self-assignment
        {
           this->vehicle_ID = other.vehicle_ID;
           this->location_code = other.location_code;
           this->distance = other.distance;
           this->speed = other.speed;
           this->time = other.time;
            
        }
    }

};


void read_vehicles(std::string file_name, min_priority<vehicle>& V){

   std::fstream infile;

   infile.open(file_name, std::ios::in);

   if(infile.is_open())
   {   
        std::string line;
        getline(infile, line);

        Node temp;

        while(getline(infile, line))     
        {      
            std::istringstream ss(line);

            ss >> temp.name;
            ss >> temp.platform;
            ss >> temp.year;
            ss >> temp.publisher;
            ss >> temp.NA_sales;
            ss >> temp.EU_sales;
            ss >> temp.other_sales;

            std::cout << temp.name << temp.platform

        }

        infile.close(); 
   }
   else std::cout << "Input file can not be opened." << std::endl;

}

class request
{
    public:
    std::string   location_code;
    double         distance;
    int           lucky_num;

    void print()
    {
        std::cout << location_code << " "
        << distance << " "
        << lucky_num << std::endl;

    }

};

void read_requests(std::string file_name, std::vector<request>& data){

   std::fstream infile;

   infile.open(file_name, std::ios::in);

   if(infile.is_open())
   {   
        std::string line;
        getline(infile, line);

        request temp;

        while(getline(infile, line))     
        {      
            std::istringstream ss(line);

            ss >> temp.location_code;
            ss >> temp.distance;
            ss >> temp.lucky_num;

            data.push_back(temp);

        }

        infile.close(); 
   }
   else std::cout << "Input file can not be opened." << std::endl;

}


void hotel(int N, min_priority<vehicle>& V, std::vector<request>& R, std::vector<int>& history)
{
  int r_index{};
  int next_op = 2;
  
  
  if(R[r_index].lucky_num!=0)
    next_op = 3;


  while(N >= next_op && r_index < R.size())
  {

    request cur_req = R[r_index];
    vehicle cur_veh;
    r_index++;

    if(cur_req.lucky_num != 0)
    {
      int lucky_index = cur_req.lucky_num;
      V.decrease(lucky_index);
      N--;
      
    }

    int ID = V.heap[0].vehicle_ID;

    if(ID != -1)
    {

      cur_veh = V.extract();
      N--;

      history.push_back(ID); 
      cur_veh.location_code = cur_req.location_code;
      cur_veh.distance = cur_req.distance;
      cur_veh.time = cur_veh.distance/cur_veh.speed;

      V.insert(cur_veh);
      N--;

      next_op = 2;
      if(R[r_index+1].lucky_num != 0)
        next_op = 3;

    }

    else std::cout << "No vehicle available" << std::endl;   

  }


}
 
int main(int argc, char** argv)
{
    int N = std::stoi(argv[1]);

    std::string vehicle_file = "vehicles.txt";
    std::string request_file = "requests.txt";

    min_priority<vehicle> V;
    std::vector<request> R;
    std::vector<int> history;

    read_vehicles(vehicle_file, V);
    read_requests(request_file, R);
    
    clock_t t;
    t = clock();
    hotel(N, V, R, history);
    t = clock() - t;

    printf ("Elapsed in %f miliseconds.\n", float(t*1.0/ (CLOCKS_PER_SEC/1000)));

    //std::ofstream out_file;
    //out_file.open("out20000.txt");
    //out_file.close();

   for(int i=0; i<history.size(); i++)
     std::cout << history[i] << " ";
    return 0;

}
