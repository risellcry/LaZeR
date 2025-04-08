#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

using namespace std;

int main()
{
    cout << "  LaZeR 1.0.0" << endl;
    cout << "   GNU GPL 3 " << endl;
    cout << "  Type 'hlp' for Help" << endl;
    cout << endl;
    vector<string> lines;
    string line;
    string file;
    int c_line;
    while (true)
    {
        cout << "  >> ";
        getline(cin, line);
        if (line == "hlp")
        {
            cout << "  hlp : Help" << endl;
            cout << "  opf <file> : Open File" << endl;
            cout << "  nwl <text> : New Line" << endl;
            cout << "  ovw <line> <text> : Overwrite Line" << endl;
            cout << "  sve : Save" << endl;
            cout << "  sva <file> : Save As" << endl;
            cout << "  prv : Preview Contents" << endl;
            cout << "  tmp : Terminate Process" << endl;
            cout << "  dbg <os> : Debug Mode" << endl;
            continue;
        }
        if (line == "opf")
        {
            cout << "  >>>> ";
            getline(cin, line);
            ifstream data(line);
            if (data)
            {
                file = line;
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
            data.close();
            continue;
        }
        if (line == "nwl")
        {
            cout << "  >>>> ";
            getline(cin, line);
            lines.push_back(line + "\n");
            c_line++;
            continue;
        }
        if (line == "ovw")
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
                        lines[num] = line + "\n";
                    }
                    else
                    {
                        cout << "Invalid Line" << endl;
                    }
                }
                else
                {
                    cout << "Invalid Line" << endl;
                }
            }
            else
            {
                cout << "Invalid Line" << endl;
            }
            continue;
        }
        if (line == "sve")
        {
            ifstream data(file);
            string saved;
            if (data)
            {
                data.close();
                ofstream data(file, ios::trunc);
                for (auto line : lines)
                {
                    saved = saved + line;
                }
                data << saved;
                data.close();
            }
            else
            {
                cout << "Invalid File" << endl;
            }
            continue;
        }
        if (line == "sva")
        {
            cout << "  >>>> ";
            getline(cin, line);
            ofstream data(line, ios::trunc);
            string saved;
            for (auto line : lines)
            {
                saved = saved + line;
            }
            data << saved;
            data.close();
            continue;
        }
        if (line == "prv")
        {
            for (auto line : lines)
            {
                cout << "  " << line;
            }
            continue;
        }
        if (line == "tmp")
        {
            break;
        }
        if (line == "dbg")
        {
            cout << "  >>>> ?" << endl;
            cout << "  >> win" << endl;
            cout << "  >> lnx" << endl;
            cout << "  >>>> ";
            getline(cin, line);
            if (line == "win")
            {
                system("cmd");
                continue;
            }
            if (line == "lnx")
            {
                system("bash");
                continue;
            }
            else
            {
                cout << "Invalid Operating System" << endl;
                continue;
            }
        }
        if (line.empty())
        {
            continue;
        }
        else
        {
            cout << "Invalid Option" << endl;
            continue;
        }
    }
    return 0;
}
