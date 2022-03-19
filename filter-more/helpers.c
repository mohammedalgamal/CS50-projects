#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (int) floor(width / 2); j++)
        {
            RGBTRIPLE *a = &image[i][j];
            RGBTRIPLE *b = &image[i][(width - 1) - j];
            RGBTRIPLE temp;
            temp = *a;
            *a = *b;
            *b = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //temp image
    RGBTRIPLE timage[height][width];
    for (int ii = 0; ii < height; ii++)
    {
        for (int jj = 0; jj < width; jj++)
        {
            //copy image
            timage[ii][jj] = image[ii][jj];
        }
    }
    //modifing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //temp array
            RGBTRIPLE temp[9];
            int count = 0;
            //cell itself
            temp[count] = timage[i][j];
            count++;
            //if middle
            if (i > 0 && j > 0 && i < height - 1 && j < width - 1)
            {
                temp[count] = timage[i + 1][j + 1];
                count++;
                temp[count] = timage[i - 1][j - 1];
                count++;
                temp[count] = timage[i + 1][j - 1];
                count++;
                temp[count] = timage[i - 1][j + 1];
                count++;
                temp[count] = timage[i + 1][j];
                count++;
                temp[count] = timage[i - 1][j];
                count++;
                temp[count] = timage[i][j + 1];
                count++;
                temp[count] = timage[i][j - 1];
                count++;
            }
            //if corner UL
            else if (i == 0 && j == 0)
            {
                temp[count] = timage[i][j + 1];
                count++;
                temp[count] = timage[i + 1][j + 1];
                count++;
                temp[count] = timage[i + 1][j];
                count++;
            }
            //if corner LR
            else if (i == height - 1 && j == width - 1)
            {
                temp[count] = timage[i][j - 1];
                count++;
                temp[count] = timage[i - 1][j - 1];
                count++;
                temp[count] = timage[i - 1][j];
                count++;
            }
            //if corner UR
            else if (i == 0 && j == width - 1)
            {
                temp[count] = timage[i][j - 1];
                count++;
                temp[count] = timage[i + 1][j - 1];
                count++;
                temp[count] = timage[i + 1][j];
                count++;
            }
            //if corner UL
            else if (i == height - 1 && j == 0)
            {
                temp[count] = timage[i][j + 1];
                count++;
                temp[count] = timage[i - 1][j + 1];
                count++;
                temp[count] = timage[i - 1][j];
                count++;
            }
            //if edge U
            else if (i == 0 && j != 0 && j != width - 1)
            {
                temp[count] = timage[i + 1][j + 1];
                count++;
                temp[count] = timage[i + 1][j - 1];
                count++;
                temp[count] = timage[i + 1][j];
                count++;
                temp[count] = timage[i][j + 1];
                count++;
                temp[count] = timage[i][j - 1];
                count++;
            }
            //if edge D
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                temp[count] = timage[i - 1][j - 1];
                count++;
                temp[count] = timage[i - 1][j + 1];
                count++;
                temp[count] = timage[i - 1][j];
                count++;
                temp[count] = timage[i][j + 1];
                count++;
                temp[count] = timage[i][j - 1];
                count++;
            }
            //if edge R
            else if (j == 0 && i != 0 && i != height - 1)
            {
                temp[count] = timage[i + 1][j + 1];
                count++;
                temp[count] = timage[i - 1][j + 1];
                count++;
                temp[count] = timage[i + 1][j];
                count++;
                temp[count] = timage[i - 1][j];
                count++;
                temp[count] = timage[i][j + 1];
                count++;
            }
            //if edge L
            else if (j == width - 1 && i != 0 && i != height - 1)
            {
                temp[count] = timage[i - 1][j - 1];
                count++;
                temp[count] = timage[i + 1][j - 1];
                count++;
                temp[count] = timage[i + 1][j];
                count++;
                temp[count] = timage[i - 1][j];
                count++;
                temp[count] = timage[i][j - 1];
                count++;
            }
            //colors
            int r = 0;
            int b = 0;
            int g = 0;
            //avg
            float rt, rb, rg;
            //loop temp array
            for (int k = 0; k < count; k++)
            {
                r += temp[k].rgbtRed;
                b += temp[k].rgbtBlue;
                g += temp[k].rgbtGreen;
            }
            //calculate avg
            rt = r / (float) count;
            rb = b / (float) count;
            rg = g / (float) count;
            //change actual image
            image[i][j].rgbtRed = (int) round(rt);
            image[i][j].rgbtBlue = (int) round(rb);
            image[i][j].rgbtGreen = (int) round(rg);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //temp image
    RGBTRIPLE timage[height][width];

    //GX
    int gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};

    //GY
    int gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    //temp image
    for (int ii = 0; ii < height; ii++)
    {
        for (int jj = 0; jj < width; jj++)
        {
            //copy image
            timage[ii][jj] = image[ii][jj];
        }
    }

    //modifing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //temp array
            RGBTRIPLE temp[9];
            for (int xx = 0; xx < 9; xx++)
            {
                temp[xx].rgbtRed = 0;
                temp[xx].rgbtBlue = 0;
                temp[xx].rgbtGreen = 0;
            }
            int count = 9;
            //cell itself
            //if middle
            if (i > 0 && j > 0 && i < height - 1 && j < width - 1)
            {
                temp[0] = timage[i - 1][j - 1];
                temp[1] = timage[i - 1][j];
                temp[2] = timage[i - 1][j + 1];
                temp[3] = timage[i][j - 1];
                temp[4] = timage[i][j];
                temp[5] = timage[i][j + 1];
                temp[6] = timage[i + 1][j - 1];
                temp[7] = timage[i + 1][j];
                temp[8] = timage[i + 1][j + 1];
            }
            //if corner UL
            else if (i == 0 && j == 0)
            {
                temp[4] = timage[i][j];
                temp[5] = timage[i][j + 1];
                temp[7] = timage[i + 1][j];
                temp[8] = timage[i + 1][j + 1];
            }
            //if corner LR
            else if (i == height - 1 && j == width - 1)
            {
                temp[0] = timage[i - 1][j - 1];
                temp[1] = timage[i - 1][j];
                temp[3] = timage[i][j - 1];
                temp[4] = timage[i][j];
            }
            //if corner UR
            else if (i == 0 && j == width - 1)
            {
                temp[3] = timage[i][j - 1];
                temp[4] = timage[i][j];
                temp[6] = timage[i + 1][j - 1];
                temp[7] = timage[i + 1][j];
            }
            //if corner UL
            else if (i == height - 1 && j == 0)
            {
                temp[1] = timage[i - 1][j];
                temp[2] = timage[i - 1][j + 1];
                temp[4] = timage[i][j];
                temp[5] = timage[i][j + 1];
            }
            //if edge U
            else if (i == 0 && j != 0 && j != width - 1)
            {
                temp[3] = timage[i][j - 1];
                temp[4] = timage[i][j];
                temp[5] = timage[i][j + 1];
                temp[6] = timage[i + 1][j - 1];
                temp[7] = timage[i + 1][j];
                temp[8] = timage[i + 1][j + 1];
            }
            //if edge D
            else if (i == height - 1 && j != 0 && j != width - 1)
            {
                temp[0] = timage[i - 1][j - 1];
                temp[1] = timage[i - 1][j];
                temp[2] = timage[i - 1][j + 1];
                temp[3] = timage[i][j - 1];
                temp[4] = timage[i][j];
                temp[5] = timage[i][j + 1];
            }
            //if edge L
            else if (j == 0 && i != 0 && i != height - 1)
            {
                temp[1] = timage[i - 1][j];
                temp[2] = timage[i - 1][j + 1];
                temp[4] = timage[i][j];
                temp[5] = timage[i][j + 1];
                temp[7] = timage[i + 1][j];
                temp[8] = timage[i + 1][j + 1];
            }
            //if edge R
            else if (j == width - 1 && i != 0 && i != height - 1)
            {
                temp[0] = timage[i - 1][j - 1];
                temp[1] = timage[i - 1][j];
                temp[3] = timage[i][j - 1];
                temp[4] = timage[i][j];
                temp[6] = timage[i + 1][j - 1];
                temp[7] = timage[i + 1][j];
            }
            //temp arryas
            int rx[9];
            int bx[9];
            int gxx[9];
            int ry[9];
            int by[9];
            int gyy[9];

            //loop temp array
            for (int k = 0; k < count; k++)
            {
                rx[k] = temp[k].rgbtRed * gx[k];
                ry[k] = temp[k].rgbtRed * gy[k];
                bx[k] = temp[k].rgbtBlue * gx[k];
                by[k] = temp[k].rgbtBlue * gy[k];
                gxx[k] = temp[k].rgbtGreen * gx[k];
                gyy[k] = temp[k].rgbtGreen * gy[k];
            }
            //intger values
            int srx = 0;
            int sry = 0;
            int sbx = 0;
            int sby = 0;
            int sgx = 0;
            int sgy = 0;

            //sum of array
            for (int kk = 0; kk < count; kk++)
            {
                srx += rx[kk];
                sry += ry[kk];
                sbx += bx[kk];
                sby += by[kk];
                sgx += gxx[kk];
                sgy += gyy[kk];
            }

            //final values
            int rt, bt, gt;
            //calculate
            rt = (int) round(sqrt((srx * srx) + (sry * sry)));
            bt = (int) round(sqrt((sbx * sbx) + (sby * sby)));
            gt = (int) round(sqrt((sgx * sgx) + (sgy * sgy)));

            //normalize
            if (rt > 255)
            {
                rt = 255;
            }
            if (bt > 255)
            {
                bt = 255;
            }
            if (gt > 255)
            {
                gt = 255;
            }
            //change actual image
            image[i][j].rgbtRed = rt;
            image[i][j].rgbtBlue = bt;
            image[i][j].rgbtGreen = gt;
        }
    }
    return;
}
