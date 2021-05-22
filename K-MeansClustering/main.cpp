#include <fstream>  
#include <iostream>  
#include <sstream>
#include <ctime>    
#include <vector>
#include <string>

//Epoch number for Kmeans
#define epoch 4

class Base{
  public:
  double x,y;

  Base():x(0),y(0){}
  Base(double x_in,double y_in):x(x_in),y(y_in){}

};

class Point: public Base{
  public:

  int cluster_id;
  double min_dist;

  Point():Base(),
    cluster_id(-1),
    min_dist(__DBL_MAX__){}

  Point(double in_x, double in_y):
    Base(in_x,in_y),
    cluster_id(-1),
    //Minimum distance initially infinite
    min_dist(__DBL_MAX__){ 
    }

    double dist(const Point point){
        return (point.x - x) * (point.x - x) 
        + (point.y - y) * (point.y - y);
    }

};

class Cluster{
  public:
  Point* centroid;
  double x_sum, y_sum;
  int point_num;
  int reset;

  Cluster(std::vector<Point>* pts):
          x_sum(0),y_sum(0),
          point_num(0),
          reset(0){
    int index = rand()%pts->size();
    centroid = &(pts->at(index));
  }

  void compute_centroid();
  void reset_cluster();
};

void Cluster::compute_centroid(){
  
    //Delete prior dynamically allocated centroid
    if(reset!=0){
      delete centroid;
      centroid = NULL;
    }

    centroid = new Point(x_sum/point_num,y_sum/point_num);

    reset++;
}

void Cluster::reset_cluster(){
  //Reset clusters before each iteration
  point_num = 0;
  x_sum = 0;
  y_sum = 0;
}


void read(std::vector<Point>& pts,
                        std::string filename
                        ){

    std::ifstream File(filename);
    std::string input;
    double x, y;

    while(getline(File, input)){
        std::stringstream Stream(input);
        std::string value;

        getline(Stream, value, ',');
        x = stof(value);

        getline(Stream, value, '\n');
        y = stof(value);

        pts.push_back(Point(x, y));
    }
}

void kMeans(std::vector<Point>& pts, 
            std::vector<Cluster>& cls
            ){

  for (auto & element : cls)
    element.reset_cluster();

  //For each point
  for(int i=0; i<pts.size();++i){
    double distance;
    //traverse clusters
    for(int j=0;j<cls.size();++j){
      distance = pts.at(i).dist(*cls.at(j).centroid);
      //to find the minimum distance to centroids
      if(distance < pts.at(i).min_dist){
        //assign the point to the cluster
        pts.at(i).min_dist = distance;
        pts.at(i).cluster_id = j;
      }
       
    }
    //Reset min dist for the next iteration
    pts.at(i).min_dist = __DBL_MAX__;
    //Update coordinate sums and number of points
        //in the cluster
    int id = pts.at(i).cluster_id;
    cls.at(id).x_sum += pts.at(i).x;
    cls.at(id).y_sum += pts.at(i).y;
    cls.at(id).point_num++;
    

  }

  //Update centroids
  for (auto & element : cls)
    element.compute_centroid();
  
}

int main(int argc, char *argv[]){
  
  std::string filename;
  filename = argv[1];
  
  //Containers for points and clusters
  std::vector<Point> pts;
  std::vector<Cluster> cls;

  //Csv file read 
  read(pts, filename);
  
  srand(time(0));
  int cluster_num = 3;

  //Initialize clusters with random points
  for(int i=0; i<cluster_num; i++)
    cls.push_back(Cluster(&pts));

  //Iterations of kMeans algorithm
  for(int i=0;i<epoch;++i)
    kMeans(pts,cls);
  
  for (auto & element : pts)
     std::cout << element.cluster_id << " " << element.x << " " << element.y << std::endl
     << cls.at(element.cluster_id).centroid->x << " " << 
     cls.at(element.cluster_id).centroid->y << std::endl;
     
  //Memory management   
  for (auto & element : cls)
     delete element.centroid;   

  return 0;
}
