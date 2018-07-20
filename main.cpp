#include "points.h"

int main(int argc, char** argv)
{
  //file1 
  std::ifstream file1;
  float max_right;
  OpenFile(file1,"img1.dat");
  std::vector<rgb> v1;
  rgb** pRgb = ImportData(file1, max_right, v1);
  CheckFilledPoint(v1, pRgb);
  ReleaseMemory(pRgb, file1);

  float dl1;
  float middle_frame1_x;
  float middle_frame1_y;

  FieldOfFrameAndMIddlePoint( v1, middle_frame1_x, middle_frame1_y, dl1 );

  float pX1;
  float pY1;
  float angle1 = RotationOfField(v1, max_right, pX1, pY1);

  //file2
  std::ifstream file2;
  OpenFile(file2, "img2.dat");
  std::vector<rgb> v2;
  rgb** pRgb2 = ImportData(file2, max_right, v2);
  CheckFilledPoint(v2, pRgb2);
  ReleaseMemory(pRgb2, file1);

  //potrzebne
  float pX;
  float pY;
  float angle2 = RotationOfField(v2, max_right, pX, pY);

  //answer: rotation of transform
  float AnsAngle = angle1 - angle2;
  std::cout << "kat: " << AnsAngle << std::endl;
  
  //answer: scaling
  float scaling = ( v2.size() / static_cast<float>( v1.size() ) );
  std::cout <<"skalowanie: "<< scaling * 100<<" % "<<std::endl;

  //answer: transform middle point of frame
  float SRODEK_KONCOWY_X;
  float SRODEK_KONCOWY_Y;
  MiddlePointFrame2nd( v2, dl1, AnsAngle, max_right, pX, pY, scaling, SRODEK_KONCOWY_X, SRODEK_KONCOWY_Y);
  
  float przesuniecie_x = SRODEK_KONCOWY_X - middle_frame1_x;
  float przesuniecie_y = SRODEK_KONCOWY_Y - middle_frame1_y;

  std::cout<<"Xprzesuniecie: " << przesuniecie_x <<"  "<<std::endl;
  std::cout<<"Yprzesuniecie: " << przesuniecie_y <<"  "<<std::endl;

  getchar();
  return 0;
}