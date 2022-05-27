#include <iostream>
#include <fstream>

#include <cstdio>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>

using namespace std;

string exec(const char *cmd)
{
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }
    return result;
}

void runFile(vector<string> txHash)
{
    int totti = 0;
    ofstream outfile("runnable02.sh");
    while (totti < txHash.size()) {

        outfile << ".././cardano-cli-build/bin/cardano-cli transaction build --alonzo-era --testnet-magic 1097911063 --change-address $(cat ../my_keys/02.addr) ";
        int limit = txHash.size() < 401+totti ? txHash.size() : 401+totti;
        for (int i = totti; i < limit; i++)
        {
            outfile << " --tx-in \"" << txHash[i] << "\"";
        }
        outfile << " --tx-out \"$(cat ../my_keys/01.addr) 1800000 lovelace\" --out-file ../tx/tx.body" << endl;
        outfile << ".././cardano-cli-build/bin/cardano-cli transaction sign --tx-body-file ../tx/tx.body --signing-key-file ../my_keys/02.skey --testnet-magic 1097911063 --out-file ../tx/tx.signed" << endl;

        outfile << ".././cardano-cli-build/bin/cardano-cli transaction submit --testnet-magic 1097911063 --tx-file ../tx/tx.signed" << endl  << endl;
        totti += 401;
    }
    outfile.close();
    system("chmod +x runnable02.sh");
}

int main()
{
    ofstream outfile("test.sh");

    outfile << ".././cardano-cli-build/bin/cardano-cli query utxo --address $(cat ../my_keys/02.addr) --testnet-magic 1097911063" << endl;

    outfile.close();
    system("chmod +x test.sh");
    string str = exec("./test.sh");
    string txIn;
    vector<string> txHash;
    int lines = 0;
    for (int i = 0; i < str.length(); i++)
    {
        txIn = "";
        while (str[i] != '\n')
            i++;
        lines++;
        i++;
        if (lines < 2)
        {
            while (str[i] != '\n')
                i++;
            i++;
        }
        while (i < str.length() && str[i] != ' ' && str[i] != '\n')
        {
            txIn.push_back(str[i]);
            i++;
        }
        if (i < str.length())
            txIn.push_back('#');
        while (i < str.length() && str[i] == ' ')
            i++;
        while (i < str.length() && str[i] != ' ' && str[i] != '\n')
        {
            txIn.push_back(str[i]);
            i++;
        }
        if (i < str.length())
            txHash.push_back(txIn);
    }
    cout << txHash.size() << endl;
    runFile(txHash);
    return 0;
}