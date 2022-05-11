#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <time.h>
#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace std;

typedef struct tx {
    string time_str;
    time_t time;
    string id;
    string number;
    string bytes;
} tx;

typedef struct performance {
    double tps; //transactions per second
    double ard; //average response delay
    double bpm; //blocks per minute
    double dps; //data per second
} performance;

performance parse_data(string input){

    ifstream infile(input);
    string line;

    while (!regex_match(line, regex(".*\"numTxs\",Number 1.0.*")) && !infile.eof())
        getline(infile, line);

    vector<tx> add_txs, block_info;

    regex tx_added_reg(".*\"kind\",String \"TraceMempoolAddedTx\".*");
    regex tx_removed_reg(".*\"kind\",String \"TraceMempoolRemoveTxs\".*");
    regex the_time("\\d{2}:\\d{2}:\\d{2}");

    regex id_string("\"txid\",String \".{8}\"");
    regex id_num("[a-z0-9]{8}");

    regex mem_size_reg("\"mempoolSize\",Object \\(fromList \\[\\(\"bytes\",Number \\d*\\.\\d*");
    regex num_reg("\"numTxs\",Number \\d*\\.\\d*");
    regex num_str("\\d*\\.\\d*");

    smatch m;
    string temp;
    int buffer;
    int current_max = 0;
    bool just_read_block;
    
    while (true)
    {
        if (infile.eof())
            break;

        tx new_tx;

        // Get Tx timestamp
        regex_search(line, m, the_time);
        new_tx.time_str = m[0];
        struct tm tm;
        strptime(new_tx.time_str.c_str(), "%H:%M:%S", &tm);
        new_tx.time = mktime(&tm);

        // Get tx ID
        regex_search(line, m, id_string);
        temp = m[0];
        regex_search(temp, m, id_num);
        new_tx.id = m[0];

        // Get Tx Number
        regex_search(line, m, num_reg);
        temp = m[0];
        regex_search(temp, m, num_str);
        new_tx.number = m[0];
        
        // Get Byte Size
        regex_search(line, m, mem_size_reg);
        temp = m[0];
        regex_search(temp, m, num_str);
        new_tx.bytes = m[0];

        if (regex_match(line, tx_added_reg)) //storing transaction info
        {
            if(just_read_block) {
                current_max = 0;
                if (block_info.size() > 0) 
                    block_info.back().bytes = to_string(stoi(block_info.back().bytes) - stoi(new_tx.bytes));
            }
            just_read_block = false;
            add_txs.push_back(new_tx);
            current_max = stoi(new_tx.number) > current_max ? stoi(new_tx.number) : current_max;
        }
        else if (regex_match(line, tx_removed_reg)) // storing block info
        {
            if (!just_read_block) {
                new_tx.number = to_string((current_max - stoi(new_tx.number)));
                buffer = stoi(new_tx.number);
                just_read_block = true;
            } else {  // if no transactions were parsed between block info
                new_tx.number = to_string((current_max - (stoi(new_tx.number)+buffer)));
                buffer += stoi(new_tx.number);
            }
            new_tx.bytes = add_txs.back().bytes;
            block_info.push_back(new_tx);
        }
        getline(infile, line);
    }

    int k = 0;
    double response_delay = 0;
    
    for (int i = 0; i < block_info.size(); i++)
    {
        for (int j = 0; j < stoi(block_info[i].number); j++)
        {
            if (i > 0 && i < block_info.size() - 1) 
                response_delay += difftime(block_info[i].time, add_txs[k].time);
            k++;
        }
    }
    cout << fixed;
    cout.precision(4);
    double seconds_elapsed = difftime(block_info[block_info.size() - 2].time, block_info[0].time);
    double selected_txs = (double)(add_txs.size() - (stoi(block_info[0].number) + stoi(block_info.back().number)));
    double tps = selected_txs / seconds_elapsed;
    double bpm = (block_info.size() - 2) / (seconds_elapsed / 60);
    double ard = response_delay / selected_txs;
    double dps;
    for (int i = 1; i < block_info.size()-1 ; i++) 
        dps += stod(block_info[i].bytes);
    
    dps = dps/seconds_elapsed;

    return {tps, ard, bpm, dps};
}

