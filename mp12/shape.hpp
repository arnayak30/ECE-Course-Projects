#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include <iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	  //Base class' constructor should be called in derived classes'
	  //constructor to initizlize Shape's private variable 
  	Shape(string name){
  	  name_ = name;
  	};
  	string getName(){
  	  return name_;
  	};
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  
  string name_;
  
};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
template <class T>
class Rectangle : public Shape{
public:
  
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle"){
  	  width_ = width;
  	  length_ = length;
  	}
	
  	double getArea() const{return width_*length_;}
	
  	double getVolume() const{return 0;}
	  
	  Rectangle<T> operator + (const Rectangle<T>& rec){return Rectangle(width_+rec.width_,length_+rec.length_);}
	
  	Rectangle<T> operator - (const Rectangle<T>& rec){
  	  double newLength = (length_-rec.length_)>0 ? length_-rec.length_ : 0;
  	  double newWidth = (width_-rec.width_)>0 ? width_-rec.width_ : 0;      
	    return Rectangle(newWidth, newLength);
	  }
	  T getWidth() const{return width_;}
	
	  T getLength() const{return length_;}
	  
private:
  
	  T width_;
    T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  
  	Circle(double radius):Shape("Circle"){
  	  radius_ = radius;
  	}
	
  	double getArea() const{
  	  return radius_*radius_*M_PI;
  	}
	
 	  double getVolume() const{
 	    return 0;
 	  }
	
  	Circle operator + (const Circle& cir){
  	  return Circle(radius_+cir.radius_);
  	}
	
	  Circle operator - (const Circle& cir){
	    return Circle((radius_-cir.radius_) > 0 ? radius_-cir.radius_ : 0);
	  }

	  double getRadius() const{
	    return radius_;
	  }
	
private:
	  
	  double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  
  	Sphere(double radius):Shape("Shape"){
  	  radius_ = radius;
  	}

    double getArea() const{
      return radius_*radius_*4*M_PI;
    }
  	double getVolume() const{
  	  return (4.0/3.0)*radius_*radius_*radius_*M_PI;
  	}

	  Sphere operator + (const Sphere& sph){
	    return Sphere(radius_+sph.radius_);
	  }

	  Sphere operator - (const Sphere& sph){
	    return Sphere((radius_-sph.radius_) > 0 ? radius_-sph.radius_ : 0);
	  }
	
	  double getRadius() const{
	    return radius_;
	  }

private:
  
	  double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism"){
  	  width_ = width;
  	  length_ = length;
  	  height_ = height;
  	}
	
	  double getArea() const{
	    return (2*length_*width_)+(2*length_*height_)+(2*height_*width_);
	  }
  	double getVolume() const{
  	  return length_*width_*height_;
  	}
	
	  RectPrism operator + (const RectPrism& rectp){
	    return RectPrism(width_+rectp.width_,length_+rectp.length_,height_+rectp.height_);
	  }
	
	  RectPrism operator - (const RectPrism& rectp){
	    return RectPrism(max(0.0, width_-rectp.width_), max(0.0, length_-rectp.length_), max(0.0, height_-rectp.height_));
	  }
	
	  double getWidth() const{
	    return width_;
	  }
	
	  double getLength() const{
	    return length_;
	  }
	
	  double getHeight() const{
	    return height_;
	  }
	  
private:
  
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {
	//@@Insert your code here
	list<Shape*> vector;
	int size;
	string type;
  ifstream ifs (file_name, std::ifstream::in);
  ifs >> size; 
  
  for (int i = 0; i < size; i++){
    ifs>>type;
    Shape* ptr = NULL;
    if (type == "Circle"){
      double r;
      ifs >> r;
      ptr = new Circle(r);
    }
    if (type == "Rectangle"){
      double w, h;
      ifs >> w >> h;
      ptr = new Rectangle<double>(w, h);
    }
    if (type == "Sphere"){
      double r;
      ifs >> r;
      ptr = new Sphere(r);
    }
    if (type == "RectPrism"){
      double w, l, h;
      ifs >> w >> l >> h;
      ptr = new RectPrism(w,l,h);
    }
    vector.push_back(ptr);
  }
  ifs.close();
	return vector;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
  double max_area = 0;
  list<Shape*>::const_iterator iter = shapes.begin();
  while(iter != shapes.end()){
    double curr = (*iter)->getArea();
    if(curr > max_area){
      max_area = curr;
    }
    iter++;
  }
  return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
  list<Shape*>::const_iterator iter = shapes.begin();
  while(iter != shapes.end()){
    double curr = (*iter)->getVolume();
    if(curr > max_volume){
      max_volume = curr;
    }
    iter++;
  }
	return max_volume;
}
#endif

