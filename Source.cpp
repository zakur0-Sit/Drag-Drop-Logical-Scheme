#define _CRT_SECURE_NO_DEPRECATE
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "Menu.h"

using namespace std;
using namespace sf;

//definesc niste dimensiuni generale ca sa le pot schimba global la nevoie

#define windowLength 1800
#define windowHeight 900
#define menuButtonLength 140
#define menuButtonHeight 60
#define insertButtonLength 100
#define insertButtonHeight 50
#define inBetweenSpace 14
#define distanceFromWindowEdge 10
#define menuButtonCharacterSize 35
#define insertButtonCharacterSize 20
#define elementCharacterSize 12
#define buttonColor 0x00d1efac
#define buttonColorHover 0x00d1efff
#define numberOfMenuButtons 6
#define numberOfInsertButtons 6
#define elementSize 75
#define elementColor 0x15d629ff
#define elementInitialPosition_x 1625
#define elementInitialPosition_y 225
#define startingBoxPosition_x 1550
#define startingBoxPosition_y 150
#define startingBoxSize 200
#define runButtonPosition 1493
#define consoleLogTextPosition_x 1450
#define consoleLogTextPosition_y 400
#define consoleLogLinesShown 22
#define consoleLogTextSize 16
#define consoleLogBoxPosition_x 1425
#define consoleLogBoxPosition_y 375
#define consoleLogBoxSize_width 350
#define consoleLogBoxSize_height 500

Font font;

struct Button
{
public:
    Button(float L, float H, float x, float y, string s, float textCharacterSize) : isMove(0)
    {
        box.setSize(sf::Vector2f(L, H));
        box.setPosition(x, y);
        box.setFillColor(sf::Color(buttonColor));
        text.setFont(font);
        text.setString(s);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(textCharacterSize);
        FloatRect textSize = text.getGlobalBounds();
        text.setPosition((L - textSize.width) / 2.2 + x, (H - textSize.height) / 2.7 + y);
        boundingBox = box.getGlobalBounds();
    }
    void replaceText(const char s[])
    {
        text.setString(s);
    }
    void changeColor(int color)
    {
        box.setFillColor(sf::Color(color));
    }
    void changeSize(float l, float h)
    {
        box.setSize(sf::Vector2f(l, h));
        boundingBox = box.getGlobalBounds();
    }
    void changePosition(float x, float y)
    {
        box.setPosition(x, y);
        text.setPosition(x, y);
        boundingBox = box.getGlobalBounds();
    }
    sf::Vector2f getPosition()
    {
        return box.getPosition();
    }
    sf::RectangleShape getBox()
    {
        return box;
    }
    sf::Text getText()
    {
        return text;
    }
    bool isMove;
    int type;
    sf::RectangleShape box;
    sf::Text text;
    sf::FloatRect boundingBox;
};

struct Form
{
public:
    Form(float L, float H, float X, float Y, int TYPE) : isMove(0), type(TYPE), x(X), y(Y), length(L), height(H)
    {
        text.setFont(font);
        text.setFillColor(Color::Black);
        text.setCharacterSize(24);
        switch (type)
        {
        case 0: case 1: case 5:
            shape.rectangle.setPosition(x, y);
            shape.rectangle.setSize(Vector2f(length, height));
            boundingBox = shape.rectangle.getGlobalBounds();
            inputLocation.x = x + length / 2;
            inputLocation.y = y;
            outputLocation.x = x + length / 2;
            outputLocation.y = y + height;
            switch (type)
            {
            case 0:
                shape.rectangle.setFillColor(Color(86, 211, 125));
                break;
            case 1:
                shape.rectangle.setFillColor(Color(235, 76, 66));
                break;
            case 5:
                shape.rectangle.setFillColor(Color(148, 87, 235));
            }
            break;
        case 2:
            shape.trapez.setPointCount(4);
            shape.trapez.setPoint(0, Vector2f(x - 25, y - 25));
            shape.trapez.setPoint(1, Vector2f(x + length * 2 - 25, y - 25));
            shape.trapez.setPoint(2, Vector2f(x + length * 1.5 - 25, y + height - 25));
            shape.trapez.setPoint(3, Vector2f(x + length / 2 - 25, y + height - 25));
            shape.trapez.setFillColor(Color(49, 140, 231));
            boundingBox = shape.trapez.getGlobalBounds();
            inputLocation.x = x + length - 25;
            inputLocation.y = y - 25;
            outputLocation.x = x + length - 25;
            outputLocation.y = y + height - 25;
            text.setFillColor(sf::Color::White);
            break;
        case 3:
            shape.retrapez.setPointCount(4);
            shape.retrapez.setPoint(0, Vector2f(x - 25, y - 25));
            shape.retrapez.setPoint(1, Vector2f(x + L - 25, y - 25));
            shape.retrapez.setPoint(2, Vector2f(x + L * 1.5 - 25, y + H - 25));
            shape.retrapez.setPoint(3, Vector2f(x - L / 2 - 25, y + H - 25));
            shape.retrapez.setFillColor(Color(244, 202, 22));
            boundingBox = shape.retrapez.getGlobalBounds();
            inputLocation.x = x + length / 2 - 25;
            inputLocation.y = y - 25;
            outputLocation.x = x + length / 2 - 25;
            outputLocation.y = y + height - 25;
            break;
        case 4:
            shape.triangle.setPosition(x, y);
            shape.triangle.setRadius(length);
            shape.triangle.setPointCount(3);
            shape.triangle.setFillColor(Color(204, 57, 123));
            boundingBox = shape.triangle.getGlobalBounds();
            inputLocation.x = x + shape.triangle.getPoint(0).x;
            inputLocation.y = y + shape.triangle.getPoint(0).y;
            outputLocationElse.x = x + shape.triangle.getPoint(1).x;
            outputLocationElse.y = y + shape.triangle.getPoint(1).y;
            outputLocation.x = x + shape.triangle.getPoint(2).x;
            outputLocation.y = y + shape.triangle.getPoint(2).y;
        }
    }
    void changePosition(float X, float Y)
    {
        x = X;
        y = Y;
        switch (type)
        {
        case 0: case 1: case 5:
            shape.rectangle.setPosition(x, y);
            boundingBox = shape.rectangle.getGlobalBounds();
            text.setPosition(x + 10, y + 10);
            inputLocation.x = x + length / 2;
            inputLocation.y = y;
            outputLocation.x = x + length / 2;
            outputLocation.y = y + height;
            break;
        case 2:
            shape.trapez.setPoint(0, Vector2f(x - 25, y - 25));
            shape.trapez.setPoint(1, Vector2f(x + length * 2 - 25, y - 25));
            shape.trapez.setPoint(2, Vector2f(x + length * 1.5 - 25, y + height - 25));
            shape.trapez.setPoint(3, Vector2f(x + length / 2 - 25, y + height - 25));
            boundingBox = shape.trapez.getGlobalBounds();
            text.setPosition(x + length / 2 - 15, y - 15);
            inputLocation.x = x + length - 25;
            inputLocation.y = y - 25;
            outputLocation.x = x + length - 25;
            outputLocation.y = y + height - 25;
            break;
            break;
        case 3:
            shape.retrapez.setPoint(0, Vector2f(x - 25, y - 25));
            shape.retrapez.setPoint(1, Vector2f(x + length - 25, y - 25));
            shape.retrapez.setPoint(2, Vector2f(x + length * 1.5 - 25, y + height - 25));
            shape.retrapez.setPoint(3, Vector2f(x - length / 2 - 25, y + height - 25));
            boundingBox = shape.retrapez.getGlobalBounds();
            text.setPosition(x - 15, y - 15);
            inputLocation.x = x + length / 2 - 25;
            inputLocation.y = y - 25;
            outputLocation.x = x + length / 2 - 25;
            outputLocation.y = y + height - 25;
            break;
        case 4:
            shape.triangle.setPosition(x, y);
            boundingBox = shape.triangle.getGlobalBounds();
            text.setPosition(x + length / 2 + 5, y + length * 0.85);
            inputLocation.x = x + shape.triangle.getPoint(0).x;
            inputLocation.y = y + shape.triangle.getPoint(0).y;
            outputLocationElse.x = x + shape.triangle.getPoint(1).x;
            outputLocationElse.y = y + shape.triangle.getPoint(1).y;
            outputLocation.x = x + shape.triangle.getPoint(2).x;
            outputLocation.y = y + shape.triangle.getPoint(2).y;
        }
    }
    void resize(int LENGTH)
    {
        length = LENGTH;
        switch (type)
        {
        case 0: case 1: case 5:
            shape.rectangle.setSize(Vector2f(length, height));
            boundingBox = shape.rectangle.getGlobalBounds();
            text.setPosition(x + 10, y + 10);
            inputLocation.x = x + length / 2;
            inputLocation.y = y;
            outputLocation.x = x + length / 2;
            outputLocation.y = y + height;
            break;
        case 2:
            shape.trapez.setPoint(0, Vector2f(x - 25, y - 25));
            shape.trapez.setPoint(1, Vector2f(x + length * 2 - 25, y - 25));
            shape.trapez.setPoint(2, Vector2f(x + length * 1.5 - 25, y + height - 25));
            shape.trapez.setPoint(3, Vector2f(x + length / 2 - 25, y + height - 25));
            boundingBox = shape.trapez.getGlobalBounds();
            text.setPosition(x + length / 2 - 15, y - 15);
            inputLocation.x = x + length - 25;
            inputLocation.y = y - 25;
            outputLocation.x = x + length - 25;
            outputLocation.y = y + height - 25;
            break;
            break;
        case 3:
            shape.retrapez.setPoint(0, Vector2f(x - 25, y - 25));
            shape.retrapez.setPoint(1, Vector2f(x + length - 25, y - 25));
            shape.retrapez.setPoint(2, Vector2f(x + length * 1.5 - 25, y + height - 25));
            shape.retrapez.setPoint(3, Vector2f(x - length / 2 - 25, y + height - 25));
            boundingBox = shape.retrapez.getGlobalBounds();
            text.setPosition(x - 15, y - 15);
            inputLocation.x = x + length / 2 - 25;
            inputLocation.y = y - 25;
            outputLocation.x = x + length / 2 - 25;
            outputLocation.y = y + height - 25;
            break;
        case 4:
            shape.triangle.setRadius(length + 5);
            boundingBox = shape.triangle.getGlobalBounds();
            text.setPosition(x + length / 2 + 5 + 10, y + length * 0.85 - 5);
            inputLocation.x = x + shape.triangle.getPoint(0).x;
            inputLocation.y = y + shape.triangle.getPoint(0).y;
            outputLocationElse.x = x + shape.triangle.getPoint(1).x;
            outputLocationElse.y = y + shape.triangle.getPoint(1).y;
            outputLocation.x = x + shape.triangle.getPoint(2).x;
            outputLocation.y = y + shape.triangle.getPoint(2).y;
        }
    }
    void changeColor(int color)
    {
        switch (type)
        {
        case 0: case 1: case 5:
            shape.rectangle.setFillColor(sf::Color(color));
            break;
        case 2:
            shape.trapez.setFillColor(sf::Color(color));
            break;
        case 3:
            shape.retrapez.setFillColor(sf::Color(color));
            break;
        case 4:
            shape.triangle.setFillColor(sf::Color(color));
        }
    }
    void changeToBaseColor()
    {
        switch (type)
        {
        case 0:
            shape.rectangle.setFillColor(Color(86, 211, 125));
            break;
        case 1:
            shape.rectangle.setFillColor(Color(235, 76, 66));
            break;
        case 5:
            shape.rectangle.setFillColor(Color(148, 87, 235));
            break;
        case 2:
            shape.trapez.setFillColor(Color(49, 140, 231));
            break;
        case 3:
            shape.retrapez.setFillColor(Color(244, 202, 22));
            break;
        case 4:
            shape.triangle.setFillColor(Color(204, 57, 123));
        }
    }
    void changeToEvaluationColor()
    {
        switch (type)
        {
        case 0:
            shape.rectangle.setFillColor(Color(50, 150, 80));
            break;
        case 1:
            shape.rectangle.setFillColor(Color(165, 55, 40));
            break;
        case 5:
            shape.rectangle.setFillColor(Color(100, 60, 160));
            break;
        case 2:
            shape.trapez.setFillColor(Color(80, 50, 120));
            break;
        case 3:
            shape.retrapez.setFillColor(Color(80, 40, 50));
            break;
        case 4:
            shape.triangle.setFillColor(Color(40, 50, 80));
        }
    }
    int getType()
    {
        return type;
    }
    Vector2f getPosition()
    {
        Vector2f aux;
        aux.x = x;
        aux.y = y;
        return aux;
    }
    bool isMove;
    bool hasText = 0;
    int isPressed;
    int type;
    float x, y;
    float length, height;
    Vector2f inputLocation;
    Vector2f outputLocation;
    Vector2f outputLocationElse;
    struct formTypes
    {
        RectangleShape rectangle;
        ConvexShape trapez;
        ConvexShape retrapez;
        CircleShape triangle;
    }shape;
    sf::FloatRect boundingBox;
    sf::Text text;
    int nextElement;
    int nextElementElse;
};

