#include <TokenPool.h>

string TokenPool::CreateToken( const size_t clientId , 
                               const size_t blockIndex,
                               const size_t time )
{
    auto token = make_sptr( Token , 
                            clientId , 
                            blockIndex , 
                            time );
    this->Push( token );

    return token->TokenStr();
}

sptr<Token> TokenPool::CheckToken( const string token )
{
    return this->Find( [&token] ( sptr<Token> t ) { 
        if ( t->TokenStr() == token )
            return true;
        return false;
    } );

    return nullptr;
}

TokenPool::TokenPool()
{
}

TokenPool::~TokenPool()
{
}
