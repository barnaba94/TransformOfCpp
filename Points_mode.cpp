#include "points.h"


int OpenFile( std::ifstream& file1, char* filename)
{
  file1.open(filename);
  if ( file1.fail() )
  {
    std::cout << "Cannot open 1st file!";
    exit(1);
  }
}

rgb** ImportData( std::ifstream& file1, float& max_right, std::vector<rgb>& v1)
{

  rgb** pRgb = new rgb*[MAX_Y];
  for (int i = 0; i <MAX_Y; i++)
    pRgb[i] = new  rgb[MAX_X];

  for (int i = 0; i < MAX_Y; i++)
    for (int j = 0; j < MAX_X; j++)
      file1 >> pRgb[i][j].p1.x >> pRgb[i][j].p1.y >> pRgb[i][j].r >> pRgb[i][j].g >> pRgb[i][j].b;
  
  max_right = pRgb[MAX_Y - 1][MAX_X - 1].p1.x;
  
  return pRgb;
}

int CheckFilledPoint(std::vector<rgb>& v1 , rgb** pRgb)
{
  for (int i = 0; i < MAX_Y; i++)
    for (int j = 0; j < MAX_X; j++)
    {
      if (!((pRgb[i][j].r == 255) && (pRgb[i][j].g == 255) && (pRgb[i][j].b == 255)))
        v1.push_back(pRgb[i][j]);
    }
  return 0;
}

void ReleaseMemory(rgb** pRgb, std::ifstream& file1)
{
  for (int i = 0; i < MAX_Y; i++)
    delete [] pRgb[i];
  delete [] pRgb;

  file1.close();
  return;
}

float FieldOfFrameAndMIddlePoint(std::vector<rgb>& v1, float& middlePoint_X, float& middlePoint_Y, float& odl_1_2_x)
{
  std::vector< float > vec_x;
  std::vector< float > vec_y;

  for (auto& vec_itr : v1)
  {
    vec_x.push_back(vec_itr.p1.x);
    vec_y.push_back(vec_itr.p1.y);
  }

  float X_min = *std::min_element(vec_x.begin(), vec_x.end());
  float Y_min = *std::min_element(vec_y.begin(), vec_y.end());

  float X_max = *std::max_element(vec_x.begin(), vec_x.end());
  float Y_max = *std::max_element(vec_y.begin(), vec_y.end());

  //field
  float pole = (Y_max - Y_min) * (X_max - X_min);
  odl_1_2_x = (X_max - X_min) / 2;
  std::cout <<"dl: "<< odl_1_2_x << std::endl;
  float odl_1_2_y = (Y_max - Y_min) / 2;

  middlePoint_X = odl_1_2_x + X_min;
  middlePoint_Y = odl_1_2_y + Y_min;

  std::cout << " srodek:  Xmiddle = " << middlePoint_X <<" Ymiddle = "<< middlePoint_Y<<std::endl;
  return pole;
}

float RotationOfField(std::vector<rgb>& v1, float max_right, float& pX, float& pY)
{
  //rotation
  std::vector<rgb> right_side;

  for (auto& p : v1)
  {
    if (p.p1.x > (max_right / 2))
      right_side.push_back(p);
  }

  std::vector<float> vec_rightside_x;
  std::vector<float> vec_rightside_y;

  for (auto& vec_itr : right_side)
  {
    vec_rightside_x.push_back(vec_itr.p1.x);
    vec_rightside_y.push_back(vec_itr.p1.y);
  }

  float max_Y_rightside = *std::max_element(vec_rightside_y.begin(), vec_rightside_y.end());
  float XofMax_Y_rightside;

  for (auto& vec_itr : right_side)
    if (vec_itr.p1.y == max_Y_rightside)
    {
      XofMax_Y_rightside = vec_itr.p1.x;
    }

  float max_X_rightside = *std::max_element(vec_rightside_x.begin(), vec_rightside_x.end());
  float YofMax_X_rightside;
  for (auto& vec_itr : right_side)
    if (vec_itr.p1.x == max_X_rightside)
    {
      YofMax_X_rightside = vec_itr.p1.y;
    }
  //std::cout << "XofYmaxR: " << XofMax_Y_rightside << " YmaxR: " << max_Y_rightside << " XmaxR: " << max_X_rightside << " YofXmaxR: " << YofMax_X_rightside<<std::endl;

  float kat_temp = atan((abs(XofMax_Y_rightside - max_X_rightside)) / (abs(YofMax_X_rightside - max_Y_rightside))); ///angle 1st file
  float angle = kat_temp *  (180 / M_PI);
  std::cout << " kat: " << angle <<"st"<<std::endl;

  pX = max_X_rightside;
  pY = YofMax_X_rightside;

  return angle;
}

