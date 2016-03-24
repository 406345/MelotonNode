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

#ifndef BLOCK_HUB_H_
#define BLOCK_HUB_H_

#include <array>
#include <string>
#include <MRT.h>
#include <BlockIndex.h>
#include <MelotonNode.h>
#include <iostream>
#include <fstream>

using namespace MRT;
using namespace std;

class BlockHub
{
public:

    MAKE_SINGLETON( BlockHub );

    void             LoadIndex      ();
    sptr<BlockIndex> FindBlock      ( size_t index );

    size_t           BlockCount     () { return this->block_count_; };
    size_t           BlockEmptyCount() { return this->block_empty_count_; };

    sptr<BlockIndex> CreateBlock    ( int partId , 
                                      size_t fileOffset , 
                                      string path);

    bool             RemoveBlock    ( size_t index );

    size_t           WriteBlock     ( int blockid , 
                                      size_t offset ,
                                      const char* data ,
                                      size_t len );

    uptr<Buffer>     ReadBlock      ( int blockid , 
                                      size_t offset ,
                                      size_t len);

private:

    BlockHub ();
    ~BlockHub();

    array<sptr<BlockIndex>,BLOCK_INDEX_ARRAY_SIZE> index_list_;
    array<sptr<BlockIndex>,BLOCK_INDEX_ARRAY_SIZE> empty_list_;
    
    fstream index_file_;
    fstream data_file_;

    int     block_count_         = 0;
    int     block_empty_count_   = 0;


    void SaveBlockIndex( sptr<BlockIndex> block );
};


#endif // !BLOCK_HUB_H_ 