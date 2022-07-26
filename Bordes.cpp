#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    Mat imagen;
    Mat imagen2;
    imagen = imread("church.jpg", 1);
    imagen2 = imread("building.jpg", 0);

    uchar Azul;
    uchar Verde;
    uchar Rojo;

    cv::Vec3b pixel;

    int filas = imagen.rows;
    int columnas = imagen.cols;
    int filas2 = imagen2.rows;
    int columnas2 = imagen2.cols;

    double RobertsFilas[2][2] = { {1,0}, {0,-1} };
    double RobertsColumnas[2][2] = { {0,1}, {-1,0} };

    double SumaFilasRoberts = 0;
    double SumaColumnasRoberts = 0;
    double SumaFilasRoberts2 = 0;
    double SumaColumnasRoberts2 = 0;

    double PrewittFilas[3][3] = { {-1,0,1}, {-1,0,1}, {-1,0,1} };
    double PrewittColumnas[3][3] = { {1,1,1}, {0,0,0}, {-1,-1,-1} };

    double SumaFilasPrewitt = 0;
    double SumaColumnasPrewitt = 0;
    double SumaFilasPrewitt2 = 0;
    double SumaColumnasPrewitt2 = 0;

    double SobelFilas[3][3] = { {-1,0,1}, {-2,0,2}, {-1,0,1} };
    double SobelColumnas[3][3] = { {1,2,1}, {0,0,0}, {-1,-2,-1} };

    double SumaFilasSobel = 0;
    double SumaColumnasSobel = 0;
    double SumaFilasSobel2 = 0;
    double SumaColumnasSobel2 = 0;

    double FreiG1[3][3] = { {1,sqrt(2),1}, {0,0,0}, {-1,-sqrt(2),-1} };
    double FreiG2[3][3] = { {1,0,-1}, {sqrt(2),0,-sqrt(2)}, {1,0,-1} };
    double FreiG3[3][3] = { {0,-1,sqrt(2)}, {1,0,-1}, {-sqrt(2),1,0} };
    double FreiG4[3][3] = { {sqrt(2),-1,0}, {-1,0,1}, {0,1,-sqrt(2)} };

    double SumaFreiG1 = 0;
    double SumaFreiG2 = 0;
    double SumaFreiG3 = 0;
    double SumaFreiG4 = 0;
    double SumaFreiG1L = 0;
    double SumaFreiG2L = 0;
    double SumaFreiG3L = 0;
    double SumaFreiG4L = 0;

    Mat gris(filas, columnas, CV_8UC1);
    Mat bordesR(filas + 1, columnas + 1, CV_8UC1);
    Mat bordesR2(filas2 + 1, columnas2 + 1, CV_8UC1);
    Mat imagenRoberts(filas, columnas, CV_8UC1);
    Mat imagenRoberts2(filas2, columnas2, CV_8UC1);
    Mat bordesP(filas + 2, columnas + 2, CV_8UC1);
    Mat bordesP2(filas2 + 2, columnas2 + 2, CV_8UC1);
    Mat imagenPrewitt(filas, columnas, CV_8UC1);
    Mat imagenPrewitt2(filas2, columnas2, CV_8UC1);
    Mat bordesS(filas + 2, columnas + 2, CV_8UC1);
    Mat bordesS2(filas2 + 2, columnas2 + 2, CV_8UC1);
    Mat imagenSobel(filas, columnas, CV_8UC1);
    Mat imagenSobel2(filas2, columnas2, CV_8UC1);
    Mat bordesF(filas + 2, columnas + 2, CV_8UC1);
    Mat bordesF2(filas2 + 2, columnas2 + 2, CV_8UC1);
    Mat imagenFrei(filas, columnas, CV_8UC1);
    Mat imagenFrei2(filas2, columnas2, CV_8UC1);


    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            pixel = imagen.at<Vec3b>(i, j);

            Azul = pixel[0];
            Verde = pixel[1];
            Rojo = pixel[2];

            gris.at<uchar>(i, j) = (Azul + Verde + Rojo) / 3;
        }
    }

    for (int i = 0; i < filas + 1; i++)
    {
        for (int j = 0; j < columnas + 1; j++)
        {
            if ((i == filas) || (j == columnas))
            {
                bordesR.at<uchar>(i, j) = 0;
            }
            else
            {
                bordesR.at<uchar>(i, j) = gris.at<uchar>(i, j);
            }
        }
    }

    for (int i = 0; i < filas2 + 1; i++)
    {
        for (int j = 0; j < columnas2 + 1; j++)
        {
            if ((i == filas2) || (j == columnas2))
            {
                bordesR2.at<uchar>(i, j) = 0;
            }
            else
            {
                bordesR2.at<uchar>(i, j) = imagen2.at<uchar>(i, j);
            }
        }
    }

    for (int i = 0; i < filas + 2; i++)
    {
        for (int j = 0; j < columnas + 2; j++)
        {
            if ((i == filas) || (j == columnas) || (i == filas + 1) || (j == columnas + 1))
            {
                bordesP.at<uchar>(i, j) = 0;
                bordesS.at<uchar>(i, j) = 0;
                bordesF.at<uchar>(i, j) = 0;
            }
            else
            {
                bordesP.at<uchar>(i, j) = gris.at<uchar>(i, j);
                bordesS.at<uchar>(i, j) = gris.at<uchar>(i, j);
                bordesF.at<uchar>(i, j) = gris.at<uchar>(i, j);
            }
        }
    }

    for (int i = 0; i < filas2 + 2; i++)
    {
        for (int j = 0; j < columnas2 + 2; j++)
        {
            if ((i == filas2) || (j == columnas2) || (i == filas2 + 1) || (j == columnas2 + 1))
            {
                bordesP2.at<uchar>(i, j) = 0;
                bordesS2.at<uchar>(i, j) = 0;
                bordesF2.at<uchar>(i, j) = 0;
            }
            else
            {
                bordesP2.at<uchar>(i, j) = imagen2.at<uchar>(i, j);
                bordesS2.at<uchar>(i, j) = imagen2.at<uchar>(i, j);
                bordesF2.at<uchar>(i, j) = imagen2.at<uchar>(i, j);
            }
        }
    }

    /////////////////////////   BORDES ROBERTS  //////////////////////////////////////
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                for (int l = 0; l < 2; l++)
                {
                    SumaFilasRoberts = SumaFilasRoberts + ( (RobertsFilas[k][l])*(bordesR.at<uchar>(i + k, j + l) ) );
                    SumaColumnasRoberts = SumaColumnasRoberts + 
                                        ( (RobertsColumnas[k][l])*(bordesR.at<uchar>(i + k, j + l) ) );
                }
            }

            imagenRoberts.at<uchar>(i,j) = uint8_t(sqrt((SumaFilasRoberts*SumaFilasRoberts) 
                                                + (SumaColumnasRoberts*SumaColumnasRoberts)));
            SumaFilasRoberts = 0;
            SumaColumnasRoberts = 0;
        }
    }

    for (int i = 0; i < filas2; i++)
    {
        for (int j = 0; j < columnas2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                for (int l = 0; l < 2; l++)
                {
                    SumaFilasRoberts2 = SumaFilasRoberts2 + 
                        ((RobertsFilas[k][l]) * (bordesR2.at<uchar>(i + k, j + l)));
                    SumaColumnasRoberts2 = SumaColumnasRoberts2 +
                        ((RobertsColumnas[k][l]) * (bordesR2.at<uchar>(i + k, j + l)));
                }
            }

            imagenRoberts2.at<uchar>(i, j) = uint8_t(sqrt((SumaFilasRoberts2 * SumaFilasRoberts2)
                                            + (SumaColumnasRoberts2 * SumaColumnasRoberts2)));
            SumaFilasRoberts2 = 0;
            SumaColumnasRoberts2 = 0;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////

    /////////////////////////   BORDES PREWITT  //////////////////////////////////////
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    SumaFilasPrewitt = SumaFilasPrewitt + 
                        ((PrewittFilas[k][l]) * (bordesP.at<uchar>(i + k, j + l)));
                    SumaColumnasPrewitt = SumaColumnasPrewitt + 
                        ((PrewittColumnas[k][l]) * (bordesP.at<uchar>(i + k, j + l)));
                }
            }

            imagenPrewitt.at<uchar>(i, j) = uint8_t(sqrt((SumaFilasPrewitt * SumaFilasPrewitt) 
                                            + (SumaColumnasPrewitt * SumaColumnasPrewitt)));
            SumaFilasPrewitt = 0;
            SumaColumnasPrewitt = 0;
        }
    }

    for (int i = 0; i < filas2; i++)
    {
        for (int j = 0; j < columnas2; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    SumaFilasPrewitt2 = SumaFilasPrewitt2 +
                        ((PrewittFilas[k][l]) * (bordesP2.at<uchar>(i + k, j + l)));
                    SumaColumnasPrewitt2 = SumaColumnasPrewitt2 +
                        ((PrewittColumnas[k][l]) * (bordesP2.at<uchar>(i + k, j + l)));
                }
            }

            imagenPrewitt2.at<uchar>(i, j) = uint8_t(sqrt((SumaFilasPrewitt2 * SumaFilasPrewitt2)
                + (SumaColumnasPrewitt2 * SumaColumnasPrewitt2)));
            SumaFilasPrewitt2 = 0;
            SumaColumnasPrewitt2 = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////

    /////////////////////////   BORDES SOBEL  //////////////////////////////////////
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    SumaFilasSobel = SumaFilasSobel + 
                        ((SobelFilas[k][l]) * (bordesS.at<uchar>(i + k, j + l)));
                    SumaColumnasSobel = SumaColumnasSobel + 
                        ((SobelColumnas[k][l]) * (bordesS.at<uchar>(i + k, j + l)));
                }
            }

            imagenSobel.at<uchar>(i, j) = uint8_t(sqrt((SumaFilasSobel * SumaFilasSobel) 
                                        + (SumaColumnasSobel * SumaColumnasSobel)));
            SumaFilasSobel = 0;
            SumaColumnasSobel = 0;
        }
    }

    for (int i = 0; i < filas2; i++)
    {
        for (int j = 0; j < columnas2; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    SumaFilasSobel2 = SumaFilasSobel2 +
                        ((SobelFilas[k][l]) * (bordesS2.at<uchar>(i + k, j + l)));
                    SumaColumnasSobel2 = SumaColumnasSobel2 +
                        ((SobelColumnas[k][l]) * (bordesS2.at<uchar>(i + k, j + l)));
                }
            }

            imagenSobel2.at<uchar>(i, j) = uint8_t(sqrt((SumaFilasSobel2 * SumaFilasSobel2)
                + (SumaColumnasSobel2 * SumaColumnasSobel2)));
            SumaFilasSobel2 = 0;
            SumaColumnasSobel2 = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////

    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            FreiG1[i][j] = ( 1 / (2*sqrt(2) ) )*(FreiG1[i][j]);
            FreiG2[i][j] = ( 1 / (2*sqrt(2) ) )*(FreiG2[i][j]);
            FreiG3[i][j] = ( 1 / (2*sqrt(2) ) )*(FreiG3[i][j]);
            FreiG4[i][j] = ( 1 / (2*sqrt(2) ) )*(FreiG4[i][j]);
        }
    }

    /////////////////////////   BORDES FREI-CHEN  //////////////////////////////////////
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    SumaFreiG1 = SumaFreiG1 + 
                        ((FreiG1[k][l]) * (bordesF.at<uchar>(i + k, j + l)));
                    SumaFreiG2 = SumaFreiG2 + 
                        ((FreiG2[k][l]) * (bordesF.at<uchar>(i + k, j + l)));
                    SumaFreiG3 = SumaFreiG3 + 
                        ((FreiG3[k][l]) * (bordesF.at<uchar>(i + k, j + l)));
                    SumaFreiG4 = SumaFreiG4 + 
                        ((FreiG4[k][l]) * (bordesF.at<uchar>(i + k, j + l)));
                }
            }

            imagenFrei.at<uchar>(i, j) = uint8_t(sqrt( (SumaFreiG1*SumaFreiG1) + 
                                            (SumaFreiG2 * SumaFreiG2) + 
                                        (SumaFreiG3 * SumaFreiG3) + 
                                            (SumaFreiG4 * SumaFreiG4) ) );

            SumaFreiG1 = 0;
            SumaFreiG2 = 0;
            SumaFreiG3 = 0;
            SumaFreiG4 = 0;
        }
    }

    for (int i = 0; i < filas2; i++)
    {
        for (int j = 0; j < columnas2; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    SumaFreiG1L = SumaFreiG1L +
                        ((FreiG1[k][l]) * (bordesF2.at<uchar>(i + k, j + l)));
                    SumaFreiG2L = SumaFreiG2L +
                        ((FreiG2[k][l]) * (bordesF2.at<uchar>(i + k, j + l)));
                    SumaFreiG3L = SumaFreiG3L +
                        ((FreiG3[k][l]) * (bordesF2.at<uchar>(i + k, j + l)));
                    SumaFreiG4L = SumaFreiG4L +
                        ((FreiG4[k][l]) * (bordesF2.at<uchar>(i + k, j + l)));
                }
            }

            imagenFrei2.at<uchar>(i, j) = uint8_t(sqrt((SumaFreiG1L * SumaFreiG1L) +
                (SumaFreiG2L * SumaFreiG2L) +
                (SumaFreiG3L * SumaFreiG3L) +
                (SumaFreiG4L * SumaFreiG4L)));

            SumaFreiG1L = 0;
            SumaFreiG2L = 0;
            SumaFreiG3L = 0;
            SumaFreiG4L = 0;
        }
    }
    //////////////////////////////////////////////////////////////////////////////////

    //namedWindow("Imagen gris", WINDOW_NORMAL);
    //imshow("Imagen gris", gris);
    //namedWindow("Imagen bordes roberts", WINDOW_NORMAL);
    //imshow("Imagen bordes roberts", imagenRoberts);
    //namedWindow("Imagen bordes prewitt", WINDOW_NORMAL);
    //imshow("Imagen bordes prewitt", imagenPrewitt);
    //namedWindow("Imagen bordes sobel", WINDOW_NORMAL);
    //imshow("Imagen bordes sobel", imagenSobel);
    //namedWindow("Imagen bordes Frei", WINDOW_NORMAL);
    //imshow("Imagen bordes Frei", imagenFrei);

    /*
    namedWindow("Imagen gris2", WINDOW_NORMAL);
    imshow("Imagen gris2", imagen2);
    namedWindow("Imagen bordes roberts2", WINDOW_NORMAL);
    imshow("Imagen bordes roberts2", imagenRoberts2);
    namedWindow("Imagen bordes prewitt2", WINDOW_NORMAL);
    imshow("Imagen bordes prewitt2", imagenPrewitt2);
    namedWindow("Imagen bordes sobel2", WINDOW_NORMAL);
    imshow("Imagen bordes sobel2", imagenSobel2);
    namedWindow("Imagen bordes Frei2", WINDOW_NORMAL);
    imshow("Imagen bordes Frei2", imagenFrei2);
    */

    printf("%d", columnas2);

    waitKey();
    return 0;
}