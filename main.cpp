#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

using namespace std;

int main()
{
    vector<string> lines;
    string line;
    int c_line;
    while (true)
    {
        cout << "  >> ";
        getline(cin, line);
        if (line == "o")
        {
            cout << "  >>>> ";
            getline(cin, line);
            if (filesystem::exists(line))
            {
                ifstream data(line);
                while (data.good())
                {
                    getline(data, line);
                    lines.push_back(line + "\n");
                    c_line++;
                }
            }
            else
            {
                cout << "Invalid File" << endl;
            }
            continue;
        }
        if (line == "n")
        {
            cout << "  >>>> ";
            getline(cin, line);
            lines.push_back(line + "\n");
            c_line++;
            continue;
        }
        if (line == "o")
        {
            cout << "  >>>> ";
            getline(cin, line);
            int num = stoi(line);
            if (line != "0")
            {
                if (num != 0)
                {
                    num = num - 1;
                    if (num >= 0 && num <= c_line)
                    {
                        cout << "  >>>>>> ";
                        getline(cin, line);
                        lines[num] = line;
                    }
                    else
                    {
                        cout << "Invalid Line" << endl;
                    }
                }
                else
                {
                    cout << "Invalid Line";
                }
            }
        }
        if (line == "p")
        {
            for (auto line : lines)
            {
                cout << line;
            }
            continue;
        }
        if (line == "q")
        {
            break;
        }
    }
    return 0;
}