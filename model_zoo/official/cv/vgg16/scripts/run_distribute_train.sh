#!/bin/bash
# Copyright 2020 Huawei Technologies Co., Ltd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ============================================================================

if [ $# != 2 ]
then
    echo "Usage: sh run_distribute_train.sh [RANK_TABLE_FILE] [DATA_PATH]"
exit 1
fi

if [ ! -f $1 ]
then
    echo "error: RANK_TABLE_FILEH=$1 is not a file"
exit 1
fi

if [ ! -d $2 ]
then
    echo "error: DATA_PATH=$2 is not a directory"
exit 1
fi

export DEVICE_NUM=8
export RANK_SIZE=8
export RANK_TABLE_FILE=$1

for((i=0;i<RANK_SIZE;i++))
do
    export DEVICE_ID=$i
    export RANK_ID=$i
    rm -rf ./train_parallel$i
    mkdir ./train_parallel$i
    cp *.py ./train_parallel$i
    cp -r src ./train_parallel$i
    cd ./train_parallel$i || exit
    echo "start training for rank $RANK_ID, device $DEVICE_ID"
    env > env.log
    python train.py --data_path=$2 --device_target="Ascend" --device_id=$i &> log &
    cd ..
done