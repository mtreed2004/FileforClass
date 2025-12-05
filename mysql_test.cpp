//
// An example from the web
// To make it work on voyager it must be compiled as such:
//
// g++ -Wall -o mysql_test -I/usr/include/mysql-cppconn-8/mysql -I/usr/include/mysql-cppconn-8/jdbc mysql_test.cpp -L/usr/lib64 -lmysqlcppconn 
//

// To use c++ libraries
#include <iostream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

// To use lambda anonymous functions in c++ programming 
#include <boost/lambda/lambda.hpp> 

// To create MySQL connections
#include "mysql_connection.h"

// To use SQL statements in c++
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define HOST "localhost"
#define USER "Put your MySQL username here"
#define PASS "Put your MySQL password here"
#define DB   "Put the name of your database here"

using namespace std;

int main(void)
{

    try {
        sql::Driver* driver;
        sql::Connection* con;
        sql::ResultSet* res;
        sql::PreparedStatement* pstmt;

        // Create a connection
        driver = get_driver_instance();
        con = driver->connect(HOST, USER, PASS);

        // Connect to the MySQL database
        con->setSchema(DB);

        // Execute your SQL query
        pstmt = con->prepareStatement("SELECT Fname, Lname FROM EMPLOYEE ORDER BY Fname ASC");
        res = pstmt->executeQuery();

        // Fetch the results
        while (res->next())
            cout << res->getString("Fname") << "\t" << res->getString("Lname") << endl;

        delete res;
        delete pstmt;
        delete con;

    }
    catch (sql::SQLException& e) {
        cout << "# ERR: " << e.what() << endl;
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << "Done." << endl;

    return EXIT_SUCCESS;
}