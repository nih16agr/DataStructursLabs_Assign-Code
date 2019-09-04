#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStringList>
//#include <QStringListIterator>
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

struct Trie {
    bool isEndOfWord;
    unordered_map<char, Trie*> map;
    string meaning;
}*root;


Trie* getNewTrieNode()

{
    Trie* node = new Trie;
    node->isEndOfWord = false;
    return node;
}


void insert(Trie*& root, const string& str,
            const string& meaning)
{

    // If root is null
    if (root == NULL)
        root = getNewTrieNode();

    Trie* temp = root;
    for (int i = 0; i < str.length(); i++) {
        char x = str[i];

        // Make a new node if there is no path
        if (temp->map.find(x) == temp->map.end())
            temp->map[x] = getNewTrieNode();

        temp = temp->map[x];
    }

    // Mark end of word and store the meaning
    temp->isEndOfWord = true;
    temp->meaning = meaning;
}


string getMeaning(Trie* root, const string& word)
{

    // If root is null i.e. the dictionary is empty
    if (root == NULL)
        return "";

    Trie* temp = root;

    // Search a word in the Trie
    for (int i = 0; i < word.length(); i++) {
        temp = temp->map[word[i]];
        if (temp == NULL)
            return "";
    }

    // If it is the end of a valid word stored
    // before then return its meaning
    if (temp->isEndOfWord)
        return temp->meaning;
    return "";
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTextFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTextFile()
{

    QStringList wordList;
    QFile inputFile(":/L4_P1_input.csv");
    if(inputFile.open(QIODevice::ReadOnly))
    {
        QString data;
       data = inputFile.readAll();
       wordList = data.split(',');
    }
    for(QStringList::const_iterator S = wordList.constBegin();S != wordList.constEnd() ; S++)
    {
        string ws = (*S).toUtf8().constData();
        //cout<<ws<<endl;
        S++;
        string ms = (*S).toUtf8().constData();
        //cout<<ms<<endl;
        insert(root,ws,ms);
        //cout<<"yay"<<endl;
    }
    inputFile.close();

}

void MainWindow::on_pushButton_search_clicked()
{
    string word = ui->textEdit_input->toPlainText().toUtf8().constData();
    if(getMeaning(root,word) == ""){
        QMessageBox ohno;
        ohno.setText("No word found");
        ohno.exec();
        ui->textEdit_input->clear();
    }
    ui->textBrowser_show->setPlainText(getMeaning(root,word).c_str());
}

void MainWindow::on_pushButton_2_exit_clicked()
{
    close();
}
