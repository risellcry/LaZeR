/*
TODO LIST
copy paste command one to out
and fix some minor bugs in new out command
add feature to read file
*/

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
    vector<string> tokens;
    if (line.empty())
    {
        return tokens;
    }
    tokens = split(line, " ");
    vector<string> lexed;
    string type;
    string variable;
    string value;
    for (auto token : tokens)
    {
        if (type.empty())
        {
            if (token == "in" or token == "out" or token == "one")
            {
                type = token;
                lexed.push_back(type);
                continue;
            }
            if (token == "get" or token == "set" or token == "clean")
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
        if (variable.empty())
        {
            if (type != "clean")
            {
                variable = token;
                lexed.push_back(variable);
                continue;
            }
            else
            {
                cout << "Overloaded Arguments For " << type << endl;
                break;
            }
        }
        if (value.empty())
        {
            if (type != "out" or type != "one" or type != "get")
            {
                value = token;
                lexed.push_back(value);
            }
            else
            {
                cout << "Overloaded Arguments For " << type << endl;
            }
            break;
        }
    }
    return lexed;
}

bool starts_with(string line, string wanted)
{
    return line.compare(0, wanted.length(), wanted) == 0;
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        string line;
        vector<string> ints_names;
        vector<int> ints_contents;
        vector<string> strs_names;
        vector<string> strs_contents;
        vector<string> flts_names;
        vector<float> flts_contents;
        cout << "LaZecript IIRT" << endl;
        cout << "  GNU GPL 3" << endl;
        while (true)
        {
            cout << " >> ";
            getline(cin, line);
            if (line == "about")
            {
                cout << " LaZecript IIRT" << endl;
                cout << "  GNU GPL 3" << endl;
                continue;
            }
            if (line == "exit")
            {
                break;
            }
            if (line == "help")
            {
                cout << " (Exclusive To IIRT <Interpret In Real Time>)" << endl;
                cout << " help : Help" << endl;
                cout << " about : About" << endl;
                cout << " exit : Exit" << endl;
                cout << " (Normal)" << endl;
                cout << " in <variable> <value> : Create Variable" << endl;
                cout << " out <variable/string> : Prints Variable or String" << endl;
                cout << " one <variable/string> : Prints Variable or String without New Line" << endl;
                cout << " get <variable (string)> : Get the Input and Stores Inside Variable" << endl;
                cout << " set <variable> <value> : Change Variable Value" << endl;
                cout << " clean : Clear Console" << endl;
                continue;
            }
            vector<string> lexed = lexer(line);
            int i;
            string type;
            string variable;
            string value;
            for (auto keyword : lexed)
            {
                if (type.empty())
                {
                    if (keyword == "in" or keyword == "out" or keyword == "one")
                    {
                        type = keyword;
                        continue;
                    }
                    if (keyword == "get" or keyword == "set")
                    {
                        type = keyword;
                        continue;
                    }
                }
                if (variable.empty())
                {
                    if (type == "in" or type == "set")
                    {
                        variable = keyword;
                        continue;
                    }
                    if (type == "clean")
                    {
                        try
                        {
                            system("cls");
                        }
                        catch (exception error)
                        {
                            system("clear");
                        }
                    }
                    if (type == "get")
                    {
                        variable = keyword;
                        bool founded;
                        int i;
                        for (auto str_name : strs_names)
                        {
                            if (variable == str_name)
                            {
                                founded = true;
                                break;
                            }
                            i++;
                        }
                        if (founded == true)
                        {
                            getline(cin, strs_contents[i]);
                        }
                        else
                        {
                            cout << "Invalid String Variable : " << variable << endl;
                        }
                        continue;
                    }
                    if (type == "out")
                    {
                        vector<string> lines = split(keyword, "^");
                        int i;
                        for (auto line : lines)
                        {
                            if (!lines[i + 1].empty())
                            {
                                int ii;
                                vector<string> words = split(line, "`");
                                for (auto word : words)
                                {
                                    if (!words[ii + 1].empty())
                                    {
                                        if (starts_with(word, "@"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto int_name : ints_names)
                                            {
                                                if (int_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << ints_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            cout << " ";
                                            continue;
                                        }
                                        if (starts_with(word, "~"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto str_name : strs_names)
                                            {
                                                if (str_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << strs_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            cout << " ";
                                            continue;
                                        }
                                        if (starts_with(word, "!"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto flt_name : flts_names)
                                            {
                                                if (flt_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << flts_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            cout << " ";
                                            continue;
                                        }
                                        if (!starts_with(word, "@") and !starts_with(word, "~") or !starts_with(word, "~!"))
                                        {
                                            cout << word << " ";
                                        }
                                    }
                                    else
                                    {
                                        if (starts_with(word, "@"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto int_name : ints_names)
                                            {
                                                if (int_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << ints_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "~"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto str_name : strs_names)
                                            {
                                                if (str_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << strs_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "!"))
                                        
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto flt_name : flts_names)
                                            {
                                                if (flt_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << flts_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (!starts_with(word, "@") and !starts_with(word, "~") or !starts_with(word, "~!"))
                                        {
                                            cout << word;
                                        }
                                    }
                                }
                                cout << endl;
                                continue;
                            }
                            else
                            {
                                int ii;
                                vector<string> words = split(line, "`");
                                for (auto word : words)
                                {
                                    if (!words[ii + 1].empty())
                                    {
                                        if (starts_with(word, "@"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto int_name : ints_names)
                                            {
                                                if (int_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << ints_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            cout << " ";
                                            continue;
                                        }
                                        if (starts_with(word, "~"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto str_name : strs_names)
                                            {
                                                if (str_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << strs_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            cout << " ";
                                            continue;
                                        }
                                        
                                        if (starts_with(word, "!"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto flt_name : flts_names)
                                            {
                                                if (flt_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << flts_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word<< endl;
                                                break;
                                            }
                                            cout << " ";
                                            continue;
                                        }
                                        if (!starts_with(word, "@") and !starts_with(word, "~") or !starts_with(word, "~!"))
                                        {
                                            cout << word << " " << endl;
                                        }
                                    }
                                    else
                                    {
                                        if (starts_with(word, "@"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto int_name : ints_names)
                                            {
                                                if (int_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << ints_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "~"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto str_name : strs_names)
                                            {
                                                if (str_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << strs_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "!"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto flt_name : flts_names)
                                            
                                            {
                                                if (flt_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                founded = true;
                                                cout << flts_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (!starts_with(word, "@") and !starts_with(word, "~") or !starts_with(word, "~!"))
                                        {
                                            cout << word;
                                        }
                                    }
                                }
                                cout << endl;
                                break;
                            }
                        }
                        break;
                    }
                    if (type == "one")
                    {
                        vector<string> lines = split(keyword, "^");
                        int i;
                        for (auto line : lines)
                        {
                            if (!lines[i + 1].empty())
                            {
                                int ii;
                                vector<string> words = split(line, "`");
                                for (auto word : words)
                                {
                                    if (!words[ii + 1].empty())
                                    {
                                        if (starts_with(word, "@"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto int_name : ints_names)
                                            {
                                                if (int_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << ints_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "~"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto str_name : strs_names)
                                            {
                                                if (str_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << strs_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "!"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto flt_name : flts_names)
                                            {
                                                if (flt_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << flts_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (!starts_with(word, "@") and !starts_with(word, "~") or !starts_with(word, "~!"))
                                        {
                                            cout << word;
                                        }
                                    }
                                    else
                                    {
                                        if (starts_with(word, "@"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto int_name : ints_names)
                                            {
                                                if (int_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << ints_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "~"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto str_name : strs_names)
                                            {
                                                if (str_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << strs_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "!"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto flt_name : flts_names)
                                            {
                                                if (flt_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << flts_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (!starts_with(word, "@") and !starts_with(word, "~") or !starts_with(word, "~!"))
                                        {
                                            cout << word;
                                        }
                                    }
                                }
                                continue;
                            }
                            else
                            {
                                int ii;
                                vector<string> words = split(line, "`");
                                for (auto word : words)
                                {
                                    if (!words[ii + 1].empty())
                                    {
                                        if (starts_with(word, "@"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto int_name : ints_names)
                                            {
                                                if (int_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << ints_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "~"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto str_name : strs_names)
                                            {
                                                if (str_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << strs_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "!"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto flt_name : flts_names)
                                            {
                                                if (flt_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << flts_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word<< endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (!starts_with(word, "@") and !starts_with(word, "~") or !starts_with(word, "~!"))
                                        {
                                            cout << word;
                                        }
                                    }
                                    else
                                    {
                                        if (starts_with(word, "@"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto int_name : ints_names)
                                            {
                                                if (int_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << ints_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "~"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto str_name : strs_names)
                                            {
                                                if (str_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                cout << strs_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (starts_with(word, "!"))
                                        {
                                            word.replace(0, 1, "");
                                            int iii;
                                            bool founded;
                                            for (auto flt_name : flts_names)
                                            {
                                                if (flt_name == word)
                                                {
                                                    founded = true;
                                                    break;
                                                }
                                                iii++;
                                            }
                                            if (founded == true)
                                            {
                                                founded = true;
                                                cout << flts_contents[iii];
                                            }
                                            else
                                            {
                                                cout << "Invalid Variable : " << word << endl;
                                                break;
                                            }
                                            continue;
                                        }
                                        if (!starts_with(word, "@") and !starts_with(word, "~") or !starts_with(word, "~!"))
                                        {
                                            cout << word;
                                        }
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                if (value.empty())
                {
                    value = keyword;
                    if (type == "in")
                    {
                        try
                        {
                            if (!(value.find(".") != string::npos))
                            {
                                for (auto int_name : ints_names)
                                {
                                    if (variable == int_name)
                                    {
                                        cout << "Already Declared : " << variable << endl;
                                        break;
                                    }
                                }
                                ints_contents.push_back(stoi(value));
                                ints_names.push_back(variable);
                            }
                            else
                            {
                                for (auto flt_name : flts_names)
                                {
                                    if (variable == flt_name)
                                    {
                                        cout << "Already Declared : " << variable << endl;
                                        break;
                                    }
                                }
                                flts_contents.push_back(stof(value));
                                flts_names.push_back(variable);
                            }
                        }
                        catch (exception error)
                        {
                            for (auto str_name : strs_names)
                            {
                                if (variable == str_name)
                                {
                                    cout << "Already Declared : " << variable << endl;
                                    break;
                                }
                            }
                            while (value.find("^") != string::npos)
                            {
                                value.replace(value.find("^"), 1, "\n");
                            }
                            while (value.find("`") != string::npos)
                            {
                                value.replace(value.find("`"), 1, " ");
                            }
                            strs_contents.push_back(value);
                            strs_names.push_back(variable);
                        }
                        continue;
                    }
                    if (type == "set")
                    {
                        bool founded;
                        int i;
                        if (starts_with(variable, "@"))
                        {
                            variable.replace(0, 1, "");
                            for (auto int_name : ints_names)
                            {
                                if (variable == int_name)
                                {
                                    founded = true;
                                    break;
                                }
                                else
                                {
                                    founded = false;
                                    i++;
                                }
                            }
                            if (founded)
                            {
                                try
                                {
                                    ints_contents[i] = stoi(value);
                                }
                                catch (exception error)
                                {
                                    cout << "Invalid Value";
                                }
                            }
                            else
                            {
                                cout << "Invalid Variable" << endl;
                            }
                        }
                        if (starts_with(variable, "!"))
                        {
                            variable.replace(0, 1, "");
                            for (auto flt_name : flts_names)
                            {
                                if (variable == flt_name)
                                {
                                    founded = true;
                                    break;
                                }
                                else
                                {
                                    founded = false;
                                    i++;
                                }
                            }
                            if (founded)
                            {
                                try
                                {
                                    flts_contents[i] = stof(value);
                                }
                                catch (exception error)
                                {
                                    cout << "Invalid Value";
                                }
                            }
                            else
                            {
                                cout << "Invalid Variable" << endl;
                            }
                        }
                        if (starts_with(variable, "~"))
                        {
                            variable.replace(0, 1, "");
                            for (auto str_name : strs_names)
                            {
                                if (variable == str_name)
                                {
                                    founded = true;
                                    break;
                                }
                                else
                                {
                                    founded = false;
                                    i++;
                                }
                            }
                            if (founded)
                            {
                                try
                                {
                                    strs_contents[i] = value;
                                }
                                catch (exception error)
                                {
                                    cout << "Invalid Value";
                                }
                            }
                            else
                            {
                                cout << "Invalid Variable" << endl;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}