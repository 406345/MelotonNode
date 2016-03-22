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

#ifndef MELOTON_SESSION_H_
#define MELOTON_SESSION_H_

#include <MRT.h>
#include <google/protobuf/message.h>

#include <MelotonNode.h>

using MRT::Session;
using MRT::Buffer;

class MelotonSession :
    public Session
{
public:

    MelotonSession      ();
    ~MelotonSession     ();
    void    SendMessage ( uptr<google::protobuf::Message> message );
    size_t  Id          ()
    {
        return id_;
    };

protected:

    enum MelotonSessionParseState
    {
        kHead = 1,
        kLength,
        kBody
    };

    static size_t SessionId;

    // Callback when session is connnecting to remote server
    void OnConnect  ()                    override;

    // Callback when network data is arrived
    // @data : received data 
    void OnRead     ( uptr<Buffer> data ) override;

    // Callback when the data has been send to remote server
    void OnWrite    ( uptr<Buffer> data ) override;

    // Callback when the session is closed
    void OnClose    ()                    override;

    void dispatch_message( MRT::CircleBuffer & buffer );

    MelotonSessionParseState parse_state_;
    int                      body_length_;
    MRT::CircleBuffer        circle_buffer_;
    size_t                   id_;

};

#endif // !MELOTON_SESSION_H_ 