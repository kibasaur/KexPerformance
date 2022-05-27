
#!/bin/bash
for i in {1..400}; 
do 
    ./cardano-cli-build/bin/cardano-cli transaction build \
        --alonzo-era \
        --testnet-magic 1097911063 \
        --change-address $(cat my_keys/02.addr) \
        --tx-in "30bf8900fdc39e269624470c3e3b5c771ba646e765372720543fc3c91c4b4cc2#$i" \
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

for i in {1..400}; 
do 
    ./cardano-cli-build/bin/cardano-cli transaction build \
        --alonzo-era \
        --testnet-magic 1097911063 \
        --change-address $(cat my_keys/02.addr) \
        --tx-in "39db68904192d907008be24ccf537e8a328ad53c2570a85703a18de7650b80ba#$i" \
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

for i in {1..400}; 
do 
    ./cardano-cli-build/bin/cardano-cli transaction build \
        --alonzo-era \
        --testnet-magic 1097911063 \
        --change-address $(cat my_keys/02.addr) \
        --tx-in "e7a72c237f92b29a838f8ddfd76b6fe978c53aa6db1cf941373455a3c0d6bf96#$i" \
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

for i in {1..400}; 
do 
    ./cardano-cli-build/bin/cardano-cli transaction build \
        --alonzo-era \
        --testnet-magic 1097911063 \
        --change-address $(cat my_keys/02.addr) \
        --tx-in "2b2dccd5326074caecb52af73676b131ef94599dd134b7f7b2e827c7bd7f73a0#$i" \
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

for i in {1..400}; 
do 
    ./cardano-cli-build/bin/cardano-cli transaction build \
        --alonzo-era \
        --testnet-magic 1097911063 \
        --change-address $(cat my_keys/02.addr) \
        --tx-in "19e215ae054d05245e7418eecac89e9edcae4828039991b3ba9268a026d5ffbf#$i" \
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