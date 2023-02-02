/*Jared Zaugg
  CPSC 122
  Gonzaga University
  1-25-23
*/

ifstream inFile;
ofstream outFile;
string morseStrings[91];
int charsConv = 0;

char engKey[36] = {'a','b','c','d','e','f','g','h', ///index corresponds
                     'i','j','k','l','m','n','o','p',//morseKey
                     'q','r','s','t','u','v','w','x',
                     'y','z','1','2','3','4','5','6',
                     '7','8','9','0'};

///index corresponds to engKey
string morseKey[36] = {".-","-...","-.-.","-..",".","..-.","--.",
                       "....","..",".---","-.-",".-..","--","-.",
                       "---",".--.","--.-",".-.","...","-","..-",
                       "...-",".--","-..-","-.--","--..",".----",
                       "..---","...--","....-",".....","-....",
                       "--...","---..","----.","-----"};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Author: Jared Zaugg
School: Gonzaga University
Date Updated: 2/1/23
Description: A function to determine whether the user
wants to convert from english text to morse text
or morse text to english text.
*/
void convertDecision(){
    string decision, decision2, decision3;
    int dumb = 0;

    cout << "If you want to transcribe to english type: '-m'.\nIf you want to transcribe to morse type: '-t'." << endl;
    cin >> decision;

    if (decision == "-m"){///if they type m
        dumb++;
        cout << "Which do you want to be your source file? 'english.txt' or 'morse.txt'?" << endl;
        cin >> decision2;
        if (decision2 == "english.txt"){///then if they type english.txt
            cout << "Which file do you want to write to? 'english.txt or morse.txt'?" << endl;
            cin >> decision3;
            if (decision3 == "morse.txt"){///then if they type morse.txt
                convertETM(); ///converts english text to morse text
            }
        }
    }
    if (decision == "-t"){///if they typed t
        dumb++;
        cout << "Which do you want to be your source file? 'english.txt' or 'morse.txt'?" << endl;
        cin >> decision2;
        if (decision2 == "morse.txt"){///if they typed morse.txt
            cout << "Which file do you want to write to? 'english.txt or morse.txt'?" << endl;
            cin >> decision3;
            if (decision3 == "english.txt"){///if they typed english.txt
                convertMTE(); ///converts morse text to english text
            }
            else{
                cout << "There was a typo. Try '-m, english.txt, morse.txt' (english to morse) or '-t, morse.txt, english.txt' (morse to english)." << endl;///if they typed something wrong, this comes up.
            }
        }
        else{
            cout << "There was a typo. Try '-m, english.txt, morse.txt' (english to morse) or '-t, morse.txt, english.txt' (morse to english)." << endl;///if they typed something wrong, this comes up.
        }
    }
    else if(dumb < 1){
        cout << "There was a typo. Try '-m, english.txt, morse.txt' (english to morse) or '-t, morse.txt, english.txt' (morse to english)." << endl; ///if they typed something wrong, this comes up.
    }
}

/*Author: Jared Zaugg
School: Gonzaga University
Date Updated: 2/1/23
Description: This function's job is to take lines from englist.txt, convert that
text to individual chars, convert those chars to morse code, then write that
code to morse.txt and keep track of character count.
*/
void convertETM(){
    inFile.open("english.txt");
    outFile.open("morse.txt");
    int dumb;
    string line,word;
    istringstream iss;

    while (!inFile.eof()){ ///not end of file
        getline(inFile,line); ///get a line from english.txt
        if(!inFile.bad()){  ///if there's no errors
            if (line.length() > 0){///if there's chars on the line
                iss.clear();
                iss.str(line);
                while(iss >> word){///extract a word from the line
                    for (char c:word){///turn that word into chars
                    }
                    for (int i = 0; i < word.length(); i++){ ///for the word length, convert all the chars into morse
                        for (int j = 0; j < 36; j++){
                            if (word[i] == engKey[j]){
                                outFile << morseKey[j] << ' ';
                                charsConv++; ///keeps track of chars converted
                            }
                        }
                    }
                    outFile << ' ';
                }
            }
        }
        outFile << endl;
    }
    cout << "Characters Converted: " << charsConv << endl;

    inFile.close();
    outFile.close();
}

/*Author: Jared Zaugg
School: Gonzaga University
Date Updated: 2/1/23
Description: This function's job is to take lines from morse.txt, convert
the morse code into strings, then convert those strings into chars, then
outFile those chars with correct whitespace and keep track of character count.
*/
void convertMTE(){
    inFile.open("morse.txt");
    outFile.open("english.txt");
    string line, morse;
    int seenspace = 0;

    while(!inFile.eof()){ ///not end of file
        if(!inFile.bad()){ ///if there's no errors
            getline(inFile,line); ///get a line from morse.txt
            for (int i = 0; i < line.size(); i++){///for the size of the line
                char c = line[i];///convert line into chars
                if (!(c == ' ')){///if it's not whitespace
                    morse += c;///apend char to morse string
                    seenspace = 0;///tracks whitespace(seenspace? false)
                }
                else{ ///if it's whitespace
                    for (int i = 0; i < 36; i++){
                        if (morse == morseKey[i]){///if the morse string match with an index of morseKey
                            outFile << engKey[i];///write the corresponding english letter
                            charsConv++;///keeps track of chars conv.
                            morse = "";///resets morse string
                        }
                    }
                    if (seenspace == 1){///if the previous char was whitespace
                        outFile << ' ';///outFile whitespace to english.txt
                    }
                    seenspace = 1;///says that the current char is whitespace even if the one before wasn't
                }
            }
            outFile << endl;///keeps the lines together
        }
    }
    cout << "Characters Converted: " << charsConv << endl;

    inFile.close();
    outFile.close();
}