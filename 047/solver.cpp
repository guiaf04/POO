#include <iostream>
#include <fn.hpp>
#include <iomanip>
#include <math.h>

using namespace std;
using namespace fn;

#define PI 3.14;

class Point2D{
public:
  double x;
  double y;

  Point2D(double x, double y) : x(x), y(y){
  }

  Point2D(string serial){
    stringstream ss(serial);
    char c {};
    ss >> c >> x >> c >> y >> c;
  }

  string toString() const{
    ostringstream oss;
    oss << fixed <<setprecision(2) <<"(" << x << "," << y << ")";
    return oss.str();
  }
};

class Calc{
public:
  static double distance(Point2D p1, Point2D p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
  }
};

class Shape{
  string name;

public:
  Shape(string name){
    this->name = name;
  }

  virtual string getName() const{
    return this->name;
  }

  virtual bool inside(Point2D p) = 0;
  virtual double getArea() = 0;
  virtual double getPerimeter() = 0;
  
  virtual string toString() const{
    return this->getName();
  }
};

ostream& operator<<(ostream& os, const Shape& shape){
  return os << shape.to_string();
}

class Circle: public Shape{
public:
  Point2D center;
  double radius;

  Circle(Point2D center, double radius) : Shape("Circle"){
    this->center = center;
    this->radius = radius;
  }

  bool inside(Point2D p) override{
    if(Calc::distance(center, p) <= radius)
      return true;
    else
      return false;
  }

  double getArea() override{
    return radius * radius * PI;
  }

  double getPerimeter() override{
    return 2 * radius * PI;
  }

  virtual string toString() const override{
    stringstream ss;
    ss << fixed << setprecision(2) << this->getName() << ": " << "C=" << this->center << ", R=" << setprecision(2) << this->radius;

    return ss.str();
  }
};

// class Rectangle: public Shape{
// public:
//     Point2D p1;
//     Point2D p2;

//     Rectangle(Point2D p1, Point2D p2){
//       this->p1 = p1;
//       this->p2 = p2;
//     }

//     bool inside(Point2D p) override{
//       if(p1.x <= p.x && p.x <= p2.x && p1.y <= p.y && p.y <= p2.y)
//         return true;
//       else
//         return false;
//     }

//     double getArea() override{
//       return (p2.x - p1.x) * (p2.y - p1.y);
//     }

//     double getPerimeter() override{
//       return 2 * ((p2.x - p1.x) + (p2.y - p1.y));
//     }

//     string toString() override{
//       stringstream ss;
//       ss << getName() << " " << p1.toString() << " " << p2.toString();
//       return ss.str();
//     }
// };

int main(){
  vector<shared_ptr<Shape>> shapes;

  while(true){
    auto line = input();
    auto args = split(line, ' ');
    write("$" + line);

    if(args[0] == "end"){
      break;
    }else if(args[0] == "show"){
      write(join(shapes, "\n"));
    }else if(args[0] == "circle"){
      auto x = number(args[1]);
      auto y = number(args[2]);
      auto r = number(args[3]);
      shapes.push_back(make_shared<Circle>(Point2D{x,y}, r));
    // }else if(args[0] == "rect"){
    //   auto p1 = Point2D{number(args[1]), number(args[2])};
    //   auto p2 = Point2D{number(args[3]), number(args[4])};
    //   shapes.push_back(make_shared<Rectangle>(p1, p2));
    // }else if(args[0] == "info"){
      
    }else{
      cout << "fail: invalid command\n";
    }
  }
}