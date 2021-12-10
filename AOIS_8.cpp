#include <iostream>
#include <vector>
#include <map>

using namespace std;

const int amount_of_words_and_symbols = 16;
const int recursion_border_index = -1;

vector<bool> multiplication(vector<bool> term_one, vector<bool> term_two)
{
    if (term_one.size() < term_two.size()) {
        while (term_one.size() != term_two.size())
        {
            term_one.insert(term_one.begin(), 0);
        }
    }
    else if (term_one.size() > term_two.size()) {
        while (term_one.size() != term_two.size())
        {
            term_two.insert(term_one.begin(), 0);
        }
    }
    vector<bool> result;
    for (int i = 0; i < term_one.size(); i++)
    {
        result.push_back(term_one[i] * term_two[i]);
    }
    return result;
}
bool summary(bool first, bool second)
{
    if (first && second) return true;
    else return (first + second);
}
pair<bool, bool> recursion_compare(vector<bool>& term_one, const vector<bool>& term_two, int position)
{
    pair<bool, bool> result;
    if (position == recursion_border_index) {
        result.first = false;
        result.second = false;
        return result;
    }
    else {
        pair<bool, bool> previous_result = recursion_compare(term_one, term_two, position - 1);
        result.first = summary(previous_result.first, !term_one[position] * term_two[position] * !previous_result.second);
        result.second = summary(previous_result.second, term_one[position] * !term_two[position] * !previous_result.first);
        return result;
    }
}


class Word
{
    int word_size;
    vector<bool> data;
public:
    Word();
    Word(int size);
    Word(vector<bool>& data);
    void shiftUp();
    void shiftDown();
    string print();
    Word operator*(Word& term);
    Word operator=(Word& term);
    bool operator==(Word& term);
    Word operator!();
};
Word::Word() {}
Word::Word(int size) : word_size(size)
{
    srand(time(NULL));
    for (int i = 0; i < word_size; i++)
    {
        int positive_sign = rand() % 2;
        if (positive_sign == 1) {
            data.push_back(true);
        }
        else {
            data.push_back(false);
        }
    }
}
Word::Word(vector<bool>& data) : word_size(data.size())
{
    this->data = data;
}
void Word::shiftUp()
{
    if (word_size == 0) return;
    bool temp = data[data.size() - 1];
    data.erase(data.begin() + (data.size() - 1));
    data.insert(data.begin(), temp);
}
void Word::shiftDown()
{
    if (word_size == 0) return;
    bool temp = data[0];
    data.erase(data.begin());
    data.insert(data.begin() + data.size(), temp);
}
string Word::print()
{
    string result; 
    for (int i = 0; i < word_size; i++)
    {
        result += data[i];
    }
    return result;
}
Word Word::operator*(Word& term)
{
    vector<bool> output = multiplication(data, term.data);
    Word result(output);
    return result;
}
Word Word::operator!()
{
    vector<bool> output;
    for (int i = 0; i < word_size; i++)
    {
        output.push_back(!data[i]);
    }
    Word result(output);
    return result;
}
Word Word::operator=(Word& term)
{
    data = term.data;
    word_size = term.word_size;
    return *this;
}
bool Word::operator==(Word& term)
{
    if (data == term.data && word_size == term.word_size) return true;
    return false;
}

class AsociatedMemory
{
    vector<Word>table;
    AsociatedMemory() {};
    AsociatedMemory(AsociatedMemory& example) {};
    void push(int position, vector<bool> term);
    void print();
    void print_diagonalized();
    void F1(int position_one, int position_two);
    void F14(int position_one, int position_two);
    void F3(int position_one, int position_two);
    void F12(int position_one, int position_two);


};
AsociatedMemory::AsociatedMemory()
{
    table.resize(amount_of_words_and_symbols);
    for (int i = 0; i < amount_of_words_and_symbols; i++)
    {
        Word example(amount_of_words_and_symbols);
        table[i] = example;
    }
}
void AsociatedMemory::push(int position, vector<bool> term)
{
    if (position > amount_of_words_and_symbols - 1 || position < 0) return;
    if (term.size() != amount_of_words_and_symbols) return;
    table.insert(table.begin() + position, term);
    table.erase(table.begin() + table.size() - 1);
}
void AsociatedMemory::print()
{
    cout << "Table : " << endl << "-------------------------------------" << endl;
    for (int i = 0; i < table.size(); i++)
    {
        cout << "word[" << i << "] = " << table[i].print() << endl;
    }
    cout << "-------------------------------------" << endl;
}
void AsociatedMemory::print_diagonalized()
{
    vector<Word> example = table;
    cout << "Diagonalized table : " << endl << "-------------------------------------" << endl;
    for (int i = 0; i < example.size(); i++)
    {
        for  (int j = 0; j < i;  j++)
        {
            example[i].shiftUp();
        }
        cout << "word[" << i << "] = " << example[i].print() << endl;
    }
    cout << "-------------------------------------" << endl;
}
void AsociatedMemory::F1(int position_one, int position_two)
{
    if (position_one < 0 || position_one > amount_of_words_and_symbols - 1) return;
    if (position_two < 0 || position_two > amount_of_words_and_symbols - 1) return;
    Word example = table[position_one] * table[position_two];
    cout << "F1(word[" << position_one << "], word[" << position_two << "]) = " << example.print() << endl;
}
void AsociatedMemory::F3(int position_one, int position_two)
{
    if (position_one < 0 || position_one > amount_of_words_and_symbols - 1) return;
    if (position_two < 0 || position_two > amount_of_words_and_symbols - 1) return;
    cout << "F3(word[" << position_one << "], word[" << position_two << "]) = " << table[position_one].print() << endl;
}
void AsociatedMemory::F12(int position_one, int position_two)
{
    if (position_one < 0 || position_one > amount_of_words_and_symbols - 1) return;
    if (position_two < 0 || position_two > amount_of_words_and_symbols - 1) return;
    Word example = !table[position_one];
    cout << "F12(word[" << position_one << "], word[" << position_two << "]) = " << example.print() << endl;
}
void AsociatedMemory::F14(int position_one, int position_two)
{
    if (position_one < 0 || position_one > amount_of_words_and_symbols - 1) return;
    if (position_two < 0 || position_two > amount_of_words_and_symbols - 1) return;
    Word example = !(table[position_one] * table[position_two]);
    cout << "F14(word[" << position_one << "], word[" << position_two << "]) = " << example.print() << endl;
}

int main()
{
    return 0;
}
