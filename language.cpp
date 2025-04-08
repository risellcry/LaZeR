#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string tokens, const string delimiter)
{
    string line;
    vector<string> lines;
    size_t start = 0;
    size_t end;
    size_t len = delimiter.length();
    while ((end = tokens.find(delimiter, start)) != string::npos)
    {
        line = tokens.substr(start, end - start);
        start = end + len;
        lines.push_back(line);
    }
    lines.push_back(tokens.substr(start));
    return lines;
}

vector<string> lexer(string line)
{
    vector<string> tokens = split(line, " ");
    vector<string> lexed;
    string type;
    string variable;
    string value;
    for (auto token : tokens)
    {
        if (type.empty())
        {
            if (token == "in" or token == "out")
            {
                type = token;
                lexed.push_back(type);
                continue;
            }
            if (token == "get")
            {
                type = token;
                lexed.push_back(type);
                continue;
            }
            else
            {
                cout << "Invalid Command : " << token << endl;
                break;
            }
        }
    }
    return lexed;
}

bool replace(string line, string old_data, string new_data)
{
    size_t start = line.find(old_data);
    if (start != string::npos)
    {
        line.replace(start, old_data.length(), new_data);
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        cout << "Invalid File" << endl;
    }
    else
    {
        ifstream data(argv[1]);
        vector<string> lines;
        string line;
        if (data)
        {
            while (data.good())
            {
                getline(data, line);
                lines.push_back(line);
            }
            for (auto line : lines)
            {
                vector<string> lexed = lexer(line);
                int i;
                string type;
                string variable;
                string value;
                vector<string> ints_names;
                vector<int> ints_contents;
                for (auto keyword : lexed)
                {
                    if (type.empty())
                    {
                        if (lexed[i] == "in" or lexed[i] == "out")
                        {
                            type = lexed[i];
                            i++;
                        }
                        continue;
                    }
                    if (!type.empty() and variable.empty())
                    {
                        variable = lexed[i];
                        if (type == "out")
                        {
                            vector<string> lines = split(lexed[i], "^");
                            for (auto line : lines)
                            {
                                vector<string> words = split(line, "`");
                                int c_int;
                                string c_str;
                                float c_flt;
                                for (auto word : words)
                                {
                                    if (word.rfind("@", 0) == 0)
                                    {
                                        word = replace(word, "@", "");
                                        for (auto int_name : ints_names)
                                        {
                                            if (word == int_name)
                                            {
                                                cout << ints_contents[c_int] << " ";
                                                break;
                                            }
                                            c_int++;
                                        }
                                        continue;
                                    }
                                    else
                                    {
                                        cout << word << " ";
                                        continue;
                                    }
                                }
                            }
                            cout << endl;
                            continue;
                        }
                        i++;
                        continue;
                    }
                }
            }
        }
        else
        {
            cout << "Invalid File" << endl;
        }
    }
    return 0;
}