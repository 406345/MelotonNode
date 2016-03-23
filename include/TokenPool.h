/***********************************************************************************
This file is part of Project for Meloton
For the latest info, see  https://github.com/Yhgenomics/MelotonNode.git

Copyright 2016 Yhgenomics

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
***********************************************************************************/

/***********************************************************************************
* Description   :
* Creator       : Shubo Yang
* Date          :
* Modifed       : When      | Who       | What
***********************************************************************************/

#ifndef TOKEN_POOL_H_
#define TOKEN_POOL_H_

#include <string>
#include <MRT.h>
#include <ObjectPool.h>

using std::string;

class Token
{
public:

    Token( size_t clientid , size_t index , size_t time )
    {
        this->token_        = MRT::UUID::Create();
        this->client_id_    = clientid;
        this->time_         = time;
        this->index_        = index;
    };

    ~Token() { };

    size_t ClientId () { return this->client_id_; };
    size_t Time     () { return this->time_; };
    string TokenStr () { return this->token_; };
    size_t Index    () { return this->index_; };
        
private:

    string token_      = "";
    size_t client_id_  = 0;
    size_t time_       = 0;
    size_t index_      = 0;
};

class TokenPool :
    public ObjectPool<sptr<Token>>
{
public:

    MAKE_SINGLETON( TokenPool );

    string      CreateToken( const size_t clientId , 
                             const size_t blockIndex,
                             const size_t time );

    sptr<Token> CheckToken ( const string token );

private:

    TokenPool ();
    ~TokenPool();
};

#endif // !TOKEN_POOL_H_ 