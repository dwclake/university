/*
 Devon Webb CSCI 41
 lab_3.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

// Functions for Exercise 1
double Exercise1Pt1(double a[], double b[], int n, int m) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result += a[i] * b[j];
        }
    }
    return result;
}
void Exercise1Pt2(double a[], double b[], int n, int m, double* result) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            *result += a[i] * b[j];
        }
    }
}
void Exercise1Pt3(double a[], double b[], int n, int m, double& result) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result += a[i] * b[j];
        }
    }
}
//Functions for Exercise 2
double GetMax1(double* a, int n) {
    double max = 0;
    for (int i = 0; i < n; i++) {
           if (a[i] > max) max = a[i];
    }
    return max;
}
void GetMax2(double* a, int n, double* vmax) {
    for (int i = 0; i < n; i++) {
        if (a[i] > *vmax) *vmax = a[i];
    }
}
void GetMax3(double* a, int n, double& vmax) {
    for (int i = 0; i < n; i++) {
        if (a[i] > vmax) vmax = a[i];
    }
}
//Functions for Exercise 3
struct Point3D {
    double x;
    double y;
    double z;
};
double DistanceBetweenTwoPoints(Point3D a, Point3D b) {
    double distance = sqrt( pow((a.x - b.x), 2)
            + pow((a.y - b.y), 2)
            + pow((a.z - b.z), 2));
    return distance;
}
double DistanceBetweenPointandOrigin(Point3D a) {
    double distance = sqrt( pow((a.x - 0), 2)
                            + pow((a.y - 0), 2)
                            + pow((a.z - 0), 2));
    return distance;
}
Point3D AddTwoPoints(Point3D a, Point3D b) {
    //your code here
}
Point3D SubtractTwoPoints(Point3D a, Point3D b) {
    //your code here
}
//Functions for Exercise 4
class ThreeDPoint {
public:
    ThreeDPoint(); // Default constructor
    ThreeDPoint(int,int,int); // Constructor with 3 values
    ThreeDPoint(const ThreeDPoint&); // Copy constructor
    int GetX(); // accessor functions
    int GetY();
    int GetZ();
    void SetX(int); // modifier functions
    void SetY(int);
    void SetZ(int);
    double DistanceBetweenTwoPoints(ThreeDPoint*);
    double DistanceBetweenPointandOrigin();
    ThreeDPoint operator+ (const ThreeDPoint&); // + operator overloading
    ThreeDPoint operator- (const ThreeDPoint&); // - operator overloading
private:
    int x;
    int y;
    int z;
protected:
};
ThreeDPoint::ThreeDPoint() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
ThreeDPoint::ThreeDPoint(int tempX, int tempY, int tempZ) {
    this->x = tempX;
    this->y = tempY;
    this->z = tempZ;
}
ThreeDPoint::ThreeDPoint(const ThreeDPoint& input3DPoint) {
    this->x = input3DPoint.x;
    this->y = input3DPoint.y;
    this->z = input3DPoint.z;
}
int ThreeDPoint::GetX() {
    return this->x;
}
int ThreeDPoint::GetY() {
    return this->y;
}
int ThreeDPoint::GetZ() {
    return this->z;
}
void ThreeDPoint::SetX(int tempX) {
    this->x = tempX;
}
void ThreeDPoint::SetY(int tempY) {
    this->y = tempY;
}
void ThreeDPoint::SetZ(int tempZ) {
    this->z = tempZ;
}
double ThreeDPoint::DistanceBetweenTwoPoints(ThreeDPoint* b) {
    double distance = sqrt( pow((this->x - b->x), 2)
                            + pow((this->y - b->y), 2)
                            + pow((this->z - b->z), 2));
    return distance;
}
double ThreeDPoint::DistanceBetweenPointandOrigin() {
    double distance = sqrt( pow((this->x - 0), 2)
                            + pow((this->y - 0), 2)
                            + pow((this->z - 0), 2));
    return distance;
};
ThreeDPoint ThreeDPoint::operator+ (const ThreeDPoint& b) {
    ThreeDPoint temp((this->x + b.x),
                     (this->y + b.y),
                     (this->z + b.z));
    
    return temp;
};
ThreeDPoint ThreeDPoint::operator- (const ThreeDPoint& b) {
    ThreeDPoint temp((this->x - b.x),
                     (this->y - b.y),
                     (this->z - b.z));
    
    return temp;
};
int main()
{
    // Exercise 1
    cout << "Exercise 1: " << endl << endl;
    
    double x[]{1,2,3};
    double y[]{2,3};
    double result = Exercise1Pt1(x, y, 3, 2);
    cout << "\tExercise1Pt1: " << result << endl;
    
    double* result2 = new double;
    *result2 = 0;
    Exercise1Pt2(x, y, 3, 2, result2);
    cout << "\tExercise1Pt2: " << *result2 << endl;
    delete result2;
    
    double result3 = 0;
    Exercise1Pt3(x, y, 3, 2, result3);
    cout << "\tExercise1Pt3: " << result3 << endl << endl;
    
    // Exercise 2
    cout << "Exercise 2: " << endl << endl;
    
    double max = GetMax1(x, 3);
    cout << "\tGetMax1: " << max << endl;
    
    double* max2 = new double;
    GetMax2(x, 3, max2);
    cout << "\tGetMax2: " << max << endl;
    delete max2;
    
    double max3 = 0;
    GetMax3(x, 3, max3);
    cout << "\tGetMax3: " << max << endl << endl;
    
    // Exercise 3
    cout << "Exercise 3: " << endl << endl;
    
    Point3D point1{5,5,3};
    cout << "\tpoint1: " << point1.x << " " << point1.y << " " << point1.z << endl;
    
    Point3D point2{1,1,1};
    cout << "\tpoint2: " << point2.x << " " << point2.y << " " << point2.z << endl;
    
    double dis = DistanceBetweenTwoPoints(point1, point2);
    cout << "\tDistanceBetweenTwoPoints: " << dis << endl;
    
    double dis2 = DistanceBetweenPointandOrigin(point1);
    cout << "\tDistanceBetweenPointandOrigin: " << dis2 << endl << endl;
    
    // Exercise 4
    cout << "Exercise 4: " << endl << endl;
    
    ThreeDPoint point3d;
    cout << "\tdefault constructor: " << point3d.GetX() << " " << point3d.GetY() << " " << point3d.GetZ() << endl;
    
    ThreeDPoint point3d1(5,5,3);
    cout << "\toverload constructor: " << point3d1.GetX() << " " << point3d1.GetY() << " " << point3d1.GetZ() << endl;
    
    ThreeDPoint* point3d2 = new ThreeDPoint();
    *point3d2 = ThreeDPoint(1,1,1);
    cout << "\tcopy constructor: " << point3d2->GetX() << " " << point3d2->GetY() << " " << point3d2->GetZ() << endl;
    
    double dis3D = point3d1.DistanceBetweenTwoPoints(point3d2);
    cout << "\tDistanceBetweenTwoPoints: " << dis3D << endl;
    
    double dis3D2 = point3d1.DistanceBetweenPointandOrigin();
    cout << "\tDistanceBetweenPointandOrigin: " << dis3D2 << endl;
    
    ThreeDPoint point3d3 = point3d1 + *point3d2;
    cout << "\t+ overload: " << point3d3.GetX() << " " << point3d3.GetY() << " " << point3d3.GetZ() << endl;
    
    ThreeDPoint point3d4 = point3d1 - *point3d2;
    cout << "\t- overload: " << point3d4.GetX() << " " << point3d4.GetY() << " " << point3d4.GetZ() << endl;
    
    delete point3d2;
    
    return 0;
}