#include "helpers.h"
#include<math.h>
#include<stdio.h>

int limit(int RGB)
{
    if(RGB > 255)
    {
        return 255;
    }

    return RGB;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j].rgbtBlue = limit(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            copy[i][j].rgbtGreen = limit(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            copy[i][j].rgbtRed = limit(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }
}

int get_edge(int i, int j, int height, int width, RGBTRIPLE image[i][j], int pos)
{
    int sum_Gx = 0;
    int sum_Gy = 0;
    
    int Gx[3][3] = {{-1,0-1},{-2,0-2},{-1,0,-1}};
    int Gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    
    int x1 = 0;
    for(int x = i - 1; x <= i + 1; x++)
    {
        int y1 = 0;
        for(int y = j - 1; y <= j + 1; y++)
        {
            if(pos == 0)
            {
                sum_Gx += Gx[x1][y1] * image[x][y].rgbtBlue;
                sum_Gy += Gy[x1][y1] * image[x][y].rgbtBlue;
            }
            
            if(pos == 1)
            {
                sum_Gx += Gx[x1][y1] * image[x][y].rgbtBlue;
                sum_Gy += Gy[x1][y1] * image[x][y].rgbtBlue;
            }
            
            if(pos == 2)
            {
                sum_Gx += Gx[x1][y1] * image[x][y].rgbtBlue;
                sum_Gy += Gy[x1][y1] * image[x][y].rgbtBlue;
            }
            
            y1++;
        }
        
        x1++;
    }
    
    return limit(round(sqrt(pow(sum_Gx, 2) + pow(sum_Gy, 2))));

}

// Convert image to sepia
void edge(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j]= image[i][j];
        }
    }
    
    for(int i = 1; i < height - 1; i++)
    {
        for(int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtBlue = get_edge(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = get_edge(i, j, height, width, copy, 1);
            image[i][j].rgbtRed = get_edge(i, j, height, width, copy, 2);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - 1 -j];
            image[i][width - 1 - j] = tmp;
        }
    }
}

int get_blur(int i, int j, int height, int width, RGBTRIPLE image[i][j], int pos)
{
    int sum = 0;
    int count = 0;
    
    for(int x = i - 1; x <= i + 1; x++)
    {
        for(int y = j - 1; y <= j + 1; y++)
        {
            if(x > 0 && x < height && y > 0 && y < width)
            {
                if(pos == 0)
                {
                    sum += image[x][y].rgbtBlue;
                    count++;
                }
                
                if(pos == 1)
                {
                    sum += image[x][y].rgbtGreen;
                    count++;
                }
                
                if(pos == 2)
                {
                    sum += image[x][y].rgbtRed;
                    count++;
                }
            }
        }
    }
    return limit(sum / count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = get_blur(i, j, height, width, copy, 0);
            image[i][j].rgbtGreen = get_blur(i, j, height, width, copy, 1);
            image[i][j].rgbtRed = get_blur(i, j, height, width, copy, 2);
        }
    }
}
