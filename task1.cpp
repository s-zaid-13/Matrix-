#include <iostream>
using namespace std;
#include <string>
// Header
class Matrix
{
private:
    int rows;
    int columns;
    int **data;

public:
    // Constructors
    Matrix(int r, int c);
    Matrix(int n);
    Matrix(const Matrix &m);
    Matrix();
    // Destructor
    ~Matrix();
    // Member Functions
    void inputValues();
    void display();
    void addScalar(int scalar);
    void addMatrix(Matrix &);
    void subtractScalar(int scalar);
    void subtractMatrix(Matrix &);
    void multiplyScalar(int scalar);
    void multiplyMatrix(Matrix &);
    void getElement(int i, int j);
    void setElement(int i, int j);
    int getRows();
    int getColumns();
};
// Non-Member functions for main
int inputNumber();
int inputRows(Matrix);
int inputCols(Matrix);
void inputScalar(int *s);
void operation(Matrix m1);
Matrix inputMatrix(const Matrix &m);

int main()
{
    int option;
    int r, col;
    do
    {
        cout << "1.Create a square matrix		2.Create a rectangular matrix" << endl
             << "Choose your option: ";
        option = inputNumber();
        if (option < 1 || option > 2)
        {
            cout << "Invalid Option!Try again" << endl;
        }
    } while (option < 1 || option > 2);
    cout << "-----------------------" << endl;
    if (option == 1)
    {
        do
        {
            cout << "Enter the no. of rows/columns(positive integer >0) of a square matrix: ";
            r = inputNumber();
            if (r <= 0)
            {
                cout << "Invalid Input!Try Again." << endl;
            }
        } while (r <= 0);
        Matrix m1(r);
        cout << "Enter a element for matrix: " << endl;
        m1.inputValues();
        operation(m1);
    }
    else if (option == 2)
    {
        do
        {
            cout << "Enter the no. of rows(positive integer >0) of a rectangular matrix: ";
            r = inputNumber();
            if (r <= 0)
            {
                cout << "Invalid Input!Try Again." << endl;
            }
        } while (r <= 0);

        do
        {
            cout << "Enter the no. of columns(positive integer >0) of a rectangular matrix: ";
            col = inputNumber();
            if (col <= 0)
            {
                cout << "Invalid Input!Try Again." << endl;
            }
        } while (col <= 0);
        Matrix m1(r, col);
        cout << "Enter a element for matrix: " << endl;
        m1.inputValues();
        operation(m1);
    }
}
// Definations
//  Constructors
Matrix::Matrix(int r, int c)
{
    rows = r;
    columns = c;
    data = new int *[r];
    for (int i = 0; i < r; i++)
    {
        data[i] = new int[c];
    }
}
Matrix::Matrix(int n)
{
    rows = n;
    columns = n;
    data = new int *[n];
    for (int i = 0; i < n; i++)
    {
        data[i] = new int[n];
    }
}
Matrix::Matrix(const Matrix &m)
{
    rows = m.rows;
    columns = m.columns;
    data = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new int[columns];
        for (int j = 0; j < columns; j++)
        {
            data[i][j] = m.data[i][j];
        }
    }
}
Matrix::Matrix()
{
    rows = 0;
    columns = 0;
    data = nullptr;
}
// Destructor
Matrix::~Matrix()
{
    if (data != nullptr)
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] data[i];
        }
        delete[] data;
    }
}
// Member Functions
void Matrix::inputValues()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << "Enter a element at matrix position [" << i << "][" << j << "]: ";
            data[i][j] = inputNumber();
        }
    }
}
void Matrix::display()
{
    cout << "Matrix: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << data[i][j] << "\t";
        }
        cout << endl;
    }
}
void Matrix::addScalar(int scalar)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            data[i][j] += scalar;
        }
    }
    cout << "Scalar Addition Performed" << endl;
}
void Matrix::addMatrix(Matrix &m)
{
    if (rows == m.rows && columns == m.columns)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                data[i][j] += m.data[i][j];
            }
        }
        cout << "Matrices Addition Performed" << endl;
    }
    else
    {
        cout << "Addition cannot be performed" << endl;
    }
}
void Matrix::subtractScalar(int scalar)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            data[i][j] -= scalar;
        }
    }
    cout << "Scalar Subtraction Performed" << endl;
}
void Matrix::subtractMatrix(Matrix &m)
{
    if (rows == m.rows && columns == m.columns)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                data[i][j] -= m.data[i][j];
            }
        }
        cout << "Matrices Subtraction Performed" << endl;
    }
    else
    {
        cout << "Subtraction cannot be performed" << endl;
    }
}
void Matrix::multiplyScalar(int scalar)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            data[i][j] *= scalar;
        }
    }
    cout << "Scalar Multiplication Performed" << endl;
}
void Matrix::multiplyMatrix(Matrix &m)
{
    if (columns == m.rows)
    {
        Matrix result(rows, m.columns);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < m.columns; j++)
            {
                int res = 0;
                for (int k = 0; k < columns; k++)
                {
                    res = res + data[i][k] * m.data[k][j];
                }
                result.data[i][j] = res;
            }
        }
        if (columns != m.columns)
        {
            for (int i = 0; i < rows; i++)
            {
                delete[] data[i];
            }
            delete[] data;
            data = new int *[rows];
            for (int i = 0; i < rows; i++)
            {
                data[i] = new int[m.columns];
            }
            columns = m.columns;
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < m.columns; j++)
            {
                data[i][j] = result.data[i][j];
            }
        }
        cout << "Matrices Multiplication Performed" << endl;
    }
    else
    {
        cout << "Multiplication can't be performed" << endl;
    }
}
void Matrix::getElement(int i, int j)
{
    cout << "Element at position [" << i << "][" << j << "]: " << data[i][j] << endl;
}
void Matrix::setElement(int i, int j)
{
    cout << "Enter a value that modify element at position [" << i << "][" << j << "]: ";
    cin >> data[i][j];
    cout << "Element Modified" << endl;
}
// Getter/setter function
int Matrix::getRows()
{
    return rows;
}
int Matrix::getColumns()
{
    return columns;
}
// Non-Member functions for main
int inputNumber()
{
    int number;
    while (!(cin >> number))
    {
        cout << "Invalid input. Please enter an number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    return number;
}
void inputScalar(int *s)
{
    cout << "Enter a scalar number: ";
    *s = inputNumber();
}

int inputRows(Matrix m1)
{
    int r;
    do
    {
        cout << "Enter a position of row(position range 0 to " << m1.getRows() - 1 << "): ";
        r = inputNumber();
        if (r < 0 || r >= m1.getRows())
        {
            cout << "Invalid Input" << endl;
        }
    } while (r < 0 || r >= m1.getRows());

    return r;
}
int inputCols(Matrix m1)
{
    int col;
    do
    {
        cout << "Enter a position of column(position range 0 to " << m1.getColumns() - 1 << "): ";
        col = inputNumber();
        if (col < 0 || col >= m1.getColumns())
        {
            cout << "Invalid Input!" << endl;
        }
    } while (col < 0 || col >= m1.getColumns());

    return col;
}

void operation(Matrix m1)
{
    int choice;
    int scalar;
    int r, col;

    do
    {
        do
        {
            cout << "________Matrix Operation_________" << endl
                 << "1.Display the matrix" << endl
                 << "2.Add Scalar to matrix" << endl
                 << "3.Subtract Scalar from matrix" << endl
                 << "4.Multiply matrix by scalar" << endl
                 << "5.Add Matrix to matrix" << endl
                 << "6.Subtract Matrix from matrix" << endl
                 << "7.Multiply matrix by matrix" << endl
                 << "8.Get Element of matrix" << endl
                 << "9.Modify element of matrix" << endl
                 << "0.To terminate" << endl
                 << "Choose which opeartion to be performed: ";
            choice = inputNumber();
            if (choice < 0 || choice > 9)
            {
                cout << "Invalid Option!Try again" << endl;
            }
        } while (choice < 0 || choice > 9);
        cout << "-----------------------" << endl;
        switch (choice)
        {
        case 1:
            m1.display();
            break;
        case 2:
            inputScalar(&scalar);
            m1.addScalar(scalar);
            break;
        case 3:
            inputScalar(&scalar);
            m1.subtractScalar(scalar);
            break;
        case 4:
            inputScalar(&scalar);
            m1.multiplyScalar(scalar);
            break;
        case 5:
        {
            Matrix m2 = inputMatrix(m1);
            m1.addMatrix(m2);
            break;
        }
        case 6:
        {
            Matrix m2 = inputMatrix(m1);
            m1.subtractMatrix(m2);
            break;
        }
        case 7:
        {
            Matrix m2 = inputMatrix(m1);
            m1.multiplyMatrix(m2);
            break;
        }
        case 8:
            r = inputRows(m1);
            col = inputCols(m1);
            m1.getElement(r, col);
            break;
        case 9:
            r = inputRows(m1);
            col = inputCols(m1);
            m1.setElement(r, col);
            break;
        case 0:
            cout << "Program Terminate........." << endl;
            return;
            break;
        default:
            cout << "Not a valid Option!!!!" << endl;
            break;
        }
        cout << "-----------------------" << endl;
    } while (choice != 0);
}

Matrix inputMatrix(const Matrix &m)
{
    int option;
    do
    {
        cout << "1. Create new Matrix	2. Use Existing Matrix" << endl
             << "Choose your option: ";
        option = inputNumber();
        if (option < 1 || option > 2)
        {
            cout << "Invalid Input! Try Again." << endl;
        }
    } while (option < 1 || option > 2);
    int rows, cols;
    if (option == 1)
    {
        do
        {
            cout << "Enter the no. of rows(positive integer >0) of a matrix: ";
            rows = inputNumber();
            if (rows <= 0)
            {
                cout << "Invalid Input!Try Again." << endl;
            }
        } while (rows <= 0);

        do
        {
            cout << "Enter the no. of columns(positive integer >0) of a matrix: ";
            cols = inputNumber();
            if (cols <= 0)
            {
                cout << "Invalid Input!Try Again." << endl;
            }
        } while (cols <= 0);
        Matrix m2(rows, cols);
        m2.inputValues();
        return m2;
    }
    else
    {
        return Matrix(m);
    }
}