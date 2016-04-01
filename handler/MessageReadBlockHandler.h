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
* Description   : MessageReadBlock handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-03-22
* Modifed       : 2016-03-22      | Shubo Yang      | Create
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageReadBlock.pb.h>
#include <TokenPool.h>
#include <MessageBlockData.pb.h>
#include <BlockHub.h>
#include <MelotonNode.h>
#include <ClientSession.h>

static int MessageReadBlockHandler( MRT::Session * session , uptr<MessageReadBlock> message )
{
    auto token_str  = message->token();
    auto token      = TokenPool::Instance()->CheckToken( token_str );
    auto client     = scast<ClientSession*>( session );

    // Check the token is exist or not
    if ( token == nullptr )
    {
        return -1;
    }

    auto size   = message->size();
    auto offset = message->offset();
    auto block  = BlockHub::Instance()->FindBlock( token->Index() );
    
    // Check if the size is out of range
    size = ( offset + size ) > block->Size ? ( block->Size - size ) : size;

    // Check if the size is bigger than the max tranfer size
    size = size > MAX_TRANSFER_SIZE ? MAX_TRANSFER_SIZE : size;

    auto data = BlockHub::Instance()->ReadBlock( block->Index , offset , size );

    uptr<MessageBlockData> reply = make_uptr( MessageBlockData );
    reply->set_token   ( token->TokenStr() );
    reply->set_size    ( data->Size() );
    reply->set_offset  ( offset );
    reply->set_data    ( data->Data() , 
                         data->Size() );
    reply->set_checksum( 0 );
    reply->set_islast  ( data->Size() == 0 );

    client->SendMessage( move_ptr( reply ) );

    return 0;
}
