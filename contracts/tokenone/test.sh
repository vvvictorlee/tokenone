#!/usr/bin/env bash

. ../../scripts/boot/init.sh
action=$1

## variables
contract_name="tokenone"
account_name="tokenone"


if [ "${action}" == '' ];then
    ## step 1: bios boot.
    . ../../scripts/boot/boot.sh

    ## step 2: create account
    key1='5J4WkksPLoraSdf38773PRYFK8K85whAyxFPLC4VgZWJf9CM1UH|EOS8U45mWyvjKmjefEWirySNyWAGKjeCXzgi9zCig3r95jRY8ads2'
    create_account_and_import_key ${account_name} ${key1}
fi


if [[ "${action}" == '' || "${action}" == 'deploy' ]]; then
    ## setp 3: build and deploy contract.
    build_deploy_contract(){
        cd ${ROOT_DIR}/contracts/${contract_name}
        eosiocpp -o ${contract_name}.wast ${contract_name}.cpp
        eosiocpp -g ${contract_name}.abi  ${contract_name}.cpp
#        add_abi_types ${contract_name}.abi
        cd -

        $cleos set contract  ${account_name} /mycts/${contract_name} -p ${account_name}
    }
    build_deploy_contract
fi

if [[ "${action}" == '' || "${action}" == 'test' ]]; then
    test_create(){
        $cleos push action ${account_name} create '["chsong", "SONGT", "Song Token", "10000000000", "8"]' -p ${account_name}
        $cleos get table ${account_name}  ${account_name}  meta
    }




    create_and_issue_eos_token(){
        $cleos push action ${account_name} create '["token", "10000000000.0000 SONG"]' -p ${account_name}
        $cleos push action ${account_name} issue  '["token", "1000000000.0000 SONG", "memo"]' -p ${account_name}
    }
    #create_and_issue_eos_token







    test_contract(){
        #$cleos push action hello.code hi '["user"]' -p user
        #$cleos push action hello.code hi '["tester"]' -p tester

        $cleos push action ${account_name} echo '[""]' -p ${account_name}

    }
    #test_contract
fi