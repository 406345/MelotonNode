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
* Description   : MessagePrepareWrite handler.
* Creator       : Shubo Yang(shuboyang@yhgenomics.com)
* Date          : 2016-03-22
* Modifed       : 2016-03-22      | Shubo Yang      | Create
***********************************************************************************/

#include <string>
#include <MRT.h>
#include <MessagePrepareWrite.pb.h>
#include <TokenPool.h>
#include <MessagePrepareWriteACK.pb.h>
#include <ClientSession.h>
#include <BlockHub.h>
#include <MessageBlockMeta.pb.h>
#include <MasterSession.h>
#include <MessageSyncBlock.pb.h>
#include <Settings.h>

static int MessagePrepareWriteHandler( MRT::Session * session , uptr<MessagePrepareWrite> message )
{
    auto index              = message->index();
    auto master             = scast<MasterSession*>( session );
    sptr<BlockIndex> block  = nullptr;

    if ( index == 0 )
    {
        block = BlockHub::Instance()->CreateBlock( message->partid() ,
                                                   message->fileoffset() ,
                                                   message->path() );
        index = block->Index;
    }
    else
    {
        block = BlockHub::Instance()->FindBlock( index );
    }
    
    auto token  = TokenPool::Instance()->CreateToken( message->clientid() , 
                                                      index , 
                                                      TOKEN_EXPIRE_TIME );

    auto reply  = make_uptr( MessagePrepareWriteACK );
    reply->set_clientid    ( message->clientid() );
    reply->set_token       ( token );
    reply->set_fileoffset  ( block->FileOffset );
    reply->set_partid      ( block->PartId );
    reply->set_size        ( block->Size );
    reply->set_port        ( Settings::Instance()->ListenerPort() ); 
    master->SendMessage    ( move_ptr( reply ) );

    return 0;
}
