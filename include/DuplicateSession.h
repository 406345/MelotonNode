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

#ifndef DUPLICATE_SESSION_H_
#define DUPLICATE_SESSION_H_

#include <MRT.h>
#include <MelotonSession.h>
#include <MessageDuplicateBlock.pb.h>
#include <BlockIndex.h>
#include <MessageDuplicateData.pb.h>

class DuplicateSession
    : public MelotonSession

{
public:

    DuplicateSession ( );
    DuplicateSession ( uptr<MessageDuplicateBlock> msg );
    ~DuplicateSession();

    void SendRequest();
    void AcceptBlock( uptr<MessageDuplicateData> msg );
    bool DuplicateFinish();

protected:

    void OnConnect      ()                    override;

private:

    uptr<MessageDuplicateBlock> message_block_ = nullptr;
    sptr<BlockIndex>            index_         = nullptr;
    size_t                      block_offset_  = 0;
    size_t                      index_num_     = 0;
    bool                        finish_        = false;

    size_t                      part_id_       = 0;
    std::string                 path_          = "";
    size_t                      file_offset_   = 0;
    size_t                      remote_index_  = 0;
    std::string                 remote_ip_     = "";

    MRT::SyncWorker*            worker_        = nullptr;
    void                        RetryTimer();
};

#endif // !DUPLICATE_SESSION_H_ 