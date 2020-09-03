#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdint.h>
//#include <filesystem>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;
using namespace boost;
namespace fs = boost::filesystem;

bool isRegex(const string& txData) {
    // Ef strengurinn byrjar á "ACCEPT offer "(í hex) 
    // og ef strengurinn er 90 á lengd
    // þá skoðum við txid sem kemur þar á eftir
    if (txData.rfind("414343455054206f6666657220", 0) == 0 && txData.length() == 90) {
        // náum í txid-ið eða þá 64 stafi sem eru á eftir "ACCEPT offer "
        std::string txid = txData.substr(26, 64);
        // Köllum á gettransaction með því txid - ef það er ekki til þá skilum við false
        uint256 hash = ParseHashV(txid, "parameter 1");
        CTransaction tx;
        uint256 hashBlock = 0;
        if (!GetTransaction(hash, tx, hashBlock, true))
        {
            return false;
        }
    }

    std::vector<std::string> lines;
    string filename = "./smileyCoin/src/regex.txt"; //virkar ef smileyCoin er i working directory?
    ifstream infile(filename.c_str());
    if (!infile.is_open())
    {
        return false;
    }

    string line;
    while (getline(infile, line))
    {
        istringstream iss(line);
        ostringstream oss;
        lines.push_back(line);
    }

    for (int i = 0; i < lines.size(); i++) {
        std::string strengur = lines[i];
        std::regex expr(strengur);

        if (std::regex_match(txData, expr)) {
            LogPrintStr(" 8 i regex: " + txData);

            return true;
        }
    }
    // send the data encrypted
    return false;

    infile.close();

}