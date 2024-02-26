#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <math.h>

using namespace std;

vector<char *> split(char *s, char *delim)
{
  vector<char *> result;
  char *section;
  section = strtok(s, delim);
  while (section != NULL)
  {
    result.push_back(section);
    section = strtok(0, delim);
  }
  return result;
}

vector<vector<float>> createMatrix(char *s)
{
  vector<char *> withoutOpeningBracket = split(s, "[");
  vector<char *> withoutClosingBracket = split(withoutOpeningBracket[0], "]");
  char *withoutBrackets = withoutClosingBracket[0];

  vector<char *> rows = split(withoutBrackets, ",");
  vector<vector<float>> Error;

  vector<vector<float>> Matrix;

  for (int i = 0; i < rows.size(); ++i)
  {
    vector<char *> cols = split(rows[i], " ");
    vector<float> colsAsNums;
    for (int j = 0; j < cols.size(); ++j)
    {
      float colsAsF = stof(cols[j]);
      colsAsNums.push_back(colsAsF);
    }

    Matrix.push_back(colsAsNums);
  }
  int num = Matrix[0].size();
  for (int i = 1; i < Matrix.size(); i++)
  {
    if (Matrix[i].size() != num)
    {
      return Error;
    }
  }
  return Matrix;
}

void printMatrix(vector<vector<float>> matrix)
{
  cout << "[";
  for (int i = 0; i < matrix.size(); i++)
  {
    if (i != 0)
    {
      cout << ", ";
    }
    for (int j = 0; j < matrix[i].size(); j++)
    {
      if (j != 0)
      {
        cout << " ";
        
      }

      cout << matrix[i][j];
    }
  }
  cout << "]";
}

vector<vector<float>> MultiplyByScalar(vector<vector<float>> Matrix1, float n)

{

  vector<vector<float>> ResultofMult;

  for (int i = 0; i < Matrix1.size(); i++)
  {
    vector<float> rows;
    for (int j = 0; j < Matrix1.size(); j++)
    {
      float r = n * Matrix1[i][j];
      rows.push_back(r);
    }
    ResultofMult.push_back(rows);
  }
  return ResultofMult;
}
vector<vector<float>> Transpose(vector<vector<float>> matrix)
{

  vector<vector<float>> Newmatrix;
  for (int i = 0; i < matrix[0].size(); i++)
  {
    vector<float> Rows;

    for (int j = 0; j < matrix.size(); j++)
    {
      Rows.push_back(matrix[j][i]);
    }
    Newmatrix.push_back(Rows);
  }
  return Newmatrix;
}

vector<vector<float>> getElementMinorMatrix(vector<vector<float>> matrix, int i, int j)
{
  vector<vector<float>> minormatrix;
  for (int x = 0; x < matrix.size(); x++)
  {

    if (x == i)
    {
      continue;
    }
    vector<float> rows;

    for (int y = 0; y < matrix[0].size(); y++)
    {
      if (y == j)
      {
        continue;
      }

      rows.push_back(matrix[x][y]);
    }
    minormatrix.push_back(rows);
  }
  return minormatrix;
}
float Determinant(vector<vector<float>> matrix)
{
  float determinant = 0;
  if (matrix.size() == 1 && matrix[0].size() == 1)
  {
    return matrix[0][0];
  }
  if (matrix.size() == 2 && matrix[0].size() == 2)
  {
    return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
  }

  int sign = 1;

  for (int j = 0; j < matrix.size(); ++j)
  {
    vector<vector<float>> submatrix = getElementMinorMatrix(matrix, 0, j);
    determinant += sign * matrix[0][j] * Determinant(submatrix);
    sign *= -1;
  }

  return determinant;
}
vector<vector<float>> Adjointmatrix(vector<vector<float>> matrix)
{
  int sign;
  vector<vector<float>> adjointmatrix;
  for (int i = 0; i < matrix.size(); i++)
  {
    vector<float> rows;
    for (int j = 0; j < matrix[0].size(); j++)
    {
      if ((i + j) % 2 == 0)
        sign = 1;
      else
        sign = -1;
      float newelement = sign*Determinant(getElementMinorMatrix(matrix, i, j));
      rows.push_back(newelement);
    
    }
    adjointmatrix.push_back(rows);
  }

  return Transpose(adjointmatrix);
}
vector<vector<float>> inversematrix(vector<vector<float>> matrix)
{
  float d = Determinant(matrix);
  vector<vector<float>> inversematrix = MultiplyByScalar(Adjointmatrix(matrix), 1 / d);
  return inversematrix;
}

int main()
{
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */

   char s1[1000];
   cin.getline(s1, 1000);
   char operation[2];
   cin.getline(operation, 2);
   char op = operation[0];


  vector<vector<float>> matrix1 = createMatrix(s1);
  if (matrix1.size() == 0)
  {
    cout << "ERROR!";
    return 0;
  }

    switch (op)
    {
    case 'T':
      printMatrix(Transpose(matrix1));
      break;

    case 'D':
     cout<<Determinant(matrix1);
     break;

    case 'I':
         printMatrix(inversematrix(matrix1));
    }

  return 0;
}

