#include "model/executioner.h"


Executioner::Executioner()
{
};

Executioner::Executioner(std::string script) : script(script)
{
};

void Executioner::updateScript(std::string script)
{
    this->script=script;
};

std::string Executioner::getScript()
{
    return script;
}

std::string Executioner::getResult()
{
    return result;
}

void Executioner::run()
{
    FILE * pipein_fp;
    char readbuf[80];
    result = "";

    if(( pipein_fp = popen( script.c_str(), "r" ) ) == NULL )
    {
        perror( "popen" );
        exit( - 10 );
    }

    while( fgets( readbuf, 80, pipein_fp ) )
    {
        result += readbuf;
    }

    if( pclose( pipein_fp ) ==- 1 )
    {
        printf( "Error closign pipe" );
        exit( - 11 );
    };
}

void Executioner::executeScript(std::string script)
{
    this->updateScript(script);
    this->start();
};
