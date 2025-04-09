#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool is_number(string line)
{
    istringstream iss(line);
    double digit;
    return iss >> noskipws >> digit && iss.eof();
}

int main()
{
    cout << "  LaZeR 1.0.0" << endl;
    cout << "   GNU GPL 3 " << endl;
    cout << "  Type 'hlp' for Help" << endl;
    cout << endl;
    vector<string> lines;
    vector<string> temp;
    bool auto_save;
    string line;
    string file;
    int c_line;
    ifstream data("LaZeR-AutoSave");
    if (data)
    {
        file = "LaZeR-AutoSave";
        if (data.good())
        {
            auto_save = true;
        }
        while (data.good())
        {
            getline(data, line);
            temp.push_back(line);
            c_line++;
        }
        int current;
        for (auto line : temp)
        {
            if (current < c_line - 1)
            {
                lines.push_back(line + "\n");
                current++;
            }
            else
            {
                lines.push_back(line);
                break;
            }
        }
        data.close();
    }
    while (true)
    {
        cout << "  >> ";
        getline(cin, line);
        if (line == "hlp")
        {
            cout << "  hlp : Help" << endl;
            cout << "  opf <file> : Open File" << endl;
            cout << "  nwl <text> : New Line" << endl;
            cout << "  inl <line> <text> : Insert Line" << endl;
            cout << "  ovw <line> <text> : Overwrite Line" << endl;
            cout << "  sve : Save" << endl;
            cout << "  sva <file> : Save As" << endl;
            cout << "  prv : Preview Contents" << endl;
            cout << "  dlt <line> : Delete Line" << endl;
            cout << "  clr : Clear All Lines" << endl;
            cout << "  tmp : Terminate Process" << endl;
            cout << "  dbg <os> : Debug Mode" << endl;
            cout << "  ats <enable> : Auto Save" << endl;
            continue;
        }
        if (line == "opf")
        {
            cout << "  >>>> ";
            getline(cin, line);
            ifstream data(line);
            file = "";
            lines.clear();
            if (data)
            {
                file = line;
                while (data.good())
                {
                    getline(data, line);
                    temp.push_back(line);
                    c_line++;
                }
                int current;
                for (auto line : temp)
                {
                    if (current < c_line)
                    {
                        lines.push_back(line + "\n");
                        current++;
                    }
                    else
                    {
                        lines.push_back(line);
                        break;
                    }
                }
            }
            else
            {
                cout << "  Invalid File" << endl;
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
            if (auto_save == true)
            {
                ofstream data("LaZeR-AutoSave", ios::trunc);
                string all;
                for (auto line : lines)
                {
                    all = all + line + "\n";
                }
                data << all;
                data.close();
            }
            continue;
        }
        if (line == "inl")
        {
            cout << "  >>>> ";
            getline(cin, line);
            if (!is_number(line))
            {
                cout << "  Invalid Line" << endl;
                continue;
            }
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
                        lines.insert(lines.begin() + num, line + "\n");
                        if (auto_save == true)
                        {
                            ofstream data("LaZeR-AutoSave", ios::trunc);
                            string all;
                            for (auto line : lines)
                            {
                                cout << line;
                                all = all + line + "\n";
                            }
                            data << all;
                            data.close();
                        }
                    }
                    else
                    {
                        cout << "  Invalid Line" << endl;
                    }
                }
                else
                {
                    cout << "  Invalid Line" << endl;
                }
            }
            else
            {
                cout << "  Invalid Line" << endl;
            }
            continue;
        }
        if (line == "ovw")
        {
            cout << "  >>>> ";
            getline(cin, line);
            if (!is_number(line))
            {
                cout << "  Invalid Line" << endl;
                continue;
            }
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
                        if (auto_save == true)
                        {
                            ofstream data("LaZeR-AutoSave", ios::trunc);
                            string all;
                            for (auto line : lines)
                            {
                                cout << line;
                                all = all + line + "\n";
                            }
                            data << all;
                            data.close();
                        }
                    }
                    else
                    {
                        cout << "  Invalid Line" << endl;
                    }
                }
                else
                {
                    cout << "  Invalid Line" << endl;
                }
            }
            else
            {
                cout << "  Invalid Line" << endl;
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
                cout << "  Invalid File" << endl;
            }
            continue;
        }
        if (line == "sva")
        {
            cout << "  >>>> ";
            getline(cin, line);
            ofstream data(line, ios::trunc);
            file = line;
            string saved;
            for (auto line : lines)
            {
                saved = saved + line;
            }
            data << saved;
            data.close();
            continue;
        }
        if (line == "dlt")
        {
            cout << "  >>>> ";
            getline(cin, line);
            if (!is_number(line))
            {
                cout << "  Invalid Line" << endl;
            }
            int num = stoi(line);
            if (line != "0")
            {
                if (num != 0)
                {
                    num = num - 1;
                    if (num >= 0 && num <= c_line)
                    {
                        lines.erase(lines.begin() + num);
                        c_line--;
                        if (auto_save == true)
                        {
                            ofstream data("LaZeR-AutoSave", ios::trunc);
                            string all;
                            for (auto line : lines)
                            {
                                all = all + line;
                            }
                            data << all;
                            data.close();
                        }
                    }
                    else
                    {
                        cout << "  Invalid Line" << endl;
                    }
                }
                else
                {
                    cout << "  Invalid Line" << endl;
                }
            }
            else
            {
                cout << "  Invalid Line" << endl;
            }
            continue;
        }
        if (line == "clr")
        {
            lines.clear();
            if (auto_save == true)
            {
                ofstream data("LaZeR-AutoSave", ios::trunc);
                data.close();
            }
            continue;
        }
        if (line == "prv")
        {
            if (c_line > 1)
            {
                for (auto line : lines)
                {
                    cout << "  " << line;
                }
            }
            if (c_line == 1)
            {
                for (auto line : lines)
                {
                    if (!line.empty())
                    {
                        cout << "  " << line;
                    }
                }
            }
            continue;
        }
        if (line == "tmp")
        {
            break;
        }
        if (line == "ats")
        {
            cout << "  >>>> ?" << endl;
            cout << "  >> y" << endl;
            cout << "  >> n" << endl;
            cout << "  >>>> ";
            getline(cin, line);
            if (line == "y")
            {
                auto_save = true;
                ifstream data("LaZeR-AutoSave");
                data.close();
                continue;
            }
            if (line == "n")
            {
                auto_save = false;
                remove("LaZeR-AutoSave");
                continue;
            }
            else
            {
                cout << "  Invalid Choice" << endl;
                continue;
            }
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
                cout << "  Invalid Choice" << endl;
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
