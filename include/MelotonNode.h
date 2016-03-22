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

/* * * * * * * * * * * * * * * *
* YHGenomics Inc.
* Author     : yang shubo
* Date       : 2015-11-11
* Description:
* * * * * * * * * * * * * * * */

#ifndef MELOTON_NODE_H_
#define MELOTON_NODE_H_ 

/* * * * * * * * * * * * * * * * * * * * * * * * * * *
  Const Section
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
static const size_t ALIVE_TIME              = 1000;
static const size_t BLOCK_INDEX_ARRAY_SIZE  = 1024 * 1024 * 10;
static const size_t BLOCK_SIZE              = 1024 * 1024 * 16;
static const size_t BLOCK_PATH_SIZE         = 256;
 
/* * * * * * * * * * * * * * * * * * * * * * * * * * *
  Enum Section
 * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * *
  Debug Section
 * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifdef _DEBUG

#define DEBUG_LOG(FMT,... ) Logger::Log( FMT,__VA_ARGS__)

#endif // DEBUG

#endif // !MELOTON_NODE_H_





