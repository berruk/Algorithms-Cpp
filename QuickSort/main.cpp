/* Compiled in SSH with "g++ quicksort.cpp -o q -std=c++11"
*
*   BERRU KARAKAS
*   21.11.2021
*   QUICK SORT
*
*/

#include <cstdlib> 
#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>

/*
    {READ CSV}
    @param file_name    : input file name
    @param data         : vector to vectors of individual rows
    @param number       : amount of rows to read

    Reads csv file, parses the rows with a delimeter (tab),
    pushes the elements to a vector, pushes the vectors to a vector.

*/
void read_csv(std::string file_name, std::vector< std::vector <std::string> >& data, int number){

   std::fstream infile;
   int counter = 0;
   infile.open(file_name, std::ios::in);

   if(infile.is_open())
   {   
      std::string file_ptr;
      getline(infile, file_ptr);

      while(getline(infile, file_ptr) && counter != number)     //  Till EOF or number tweets 
      {     
          
        size_t pos = 0; 
        std::string del("\t");                                  //  Tab seperated
        std::vector<std::string> temp;    
        file_ptr.append(del);   

        while ((pos = file_ptr.find(del)) != std::string::npos) //  Find position of tab
        {   
            temp.push_back(file_ptr.substr(0, pos));            //  Extract word
            file_ptr.erase(0, pos + del.length());              //  Delete tab
        }   

        data.push_back(temp);                                   //  Add the line
        counter++;

      }

      infile.close(); 
   }
   else std::cout << "Input file can not be opened." << std::endl;

}


/*
    {PARTITION}
    @param arr       : input array
    @param start     : start index of subarray
    @param end       : end index of subarray
    @param randomize : random/deterministic mode

    Sorts the array as elements less than pivot to the left
                                more than pivot to the right

    @return pivot   : returns the index of pivot in sorted array

*/
int partition(std::vector< std::vector<std::string> >& arr, int start, int end, bool randomize, int axis)
{
    std::string pivot;
    int p_index = start;
    
    /*Random Mode*/
    if(randomize)                                        
    {
        int pivot_index; 
        srand(time(NULL));
        pivot_index = rand() % (end-start) + start;     //  Get random index
                            
        pivot = arr[pivot_index][3];                    //  Get random pivot
        std::swap(arr[pivot_index], arr[end]);          //  Move pivot to rightmost

    }

    /*Deterministic Mode*/
    else pivot = arr[end][3];                           //  Always get the rightmost                       

    std::string pivot_copy(arr[end][3]);                //  Copy name column

    for(int j=0; j<pivot_copy.size(); j++)  
        pivot_copy[j] = std::tolower(pivot_copy[j]);    //  Make lower case for case insensitivity

    for(int i=start; i<end; i++)                        //  Traverse array
    {               
       std::string arr_copy(arr[i][3]);

       for(int j=0; j<arr_copy.size(); j++)            // All lower case for case insensitivity
           arr_copy[j] = std::tolower(arr_copy[j]);
       
       if( (arr[i][5] < arr[end][5])               // Check country
           || ((arr[end][5] == arr[i][5])          // If country is same,
               && (arr_copy < pivot_copy))         // check name
           || ((arr[end][5] == arr[i][5])          // If country and
              && (arr_copy == pivot_copy)          // name is same
               && (arr[i][1] < arr[end][1])))      // check date
           { 

           std::swap(arr[i], arr[p_index]);        // Swap 
           p_index++;                              // Increment index                     
        }     
    } 
    std::swap(arr[p_index], arr[end]);                 // Swap pivot with p_index to place in between
    return p_index;

}

/*
    {QUICKSORT}
    @param arr       : input array
    @param start     : start index of subarray
    @param end       : end index of subarray
    @param randomize : random/deterministic mode

    Recursively calls function to sort sub arrays divided by the pivot

*/
void quick_sort(std::vector<std::vector<std::string> >& arr, int start, int end, bool randomize, int axis)
{
    if(start >= end) return;                                    // If 0 or 1 element is left in segment 
    
    int p_index = partition(arr, start, end, randomize, axis);  // Get pivot's index and quicksorted array 
    std::cout << p_index << std::endl;
    quick_sort(arr, start, p_index - 1, randomize, axis);       // Quicksort left  to pivot by recursive call
    quick_sort(arr, p_index + 1, end, randomize, axis);         // Quicksort right to pivot by recursive call

}

int main(int argc, char** argv){

    int rand_mode = true;
    if(strcmp(argv[2], "deterministic") == 0)       
        rand_mode = false;
    
    int number_tweets = std::stoi(argv[1]);
    std::string input_file = argv[3], output_file = argv[4];

    std::vector<std::vector<std::string> > data;
    read_csv(input_file, data, number_tweets);
    
    clock_t t;
    t = clock();

    /**SORTING**/
    quick_sort(data, 0, data.size() - 1, rand_mode, 5);

    t = clock() - t;

    printf ("Sorted in %f miliseconds.\n", float(t*1.0/ (CLOCKS_PER_SEC/1000)));

    //OUTPUT FILE OPERATIONS
    /*std::ofstream outfile;
    outfile.open(output_file);  

    if(outfile.is_open())
    {
        for(int i=0; i<data.size(); i++)
        {
            for(int j=0; j<6; j++)
                outfile << data[i][j] << "\t" ;

            outfile << "\n";
        }
    }

    else std::cout << "Output file can not be opened." << std::endl;
    outfile.close();*/
    
}
