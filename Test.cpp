/*
 * AUTHORS: Wissam kabha
 * gitHub: https://github.com/Wissam111
 * Date: 03/2022
 */

#include "Notebook.hpp"
#include "doctest.h"
#include <string>
#include <iostream>
using namespace std;
using namespace ariel;
#include <algorithm>
#include "Direction.hpp"
using ariel::Direction;

TEST_CASE("not valid  input test case")
{
    ariel::Notebook notebook;
    CHECK_THROWS(notebook.write(10000, -50, 90, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(2, 101, 99, Direction::Horizontal, "ahod"));
    CHECK_THROWS(notebook.write(-30, 1, 30, Direction::Horizontal, "assd"));
    CHECK_THROWS(notebook.write(2, 2000, -10, Direction::Horizontal, "aaabcd"));
    CHECK_THROWS(notebook.write(3, 100, 200, Direction::Horizontal, "asdsd"));
    CHECK_THROWS(notebook.write(3, 100, 200, Direction::Horizontal, "asd~sd"));
    CHECK_THROWS(notebook.read(0, 0, 0, Direction::Horizontal, 1000));
    CHECK_THROWS(notebook.read(-1, 0, 0, Direction::Horizontal, 4));
    CHECK_THROWS(notebook.read(0, -2, 0, Direction::Horizontal, 5));
    CHECK_THROWS(notebook.read(-3, 0, 0, Direction::Horizontal, 1));
    CHECK_THROWS(notebook.erase(0, -2, 0, Direction::Horizontal, 1));
    CHECK_THROWS(notebook.erase(0, 0, -3, Direction::Horizontal, 1));
    CHECK_THROWS(notebook.erase(-1, 0, -3, Direction::Horizontal, 2));
    CHECK_THROWS(notebook.erase(0, 0, 0, Direction::Horizontal, 1000));
}

TEST_CASE("valid  input test case")
{
    Notebook notebook;
    CHECK_NOTHROW(notebook.write(1, 50, 90, Direction::Horizontal, "abcd"));
    CHECK_NOTHROW(notebook.write(2, 0, 0, Direction::Horizontal, "ahod"));
    CHECK_NOTHROW(notebook.write(1, 1500, 30, Direction::Horizontal, "assd"));
    CHECK_NOTHROW(notebook.write(2, 2000, 20, Direction::Horizontal, "aaabcd"));
    CHECK_NOTHROW(notebook.write(3, 100, 66, Direction::Horizontal, "asdsd"));
}
TEST_CASE("Overwrite test case")
{
    Notebook notebook;
    CHECK(notebook.read(1, 200, 90, Direction::Horizontal, 4) == string("____"));
    notebook.write(1, 200, 90, Direction::Horizontal, "abcd");
    CHECK(notebook.read(1, 200, 90, Direction::Horizontal, 4) == string("abcd"));
    CHECK_THROWS(notebook.write(1, 200, 91, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(1, 199, 92, Direction::Vertical, "abcd"));
    CHECK_THROWS(notebook.write(1, 199, 93, Direction::Vertical, "abcd"));
    notebook.write(1, 255, 90, Direction::Vertical, "abcd");
    CHECK_THROWS(notebook.write(1, 255, 88, Direction::Horizontal, "ttt"));

    CHECK_THROWS(notebook.write(3, 100, 100, Direction::Horizontal, "asdsd"));
}

TEST_CASE("Sides Test")
{

    Notebook notebook;
    notebook.write(1, 89, 89, Direction::Horizontal, "M");
    notebook.write(1, 88, 88, Direction::Horizontal, "A");
    notebook.write(1, 87, 87, Direction::Horizontal, "S");
    notebook.write(1, 86, 86, Direction::Horizontal, "S");
    notebook.write(1, 85, 85, Direction::Horizontal, "I");
    notebook.write(1, 84, 84, Direction::Horizontal, "W");

    CHECK(notebook.read(1, 84, 84, Direction::Vertical, 7) == string("W______"));
    CHECK(notebook.read(1, 84, 85, Direction::Vertical, 7) == string("_I_____"));
    CHECK(notebook.read(1, 84, 86, Direction::Vertical, 7) == string("__S____"));
    CHECK(notebook.read(1, 84, 87, Direction::Vertical, 7) == string("___S___"));
    CHECK(notebook.read(1, 84, 88, Direction::Vertical, 7) == string("____A__"));
    CHECK(notebook.read(1, 84, 89, Direction::Vertical, 7) == string("_____M_"));

    notebook.write(2, 6, 6, Direction::Horizontal, "X");
    notebook.write(2, 5, 5, Direction::Horizontal, "O");
    notebook.write(2, 4, 4, Direction::Horizontal, "F");
    notebook.write(2, 3, 3, Direction::Horizontal, "X");
    notebook.write(2, 2, 2, Direction::Horizontal, "O");
    notebook.write(2, 1, 1, Direction::Horizontal, "H");

    CHECK(notebook.read(2, 0, 1, Direction::Vertical, 7) == string("_H_____"));
    CHECK(notebook.read(2, 0, 2, Direction::Vertical, 7) == string("__O____"));
    CHECK(notebook.read(2, 0, 3, Direction::Vertical, 7) == string("___X___"));
    CHECK(notebook.read(2, 0, 4, Direction::Vertical, 7) == string("____F__"));
    CHECK(notebook.read(2, 0, 5, Direction::Vertical, 7) == string("_____O_"));
    CHECK(notebook.read(2, 0, 6, Direction::Vertical, 7) == string("______X"));
