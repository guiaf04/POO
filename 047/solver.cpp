#include <iostream>
#include <fn.hpp>
#include <iomanip>
#include <math.h>

using namespace std;
using namespace fn;

class Point2D{
public:
  double x;
  double y;

  Point2D(double x = 0, double y = 0) : x(x), y(y){
  }

  Point2D(string serial){
    stringstream ss(serial);
    char c {};
    ss >> c >> x >> c >> y >> c;
  }

  string toString() const{
    ostringstream oss;
    oss << fixed <<setprecision(2) <<"(" << x << ", " << y << ")";
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
  return os << shape.toString();
}

class Circle: public Shape{
  Point2D center;
  double radius;

public:
  Circle(Point2D center , double radius = 0) : Shape("Circ"){
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
    return radius * radius * M_PI;
  }

  double getPerimeter() override{
    return 2 * radius * M_PI;
  }

  virtual string toString() const override{
    stringstream ss;
    ss << fixed << setprecision(2) << this->getName() << ": " << "C=" << this->center.toString() << ", R=" << setprecision(2) << this->radius;

    return ss.str();
  }
};

class Rectangle: public Shape{
public:
    Point2D p1;
    Point2D p2;

    Rectangle(Point2D p1, Point2D p2) : Shape("Rect"){
      this->p1 = p1;
      this->p2 = p2;
    }

    bool inside(Point2D p) override{
      if(p1.x <= p.x && p.x <= p2.x && p1.y <= p.y && p.y <= p2.y)
        return true;
      else
        return false;
    }

    double getArea() override{
      return abs(p2.x - p1.x) * abs(p2.y - p1.y);
    }

    double getPerimeter() override{
      return 2 * (abs(p2.x - p1.x) + abs(p2.y - p1.y));
    }

    virtual string toString() const override{
      stringstream ss;
      ss << getName() << ": P1=" << p1.toString() << " P2=" << p2.toString();
      return ss.str();
    }
};

int main(){
  vector<shared_ptr<Shape>> shapes;

  while(true){
    auto line = input();
    auto args = split(line, ' ');
    write("$" + line);

    if(args[0] == "end"){
      break;
    }else if(args[0] == "show"){
      shapes | fn::MAP([](auto shape) {return shape->toString(); })
             | fn::JOIN("\n")
             | fn::WRITE();
    }else if(args[0] == "circle"){
      auto x = number(args[1]);
      auto y = number(args[2]);
      auto r = number(args[3]);
      Point2D center(x, y);
      shapes.push_back(make_shared<Circle>(center, r));
    }else if(args[0] == "rect"){
      auto p1 = Point2D{number(args[1]), number(args[2])};
      auto p2 = Point2D{number(args[3]), number(args[4])};
      shapes.push_back(make_shared<Rectangle>(p1, p2));
    }else if(args[0] == "info"){
      for (auto shape : shapes) {
                fn::write(fn::format("{}: A={%.2f} P={%.2f}", 
                shape->getName(), shape->getArea(), shape->getPerimeter()));
            }
    }else{
      cout << "fail: invalid command\n";
    }
  }
}