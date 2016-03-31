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

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <string>
#include <MRT.h>
#include <MelotonNode.h>

using std::string;

class Settings 
{
public:

    MAKE_SINGLETON( Settings );

    PP_GET_DEF( string , MasterAddress , master_address_ );
    PP_SET_DEF( string , MasterAddress , master_address_ );

    PP_GET_DEF( int , MasterPort , master_port_ );
    PP_SET_DEF( int , MasterPort , master_port_ );

    PP_GET_DEF( string , ListenerAddress , client_listener_address_ );
    PP_SET_DEF( string , ListenerAddress , client_listener_address_ );

    PP_GET_DEF( int , ListenerPort , this->client_listener_port_ );
    PP_SET_DEF( int , ListenerPort , this->client_listener_port_ );

private:

    Settings ()
    {

    }

    ~Settings()
    {

    }

    string master_address_          = "127.0.0.1";
    int    master_port_             = 100;
    string client_listener_address_ = "127.0.0.1";
    int    client_listener_port_    = 102;
};

#endif // !SETTINGS_H_ 