struct lines
{
    Vertex point[4][3];
    int elementStart = 0;
    int elementEnd = 0;
    bool lineStartsFromElse = 0;
};

void placeLine(lines& auxLine, Vector2f startPosition, Vector2f endPosition)
{
    auxLine.point[0][0].position = startPosition;
    auxLine.point[0][1].position = Vector2f(startPosition.x, (startPosition.y + endPosition.y) / 2);
    auxLine.point[1][0].position = Vector2f(startPosition.x, (startPosition.y + endPosition.y) / 2);
    auxLine.point[1][1].position = Vector2f(endPosition.x, (startPosition.y + endPosition.y) / 2);
    auxLine.point[2][0].position = Vector2f(endPosition.x, (startPosition.y + endPosition.y) / 2);
    auxLine.point[2][1].position = endPosition;
}

void moveConnectedLines(vector<Form> elementsVector, vector<lines>& linesVector, int numberOfElements, int numberOfLines, int position)
{
    for (int i = 0; i < numberOfLines; i++)
    {
        bool lineMoved = 0;
        Vector2f auxElementEnd, auxElementStart;
        if (linesVector[i].elementEnd == position)
        {
            if (elementsVector[position].getType() == 4 && linesVector[i].lineStartsFromElse)
                auxElementEnd = elementsVector[position].outputLocationElse;
            else
                auxElementEnd = elementsVector[position].outputLocation;
            auxElementStart = linesVector[i].point[0][0].position;
            lineMoved = 1;
        }
        if (linesVector[i].elementStart == position)
        {
            auxElementStart = elementsVector[position].inputLocation;
            auxElementEnd = linesVector[i].point[2][1].position;
            lineMoved = 1;
        }
        if (lineMoved)
            placeLine(linesVector[i], auxElementStart, auxElementEnd);
    }
}

void outputInFile(const char* fileName, vector<Form> elementsVector, vector<lines> linesVector, int numberOfElements, int numberOfLines)
{
    FILE* fptr;
    fptr = fopen(fileName, "w");
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    fprintf(fptr, "%d", numberOfElements);
    for (int i = 0; i < numberOfElements; i++)
    {
        int auxType = elementsVector[i].type;
        Vector2i auxPosition;
        auxPosition.x = elementsVector[i].getPosition().x;
        auxPosition.y = elementsVector[i].getPosition().y;
        int auxHasText = elementsVector[i].hasText;
        string auxString = elementsVector[i].text.getString();
        const char* auxConstChar = auxString.c_str();
        fprintf(fptr, "\n%d", auxType);
        fprintf(fptr, "\n%d", auxPosition.x);
        fprintf(fptr, " %d", auxPosition.y);
        fprintf(fptr, "\n%d", auxHasText);
        if (auxHasText)
            fprintf(fptr, "\n%s", auxConstChar);
    }
    fprintf(fptr, "\n%d", numberOfLines);
    for (int i = 0; i < numberOfLines; i++)
    {
        fprintf(fptr, "\n%d", linesVector[i].elementEnd);
        fprintf(fptr, " %d", linesVector[i].elementStart);
        fprintf(fptr, " %d", linesVector[i].lineStartsFromElse);
    }
    fclose(fptr);
}