int main () {
    vector<performance> big_results, small_results;
    big_results.push_back(parse_data("../logs/test01.txt"));
    big_results.push_back(parse_data("../logs/test02.txt"));
    big_results.push_back(parse_data("../logs/test03.txt"));
    big_results.push_back(parse_data("../logs/test04.txt"));
    big_results.push_back(parse_data("../logs/test05.txt"));
    big_results.push_back(parse_data("../logs/test06.txt"));
    big_results.push_back(parse_data("../logs/test07.txt"));
    big_results.push_back(parse_data("../logs/test08.txt"));
    big_results.push_back(parse_data("../logs/test09.txt"));
    big_results.push_back(parse_data("../logs/test10.txt"));
    big_results.push_back(parse_data("../logs/test11.txt"));

    small_results.push_back(parse_data("../logs/small01.txt"));
    small_results.push_back(parse_data("../logs/small02.txt"));
    small_results.push_back(parse_data("../logs/small03.txt"));
    small_results.push_back(parse_data("../logs/small04.txt"));
    small_results.push_back(parse_data("../logs/small05.txt"));
    small_results.push_back(parse_data("../logs/small06.txt"));
    small_results.push_back(parse_data("../logs/small07.txt"));
    small_results.push_back(parse_data("../logs/small08.txt"));
    small_results.push_back(parse_data("../logs/small09.txt"));
    small_results.push_back(parse_data("../logs/small10.txt"));
    small_results.push_back(parse_data("../logs/small11.txt"));

    vector<double> tps, ard, bpm, dps;

    for (int i = 0; i < big_results.size(); i++)
    {
        tps.push_back(big_results[i].tps);
        ard.push_back(big_results[i].ard);
        bpm.push_back(big_results[i].bpm);
        dps.push_back(big_results[i].dps);
        cout << "LARGE TEST [" << i+1 << "] tps: " << big_results[i].tps << " ard: " << big_results[i].ard 
            << " bpm: " << big_results[i].bpm << " dps: " << big_results[i].dps << endl;
    }
    for (int i = 0; i < small_results.size(); i++)
    {
        tps.push_back(small_results[i].tps);
        ard.push_back(small_results[i].ard);
        bpm.push_back(small_results[i].bpm);
        dps.push_back(small_results[i].dps);
        cout << "SMALL TEST [" << i + 1 << "] tps: " << small_results[i].tps << " ard: " << small_results[i].ard 
            << " bpm: " << small_results[i].bpm << " dps: " << small_results[i].dps << endl;
    }

    sort(tps.begin(), tps.begin() + tps.size() / 2);
    sort(tps.begin() + tps.size()/2, tps.end());
    sort(ard.begin(), ard.begin() + ard.size() / 2);
    sort(ard.begin() + ard.size() / 2, ard.end());
    sort(bpm.begin(), bpm.begin() + bpm.size() / 2);
    sort(bpm.begin() + bpm.size() / 2, bpm.end());
    sort(dps.begin(), dps.begin() + dps.size() / 2);
    sort(dps.begin() + dps.size() / 2, dps.end());
    cout << "===================================================================" << endl;
    cout << "[BIG TEST MEDIANS]   tps: " << tps[tps.size() / 4] << " ard: " << ard[ard.size() / 4] << " bpm: " << bpm[bpm.size() / 4] << " dps: " << dps[dps.size() / 4] << endl;
    cout << "[SMALL TEST MEDIANS] tps: " << tps[tps.size()*3 / 4] << " ard: " << ard[ard.size()*3 / 4] << " bpm: " << bpm[bpm.size()*3 / 4] << " dps: " << dps[dps.size()*3 / 4] << endl;
    return 0;
}