//auxiliary functions
inline float rownanie_liniowe(float angle, float x, float y )
{
  return ( y - tan(angle * (M_PI / 180)) * x );
}

inline float rownanie_liniowe_prost(float angle, float x, float y)
{
  return (y -  ((-1) / (tan(angle * (M_PI / 180))) ) * x  );
}

inline float rozw_x(float angle, float b2, float b1)
{
  return ( (b2-b1) / (tan(angle * (M_PI / 180)) - ((-1) / (tan(angle * (M_PI / 180)))) ) ) ;
}


float MiddlePointFrame2nd( std::vector<rgb>& v, float dl1, float angle, float max_right, float pX, float pY, float skalowanie, float& SRODEK_KONCOWY_X, float& SRODEK_KONCOWY_Y )
{
  std::vector<float> vec_x1;
  std::vector<float> vec_y1;

  for (auto& vec_itr : v)
  {
    vec_x1.push_back(vec_itr.p1.x);
    vec_y1.push_back(vec_itr.p1.y);
  }

  float max_Y = *std::max_element(vec_y1.begin(), vec_y1.end() );
  float XofMax_Y; //to normalny
  for (auto& vec_itr : v)
    if (vec_itr.p1.y == max_Y)
      XofMax_Y = vec_itr.p1.x;
  
  std::vector<rgb> vec_leftside;
  std::vector<float> vec_leftside_x;
  std::vector<float> vec_leftside_y;


  for (auto& vec_itr1 : v)
  {
    if( vec_itr1.p1.x < max_right / 2 )
      vec_leftside.push_back( vec_itr1 );
  }

  for (auto& vec_itr2 : vec_leftside)
  {
    vec_leftside_x.push_back( vec_itr2.p1.x );
    vec_leftside_y.push_back( vec_itr2.p1.y );
  }

  float min_leftside_Y = *std::min_element(vec_leftside_y.begin(), vec_leftside_y.end());
  float Xofmin_leftside_Y;

  for (auto& vec_itr2 : vec_leftside)
  {
    if (vec_itr2.p1.y == min_leftside_Y)
      Xofmin_leftside_Y = vec_itr2.p1.x;
  }

  //równania liniowe
  //liniowe górne
  float b_top = rownanie_liniowe( -angle, XofMax_Y, max_Y);
  
  //liniowe dolne
  float b_bottom = rownanie_liniowe( -angle, Xofmin_leftside_Y, min_leftside_Y);

  //przecinajace
  float b_przecinajace = rownanie_liniowe_prost(-angle , pX, pY );

  float górne_przeciecie_x = rozw_x(-angle, b_przecinajace, b_top );
  float dolne_przeciecie_x = rozw_x(-angle, b_przecinajace, b_bottom );

  //srodek
  float srodek_x = (górne_przeciecie_x + dolne_przeciecie_x) / 2;
  float srodek_y = ( (-1) / (tan(-angle * (M_PI / 180))) ) * srodek_x + b_przecinajace;

  SRODEK_KONCOWY_Y = srodek_y + sin(angle * (M_PI / 180) ) * skalowanie * dl1;
  SRODEK_KONCOWY_X = srodek_x - cos(angle * (M_PI / 180) ) * skalowanie * dl1;

  return 0;
}