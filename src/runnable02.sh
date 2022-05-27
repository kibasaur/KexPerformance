.././cardano-cli-build/bin/cardano-cli transaction build --alonzo-era --testnet-magic 1097911063 --change-address $(cat ../my_keys/02.addr)  --tx-in "e58249971533465205622497de58f2347ac75de15307b2d17cc7875ca1eda3c8#0" --tx-out "$(cat ../my_keys/01.addr) 3876677656 lovelace" --out-file ../tx/tx.body
.././cardano-cli-build/bin/cardano-cli transaction sign --tx-body-file ../tx/tx.body --signing-key-file ../my_keys/02.skey --testnet-magic 1097911063 --out-file ../tx/tx.signed
.././cardano-cli-build/bin/cardano-cli transaction submit --testnet-magic 1097911063 --tx-file ../tx/tx.signed

