/**
 * main.cpp
 *
 * C++ versions 4.4.5
 *
 *      fcgi_client : https://github.com/Yujiro3/fcgicli
 *      Copyright (c) 2011-2013 sheeps.me All Rights Reserved.
 *
 * @package         fcgi_client
 * @copyright       Copyright (c) 2011-2013 sheeps.me
 * @author          Yujiro Takahashi <yujiro3@gmail.com>
 * @filesource
 */

#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

#include "fcgi_client.h"

using namespace std;
using namespace fcgi;

/**
 * メイン関数
 *
 * @access public
 * @param int  argc
 * @param char **argv
 * @return int
 */
int main(int argc, char **argv) {
    client fcgcli(argv[1]);

    string response, contents("values");
    stringstream conlength;

    char dir[255];
    getcwd(dir, sizeof(dir));

    fcgcli.params["GATEWAY_INTERFACE"] = "FastCGI/1.0";
    fcgcli.params["REQUEST_METHOD"]    = "GET";
    fcgcli.params["SCRIPT_FILENAME"]   = argv[2];
    fcgcli.params["CONTENT_TYPE"]      = "";
    fcgcli.params["CONTENT_LENGTH"]    = "0";
    fcgcli.params["QUERY_STRING"]      = "seed=";
    fcgcli.params["QUERY_STRING"].append(argv[3]);

    try {
        response = fcgcli.request(&contents);
    } catch (const char* errmsg) {
        cerr << errmsg << endl;
    }
    
    cout << response << endl;

    return 0;
}
