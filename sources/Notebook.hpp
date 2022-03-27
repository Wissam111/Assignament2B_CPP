
/*
 * AUTHORS: Wissam kabha
 * gitHub: https://github.com/Wissam111
 * Date: 03/2022
 */

#include <iostream>
#include <string>
#include <map>
#include "Direction.hpp"
#include <bits/stdc++.h>
using namespace std;
// typedef unsigned int uint;
/*
 * @brief  this struct represents a char on the page
 */
struct unit_char
{
    char c = '_';
    bool notValid = false;
};

/*
 * @brief  this class represents a page on the notebook
 */
class Page
{

private:
    map<int, map<int, unit_char>> mapP;
    int _numOfPages;

public:
    int maxRow, maxCol;
    int minRow, minCol;
    // write a single char on the page
    void writeAt(int row, int col, char ch)
    {
        this->mapP[row][col].c = ch;
        // update it when erase and adding char
        if (ch != '_')
        {
            this->mapP[row][col].notValid = true;
        }
    }
    // read a single char on the page
    char readAt(int row, int col)
    {
        return this->mapP[row][col].c;
    }
    // erase a single char on the page
    void eraseAt(int row, int col)
    {
        this->mapP[row][col].c = '~';

        this->mapP[row][col].notValid = true;
    }
    // if the char is taken or earased
    bool is_notValid(int row, int col)
    {
        return this->mapP[row][col].notValid;
    }
    void updateMaxMin(int row, int col)
    {
        maxRow = max(maxRow, row);
        maxCol = max(maxCol, col);
        minCol = min(minCol, col);
        minRow = min(minRow, row);
    }

    Page()
    {
        maxRow = 0, maxCol = 0;
        minRow = INT_MAX, minCol = INT_MAX;
        Page::_numOfPages++;
    }
    ~Page()
    {
    }
};

/*
 * @brief  this class represents a notebook
 */

namespace ariel
{

    class Notebook
    {

        map<int, Page> notebook;

    public:
        void write(int page, int row, int col, Direction dir, string const &note);
        string read(int page, int row, int col, Direction dir, int len);
        void erase(int page, int row, int col, Direction dir, int len);
        void show(int page);
        bool invokeThrow(int page, int row, int col);

        bool checkValidation(int page, int row, int col, Direction dir, string const &note, int len);

        Notebook()
        {
        }
        ~Notebook()
        {
        }
    };
}