
//Autores: Jhon Idrovo, Edison Lopez, Andres Ponce

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

typedef int element;
using namespace std;

vector<vector<double>> createFilter(int, int, double);
vector<vector<int>> gFiltered;
vector<vector<int>> sFiltered;
vector<vector<int>> sFiltered2;
vector<vector<int>> anglesGeneral;

vector<vector<int>> non;
vector<vector<int>> thres;

vector<vector<double>> createFilter(int row, int column, double sigmaIn)
    {
        vector<vector<double>> filter;

        for (int i = 0; i < row; i++)
        {
            vector<double> col;
            for (int j = 0; j < column; j++)
            {
                col.push_back(-1);
            }
            filter.push_back(col);
        }

        float coordSum = 0;
        float constant = 2.0 * sigmaIn * sigmaIn;

        // Sum is for normalization
        float sum = 0.0;

        for (int x = - row/2; x <= row/2; x++)
        {
            for (int y = -column/2; y <= column/2; y++)
            {
                coordSum = (x*x + y*y);
                filter[x + row/2][y + column/2] = (exp(-(coordSum) / constant)) / (M_PI * constant);
                sum += filter[x + row/2][y + column/2];
            }
        }

        // Normalize the Filter
        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
                filter[i][j] /= sum;

        return filter;

    }
    vector<vector<int>> useFilter(vector<vector<int>> img_in, vector<vector<double>> filterIn)
    {
        int size = (int)filterIn.size()/2;
        vector<vector<int>> filteredImg=img_in;
        for (int i = size; i < img_in.size() - size; i++)
        {
            for (int j = size; j < img_in[i].size() - size; j++)
            {
                double sum = 0;

                for (int x = 0; x < filterIn.size(); x++)
                    for (int y = 0; y < filterIn.size(); y++)
                    {
                        sum += filterIn[x][y] * (double)(img_in[i + x - size][j + y - size]);
                    }

                filteredImg[i-size][j-size] = sum;
            }

        }
        return filteredImg;
    }
   vector<vector<int>> sobel(vector<vector<int>> gFiltered){
        double x1[] = {-1.0, 0, 1.0};
        double x2[] = {-2.0, 0, 2.0};
        double x3[] = {-1.0, 0, 1.0};

        vector<vector<double>> xFilter(3);
        xFilter[0].assign(x1, x1+3);
        xFilter[1].assign(x2, x2+3);
        xFilter[2].assign(x3, x3+3);
        //Sobel Y Filter
        double y1[] = {1.0, 2.0, 1.0};
        double y2[] = {0, 0, 0};
        double y3[] = {-1.0, -2.0, -1.0};

        vector<vector<double>> yFilter(3);
        yFilter[0].assign(y1, y1+3);
        yFilter[1].assign(y2, y2+3);
        yFilter[2].assign(y3, y3+3);

        //Limit Size
        int size = (int)xFilter.size()/2;

        //Mat gFiltered;
        //Mat filteredImg = Mat(gFiltered.rows - 2*size, gFiltered.cols - 2*size, CV_8UC1);
        vector<vector<int>> filteredImg=gFiltered;
        //Mat angles = Mat(gFiltered.rows - 2*size, gFiltered.cols - 2*size, CV_32FC1); //AngleMap
        vector<vector<int>> angles=gFiltered;        //angles2(angles.begin(),angles.end());
        //angles=gFiltered;
        //vector<vector<float>> angles3=angles2;

        for (int i = size; i < gFiltered.size() - size; i++)
        {
            for (int j = size; j < gFiltered[i].size() - size; j++)
            {
                double sumx = 0;
                double sumy = 0;

                for (int x = 0; x < xFilter.size(); x++)
                    for (int y = 0; y < xFilter.size(); y++)
                    {
                        sumx += xFilter[x][y] * (double)(gFiltered[i + x - size][j + y - size]); //Sobel_X Filter Value
                        sumy += yFilter[x][y] * (double)(gFiltered[i + x - size][j + y - size]); //Sobel_Y Filter Value
                    }
                double sumxsq = sumx*sumx;
                double sumysq = sumy*sumy;

                double sq2 = sqrt(sumxsq + sumysq);

                if(sq2 > 255) //Unsigned Char Fix
                    sq2 =255;
                filteredImg[i-size][j-size] = sq2;

                if(sumx==0) //Arctan Fix
                    angles[i-size][j-size] = 90;
                else
                    angles[i-size][j-size] = atan(sumy/sumx);
            }
        }

        return filteredImg;
    }
   vector<vector<int>> sobel2(vector<vector<int>> gFiltered){
        double x1[] = {-1.0, 0, 1.0};
        double x2[] = {-2.0, 0, 2.0};
        double x3[] = {-1.0, 0, 1.0};

        vector<vector<double>> xFilter(3);
        xFilter[0].assign(x1, x1+3);
        xFilter[1].assign(x2, x2+3);
        xFilter[2].assign(x3, x3+3);
        //Sobel Y Filter
        double y1[] = {1.0, 2.0, 1.0};
        double y2[] = {0, 0, 0};
        double y3[] = {-1.0, -2.0, -1.0};

        vector<vector<double>> yFilter(3);
        yFilter[0].assign(y1, y1+3);
        yFilter[1].assign(y2, y2+3);
        yFilter[2].assign(y3, y3+3);

        //Limit Size
        int size = (int)xFilter.size()/2;

        //Mat gFiltered;
        //Mat filteredImg = Mat(gFiltered.rows - 2*size, gFiltered.cols - 2*size, CV_8UC1);
        vector<vector<int>> filteredImg=gFiltered;
        //Mat angles = Mat(gFiltered.rows - 2*size, gFiltered.cols - 2*size, CV_32FC1); //AngleMap
        vector<vector<int>> angles=gFiltered;
        //angles2(angles.begin(),angles.end());
        //angles=gFiltered;
        //vector<vector<float>> angles3=angles2;

        for (int i = size; i < gFiltered.size() - size; i++)
        {
            for (int j = size; j < gFiltered[i].size() - size; j++)
            {
                double sumx = 0;
                double sumy = 0;

                for (int x = 0; x < xFilter.size(); x++)
                    for (int y = 0; y < xFilter.size(); y++)
                    {
                        sumx += xFilter[x][y] * (double)(gFiltered[i + x - size][j + y - size]); //Sobel_X Filter Value
                        sumy += yFilter[x][y] * (double)(gFiltered[i + x - size][j + y - size]); //Sobel_Y Filter Value
                    }
                double sumxsq = sumx*sumx;
                double sumysq = sumy*sumy;

                double sq2 = sqrt(sumxsq + sumysq);

                if(sq2 > 255) //Unsigned Char Fix
                    sq2 =255;
                filteredImg[i-size][j-size] = sq2;

                if(sumx==0) //Arctan Fix
                    angles[i-size][j-size] = 90;
                else
                    angles[i-size][j-size] = atan(sumy/sumx);
            }
        }

        return angles;
    }


   vector<vector<int>> nonMaxSupp(vector<vector<int>> sFiltered,vector<vector<int>> angles2)
   {
       //Mat nonMaxSupped = Mat(sFiltered.rows-2, sFiltered.cols-2, CV_8UC1);
       vector<vector<int>> nonMaxSupped=sFiltered;
       vector<vector<int>> angles=angles2;
          for (int i=1; i< sFiltered.size() - 1; i++) {
              for (int j=1; j<sFiltered[i].size() - 1; j++) {
                  float Tangent = angles[i][j];

                  nonMaxSupped[i-1][j-1] = sFiltered[i][j];
                  //Horizontal Edge
                  if (((-22.5 < Tangent) && (Tangent <= 22.5)) || ((157.5 < Tangent) && (Tangent <= -157.5)))
                  {
                      if ((sFiltered[i][j] < sFiltered[i][j+1]) || (sFiltered[i][j] < sFiltered[i][j-1]))
                          nonMaxSupped[i-1][j-1] = 0;
                  }
                  //Vertical Edge
                  if (((-112.5 < Tangent) && (Tangent <= -67.5)) || ((67.5 < Tangent) && (Tangent <= 112.5)))
                  {
                      if ((sFiltered[i][j] < sFiltered[i+1][j]) || (sFiltered[i][j] < sFiltered[i-1][j]))
                          nonMaxSupped[i-1][j-1] = 0;
                  }

                  //-45 Degree Edge
                  if (((-67.5 < Tangent) && (Tangent <= -22.5)) || ((112.5 < Tangent) && (Tangent <= 157.5)))
                  {
                      if ((sFiltered[i][j] < sFiltered[i-1][j+1]) || (sFiltered[i][j] < sFiltered[i+1][j-1]))
                          nonMaxSupped[i-1][j-1] = 0;
                  }

                  //45 Degree Edge
                  if (((-157.5 < Tangent) && (Tangent <= -112.5)) || ((22.5 < Tangent) && (Tangent <= 67.5)))
                  {
                      if ((sFiltered[i][j] < sFiltered[i+1][j+1]) || (sFiltered[i][j]< sFiltered[i-1][j-1]))
                          nonMaxSupped[i-1][j-1] = 0;
                  }
              }
          }
       return nonMaxSupped;
   }
   vector<vector<int>> threshold(vector<vector<int>> imgin,int low, int high)
   {
       if(low > 255)
           low = 255;
       if(high > 255)
           high = 255;

       vector<vector<int>> EdgeMat=imgin;
       //Mat EdgeMat = Mat(imgin.rows, imgin.cols, imgin.type());

       for (int i=0; i<imgin.size(); i++)
       {
           for (int j = 0; j<imgin[i].size(); j++)
           {
               EdgeMat[i][j] = imgin[i][j];
               if(EdgeMat[i][j] > high)
                   EdgeMat[i][j] = 255;
               else if(EdgeMat[i][j] < low)
                   EdgeMat[i][j] = 0;
               else
               {
                   bool anyHigh = false;
                   bool anyBetween = false;
                   for (int x=i-1; x < i+2; x++)
                   {
                       for (int y = j-1; y<j+2; y++)
                       {
                           if(x <= 0 || y <= 0 || x > EdgeMat.size() || y > EdgeMat[x].size()) //Out of bounds
                               continue;
                           else
                           {
                               if(EdgeMat[x][y] > high)
                               {
                                   EdgeMat[i][j] = 255;
                                   anyHigh = true;
                                   break;
                               }
                               else if(EdgeMat[x][y] >= low)
                                   anyBetween = true;
                           }
                       }
                       if(anyHigh)
                           break;
                   }
                   if(!anyHigh && anyBetween)
                       for (int x=i-2; x < i+3; x++)
                       {
                           for (int y = j-1; y<j+3; y++)
                           {
                               if(x < 0 || y < 0 || x > EdgeMat.size() || y > EdgeMat[x].size()) //Out of bounds
                                   continue;
                               else
                               {
                                   if(EdgeMat[x][y] > high)
                                   {
                                       EdgeMat[i][j] = 255;
                                       anyHigh = true;
                                       break;
                                   }
                               }
                           }
                           if(anyHigh)
                               break;
                       }
                   if(!anyHigh)
                       EdgeMat[i][j] = 0;
               }
           }
       }
       return EdgeMat;
   }

