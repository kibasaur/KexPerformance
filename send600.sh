#!/bin/bash
for i in {1..300}; 
do 
    ./cardano-cli-build/bin/cardano-cli transaction build \
        --alonzo-era \
        --testnet-magic 1097911063 \
        --change-address $(cat my_keys/02.addr) \
        --tx-in "45d980a65553c12bf9cbae563890b4d9dd8959ad286aea60ea353dbe81f39a3b#$i" \
        --tx-out "$(cat my_keys/01.addr) 1250000 lovelace" \
        --out-file tx/tx.body

    ./cardano-cli-build/bin/cardano-cli transaction sign \
        --tx-body-file tx/tx.body \
        --signing-key-file my_keys/02.skey \
        --testnet-magic 1097911063 \
        --out-file tx/tx.signed

    ./cardano-cli-build/bin/cardano-cli transaction submit \
        --testnet-magic 1097911063 \
        --tx-file tx/tx.signed;
done;

for i in {1..300}; 
do 
    ./cardano-cli-build/bin/cardano-cli transaction build \
        --alonzo-era \
        --testnet-magic 1097911063 \
        --change-address $(cat my_keys/02.addr) \
        --tx-in "5be9beac65ed7328f9958274634fd0540758a9d58068dc389786f2356272b725#$i" \
        --tx-out "$(cat my_keys/01.addr) 1250000 lovelace" \
        --out-file tx/tx.body

    ./cardano-cli-build/bin/cardano-cli transaction sign \
        --tx-body-file tx/tx.body \
        --signing-key-file my_keys/02.skey \
        --testnet-magic 1097911063 \
        --out-file tx/tx.signed

    ./cardano-cli-build/bin/cardano-cli transaction submit \
        --testnet-magic 1097911063 \
        --tx-file tx/tx.signed;
done;