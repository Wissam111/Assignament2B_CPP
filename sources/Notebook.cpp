/*
* AUTHORS: Wissam kabha
* gitHub: https://github.com/Wissam111
// Date: 03/2022
*/
#include <iostream>
#include <string>
using namespace std;
#include "NoteBook.hpp"
using namespace ariel;

const int MaxRowLen = 100;
const int minAscii = 32;
const int maxAscii = 126;

bool Notebook ::invokeThrow(int page, int row, int col)
{

    return this->notebook[page].is_notValid(row, col);
}

/*
 * @brief  check if the writing specific note is valid
 */
bool Notebook::checkValidation(int page, int row, int col, Direction dir, string const &note, int len)
{
    char ch = '~';
    if ((page < 0 || row < 0 || col < 0 || col > MaxRowLen || note.find(ch) != string::npos || len < 0))
    {
        return false;
    }

    int strlen = note.length();
    if (col >= MaxRowLen || (dir == Direction::Horizontal && ((col + strlen > MaxRowLen) || len > MaxRowLen || (col + len > MaxRowLen))))
    {
        return false;
    }

    for (char c : note)
    {

        if (invokeThrow(page, row, col) || !(int(c) >= minAscii && int(c) <= maxAscii))
        {
            return false;
        }
        (dir == Direction::Horizontal) ? col++ : row++;
    }

    return true;
}

/*
 * @brief  write a note on a specific postion
 *
 * @param page specfic page of the notebook
 * @param row col dir are the coordinates to write the note on page
 */
void Notebook::write(int page, int row, int col, Direction dir, string const &note)
{

    if (!this->checkValidation(page, row, col, dir, note, 0))
    {

        // throw "This note writing is not Valid!!";
        throw invalid_argument("This note writing is not Valid!!");
    }

    this->notebook[page].updateMaxMin(row, col);

    for (char ch : note)
    {

        this->notebook[page].writeAt(row, col, ch);
        (dir == Direction::Horizontal) ? col++ : row++;
    }
    this->notebook[page].updateMaxMin(row, col);
}

/*
 * @brief  read a note with specfic length and coordinates
 */
string Notebook::read(int page, int row, int col, Direction dir, int len)
{
    if (!this->checkValidation(page, row, col, dir, "", len))
    {
        // throw "This note writing is not Valid!!";
        throw invalid_argument("This note writing is not Valid!!");
    }
    string ans;

    for (int i = 0; i < len; i++)
    {
        char c = this->notebook[page].readAt(row, col);
        ans += c;
        (dir == Direction::Horizontal) ? col++ : row++;
    }

    return ans;
}
/*
 * @brief  erase a note with specfic length and coordinates
 */
void Notebook::erase(int page, int row, int col, Direction dir, int len)
{

    if (!this->checkValidation(page, row, col, dir, "", len))
    {
        // throw "This note writing is not Valid!!";
        throw invalid_argument("This note writing is not Valid!!");
    }

    this->notebook[page].updateMaxMin(row, col);

    for (int i = 0; i < len; i++)
    {
        this->notebook[page].eraseAt(row, col);

        (dir == Direction::Horizontal) ? col++ : row++;
    }
    this->notebook[page].updateMaxMin(row, col);
}

/*
 * @brief  show a page
 */
void Notebook::show(int page)
{

    if (page < 0)
    {
        throw invalid_argument("Page Number Should be Postive!!");
    }
    for (int i = notebook[page].minRow; i <= notebook[page].maxRow; i++)
    {
        // cout << i << ":";
        for (int j = notebook[page].minCol; j <= notebook[page].maxCol; j++)
        {
            cout << this->notebook[page].readAt(i, j) << " ";
        }
        cout << endl;
    }
}