int main(){
        vector<vector<int>> vect
                    {
                            {1, 2, 3, 100, 210, 40, 50},
                            {4, 5, 6, 110, 230, 30, 55},
                            {7, 8, 9, 140, 210, 20, 52},
                            {4, 27, 36, 160, 20, 60, 50},
                            {5, 58, 65, 10, 240, 70, 75},
                            {7, 89, 94, 40, 220, 80, 82}
                    };
        vector<vector<double>> filter = createFilter(3, 3, 1);

        //Print filter
        for (int i = 0; i<filter.size(); i++)
        {
            for (int j = 0; j<filter[i].size(); j++)
            {
                cout << filter[i][j] << " ";
            }
        }
        gFiltered=useFilter(vect,filter);
        sFiltered=sobel(gFiltered);
        sFiltered2=sobel2(gFiltered);
        anglesGeneral=sFiltered2;
        non=nonMaxSupp(sFiltered,anglesGeneral);
        thres=threshold(non,30,50);

        cout << "GFiltered, Filas:"<<gFiltered.size()<<"; Columnas:"<<gFiltered[0].size() << endl;
        cout << "SFiltered, Filas:"<<sFiltered.size()<<"; Columnas:"<<sFiltered[0].size() << endl;
        cout << "SFiltered2, Filas:"<<sFiltered2.size()<<"; Columnas:"<<sFiltered2[0].size() << endl;
        cout << "NonMaxSupp, Filas:"<<non.size()<<"; Columnas:"<<non[0].size() << endl;
        cout << "Threshold, Filas:"<<thres.size()<<"; Columnas:"<<thres[0].size() << endl;

}

