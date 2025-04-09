# LaZeR
LaZeR is a rich-feature code editor, look at this syntax.
```
  >> nwl
  >>>> This is a line.
```
What are you seeing here is a LaZer's syntax, there's 9 of them.
* hlp : Help
* opf (file) : Open File
* nwl (text) : New Line
* ovw (line) (text) : Overwrite Line
* sve : Save
* sva (file) : Save As
* prv : Preview Contents
* dlt (line) : Delete Line
* clr : Clear All Lines
* tmp : Terminate Process
* dbg (os) : Debug Mode
* ats (enable) : Auto Save

You may ask : "If I wrote my software in this code editor, can I make its price (NOT open-source) fair?"
The answer is yes, you can calculate the price of the software by (length of codes x 0.025).
# LaZecript
LaZecript is a high-level programming language for beginners, here's some example.
```
  main.lz
    in a 0
    in b 1
    in c ?
    get c
    out `@a`@b^
```
### Output
```
... 0 1

```
##### Notes
... stands for user input.
### Explain
In this code, we created 3 variables called a, b and c.
The value of a is 0, the value of b is 1 and the value of c is undefined.
Out means print something to the console, but here's the catch. The Interpreter only limited to 3 tokens in each line so it won't read further than 3 tokens and here's a list of all special characters.
```
  ` : Space
  ^ : New Line
  ~ : New Tab
```
