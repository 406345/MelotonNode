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
* Description   : MessageBlockData handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-03-22
* Modifed       : 2016-03-22      | Shubo Yang      | Create
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessageBlockData.pb.h>
#include <MessageBlockAccept.pb.h>
#include <TokenPool.h>
#include <BlockHub.h>
#include <ClientSession.h>
#include <MasterSession.h>
#include <MessageSyncBlock.pb.h>
#include <MessageBlockMeta.pb.h>

static int MessageBlockDataHandler( MRT::Session * session , uptr<MessageBlockData> message )
{
    auto client = scast<ClientSession*>( session );
    auto token  = TokenPool::Instance()->CheckToken( message->token() );

    if ( token == nullptr )
    {
        // Invailed access, disconnect it
        return -1;
    }

    auto block = BlockHub::Instance()->FindBlock( token->Index() );

    if ( block == nullptr )
    {
        // Check if the block is exist
        return -1;
    }

    if ( message->islast() )
    {
        block->Size = message->offset();
        BlockHub::Instance()->SaveBlockIndex( block );
        return -1;
    }

    size_t size   = message->size();
    size_t offset = message->offset();

    size = size > BLOCK_SIZE ? BLOCK_SIZE : size;
    size = ( offset + size ) > BLOCK_SIZE ? ( BLOCK_SIZE - offset ) : size;

    if ( size == 0 )
    {
        return -1;
    }

    block->Size += BlockHub::Instance()->WriteBlock( block->Index ,
                                                     offset ,
                                                     message->data().c_str() ,
                                                     size );
    BlockHub::Instance()->SaveBlockIndex( block );

    uptr<MessageBlockAccept> reply = make_uptr( MessageBlockAccept );
    reply->set_size         ( size );
    reply->set_token        ( token->TokenStr() );
    reply->set_checksum     ( 0 );
    reply->set_nextoffset   ( offset + size );
    reply->set_nextsize     ( BLOCK_TRANSFER_SIZE );
    client->SendMessage     ( move_ptr( reply ) );

    auto sync = make_uptr   ( MessageBlockMeta );
    sync->set_fileoffset    ( block->FileOffset );
    sync->set_index         ( block->Index );
    sync->set_partid        ( block->PartId );
    sync->set_path          ( block->Path );
    sync->set_size          ( block->Size );
    sync->set_status        ( 0 );
    MasterSession::Instance()->SendMessage( move_ptr( sync ) );

    return 0;
}
