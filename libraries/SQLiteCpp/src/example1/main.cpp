/**
 * @file  main.cpp
 * @brief Two short examples in a row.
 *
 *  Demonstrate how-to use the SQLite++ wrapper
 *
 * Copyright (c) 2012 Sebastien Rombauts (sebastien dot rombauts at gmail dot com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <iostream>
#include "stdio.h"

#include "../SQLiteC++/Database.h"
#include "../SQLiteC++/Statement.h"


/// Object Oriented Basic example
class Example
{
public:
    Example(void) :
        mDb("example.db3"),                                 // Open a database file
        mQuery(mDb, "SELECT * FROM test WHERE size > ?")    // Compile a SQL query, containing one parameter (index 1)
    {
    }
    virtual ~Example(void)
    {
    }

    // List the rows where the "size" column is greater than the provided aParamValue
    void ListGreaterThan (const int aParamValue)
    {
        std::cout << "ListGreaterThan (" << aParamValue << ")\n";

        // Bind the integer value provided to the first parameter of the SQL query
        mQuery.bind(1, aParamValue);

        // Loop to execute the query step by step, to get one a row of results at a time
        while (mQuery.executeStep())
        {
            std::cout << "row : (" << mQuery.getColumn(0) << ", " << mQuery.getColumn(1) << ", " << mQuery.getColumn(2) << ")\n";
        }

        // Reset the query to be able to use it again later
        mQuery.reset();
    }

private:
    SQLite::Database    mDb;
    SQLite::Statement   mQuery;
};


int main (void)
{
    // Basic example (1/3) :
    try
    {
        // Open a database file
        SQLite::Database    db("example.db3");
        std::cout << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully\n";

        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement   query(db, "SELECT * FROM test WHERE size > ?;SELECT id FROM test");
        std::cout << "SQLite statement '" << query.getQuery().c_str() << "' compiled (" << query.getColumnCount () << " columns in the result)\n";
        // Bind the integer value 6 to the first parameter of the SQL query
        query.bind(1, 6);

        // Loop to execute the query step by step, to get one a row of results at a time
        while (query.executeStep())
        {
            // Demonstrate how to get some typed column value
            int         id      = query.getColumn(0); // = query.getColumn(0).getInt()
          //const char* pvalue  = query.getColumn(1); // = query.getColumn(1).getText()
            std::string value   = query.getColumn(1); // = query.getColumn(1).getText()
            int         size    = query.getColumn(2); // = query.getColumn(2).getInt()

            std::cout << "row : (" << id << ", " << value.c_str() << ", " << size << ")\n";
        }

        // Reset the query to use it again
        query.reset();
        std::cout << "SQLite statement '" << query.getQuery().c_str() << "' reseted (" << query.getColumnCount () << " columns in the result)\n";
        // Bind the string value "6" to the first parameter of the SQL query
        query.bind(1, "6");

        while (query.executeStep())
        {
            // Demonstrate that inserting column value in a std:ostream is natural
            std::cout << "row : (" << query.getColumn(0) << ", " << query.getColumn(1) << ", " << query.getColumn(2) << ")\n";
        }
    }
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Object Oriented Basic example (2/3) :
    try
    {
        // Open the database and compile the query
        Example example;

        // Demonstrate the way to use the same query with different parameter values
        example.ListGreaterThan(8);
        example.ListGreaterThan(6);
        example.ListGreaterThan(2);
    }
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Simple batch queries example (3/3) :
    try
    {
        // Open a database file
        SQLite::Database    db("test.db3", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE);
        std::cout << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully\n";

        db.exec("DROP TABLE IF EXISTS test");

        db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

        int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
        std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

        db.exec("DROP TABLE test");
    }
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
    }
    remove("test.db3");

    return 0;
}