void inputFromFile(const char* fileName, vector<Form>& elementsVector, vector<lines>& linesVector, int& numberOfElements, int& numberOfLines)
{
    FILE* fptr;
    if ((fptr = fopen(fileName, "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    while (numberOfElements)
    {
        vector<Form>::iterator q = elementsVector.begin();
        vector<Form>::iterator p = elementsVector.erase(q);
        numberOfElements--;
    }
    while (numberOfLines)
    {
        vector<lines>::iterator q = linesVector.begin();
        vector<lines>::iterator p = linesVector.erase(q);
        numberOfLines--;
    }
    fscanf(fptr, "%d", &numberOfElements);
    for (int i = 0; i < numberOfElements; i++)
    {
        int auxType;
        int auxHasText;
        fscanf(fptr, "%d", &auxType);
        Vector2i auxPosition;
        fscanf(fptr, "%d", &auxPosition.x);
        fscanf(fptr, "%d", &auxPosition.y);
        elementsVector.push_back(Form(elementSize, elementSize, auxPosition.x, auxPosition.y, auxType));
        fscanf(fptr, "%d", &auxHasText);
        elementsVector[i].hasText = auxHasText;
        if (auxHasText)
        {
            string auxString;
            char auxCharArray[50] = "";
            fscanf(fptr, "%s", auxCharArray);
            auxString = auxCharArray;
            elementsVector[i].text.setString(auxString);
            int auxWidth = elementsVector[i].text.getGlobalBounds().width;
            elementsVector[i].resize(auxWidth + 20);
        }
    }
    fscanf(fptr, "%d", &numberOfLines);
    for (int i = 0; i < numberOfLines; i++)
    {
        lines auxLine;
        fscanf(fptr, "%d", &auxLine.elementEnd);
        fscanf(fptr, "%d", &auxLine.elementStart);
        fscanf(fptr, "%d", &auxLine.lineStartsFromElse);
        Vector2f auxPositionStart, auxPositionEnd;
        auxPositionStart = elementsVector[auxLine.elementStart].inputLocation;
        if (auxLine.lineStartsFromElse)
            auxPositionEnd = elementsVector[auxLine.elementEnd].outputLocationElse;
        else
            auxPositionEnd = elementsVector[auxLine.elementEnd].outputLocation;
        placeLine(auxLine, auxPositionStart, auxPositionEnd);
        linesVector.push_back(auxLine);
    }
    fclose(fptr);
}

struct variable
{
    int value;
    string name;
};

vector<variable> schemeVariables;
int numberOfVariables = 0;

int startPosition = -1;

void buildScheme(vector<Form>& elementsVector, vector<lines> linesVector, int numberOfElements, int numberOfLines, int& startPosition)
{
    for (int i = 0; i < numberOfElements; i++)
    {
        elementsVector[i].nextElement = -1;
        elementsVector[i].nextElementElse = -1;
        if (elementsVector[i].getType() == 0)
            startPosition = i;
        elementsVector[i].changeToBaseColor();
    }
    for (int i = 0; i < numberOfLines; i++)
    {
        if (!linesVector[i].lineStartsFromElse)
            elementsVector[linesVector[i].elementEnd].nextElement = linesVector[i].elementStart;
        else
            elementsVector[linesVector[i].elementEnd].nextElementElse = linesVector[i].elementStart;
    }
}

void runScheme(vector<Form>& elementsVector, int startPosition)
{
    int currentPosition = startPosition;
    elementsVector[currentPosition].changeColor(0xffffffff);
    while (elementsVector[currentPosition].nextElement != -1)
    {
        currentPosition = elementsVector[currentPosition].nextElement;
        elementsVector[currentPosition].changeColor(0xffffffff);
    }
}

struct node {
    node* next;
    string text;
    int value;
    int color = 0xffffffff;
};

struct queue {
    node* first;
    node* last;
    int size;
}consoleLogQueue;

bool queueIsVoid(queue C)
{
    return C.size == 0;
}

void initQueue(queue& C)
{
    C.first = NULL;
    C.last = NULL;
    C.size = 0;
}

void dequeue(queue& C)
{
    if (!queueIsVoid(C))
    {
        node* firstElement;
        firstElement = C.first;
        C.first = C.first->next;
        delete firstElement;
        C.size--;
    }
    else
    {
        cerr << "EROARE: coada goala. ";
    }
}

void emptyQueue(queue& C)
{
    while (!queueIsVoid(C))
        dequeue(C);
}

void enqueue(queue& C, string element)
{
    node* newNode;
    if (queueIsVoid(C))
    {
        C.size = 1;
        C.first = new node;
        C.first->text = element;
        C.first->next = NULL;
        C.last = C.first;
    }
    else
    {
        C.size++;
        newNode = new node;
        newNode->text = element;
        newNode->next = NULL;
        C.last->next = newNode;
        C.last = newNode;
    }
}

struct stack {
    node* top;
    int size;
};

bool stackIsVoid(stack S)
{
    return S.size == 0;
}

void initStack(stack& S)
{
    S.top = NULL;
    S.size = 0;
}

void pop(stack& S)
{
    if (!stackIsVoid(S))
    {
        node* newTop;
        newTop = S.top->next;
        delete S.top;
        S.top = newTop;
        S.size--;
    }
    else
    {
        cerr << "EROARE: stiva goala. ";
    }
}

void emptyStack(stack& S)
{
    while (!stackIsVoid(S))
        pop(S);
}

void pushText(stack& S, string element)
{
    node* newNode;
    if (stackIsVoid(S))
    {
        S.size = 1;
        S.top = new node;
        S.top->text = element;
        S.top->next = NULL;
    }
    else
    {
        S.size++;
        newNode = new node;
        newNode->text = element;
        newNode->next = S.top;
        S.top = newNode;
    }
}

void pushValue(stack& S, int element)
{
    node* newNode;
    if (stackIsVoid(S))
    {
        S.size = 1;
        S.top = new node;
        S.top->value = element;
        S.top->next = NULL;
    }
    else
    {
        S.size++;
        newNode = new node;
        newNode->value = element;
        newNode->next = S.top;
        S.top = newNode;
    }
}

bool higherPrecedenceThan(char operator1, char operator2)
{
    int precedenceOperator1 = 0, precedenceOperator2 = 0;
    switch (operator1)
    {
    case '*': case '/': case '%':
        precedenceOperator1 = 3;
        break;
    case '+': case '-':
        precedenceOperator1 = 2;
    }
    switch (operator2)
    {
    case '*': case '/': case '%':
        precedenceOperator2 = 3;
        break;
    case '+': case '-':
        precedenceOperator2 = 2;
    }
    return precedenceOperator1 >= precedenceOperator2;
}

string numberToString(int valueInt)
{
    long long int auxValueInt = 1;
    string valueString;
    valueString.clear();
    if (valueInt < 0)
    {
        valueInt *= -1;
        valueString += '-';
    }
    if (valueInt == 0)
        valueString = '0';
    while (valueInt)
    {
        int lastFigure = valueInt % 10;
        valueInt /= 10;
        auxValueInt = auxValueInt * 10 + lastFigure;
    }
    while (auxValueInt)
    {
        int lastFigure = auxValueInt % 10;
        auxValueInt /= 10;
        valueString += '0' + lastFigure;
    }
    valueString.erase(valueString.size() - 1);
    return valueString;
}

int stringToNumber(string valueString)
{
    int valueInt = 0;
    int valueIsNegative = 0;
    if (valueString[0] == '-')
        valueIsNegative = 1;
    for (int i = 0 + valueIsNegative; i < valueString.size(); i++)
        valueInt = valueInt * 10 + (int)(valueString[i] - '0');
    if (valueIsNegative)
        valueInt *= -1;
    return valueInt;
}

bool stringIsNumber(string valueString)
{
    if (valueString[0] != '-' && (valueString[0] < '0' || valueString[0]>'9'))
        return false;
    for (int i = 1; i < valueString.size(); i++)
        if (valueString[i] < '0' || valueString[i]>'9')
            return false;
    return true;
}

int operation(int value1, int value2, char operationType)
{
    switch (operationType)
    {
    case '*': return value2 * value1;
    case '/': return value2 / value1;
    case '%': return value2 % value1;
    case '+': return value2 + value1;
    case '-': return value2 - value1;
    default: return 0;
    }
}

void shuntingYardAlgorithm(string str, queue& postfixQueue)
{
    initQueue(postfixQueue);
    stack operatorStack;
    initStack(operatorStack);
    string auxString;
    bool nextValueIsNegative = false;
    for (int i = 0; i < str.size(); i++)
    {
        auxString.clear();
        if (nextValueIsNegative)
        {
            auxString = '-';
            nextValueIsNegative = false;
        }
        if (iswalnum(str[i]))
        {
            while (i < str.size() && iswalnum(str[i]))
            {
                auxString += str[i];
                i++;
            }
            i--;
            enqueue(postfixQueue, auxString);

        }
        if (str[i] == '-')
        {
            if (i == 0)
                enqueue(postfixQueue, "0");
            else
            {
                if (str[i - 1] == '(')
                    enqueue(postfixQueue, "0");
            }
        }
        if (strchr("*/%+-", str[i]))
        {
            if (!stackIsVoid(operatorStack))
            {
                while (!stackIsVoid(operatorStack) && operatorStack.top->text[0] != '(' && higherPrecedenceThan(operatorStack.top->text[0], str[i]))
                {
                    enqueue(postfixQueue, operatorStack.top->text);
                    pop(operatorStack);
                }
            }
            auxString = str[i];
            pushText(operatorStack, auxString);
        }
        if (str[i] == '(')
            pushText(operatorStack, "(");
        if (str[i] == ')')
        {
            while (!stackIsVoid(operatorStack) && operatorStack.top->text != "(")
            {
                enqueue(postfixQueue, operatorStack.top->text);
                pop(operatorStack);
            }
            pop(operatorStack);
        }
    }
    while (!stackIsVoid(operatorStack))
    {
        enqueue(postfixQueue, operatorStack.top->text);
        pop(operatorStack);
    }
}

int evaluateExpression(string str, vector<variable> variablesVector, int numberOfVariables, bool& allVariablesExist)
{
    queue postfixQueue;
    shuntingYardAlgorithm(str, postfixQueue);
    stack operandStack;
    initStack(operandStack);
    int auxOperand;
    while (!queueIsVoid(postfixQueue))
    {
        if (!strchr("*/%+-", postfixQueue.first->text[0]))
        {
            if (stringIsNumber(postfixQueue.first->text))
            {
                auxOperand = stringToNumber(postfixQueue.first->text);
                pushValue(operandStack, auxOperand);
                dequeue(postfixQueue);
            }
            else
            {
                bool variableFound = false;
                for (int i = 0; i < numberOfVariables && !variableFound; i++)
                    if (postfixQueue.first->text == variablesVector[i].name)
                    {
                        auxOperand = variablesVector[i].value;
                        pushValue(operandStack, auxOperand);
                        dequeue(postfixQueue);
                        variableFound = 1;
                    }
                if (!variableFound)
                {
                    allVariablesExist = false;
                    return 0;
                }
            }
        }
        else
        {
            int value1 = operandStack.top->value;
            pop(operandStack);
            int value2 = operandStack.top->value;
            pop(operandStack);
            int result = operation(value1, value2, postfixQueue.first->text[0]);
            pushValue(operandStack, result);
            dequeue(postfixQueue);
        }
    }
    if (allVariablesExist)
        return operandStack.top->value;
    else return 0;
}

bool expressionIsValid(string str)
{
    if (strchr("*/%+)=", str[0]))
        return false;
    if (strchr("(*/%+-=", str[str.size() - 1]))
        return false;
    for (int i = 1; i < str.size() - 1; i++)
    {
        if (strchr("(*/%+-", str[i]) && strchr("*/%+)", str[i + 1]))
            return false;
        if (strchr("*/%+-", str[i]) && str[i + 1] == '-')
            return false;
        if (strchr("=!", str[i]))
            return false;
    }
    return true;
}

int decisionCase(char ch1, char ch2)
{
    switch (ch1)
    {
    case '=':
        if (ch2 == '=')
            return 1;
        else return 0;
        break;
    case '!':
        if (ch2 == '=')
            return 2;
        else return 0;
        break;
    case '>':
        if (ch2 == '=')
            return 3;
        else return 4;
        break;
    case '<':
        if (ch2 == '=')
            return 5;
        else return 6;
        break;
    default:
        return 0;
    }
}

bool decisionValue(int value1, int value2, int decisionType)
{
    switch (decisionType)
    {
    case 1: return value1 == value2;
    case 2: return value1 != value2;
    case 3: return value1 >= value2;
    case 4: return value1 > value2;
    case 5: return value1 <= value2;
    case 6: return value1 < value2;
    }
}

bool syntaxIsCorrect(string str, int type)
{
    int auxPosition = 0;
    switch (type)
    {
    case 2: case 3:
        if (str[0] == '_' || (str[0] >= '0' && str[0] <= '9'))
            return false;
        break;
    case 4:
        if (str[0] == '_' || str[0] == '=')
            return false;
        for (int i = 1; i < str.size() - 1 && auxPosition == 0; i++)
            if (strchr("><!=", str[i]))
                auxPosition = i;
        if (auxPosition == 0)
            return false;
        else
        {
            string variableName;
            string mathExpression1;
            string mathExpression2;
            int mathExpression1_Value = 0;
            int mathExpression2_Value = 0;
            variableName.clear();
            mathExpression1.clear();
            mathExpression2.clear();
            int decisionType = decisionCase(str[auxPosition], str[auxPosition + 1]);
            if (decisionType)
            {
                for (int i = 0; i < auxPosition; i++)
                    mathExpression1 += str[i];
                if (str[auxPosition + 1] == '=')
                    auxPosition++;
                for (int i = auxPosition + 1; i < str.size(); i++)
                    mathExpression2 += str[i];
                if (expressionIsValid(mathExpression1) && expressionIsValid(mathExpression2))
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
        break;
    case 5:
        if (str[0] == '_' || (str[0] >= '0' && str[0] <= '9') || str[0] == '=')
            return false;
        for (int i = 1; i < str.size() - 1 && auxPosition == 0; i++)
            if (str[i] == '=')
                auxPosition = i;
        if (auxPosition == 0)
            return false;
        else
        {
            bool variableNameIsViable = true;
            for (int i = 0; i < auxPosition; i++)
                if (!iswalnum(str[i]))
                    variableNameIsViable = false;
            if (variableNameIsViable)
            {
                string auxString;
                auxString.clear();
                for (int i = auxPosition + 1; i < str.size(); i++)
                    auxString += str[i];
                if (expressionIsValid(auxString))
                    return true;
                else
                    return false;
            }
            else
                return false;
        }
    }
}

int main()
{
    RenderWindow MENU(VideoMode(windowLength, windowHeight), "Main Menu", Style::Default);

    MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);
    if (!font.loadFromFile("futur.ttf"))
    {
        //eroare
    }
    RectangleShape background;
    background.setSize(Vector2f(windowLength, windowHeight));
    Texture MainTexture;
    MainTexture.loadFromFile("img/fantastic.jpg");
    background.setTexture(&MainTexture);
    Text textInfo;
    textInfo.setFont(font);
    textInfo.setCharacterSize(24);
    textInfo.setFillColor(Color(244, 202, 22));
    textInfo.setString("User Guide \n\n To insert the elements of a logical scheme, the INSERT button will be used, which offers several predefined elements such as:\n             start, stop, input, output, decision and expression. \n After selecting a block, it will appear in the bounded space.\n\nThe blocks can be:\n\n- moved(holding down left click)\n\nThe movement can be made on the entire surface of the window, also the elements have collision so they cannot be overlapped\n\n- connected to each other(right click on the first block then right click on the second block)\n\nThe connection is made by lines from the first selected block to the second.\n\n- removed (middle click)\n\nWhen removing, both the block and the line / lines that connected that block with another are deleted(if these lines exist)\n\nIt is also possible to delete only the line by repeating the creation step (right click on the first block then right click on the second block).\n\n- edited(left click + enter)\n\nEditing assigns values or operations to elements to form a logical scheme.\n\nWhen the scheme is finished, it can be run using the RUN button.\nTo open a scheme file, use the FILE button and then declare the location where the file was saved.\nIf there is a need to save the scheme, it can be done by opening the scheme file (the FILE button) + the SAVE button.\nThe LOAD button allows returning to the previously saved scheme in case the need arises.");


    SoundBuffer buffer;
    Sound music;
    buffer.loadFromFile("BabyElephantWalk60.wav");
    music.setBuffer(buffer);
    music.setLoop(true);
    music.play();
    bool playSound = 1;

    string menuButtonsText[] = { "INSERT","BUILD","RUN","FILE","SAVE","LOAD" };
    vector<Button> menuButtons;
    for (int i = 0; i < numberOfMenuButtons; i++)
    {
        menuButtons.push_back(Button(menuButtonLength, menuButtonHeight, (i + 2) * inBetweenSpace + (i + 0.3) * menuButtonLength, distanceFromWindowEdge, menuButtonsText[i], menuButtonCharacterSize));
    }

    string insertButtonsText[] = { "start","stop","input","output","decision","expression" };
    vector<Button> insertButtons;
    for (int i = 0; i < numberOfInsertButtons; i++)
    {
        insertButtons.push_back(Button(insertButtonLength, insertButtonHeight, distanceFromWindowEdge, (i + 2) * inBetweenSpace + i * insertButtonHeight + menuButtonHeight, insertButtonsText[i], insertButtonCharacterSize));
    }

    struct runButtons
    {
        Button next = Button(menuButtonLength - 25, menuButtonHeight, runButtonPosition, 50, "NEXT", menuButtonCharacterSize);
        Button end = Button(menuButtonLength - 25, menuButtonHeight, runButtonPosition + menuButtonLength, 50, "END", menuButtonCharacterSize);
    }run;

    lines lastLineAuxiliary;
    vector<lines> line;
    int numberOfLines = 0;
    bool lineStarted = 0;
    bool lineStartedIsElse = 0;

    int insertIsPressed = -1;
    bool fileIsPressed = 0;
    bool leftMouseIsPressed = 0;
    bool buildWasPressed = 0;
    bool runIsPressed = 0;
    int runCurrentPosition = -1;
    int runPreviousPosition = -1;
    bool startBlockAlreadyPlaced = 0;
    vector<Form> elements;
    int numberOfElements = 0;
    sf::Vector2f distanceMoved;

    sf::RectangleShape startingBox(sf::Vector2f(startingBoxSize, startingBoxSize));
    startingBox.setFillColor(sf::Color::Transparent);
    startingBox.setOutlineThickness(-5);
    startingBox.setOutlineColor(sf::Color::Black);
    startingBox.setPosition(startingBoxPosition_x, startingBoxPosition_y);
    sf::FloatRect startingBoundingBox = startingBox.getGlobalBounds();
    sf::RectangleShape usableArea(sf::Vector2f(windowLength - insertButtonLength - 2 * elementSize - 350, windowHeight - menuButtonHeight - 2 * elementSize - 60));
    usableArea.setPosition(insertButtonLength + elementSize + 50, menuButtonHeight + elementSize + 50);
    sf::FloatRect usableAreaBoundingBox = usableArea.getGlobalBounds();

    string fileNameAux;
    string fileName;
    fileNameAux.erase();
    fileName.erase();
    const char* fileName_ptr = fileName.c_str();
    sf::Text fileNameInputField;
    fileNameInputField.setPosition(1250, 840);
    fileNameInputField.setCharacterSize(15);
    fileNameInputField.setFont(font);

    sf::Text consoleLogText[consoleLogLinesShown + 3];
    for (int i = 0; i < consoleLogLinesShown; i++)
    {
        consoleLogText[i].setCharacterSize(consoleLogTextSize);
        consoleLogText[i].setFont(font);
        consoleLogText[i].setFillColor(Color::White);
        consoleLogText[i].setPosition(Vector2f(consoleLogTextPosition_x, consoleLogTextPosition_y + i * 20));
    }
    sf::RectangleShape consoleLogBox;
    consoleLogBox.setPosition(Vector2f(consoleLogBoxPosition_x, consoleLogBoxPosition_y));
    consoleLogBox.setSize(Vector2f(consoleLogBoxSize_width, consoleLogBoxSize_height));
    consoleLogBox.setFillColor(Color::Black);
    consoleLogBox.setOutlineThickness(-5);
    consoleLogBox.setOutlineColor(Color::White);

    bool errorOccurred = 0;
    bool inputVariable = 0;
    string variableValueString;
    variableValueString.erase();
    int variableValueInt = 0;
    bool valueIsNegative = 0;
    bool variableFound = 0;

    string elementTextAux;
    elementTextAux.erase();

    node* newNode = new node;

    cout << evaluateExpression("2-4", schemeVariables, numberOfVariables, variableFound);

    while (MENU.isOpen())
    {
        Event event;

        while (MENU.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                MENU.close();
            }
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up)
                {
                    mainMenu.MoveUp();
                    break;
                }
                if (event.key.code == Keyboard::Down)
                {
                    mainMenu.MoveDown();
                    break;
                }
                if (event.key.code == Keyboard::Return)
                {
                    RenderWindow Play(VideoMode(windowLength, windowHeight), "Game");
                    RenderWindow Info(VideoMode(windowLength, windowHeight), "Info");

                    int x = mainMenu.MainMenuPressed();
                    if (x == 0)
                    {
                        while (Play.isOpen())
                        {
                            Event aevent;
                            sf::Event event;
                            sf::Vector2f mouseCoordinates(sf::Mouse::getPosition(Play));
                            int buttonPressed = 0;
                            if (!runIsPressed)
                            {
                                while (Play.pollEvent(event))
                                {
                                    if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                                        Play.close();
                                    if (event.type == sf::Event::MouseButtonPressed)
                                    {
                                        bool elementIsPressed;
                                        switch (event.mouseButton.button)
                                        {
                                        case Mouse::Left:
                                            buttonPressed = 0;
                                            elementIsPressed = 0;
                                            for (int i = 0; i < numberOfMenuButtons; i++)
                                            {
                                                if (menuButtons[i].boundingBox.contains(mouseCoordinates))
                                                    buttonPressed = i + 1;
                                            }
                                            if (insertIsPressed == 1)
                                            {
                                                for (int i = 0; i < numberOfInsertButtons; i++)
                                                    if (insertButtons[i].boundingBox.contains(mouseCoordinates))
                                                        buttonPressed = -i - 1;
                                            }
                                            for (int i = 0; i < numberOfElements; i++)
                                            {
                                                if (elements[i].isPressed == 2 && elements[i].hasText)
                                                    if (!syntaxIsCorrect(elements[i].text.getString(), elements[i].getType()))
                                                    {
                                                        enqueue(consoleLogQueue, "Error: syntax is incorrect");
                                                        consoleLogQueue.last->color = 0xff0000ff;
                                                        enqueue(consoleLogQueue, "Introduce text again");
                                                        consoleLogQueue.last->color = 0xff0000ff;
                                                        elements[i].text.setString("");
                                                        elements[i].resize(20);
                                                        elements[i].hasText = false;
                                                        moveConnectedLines(elements, line, numberOfElements, numberOfLines, i);
                                                    }
                                                elements[i].isPressed = 0;
                                                if (elements[i].boundingBox.contains(mouseCoordinates))
                                                {
                                                    distanceMoved.x = mouseCoordinates.x - elements[i].getPosition().x;
                                                    distanceMoved.y = mouseCoordinates.y - elements[i].getPosition().y;
                                                    elements[i].isMove = 1;
                                                    if (elements[i].isPressed == 0 && elements[i].getType() != 0 && elements[i].getType() != 1)
                                                    {
                                                        elements[i].isPressed = 1;
                                                        elementIsPressed = 1;
                                                    }
                                                    else
                                                        elements[i].isPressed = 0;
                                                }
                                                else
                                                    elements[i].isPressed = 0;
                                            }
                                            if (!elementIsPressed)
                                                elementTextAux.erase();
                                            break;
                                        case Mouse::Middle:
                                            for (int i = 0; i < numberOfElements; i++)
                                                if (elements[i].boundingBox.contains(mouseCoordinates))
                                                {
                                                    if (elements[i].getType() == 0)
                                                        startBlockAlreadyPlaced = 0;
                                                    for (int j = 0; j < numberOfLines; j++)
                                                    {
                                                        if (line[j].elementEnd == i || line[j].elementStart == i)
                                                        {
                                                            vector<lines>::iterator q = line.begin();
                                                            q += j;
                                                            vector<lines>::iterator p = line.erase(q);
                                                            numberOfLines--;
                                                            j--;
                                                        }

                                                    }
                                                    for (int j = 0; j < numberOfLines; j++)
                                                    {
                                                        if (line[j].elementEnd > i)
                                                            line[j].elementEnd--;
                                                        if (line[j].elementStart > i)
                                                            line[j].elementStart--;
                                                    }
                                                    vector<Form>::iterator q = elements.begin();
                                                    q += i;
                                                    vector<Form>::iterator p = elements.erase(q);
                                                    i--;
                                                    numberOfElements--;
                                                    enqueue(consoleLogQueue, "Block and connecting lines eliminated");
                                                }
                                            break;
                                        case Mouse::Right:
                                            bool ok = 0;
                                            for (int i = 0; i < numberOfElements; i++)
                                                if (elements[i].boundingBox.contains(mouseCoordinates))
                                                {
                                                    if (lineStarted)
                                                    {
                                                        if (lastLineAuxiliary.elementEnd != i)
                                                        {
                                                            int aux = lastLineAuxiliary.elementEnd;
                                                            Vector2f auxStartPosition, auxEndPosition;
                                                            lastLineAuxiliary.elementStart = i;
                                                            if (lastLineAuxiliary.lineStartsFromElse)
                                                                auxEndPosition = elements[aux].outputLocationElse;
                                                            else
                                                                auxEndPosition = elements[aux].outputLocation;
                                                            auxStartPosition = elements[i].inputLocation;
                                                            placeLine(lastLineAuxiliary, auxStartPosition, auxEndPosition);
                                                            bool duplicateLine = 0;
                                                            bool lineStartsFromSameElementAsAnother = 0;
                                                            int lineToEraseIndex;
                                                            for (int i = 0; i < numberOfLines && !duplicateLine; i++)
                                                            {
                                                                if (line[i].elementEnd == lastLineAuxiliary.elementEnd && line[i].lineStartsFromElse == lastLineAuxiliary.lineStartsFromElse)
                                                                {
                                                                    if (line[i].elementStart == lastLineAuxiliary.elementStart)
                                                                        duplicateLine = 1;
                                                                    else
                                                                        lineStartsFromSameElementAsAnother = 1;
                                                                    lineToEraseIndex = i;
                                                                }
                                                            }
                                                            if (duplicateLine || lineStartsFromSameElementAsAnother)
                                                            {
                                                                vector<lines>::iterator q = line.begin();
                                                                q += lineToEraseIndex;
                                                                vector<lines>::iterator p = line.erase(q);
                                                                numberOfLines--;
                                                            }
                                                            if (!duplicateLine)
                                                            {
                                                                line.push_back(lastLineAuxiliary);
                                                                numberOfLines++;
                                                            }
                                                            lineStarted = 0;
                                                        }
                                                    }
                                                    else
                                                    {
                                                        lastLineAuxiliary.elementEnd = i;
                                                        lineStarted = 1;
                                                        if (elements[i].getType() == 4 && mouseCoordinates.x > elements[i].x + elements[i].length)
                                                            lastLineAuxiliary.lineStartsFromElse = 1;
                                                        else
                                                            lastLineAuxiliary.lineStartsFromElse = 0;
                                                    }
                                                    ok = 1;
                                                }
                                            if (!ok)
                                                lineStarted = 0;
                                        }
                                    }
                                    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                                        for (int i = 0; i < numberOfElements; i++)
                                            elements[i].isMove = 0;
                                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
                                    {
                                        for (int i = 0; i < numberOfElements; i++)
                                        {
                                            if (elements[i].isPressed == 2)
                                            {
                                                if (!syntaxIsCorrect(elements[i].text.getString(), elements[i].getType()))
                                                {
                                                    enqueue(consoleLogQueue, "Error: syntax is incorrect");
                                                    consoleLogQueue.last->color = 0xff0000ff;
                                                    enqueue(consoleLogQueue, "Introduce text again");
                                                    consoleLogQueue.last->color = 0xff0000ff;
                                                    elements[i].text.setString("");
                                                    elements[i].resize(20);
                                                    elements[i].hasText = false;
                                                    moveConnectedLines(elements, line, numberOfElements, numberOfLines, i);
                                                }
                                                elements[i].isPressed = 0;
                                                elementTextAux.erase();
                                            }
                                            if (elements[i].isPressed == 1)
                                            {
                                                elements[i].isPressed = 2;
                                                elementTextAux.erase();
                                                elements[i].text.setString(elementTextAux);
                                                elements[i].hasText = 0;
                                            }
                                        }
                                    }
                                    if (event.type == sf::Event::TextEntered)
                                    {
                                        for (int i = 0; i < numberOfElements; i++)
                                        {
                                            if (elements[i].isPressed == 2)
                                            {
                                                if (event.text.unicode == 8)
                                                {
                                                    if (elementTextAux.size())
                                                        elementTextAux.erase(elementTextAux.size() - 1);
                                                }
                                                else
                                                {
                                                    if ((elements[i].getType() != 2 && strchr("!=><+-*/%()", event.text.unicode)) || iswalnum(event.text.unicode))
                                                        elementTextAux += event.text.unicode;
                                                }
                                                elements[i].text.setString(elementTextAux);
                                                if (elementTextAux.size())
                                                    elements[i].hasText = 1;
                                                else
                                                    elements[i].hasText = 0;
                                                int auxWidth = elements[i].text.getGlobalBounds().width;
                                                elements[i].resize(auxWidth + 20);
                                                moveConnectedLines(elements, line, numberOfElements, numberOfLines, i);
                                            }
                                        }
                                    }
                                    if (fileIsPressed)
                                    {
                                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
                                        {
                                            fileName = fileNameAux;
                                            fileName_ptr = fileName.c_str();
                                            fileNameAux.erase();
                                            fileIsPressed = 0;
                                            std::cout << fileName_ptr;
                                            enqueue(consoleLogQueue, "File path assigned");
                                        }
                                        if (event.type == sf::Event::TextEntered)
                                        {
                                            if (event.text.unicode == 8)
                                            {
                                                if (fileNameAux.size())
                                                    fileNameAux.erase(fileNameAux.size() - 1);
                                            }
                                            else
                                                fileNameAux += event.text.unicode;
                                            consoleLogQueue.last->text = fileNameAux;
                                        }
                                    }
                                }
                                string auxString;
                                switch (buttonPressed)
                                {
                                case 1:
                                    if (insertIsPressed == -1)
                                        enqueue(consoleLogQueue, "INSERT menu opened");
                                    else
                                        enqueue(consoleLogQueue, "INSERT menu closed");
                                    insertIsPressed *= -1;
                                    fileIsPressed = 0;
                                    break;
                                case 2:
                                    auxString = "BUILD was pressed";
                                    enqueue(consoleLogQueue, auxString);
                                    buildScheme(elements, line, numberOfElements, numberOfLines, startPosition);
                                    buildWasPressed = 1;
                                    insertIsPressed = -1;
                                    fileIsPressed = 0;
                                    runCurrentPosition = startPosition;
                                    break;
                                case 3:
                                    auxString = "Running attempted";
                                    enqueue(consoleLogQueue, auxString);
                                    insertIsPressed = -1;
                                    fileIsPressed = 0;
                                    if (!buildWasPressed)
                                    {
                                        buildScheme(elements, line, numberOfElements, numberOfLines, startPosition);
                                        buildWasPressed = 1;
                                    }
                                    else
                                    {
                                        if (!startBlockAlreadyPlaced)
                                        {
                                            enqueue(consoleLogQueue, "Error: place START block first");
                                            consoleLogQueue.last->color = 0xff0000ff;
                                        }
                                        else
                                        {
                                            while (numberOfVariables)
                                            {
                                                vector<variable>::iterator q = schemeVariables.begin();
                                                vector<variable>::iterator p = schemeVariables.erase(q);
                                                numberOfVariables--;
                                            }
                                            emptyQueue(consoleLogQueue);
                                            enqueue(consoleLogQueue, "Run started");
                                            runIsPressed = 1;
                                        }
                                    }
                                    break;
                                case 4:
                                    enqueue(consoleLogQueue, "Input file path: ");
                                    enqueue(consoleLogQueue, "");
                                    insertIsPressed = -1;
                                    fileIsPressed = 1;
                                    break;
                                case 5:
                                    auxString = "Scheme was saved";
                                    enqueue(consoleLogQueue, auxString);
                                    outputInFile(fileName_ptr, elements, line, numberOfElements, numberOfLines);
                                    insertIsPressed = -1;
                                    fileIsPressed = 0;
                                    break;
                                case 6:
                                    auxString = "Scheme was loaded from file";
                                    enqueue(consoleLogQueue, auxString);
                                    inputFromFile(fileName_ptr, elements, line, numberOfElements, numberOfLines);
                                    insertIsPressed = -1;
                                    fileIsPressed = 0;
                                    buildWasPressed = 0;
                                    break;
                                case -1:
                                    if (!startBlockAlreadyPlaced)
                                    {
                                        elements.push_back(Form(elementSize, elementSize, elementInitialPosition_x, elementInitialPosition_y, 0));
                                        numberOfElements++;
                                        startBlockAlreadyPlaced = 1;
                                        auxString = "START block placed";
                                    }
                                    else
                                        auxString = "START block already placed";
                                    enqueue(consoleLogQueue, auxString);
                                    break;
                                case -2:
                                    auxString = "STOP block placed";
                                    enqueue(consoleLogQueue, auxString);
                                    elements.push_back(Form(elementSize, elementSize, elementInitialPosition_x, elementInitialPosition_y, 1));
                                    numberOfElements++;
                                    break;
                                case -3:
                                    auxString = "INPUT block placed";
                                    enqueue(consoleLogQueue, auxString);
                                    elements.push_back(Form(elementSize, elementSize, elementInitialPosition_x, elementInitialPosition_y, 2));
                                    numberOfElements++;
                                    break;
                                case -4:
                                    auxString = "OUTPUT block placed";
                                    enqueue(consoleLogQueue, auxString);
                                    elements.push_back(Form(elementSize, elementSize, elementInitialPosition_x, elementInitialPosition_y, 3));
                                    numberOfElements++;
                                    break;
                                case -5:
                                    auxString = "DECISION block placed";
                                    enqueue(consoleLogQueue, auxString);
                                    elements.push_back(Form(elementSize, elementSize, elementInitialPosition_x, elementInitialPosition_y, 4));
                                    numberOfElements++;
                                    break;
                                case -6:
                                    auxString = "EXPRESSION block placed";
                                    enqueue(consoleLogQueue, auxString);
                                    elements.push_back(Form(elementSize, elementSize, elementInitialPosition_x, elementInitialPosition_y, 5));
                                    numberOfElements++;
                                }
                            }
                            else
                            {
                                while (Play.pollEvent(event))
                                {
                                    if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                                        Play.close();
                                    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                                    {
                                        if (run.next.boundingBox.contains(mouseCoordinates) && !inputVariable)
                                        {
                                            string auxString;
                                            cout << "Next was pressed\n";
                                            switch (elements[runCurrentPosition].getType())
                                            {
                                            case 0:
                                                enqueue(consoleLogQueue, "Run begins from START block");
                                                elements[runCurrentPosition].changeToEvaluationColor();
                                                runPreviousPosition = runCurrentPosition;
                                                runCurrentPosition = elements[runCurrentPosition].nextElement;
                                                break;
                                            case 1:
                                                enqueue(consoleLogQueue, "Run ended at STOP block");
                                                elements[runPreviousPosition].changeToBaseColor();
                                                runPreviousPosition = runCurrentPosition;
                                                elements[runCurrentPosition].changeToEvaluationColor();
                                                runIsPressed = 0;
                                                break;
                                            case 2:
                                                if (elements[runCurrentPosition].hasText)
                                                {
                                                    auxString = "Variable " + elements[runCurrentPosition].text.getString() + " has the value: ";
                                                    enqueue(consoleLogQueue, auxString);
                                                    inputVariable = 1;
                                                    enqueue(consoleLogQueue, "");
                                                }
                                                else
                                                {
                                                    enqueue(consoleLogQueue, "Error: no variable name specified");
                                                    consoleLogQueue.last->color = 0xff0000ff;
                                                    errorOccurred = 1;
                                                }
                                                elements[runPreviousPosition].changeToBaseColor();
                                                runPreviousPosition = runCurrentPosition;
                                                elements[runCurrentPosition].changeToEvaluationColor();
                                                break;
                                            case 3:
                                                cout << "Variable or constant output at OUTPUT block\n";
                                                elements[runPreviousPosition].changeToBaseColor();
                                                runPreviousPosition = runCurrentPosition;
                                                elements[runCurrentPosition].changeToEvaluationColor();
                                                variableFound = 0;
                                                for (int i = 0; i < numberOfVariables; i++)
                                                {
                                                    if (elements[runCurrentPosition].text.getString() == schemeVariables[i].name)
                                                    {
                                                        enqueue(consoleLogQueue, "Output value is: " + numberToString(schemeVariables[i].value));
                                                        variableFound = 1;
                                                    }
                                                }
                                                if (!variableFound)
                                                {
                                                    enqueue(consoleLogQueue, "Error: variable doesn't exist");
                                                    consoleLogQueue.last->color = 0xff0000ff;
                                                    errorOccurred = 1;
                                                }
                                                runCurrentPosition = elements[runCurrentPosition].nextElement;
                                                break;
                                            case 4:
                                                cout << "Decision is made at IF block\n";
                                                elements[runPreviousPosition].changeToBaseColor();
                                                runPreviousPosition = runCurrentPosition;
                                                elements[runCurrentPosition].changeToEvaluationColor();
                                                if (elements[runCurrentPosition].hasText)
                                                {
                                                    int auxPosition = 0;
                                                    while (!strchr("!=><", elements[runCurrentPosition].text.getString()[auxPosition]) && auxPosition < elements[runCurrentPosition].text.getString().getSize() - 1)
                                                        auxPosition++;
                                                    if (auxPosition == elements[runCurrentPosition].text.getString().getSize() - 1)
                                                    {
                                                        enqueue(consoleLogQueue, "Error: decision syntax is wrong");
                                                        consoleLogQueue.last->color = 0xff0000ff;
                                                        errorOccurred = 1;
                                                    }
                                                    else
                                                    {
                                                        string variableName;
                                                        string mathExpression1;
                                                        string mathExpression2;
                                                        int mathExpression1_Value = 0;
                                                        int mathExpression2_Value = 0;
                                                        variableFound = 0;
                                                        variableName.clear();
                                                        mathExpression1.clear();
                                                        mathExpression2.clear();
                                                        int decisionType = decisionCase(elements[runCurrentPosition].text.getString()[auxPosition], elements[runCurrentPosition].text.getString()[auxPosition + 1]);
                                                        if (decisionType)
                                                        {
                                                            bool allExpressionVariablesExist = true;
                                                            for (int i = 0; i < auxPosition; i++)
                                                                mathExpression1 += elements[runCurrentPosition].text.getString()[i];
                                                            if (elements[runCurrentPosition].text.getString()[auxPosition + 1] == '=')
                                                                auxPosition++;
                                                            for (int i = auxPosition + 1; i < elements[runCurrentPosition].text.getString().getSize(); i++)
                                                                mathExpression2 += elements[runCurrentPosition].text.getString()[i];
                                                            if (expressionIsValid(mathExpression1) && expressionIsValid(mathExpression2))
                                                            {
                                                                mathExpression1_Value = evaluateExpression(mathExpression1, schemeVariables, numberOfVariables, allExpressionVariablesExist);
                                                                mathExpression2_Value = evaluateExpression(mathExpression2, schemeVariables, numberOfVariables, allExpressionVariablesExist);
                                                                if (allExpressionVariablesExist)
                                                                {
                                                                    if (decisionValue(mathExpression1_Value, mathExpression2_Value, decisionType))
                                                                    {
                                                                        runCurrentPosition = elements[runCurrentPosition].nextElement;
                                                                        enqueue(consoleLogQueue, "Decision evalued: condition met");
                                                                    }
                                                                    else
                                                                    {
                                                                        runCurrentPosition = elements[runCurrentPosition].nextElementElse;
                                                                        enqueue(consoleLogQueue, "Decision evalued: condition not met");
                                                                    }
                                                                }
                                                                else
                                                                {
                                                                    enqueue(consoleLogQueue, "Error: incorrect variable names");
                                                                    consoleLogQueue.last->color = 0xff0000ff;
                                                                    errorOccurred = 1;
                                                                }
                                                            }
                                                            else
                                                            {
                                                                enqueue(consoleLogQueue, "Error: incorrect expression syntax");
                                                                consoleLogQueue.last->color = 0xff0000ff;
                                                                errorOccurred = 1;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            enqueue(consoleLogQueue, "Error: incorrect decision syntax");
                                                            consoleLogQueue.last->color = 0xff0000ff;
                                                            errorOccurred = 1;
                                                        }

                                                    }
                                                }
                                                else
                                                {
                                                    enqueue(consoleLogQueue, "Error: no decision to evaluate");
                                                    consoleLogQueue.last->color = 0xff0000ff;
                                                    errorOccurred = 1;
                                                }
                                                break;
                                            case 5:
                                                if (elements[runCurrentPosition].hasText)
                                                {
                                                    int auxPosition = 0;
                                                    while (elements[runCurrentPosition].text.getString()[auxPosition] != '=' && auxPosition < elements[runCurrentPosition].text.getString().getSize() - 1)
                                                        auxPosition++;
                                                    if (auxPosition == elements[runCurrentPosition].text.getString().getSize() - 1)
                                                    {
                                                        enqueue(consoleLogQueue, "Error: incorrect expression syntax");
                                                        consoleLogQueue.last->color = 0xff0000ff;
                                                        errorOccurred = 1;
                                                    }
                                                    else
                                                    {
                                                        bool allExpressionVariablesExist = true;
                                                        variable auxVariable;
                                                        auxVariable.name;
                                                        string mathExpression;
                                                        variableFound = 0;
                                                        auxVariable.name.clear();
                                                        mathExpression.clear();
                                                        for (int i = 0; i < auxPosition; i++)
                                                            auxVariable.name += elements[runCurrentPosition].text.getString()[i];
                                                        for (int i = auxPosition + 1; i < elements[runCurrentPosition].text.getString().getSize(); i++)
                                                            mathExpression += elements[runCurrentPosition].text.getString()[i];
                                                        if (expressionIsValid(mathExpression))
                                                        {
                                                            auxVariable.value = evaluateExpression(mathExpression, schemeVariables, numberOfVariables, allExpressionVariablesExist);
                                                            if (allExpressionVariablesExist)
                                                            {
                                                                for (int i = 0; i < numberOfVariables && !variableFound; i++)
                                                                    if (auxVariable.name == schemeVariables[i].name)
                                                                    {
                                                                        variableFound = 1;
                                                                        schemeVariables[i].value = auxVariable.value;
                                                                        enqueue(consoleLogQueue, schemeVariables[i].name + " now has the value " + numberToString(schemeVariables[i].value));
                                                                    }
                                                                if (!variableFound)
                                                                {
                                                                    schemeVariables.push_back(auxVariable);
                                                                    numberOfVariables++;
                                                                    enqueue(consoleLogQueue, "Created variable " + auxVariable.name + " with the value: ");
                                                                    enqueue(consoleLogQueue, numberToString(auxVariable.value));
                                                                }
                                                            }
                                                            else
                                                            {
                                                                enqueue(consoleLogQueue, "Error: variable used doesn't exist");
                                                                consoleLogQueue.last->color = 0xff0000ff;
                                                                errorOccurred = 1;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            enqueue(consoleLogQueue, "Error: incorrect expression syntax");
                                                            consoleLogQueue.last->color = 0xff0000ff;
                                                            errorOccurred = 1;
                                                        }
                                                    }
                                                }
                                                else
                                                {
                                                    enqueue(consoleLogQueue, "Error: no expression to evaluate");
                                                    consoleLogQueue.last->color = 0xff0000ff;
                                                    errorOccurred = 1;
                                                }
                                                elements[runPreviousPosition].changeToBaseColor();
                                                runPreviousPosition = runCurrentPosition;
                                                elements[runCurrentPosition].changeToEvaluationColor();
                                                runCurrentPosition = elements[runCurrentPosition].nextElement;
                                            }
                                            if (runCurrentPosition == -1)
                                            {
                                                elements[runPreviousPosition].changeToBaseColor();
                                                enqueue(consoleLogQueue, "Error: scheme is incomplete");
                                                consoleLogQueue.last->color = 0xff0000ff;
                                                errorOccurred = 1;
                                            }
                                            if (errorOccurred)
                                            {
                                                elements[runPreviousPosition].changeToBaseColor();
                                                runIsPressed = 0;
                                                errorOccurred = 0;
                                                enqueue(consoleLogQueue, "Run ended due to error");
                                                consoleLogQueue.last->color = 0xff0000ff;
                                            }
                                        }
                                        if (run.end.boundingBox.contains(mouseCoordinates))
                                        {
                                            runIsPressed = 0;
                                            inputVariable = 0;
                                            cout << "End was pressed\n";
                                            enqueue(consoleLogQueue, "Run ended");
                                        }
                                    }
                                    if (inputVariable)
                                    {
                                        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
                                        {
                                            variableValueString.erase();
                                            if (valueIsNegative)
                                                variableValueInt *= -1;
                                            bool variableAlreadyExists = 0;
                                            for (int i = 0; i < numberOfVariables; i++)
                                            {
                                                if (schemeVariables[i].name == elements[runCurrentPosition].text.getString())
                                                {
                                                    schemeVariables[i].value = variableValueInt;
                                                    variableAlreadyExists = 1;
                                                }
                                            }
                                            if (!variableAlreadyExists)
                                            {
                                                variable auxVariable;
                                                auxVariable.name = elements[runCurrentPosition].text.getString();
                                                auxVariable.value = variableValueInt;
                                                schemeVariables.push_back(auxVariable);
                                                numberOfVariables++;
                                            }
                                            enqueue(consoleLogQueue, "Value assigned");
                                            variableValueInt = 0;
                                            inputVariable = 0;
                                            runCurrentPosition = elements[runCurrentPosition].nextElement;
                                        }
                                        if (event.type == sf::Event::TextEntered)
                                        {
                                            if (event.text.unicode == 8)
                                            {
                                                if (variableValueString.size())
                                                {
                                                    variableValueString.erase(variableValueString.size() - 1);
                                                    variableValueInt /= 10;
                                                    if (!variableValueString.size())
                                                        valueIsNegative = 0;
                                                }
                                            }
                                            if (variableValueString.size() < 10 && event.text.unicode >= '0' && event.text.unicode <= '9')
                                            {
                                                variableValueString += event.text.unicode;
                                                variableValueInt = variableValueInt * 10 + (int)(event.text.unicode - '0');
                                            }
                                            if (!variableValueString.size() && event.text.unicode == '-')
                                            {
                                                variableValueString += event.text.unicode;
                                                valueIsNegative = 1;
                                            }
                                            consoleLogQueue.last->text = variableValueString;
                                        }
                                    }
                                }
                                if (run.next.boundingBox.contains(mouseCoordinates))
                                    run.next.changeColor(buttonColorHover);
                                else
                                    run.next.changeColor(buttonColor);
                                if (run.end.boundingBox.contains(mouseCoordinates))
                                    run.end.changeColor(buttonColorHover);
                                else
                                    run.end.changeColor(buttonColor);
                            }
                            Info.close();
                            Play.clear();
                            Play.clear(sf::Color(16, 13, 53));
                            Play.draw(startingBox);
                            if (fileIsPressed)
                                Play.draw(fileNameInputField);
                            if (runIsPressed)
                            {
                                Play.draw(run.next.getBox());
                                Play.draw(run.next.getText());
                                Play.draw(run.end.getBox());
                                Play.draw(run.end.getText());
                            }
                            for (int i = 0; i < numberOfElements; i++)
                            {
                                if (!runIsPressed && !fileIsPressed && elements[i].isMove)
                                {
                                    bool ok = 1;
                                    bool lineConnected = 0;
                                    Form auxForm(elements[i].length, elements[i].height, elements[i].x, elements[i].y, elements[i].type);
                                    auxForm.changePosition(mouseCoordinates.x - distanceMoved.x, mouseCoordinates.y - distanceMoved.y);
                                    for (int j = 0; j < numberOfElements && ok; j++)
                                        if (j != i && auxForm.boundingBox.intersects(elements[j].boundingBox))
                                            ok = 0;
                                    if ((!auxForm.boundingBox.intersects(usableAreaBoundingBox) || auxForm.boundingBox.intersects(startingBoundingBox)) && !elements[i].boundingBox.intersects(startingBoundingBox))
                                        ok = 0;
                                    if (ok)
                                    {
                                        elements[i].changePosition(mouseCoordinates.x - distanceMoved.x, mouseCoordinates.y - distanceMoved.y);
                                        moveConnectedLines(elements, line, numberOfElements, numberOfLines, i);
                                        /*for (int j = 0; j < numberOfLines; j++)
                                        {
                                            bool lineMoved = 0;
                                            Vector2f auxElementEnd, auxElementStart;
                                            if (line[j].elementEnd == i)
                                            {
                                                if (elements[i].getType() == 4 && line[j].lineStartsFromElse)
                                                    auxElementEnd = elements[i].outputLocationElse;
                                                else
                                                    auxElementEnd = elements[i].outputLocation;
                                                auxElementStart = line[j].point[0][0].position;
                                                lineMoved = 1;
                                            }
                                            if (line[j].elementStart == i)
                                            {
                                                auxElementStart = elements[i].inputLocation;
                                                auxElementEnd = line[j].point[2][1].position;
                                                lineMoved = 1;
                                            }
                                            if (lineMoved)
                                                placeLine(line[j], auxElementStart, auxElementEnd);
                                        }*/
                                    }
                                }
                                switch (elements[i].type)
                                {
                                case 0: case 1: case 5:
                                    Play.draw(elements[i].shape.rectangle);
                                    break;
                                case 2:
                                    Play.draw(elements[i].shape.trapez);
                                    break;
                                case 3:
                                    Play.draw(elements[i].shape.retrapez);
                                    break;
                                case 4:
                                    Play.draw(elements[i].shape.triangle);
                                }
                                Play.draw(elements[i].text);
                            }
                            for (int i = 0; i < numberOfLines; i++)
                                for (int j = 0; j < 3; j++)
                                    Play.draw(line[i].point[j], 2, Lines);
                            for (int i = 0; i < numberOfMenuButtons; i++)
                            {
                                if (menuButtons[i].boundingBox.contains(mouseCoordinates))
                                    menuButtons[i].changeColor(buttonColorHover);
                                else
                                    menuButtons[i].changeColor(buttonColor);
                                Play.draw(menuButtons[i].getBox());
                                Play.draw(menuButtons[i].getText());
                            }
                            if (insertIsPressed == 1)
                            {

                                for (int i = 0; i < numberOfInsertButtons; i++)
                                {
                                    if (insertButtons[i].boundingBox.contains(mouseCoordinates))
                                        insertButtons[i].changeColor(buttonColorHover);
                                    else
                                        insertButtons[i].changeColor(buttonColor);
                                    Play.draw(insertButtons[i].getBox());
                                    Play.draw(insertButtons[i].getText());
                                }
                            }
                            Play.draw(consoleLogBox);
                            while (consoleLogQueue.size > consoleLogLinesShown)
                                dequeue(consoleLogQueue);
                            if (!queueIsVoid(consoleLogQueue))
                                newNode = consoleLogQueue.first;
                            for (int i = 0; i < consoleLogQueue.size; i++)
                            {
                                string auxString = newNode->text;
                                int auxColor = newNode->color;
                                consoleLogText[i].setString(auxString);
                                consoleLogText[i].setFillColor(Color(auxColor));
                                Play.draw(consoleLogText[i]);
                                newNode = newNode->next;
                            }
                            Play.display();
                        }
                    }
                    if (x == 1)
                    {
                        while (Info.isOpen())
                        {
                            Event aevent;



                            while (Info.pollEvent(aevent))
                            {
                                if (aevent.type == Event::Closed)
                                    Info.close();

                                if (aevent.type == Event::KeyPressed)

                                    if (aevent.key.code == Keyboard::Escape)
                                        Info.close();
                            }

                            Play.close();
                            Info.clear();
                            Info.clear(Color(16, 13, 53));
                            Info.draw(textInfo);

                            Info.display();
                        }
                    }
                    if (x == 2)
                    {
                        if (playSound)
                        {
                            music.pause();
                            playSound = 0;
                        }
                        else
                        {
                            music.play();
                            playSound = 1;
                        }
                    }
                    if (x == 3)
                        MENU.close();
                    break;
                    break;
                }
            }
        }
        MENU.clear();
        MENU.draw(background);
        mainMenu.draw(MENU);

        MENU.display();
    }
}