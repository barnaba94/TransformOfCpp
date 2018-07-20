#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>    // std::min_element, std::max_element
#include <cmath>

#define MAX_X 640
#define MAX_Y 400
#define M_PI 3.14159265358979323846

typedef unsigned short int usi;

class Point
{
public:
  float x;
  float y;
};

class rgb
{
public:
  Point p1;

  usi r;
  usi g;
  usi b;
};

int OpenFile(std::ifstream&, char*);
rgb** ImportData(std::ifstream& file1, float& max_right, std::vector<rgb>& v1);
int CheckFilledPoint(std::vector<rgb>& v1, rgb** pRgb);
void ReleaseMemory(rgb** pRgb, std::ifstream& file1);
float FieldOfFrameAndMIddlePoint(std::vector<rgb>& v1, float&, float&, float& );
float RotationOfField(std::vector<rgb>& v1, float max_right, float& pX, float& pY);
float MiddlePointFrame2nd(std::vector<rgb>& v, float dl1, float angle, float max_right, float pX, float pY, float skalowanie, float& SRODEK_KONCOWY_X, float& SRODEK_KONCOWY_Y);