#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

typedef struct Message
{
    char* message;
    TTF_Font* font;
    double X, Y;
}Message;


#endif // MESSAGE_H_INCLUDED
